
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
};

namespace LX_EventHandler
{

bool pollEvent(LX_Event& event)
{
    return SDL_PollEvent(&event) == 1;
}

bool waitEvent(LX_Event& event)
{
    return SDL_WaitEvent(&event) == 1;
}

bool waitEventTimeout(LX_Event& event, int timeout)
{
    return SDL_WaitEventTimeout(&event,timeout) == 1;
}

bool pushEvent(LX_Event& event)
{
    return SDL_PushEvent(&event) == 1;
}

bool pushUserEvent(LX_UserEvent& uevent)
{
    if(utype == -1)
    {
        if((utype = SDL_RegisterEvents(1)) == static_cast<uint32_t>(-1))
            return false;
    }

    LX_Event ev;
    SDL_zero(ev);

    uevent.type = utype;
    ev.type = SDL_USEREVENT;
    ev.user = uevent;

    return pushEvent(ev);
}

LX_KeyCode getKeyCode(LX_Event& event)
{
    return event.key.keysym.sym;
}

LX_ScanCode getScanCode(LX_Event& event)
{
    return event.key.keysym.scancode;
}

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

};
