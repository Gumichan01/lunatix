
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
const uint32_t UTYPE_ERR = static_cast<uint32_t>(-1);
// Type of the user event
uint32_t utype = UTYPE_ERR;

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

    default:
        m = LX_Event::LX_MOUSE_UNKNWON;
        break;
    }

    return m;
}

inline void fillButtonState(bool * state, uint32_t st)
{
    if(st & SDL_BUTTON(LX_Event::LX_MOUSE_LBUTTON))
        state[LX_Event::LX_MOUSE_LBUTTON] = true;

    if(st & SDL_BUTTON(LX_Event::LX_MOUSE_MBUTTON))
        state[LX_Event::LX_MOUSE_MBUTTON] = true;

    if(st & SDL_BUTTON(LX_Event::LX_MOUSE_RBUTTON))
        state[LX_Event::LX_MOUSE_RBUTTON] = true;

    if(st & SDL_BUTTON(LX_Event::LX_MOUSE_X1))
        state[LX_Event::LX_MOUSE_X1] = true;

    if(st & SDL_BUTTON(LX_Event::LX_MOUSE_X2))
        state[LX_Event::LX_MOUSE_X2] = true;
}

inline LX_Event::LX_WinEventID toWinEvent(uint8_t id)
{
    LX_Event::LX_WinEventID wid;

    switch (id)
    {
    case SDL_WINDOWEVENT_SHOWN:
        wid = LX_Event::LX_WINEV_SHOWN;
        break;

    case SDL_WINDOWEVENT_HIDDEN:
        wid = LX_Event::LX_WINEV_HIDDEN;
        break;

    case SDL_WINDOWEVENT_EXPOSED:
        wid = LX_Event::LX_WINEV_EXPOSED;
        break;

    case SDL_WINDOWEVENT_MOVED:
        wid = LX_Event::LX_WINEV_MOVED;
        break;

    case SDL_WINDOWEVENT_RESIZED:
        wid = LX_Event::LX_WINEV_RESIZED;
        break;

    case SDL_WINDOWEVENT_SIZE_CHANGED:
        wid = LX_Event::LX_WINEV_SIZE_CHANGED;
        break;

    case SDL_WINDOWEVENT_MINIMIZED:
        wid = LX_Event::LX_WINEV_MINIMIZED;
        break;

    case SDL_WINDOWEVENT_MAXIMIZED:
        wid = LX_Event::LX_WINEV_MAXIMIZED;
        break;

    case SDL_WINDOWEVENT_RESTORED:
        wid = LX_Event::LX_WINEV_RESTORED;
        break;

    case SDL_WINDOWEVENT_ENTER:
        wid = LX_Event::LX_WINEV_ENTER;
        break;

    case SDL_WINDOWEVENT_LEAVE:
        wid = LX_Event::LX_WINEV_LEAVE;
        break;

    case SDL_WINDOWEVENT_FOCUS_GAINED:
        wid = LX_Event::LX_WINEV_FOCUS_GAINED;
        break;

    case SDL_WINDOWEVENT_FOCUS_LOST:
        wid = LX_Event::LX_WINEV_FOCUS_LOST;
        break;

    case SDL_WINDOWEVENT_CLOSE:
        wid = LX_Event::LX_WINEV_CLOSE;
        break;

    default:
        wid = LX_Event::LX_WINEV_NONE;
        break;
    }

    return wid;
}


