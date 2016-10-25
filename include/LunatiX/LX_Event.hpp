#ifndef LX_EVENT_HPP_INCLUDED
#define LX_EVENT_HPP_INCLUDED


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
*    @file LX_Event.hpp
*    @brief The Event module
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <SDL2/SDL_events.h>

/// @todo (#1#) LX_EventHandler: Full implementation
/// @todo (#2#) LX_EventHandler: Documentation

namespace LX_EventHandler
{
using LX_Event = SDL_Event;                         /* Event                        */
using LX_UserEvent = SDL_UserEvent;                 /* User-defined event           */
using LX_KeyCode = SDL_Keycode;                     /* Virtual key representation   */
using LX_ScanCode = SDL_Scancode;                   /* Physical key representation  */
using LX_GamepadButton = SDL_GameControllerButton;  /* Gamepad button               */
using LX_GamepadAxis = SDL_GameControllerAxis;      /* Gamepad axis                 */

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

// Button state
const uint8_t LX_BUTTON_RELEASED = SDL_RELEASED;
const uint8_t LX_BUTTON_PRESSED  = SDL_PRESSED;

const LX_GamepadAxis LX_AXIS_INVALID      = SDL_CONTROLLER_AXIS_INVALID;
const LX_GamepadAxis LX_AXIS_LEFTX        = SDL_CONTROLLER_AXIS_LEFTX;
const LX_GamepadAxis LX_AXIS_LEFTY        = SDL_CONTROLLER_AXIS_LEFTY;
const LX_GamepadAxis LX_AXIS_RIGHTX       = SDL_CONTROLLER_AXIS_RIGHTX;
const LX_GamepadAxis LX_AXIS_RIGHTY       = SDL_CONTROLLER_AXIS_RIGHTY;
const LX_GamepadAxis LX_AXIS_TRIGGERLEFT  = SDL_CONTROLLER_AXIS_TRIGGERLEFT;
const LX_GamepadAxis LX_AXIS_TRIGGERRIGHT = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
const LX_GamepadAxis LX_AXIS_MAX          = SDL_CONTROLLER_AXIS_MAX;

// Axis represantation of a gamepad
struct LX_GAxis
{
    SDL_JoystickID id;      /* ID of the gamepad        */
    LX_GamepadAxis axis;    /* Axis                     */
    int16_t value;          /* Value [-32768 ↔ 32768]   */
};

// Button represantation of a gamepad
struct LX_GButton
{
    SDL_JoystickID which;   /* ID of the gamepad                                */
    LX_GamepadButton value; /* Button value                                     */
    int16_t state;          /* Value : LX_BUTTON_PRESSED or LX_BUTTON_RELEASED  */
};


bool pollEvent(LX_Event& event);
bool waitEvent(LX_Event& event);
bool waitEventTimeout(LX_Event& event, int timeout);

bool pushEvent(LX_Event& event);
bool pushUserEvent(LX_UserEvent& uevent);

// Keyboard

LX_KeyCode getKeyCode(LX_Event& event);
LX_ScanCode getScanCode(LX_Event& event);

LX_KeyCode getKeyCodeFrom(LX_ScanCode scancode);
LX_ScanCode getScanCodeFrom(LX_KeyCode keycode);

UTF8string stringOfScanCode(LX_ScanCode scancode);
UTF8string stringOfKeyCode(LX_KeyCode keycode);


// Gamepad

const LX_GAxis getAxis(LX_Event& event);
const LX_GButton getButton(LX_Event& event);

UTF8string stringOfButton(LX_GamepadButton button);
UTF8string stringOfButton(uint8_t button);

UTF8string stringOfAxis(LX_GamepadAxis axis);
UTF8string stringOfAxis(uint8_t axis);


/// @todo (#2#) LX_EventHandler: Get keypad (and test it) and mouse buttons
/// @todo (#1#) LX_EventHandler: Get gamepad button and test it

};

#endif // LX_EVENT_HPP_INCLUDED
