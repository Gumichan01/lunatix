
#include <LunatiX/Lunatix.hpp>
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
void test_volume_(const unsigned ex);
void test_info(const std::string& s);


int main(int argc, char **argv)
{
    bool err = LX_Init();

    if(!err)
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - LX_Init() failed");
    else
        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - The LunatiX library has been initialized with success");

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Audio ==== ");
    test_audioInit();
    test_channels();
    test_music();
    test_chunk();
    test_effects();
    test_volume();
    test_volume2();
    LX_Log::log(" ==== End Audio ==== ");

    LX_Quit();

    return EXIT_SUCCESS;
}


void test_info(const std::string& s)
{
    const LX_Mixer::LX_MusicTag tag = LX_Mixer::getMusicInfoFrom(s);

    try
    {
        LX_Win::LX_WindowInfo info;
        LX_Win::LX_initWindowInfo(info);
        info.w = 256;
        info.h = 256;
        LX_Win::LX_Window w(info);

        if(tag.img != nullptr)
        {
            LX_Graphics::LX_Sprite * cover = tag.img->generateSprite(w);
            LX_Log::logInfo(LX_Log::TEST,"SUCCESS - cover opened");

            w.clearWindow();
            LX_Graphics::LX_ImgRect box{0,0,info.w,info.h};
            cover->draw(box);
            w.update();
            LX_Timer::delay(2000);
            delete cover;
        }
    }
    catch(LX_Graphics::LX_ImageException& ie)
    {
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - %s", ie.what());
    }

    LX_Log::log("File: %s",s.c_str());
    LX_Log::log("================================");
    LX_Log::log("Title - %s",tag.title.utf8_str());
    LX_Log::log("Artist - %s",tag.artist.utf8_str());
    LX_Log::log("Album - %s",tag.album.utf8_str());
    LX_Log::log("Year - %s",tag.year.utf8_str());
    LX_Log::log("--------------------------------");
    LX_Log::log("Duration - %s", tag.duration.utf8_str());
    LX_Log::log("Format - %s", tag.format.utf8_str());
    LX_Log::log("================================");
}


void test_audioInit()
{
    LX_Log::logInfo(LX_Log::APPLICATION," = TEST audio = ");

    int n, freq, channels;
    Uint16 format;
    LX_Log::logInfo(LX_Log::TEST,"Get information about the library");
    n = Mix_QuerySpec(&freq, &format, &channels);

    if(n == 0)
    {
        LX_Log::logError(LX_Log::TEST,"Cannot get information: %s",
                         Mix_GetError());
    }
    else
    {
        std::string format_str = "Unknown";

        switch(format)
        {
        case AUDIO_U8:
            format_str="U8";
            break;
        case AUDIO_S8:
            format_str="S8";
            break;
        case AUDIO_U16LSB:
            format_str="U16LSB";
            break;
        case AUDIO_S16LSB:
            format_str="S16LSB";
            break;
        case AUDIO_U16MSB:
            format_str="U16MSB";
            break;
        case AUDIO_S16MSB:
            format_str="S16MSB";
            break;
        default:
            break;
        }
        LX_Log::logInfo(LX_Log::TEST,"opened = %d time(s)",n);
        LX_Log::logInfo(LX_Log::TEST,"frequency = %d Hz",freq);
        LX_Log::logInfo(LX_Log::TEST,"format = %s",format_str.c_str());
        LX_Log::logInfo(LX_Log::TEST,"channels = %d",channels);

        int m = Mix_GetNumChunkDecoders();

        LX_Log::logInfo(LX_Log::TEST,"Get the chunk decoders");
        for(int i = 0; i < m; i++)
        {
            LX_Log::logInfo(LX_Log::TEST,"Sample chunk decoder %d: %s",
                            i,Mix_GetChunkDecoder(i));
        }

        m = Mix_GetNumMusicDecoders();

        LX_Log::logInfo(LX_Log::TEST,"Get the music decoders");
        for(int j = 0; j < m; j++)
        {
            LX_Log::logInfo(LX_Log::TEST,"Sample chunk decoder %d: %s",
                            j,Mix_GetMusicDecoder(j));
        }

        LX_Log::logInfo(LX_Log::TEST,"Allocated channel(s): %d",LX_Mixer::allocateChannels(-1));
    }

    LX_Log::logInfo(LX_Log::APPLICATION," = END TEST = ");
}

