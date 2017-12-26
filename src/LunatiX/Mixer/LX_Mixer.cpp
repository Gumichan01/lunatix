

/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file LX_Mixer.cpp
*   @brief The implementation of the mixer library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*
*/

#include <LunatiX/LX_Mixer.hpp>
#include <LunatiX/LX_Music.hpp>
#include <LunatiX/LX_Chunk.hpp>
#include <LunatiX/LX_FileBuffer.hpp>
#include <SDL2/SDL_mixer.h>

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

struct LX_Mixer::LX_MixerEffectType LX_EFFECT_NONE = {false, false, false, false};

bool operator ==(const LX_Mixer::LX_MixerEffectType& t,
                 const LX_Mixer::LX_MixerEffectType& u)
{
    return t.LX_DISTANCE == u.LX_DISTANCE && t.LX_PANNING == u.LX_PANNING
           && t.LX_POSITION == u.LX_POSITION && t.LX_STEREO == u.LX_STEREO;
}

}

namespace LX_Mixer
{


LX_MixerEffect::LX_MixerEffect() noexcept: type(LX_EFFECT_NONE),
    pan_left(0), pan_right(0), pos_angle(0), pos_distance(0),
    rev_stereo(false), loops(0) {}

LX_MixerEffect::LX_MixerEffect(const LX_MixerEffect& st) noexcept:
    type(st.type), pan_left(st.pan_left), pan_right(st.pan_right),
    pos_angle(st.pos_angle), pos_distance(st.pos_distance),
    rev_stereo(st.rev_stereo), loops(st.loops) {}

LX_MixerEffect& LX_MixerEffect::operator = (const LX_MixerEffect& st) noexcept
{
    type = st.type;
    pan_left = st.pan_left;
    pan_right = st.pan_right;
    pos_angle = st.pos_angle;
    pos_distance = st.pos_distance;
    rev_stereo = st.rev_stereo;
    loops = st.loops;

    return *this;
}


void setOverallVolume(unsigned short volume) noexcept
{
    if(volume > LX_DEFAULT_VOLUME)
        overall_volume = LX_DEFAULT_VOLUME;
    else
        overall_volume = volume;

    setMusicVolume(music_pvolume);
    setFXVolume(fx_pvolume);
}

void setMusicVolume(unsigned short pvolume) noexcept
{
    if (pvolume > 100) pvolume = 100;

    if(overall_volume == 0)
        music_volume = 0;
    else
        music_volume = pvolume * overall_volume/100;

    Mix_VolumeMusic(music_volume);
    music_pvolume = pvolume;
}

void setFXVolume(unsigned short pvolume) noexcept
{
    if (pvolume > 100) pvolume = 100;

    if(overall_volume == 0)
        fx_volume = 0;
    else
        fx_volume = pvolume * overall_volume/100;

    if(allocateChannels(-1) > 0)
        Mix_Volume(-1, fx_volume);

    fx_pvolume = pvolume;
}

unsigned short getOverallVolume() noexcept
{
    return overall_volume;
}

unsigned short getMusicVolume() noexcept
{
    return music_volume;
}

unsigned short getFXVolume() noexcept
{
    return fx_volume;
}


LX_Chunk * loadSample(LX_FileIO::LX_FileBuffer& file)
{
    return file.loadSample();
}


void setMusicPosition(double pos) noexcept
{
    Mix_RewindMusic();
    Mix_SetMusicPosition(pos);
}


int allocateChannels(int num) noexcept
{
    int n = Mix_AllocateChannels(num);

    // Set the volume of every channels to *fx_volume*
    if(num > 0)
        Mix_Volume(-1, fx_volume);

    return n;
}


int reserveChannels(int numchans) noexcept
{
    return Mix_ReserveChannels(numchans);
}


bool groupChannel(int chan, int tag) noexcept
{
    return Mix_GroupChannel(chan, tag) == 1;
}


int groupChannels(int from, int to, int tag) noexcept
{
    return Mix_GroupChannels(from, to, tag);
}

int groupCount(int tag) noexcept
{
    return Mix_GroupCount(tag);
}


int channelAvailable(int tag) noexcept
{
    return Mix_GroupAvailable(tag);
}


bool groupPlayChunk(LX_Chunk& chunk, int tag, int loops) noexcept
{
    if(groupCount(tag) == 0)
        return chunk.play(-1, loops);

    int chan = channelAvailable(tag);

    if(chan == -1)
    {
        chan = Mix_GroupOldest(tag);

        if(chan > -1)
            haltChannel(chan);
    }

    return chunk.play(chan, loops);
}

bool groupPlayChunk(LX_Chunk& chunk, int tag, const LX_MixerEffect effect) noexcept
{
    int chan = -1;
    int _tag;

    if(groupCount(tag) == 0)
        _tag = -1;
    else
        _tag = tag;

    chan = channelAvailable(_tag);

    if(chan == -1)
    {
        chan = Mix_GroupOldest(_tag);

        if(chan > -1)
            haltChannel(chan);
    }

    if(effect.type == LX_EFFECT_NONE)
        return chunk.play(chan, effect.loops);
    else
    {
        Mix_UnregisterAllEffects(chan);

        if(effect.type.LX_PANNING)
            setPanning(chan, effect.pan_left, effect.pan_right);

        if(effect.type.LX_POSITION)
            setPosition(chan, effect.pos_angle, effect.pos_distance);

        if(effect.type.LX_DISTANCE)
            setDistance(chan, effect.distance);

        if(effect.type.LX_STEREO)
            reverseStereo(chan, effect.rev_stereo);
    }

    return chunk.play(chan, effect.loops);
}

void pause(int channel) noexcept
{
    Mix_Pause(channel);
}


void resume(int channel) noexcept
{
    Mix_Resume(channel);
}


void haltChannel(int channel) noexcept
{
    Mix_HaltChannel(channel);
}


void expireChannel(int channel, int ticks) noexcept
{
    Mix_ExpireChannel(channel, ticks);
}


int isPlaying(int channel) noexcept
{
    return Mix_Playing(channel);
}


int isPaused(int channel) noexcept
{
    return Mix_Paused(channel);
}


void fadeInMusic(LX_Music& music, int ms) noexcept
{
    music.fadeIn(ms);
}


void fadeInMusicPos(LX_Music& music, int ms, int pos) noexcept
{
    music.fadeInPos(ms, pos);
}


void fadeOutMusic(int ms) noexcept
{
    Mix_FadeOutMusic(ms);
}


void setPanning(uint8_t left, uint8_t right) noexcept
{
    Mix_SetPanning(MIX_CHANNEL_POST, left, right);
}

void setPanning(int chan, uint8_t left, uint8_t right) noexcept
{
    Mix_SetPanning(chan, left, right);
}

void removePanning() noexcept
{
    setPanning(LX_MIXER_EFFECT_LOUD, LX_MIXER_EFFECT_LOUD);
}

void removePanning(int chan) noexcept
{
    setPanning(chan, LX_MIXER_EFFECT_LOUD, LX_MIXER_EFFECT_LOUD);
}

void setPosition(int16_t angle) noexcept
{
    setPosition(angle, LX_MIXER_EFFECT_NO_DISTANCE);
}


void setPosition(int16_t angle, uint8_t distance) noexcept
{
    Mix_SetPosition(MIX_CHANNEL_POST, angle, distance);
}

void setPosition(int chan, int16_t angle, uint8_t distance) noexcept
{
    Mix_SetPosition(chan, angle, distance);
}


void resetPosition() noexcept
{
    Mix_SetPosition(MIX_CHANNEL_POST, LX_MIXER_EFFECT_NO_ANGLE,
                    LX_MIXER_EFFECT_NO_DISTANCE);
}

void resetPosition(int chan) noexcept
{
    Mix_SetPosition(chan, LX_MIXER_EFFECT_NO_ANGLE, LX_MIXER_EFFECT_NO_DISTANCE);
}

void reverseStereo(bool flip) noexcept
{
    reverseStereo(MIX_CHANNEL_POST, flip);
}

void reverseStereo(int chan, bool flip) noexcept
{
    int opt = flip ? 1:0;
    Mix_SetReverseStereo(chan, opt);
}

void setDistance(uint8_t distance) noexcept
{
    Mix_SetDistance(MIX_CHANNEL_POST, distance);
}

void setDistance(int chan, uint8_t distance) noexcept
{
    Mix_SetDistance(chan, distance);
}

}
