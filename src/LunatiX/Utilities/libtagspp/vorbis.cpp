/*
 * https://xiph.org/vorbis/doc/Vorbis_I_spec.html#x1-810005
 * https://wiki.xiph.org/VorbisComment
 */
#include <LunatiX/utils/libtagspp/tagspriv.h>

#define leuint(d) (uint)(((uchar*)(d))[3]<<24 | ((uchar*)(d))[2]<<16 | ((uchar*)(d))[1]<<8 | ((uchar*)(d))[0]<<0)

void cbvorbiscomment( Tagctx * ctx, char * k, char * v )
{
    if ( *v == 0 )
        return;
    if ( cistrcmp( k, "album" ) == 0 )
        txtcb( ctx, Talbum, v );
    else if ( cistrcmp( k, "title" ) == 0 )
        txtcb( ctx, Ttitle, v );
    else if ( cistrcmp( k, "artist" ) == 0 || cistrcmp( k, "performer" ) == 0 )
        txtcb( ctx, Tartist, v );
    else if ( cistrcmp( k, "tracknumber" ) == 0 )
        txtcb( ctx, Ttrack, v );
    else if ( cistrcmp( k, "date" ) == 0 )
        txtcb( ctx, Tdate, v );
    else if ( cistrcmp( k, "replaygain_track_peak" ) == 0 )
        txtcb( ctx, Ttrackpeak, v );
    else if ( cistrcmp( k, "replaygain_track_gain" ) == 0 )
        txtcb( ctx, Ttrackgain, v );
    else if ( cistrcmp( k, "replaygain_album_peak" ) == 0 )
        txtcb( ctx, Talbumpeak, v );
    else if ( cistrcmp( k, "replaygain_album_gain" ) == 0 )
        txtcb( ctx, Talbumgain, v );
    else if ( cistrcmp( k, "genre" ) == 0 )
        txtcb( ctx, Tgenre, v );
}

int tagvorbis( Tagctx * ctx );

int tagvorbis( Tagctx * ctx )
{
    char * v;
    uchar * d, h[4];
    int sz, numtags, i, npages;

    d = ( uchar * )ctx->buf;
    /* need to find vorbis frame with type=3 */
    for ( npages = 0; npages < 2; npages++ ) /* vorbis comment is the second header */
    {
        int nsegs;
        if ( ctx->read( ctx, d, 27 ) != 27 )
            return -1;
        if ( std::memcmp( d, "OggS", 4 ) != 0 )
            return -1;

        /* calculate the size of the packet */
        nsegs = d[26];
        if ( ctx->read( ctx, d, nsegs + 1 ) != nsegs + 1 )
            return -1;
        for ( sz = i = 0; i < nsegs; sz += d[i++] );

        if ( d[nsegs] == 3 ) /* comment */
            break;
        if ( d[nsegs] == 1 && sz >= 28 ) /* identification */
        {
            if ( ctx->read( ctx, d, 28 ) != 28 )
                return -1;
            sz -= 28;
            ctx->channels = d[10];
            ctx->samplerate = leuint( &d[11] );
            if ( ( ctx->bitrate = leuint( &d[15] ) ) == 0 ) /* maximum */
                ctx->bitrate = leuint( &d[19] ); /* nominal */
        }

        ctx->seek( ctx, sz - 1, 1 );
    }

    if ( ctx->read( ctx, &d[1], 10 ) != 10 || std::memcmp( &d[1], "vorbis", 6 ) != 0 )
        return -1;
    sz = leuint( &d[7] );
    if ( ctx->seek( ctx, sz, 1 ) < 0 || ctx->read( ctx, h, 4 ) != 4 )
        return -1;
    numtags = leuint( h );

    for ( i = 0; i < numtags; i++ )
    {
        if ( ctx->read( ctx, h, 4 ) != 4 )
            return -1;
        if ( ( sz = leuint( h ) ) < 0 )
            return -1;

        if ( ctx->bufsz < sz + 1 )
        {
            if ( ctx->seek( ctx, sz, 1 ) < 0 )
                return -1;
            continue;
        }
        if ( ctx->read( ctx, ctx->buf, sz ) != sz )
            return -1;
        ctx->buf[sz] = 0;

        if ( ( v = strchr( ctx->buf, '=' ) ) == nil )
            return -1;
        *v++ = 0;
        cbvorbiscomment( ctx, ctx->buf, v );
    }

    /* calculate the duration */
    if ( ctx->samplerate > 0 )
    {
        sz = ctx->bufsz <= 4096 ? ctx->bufsz : 4096;
        for ( i = sz; i < 65536 + 16; i += sz - 16 )
        {
            if ( ctx->seek( ctx, -i, 2 ) <= 0 )
                break;
            v = ctx->buf;
            if ( ctx->read( ctx, v, sz ) != sz )
                break;
            for ( ; v != nil && v < ctx->buf + sz; )
            {
                v = ( char * ) std::memchr( v, 'O', ctx->buf + sz - v - 14 );
                if ( v != nil && v[1] == 'g' && v[2] == 'g' && v[3] == 'S' && ( v[5] & 4 ) == 4 ) /* last page */
                {
                    uvlong g = leuint( v + 6 ) | ( uvlong )leuint( v + 10 ) << 32;
                    ctx->duration = g * 1000 / ctx->samplerate;
                    return 0;
                }
                if ( v != nil )
                    v++;
            }
        }
    }

    return 0;
}
