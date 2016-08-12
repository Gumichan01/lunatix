#ifndef LX_DEVICE_HPP_INCLUDED
#define LX_DEVICE_HPP_INCLUDED


/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    The LunatiX Engine is a SDL2-based game engine.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_Device.hpp
*    @brief The library that deals with gamepads and mouse cursor
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <SDL2/SDL_joystick.h>

#define LX_MOUSE_SHOW SDL_ENABLE        /**< Enable the mouse display   */
#define LX_MOUSE_HIDE SDL_DISABLE       /**< Disable the mouse display  */
#define LX_MOUSE_QUERY SDL_QUERY        /**< Get the mouse status       */

namespace LX_Graphics
{
class LX_Surface;
}

struct SDL_Cursor;

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
*   @class LX_Mouse
*   @brief The mouse cursor
*/
class LX_Mouse
{
    SDL_Cursor * _cursor;

public:

    /**
    *   @fn LX_Mouse(LX_Graphics::LX_Surface& surface, int hot_x, int hot_y)
    *
    *   Construct the mouse cursor using a surface and the coordinates of
    *   the mouse clicking zone
    *
    *   @param [in] surface The surface image to load the cursor from
    *   @param [in] hot_x The x hot spot position
    *   @param [in] hot_y The y hot spot position
    */
    LX_Mouse(LX_Graphics::LX_Surface& surface, int hot_x, int hot_y);
    /**
    *   @fn bool isOpen()
    *
    *   Check if the mouse is loaded without issues
    *
    *   @return TRUE if there is no problem, FALSE otherwise
    */
    bool isOpen();
    /**
    *   @fn void setMouse()
    *   Activate the current mouse
    */
    void setMouse();
    /// Destructor
    ~LX_Mouse();
};

/**
*   @fn int numberOfDevices(void)
*
*   Count the number of connected devices (gamepads)
*
*   @return The number of gamepads
*/
int numberOfDevices(void);

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
*   Define is the cursor will be shown or not
*
*   @param [in] toggle One of hese following values :
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

