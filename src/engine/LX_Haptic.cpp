
/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Haptic.cpp
*	@brief The Haptic implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include "LX_Haptic.hpp"

namespace LX_Device
{


int numberOfHapticDevices(void)
{
    return SDL_NumHaptics();
}



bool isHaptic(SDL_Joystick *joy)
{
    return SDL_JoystickIsHaptic(joy) == 1;
}



LX_Haptic::LX_Haptic(int index)
{
    haptic = SDL_HapticOpen(index);
    instanceID = index;
}



LX_Haptic::LX_Haptic(SDL_Joystick *joy)
{
    haptic = SDL_HapticOpenFromJoystick(joy);
    instanceID = SDL_JoystickInstanceID(joy);
}


LX_Haptic::~LX_Haptic()
{
    SDL_HapticClose(haptic);
}



bool LX_Haptic::isOpened(void)
{
    return SDL_HapticOpened(instanceID);
}



bool LX_Haptic::RumbleEffectInit(void)
{
    if(SDL_HapticRumbleSupported(haptic) == SDL_TRUE)
        return SDL_HapticRumbleInit(haptic) == 0;

    return false;
}



void LX_Haptic::RumbleEffectPlay(void)
{
    RumbleEffectPlay(1,100);
}



void LX_Haptic::RumbleEffectPlay(float strengh, Uint32 length)
{
    if(strengh < 0)
        strengh = 0;
    else if(strengh > 1)
        strengh = 0;

    SDL_HapticRumblePlay(haptic,strengh,length);
}



int LX_Haptic::newEffect(SDL_HapticEffect * effect)
{
    return SDL_HapticNewEffect(haptic,effect);
}



void LX_Haptic::runEffect(int effectID, Uint32 iterations)
{
    SDL_HapticRunEffect(haptic,effectID,iterations);
}



void LX_Haptic::stopEffect(int effectID)
{
    SDL_HapticStopEffect(haptic,effectID);
}



int LX_Haptic::numberOfEffects(void)
{
    SDL_HapticNumEffects(haptic);
}





};