void eventState(const LX_Event::LX_EventType ty, bool process)
{
    /*
        0 → do nothing
        1 → disable gamepad (LX_CONTROLLERDEVICEADDED)
        2 → disable gamepad (LX_CONTROLLERDEVICEREMOVED)
    */
    uint32_t sdl_ev_ty = 0;
    int state = process ? SDL_ENABLE : SDL_DISABLE;

    switch(ty)
    {
    case LX_Event::LX_QUIT:
        sdl_ev_ty = SDL_QUIT;
        break;

    case LX_Event::LX_WINDOWEVENT:
        sdl_ev_ty = SDL_WINDOWEVENT;
        break;

    case LX_Event::LX_KEYDOWN:
        sdl_ev_ty = SDL_KEYDOWN;
        break;

    case LX_Event::LX_KEYUP:
        sdl_ev_ty = SDL_KEYUP;
        break;

    case LX_Event::LX_MOUSEMOTION:
        sdl_ev_ty = SDL_MOUSEMOTION;
        break;

    case LX_Event::LX_MOUSEBUTTONDOWN:
        sdl_ev_ty = SDL_MOUSEBUTTONDOWN;
        break;

    case LX_Event::LX_MOUSEBUTTONUP:
        sdl_ev_ty = SDL_MOUSEBUTTONUP;
        break;

    case LX_Event::LX_MOUSEWHEEL:
        sdl_ev_ty = SDL_MOUSEWHEEL;
        break;

    case LX_Event::LX_CONTROLLERAXISMOTION:
        sdl_ev_ty = SDL_CONTROLLERAXISMOTION;
        break;

    case LX_Event::LX_CONTROLLERBUTTONDOWN:
        sdl_ev_ty = SDL_CONTROLLERBUTTONDOWN;
        break;

    case LX_Event::LX_CONTROLLERBUTTONUP:
        sdl_ev_ty = SDL_CONTROLLERBUTTONUP;
        break;

    case LX_Event::LX_CONTROLLERDEVICEADDED:
        sdl_ev_ty = 1;
        break;

    case LX_Event::LX_CONTROLLERDEVICEREMOVED:
        sdl_ev_ty = 2;
        break;

    case LX_Event::LX_DROPFILE:
        sdl_ev_ty = SDL_DROPFILE;
        break;

    default:
        break;
    }

    if(sdl_ev_ty == 1)
    {
        SDL_EventState(SDL_JOYDEVICEADDED,state);
        SDL_EventState(SDL_CONTROLLERDEVICEADDED,state);
    }
    else if(sdl_ev_ty == 2)
    {
        SDL_EventState(SDL_JOYDEVICEREMOVED,state);
        SDL_EventState(SDL_CONTROLLERDEVICEREMOVED,state);
    }
    else if(sdl_ev_ty != 0)
    {
        SDL_EventState(sdl_ev_ty,state);
    }
}

};

