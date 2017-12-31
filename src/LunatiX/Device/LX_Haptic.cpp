
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
*   @file LX_Haptic.cpp
*   @brief The Haptic system implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*
*/

#include <LunatiX/LX_Haptic.hpp>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_haptic.h>


namespace LX_Device
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

// Specific to LX_Haptic
struct LX_Haptic_
{
    int _instanceID;

    explicit LX_Haptic_(int i) noexcept
    {
        _instanceID = i;
    }

    ~LX_Haptic_() = default;
};

// Common data
struct LX_Haptic_common
{
    SDL_Haptic *_haptic;

    explicit LX_Haptic_common(SDL_Haptic *h) noexcept
    {
        _haptic = h;
    }

    ~LX_Haptic_common()
    {
        SDL_HapticClose(_haptic);
    }
};


/* LX_Haptic */

LX_Haptic::LX_Haptic() noexcept
    : _himpl(new LX_Haptic_(-1)), _hcimpl(new LX_Haptic_common(nullptr)) {}


LX_Haptic::LX_Haptic(int index) noexcept
    : _himpl(new LX_Haptic_(index)),
      _hcimpl(new LX_Haptic_common(SDL_HapticOpen(index))) {}


LX_Haptic::LX_Haptic(LX_Joystick *joy) noexcept
    : _himpl(new LX_Haptic_(SDL_JoystickInstanceID(joy))),
      _hcimpl(new LX_Haptic_common(SDL_HapticOpenFromJoystick(joy))) {}


LX_Haptic::LX_Haptic(LX_GameController *gc) noexcept
    : LX_Haptic(SDL_GameControllerGetJoystick(gc)) {}


LX_Haptic::~LX_Haptic()
{
    _hcimpl.reset();
    _himpl.reset();
}


bool LX_Haptic::isOpened() const noexcept
{
    return SDL_HapticOpened(_himpl->_instanceID) == 1;
}


bool LX_Haptic::rumbleEffectInit() noexcept
{
    if(SDL_HapticRumbleSupported(_hcimpl->_haptic) == SDL_TRUE)
        return SDL_HapticRumbleInit(_hcimpl->_haptic) == 0;

    return false;
}

void LX_Haptic::rumbleEffectPlay() noexcept
{
    rumbleEffectPlay(1, 100);
}

void LX_Haptic::rumbleEffectPlay(float strength, uint32_t length) noexcept
{
    if(strength < 0.0f)
        strength = 0.0f;
    else if(strength > 1.0f)
        strength = 1.0f;

    SDL_HapticRumblePlay(_hcimpl->_haptic, strength, length);
}


bool LX_Haptic::effectSupported(LX_HapticEffect& effect) const noexcept
{
    return SDL_HapticEffectSupported(_hcimpl->_haptic, &effect) == SDL_TRUE;
}

int LX_Haptic::newEffect(LX_HapticEffect& effect) noexcept
{
    return SDL_HapticNewEffect(_hcimpl->_haptic, &effect);
}

void LX_Haptic::runEffect(int effect_id, uint32_t iterations) noexcept
{
    SDL_HapticRunEffect(_hcimpl->_haptic, effect_id, iterations);
}

void LX_Haptic::stopEffect(int effect_id) noexcept
{
    SDL_HapticStopEffect(_hcimpl->_haptic, effect_id);
}


int LX_Haptic::numberOfEffects() const noexcept
{
    return SDL_HapticNumEffects(_hcimpl->_haptic);
}

/* LX_MouseHaptic */

LX_MouseHaptic::LX_MouseHaptic() noexcept: LX_Haptic()
{
    _hcimpl.reset(new LX_Haptic_common(SDL_HapticOpenFromMouse()));
}

bool LX_MouseHaptic::isOpened() const noexcept
{
    return _hcimpl != nullptr;
}

LX_MouseHaptic::~LX_MouseHaptic() {}

}
