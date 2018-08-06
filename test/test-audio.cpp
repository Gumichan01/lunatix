
#include <Lunatix/Lunatix.hpp>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <string>

void test_audioInit();
void test_channels();
void test_music();
void test_chunk();
void test_effects();
void test_volume();
void test_volume2();
void test_volume_( const unsigned ex );
void test_info( const std::string& s );


int main( int argc, char ** argv )
{
    bool err = lx::init();

    if ( !err )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - lx::init() failed" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - The LunatiX library has been initialized with success" );

    lx::Log::setDebugMode();
    lx::Log::log( " ==== Test Audio ==== " );
    test_audioInit();
    test_channels();
    test_music();
    test_chunk();
    test_effects();
    test_volume();
    test_volume2();
    lx::Log::log( " ==== End Audio ==== " );

    lx::quit();

    return EXIT_SUCCESS;
}


void test_info( const std::string& s )
{
    const lx::Mixer::MusicTag tag = lx::Mixer::getMusicInfoFrom( s );

    try
    {
        lx::Win::WindowInfo info;
        lx::Win::initWindowInfo( info );
        info.w = 256;
        info.h = 256;
        lx::Win::Window w( info );

        if ( tag.img != nullptr )
        {
            lx::Log::log( "File: %s", s.c_str() );
            lx::Log::log( "================================" );
            lx::Log::log( "Title - %s", tag.title.utf8_str() );
            lx::Log::log( "Artist - %s", tag.artist.utf8_str() );
            lx::Log::log( "Album - %s", tag.album.utf8_str() );
            lx::Log::log( "Year - %s", tag.year.utf8_str() );
            lx::Log::log( "--------------------------------" );
            lx::Log::log( "Duration - %s", tag.duration.utf8_str() );
            lx::Log::log( "Format - %s", tag.format.utf8_str() );
            lx::Log::log( "================================" );

            lx::Graphics::Sprite * cover = tag.img->generateSprite( w );
            lx::Log::logInfo( lx::Log::TEST, "cover opened" );

            w.clearWindow();
            lx::Graphics::ImgRect box{0, 0, info.w, info.h};
            cover->draw( box );
            w.update();
            lx::Time::delay( 2000 );
            delete cover;
        }
    }
    catch ( lx::Graphics::ImageException& ie )
    {
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - %s", ie.what() );
    }
}


void test_audioInit()
{
    lx::Log::logInfo( lx::Log::APPLICATION, " = TEST audio = " );

    int n, freq, channels;
    Uint16 format;
    lx::Log::logInfo( lx::Log::TEST, "Get information about the library" );
    n = Mix_QuerySpec( &freq, &format, &channels );

    if ( n == 0 )
    {
        lx::Log::logError( lx::Log::TEST, "Cannot get information: %s",
                           Mix_GetError() );
    }
    else
    {
        std::string format_str = "Unknown";

        switch ( format )
        {
        case AUDIO_U8:
            format_str = "U8";
            break;
        case AUDIO_S8:
            format_str = "S8";
            break;
        case AUDIO_U16LSB:
            format_str = "U16LSB";
            break;
        case AUDIO_S16LSB:
            format_str = "S16LSB";
            break;
        case AUDIO_U16MSB:
            format_str = "U16MSB";
            break;
        case AUDIO_S16MSB:
            format_str = "S16MSB";
            break;
        default:
            break;
        }
        lx::Log::logInfo( lx::Log::TEST, "opened = %d time(s)", n );
        lx::Log::logInfo( lx::Log::TEST, "frequency = %d Hz", freq );
        lx::Log::logInfo( lx::Log::TEST, "format = %s", format_str.c_str() );
        lx::Log::logInfo( lx::Log::TEST, "channels = %d", channels );

        int m = Mix_GetNumChunkDecoders();

        lx::Log::logInfo( lx::Log::TEST, "Get the chunk decoders" );
        for ( int i = 0; i < m; i++ )
        {
            lx::Log::logInfo( lx::Log::TEST, "Sample chunk decoder %d: %s",
                              i, Mix_GetChunkDecoder( i ) );
        }

        m = Mix_GetNumMusicDecoders();

        lx::Log::logInfo( lx::Log::TEST, "Get the music decoders" );
        for ( int j = 0; j < m; j++ )
        {
            lx::Log::logInfo( lx::Log::TEST, "Sample chunk decoder %d: %s",
                              j, Mix_GetMusicDecoder( j ) );
        }

        lx::Log::logInfo( lx::Log::TEST, "Allocated channel(s): %d", lx::Mixer::allocateChannels( -1 ) );
    }

    lx::Log::logInfo( lx::Log::APPLICATION, " = END TEST = " );
}

