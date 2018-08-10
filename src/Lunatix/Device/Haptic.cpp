
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
*   @file Haptic.cpp
*   @brief The Haptic system implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*/

#include <Lunatix/Haptic.hpp>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_haptic.h>


namespace lx
{

namespace Device
{

int numberOfHapticDevices() noexcept
{
    return SDL_NumHaptics();
}


bool mouseIsHaptic() noexcept
{
    return SDL_MouseIsHaptic() == 1;
}

/* Private implementation */

// Specific to Haptic
struct Haptic_ final
{
    int instance_id = -1;

    Haptic_( const Haptic_& ) = delete;
    Haptic_& operator =( const Haptic_& ) = delete;

    explicit Haptic_( int i ) noexcept : instance_id( i ) {}
    ~Haptic_() = default;
};

// Common data
struct Haptic_common final
{
    SDL_Haptic * haptic = nullptr;

    Haptic_common( const Haptic_common& ) = delete;
    Haptic_common& operator =( const Haptic_common& ) = delete;

    explicit Haptic_common( SDL_Haptic * h ) noexcept
    {
        haptic = h;
    }

    ~Haptic_common()
    {
        SDL_HapticClose( haptic );
    }
};


/* Haptic */

Haptic::Haptic() noexcept
    : m_himpl( new Haptic_( -1 ) ), _hcimpl( new Haptic_common( nullptr ) ) {}


Haptic::Haptic( int index ) noexcept
    : m_himpl( new Haptic_( index ) ),
      _hcimpl( new Haptic_common( SDL_HapticOpen( index ) ) ) {}


Haptic::Haptic( Joystick * joy ) noexcept
    : m_himpl( new Haptic_( SDL_JoystickInstanceID( joy ) ) ),
      _hcimpl( new Haptic_common( SDL_HapticOpenFromJoystick( joy ) ) ) {}


Haptic::Haptic( GameController * gc ) noexcept
    : Haptic( SDL_GameControllerGetJoystick( gc ) ) {}



bool Haptic::isOpened() const noexcept
{
    return SDL_HapticOpened( m_himpl->instance_id ) == 1;
}


bool Haptic::rumbleEffectInit() noexcept
{
    if ( SDL_HapticRumbleSupported( _hcimpl->haptic ) == SDL_TRUE )
        return SDL_HapticRumbleInit( _hcimpl->haptic ) == 0;

    return false;
}

void Haptic::rumbleEffectPlay() noexcept
{
    rumbleEffectPlay( 1, 100 );
}

void Haptic::rumbleEffectPlay( float strength, uint32_t length ) noexcept
{
    if ( strength < 0.0f )
        strength = 0.0f;
    else if ( strength > 1.0f )
        strength = 1.0f;

    SDL_HapticRumblePlay( _hcimpl->haptic, strength, length );
}


bool Haptic::effectSupported( HapticEffect& effect ) const noexcept
{
    return SDL_HapticEffectSupported( _hcimpl->haptic, &effect ) == SDL_TRUE;
}

int Haptic::newEffect( HapticEffect& effect ) noexcept
{
    return SDL_HapticNewEffect( _hcimpl->haptic, &effect );
}

void Haptic::runEffect( int effect_id, uint32_t iterations ) noexcept
{
    SDL_HapticRunEffect( _hcimpl->haptic, effect_id, iterations );
}

void Haptic::stopEffect( int effect_id ) noexcept
{
    SDL_HapticStopEffect( _hcimpl->haptic, effect_id );
}


int Haptic::numberOfEffects() const noexcept
{
    return SDL_HapticNumEffects( _hcimpl->haptic );
}

Haptic::~Haptic()
{
    _hcimpl.reset();
}

/* MouseHaptic */

MouseHaptic::MouseHaptic() noexcept: Haptic()
{
    _hcimpl.reset( new Haptic_common( SDL_HapticOpenFromMouse() ) );
}

bool MouseHaptic::isOpened() const noexcept
{
    return _hcimpl != nullptr;
}

}   // Device

}   // lx
