#ifndef LX_GAMEPAD_HPP_INCLUDED
#define LX_GAMEPAD_HPP_INCLUDED


/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Gamepad.hpp
*	@brief The file that contains the declaration of LX_Gamepad
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.7
*
*/

#include <string>

#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_gamecontroller.h>

namespace LX_Device
{

class LX_Haptic;

/**
*   @class LX_Gamepad
*   @brief The gamepad (joystick, game controller)
*
*   It handles any type of gamepad
*/
class LX_Gamepad
{
    SDL_GameController *gc;
    SDL_Joystick *joy;
    LX_Haptic *haptic;


public :

    LX_Gamepad(int index=0);

    bool isConnected(void);
    bool isHaptic(void);

    SDL_JoystickID getID(void);
    LX_Haptic * getHaptic(void);
    const char * getName(void);
    const char * toString(void);

    ~LX_Gamepad();
};

};

#endif  // LX_GAMEPAD_HPP_INCLUDED

