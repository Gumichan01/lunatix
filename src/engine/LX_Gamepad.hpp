#ifndef LX_GAMEPAD_HPP_INCLUDED
#define LX_GAMEPAD_HPP_INCLUDED



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
*	@file LX_Gamepad.hpp
*	@brief The file that contains the declaration of LX_Gamepad
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include <iostream> // Debug
#include "LX_Device.hpp"


namespace LX_Device
{

/**
*   @class LX_Gamepad
*   @brief The gamepad class
*
*   It handles any type of gamepad
*
*/
class LX_Gamepad
{

    SDL_GameController *gc;
    SDL_Joystick *joy;


public :

    LX_Gamepad(int index=0);

    bool isConnected(void);
    SDL_JoystickID getID(void);
    const char * getName(void);
    const char * toString(void);

    ~LX_Gamepad();

};


};


#endif  // LX_GAMEPAD_HPP_INCLUDED