void test_channels()
{
    const int N = 32;
    LX_Log::logInfo(LX_Log::APPLICATION," = TEST channels = ");
    LX_Log::logInfo(LX_Log::APPLICATION,"%d channel(s)",LX_Mixer::allocateChannels(-1));
    LX_Log::logInfo(LX_Log::APPLICATION,"Trying to get %d channels",N);

    int res = LX_Mixer::allocateChannels(N);

    if(res == N)
        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - %d channel(s)",
                        LX_Mixer::allocateChannels(-1));
    else
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - expected: %d; got: %d",
                        N,res);

    LX_Log::logInfo(LX_Log::APPLICATION,"Trying to reserve channels from 0 to 7 in group 1");
    LX_Mixer::groupChannels(0,7,1);
    LX_Log::logInfo(LX_Log::APPLICATION,"Trying to reserve channels from 9 to 15 in group 2");
    LX_Mixer::groupChannels(8,15,2);
    int g1 = LX_Mixer::groupCount(1);
    int g2 = LX_Mixer::groupCount(2);

    LX_Log::logInfo(LX_Log::APPLICATION,"In group 1: %d channel(s)",g1);
    LX_Log::logInfo(LX_Log::APPLICATION,"In group 2: %d channel(s)",g2);

    const int M = 24;
    LX_Log::logInfo(LX_Log::APPLICATION,"Try to reserve %d channel(s)",M);
    int r1 = LX_Mixer::reserveChannels(M);
    LX_Log::logInfo(LX_Log::APPLICATION,"Reserved: %d channel(s)",r1);

    // PLay a chunk in a specific channel
    std::string sc = "data/explosion.wav";
    LX_Mixer::LX_Chunk chunk(sc);

    LX_Log::logInfo(LX_Log::APPLICATION,"Available channel before playing: %d",
                    LX_Mixer::channelAvailable(1));
    LX_Log::logInfo(LX_Log::APPLICATION,"Available channel before playing: %d",
                    LX_Mixer::channelAvailable(2));

    LX_Log::logInfo(LX_Log::APPLICATION,"Playing a chunk in the 2 groups");
    LX_Mixer::groupPlayChunk(chunk,1);
    LX_Mixer::groupPlayChunk(chunk,2);

    LX_Log::logInfo(LX_Log::APPLICATION,"Available channel (grp 1): %d",
                    LX_Mixer::channelAvailable(1));
    LX_Log::logInfo(LX_Log::APPLICATION,"Available channel (grp 2): %d",
                    LX_Mixer::channelAvailable(2));

    LX_Timer::delay(2000);
    LX_Log::logInfo(LX_Log::APPLICATION,"Done");

    LX_Log::logInfo(LX_Log::APPLICATION,"Reset");
    r1 = LX_Mixer::reserveChannels(0);
    LX_Log::logInfo(LX_Log::APPLICATION,"Reserved: %d channel(s)",r1);

    LX_Log::logInfo(LX_Log::APPLICATION,"Reset the groups");
    int g3 = LX_Mixer::groupChannels(0,15,-1);
    LX_Log::logInfo(LX_Log::APPLICATION,"Reset: %d channel(s)",g3);

    LX_Mixer::allocateChannels(8);
    LX_Log::logInfo(LX_Log::APPLICATION," = END TEST = ");
}

