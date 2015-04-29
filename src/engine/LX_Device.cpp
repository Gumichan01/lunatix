

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




