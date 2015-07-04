
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






};









