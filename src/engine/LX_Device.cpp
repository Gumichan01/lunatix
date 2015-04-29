

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
*	@brief The LX_Device implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.3
*
*/

#include "LX_Device.hpp"


namespace LX_Device{


    /**
    *   @fn int numberOfDevices(void)
    *
    *   Count the number of connected devices (joystick and gamepads)
    *
    */
    int numberOfDevices(void)
    {
      return SDL_NumJoysticks();
    }


    /**
    *   @fn const char * nameOf(SDL_Joystick * joy)
    *
    *   Get the name of a joystick
    *
    *   @param joy The pointer to a joystick structure
    *
    *   @return the name of the joystick, NULL if the pointer is not valid
    *
    */
    const char * nameOf(SDL_Joystick * joy)
    {
        return SDL_JoystickName(joy);
    }


    /**
    *   @fn const char * nameOf(SDL_GameController * controller)
    *
    *   Get the name of a game controller
    *
    *   @param controller The pointer to a structure relative to the gamepad
    *
    *   @return the name of the game controller, NULL if the pointer is not valid
    *
    */
    const char * nameOf(SDL_GameController * controller)
    {
        return SDL_GameControllerName(controller);
    }


};




