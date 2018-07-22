

/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file Mixer.cpp
*   @brief The implementation of the mixer library
*   @author Luxon Jean-Pierre(Gumichan01)
*
*
*/

#include <Lunatix/Mixer.hpp>
#include <Lunatix/Music.hpp>
#include <Lunatix/Chunk.hpp>
#include <Lunatix/FileBuffer.hpp>
#include <SDL2/SDL_mixer.h>

#include <functional>

using namespace lx::FileIO;

namespace
{

const uint8_t MIX_FX_LOUD = 255;         /**< Loud (for effect functions)    */
const uint8_t MIX_FX_SILENCE = 0;        /**< Silence (for effect functions) */
const uint8_t MIX_FX_NO_distance = 0;    /**< The distance between the source and the listener */
const uint16_t MIX_FX_NO_ANGLE = 0;      /**< The angle between the source and the front */

constexpr struct lx::Mixer::MixerEffectType EFFECT_NONE;

constexpr bool operator ==( const lx::Mixer::MixerEffectType& t,
                            const lx::Mixer::MixerEffectType& u )
{
    return t.distance == u.distance && t.panning == u.panning
           && t.position == u.position && t.reverse_stereo == u.reverse_stereo;
}

constexpr bool operator !=( const lx::Mixer::MixerEffectType& t,
                            const lx::Mixer::MixerEffectType& u )
{
    return !( t == u );
}

// In C++14, this function can be constexpr
inline unsigned short adaptVolume_( unsigned short pvol, unsigned short ov, unsigned short maxv )
{
    // I use std::divides and std::multiplies because the compiler
    // seems to convert unsigned short values to integer become applying
    // the calculation
    using uint16 = unsigned short;
    return std::divides<uint16>()( std::multiplies<uint16>()( pvol, ov ), maxv );
}

}


