
/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_Haptic.cpp
*    @brief The Haptic system implementation
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/LX_Haptic.hpp>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_haptic.h>


namespace LX_Device
{

int numberOfHapticDevices()
{
    return SDL_NumHaptics();
}


bool mouseIsHaptic()
{
    return SDL_MouseIsHaptic() == 1;
}

/* Private implementation */

// Specific to LX_Haptic
struct LX_Haptic_
{
    int _instanceID;

    LX_Haptic_(int i)
    {
        _instanceID = i;
    }

    ~LX_Haptic_() = default;
};

// Common data
struct LX_Haptic_common
{
    SDL_Haptic *_haptic;

    LX_Haptic_common(SDL_Haptic *h)
    {
        _haptic = h;
    }

    ~LX_Haptic_common()
    {
        SDL_HapticClose(_haptic);
    }
};


/* LX_Haptic */

LX_Haptic::LX_Haptic()
    : _himpl(new LX_Haptic_(-1)), _hcimpl(new LX_Haptic_common(nullptr)) {}


LX_Haptic::LX_Haptic(int index)
    : _himpl(new LX_Haptic_(index)),
      _hcimpl(new LX_Haptic_common(SDL_HapticOpen(index))) {}


LX_Haptic::LX_Haptic(LX_Joystick *joy)
    : _himpl(new LX_Haptic_(SDL_JoystickInstanceID(joy))),
      _hcimpl(new LX_Haptic_common(SDL_HapticOpenFromJoystick(joy))) {}


LX_Haptic::LX_Haptic(LX_GameController *gc)
    : LX_Haptic(SDL_GameControllerGetJoystick(gc)) {}


LX_Haptic::~LX_Haptic()
{
    _hcimpl.reset();
    _himpl.reset();
}


bool LX_Haptic::isOpened() const
{
    return SDL_HapticOpened(_himpl->_instanceID) == 1;
}


bool LX_Haptic::rumbleEffectInit()
{
    if(SDL_HapticRumbleSupported(_hcimpl->_haptic) == SDL_TRUE)
        return SDL_HapticRumbleInit(_hcimpl->_haptic) == 0;

    return false;
}


void LX_Haptic::rumbleEffectPlay()
{
    rumbleEffectPlay(1,100);
}


void LX_Haptic::rumbleEffectPlay(float strength, uint32_t length)
{
    if(strength < 0.0f)
        strength = 0.0f;
    else if(strength > 1.0f)
        strength = 1.0f;

    SDL_HapticRumblePlay(_hcimpl->_haptic,strength,length);
}


bool LX_Haptic::effectSupported(SDL_HapticEffect& effect) const
{
    return SDL_HapticEffectSupported(_hcimpl->_haptic,&effect) == SDL_TRUE;
}


int LX_Haptic::newEffect(SDL_HapticEffect& effect)
{
    return SDL_HapticNewEffect(_hcimpl->_haptic,&effect);
}


void LX_Haptic::runEffect(int effect_id, uint32_t iterations)
{
    SDL_HapticRunEffect(_hcimpl->_haptic,effect_id,iterations);
}


void LX_Haptic::stopEffect(int effect_id)
{
    SDL_HapticStopEffect(_hcimpl->_haptic,effect_id);
}


int LX_Haptic::numberOfEffects() const
{
    return SDL_HapticNumEffects(_hcimpl->_haptic);
}

/* LX_MouseHaptic */

LX_MouseHaptic::LX_MouseHaptic(): LX_Haptic()
{
    _hcimpl.reset(new LX_Haptic_common(SDL_HapticOpenFromMouse()));
}

bool LX_MouseHaptic::isOpened() const
{
    return _hcimpl != nullptr;
}

LX_MouseHaptic::~LX_MouseHaptic() {}

};
