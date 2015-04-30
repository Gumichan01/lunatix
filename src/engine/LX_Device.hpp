#ifndef LX_DEVICE_HPP_INCLUDED
#define LX_DEVICE_HPP_INCLUDED



/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Device.cpp
*	@brief The LX_Device library. It gathers information about gamepad
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.3
*
*/

#include <SDL2/SDL.h>


#define LX_JOY_NAMESIZE 64


namespace LX_Device{

/**
*   @struct LX_GamepadInfo
*   @brief The gamepad information
*
*   This structure gathers information about a gamepad
*
*/
typedef struct LX_GamepadInfo{

    SDL_JoystickID id;
    char name[LX_JOY_NAMESIZE];
    int numAxis;
    int numBalls;
    int numButtons;
    int numHats;

}LX_GamepadInfo; /** < */


    int numberOfDevices(void);

    const char * nameOf(SDL_Joystick * joy);
    const char * nameOf(SDL_GameController * controller);

    int statGamepad(SDL_Joystick * joy, LX_GamepadInfo *info);
    int statGamepad(SDL_GameController * gp, LX_GamepadInfo *info);

    const char * gamepadToString(LX_GamepadInfo *info);

};




#endif // LX_DEVICE_HPP_INCLUDED



