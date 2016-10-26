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
/// @todo (#2#) LX_EventHandler: handle window event
/// @todo (#2#) LX_EventHandler: handle text input/editing events
/// @todo (#2#) LX_EventHandler: handle user event
/// @todo (#2#) LX_EventHandler: handle drag-and-drop event (only DROPFILE)

namespace LX_Event
{
using LX_EventType = uint32_t;                      /* Event type                   */
using LX_EventData = SDL_Event;                     /* Event                        */
using LX_UserEvent = SDL_UserEvent;                 /* User-defined event           */
using LX_KeyCode = SDL_Keycode;                     /* Virtual key representation   */
using LX_ScanCode = SDL_Scancode;                   /* Physical key representation  */
using LX_GamepadButton = SDL_GameControllerButton;  /* Gamepad button               */
using LX_GamepadAxis = SDL_GameControllerAxis;      /* Gamepad axis                 */

using LX_GamepadID = int32_t;                       /* Identifier of the gamepad    */

enum LX_MouseButton: uint8_t {LX_MOUSE_LBUTTON = SDL_BUTTON_LEFT,
                              LX_MOUSE_MBUTTON = SDL_BUTTON_MIDDLE,
                              LX_MOUSE_RBUTTON = SDL_BUTTON_RIGHT,
                              LX_MOUSE_X1 = SDL_BUTTON_X1,
                              LX_MOUSE_X2 = SDL_BUTTON_X2,
                              LX_MOUSE_UNKNWON
                             };

const int LX_MBUTTONS = 6;

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
const uint8_t LX_BUTTON_PRESSED  = SDL_PRESSED;
const uint8_t LX_BUTTON_RELEASED = SDL_RELEASED;

const LX_GamepadAxis LX_AXIS_INVALID      = SDL_CONTROLLER_AXIS_INVALID;
const LX_GamepadAxis LX_AXIS_LEFTX        = SDL_CONTROLLER_AXIS_LEFTX;
const LX_GamepadAxis LX_AXIS_LEFTY        = SDL_CONTROLLER_AXIS_LEFTY;
const LX_GamepadAxis LX_AXIS_RIGHTX       = SDL_CONTROLLER_AXIS_RIGHTX;
const LX_GamepadAxis LX_AXIS_RIGHTY       = SDL_CONTROLLER_AXIS_RIGHTY;
const LX_GamepadAxis LX_AXIS_TRIGGERLEFT  = SDL_CONTROLLER_AXIS_TRIGGERLEFT;
const LX_GamepadAxis LX_AXIS_TRIGGERRIGHT = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
const LX_GamepadAxis LX_AXIS_MAX          = SDL_CONTROLLER_AXIS_MAX;

// Axis of a gamepad
struct LX_GAxis
{
    SDL_JoystickID id;      /* ID of the gamepad        */
    LX_GamepadAxis axis;    /* Axis                     */
    int16_t value;          /* Value [-32768 ↔ 32768]   */
};

// Button of a gamepad
struct LX_GButton
{
    SDL_JoystickID which;   /* ID of the gamepad                                        */
    LX_GamepadButton value; /* Button value                                             */
    int16_t state;          /* Button state : LX_BUTTON_PRESSED or LX_BUTTON_RELEASE    */
};

// Button of a mouse
struct LX_MButton
{
    uint32_t wid;
    LX_MouseButton button;
    uint8_t state;
    uint8_t clicks;
    int x;
    int y;
};


// Mouse movement
struct LX_MMotion
{
    uint32_t wid;
    bool state[LX_MBUTTONS];
    int x;
    int y;
    int xrel;
    int yrel;
};


// Mouse wheel
struct LX_MWheel
{
    uint32_t wid;
    int x;
    int y;
};

// Keyboard

LX_KeyCode getKeyCodeFrom(LX_ScanCode scancode);
LX_ScanCode getScanCodeFrom(LX_KeyCode keycode);

UTF8string stringOfScanCode(LX_ScanCode scancode);
UTF8string stringOfKeyCode(LX_KeyCode keycode);


// Gamepad

UTF8string stringOfButton(LX_GamepadButton button);
UTF8string stringOfButton(uint8_t button);

UTF8string stringOfAxis(LX_GamepadAxis axis);
UTF8string stringOfAxis(uint8_t axis);


// Event handling

class LX_EventHandler
{
    LX_EventData event;

    LX_EventHandler(const LX_EventHandler&);

public:

    LX_EventHandler();

    bool pollEvent();
    bool waitEvent();
    bool waitEventTimeout(int timeout);

    bool pushEvent(LX_EventData& ev);
    bool pushUserEvent(LX_UserEvent& uevent);

    LX_EventType getEventType();
    LX_KeyCode getKeyCode();
    LX_ScanCode getScanCode();
    LX_GamepadID getGamepadID();

    const LX_GAxis getAxis();
    const LX_GButton getButton();

    const LX_MButton getMouseButton();
    const LX_MMotion getMouseMotion();
    const LX_MWheel getMouseWheel();

    ~LX_EventHandler() = default;
};

};

#endif // LX_EVENT_HPP_INCLUDED
