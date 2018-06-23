
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

/**
*   @file LX_Event.cpp
*   @brief The Implementation of the event odule
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <LunatiX/LX_Event.hpp>
#include <SDL2/SDL_events.h>

namespace
{

inline constexpr LX_Event::LX_State u8st( uint8_t s )
{
    return static_cast<LX_Event::LX_State>( s );
}

LX_Event::LX_MouseButton toMouseButton( uint8_t button ) noexcept
{
    LX_Event::LX_MouseButton m;

    switch ( button )
    {
    case SDL_BUTTON_LEFT:
        m = LX_Event::LX_MouseButton::LBUTTON;
        break;

    case SDL_BUTTON_MIDDLE:
        m = LX_Event::LX_MouseButton::MBUTTON;
        break;

    case SDL_BUTTON_RIGHT:
        m = LX_Event::LX_MouseButton::RBUTTON;
        break;

    case SDL_BUTTON_X1:
        m = LX_Event::LX_MouseButton::X1;
        break;

    case SDL_BUTTON_X2:
        m = LX_Event::LX_MouseButton::X2;
        break;

    default:
        m = LX_Event::LX_MouseButton::UNKNWON;
        break;
    }

    return m;
}


/*
    Test if a mouse button is activated

    - st is the state of the mouse
    - b is the button state
*/
inline constexpr bool hasState( uint32_t st, uint8_t b )
{
    return ( st & static_cast<uint32_t>( b ) ) != 0;
}

void fillButtonState( bool * state, uint32_t st ) noexcept
{
    const uint8_t LBUTTON  = LX_MBIndex( LX_Event::LX_MouseButton::LBUTTON );
    const uint8_t MBUTTON  = LX_MBIndex( LX_Event::LX_MouseButton::MBUTTON );
    const uint8_t RBUTTON  = LX_MBIndex( LX_Event::LX_MouseButton::RBUTTON );
    const uint8_t X1BUTTON = LX_MBIndex( LX_Event::LX_MouseButton::X1 );
    const uint8_t X2BUTTON = LX_MBIndex( LX_Event::LX_MouseButton::X2 );

    if ( hasState( st, LBUTTON ) )
        state[LBUTTON] = true;

    if ( hasState( st, MBUTTON ) )
        state[MBUTTON] = true;

    if ( hasState( st, RBUTTON ) )
        state[RBUTTON] = true;

    if ( hasState( st, X1BUTTON ) )
        state[X1BUTTON] = true;

    if ( hasState( st, X2BUTTON ) )
        state[X2BUTTON] = true;
}

LX_Event::LX_WinEventType toWinEvent( uint8_t id ) noexcept
{
    LX_Event::LX_WinEventType wid;

    switch ( id )
    {
    case SDL_WINDOWEVENT_SHOWN:
        wid = LX_Event::LX_WinEventType::WIN_SHOWN;
        break;

    case SDL_WINDOWEVENT_HIDDEN:
        wid = LX_Event::LX_WinEventType::WIN_HIDDEN;
        break;

    case SDL_WINDOWEVENT_EXPOSED:
        wid = LX_Event::LX_WinEventType::WIN_EXPOSED;
        break;

    case SDL_WINDOWEVENT_MOVED:
        wid = LX_Event::LX_WinEventType::WIN_MOVED;
        break;

    case SDL_WINDOWEVENT_RESIZED:
        wid = LX_Event::LX_WinEventType::WIN_RESIZED;
        break;

    case SDL_WINDOWEVENT_SIZE_CHANGED:
        wid = LX_Event::LX_WinEventType::WIN_SIZE_CHANGED;
        break;

    case SDL_WINDOWEVENT_MINIMIZED:
        wid = LX_Event::LX_WinEventType::WIN_MINIMIZED;
        break;

    case SDL_WINDOWEVENT_MAXIMIZED:
        wid = LX_Event::LX_WinEventType::WIN_MAXIMIZED;
        break;

    case SDL_WINDOWEVENT_RESTORED:
        wid = LX_Event::LX_WinEventType::WIN_RESTORED;
        break;

    case SDL_WINDOWEVENT_ENTER:
        wid = LX_Event::LX_WinEventType::WIN_ENTER;
        break;

    case SDL_WINDOWEVENT_LEAVE:
        wid = LX_Event::LX_WinEventType::WIN_LEAVE;
        break;

    case SDL_WINDOWEVENT_FOCUS_GAINED:
        wid = LX_Event::LX_WinEventType::WIN_FOCUS_GAINED;
        break;

    case SDL_WINDOWEVENT_FOCUS_LOST:
        wid = LX_Event::LX_WinEventType::WIN_FOCUS_LOST;
        break;

    case SDL_WINDOWEVENT_CLOSE:
        wid = LX_Event::LX_WinEventType::WIN_CLOSE;
        break;

    default:
        wid = LX_Event::LX_WinEventType::WIN_NONE;
        break;
    }

    return wid;
}


