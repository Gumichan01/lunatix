

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
const unsigned short LX_DEFAULT_VOLUME = 100;
// Overall volume in volume unit [0-100]
unsigned short overall_volume = LX_DEFAULT_VOLUME;
// Music volume in volume unit [0-100]
unsigned short music_volume = LX_DEFAULT_VOLUME;
// Effects volume in volume unit [0-100]
unsigned short fx_volume = LX_DEFAULT_VOLUME;

// Music volume in percentage
unsigned short music_pvolume = LX_DEFAULT_VOLUME;
// Effects volume in percentage
unsigned short fx_pvolume = LX_DEFAULT_VOLUME;
};

namespace LX_Mixer
{

void setOverallVolume(unsigned short volume)
{
    if(volume > LX_DEFAULT_VOLUME)
        overall_volume = LX_DEFAULT_VOLUME;
    else
        overall_volume = volume;

    setMusicVolume(music_pvolume);
    setFXVolume(fx_pvolume);
}

void setMusicVolume(unsigned short pvolume)
{
    if (pvolume > 100) pvolume = 100;

    if(overall_volume == 0)
        music_volume = 0;
    else
        music_volume = pvolume * overall_volume/100;

    Mix_VolumeMusic(music_volume);
    music_pvolume = pvolume;
}

void setFXVolume(unsigned short pvolume)
{
    if (pvolume > 100) pvolume = 100;

    if(overall_volume == 0)
        fx_volume = 0;
    else
        fx_volume = pvolume * overall_volume/100;

    Mix_Volume(-1,fx_volume);
    fx_pvolume = pvolume;
}

unsigned short getOverallVolume()
{
    return overall_volume;
}

unsigned short getMusicVolume()
{
    return music_volume;
}

unsigned short getFXVolume()
{
    return fx_volume;
}


LX_Music * loadMusic(std::string filename)
{
    return new LX_Music(filename);
}


LX_Music * loadMusic(UTF8string& filename)
{
    return new LX_Music(filename);
}


LX_Chunk * loadSample(std::string filename)
{
    return new LX_Chunk(filename);
}

LX_Chunk * loadSample(UTF8string& filename)
{
    return new LX_Chunk(filename);
}


LX_Chunk * loadSample(LX_FileIO::LX_FileBuffer *file)
{
    return (file == nullptr) ? nullptr:(new LX_Chunk(file));
}


void setMusicPosition(double pos)
{
    Mix_RewindMusic();
    Mix_SetMusicPosition(pos);
}


int allocateChannels(int num)
{
    return Mix_AllocateChannels(num);
}


int reserveChannels(int numchans)
{
    return Mix_ReserveChannels(numchans);
}


bool groupChannel(int chan, int tag)
{
    return Mix_GroupChannel(chan,tag) == 1;
}


int groupChannels(int from, int to, int tag)
{
    return Mix_GroupChannels(from,to,tag);
}

int groupCount(int tag)
{
    return Mix_GroupCount(tag);
}


int channelAvailable(int tag)
{
    return Mix_GroupAvailable(tag);
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


void fadeInMusic(LX_Music& music,int ms)
{
    music.fadeIn(ms);
}


void fadeOutMusic(int ms)
{
    Mix_FadeOutMusic(ms);
}


void setPanning(Uint8 left,Uint8 right)
{
    Mix_SetPanning(MIX_CHANNEL_POST,left,right);
}


void removePanning()
{
    setPanning(LX_MIXER_EFFECT_LOUD,LX_MIXER_EFFECT_LOUD);
}


void setPosition(Sint16 angle)
{
    setPosition(angle,LX_MIXER_EFFECT_NO_DISTANCE);
}


void setPosition(Sint16 angle, Uint8 distance)
{
    Mix_SetPosition(MIX_CHANNEL_POST,angle,distance);
}


void resetPosition()
{
    Mix_SetPosition(MIX_CHANNEL_POST,LX_MIXER_EFFECT_NO_ANGLE,LX_MIXER_EFFECT_NO_DISTANCE);
}


void reverseStereo(bool flip)
{
    int opt = flip ? 1:0;
    Mix_SetReverseStereo(MIX_CHANNEL_POST,opt);
}


void setDistance(Uint8 distance)
{
    Mix_SetDistance(MIX_CHANNEL_POST,distance);
}

};
