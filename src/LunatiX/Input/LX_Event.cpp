
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
*    @file LX_Event.cpp
*    @brief The Implementation of the event odule
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*
*/

#include <LunatiX/LX_Event.hpp>


namespace
{
// Type of the user event
uint32_t utype = -1;

inline LX_Event::LX_MouseButton toMouseButton(uint8_t button)
{
    LX_Event::LX_MouseButton m;

    switch(button)
    {
    case SDL_BUTTON_LEFT:
        m = LX_Event::LX_MOUSE_LBUTTON;
        break;

    case SDL_BUTTON_MIDDLE:
        m = LX_Event::LX_MOUSE_MBUTTON;
        break;

    case SDL_BUTTON_RIGHT:
        m = LX_Event::LX_MOUSE_RBUTTON;
        break;

    case SDL_BUTTON_X1:
        m = LX_Event::LX_MOUSE_X1;
        break;

    case SDL_BUTTON_X2:
        m = LX_Event::LX_MOUSE_X2;
        break;
    }

    return m;
}

};

namespace LX_Event
{
// LX_Event

LX_EventHandler::LX_EventHandler()
{
    SDL_zero(event);
}


bool LX_EventHandler::pollEvent()
{
    return SDL_PollEvent(&event) == 1;
}

bool LX_EventHandler::waitEvent()
{
    return SDL_WaitEvent(&event) == 1;
}

bool LX_EventHandler::waitEventTimeout(int timeout)
{
    return SDL_WaitEventTimeout(&event,timeout) == 1;
}

bool LX_EventHandler::pushEvent(LX_EventData& ev)
{
    return SDL_PushEvent(&ev) == 1;
}


bool LX_EventHandler::pushUserEvent(LX_UserEvent& uevent)
{
    if(utype == -1)
    {
        if((utype = SDL_RegisterEvents(1)) == static_cast<uint32_t>(-1))
            return false;
    }

    LX_EventData ev;
    SDL_zero(ev);

    uevent.type = utype;
    ev.type = SDL_USEREVENT;
    ev.user = uevent;

    return pushEvent(ev);
}

LX_EventType LX_EventHandler::getEventType()
{
    return event.type;
}

LX_KeyCode LX_EventHandler::getKeyCode()
{
    return event.key.keysym.sym;
}


LX_ScanCode LX_EventHandler::getScanCode()
{
    return event.key.keysym.scancode;
}

LX_GamepadID LX_EventHandler::getGamepadID()
{
    LX_GamepadID id;

    switch(event.type)
    {
    case SDL_CONTROLLERBUTTONDOWN:
    case SDL_CONTROLLERBUTTONUP:
        id = event.cbutton.which;
        break;

    case SDL_CONTROLLERAXISMOTION:
        id = event.caxis.which;
        break;

    case SDL_CONTROLLERDEVICEADDED:
    case SDL_CONTROLLERDEVICEREMOVED:
    case SDL_CONTROLLERDEVICEREMAPPED:
        id = event.cdevice.which;
        break;

    default:
        id = -1;
        break;
    }

    return id;
}

const LX_GAxis LX_EventHandler::getAxis()
{
    const SDL_ControllerAxisEvent ax = event.caxis;
    const LX_GAxis gax = {ax.which, static_cast<LX_GamepadAxis>(ax.axis), ax.value};
    return gax;
}

const LX_GButton LX_EventHandler::getButton()
{
    const SDL_ControllerButtonEvent bu = event.cbutton;
    const LX_GButton gbutton = {bu.which, static_cast<LX_GamepadButton>(bu.button), bu.state};
    return gbutton;
}

const LX_MButton LX_EventHandler::getMouseButton()
{
    const SDL_MouseButtonEvent mb = event.button;
    LX_MouseButton b = toMouseButton(mb.button);
    const LX_MButton mbutton = {b, mb.state, mb.clicks, mb.x, mb.y};
    return mbutton;
}


// Keyboard

LX_KeyCode getKeyCodeFrom(LX_ScanCode scancode)
{
    return SDL_GetKeyFromScancode(scancode);
}

LX_ScanCode getScanCodeFrom(LX_KeyCode keycode)
{
    return SDL_GetScancodeFromKey(keycode);
}

UTF8string stringOfScanCode(LX_ScanCode scancode)
{
    return UTF8string(SDL_GetScancodeName(scancode));
}

UTF8string stringOfKeyCode(LX_KeyCode keycode)
{
    return UTF8string(SDL_GetKeyName(keycode));
}


// Gamepad

UTF8string stringOfButton(LX_GamepadButton button)
{
    const char * s = SDL_GameControllerGetStringForButton(button);
    return UTF8string(s == nullptr ? "null" : s);
}

UTF8string stringOfButton(uint8_t button)
{
    return stringOfButton(static_cast<LX_GamepadButton>(button));
}


UTF8string stringOfAxis(LX_GamepadAxis axis)
{
    const char * s = SDL_GameControllerGetStringForAxis(axis);
    return UTF8string(s == nullptr ? "null" : s);
}

UTF8string stringOfAxis(uint8_t axis)
{
    return stringOfAxis(static_cast<LX_GamepadAxis>(axis));
}

};