void eventState( const LX_Event::LX_EventType ty, bool process ) noexcept
{
    /*
        0 → do nothing
        1 → disable gamepad (LX_CONTROLLERDEVICEADDED)
        2 → disable gamepad (LX_CONTROLLERDEVICEREMOVED)
    */
    uint32_t sdl_ev_ty = 0;
    int state = process ? SDL_ENABLE : SDL_DISABLE;

    switch ( ty )
    {
    case LX_Event::LX_EventType::QUIT:
        sdl_ev_ty = SDL_QUIT;
        break;

    case LX_Event::LX_EventType::WINDOWEVENT:
        sdl_ev_ty = SDL_WINDOWEVENT;
        break;

    case LX_Event::LX_EventType::KEYDOWN:
        sdl_ev_ty = SDL_KEYDOWN;
        break;

    case LX_Event::LX_EventType::KEYUP:
        sdl_ev_ty = SDL_KEYUP;
        break;

    case LX_Event::LX_EventType::MOUSEMOTION:
        sdl_ev_ty = SDL_MOUSEMOTION;
        break;

    case LX_Event::LX_EventType::MOUSEBUTTONDOWN:
        sdl_ev_ty = SDL_MOUSEBUTTONDOWN;
        break;

    case LX_Event::LX_EventType::MOUSEBUTTONUP:
        sdl_ev_ty = SDL_MOUSEBUTTONUP;
        break;

    case LX_Event::LX_EventType::MOUSEWHEEL:
        sdl_ev_ty = SDL_MOUSEWHEEL;
        break;

    case LX_Event::LX_EventType::CONTROLLERAXISMOTION:
        sdl_ev_ty = SDL_CONTROLLERAXISMOTION;
        break;

    case LX_Event::LX_EventType::CONTROLLERBUTTONDOWN:
        sdl_ev_ty = SDL_CONTROLLERBUTTONDOWN;
        break;

    case LX_Event::LX_EventType::CONTROLLERBUTTONUP:
        sdl_ev_ty = SDL_CONTROLLERBUTTONUP;
        break;

    case LX_Event::LX_EventType::CONTROLLERDEVICEADDED:
        sdl_ev_ty = 1;
        break;

    case LX_Event::LX_EventType::CONTROLLERDEVICEREMOVED:
        sdl_ev_ty = 2;
        break;

    case LX_Event::LX_EventType::DROPFILE:
        sdl_ev_ty = SDL_DROPFILE;
        break;

    default:
        break;
    }

    if ( sdl_ev_ty == 1 )
    {
        SDL_EventState( SDL_JOYDEVICEADDED, state );
        SDL_EventState( SDL_CONTROLLERDEVICEADDED, state );
    }
    else if ( sdl_ev_ty == 2 )
    {
        SDL_EventState( SDL_JOYDEVICEREMOVED, state );
        SDL_EventState( SDL_CONTROLLERDEVICEREMOVED, state );
    }
    else if ( sdl_ev_ty != 0 )
    {
        SDL_EventState( sdl_ev_ty, state );
    }
}

}