void test_channels()
{
    const int N = 32;
    lx::Log::logInfo( lx::Log::APPLICATION, " = TEST channels = " );
    lx::Log::logInfo( lx::Log::APPLICATION, "%d channel(s)", lx::Mixer::allocateChannels( -1 ) );
    lx::Log::logInfo( lx::Log::APPLICATION, "Trying to get %d channels", N );

    int res = lx::Mixer::allocateChannels( N );

    if ( res == N )
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - %d channel(s)",
                          lx::Mixer::allocateChannels( -1 ) );
    else
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - expected: %d; got: %d",
                          N, res );

    lx::Log::logInfo( lx::Log::APPLICATION, "Trying to reserve channels from 0 to 7 in group 1" );
    lx::Mixer::groupChannels( 0, 7, 1 );
    lx::Log::logInfo( lx::Log::APPLICATION, "Trying to reserve channels from 9 to 15 in group 2" );
    lx::Mixer::groupChannels( 8, 15, 2 );
    int g1 = lx::Mixer::groupCount( 1 );
    int g2 = lx::Mixer::groupCount( 2 );

    lx::Log::logInfo( lx::Log::APPLICATION, "In group 1: %d channel(s)", g1 );
    lx::Log::logInfo( lx::Log::APPLICATION, "In group 2: %d channel(s)", g2 );

    const int M = 24;
    lx::Log::logInfo( lx::Log::APPLICATION, "Try to reserve %d channel(s)", M );
    int r1 = lx::Mixer::reserveChannels( M );
    lx::Log::logInfo( lx::Log::APPLICATION, "Reserved: %d channel(s)", r1 );
    lx::Log::logInfo( lx::Log::APPLICATION, "Done" );
    r1 = lx::Mixer::reserveChannels( 0 );
    lx::Log::logInfo( lx::Log::APPLICATION, "Reserved: %d channel(s)", r1 );

    // Play a chunk in a specific channel
    std::string sc0 = "data/explosion.wav";
    std::string sc = "data/01.ogg";
    lx::Mixer::Chunk chunk( sc0 );
    lx::Mixer::Chunk chunk0( sc );

    lx::Log::logInfo( lx::Log::APPLICATION, "Available channel before playing: %d",
                      lx::Mixer::channelAvailable( 1 ) );
    lx::Log::logInfo( lx::Log::APPLICATION, "Available channel before playing: %d",
                      lx::Mixer::channelAvailable( 2 ) );

    lx::Log::logInfo( lx::Log::APPLICATION, "Playing a chunk in the 2 groups" );
    lx::Mixer::MixerEffect me;
    lx::Mixer::groupPlayChunk( chunk0, 1, me );
    lx::Mixer::groupPlayChunk( chunk, 2, me );

    lx::Log::logInfo( lx::Log::APPLICATION, "Available channel (grp 1): %d",
                      lx::Mixer::channelAvailable( 1 ) );
    lx::Log::logInfo( lx::Log::APPLICATION, "Available channel (grp 2): %d",
                      lx::Mixer::channelAvailable( 2 ) );

    lx::Time::delay( 2000 );
    lx::Mixer::groupPlayChunk( chunk0, 1, me );
    lx::Time::delay( 500 );
    lx::Mixer::groupPlayChunk( chunk, 2, me );
    lx::Time::delay( 200 );
    lx::Mixer::groupPlayChunk( chunk, 2, me );
    lx::Time::delay( 200 );
    lx::Mixer::groupPlayChunk( chunk, 2, me );
    lx::Time::delay( 200 );
    lx::Mixer::groupPlayChunk( chunk, 2, me );
    lx::Time::delay( 200 );
    lx::Mixer::groupPlayChunk( chunk, 2, me );
    lx::Time::delay( 1000 );
    lx::Log::logInfo( lx::Log::APPLICATION, "Halt group 1" );
    lx::Mixer::haltGroup( 1 );
    lx::Log::logInfo( lx::Log::APPLICATION, "Done" );

    lx::Log::logInfo( lx::Log::APPLICATION, "Reset the groups" );
    int g3 = lx::Mixer::groupChannels( 0, 15, -1 );
    lx::Log::logInfo( lx::Log::APPLICATION, "Reset: %d channel(s)", g3 );

    lx::Mixer::allocateChannels( 8 );
    lx::Log::logInfo( lx::Log::APPLICATION, " = END TEST = " );
}