void test_music()
{
    LX_Log::logInfo(LX_Log::APPLICATION," = TEST music = ");
    std::string s = "data/test.mp3";
    std::string sm = "data/01.ogg";

    LX_Log::logInfo(LX_Log::TEST,"Launch music: %s",s.c_str());

    try
    {
        LX_Mixer::LX_Music music(s);
    }
    catch(LX_Mixer::LX_MixerException& se)
    {
        LX_Log::log("mp3 file not loaded");
        LX_Log::log("%s", se.what());
    }

    test_info(s);

    try
    {
        LX_Mixer::LX_Music music(sm);
        LX_Log::log("SUCCESS - Loaded");

        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - music loaded");
        LX_Log::logInfo(LX_Log::TEST,"play music");

        if(music.play())
        {
            LX_Log::logInfo(LX_Log::TEST,"SUCCESS - play music OK");
            LX_Timer::delay(4000);
            music.pause();
            LX_Log::logInfo(LX_Log::TEST,"music paused during 1 second");
            LX_Timer::delay(1000);
            music.pause();
            LX_Log::logInfo(LX_Log::TEST,"music resumed");
            LX_Timer::delay(2000);
            music.stop();
            LX_Log::logInfo(LX_Log::TEST,"music stopped");
        }
        else
            LX_Log::logInfo(LX_Log::TEST,"FAILURE - play music KO");

        const libtagpp::Tag& tag = music.getInfo();
        LX_Log::log("================================");
        LX_Log::log("Title - %s",tag.title());
        LX_Log::log("Artist - %s",tag.artist());
        LX_Log::log("Album - %s",tag.album());
        LX_Log::log("Year - %s",tag.year());
        LX_Log::log("--------------------------------");
        LX_Log::log("Image - position %d %d",tag.getImageMetaData()._img_offset,
                    tag.getImageMetaData()._img_size);
        LX_Log::log("Duration - %s", tag.properties().duration.c_str());
        LX_Log::log("Channels - %d", tag.properties().channels);
        LX_Log::log("Sample rate - %d Hz", tag.properties().samplerate);
        LX_Log::log("Bitrate - %d bits/s", tag.properties().bitrate);
        LX_Log::log("Format - %s", tag.properties().format.c_str());
        LX_Log::log("================================");

        LX_Log::logCritical(LX_Log::APPLICATION,"DANGER ZONE IN");
        LX_Log::logCritical(LX_Log::APPLICATION,"play");
        music.play();
        LX_Log::logCritical(LX_Log::APPLICATION,"stop");
        music.stop();
        LX_Log::logCritical(LX_Log::APPLICATION,"play");
        music.play();
        LX_Log::logCritical(LX_Log::APPLICATION,"pause");
        music.pause();
        LX_Log::logCritical(LX_Log::APPLICATION,"stop");
        music.stop();
        LX_Log::logCritical(LX_Log::APPLICATION,"pause");
        music.pause();
        LX_Log::logCritical(LX_Log::APPLICATION,"fadeIn");
        music.fadeIn(1000);
        LX_Log::logCritical(LX_Log::APPLICATION,"fadeOut");
        music.fadeOut(1000);
        LX_Log::logCritical(LX_Log::APPLICATION,"DANGER ZONE OUT");
    }
    catch(LX_Mixer::LX_MixerException& se)
    {
        LX_Log::log("FAILURE - not loaded");
        LX_Log::log("%s", se.what());
    }

    LX_Log::logInfo(LX_Log::TEST,"Launch music: <empty_string>");

    try
    {
        LX_Mixer::LX_Music *mus = new LX_Mixer::LX_Music(std::string());
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - music launched, it should not");
        delete mus;
    }
    catch(LX_Mixer::LX_MixerException& se)
    {
        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - music: not launched as expected");
        LX_Log::log("%s", se.what());
    }

    LX_Log::logInfo(LX_Log::APPLICATION," = END TEST = ");
}

