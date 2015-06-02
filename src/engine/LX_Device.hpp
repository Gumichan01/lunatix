#ifndef LX_DEVICE_HPP_INCLUDED
#define LX_DEVICE_HPP_INCLUDED



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
*	@file LX_Device.hpp
*	@brief The library that deals with gamepads and mouse cursor
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_gamecontroller.h>

#define LX_JOY_NAMESIZE 64              /**< The size of the joystick name */
#define LX_MOUSE_SHOW SDL_ENABLE        /**< Enable the mouse display */
#define LX_MOUSE_HIDE SDL_DISABLE       /**< Disable the mouse display */
#define LX_MOUSE_QUERY SDL_QUERY        /**< Get the mouse status */


namespace LX_Device
{

/**
*   @struct LX_GamepadInfo
*   @brief Information about gamepad
*
*   This structure gathers information about a gamepad
*/
typedef struct LX_GamepadInfo
{

    SDL_JoystickID id;              /**< The joystick ID */
    char name[LX_JOY_NAMESIZE];     /**< The name of the joystick */
    int numAxis;                    /**< The number of axes */
    int numBalls;                   /**< The number of balls */
    int numButtons;                 /**< The number of buttons */
    int numHats;                    /**< The number of hats */

} LX_GamepadInfo; /**< @brief The gamepad structure */


int numberOfDevices(void);

const char * nameOf(SDL_Joystick * joy);
const char * nameOf(SDL_GameController * controller);

int statGamepad(SDL_Joystick * joy, LX_GamepadInfo *info);
int statGamepad(SDL_GameController * gp, LX_GamepadInfo *info);

const char * gamepadToString(LX_GamepadInfo *info);

int mouseCursorDisplay(int toggle);

};


#endif // LX_DEVICE_HPP_INCLUDED