void test_music()
{
    lx::Log::logInfo( lx::Log::APPLICATION, " = TEST music = " );
    std::string s = "data/test.mp3";
    std::string sm = "data/01.ogg";

    lx::Log::logInfo( lx::Log::TEST, "Launch music: %s", s.c_str() );

    try
    {
        lx::Mixer::Music music( s );
    }
    catch ( lx::Mixer::MixerException& se )
    {
        lx::Log::log( "mp3 file not loaded" );
        lx::Log::log( "%s", se.what() );
    }

    test_info( s );

    try
    {
        lx::Mixer::Music music( sm );
        lx::Log::log( "SUCCESS - Loaded" );

        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - music loaded" );
        lx::Log::logInfo( lx::Log::TEST, "play music" );

        if ( music.play() )
        {
            lx::Log::logInfo( lx::Log::TEST, "SUCCESS - play music OK" );
            lx::Time::delay( 4000 );
            music.pause();
            lx::Log::logInfo( lx::Log::TEST, "music paused during 1 second" );
            lx::Time::delay( 1000 );
            music.pause();
            lx::Log::logInfo( lx::Log::TEST, "music resumed" );
            lx::Time::delay( 2000 );
            music.stop();
            lx::Log::logInfo( lx::Log::TEST, "music stopped" );
        }
        else
            lx::Log::logInfo( lx::Log::TEST, "FAILURE - play music KO" );

        const libtagpp::Tag& tag = music.getInfo();
        lx::Log::log( "================================" );
        lx::Log::log( "Title - %s", tag.title() );
        lx::Log::log( "Artist - %s", tag.artist() );
        lx::Log::log( "Album - %s", tag.album() );
        lx::Log::log( "Year - %s", tag.year() );
        lx::Log::log( "--------------------------------" );
        lx::Log::log( "Image - position %d %d", tag.getImageMetaData()._img_offset,
                      tag.getImageMetaData()._img_size );
        lx::Log::log( "Duration - %s", tag.properties().duration.c_str() );
        lx::Log::log( "Channels - %d", tag.properties().channels );
        lx::Log::log( "Sample rate - %d Hz", tag.properties().samplerate );
        lx::Log::log( "Bitrate - %d bits/s", tag.properties().bitrate );
        lx::Log::log( "Format - %s", tag.properties().format.c_str() );
        lx::Log::log( "================================" );

        lx::Log::logCritical( lx::Log::APPLICATION, "DANGER ZONE IN" );
        lx::Log::logCritical( lx::Log::APPLICATION, "play" );
        music.play();
        lx::Log::logCritical( lx::Log::APPLICATION, "stop" );
        music.stop();
        lx::Log::logCritical( lx::Log::APPLICATION, "play" );
        music.play();
        lx::Log::logCritical( lx::Log::APPLICATION, "pause" );
        music.pause();
        lx::Log::logCritical( lx::Log::APPLICATION, "stop" );
        music.stop();
        lx::Log::logCritical( lx::Log::APPLICATION, "pause" );
        music.pause();
        lx::Log::logCritical( lx::Log::APPLICATION, "fadeIn" );
        music.fadeIn( 1000 );
        lx::Log::logCritical( lx::Log::APPLICATION, "fadeOut" );
        music.fadeOut( 1000 );
        lx::Log::logCritical( lx::Log::APPLICATION, "DANGER ZONE OUT" );
    }
    catch ( lx::Mixer::MixerException& se )
    {
        lx::Log::log( "FAILURE - not loaded" );
        lx::Log::log( "%s", se.what() );
    }

    lx::Log::logInfo( lx::Log::TEST, "Launch music: <empty_string>" );

    try
    {
        lx::Mixer::Music * mus = new lx::Mixer::Music( std::string() );
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - music launched, it should not" );
        delete mus;
    }
    catch ( lx::Mixer::MixerException& se )
    {
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - music: not launched as expected" );
        lx::Log::log( "%s", se.what() );
    }

    lx::Log::logInfo( lx::Log::APPLICATION, " = END TEST = " );
}

