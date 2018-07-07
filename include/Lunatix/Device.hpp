
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef DEVICE_HPP_INCLUDED
#define DEVICE_HPP_INCLUDED

/**
*   @file Device.hpp
*   @brief The Device header
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/utils/utf8_string.hpp>
#include <SDL2/SDL_joystick.h>


/**
*   @defgroup Device Device
*   @brief Device handling (gamepad, mouse, force feedback)
*/

namespace lx
{

/**
*   @ingroup Device
*   @namespace lx::Device
*   @brief The device namespace
*
*   This namespaces handles several types of device (gamepad, mouse)
*   and the haptic system
*
*   @warning In order to use any gamepad in Device, the *gamepad* flag
*   in the configuration file must be set to 1, otherwise the behaviour of
*   the library is undefined.
*
*/
namespace Device
{

/**
*   @enum MouseToggle
*   @brief State of the mouse (display)
*/
enum class MouseToggle
{
    SHOW  = 1,      /**< Enable the mouse display   */
    HIDE  = 0,      /**< Disable the mouse display  */
    QUERY = -1      /**< Get the mouse status       */
};


/**
*   @fn int numberOfDevices() noexcept
*   Count the number of plugged devices (gamepads)
*   @return The number of gamepads
*/
int numberOfDevices() noexcept;


/**
*   @fn MouseToggle mouseCursorDisplay(const MouseToggle& toggle) noexcept
*
*   Define if the cursor will be shown or not
*
*   @param [in] toggle show, hide or query
*
*   @return The status of the mouse.
*/
MouseToggle mouseCursorDisplay( const MouseToggle& toggle ) noexcept;

}   // Device

}   // lx

#endif // DEVICE_HPP_INCLUDED
