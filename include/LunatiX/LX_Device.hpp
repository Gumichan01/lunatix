
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_DEVICE_HPP_INCLUDED
#define LX_DEVICE_HPP_INCLUDED

/**
*   @file LX_Device.hpp
*   @brief The Device header
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <SDL2/SDL_joystick.h>


/**
*   @defgroup Device Device
*   @brief Device handling (gamepad, mouse, force feedback)
*/

/**
*   @ingroup Device
*   @namespace LX_Device
*   @brief The device namespace
*
*   This namespaces handles several types of device (gamepad, mouse)
*   and the haptic system
*
*   @warning In order to use any gamepad in LX_Device, the *gamepad* flag
*   in the configuration file must be set to 1, otherwise the behaviour of
*   the library is undefined.
*
*/
namespace LX_Device
{

const int LX_MOUSE_SHOW  = 1;     /**< Enable the mouse display   */
const int LX_MOUSE_HIDE  = 0;     /**< Disable the mouse display  */
const int LX_MOUSE_QUERY = -1;    /**< Get the mouse status       */

using LX_DeviceID = int32_t;
using LX_DeviceGUID = SDL_JoystickGUID;

/**
*   @struct LX_GamepadInfo
*   @brief Information about gamepad
*/
struct LX_GamepadInfo
{
    LX_DeviceID id;         /**< The joystick ID            */
    LX_DeviceGUID uid;      /**< The joystick UID           */
    UTF8string name;        /**< The name of the joystick   */
    UTF8string is_haptic;   /**< Haptic joystick or not     */
    int nb_axis;            /**< The number of axes         */
    int nb_balls;           /**< The number of balls        */
    int nb_buttons;         /**< The number of buttons      */
    int nb_hats;            /**< The number of hats         */
};


/**
*   @fn int numberOfDevices() noexcept
*   Count the number of plugged devices (gamepads)
*   @return The number of gamepads
*/
int numberOfDevices() noexcept;

/**
*   @fn UTF8string gamepadToString(LX_GamepadInfo& info)
*
*   Get the string format of the information structure
*
*   @param [in] info The information structure
*   @return Always returns a valid string
*
*   @note This function never returns an invalid string
*   @sa statGamepad
*/
UTF8string gamepadToString(LX_GamepadInfo& info);

/**
*   @fn int mouseCursorDisplay(int toggle) noexcept
*
*   Define if the cursor will be shown or not
*
*   @param [in] toggle One of these following values :
*           - ::LX_MOUSE_SHOW:  to show it
*           - ::LX_MOUSE_HIDE:  to hide
*           - ::LX_MOUSE_QUERY: to get the current state
*
*   @return LX_MOUSE_SHOW if the cursor is shown, LX_MOUSE_HIDE if it is hidden,
*          a negative value on failure.
*/
int mouseCursorDisplay(int toggle) noexcept;

}

#endif // LX_DEVICE_HPP_INCLUDED