void test_chunk()
{
    lx::Log::logInfo( lx::Log::APPLICATION, " = TEST chunk = " );

    std::string s = "data/explosion.wav";
    lx::Mixer::Chunk * chunk = nullptr;

    lx::Log::logInfo( lx::Log::TEST, "Launch music: %s", s.c_str() );

    try
    {
        chunk = new lx::Mixer::Chunk( s );
        lx::Log::log( "SUCCESS - Loaded" );

        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - chunk launched" );
        lx::Log::logInfo( lx::Log::TEST, "play chunk with no loop on any channel" );

        lx::Time::delay( 1000 );
        // play on any channel (no loop)
        if ( chunk->play() )
            lx::Log::logInfo( lx::Log::TEST, "SUCCESS - play chunk (no loop) OK" );
        else
            lx::Log::logInfo( lx::Log::TEST, "FAILURE - play chunk (no loop) KO" );

        lx::Time::delay( 2000 );

        // play chunk in 2 loops
        lx::Log::logInfo( lx::Log::TEST, "play chunk with 2 loops on any channel" );
        if ( chunk->play( -1, 1 ) )
        {
            lx::Log::logInfo( lx::Log::TEST, "SUCCESS - play chunk on any channel (2 loop) OK" );
            lx::Time::delay( 4000 );
        }
        else
            lx::Log::logInfo( lx::Log::TEST, "FAILURE - play chunk (2 loops) KO" );

        // play on any channel (infinite loop) during 8s
        if ( chunk->play( -1, -1, 8000 ) )
            lx::Log::logInfo( lx::Log::TEST, "SUCCESS - play chunk during 8s OK" );
        else
            lx::Log::logInfo( lx::Log::TEST, "FAILURE - play chunk during 8s KO" );

        lx::Time::delay( 9000 );
        delete chunk;
    }
    catch ( lx::Mixer::MixerException& se )
    {
        lx::Log::log( "FAILURE - not loaded" );
        lx::Log::log( "%s", se.what() );
    }

    lx::Log::logInfo( lx::Log::TEST, "Launch chunk: <empty_string>" );

    try
    {
        chunk = new lx::Mixer::Chunk( std::string() );
        lx::Log::log( "FAILURE - loaded, but it should not be" );
        delete chunk;
    }
    catch ( lx::Mixer::MixerException& se )
    {
        lx::Log::log( "SUCCESS - not loaded, as expected" );
        lx::Log::log( "%s", se.what() );
    }

    lx::Log::logInfo( lx::Log::APPLICATION, " = END TEST = " );
}

