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

#include <SDL2/SDL_events.h>

/// @todo (#5#) LX_EventHandler: Full implementation
/// @todo (#5#) LX_EventHandler: Documentation

namespace LX_EventHandler
{
using LX_Event = SDL_Event;             /* Event                        */
using LX_UserEvent = SDL_UserEvent;     /* User-defined event           */
using LX_KeyCode = SDL_Keycode;         /* Virtual key representation   */
using LX_ScanCode = SDL_Scancode;       /* Physical key representation  */

bool pollEvent(LX_Event& event);
bool waitEvent(LX_Event& event);
bool waitEventTimeout(LX_Event& event, int timeout);

bool pushEvent(LX_Event& event);
bool pushUserEvent(LX_UserEvent& uevent);

LX_KeyCode getKeyCode(LX_Event& event);
LX_ScanCode getScanCode(LX_Event& event);

LX_KeyCode getKeyCodeFromScanCode(LX_ScanCode scancode);
LX_ScanCode getScanCodeFromKeyCode(LX_KeyCode keycode);

/// @todo (#2#) LX_EventHandler: Get keypad and mouse buttons
/// @todo (#5#) LX_EventHandler: Get gamepad button (joystick and game controller)

};

#endif // LX_EVENT_HPP_INCLUDED