void test_chunk()
{
    LX_Log::logInfo(LX_Log::APPLICATION," = TEST chunk = ");

    std::string s = "data/explosion.wav";
    LX_Mixer::LX_Chunk *chunk = nullptr;

    LX_Log::logInfo(LX_Log::TEST,"Launch music: %s",s.c_str());

    try
    {
        chunk = new LX_Mixer::LX_Chunk(s);
        LX_Log::log("SUCCESS - Loaded");

        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - chunk launched");
        LX_Log::logInfo(LX_Log::TEST,"play chunk with no loop on any channel");

        LX_Timer::delay(1000);
        // play on any channel (no loop)
        if(chunk->play())
            LX_Log::logInfo(LX_Log::TEST,"SUCCESS - play chunk (no loop) OK");
        else
            LX_Log::logInfo(LX_Log::TEST,"FAILURE - play chunk (no loop) KO");

        LX_Timer::delay(2000);

        // play chunk in 2 loops
        LX_Log::logInfo(LX_Log::TEST,"play chunk with 2 loops on any channel");
        if(chunk->play(-1,1))
        {
            LX_Log::logInfo(LX_Log::TEST,"SUCCESS - play chunk on any channel (2 loop) OK");
            LX_Timer::delay(4000);
        }
        else
            LX_Log::logInfo(LX_Log::TEST,"FAILURE - play chunk (2 loops) KO");

        // play on any channel (infinite loop) during 8s
        if(chunk->play(-1,-1,8000))
            LX_Log::logInfo(LX_Log::TEST,"SUCCESS - play chunk during 8s OK");
        else
            LX_Log::logInfo(LX_Log::TEST,"FAILURE - play chunk during 8s KO");

        LX_Timer::delay(9000);
        delete chunk;
    }
    catch(LX_Mixer::LX_MixerException& se)
    {
        LX_Log::log("FAILURE - not loaded");
        LX_Log::log("%s", se.what());
    }

    LX_Log::logInfo(LX_Log::TEST,"Launch chunk: <empty_string>");

    try
    {
        chunk = new LX_Mixer::LX_Chunk(std::string());
        LX_Log::log("FAILURE - loaded, but it should not be");
        delete chunk;
    }
    catch(LX_Mixer::LX_MixerException& se)
    {
        LX_Log::log("SUCCESS - not loaded, as expected");
        LX_Log::log("%s", se.what());
    }

    LX_Log::logInfo(LX_Log::APPLICATION," = END TEST = ");
}

