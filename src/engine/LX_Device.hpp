#ifndef LX_DEVICE_HPP_INCLUDED
#define LX_DEVICE_HPP_INCLUDED



/*
*
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
*	@brief The LX_Device library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.3
*
*/

#include <SDL2/SDL.h>

namespace LX_Device{


    int numberOfDevices(void);

    const char * nameOf(SDL_Joystick * joy);
    const char * nameOf(SDL_GameController * controller);

};




#endif // LX_DEVICE_HPP_INCLUDED



