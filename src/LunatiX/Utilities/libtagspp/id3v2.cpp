/*
 * Have fun reading the following:
 *
 * http://id3.org/id3v2.4.0-structure
 * http://id3.org/id3v2.4.0-frames
 * http://id3.org/d3v2.3.0
 * http://id3.org/id3v2-00
 * http://mpgedit.org/mpgedit/mpeg_format/mpeghdr.htm
 * http://wiki.hydrogenaud.io/index.php?title=MP3#VBRI.2C_XING.2C_and_LAME_headers
 * http://www.codeproject.com/Articles/8295/MPEG-Audio-Frame-Header#VBRIHeader
 */
#include <LunatiX/utils/libtagspp/tagspriv.h>

#define synchsafe(d) (uint)(((d)[0]&127)<<21 | ((d)[1]&127)<<14 | ((d)[2]&127)<<7 | ((d)[3]&127)<<0)
#define beuint(d) (uint)((d)[0]<<24 | (d)[1]<<16 | (d)[2]<<8 | (d)[3]<<0)

static int v2cb(Tagctx *ctx, char *k, char *v)
{
    k++;
    if(std::strcmp(k, "AL") == 0 || std::strcmp(k, "ALB") == 0)
        txtcb(ctx, Talbum, v);
    else if(std::strcmp(k, "PE1") == 0 || std::strcmp(k, "PE2") == 0 ||
            std::strcmp(k, "P1") == 0 || std::strcmp(k, "P2") == 0)
        txtcb(ctx, Tartist, v);
    else if(std::strcmp(k, "IT2") == 0 || std::strcmp(k, "T2") == 0)
        txtcb(ctx, Ttitle, v);
    else if(std::strcmp(k, "YE") == 0 || std::strcmp(k, "YER") == 0 || std::strcmp(k, "DRC") == 0)
        txtcb(ctx, Tdate, v);
    else if(std::strcmp(k, "RK") == 0 || std::strcmp(k, "RCK") == 0)
        txtcb(ctx, Ttrack, v);
    else if(std::strcmp(k, "CO") == 0 || std::strcmp(k, "CON") == 0)
    {
        for(; v[0]; v++)
        {
            if(v[0] == '(' && v[1] <= '9' && v[1] >= '0')
            {
                int i = atoi(&v[1]);
                if(i < Numgenre)
                    txtcb(ctx, Tgenre, id3genres[i]);
                for(v++; v[0] && v[0] != ')'; v++);
                v--;
            }
            else if(v[0] != '(' && v[0] != ')')
            {
                txtcb(ctx, Tgenre, v);
                break;
            }
        }
    }
    else if(std::strcmp(k, "XXX") == 0 && std::strncmp(v, "REPLAYGAIN_", 11) == 0)
    {
        int type = -1;
        v += 11;
        if(std::strncmp(v, "TRACK_", 6) == 0)
        {
            v += 6;
            if(std::strcmp(v, "GAIN") == 0)
                type = Ttrackgain;
            else if(std::strcmp(v, "PEAK") == 0)
                type = Ttrackpeak;
        }
        else if(std::strncmp(v, "ALBUM_", 6) == 0)
        {
            v += 6;
            if(std::strcmp(v, "GAIN") == 0)
                type = Talbumgain;
            else if(std::strcmp(v, "PEAK") == 0)
                type = Talbumpeak;
        }
        if(type >= 0)
            txtcb(ctx, type, v+5);
        else
            return 0;
    }
    else
        return 0;
    return 1;
}

static int rva2(Tagctx *ctx, char *tag, int sz)
{
    uchar *b, *end;

    if((b = (uchar*) std::memchr(tag, 0, sz)) == nil)
        return -1;
    b++;
    for(end = (uchar*)tag+sz; b+4 < end; b += 5)
    {
        int type = b[0];
        float peak;
        float va = (float)(b[1]<<8 | b[2]) / 512.0f;

        if(b[3] == 24)
        {
            peak = (float)(b[4]<<16 | b[5]<<8 | b[6]) / 32768.0f;
            b += 2;
        }
        else if(b[3] == 16)
        {
            peak = (float)(b[4]<<8 | b[5]) / 32768.0f;
            b += 1;
        }
        else if(b[3] == 8)
        {
            peak = (float)b[4] / 32768.0f;
        }
        else
            return -1;

        if(type == 1)  /* master volume */
        {
            char vas[16], peaks[8];
            snprint(vas, sizeof(vas), "%+.5f dB", va);
            snprint(peaks, sizeof(peaks), "%.5f", peak);
            vas[sizeof(vas)-1] = 0;
            peaks[sizeof(peaks)-1] = 0;

            if(std::strcmp((char*)tag, "track") == 0)
            {
                txtcb(ctx, Ttrackgain, vas);
                txtcb(ctx, Ttrackpeak, peaks);
            }
            else if(std::strcmp((char*)tag, "album") == 0)
            {
                txtcb(ctx, Talbumgain, vas);
                txtcb(ctx, Talbumpeak, peaks);
            }
            break;
        }
    }
    return 0;
}