void test_effects()
{
    LX_Log::logInfo(LX_Log::APPLICATION," = TEST effects = ");
    std::string sm = "data/01.ogg";
    std::string sc = "data/explosion.wav";
    int chan = 5;
    LX_Mixer::LX_Music music(sm);
    LX_Mixer::LX_Chunk chunk(sc);

    {
        LX_Log::logInfo(LX_Log::APPLICATION,"combine effects in a group");
        LX_Mixer::allocateChannels(255);
        LX_Mixer::groupChannels(1, 32, 64);
        LX_Mixer::LX_MixerEffect effect;
        effect.type.panning = true;
        effect.type.distance = true;
        effect.type.reverse_stereo = true;
        effect.loops = 0;
        effect.pan_left  = 1;
        effect.pan_right = 254;
        effect.distance = 32;
        effect.rev_stereo = true;

        while(effect.pan_left < 255)
        {
            LX_Mixer::groupPlayChunk(chunk, 64, effect);
            LX_Timer::delay(17);
            effect.pan_left++;
            effect.pan_right--;
        }

        LX_Mixer::groupChannels(1, 32, -1);
        LX_Mixer::allocateChannels(8);
    }

    LX_Log::logInfo(LX_Log::TEST,"music: fade in effect");
    LX_Mixer::fadeInMusic(music,1000);
    LX_Timer::delay(2000);

    // play chunk during the music
    int fxv = LX_Mixer::getFXVolume();
    LX_Log::logInfo(LX_Log::TEST,"chunk: left on channel %d", chan);
    LX_Mixer::setFXVolume(fxv/3);
    LX_Mixer::setPanning(chan,255,0);
    chunk.play(chan);
    LX_Timer::delay(2000);
    LX_Mixer::setFXVolume(fxv);

    LX_Log::logInfo(LX_Log::TEST,"music: fade out effect");
    LX_Mixer::fadeOutMusic(1000);
    LX_Timer::delay(2000);

    LX_Mixer::removePanning();
    LX_Log::logInfo(LX_Log::TEST,"chunk: no effect");
    chunk.play();
    LX_Timer::delay(1000);

    // Left
    LX_Log::logInfo(LX_Log::TEST,"chunk: panning effect: left");
    LX_Mixer::setPanning(255,0);
    chunk.play();
    LX_Timer::delay(500);

    // Right
    LX_Log::logInfo(LX_Log::TEST,"chunk: panning effect: right");
    LX_Mixer::setPanning(0,255);
    chunk.play();
    LX_Timer::delay(1000);
    LX_Mixer::removePanning();

    LX_Log::logInfo(LX_Log::TEST,"music: position");
    LX_Log::logInfo(LX_Log::TEST,"music: position 60°, no distance");
    LX_Mixer::setPosition(60);
    music.play();
    LX_Timer::delay(4000);
    LX_Log::logInfo(LX_Log::TEST,"music: position 270°, no distance");
    LX_Mixer::setPosition(270);
    LX_Timer::delay(4000);

    LX_Log::logInfo(LX_Log::TEST,"music: position 180°, no distance");
    LX_Mixer::setPosition(180);
    LX_Timer::delay(4000);

    LX_Log::logInfo(LX_Log::TEST,"music: position 60°, distance: 64");
    LX_Mixer::setPosition(60, 64);
    LX_Timer::delay(4000);

    LX_Log::logInfo(LX_Log::TEST,"music: position 270°, distance: 128");
    LX_Mixer::setPosition(270, 128);
    LX_Timer::delay(4000);

    LX_Log::logInfo(LX_Log::TEST,"music: reverseStereo");
    LX_Mixer::reverseStereo(true);
    LX_Timer::delay(4000);
    LX_Log::logInfo(LX_Log::TEST,"music: reverseStereo (reset)");
    LX_Mixer::reverseStereo(false);
    LX_Timer::delay(4000);

    LX_Log::logInfo(LX_Log::TEST,"music: position 180°, distance: 4");
    LX_Mixer::setPosition(180, 4);
    LX_Timer::delay(4000);

    LX_Mixer::resetPosition();
    LX_Log::logInfo(LX_Log::TEST,"music: dynamic position effect");
    LX_Timer::delay(1000);

    for(Sint16 k = 0; k < 360; k += 2)
    {
        LX_Log::logInfo(LX_Log::TEST,"music: position %d",k);
        LX_Mixer::setPosition(k);
        LX_Timer::delay(100);
    }

    LX_Mixer::resetPosition();
    LX_Log::logInfo(LX_Log::TEST,"music: dynamic distance effect");
    LX_Timer::delay(1000);

    for(Uint8 i = 0; i < 254; i += 2)
    {
        LX_Log::logInfo(LX_Log::TEST,"music: distance %d",i);
        LX_Mixer::setDistance(i);
        LX_Timer::delay(100);
    }

    uint8_t j = 254;
    do
    {
        LX_Log::logInfo(LX_Log::TEST,"music: distance %d",j);
        LX_Mixer::setDistance(j);
        j -= 1;
        LX_Timer::delay(33);
    }
    while(j > 0);

    LX_Log::logInfo(LX_Log::TEST,"music: fade out effect (again)");
    LX_Mixer::fadeOutMusic(2560);
    LX_Timer::delay(3000);
    music.stop();

    LX_Log::logInfo(LX_Log::APPLICATION," = END TEST = ");
}