void test_effects()
{
    lx::Log::logInfo( lx::Log::APPLICATION, " = TEST effects = " );
    std::string sm = "data/01.ogg";
    std::string sc = "data/explosion.wav";
    int chan = 5;
    lx::Mixer::Music music( sm );
    lx::Mixer::Chunk chunk( sc );

    {
        lx::Log::logInfo( lx::Log::APPLICATION, "combine effects in a group" );
        lx::Mixer::allocateChannels( 255 );
        lx::Mixer::groupChannels( 1, 32, 64 );
        lx::Mixer::MixerEffect effect;
        effect.type.panning = true;
        effect.type.distance = true;
        effect.type.reverse_stereo = true;
        effect.loops = 0;
        effect.pan_left  = 1;
        effect.pan_right = 254;
        effect.distance = 32;
        effect.rev_stereo = true;

        while ( effect.pan_left < 255 )
        {
            lx::Mixer::groupPlayChunk( chunk, 64, effect );
            lx::Time::delay( 17 );
            effect.pan_left++;
            effect.pan_right--;
        }

        lx::Log::logInfo( lx::Log::TEST, "playing channels : %d", lx::Mixer::playingChannels() );
        lx::Log::logInfo( lx::Log::TEST, "paused channels : %d", lx::Mixer::pausedChannels() );
        lx::Mixer::groupChannels( 1, 32, -1 );
        lx::Mixer::allocateChannels( 8 );
    }

    lx::Log::logInfo( lx::Log::TEST, "music: fade in effect" );
    lx::Mixer::fadeInMusic( music, 1000 );
    lx::Time::delay( 2000 );

    // play chunk during the music
    int fxv = lx::Mixer::getFXVolume();
    lx::Log::logInfo( lx::Log::TEST, "chunk: left on channel %d", chan );
    lx::Mixer::setFXVolume( fxv / 3 );
    lx::Mixer::setPanning( chan, 255, 0 );
    chunk.play( chan );
    lx::Time::delay( 2000 );
    lx::Mixer::setFXVolume( fxv );

    lx::Log::logInfo( lx::Log::TEST, "music: fade out effect" );
    lx::Mixer::fadeOutMusic( 1000 );
    lx::Time::delay( 2000 );

    lx::Mixer::removePanning();
    lx::Log::logInfo( lx::Log::TEST, "chunk: no effect" );
    chunk.play();
    lx::Time::delay( 1000 );

    // Left
    lx::Log::logInfo( lx::Log::TEST, "chunk: panning effect: left" );
    lx::Mixer::setPanning( 255, 0 );
    chunk.play();
    lx::Time::delay( 500 );

    // Right
    lx::Log::logInfo( lx::Log::TEST, "chunk: panning effect: right" );
    lx::Mixer::setPanning( 0, 255 );
    chunk.play();
    lx::Time::delay( 1000 );
    lx::Mixer::removePanning();

    lx::Log::logInfo( lx::Log::TEST, "music: position" );
    lx::Log::logInfo( lx::Log::TEST, "music: position 60°, no distance" );
    lx::Mixer::setPosition( 60 );
    music.play();
    lx::Time::delay( 4000 );
    lx::Log::logInfo( lx::Log::TEST, "music: position 270°, no distance" );
    lx::Mixer::setPosition( 270 );
    lx::Time::delay( 4000 );

    lx::Log::logInfo( lx::Log::TEST, "music: position 180°, no distance" );
    lx::Mixer::setPosition( 180 );
    lx::Time::delay( 4000 );

    lx::Log::logInfo( lx::Log::TEST, "music: position 60°, distance: 64" );
    lx::Mixer::setPosition( 60, 64 );
    lx::Time::delay( 4000 );

    lx::Log::logInfo( lx::Log::TEST, "music: position 270°, distance: 128" );
    lx::Mixer::setPosition( 270, 128 );
    lx::Time::delay( 4000 );

    lx::Log::logInfo( lx::Log::TEST, "music: reverseStereo" );
    lx::Mixer::reverseStereo( true );
    lx::Time::delay( 4000 );
    lx::Log::logInfo( lx::Log::TEST, "music: reverseStereo (reset)" );
    lx::Mixer::reverseStereo( false );
    lx::Time::delay( 4000 );

    lx::Log::logInfo( lx::Log::TEST, "music: position 180°, distance: 4" );
    lx::Mixer::setPosition( 180, 4 );
    lx::Time::delay( 4000 );

    lx::Mixer::resetPosition();
    lx::Log::logInfo( lx::Log::TEST, "music: dynamic position effect" );
    lx::Time::delay( 1000 );

    for ( Sint16 k = 0; k < 360; k += 2 )
    {
        lx::Log::logInfo( lx::Log::TEST, "music: position %d", k );
        lx::Mixer::setPosition( k );
        lx::Time::delay( 100 );
    }

    lx::Mixer::resetPosition();
    lx::Log::logInfo( lx::Log::TEST, "music: dynamic distance effect" );
    lx::Time::delay( 1000 );

    for ( Uint8 i = 0; i < 254; i += 2 )
    {
        lx::Log::logInfo( lx::Log::TEST, "music: distance %d", i );
        lx::Mixer::setDistance( i );
        lx::Time::delay( 100 );
    }

    uint8_t j = 254;
    do
    {
        lx::Log::logInfo( lx::Log::TEST, "music: distance %d", j );
        lx::Mixer::setDistance( j );
        j -= 1;
        lx::Time::delay( 33 );
    }
    while ( j > 0 );

    lx::Log::logInfo( lx::Log::TEST, "music: fade out effect (again)" );
    lx::Mixer::fadeOutMusic( 2560 );
    lx::Time::delay( 3000 );
    music.stop();

    lx::Log::logInfo( lx::Log::APPLICATION, " = END TEST = " );
}