static int resync(uchar *b, int sz)
{
    int i;

    if(sz < 4)
        return sz;
    for(i = 0; i < sz-2; i++)
    {
        if(b[i] == 0xff && b[i+1] == 0x00 && (b[i+2] & 0xe0) == 0xe0)
        {
            std::memmove(&b[i+1], &b[i+2], sz-i-2);
            sz--;
        }
    }
    return sz;
}

static int unsyncread(void *buf, int *sz)
{
    int i;
    uchar *b;

    b = (uchar*) buf;
    for(i = 0; i < *sz; i++)
    {
        if(b[i] == 0xff)
        {
            if(i+1 >= *sz || (b[i+1] == 0x00 && i+2 >= *sz))
                break;
            if(b[i+1] == 0x00 && (b[i+2] & 0xe0) == 0xe0)
            {
                std::memmove(&b[i+1], &b[i+2], *sz-i-2);
                (*sz)--;
            }
        }
    }
    return i;
}

static int nontext(Tagctx *ctx, uchar *d, int tsz, int unsync)
{
    int n, offset;
    char *b, *tag;
    Tagread f;

    tag = ctx->buf;
    n = 0;
    f = unsync ? unsyncread : nil;
    if(std::strcmp((char*)d, "APIC") == 0)
    {
        offset = ctx->seek(ctx, 0, 1);
        if((n = ctx->read(ctx, tag, 256)) == 256)  /* APIC mime and description should fit */
        {
            b = tag + 1; /* mime type */
            for(n = 1 + strlen(b) + 2; n < 253; n++)
            {
                if(tag[0] == 0 || tag[0] == 3)  /* one zero byte */
                {
                    if(tag[n] == 0)
                    {
                        n++;
                        break;
                    }
                }
                else if(tag[n] == 0 && tag[n+1] == 0 && tag[n+2] == 0)
                {
                    n += 3;
                    break;
                }
            }
            tagscallcb(ctx, Timage, b, offset+n, tsz-n, f);
            n = 256;
        }
    }
    else if(std::strcmp((char*)d, "PIC") == 0)
    {
        offset = ctx->seek(ctx, 0, 1);
        if((n = ctx->read(ctx, tag, 256)) == 256)  /* PIC description should fit */
        {
            b = tag + 1; /* mime type */
            for(n = 5; n < 253; n++)
            {
                if(tag[0] == 0 || tag[0] == 3)  /* one zero byte */
                {
                    if(tag[n] == 0)
                    {
                        n++;
                        break;
                    }
                }
                else if(tag[n] == 0 && tag[n+1] == 0 && tag[n+2] == 0)
                {
                    n += 3;
                    break;
                }
            }
            tagscallcb(ctx, Timage, std::strcmp(b, "JPG") == 0 ? "image/jpeg" : "image/png", offset+n, tsz-n, f);
            n = 256;
        }
    }
    else if(std::strcmp((char*)d, "RVA2") == 0 && tsz >= 6+5)
    {
        /* replay gain. 6 = "track\0", 5 = other */
        if(ctx->bufsz >= tsz && (n = ctx->read(ctx, tag, tsz)) == tsz)
            rva2(ctx, tag, unsync ? resync((uchar*)tag, n) : n);
    }

    return ctx->seek(ctx, tsz-n, 1) < 0 ? -1 : 0;
}

static int text(Tagctx *ctx, uchar *d, int tsz, int unsync)
{
    char *b, *tag;

    if(ctx->bufsz >= tsz+1)
    {
        /* place the data at the end to make best effort at charset conversion */
        tag = &ctx->buf[ctx->bufsz - tsz - 1];
        if(ctx->read(ctx, tag, tsz) != tsz)
            return -1;
    }
    else
    {
        ctx->seek(ctx, tsz, 1);
        return 0;
    }

    if(unsync)
        tsz = resync((uchar*)tag, tsz);

    tag[tsz] = 0;
    b = &tag[1];

    switch(tag[0])
    {
    case 0:     /* iso-8859-1 */
        if(iso88591toutf8((uchar*)ctx->buf, ctx->bufsz, (uchar*)b, tsz) > 0)
            v2cb(ctx, (char*)d, ctx->buf);
        break;

    case 1:     /* utf-16 */
    case 2:
        if(utf16to8((uchar*)ctx->buf, ctx->bufsz, (uchar*)b, tsz) > 0)
            v2cb(ctx, (char*)d, ctx->buf);
        break;
    case 3:     /* utf-8 */
        if(*b)
            v2cb(ctx, (char*)d, b);
        break;

    default:    /* Unknown format */
        return -1;
        break;
    }

    return 0;
}