void test_volume()
{
    const unsigned short XVOLUME = 100;
    const unsigned short XVOLUME2 = 50;
    const unsigned short XVOLUME3 = 10;
    const unsigned short XVOLUME4 = 50;

    LX_Log::logInfo(LX_Log::APPLICATION," = TEST volume = ");
    test_volume_(XVOLUME);

    LX_Log::logInfo(LX_Log::APPLICATION,"set overall volume to %d",XVOLUME2);
    LX_Mixer::setOverallVolume(XVOLUME2);
    test_volume_(XVOLUME2);

    LX_Log::logInfo(LX_Log::APPLICATION,"set music volume to %d%%",XVOLUME3);
    LX_Mixer::setMusicVolume(XVOLUME3);
    LX_Log::logInfo(LX_Log::TEST,"overall volume: %d",LX_Mixer::getOverallVolume());
    LX_Log::logInfo(LX_Log::TEST,"music volume: %d",LX_Mixer::getMusicVolume());
    LX_Log::logInfo(LX_Log::TEST,"FX volume: %d",LX_Mixer::getFXVolume());

    unsigned short mv = LX_Mixer::getMusicVolume();
    unsigned short ex = XVOLUME2 / XVOLUME3;
    if(mv != ex)
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - music volume expected: %d; got: %d",
                        ex,mv);
    else
        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - music volume: %d",ex);

    LX_Log::logInfo(LX_Log::APPLICATION,"set fx volume to %d%%",XVOLUME4);
    LX_Mixer::setFXVolume(XVOLUME4);
    LX_Log::logInfo(LX_Log::TEST,"overall volume: %d",LX_Mixer::getOverallVolume());
    LX_Log::logInfo(LX_Log::TEST,"music volume: %d",LX_Mixer::getMusicVolume());
    LX_Log::logInfo(LX_Log::TEST,"FX volume: %d",LX_Mixer::getFXVolume());

    unsigned short fxv = LX_Mixer::getFXVolume();
    unsigned short ex2 = XVOLUME2 / 2;
    if(fxv != ex2)
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - FX volume expected: %d; got: %d",
                        ex2,fxv);
    else
        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - FX volume: %d",ex2);

    LX_Log::logInfo(LX_Log::APPLICATION,"set overall volume to %d",XVOLUME);
    LX_Mixer::setOverallVolume(XVOLUME);

    mv  = LX_Mixer::getMusicVolume();
    fxv = LX_Mixer::getFXVolume();
    ex  *= 2;
    ex2 *= 2;

    if(mv != ex)
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - music volume expected: %d; got: %d",
                        ex,mv);
    else
        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - music volume: %d",ex);

    if(fxv != ex2)
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - FX volume expected: %d; got: %d",
                        ex2,fxv);
    else
        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - FX volume: %d",ex2);

    LX_Log::logInfo(LX_Log::APPLICATION," = END TEST = ");
}

void test_volume_(const unsigned ex)
{
    unsigned short ov = LX_Mixer::getOverallVolume();
    unsigned short mv = LX_Mixer::getMusicVolume();
    unsigned short fxv = LX_Mixer::getFXVolume();

    // Overall
    if(ov != ex)
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - overall volume expected: %d; got: %d",
                        ex,ov);
    else
        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - overall volume: %d",ex);

    // Music
    if(mv != ex)
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - music volume expected: %d; got: %d",
                        ex,mv);
    else
        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - music volume: %d",ex);

    // FX
    if(fxv != ex)
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - FX volume expected: %d; got: %d",
                        ex,fxv);
    else
        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - FX volume: %d",ex);
}

void test_volume2()
{
    LX_Log::logInfo(LX_Log::APPLICATION," = TEST volume 2 = ");

    LX_Mixer::setOverallVolume(100);
    LX_Mixer::setMusicVolume(100);
    LX_Mixer::setFXVolume(100);
    LX_Log::logInfo(LX_Log::TEST,"overall volume: %d",LX_Mixer::getOverallVolume());
    LX_Log::logInfo(LX_Log::TEST,"music volume: %d",LX_Mixer::getMusicVolume());
    LX_Log::logInfo(LX_Log::TEST,"FX volume: %d",LX_Mixer::getFXVolume());

    std::string str = "data/01.ogg";
    LX_Mixer::LX_Music music(str);
    music.play();

    LX_Log::logInfo(LX_Log::TEST,"set the position to 128.0 second");
    LX_Timer::delay(2000);
    LX_Mixer::setMusicPosition(128.0);
    LX_Timer::delay(2000);

    for(short i = 100; i > 0; i--)
    {
        LX_Timer::delay(100);
        LX_Log::logInfo(LX_Log::TEST,"set overall volume to %d",i);
        LX_Mixer::setOverallVolume(static_cast<unsigned short>(i));
    }

    for(unsigned short i = 0; i <= 100; i++)
    {
        LX_Timer::delay(100);
        LX_Log::logInfo(LX_Log::TEST,"set overall volume to %d",i);
        LX_Mixer::setOverallVolume(i);
    }

    LX_Mixer::fadeOutMusic(1000);
    LX_Timer::delay(1024);
    music.stop();
    LX_Log::logInfo(LX_Log::APPLICATION," = END TEST = ");
}

/**/
