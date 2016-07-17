

/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Mixer.cpp
*	@brief The implementation of the mixer library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/LX_Music.hpp>
#include <LunatiX/LX_Chunk.hpp>
#include <LunatiX/LX_Mixer.hpp>
#include <LunatiX/LX_FileIO.hpp>
#include <LunatiX/LX_FileBuffer.hpp>

using namespace LX_FileIO;

namespace
{
    const short LX_DEFAULT_VOLUME = 100;

    // Overall volume in volume unit [0-100]
    short overall_volume = LX_DEFAULT_VOLUME;
    // Music volume in percentage of overall volume
    short music_volume = LX_DEFAULT_VOLUME;
    // Effects volume in percentage of overall volume
    short fx_volume = LX_DEFAULT_VOLUME;
};

namespace LX_Mixer
{

LX_Music * loadMusic(std::string filename)
{
    return new LX_Music(filename.c_str());
}


LX_Music * loadMusic(Mix_Music *mus)
{
    return new LX_Music(mus);
}


LX_Chunk * loadSample(std::string filename)
{
    return new LX_Chunk(filename.c_str());
}


LX_Chunk * loadSample(Mix_Chunk *ch)
{
    return new LX_Chunk(ch);
}


LX_Chunk * loadSample(LX_FileIO::LX_FileBuffer *file)
{
    return (file == nullptr) ? nullptr:(new LX_Chunk(file));
}


int allocateChannels(int num)
{
    return Mix_AllocateChannels(num);
}


int reserveChannels(int numchans)
{
    return Mix_ReserveChannels(numchans);
}


int channelVolume(int channel,int volume)
{
    return Mix_Volume(channel,volume);
}


void pause(int channel)
{
    Mix_Pause(channel);
}


void resume(int channel)
{
    Mix_Resume(channel);
}


void haltChannel(int channel)
{
    Mix_HaltChannel(channel);
}


void expireChannel(int channel, int ticks)
{
    Mix_ExpireChannel(channel,ticks);
}


int isPlaying(int channel)
{
    return Mix_Playing(channel);
}


int isPaused(int channel)
{
    return Mix_Paused(channel);
}


void fadeInMusic(LX_Music *music,int ms)    /// TODO use reference instead of pointer
{
    Mix_FadeInMusic(music->getMusic(),LX_MIXER_NOLOOP,ms);
}


void fadeOutMusic(int ms)
{
    Mix_FadeOutMusic(ms);
}


void setPanning(int channel,Uint8 left,Uint8 right)
{
    Mix_SetPanning(channel,left,right);
}


void removePanning(int channel)
{
    setPanning(channel,LX_MIXER_EFFECT_LOUD,LX_MIXER_EFFECT_LOUD);
}


void setDistance(Uint8 distance)
{
    setDistance(MIX_CHANNEL_POST,distance);
}

void setPosition(Sint16 angle)
{
    setPosition(angle,LX_MIXER_EFFECT_NO_DISTANCE);
}


void setPosition(Sint16 angle, Uint8 distance)
{
    setPosition(MIX_CHANNEL_POST,angle,distance);
}


void setPosition(int channel, Sint16 angle, Uint8 distance)
{
    Mix_SetPosition(channel,angle,distance);
}


void resetPosition(int channel)
{
    setPosition(channel,LX_MIXER_EFFECT_NO_ANGLE,LX_MIXER_EFFECT_NO_DISTANCE);
}


void reverseStereo(int channel, int flip)
{
    Mix_SetReverseStereo(channel,flip);
}


void setDistance(int channel,Uint8 distance)
{
    Mix_SetDistance(channel,distance);
}


};