static int isid3(uchar *d)
{
    /* "ID3" version[2] flags[1] size[4] */
    return (
               d[0] == 'I' && d[1] == 'D' && d[2] == '3' &&
               d[3] < 0xff && d[4] < 0xff &&
               d[6] < 0x80 && d[7] < 0x80 && d[8] < 0x80 && d[9] < 0x80
           );
}

static const uchar bitrates[4][4][16] =
{
    {
        {0},
        {0,  4,  8, 12, 16, 20, 24, 28, 32, 40, 48, 56, 64,  72,  80, 0}, /* v2.5 III */
        {0,  4,  8, 12, 16, 20, 24, 28, 32, 40, 48, 56, 64,  72,  80, 0}, /* v2.5 II */
        {0, 16, 24, 28, 32, 40, 48, 56, 64, 72, 80, 88, 96, 112, 128, 0}, /* v2.5 I */
    },
    { {0}, {0}, {0}, {0} },
    {
        {0},
        {0,  4,  8, 12, 16, 20, 24, 28, 32, 40, 48, 56, 64,  72,  80, 0}, /* v2 III */
        {0,  4,  8, 12, 16, 20, 24, 28, 32, 40, 48, 56, 64,  72,  80, 0}, /* v2 II */
        {0, 16, 24, 28, 32, 40, 48, 56, 64, 72, 80, 88, 96, 112, 128, 0}, /* v2 I */
    },
    {
        {0},
        {0, 16, 20, 24, 28, 32, 40,  48,  56,  64,  80,  96, 112, 128, 160, 0}, /* v1 III */
        {0, 16, 24, 28, 32, 40, 48,  56,  64,  80,  96, 112, 128, 160, 192, 0}, /* v1 II */
        {0, 16, 32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 0}, /* v1 I */
    }
};

static const uint samplerates[4][4] =
{
    {11025, 12000,  8000, 0},
    {    0,     0,     0, 0},
    {22050, 24000, 16000, 0},
    {44100, 48000, 32000, 0},
};

static const int chans[] = {2, 2, 2, 1};

static const int samplesframe[4][4] =
{
    {0,    0,    0,   0},
    {0,  576, 1152, 384},
    {0,  576, 1152, 384},
    {0, 1152, 1152, 384},
};

static void getduration(Tagctx *ctx, int offset)
{
    uvlong n, framelen, samplespf;
    uchar *b;
    uint x;
    int xversion, xlayer, xbitrate;

    if(ctx->read(ctx, ctx->buf, 64) != 64)
        return;

    x = beuint((uchar*)ctx->buf);
    xversion = x >> 19 & 3;
    xlayer = x >> 17 & 3;
    xbitrate = x >> 12 & 0xf;
    ctx->bitrate = 2000*(int)bitrates[xversion][xlayer][xbitrate];
    samplespf = samplesframe[xversion][xlayer];

    ctx->samplerate = samplerates[xversion][x >> 10 & 3];
    ctx->channels = chans[x >> 6 & 3];

    if(ctx->samplerate > 0)
    {
        framelen = (uvlong)144*ctx->bitrate / ctx->samplerate;
        if((x & (1<<9)) != 0) /* padding */
            framelen += xlayer == 3 ? 4 : 1; /* for I it's 4 bytes */

        if(memcmp(&ctx->buf[0x24], "Info", 4) == 0 || memcmp(&ctx->buf[0x24], "Xing", 4) == 0)
        {
            b = (uchar*)ctx->buf + 0x28;
            x = beuint(b);
            b += 4;
            if((x & 1) != 0)  /* number of frames is set */
            {
                n = beuint(b);
                b += 4;
                ctx->duration = n * samplespf * 1000 / ctx->samplerate;
            }

            if(ctx->duration == 0 && (x & 2) != 0 && framelen > 0)  /* file size is set */
            {
                n = beuint(b);
                ctx->duration = n * samplespf * 1000 / framelen / ctx->samplerate;
            }
        }
        else if(memcmp(&ctx->buf[0x24], "VBRI", 4) == 0)
        {
            n = beuint((uchar*)&ctx->buf[0x32]);
            ctx->duration = n * samplespf * 1000 / ctx->samplerate;

            if(ctx->duration == 0 && framelen > 0)
            {
                n = beuint((uchar*)&ctx->buf[0x28]); /* file size */
                ctx->duration = n * samplespf * 1000 / framelen / ctx->samplerate;
            }
        }
    }

    if(ctx->bitrate > 0 && ctx->duration == 0) /* worst case -- use real file size instead */
        ctx->duration = (ctx->seek(ctx, 0, 2) - offset)/(ctx->bitrate / 1000) * 8;
}

