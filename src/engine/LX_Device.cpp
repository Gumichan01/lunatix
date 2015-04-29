

/*
*	Copyright (C)  Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*
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


    int numberOfDevices(void)
    {
      return SDL_NumJoysticks();
    }

    const char * nameOf(SDL_Joystick * joy)
    {
        return SDL_JoystickName(joy);
    }


    const char * nameOf(SDL_GameController * controller)
    {
        return SDL_GameControllerName(controller);
    }


};




