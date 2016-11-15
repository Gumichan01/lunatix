#ifndef LX_DEVICE_HPP_INCLUDED
#define LX_DEVICE_HPP_INCLUDED


/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_Device.hpp
*    @brief The library that deals with gamepads and mouse cursor
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_keyboard.h>

#define LX_MOUSE_SHOW SDL_ENABLE        /**< Enable the mouse display   */
#define LX_MOUSE_HIDE SDL_DISABLE       /**< Disable the mouse display  */
#define LX_MOUSE_QUERY SDL_QUERY        /**< Get the mouse status       */


/**
*   @namespace LX_Device
*   @brief The device module
*/
namespace LX_Device
{

using LX_GamepadButton       = SDL_GameControllerButton;
using LX_GamepadAxis         = SDL_GameControllerAxis;
using LX_KeyboardPhysicalKey = SDL_Scancode;
using LX_KeyboardVirtualKey  = SDL_Keycode;


const LX_GamepadButton LX_BUTTON_INVALID       = SDL_CONTROLLER_BUTTON_INVALID;
const LX_GamepadButton LX_BUTTON_A             = SDL_CONTROLLER_BUTTON_A;
const LX_GamepadButton LX_BUTTON_B             = SDL_CONTROLLER_BUTTON_B;
const LX_GamepadButton LX_BUTTON_X             = SDL_CONTROLLER_BUTTON_X;
const LX_GamepadButton LX_BUTTON_Y             = SDL_CONTROLLER_BUTTON_Y;
const LX_GamepadButton LX_BUTTON_BACK          = SDL_CONTROLLER_BUTTON_BACK;
const LX_GamepadButton LX_BUTTON_GUIDE         = SDL_CONTROLLER_BUTTON_GUIDE;
const LX_GamepadButton LX_BUTTON_START         = SDL_CONTROLLER_BUTTON_START;
const LX_GamepadButton LX_BUTTON_LEFTSTICK     = SDL_CONTROLLER_BUTTON_LEFTSTICK;
const LX_GamepadButton LX_BUTTON_RIGHTSTICK    = SDL_CONTROLLER_BUTTON_RIGHTSTICK;
const LX_GamepadButton LX_BUTTON_LEFTSHOULDER  = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
const LX_GamepadButton LX_BUTTON_RIGHTSHOULDER = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
const LX_GamepadButton LX_BUTTON_DPAD_UP       = SDL_CONTROLLER_BUTTON_DPAD_UP;
const LX_GamepadButton LX_BUTTON_DPAD_DOWN     = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
const LX_GamepadButton LX_BUTTON_DPAD_LEFT     = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
const LX_GamepadButton LX_BUTTON_DPAD_RIGHT    = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
const LX_GamepadButton LX_BUTTON_MAX           = SDL_CONTROLLER_BUTTON_MAX;

const LX_GamepadAxis LX_AXIS_INVALID      = SDL_CONTROLLER_AXIS_INVALID;
const LX_GamepadAxis LX_AXIS_LEFTX        = SDL_CONTROLLER_AXIS_LEFTX;
const LX_GamepadAxis LX_AXIS_LEFTY        = SDL_CONTROLLER_AXIS_LEFTY;
const LX_GamepadAxis LX_AXIS_RIGHTX       = SDL_CONTROLLER_AXIS_RIGHTX;
const LX_GamepadAxis LX_AXIS_RIGHTY       = SDL_CONTROLLER_AXIS_RIGHTY;
const LX_GamepadAxis LX_AXIS_TRIGGERLEFT  = SDL_CONTROLLER_AXIS_TRIGGERLEFT;
const LX_GamepadAxis LX_AXIS_TRIGGERRIGHT = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
const LX_GamepadAxis LX_AXIS_MAX          = SDL_CONTROLLER_AXIS_MAX;


/**
*   @struct LX_GamepadInfo
*   @brief Information about gamepad
*/
struct LX_GamepadInfo
{
    SDL_JoystickID id;              /**< The joystick ID            */
    SDL_JoystickGUID uid;           /**< The joystick UID           */
    UTF8string name;                /**< The name of the joystick   */
    UTF8string is_haptic;           /**< Haptic joystick or not     */
    int nb_axis;                    /**< The number of axes         */
    int nb_balls;                   /**< The number of balls        */
    int nb_buttons;                 /**< The number of buttons      */
    int nb_hats;                    /**< The number of hats         */
};


/**
*   @fn int numberOfDevices()
*
*   Count the number of connected devices (gamepads)
*
*   @return The number of gamepads
*/
int numberOfDevices();

/**
*   @fn UTF8string stringOfButton(LX_GamepadButton button)
*
*   Get the string value of a button specified by the enum
*   given in argument
*
*   @param [in] button The enumeration to get the string from
*
*   @return The string on success, "null" otherwise
*/
UTF8string stringOfButton(LX_GamepadButton button);
/**
*   @fn UTF8string stringOfButton(uint8_t button)
*
*   Get the string value of a button value
*
*   @param [in] button The value to get the string from
*
*   @return The string on success, "null" otherwise
*/
UTF8string stringOfButton(uint8_t button);

/**
*   @fn UTF8string stringOfAxis(LX_GamepadAxis axis)
*
*   Get the string value of an axis specified by the enum
*   given in argument
*
*   @param [in] axis The enumeration to get the string from
*
*   @return The string on success, "null" otherwise
*/
UTF8string stringOfAxis(LX_GamepadAxis axis);
/**
*   @fn UTF8string stringOfAxis(uint8_t axis)
*
*   Get the string value of an axis specified by the enum
*   given in argument
*
*   @param [in] axis The value to get the string from
*
*   @return The string on success, "null" otherwise
*/
UTF8string stringOfAxis(uint8_t axis);

/**
*   @fn UTF8string stringOfPhysicalKey(LX_KeyboardPhysicalKey key)
*
*   Get the string value of the physical key value given in argument
*
*   @param [in] key The physical key value to get the string from
*
*   @return A non-empty string on success, "" otherwise
*/
UTF8string stringOfPhysicalKey(LX_KeyboardPhysicalKey key);
/**
*   @fn UTF8string stringOfVirtualKey(LX_KeyboardVirtualKey key)
*
*   Get the string value of the virtual key value given in argument
*
*   @param [in] key The virtual key value to get the string from
*
*   @return A non-empty string on success, "" otherwise
*/
UTF8string stringOfVirtualKey(LX_KeyboardVirtualKey key);

/**
*   @fn LX_KeyboardVirtualKey getVirtualKey(LX_KeyboardPhysicalKey key)
*
*   Get the virtual key that corresponds to the physical key given in argument
*
*   @param [in] key The virtual key value
*
*   @return The virtual key that corresponds to the physical key
*/
LX_KeyboardVirtualKey getVirtualKey(LX_KeyboardPhysicalKey key);
/**
*   @fn LX_KeyboardPhysicalKey getPhysicalKey(LX_KeyboardVirtualKey key)
*
*   Get the physical key that corresponds to the virtual key given in argument
*
*   @param [in] key The physical key value
*
*   @return The physical key that corresponds to the virtual key
*/
LX_KeyboardPhysicalKey getPhysicalKey(LX_KeyboardVirtualKey key);

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
*   @fn int mouseCursorDisplay(int toggle)
*
*   Define if the cursor will be shown or not
*
*   @param [in] toggle One of these following values :
*            1 to show it
*            0 to hide
*           -1 to get the current state
*
*   @return 1 if the cursor is shown, 0 if it is hidden,
*           a negative value on failure
*
*/
int mouseCursorDisplay(int toggle);

};

#endif // LX_DEVICE_HPP_INCLUDED