namespace lx
{

namespace Mixer
{

const unsigned short MAX_VOLUME = 100;
const unsigned short DEFAULT_VOLUME = 100;
// Overall volume in volume unit [0-100]
unsigned short overall_volume = DEFAULT_VOLUME;
// Music volume in volume unit [0-100]
unsigned short music_volume = DEFAULT_VOLUME;
// Effects volume in volume unit [0-100]
unsigned short fx_volume = DEFAULT_VOLUME;

// Music volume in percentage
unsigned short music_pvolume = DEFAULT_VOLUME;
// Effects volume in percentage
unsigned short fx_pvolume = DEFAULT_VOLUME;

int selectChannel( int tag ) noexcept;
void applyEffect( int chan, const MixerEffect& effect ) noexcept;

void setOverallVolume( unsigned short volume ) noexcept
{
    if ( volume > MAX_VOLUME )
        overall_volume = MAX_VOLUME;
    else
        overall_volume = volume;

    setMusicVolume( music_pvolume );
    setFXVolume( fx_pvolume );
}

void setMusicVolume( unsigned short pvolume ) noexcept
{
    if ( pvolume > MAX_VOLUME )
        pvolume = MAX_VOLUME;

    if ( overall_volume == 0 )
        music_volume = 0;
    else
        music_volume = adaptVolume_( pvolume, overall_volume, MAX_VOLUME );

    Mix_VolumeMusic( music_volume );
    music_pvolume = pvolume;
}

void setFXVolume( unsigned short pvolume ) noexcept
{
    if ( pvolume > MAX_VOLUME )
        pvolume = MAX_VOLUME;

    if ( overall_volume == 0 )
        fx_volume = 0;
    else
        fx_volume = adaptVolume_( pvolume, overall_volume, MAX_VOLUME );

    if ( allocateChannels( -1 ) > 0 )
        Mix_Volume( -1, fx_volume );

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


Chunk * loadSample( lx::FileIO::FileBuffer& file )
{
    return file.loadSample();
}


void setMusicPosition( double pos ) noexcept
{
    Mix_RewindMusic();
    Mix_SetMusicPosition( pos );
}


int allocateChannels( int num ) noexcept
{
    int n = Mix_AllocateChannels( num );

    // Set the volume of every channels to *fx_volume*
    if ( num > 0 )
        Mix_Volume( -1, fx_volume );

    return n;
}


int reserveChannels( int numchans ) noexcept
{
    return Mix_ReserveChannels( numchans );
}


bool groupChannel( int chan, int tag ) noexcept
{
    return Mix_GroupChannel( chan, tag ) == 1;
}


int groupChannels( int from, int to, int tag ) noexcept
{
    return Mix_GroupChannels( from, to, tag );
}

int groupCount( int tag ) noexcept
{
    return Mix_GroupCount( tag );
}


int channelAvailable( int tag ) noexcept
{
    return Mix_GroupAvailable( tag );
}

// private function
int selectChannel( int tag ) noexcept
{
    int chan = channelAvailable( tag );

    if ( chan == -1 )
    {
        chan = Mix_GroupOldest( tag );

        if ( chan > -1 )
            haltChannel( chan );
    }

    return chan;
}

// private function
void applyEffect( int chan, const MixerEffect& effect ) noexcept
{
    Mix_UnregisterAllEffects( chan );

    if ( effect.type != EFFECT_NONE )
    {
        if ( effect.type.panning )
            setPanning( chan, effect.pan_left, effect.pan_right );

        if ( effect.type.position )
            setPosition( chan, effect.pos_angle, effect.pos_distance );

        if ( effect.type.distance )
            setDistance( chan, effect.distance );

        if ( effect.type.reverse_stereo )
            reverseStereo( chan, effect.rev_stereo );
    }
}

bool groupPlayChunk( Chunk& chunk, int tag, const MixerEffect effect ) noexcept
{
    if ( groupCount( tag ) != 0 )
        tag = -1;

    int chan = selectChannel( tag );
    applyEffect( chan, effect );
    return chunk.play( chan, effect.loops );
}

void pause( int channel ) noexcept
{
    Mix_Pause( channel );
}


void resume( int channel ) noexcept
{
    Mix_Resume( channel );
}


void haltChannel( int channel ) noexcept
{
    Mix_HaltChannel( channel );
}


void expireChannel( int channel, int ticks ) noexcept
{
    Mix_ExpireChannel( channel, ticks );
}


int isPlaying( int channel ) noexcept
{
    return Mix_Playing( channel );
}


int isPaused( int channel ) noexcept
{
    return Mix_Paused( channel );
}


void fadeInMusic( Music& music, int ms ) noexcept
{
    music.fadeIn( ms );
}


void fadeInMusicPos( Music& music, int ms, int pos ) noexcept
{
    music.fadeInPos( ms, pos );
}


void fadeOutMusic( int ms ) noexcept
{
    Mix_FadeOutMusic( ms );
}


void setPanning( uint8_t left, uint8_t right ) noexcept
{
    Mix_SetPanning( MIX_CHANNEL_POST, left, right );
}

void setPanning( int chan, uint8_t left, uint8_t right ) noexcept
{
    Mix_SetPanning( chan, left, right );
}

void removePanning() noexcept
{
    setPanning( MIX_FX_LOUD, MIX_FX_LOUD );
}

void removePanning( int chan ) noexcept
{
    setPanning( chan, MIX_FX_LOUD, MIX_FX_LOUD );
}

void setPosition( int16_t angle ) noexcept
{
    setPosition( angle, MIX_FX_NO_distance );
}


void setPosition( int16_t angle, uint8_t distance ) noexcept
{
    Mix_SetPosition( MIX_CHANNEL_POST, angle, distance );
}

void setPosition( int chan, int16_t angle, uint8_t distance ) noexcept
{
    Mix_SetPosition( chan, angle, distance );
}


void resetPosition() noexcept
{
    Mix_SetPosition( MIX_CHANNEL_POST, MIX_FX_NO_ANGLE,
                     MIX_FX_NO_distance );
}

void resetPosition( int chan ) noexcept
{
    Mix_SetPosition( chan, MIX_FX_NO_ANGLE, MIX_FX_NO_distance );
}

void reverseStereo( bool flip ) noexcept
{
    reverseStereo( MIX_CHANNEL_POST, flip );
}

void reverseStereo( int chan, bool flip ) noexcept
{
    int opt = flip ? 1 : 0;
    Mix_SetReverseStereo( chan, opt );
}

void setDistance( uint8_t distance ) noexcept
{
    Mix_SetDistance( MIX_CHANNEL_POST, distance );
}

void setDistance( int chan, uint8_t distance ) noexcept
{
    Mix_SetDistance( chan, distance );
}

MixerEffect::MixerEffect() : type() {}

}   // Mixer

}   // lx