namespace LX_Event
{

const uint32_t UTYPE_ERR = static_cast<uint32_t>( -1 );
// Type of the user event
uint32_t utype = UTYPE_ERR;

// LX_Event

LX_EventHandler::LX_EventHandler() noexcept: event( new SDL_Event() )
{
    SDL_zerop( event );
}

LX_EventHandler::~LX_EventHandler()
{
    delete event;
}


bool LX_EventHandler::pollEvent() noexcept
{
    return SDL_PollEvent( event ) == 1;
}


bool LX_EventHandler::waitEvent() noexcept
{
    return SDL_WaitEvent( event ) == 1;
}


bool LX_EventHandler::waitEventTimeout( int timeout ) noexcept
{
    return SDL_WaitEventTimeout( event, timeout ) == 1;
}


bool LX_EventHandler::pushUserEvent( LX_UserEvent& uevent ) noexcept
{
    if ( ( utype = SDL_RegisterEvents( 1 ) ) == UTYPE_ERR )
        return false;

    SDL_Event user_event;
    SDL_zero( user_event );

    uevent.type = utype;
    user_event.type = SDL_USEREVENT;
    user_event.user = {uevent.type, 0, uevent.wid, uevent.code, uevent.data1, uevent.data2};

    return SDL_PushEvent( &user_event ) == 1;
}


void LX_EventHandler::processEvent( const LX_EventType ty ) noexcept
{
    eventState( ty, true );
}


void LX_EventHandler::ignoreEvent( const LX_EventType ty ) noexcept
{
    eventState( ty, false );
}


uint32_t LX_EventHandler::getWindowID() const noexcept
{
    uint32_t id = 0;
    const SDL_Event& EV = ( *event );

    switch ( EV.type )
    {
    case SDL_WINDOWEVENT:
        id = EV.window.windowID;
        break;

    case SDL_KEYDOWN:
    case SDL_KEYUP:
        id = EV.key.windowID;
        break;

    case SDL_TEXTEDITING:
        id = EV.edit.windowID;
        break;

    case SDL_TEXTINPUT:
        id = EV.text.windowID;
        break;

    case SDL_MOUSEMOTION:
        id = EV.motion.windowID;
        break;

    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        id = EV.button.windowID;
        break;

    case SDL_MOUSEWHEEL:
        id = EV.wheel.windowID;
        break;

    case SDL_USEREVENT:
        id = EV.user.windowID;
        break;

    default:
        break;
    }

    return id;
}


LX_EventType LX_EventHandler::getEventType() const noexcept
{
    LX_EventType ty;
    const SDL_Event& EV = ( *event );

    switch ( EV.type )
    {
    case SDL_QUIT:
        ty = LX_EventType::QUIT;
        break;
    case SDL_WINDOWEVENT:
        ty = LX_EventType::WINDOWEVENT;
        break;

    /* Keyboard events */
    case SDL_KEYDOWN:
        ty = LX_EventType::KEYDOWN;
        break;
    case SDL_KEYUP:
        ty = LX_EventType::KEYUP;
        break;
    case SDL_TEXTEDITING:
        ty = LX_EventType::TEXTEDITING;
        break;
    case SDL_TEXTINPUT:
        ty = LX_EventType::TEXTINPUT;
        break;

    /* Mouse events */
    case SDL_MOUSEMOTION:
        ty = LX_EventType::MOUSEMOTION;
        break;
    case SDL_MOUSEBUTTONDOWN:
        ty = LX_EventType::MOUSEBUTTONDOWN;
        break;
    case SDL_MOUSEBUTTONUP:
        ty = LX_EventType::MOUSEBUTTONUP;
        break;
    case SDL_MOUSEWHEEL:
        ty = LX_EventType::MOUSEWHEEL;
        break;

    /* Game controller events */
    case SDL_CONTROLLERAXISMOTION:
        ty = LX_EventType::CONTROLLERAXISMOTION;
        break;
    case SDL_CONTROLLERBUTTONDOWN:
        ty = LX_EventType::CONTROLLERBUTTONDOWN;
        break;
    case SDL_CONTROLLERBUTTONUP:
        ty = LX_EventType::CONTROLLERBUTTONUP;
        break;

    case SDL_CONTROLLERDEVICEADDED:
        ty = LX_EventType::CONTROLLERDEVICEADDED;
        break;

    case SDL_CONTROLLERDEVICEREMOVED:
        ty = LX_EventType::CONTROLLERDEVICEREMOVED;
        break;

    /* Drag and drop events */
    case SDL_DROPFILE:
        ty = LX_EventType::DROPFILE;
        break;
    case SDL_USEREVENT:
        ty = LX_EventType::USEREVENT;
        break;

    default:
        ty = LX_EventType::UNKNOWN;
        break;
    }

    return ty;
}


const LX_KeyboardState LX_EventHandler::getKeyboardState() noexcept
{
    int sz;
    LX_KeyboardState ks = {SDL_GetKeyboardState( &sz ), sz};
    return ks;
}

LX_KeyCode LX_EventHandler::getKeyCode() const noexcept
{
    return ( *event ).key.keysym.sym;
}

LX_ScanCode LX_EventHandler::getScanCode() const noexcept
{
    return ( *event ).key.keysym.scancode;
}

LX_GamepadID LX_EventHandler::getGamepadID() const noexcept
{
    LX_GamepadID id;
    const SDL_Event& EVENT = ( *event );

    switch ( EVENT.type )
    {
    case SDL_CONTROLLERBUTTONDOWN:
    case SDL_CONTROLLERBUTTONUP:
        id = EVENT.cbutton.which;
        break;

    case SDL_CONTROLLERAXISMOTION:
        id = EVENT.caxis.which;
        break;

    case SDL_CONTROLLERDEVICEADDED:
    case SDL_CONTROLLERDEVICEREMOVED:
    case SDL_CONTROLLERDEVICEREMAPPED:
        id = EVENT.cdevice.which;
        break;

    case SDL_JOYDEVICEADDED:
    case SDL_JOYDEVICEREMOVED:
        id = EVENT.jdevice.which;
        break;

    default:
        id = -1;
        break;
    }

    return id;
}


const LX_GAxis LX_EventHandler::getAxis() const noexcept
{
    const SDL_ControllerAxisEvent AX = ( *event ).caxis;
    const LX_GAxis GAX = {AX.which, static_cast<LX_GamepadAxis>( AX.axis ), AX.value};
    return GAX;
}

const LX_GButton LX_EventHandler::getButton() const noexcept
{
    const SDL_ControllerButtonEvent BU = ( *event ).cbutton;
    const LX_GButton GBUTTON = {BU.which, static_cast<LX_GamepadButton>( BU.button ), u8st( BU.state )};
    return GBUTTON;
}

const LX_MButton LX_EventHandler::getMouseButton() const noexcept
{
    const SDL_MouseButtonEvent MB = ( *event ).button;
    const LX_MouseButton B = toMouseButton( MB.button );
    const LX_MButton MBUTTON = {MB.windowID, B, u8st( MB.state ), MB.clicks, MB.x, MB.y};
    return MBUTTON;
}

const LX_MMotion LX_EventHandler::getMouseMotion() const noexcept
{
    LX_MMotion mmotion;
    const SDL_MouseMotionEvent MOUSE_MOTION_EVENT = ( *event ).motion;

    for ( int i = 0; i < LX_MBUTTONS; i++ )
    {
        mmotion.state[i] = false;
    }

    fillButtonState( mmotion.state, MOUSE_MOTION_EVENT.state );
    mmotion.wid = MOUSE_MOTION_EVENT.windowID;
    mmotion.x = MOUSE_MOTION_EVENT.x;
    mmotion.y = MOUSE_MOTION_EVENT.y;
    mmotion.xrel = MOUSE_MOTION_EVENT.xrel;
    mmotion.yrel = MOUSE_MOTION_EVENT.yrel;

    return mmotion;
}

const LX_MWheel LX_EventHandler::getMouseWheel() const noexcept
{
    const SDL_MouseWheelEvent MOUSE_WHEEL_EVENT = ( *event ).wheel;
    return LX_MWheel{MOUSE_WHEEL_EVENT.windowID, MOUSE_WHEEL_EVENT.x, MOUSE_WHEEL_EVENT.y};
}

const LX_WEvent LX_EventHandler::getWindowEvent() const noexcept
{
    const SDL_WindowEvent WIN_EVENT = ( *event ).window;
    return LX_WEvent{WIN_EVENT.windowID,
                     toWinEvent( WIN_EVENT.event ), WIN_EVENT.data1,
                     WIN_EVENT.data2
                    };
}

const LX_UserEvent LX_EventHandler::getUserEvent() const noexcept
{
    const SDL_UserEvent USR = ( *event ).user;
    return LX_UserEvent{USR.type, USR.windowID, USR.code, USR.data1, USR.data2};
}

const LX_TextEvent LX_EventHandler::getTextEvent() const noexcept
{
    const SDL_Event EVENT = ( *event );

    if ( EVENT.type == SDL_TEXTINPUT )
    {
        const SDL_TextInputEvent TINPOUT = EVENT.text;
        return LX_TextEvent{TINPOUT.windowID, TINPOUT.text, 0, std::string( TINPOUT.text ).length()};
    }
    else
    {
        const SDL_TextEditingEvent TEDIT = EVENT.edit;
        return LX_TextEvent{TEDIT.windowID, TEDIT.text, TEDIT.start, static_cast<size_t>( TEDIT.length )};
    }
}

const LX_DropEvent LX_EventHandler::getDropEvent() const noexcept
{
    LX_DropEvent drop = {""};
    const SDL_DropEvent DROP_EVENT = ( *event ).drop;

    if ( ( *event ).type == SDL_DROPFILE && DROP_EVENT.file != nullptr )
    {
        drop.file = DROP_EVENT.file;
        SDL_free( DROP_EVENT.file );
    }

    return drop;
}


// Keyboard

LX_KeyCode getKeyCodeFrom( LX_ScanCode scancode ) noexcept
{
    return SDL_GetKeyFromScancode( scancode );
}

LX_ScanCode getScanCodeFrom( LX_KeyCode keycode ) noexcept
{
    return SDL_GetScancodeFromKey( keycode );
}

UTF8string stringOfScanCode( LX_ScanCode scancode ) noexcept
{
    return UTF8string( SDL_GetScancodeName( scancode ) );
}

UTF8string stringOfKeyCode( LX_KeyCode keycode ) noexcept
{
    return UTF8string( SDL_GetKeyName( keycode ) );
}


// Gamepad

UTF8string stringOfButton( LX_GamepadButton button ) noexcept
{
    const char * S = SDL_GameControllerGetStringForButton( static_cast<SDL_GameControllerButton>( button ) );
    return UTF8string( S == nullptr ? "<null>" : S );
}

UTF8string stringOfAxis( LX_GamepadAxis axis ) noexcept
{
    const char * S = SDL_GameControllerGetStringForAxis( static_cast<SDL_GameControllerAxis>( axis ) );
    return UTF8string( S == nullptr ? "<null>" : S );
}

}