namespace LX_Event
{
// LX_Event

LX_EventHandler::LX_EventHandler(): event(new SDL_Event())
{
    SDL_zerop(event);
}

LX_EventHandler::~LX_EventHandler()
{
    delete event;
}


bool LX_EventHandler::pollEvent()
{
    return SDL_PollEvent( &(*event) ) == 1;
}


bool LX_EventHandler::waitEvent()
{
    return SDL_WaitEvent( &(*event) ) == 1;
}


bool LX_EventHandler::waitEventTimeout(int timeout)
{
    return SDL_WaitEventTimeout(&(*event), timeout) == 1;
}


bool LX_EventHandler::pushUserEvent(LX_UserEvent& uevent)
{
    if(utype == UTYPE_ERR)
    {
        if((utype = SDL_RegisterEvents(1)) == UTYPE_ERR)
            return false;
    }

    SDL_Event ev;
    SDL_zero(ev);

    uevent.type = utype;
    ev.type = SDL_USEREVENT;
    ev.user = {uevent.type, 0, uevent.wid, uevent.code, uevent.data1, uevent.data2};

    return SDL_PushEvent(&ev) == 1;
}


void LX_EventHandler::processEvent(const LX_EventType ty)
{
    eventState(ty, true);
}


void LX_EventHandler::ignoreEvent(const LX_EventType ty)
{
    eventState(ty, false);
}


uint32_t LX_EventHandler::getWindowID() const
{
    uint32_t id = 0;
    const SDL_Event& ev = (*event);

    switch(ev.type)
    {
    case SDL_WINDOWEVENT:
        id = ev.window.windowID;
        break;

    case SDL_KEYDOWN:
    case SDL_KEYUP:
        id = ev.key.windowID;
        break;

    case SDL_TEXTEDITING:
        id = ev.edit.windowID;
        break;

    case SDL_TEXTINPUT:
        id = ev.text.windowID;
        break;

    case SDL_MOUSEMOTION:
        id = ev.motion.windowID;
        break;

    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        id = ev.button.windowID;
        break;

    case SDL_MOUSEWHEEL:
        id = ev.wheel.windowID;
        break;

    case SDL_USEREVENT:
        id = ev.user.windowID;
        break;

    default:
        break;
    }

    return id;
}


LX_EventType LX_EventHandler::getEventType() const
{
    LX_EventType ty;
    const SDL_Event& ev = (*event);

    switch(ev.type)
    {
    case SDL_QUIT:
        ty = LX_QUIT;
        break;
    case SDL_WINDOWEVENT:
        ty = LX_WINDOWEVENT;
        break;

    /* Keyboard events */
    case SDL_KEYDOWN:
        ty = LX_KEYDOWN;
        break;
    case SDL_KEYUP:
        ty = LX_KEYUP;
        break;
    case SDL_TEXTEDITING:
        ty = LX_TEXTEDITING;
        break;
    case SDL_TEXTINPUT:
        ty = LX_TEXTINPUT;
        break;

    /* Mouse events */
    case SDL_MOUSEMOTION:
        ty = LX_MOUSEMOTION;
        break;
    case SDL_MOUSEBUTTONDOWN:
        ty = LX_MOUSEBUTTONDOWN;
        break;
    case SDL_MOUSEBUTTONUP:
        ty = LX_MOUSEBUTTONUP;
        break;
    case SDL_MOUSEWHEEL:
        ty = LX_MOUSEWHEEL;
        break;

    /* Game controller events */
    case SDL_CONTROLLERAXISMOTION:
        ty = LX_CONTROLLERAXISMOTION;
        break;
    case SDL_CONTROLLERBUTTONDOWN:
        ty = LX_CONTROLLERBUTTONDOWN;
        break;
    case SDL_CONTROLLERBUTTONUP:
        ty = LX_CONTROLLERBUTTONUP;
        break;

    case SDL_CONTROLLERDEVICEADDED:
    /*case SDL_JOYDEVICEADDED:*/
        ty = LX_CONTROLLERDEVICEADDED;
        break;

    case SDL_CONTROLLERDEVICEREMOVED:
    /*case SDL_JOYDEVICEREMOVED:*/
        ty = LX_CONTROLLERDEVICEREMOVED;
        break;

    /* Drag and drop events */
    case SDL_DROPFILE:
        ty = LX_DROPFILE;
        break;
    case SDL_USEREVENT:
        ty = LX_USEREVENT;
        break;

    default:
        ty = LX_UNKNOWN;
        break;
    }

    return ty;
}


const LX_KeyboardState LX_EventHandler::getKeyboardState()
{
    int sz;
    LX_KeyboardState ks = {SDL_GetKeyboardState(&sz),sz};
    return ks;
}


LX_KeyCode LX_EventHandler::getKeyCode() const
{
    return (*event).key.keysym.sym;
}


LX_ScanCode LX_EventHandler::getScanCode() const
{
    return (*event).key.keysym.scancode;
}


LX_GamepadID LX_EventHandler::getGamepadID() const
{
    LX_GamepadID id;
    const SDL_Event& ev = (*event);

    switch(ev.type)
    {
    case SDL_CONTROLLERBUTTONDOWN:
    case SDL_CONTROLLERBUTTONUP:
        id = ev.cbutton.which;
        break;

    case SDL_CONTROLLERAXISMOTION:
        id = ev.caxis.which;
        break;

    case SDL_CONTROLLERDEVICEADDED:
    case SDL_CONTROLLERDEVICEREMOVED:
    case SDL_CONTROLLERDEVICEREMAPPED:
        id = ev.cdevice.which;
        break;

    case SDL_JOYDEVICEADDED:
    case SDL_JOYDEVICEREMOVED:
        id = ev.jdevice.which;
        break;

    default:
        id = -1;
        break;
    }

    return id;
}


const LX_GAxis LX_EventHandler::getAxis() const
{
    const SDL_ControllerAxisEvent ax = (*event).caxis;
    const LX_GAxis gax = {ax.which, static_cast<LX_GamepadAxis>(ax.axis), ax.value};
    return gax;
}


const LX_GButton LX_EventHandler::getButton() const
{
    const SDL_ControllerButtonEvent bu = (*event).cbutton;
    const LX_GButton gbutton = {bu.which, static_cast<LX_GamepadButton>(bu.button), bu.state};
    return gbutton;
}


const LX_MButton LX_EventHandler::getMouseButton() const
{
    const SDL_MouseButtonEvent mb = (*event).button;
    LX_MouseButton b = toMouseButton(mb.button);
    const LX_MButton mbutton = {mb.windowID,b, mb.state, mb.clicks, mb.x, mb.y};
    return mbutton;
}


const LX_MMotion LX_EventHandler::getMouseMotion() const
{
    LX_MMotion mmotion;
    const SDL_MouseMotionEvent mm = (*event).motion;

    for(int i = 0; i < LX_MBUTTONS; i++)
    {
        mmotion.state[i] = false;
    }
    fillButtonState(mmotion.state,mm.state);

    mmotion.wid = mm.windowID;
    mmotion.x = mm.x;
    mmotion.y = mm.y;
    mmotion.xrel = mm.xrel;
    mmotion.yrel = mm.yrel;

    return mmotion;
}

const LX_MWheel LX_EventHandler::getMouseWheel() const
{
    const SDL_MouseWheelEvent mw = (*event).wheel;
    const LX_MWheel mwheel = {mw.windowID, mw.x, mw.y};
    return mwheel;
}


const LX_WEvent LX_EventHandler::getWindowEvent() const
{
    const SDL_WindowEvent winev = (*event).window;
    const LX_WEvent we = {winev.windowID,
                          toWinEvent(winev.event), winev.data1, winev.data2
                         };
    return we;
}


const LX_UserEvent LX_EventHandler::getUserEvent() const
{
    const SDL_UserEvent usr = (*event).user;
    const LX_UserEvent uev = {usr.type, usr.windowID, usr.code, usr.data1, usr.data2};
    return uev;
}


const LX_TextEvent LX_EventHandler::getTextEvent() const
{
    LX_TextEvent t = {0,"",0,0};
    const SDL_Event& ev = (*event);

    if(ev.type == SDL_TEXTINPUT)
    {
        const SDL_TextInputEvent ti = ev.text;
        t = {ti.windowID, ti.text, 0, static_cast<size_t>(std::string(ti.text).length())};
    }
    else
    {
        const SDL_TextEditingEvent te = ev.edit;
        t = {te.windowID, te.text, te.start, static_cast<size_t>(te.length)};
    }

    return t;
}


const LX_DropEvent LX_EventHandler::getDropEvent() const
{
    LX_DropEvent drop = {""};
    const SDL_DropEvent dev = (*event).drop;

    if((*event).type == SDL_DROPFILE && dev.file != nullptr)
    {
        drop.file = dev.file;
        SDL_free(dev.file);
    }

    return drop;
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
    const char * s = SDL_GameControllerGetStringForButton(static_cast<SDL_GameControllerButton>(button));
    return UTF8string(s == nullptr ? "null" : s);
}


UTF8string stringOfAxis(LX_GamepadAxis axis)
{
    const char * s = SDL_GameControllerGetStringForAxis(static_cast<SDL_GameControllerAxis>(axis));
    return UTF8string(s == nullptr ? "null" : s);
}

};