void test_volume()
{
    const unsigned short XVOLUME = 100;
    const unsigned short XVOLUME2 = 50;
    const unsigned short XVOLUME3 = 10;
    const unsigned short XVOLUME4 = 50;

    lx::Log::logInfo( lx::Log::APPLICATION, " = TEST volume = " );
    test_volume_( XVOLUME );

    lx::Log::logInfo( lx::Log::APPLICATION, "set overall volume to %d", XVOLUME2 );
    lx::Mixer::setOverallVolume( XVOLUME2 );
    test_volume_( XVOLUME2 );

    lx::Log::logInfo( lx::Log::APPLICATION, "set music volume to %d%%", XVOLUME3 );
    lx::Mixer::setMusicVolume( XVOLUME3 );
    lx::Log::logInfo( lx::Log::TEST, "overall volume: %d", lx::Mixer::getOverallVolume() );
    lx::Log::logInfo( lx::Log::TEST, "music volume: %d", lx::Mixer::getMusicVolume() );
    lx::Log::logInfo( lx::Log::TEST, "FX volume: %d", lx::Mixer::getFXVolume() );

    unsigned short mv = lx::Mixer::getMusicVolume();
    unsigned short ex = XVOLUME2 / XVOLUME3;
    if ( mv != ex )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - music volume expected: %d; got: %d",
                          ex, mv );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - music volume: %d", ex );

    lx::Log::logInfo( lx::Log::APPLICATION, "set fx volume to %d%%", XVOLUME4 );
    lx::Mixer::setFXVolume( XVOLUME4 );
    lx::Log::logInfo( lx::Log::TEST, "overall volume: %d", lx::Mixer::getOverallVolume() );
    lx::Log::logInfo( lx::Log::TEST, "music volume: %d", lx::Mixer::getMusicVolume() );
    lx::Log::logInfo( lx::Log::TEST, "FX volume: %d", lx::Mixer::getFXVolume() );

    unsigned short fxv = lx::Mixer::getFXVolume();
    unsigned short ex2 = XVOLUME2 / 2;
    if ( fxv != ex2 )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - FX volume expected: %d; got: %d",
                          ex2, fxv );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - FX volume: %d", ex2 );

    lx::Log::logInfo( lx::Log::APPLICATION, "set overall volume to %d", XVOLUME );
    lx::Mixer::setOverallVolume( XVOLUME );

    mv  = lx::Mixer::getMusicVolume();
    fxv = lx::Mixer::getFXVolume();
    ex  *= 2;
    ex2 *= 2;

    if ( mv != ex )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - music volume expected: %d; got: %d",
                          ex, mv );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - music volume: %d", ex );

    if ( fxv != ex2 )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - FX volume expected: %d; got: %d",
                          ex2, fxv );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - FX volume: %d", ex2 );

    lx::Log::logInfo( lx::Log::APPLICATION, " = END TEST = " );
}

void test_volume_( const unsigned ex )
{
    unsigned short ov = lx::Mixer::getOverallVolume();
    unsigned short mv = lx::Mixer::getMusicVolume();
    unsigned short fxv = lx::Mixer::getFXVolume();

    // Overall
    if ( ov != ex )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - overall volume expected: %d; got: %d",
                          ex, ov );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - overall volume: %d", ex );

    // Music
    if ( mv != ex )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - music volume expected: %d; got: %d",
                          ex, mv );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - music volume: %d", ex );

    // FX
    if ( fxv != ex )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - FX volume expected: %d; got: %d",
                          ex, fxv );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - FX volume: %d", ex );
}

void test_volume2()
{
    lx::Log::logInfo( lx::Log::APPLICATION, " = TEST volume 2 = " );

    lx::Mixer::setOverallVolume( 100 );
    lx::Mixer::setMusicVolume( 100 );
    lx::Mixer::setFXVolume( 100 );
    lx::Log::logInfo( lx::Log::TEST, "overall volume: %d", lx::Mixer::getOverallVolume() );
    lx::Log::logInfo( lx::Log::TEST, "music volume: %d", lx::Mixer::getMusicVolume() );
    lx::Log::logInfo( lx::Log::TEST, "FX volume: %d", lx::Mixer::getFXVolume() );

    std::string str = "data/01.ogg";
    lx::Mixer::Music music( str );
    music.play();

    lx::Log::logInfo( lx::Log::TEST, "set the position to 128.0 second" );
    lx::Time::delay( 2000 );
    lx::Mixer::setMusicPosition( 128.0 );
    lx::Time::delay( 2000 );

    for ( short i = 100; i > 0; i-- )
    {
        lx::Time::delay( 100 );
        lx::Log::logInfo( lx::Log::TEST, "set overall volume to %d", i );
        lx::Mixer::setOverallVolume( static_cast<unsigned short>( i ) );
    }

    for ( unsigned short i = 0; i <= 100; i++ )
    {
        lx::Time::delay( 100 );
        lx::Log::logInfo( lx::Log::TEST, "set overall volume to %d", i );
        lx::Mixer::setOverallVolume( i );
    }

    lx::Mixer::fadeOutMusic( 1000 );
    lx::Time::delay( 1024 );
    music.stop();
    lx::Log::logInfo( lx::Log::APPLICATION, " = END TEST = " );
}

/**/
