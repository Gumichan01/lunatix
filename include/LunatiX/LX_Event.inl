
/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    https://gumichan01.github.io/
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/*
*   This file describes every constant values usable by the user (LX_Event)
*/

#include <SDL2/SDL_events.h>

namespace LX_Event
{

// Button state (keyboard, mouse, gamepad)
const uint8_t LX_BUTTON_PRESSED  = 1;
const uint8_t LX_BUTTON_RELEASED = 0;

// Gamepad buttons
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

// Gamepad axis
const LX_GamepadAxis LX_AXIS_INVALID      = SDL_CONTROLLER_AXIS_INVALID;
const LX_GamepadAxis LX_AXIS_LEFTX        = SDL_CONTROLLER_AXIS_LEFTX;
const LX_GamepadAxis LX_AXIS_LEFTY        = SDL_CONTROLLER_AXIS_LEFTY;
const LX_GamepadAxis LX_AXIS_RIGHTX       = SDL_CONTROLLER_AXIS_RIGHTX;
const LX_GamepadAxis LX_AXIS_RIGHTY       = SDL_CONTROLLER_AXIS_RIGHTY;
const LX_GamepadAxis LX_AXIS_TRIGGERLEFT  = SDL_CONTROLLER_AXIS_TRIGGERLEFT;
const LX_GamepadAxis LX_AXIS_TRIGGERRIGHT = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
const LX_GamepadAxis LX_AXIS_MAX          = SDL_CONTROLLER_AXIS_MAX;

};
