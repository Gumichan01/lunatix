
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


LX_Haptic * getMouseHaptic()
{
    SDL_Haptic * sdl_hap = SDL_HapticOpenFromMouse();

    if(sdl_hap == nullptr)
        return nullptr;

    LX_Haptic *hap = new LX_Haptic();
    (*hap) = (*sdl_hap);

    return hap;
}


LX_Haptic::LX_Haptic() : _haptic(nullptr), _instanceID(-1) {}

LX_Haptic& LX_Haptic::operator =(SDL_Haptic& haptic)
{
    _haptic = &haptic;
    return *this;
}


LX_Haptic::LX_Haptic(int index)
    : _haptic(SDL_HapticOpen(index)), _instanceID(index) {}


LX_Haptic::LX_Haptic(SDL_Joystick *joy)
    : _haptic(SDL_HapticOpenFromJoystick(joy)),
      _instanceID(SDL_JoystickInstanceID(joy)) {}


LX_Haptic::LX_Haptic(SDL_GameController *gc)
    : LX_Haptic(SDL_GameControllerGetJoystick(gc)) {}


LX_Haptic::~LX_Haptic()
{
    SDL_HapticClose(_haptic);
}


bool LX_Haptic::isOpened()
{
    return SDL_HapticOpened(_instanceID) == 1;
}


bool LX_Haptic::rumbleEffectInit()
{
    if(SDL_HapticRumbleSupported(_haptic) == SDL_TRUE)
        return SDL_HapticRumbleInit(_haptic) == 0;

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

    SDL_HapticRumblePlay(_haptic,strength,length);
}


int LX_Haptic::newEffect(SDL_HapticEffect& effect)
{
    return SDL_HapticNewEffect(_haptic,&effect);
}


void LX_Haptic::runEffect(int effect_id, uint32_t iterations)
{
    SDL_HapticRunEffect(_haptic,effect_id,iterations);
}


void LX_Haptic::stopEffect(int effect_id)
{
    SDL_HapticStopEffect(_haptic,effect_id);
}


int LX_Haptic::numberOfEffects()
{
    return SDL_HapticNumEffects(_haptic);
}

};
