#ifndef LX_DEVICE_HPP_INCLUDED
#define LX_DEVICE_HPP_INCLUDED


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
*	@file LX_Device.hpp
*	@brief The library that deals with gamepads and mouse cursor
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.7
*
*/

#include <string>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_gamecontroller.h>

#define LX_MOUSE_SHOW SDL_ENABLE        /**< Enable the mouse display   */
#define LX_MOUSE_HIDE SDL_DISABLE       /**< Disable the mouse display  */
#define LX_MOUSE_QUERY SDL_QUERY        /**< Get the mouse status       */


/**
*   @namespace LX_Device
*   @brief The device module
*/
namespace LX_Device
{

/**
*   @struct LX_GamepadInfo
*   @brief Information about gamepad
*/
typedef struct LX_GamepadInfo
{

    SDL_JoystickID id;              /**< The joystick ID                */
    SDL_JoystickGUID uid;           /**< The joystick UID               */
    std::string name;               /**< The name of the joystick       */
    int nb_axis;                    /**< The number of axes             */
    int nb_balls;                   /**< The number of balls            */
    int nb_buttons;                 /**< The number of buttons          */
    int nb_hats;                    /**< The number of hats             */

} LX_GamepadInfo;                   /**< @brief The gamepad structure   */


int numberOfDevices(void);

const char * nameOf(SDL_Joystick * joy);
const char * nameOf(SDL_GameController * controller);

int statGamepad(SDL_Joystick * joy, LX_GamepadInfo& info);
int statGamepad(SDL_GameController * gp, LX_GamepadInfo& info);

std::string gamepadToString(LX_GamepadInfo& info);

int mouseCursorDisplay(int toggle);

};

#endif // LX_DEVICE_HPP_INCLUDED