int tagid3v2(Tagctx *ctx);

int tagid3v2(Tagctx *ctx)
{
    int sz, exsz, framesz;
    int ver, unsync, offset;
    uchar d[10], *b;

    if(ctx->read(ctx, d, sizeof(d)) != sizeof(d))
        return -1;
    if(!isid3(d))  /* no tags, but the stream information is there */
    {
        if(d[0] != 0xff || (d[1] & 0xe0) != 0xe0)
            return -1;
        ctx->seek(ctx, -(int)sizeof(d), 1);
        getduration(ctx, 0);
        return 0;
    }

header:
    ver = d[3];
    unsync = d[5] & (1<<7);
    sz = synchsafe(&d[6]);

    if(ver == 2 && (d[5] & (1<<6)) != 0) /* compression */
        return -1;

    if(ver > 2)
    {
        if((d[5] & (1<<4)) != 0) /* footer */
            sz -= 10;
        if((d[5] & (1<<6)) != 0)  /* skip extended header */
        {
            if(ctx->read(ctx, d, 4) != 4)
                return -1;
            exsz = (ver >= 3) ? beuint(d) : synchsafe(d);
            if(ctx->seek(ctx, exsz, 1) < 0)
                return -1;
            sz -= exsz;
        }
    }

    framesz = (ver >= 3) ? 10 : 6;
    for(; sz > framesz;)
    {
        int tsz, frameunsync;

        if(ctx->read(ctx, d, framesz) != framesz)
            return -1;
        sz -= framesz;

        /* return on padding */
        if(memcmp(d, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", framesz) == 0)
            break;
        if(ver >= 3)
        {
            tsz = (ver == 3) ? beuint(&d[4]) : synchsafe(&d[4]);
            if(tsz < 0 || tsz > sz)
                break;
            frameunsync = d[9] & (1<<1);
            d[4] = 0;

            if((d[9] & 0x0c) != 0)  /* compression & encryption */
            {
                ctx->seek(ctx, tsz, 1);
                sz -= tsz;
                continue;
            }
            if(ver == 4 && (d[9] & 1<<0) != 0)  /* skip data length indicator */
            {
                ctx->seek(ctx, 4, 1);
                sz -= 4;
                tsz -= 4;
            }
        }
        else
        {
            tsz = beuint(&d[3]) >> 8;
            if(tsz > sz)
                return -1;
            frameunsync = 0;
            d[3] = 0;
        }
        sz -= tsz;

        if(d[0] == 'T' && text(ctx, d, tsz, unsync || frameunsync) != 0)
            return -1;
        else if(d[0] != 'T' && nontext(ctx, d, tsz, unsync || frameunsync) != 0)
            return -1;
    }

    offset = ctx->seek(ctx, sz, 1);
    sz = ctx->bufsz <= 2048 ? ctx->bufsz : 2048;
    b = nil;
    for(exsz = 0; exsz < 2048; exsz += sz)
    {
        if(ctx->read(ctx, ctx->buf, sz) != sz)
            break;
        for(b = (uchar*)ctx->buf; (b = (uchar*) std::memchr(b, 'I', sz - 1 - ((char*)b - ctx->buf))) != nil; b++)
        {
            ctx->seek(ctx, (char*)b - ctx->buf + offset + exsz, 0);
            if(ctx->read(ctx, d, sizeof(d)) != sizeof(d))
                return 0;
            if(isid3(d))
                goto header;
        }
        if((b = (uchar*) std::memchr(ctx->buf, 0xff, sz-1)) != nil && (b[1] & 0xe0) == 0xe0)
        {
            offset = ctx->seek(ctx, (char*)b - ctx->buf + offset + exsz, 0);
            break;
        }
    }

    if(b != nil)
        getduration(ctx, offset);

    return 0;
}
