
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
*   @file Event.cpp
*   @brief The Implementation of the event odule
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/Event.hpp>
#include <SDL2/SDL_events.h>

namespace
{

inline constexpr lx::Event::State u8st( uint8_t s )
{
    return static_cast<lx::Event::State>( s );
}

lx::Event::MouseButton toMouseButton( uint8_t button ) noexcept
{
    lx::Event::MouseButton m;

    switch ( button )
    {
    case SDL_BUTTON_LEFT:
        m = lx::Event::MouseButton::LBUTTON;
        break;

    case SDL_BUTTON_MIDDLE:
        m = lx::Event::MouseButton::MBUTTON;
        break;

    case SDL_BUTTON_RIGHT:
        m = lx::Event::MouseButton::RBUTTON;
        break;

    case SDL_BUTTON_X1:
        m = lx::Event::MouseButton::X1;
        break;

    case SDL_BUTTON_X2:
        m = lx::Event::MouseButton::X2;
        break;

    default:
        m = lx::Event::MouseButton::UNKNWON;
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
    const uint8_t LBUTTON  = MBIndex( lx::Event::MouseButton::LBUTTON );
    const uint8_t MBUTTON  = MBIndex( lx::Event::MouseButton::MBUTTON );
    const uint8_t RBUTTON  = MBIndex( lx::Event::MouseButton::RBUTTON );
    const uint8_t X1BUTTON = MBIndex( lx::Event::MouseButton::X1 );
    const uint8_t X2BUTTON = MBIndex( lx::Event::MouseButton::X2 );

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

lx::Event::WinEventType toWinEvent( uint8_t id ) noexcept
{
    lx::Event::WinEventType wid;

    switch ( id )
    {
    case SDL_WINDOWEVENT_SHOWN:
        wid = lx::Event::WinEventType::WIN_SHOWN;
        break;

    case SDL_WINDOWEVENT_HIDDEN:
        wid = lx::Event::WinEventType::WIN_HIDDEN;
        break;

    case SDL_WINDOWEVENT_EXPOSED:
        wid = lx::Event::WinEventType::WIN_EXPOSED;
        break;

    case SDL_WINDOWEVENT_MOVED:
        wid = lx::Event::WinEventType::WIN_MOVED;
        break;

    case SDL_WINDOWEVENT_RESIZED:
        wid = lx::Event::WinEventType::WIN_RESIZED;
        break;

    case SDL_WINDOWEVENT_SIZE_CHANGED:
        wid = lx::Event::WinEventType::WIN_SIZE_CHANGED;
        break;

    case SDL_WINDOWEVENT_MINIMIZED:
        wid = lx::Event::WinEventType::WIN_MINIMIZED;
        break;

    case SDL_WINDOWEVENT_MAXIMIZED:
        wid = lx::Event::WinEventType::WIN_MAXIMIZED;
        break;

    case SDL_WINDOWEVENT_RESTORED:
        wid = lx::Event::WinEventType::WIN_RESTORED;
        break;

    case SDL_WINDOWEVENT_ENTER:
        wid = lx::Event::WinEventType::WIN_ENTER;
        break;

    case SDL_WINDOWEVENT_LEAVE:
        wid = lx::Event::WinEventType::WIN_LEAVE;
        break;

    case SDL_WINDOWEVENT_FOCUS_GAINED:
        wid = lx::Event::WinEventType::WIN_FOCUS_GAINED;
        break;

    case SDL_WINDOWEVENT_FOCUS_LOST:
        wid = lx::Event::WinEventType::WIN_FOCUS_LOST;
        break;

    case SDL_WINDOWEVENT_CLOSE:
        wid = lx::Event::WinEventType::WIN_CLOSE;
        break;

    default:
        wid = lx::Event::WinEventType::WIN_NONE;
        break;
    }

    return wid;
}


void eventState( const lx::Event::EventType ty, bool process ) noexcept
{
    /*
        0 → do nothing
        1 → disable gamepad (CONTROLLERDEVICEADDED)
        2 → disable gamepad (CONTROLLERDEVICEREMOVED)
    */
    uint32_t sdl_ev_ty = 0;
    int state = process ? SDL_ENABLE : SDL_DISABLE;

    switch ( ty )
    {
    case lx::Event::EventType::QUIT:
        sdl_ev_ty = SDL_QUIT;
        break;

    case lx::Event::EventType::WINDOWEVENT:
        sdl_ev_ty = SDL_WINDOWEVENT;
        break;

    case lx::Event::EventType::KEYDOWN:
        sdl_ev_ty = SDL_KEYDOWN;
        break;

    case lx::Event::EventType::KEYUP:
        sdl_ev_ty = SDL_KEYUP;
        break;

    case lx::Event::EventType::MOUSEMOTION:
        sdl_ev_ty = SDL_MOUSEMOTION;
        break;

    case lx::Event::EventType::MOUSEBUTTONDOWN:
        sdl_ev_ty = SDL_MOUSEBUTTONDOWN;
        break;

    case lx::Event::EventType::MOUSEBUTTONUP:
        sdl_ev_ty = SDL_MOUSEBUTTONUP;
        break;

    case lx::Event::EventType::MOUSEWHEEL:
        sdl_ev_ty = SDL_MOUSEWHEEL;
        break;

    case lx::Event::EventType::CONTROLLERAXISMOTION:
        sdl_ev_ty = SDL_CONTROLLERAXISMOTION;
        break;

    case lx::Event::EventType::CONTROLLERBUTTONDOWN:
        sdl_ev_ty = SDL_CONTROLLERBUTTONDOWN;
        break;

    case lx::Event::EventType::CONTROLLERBUTTONUP:
        sdl_ev_ty = SDL_CONTROLLERBUTTONUP;
        break;

    case lx::Event::EventType::CONTROLLERDEVICEADDED:
        sdl_ev_ty = 1;
        break;

    case lx::Event::EventType::CONTROLLERDEVICEREMOVED:
        sdl_ev_ty = 2;
        break;

    case lx::Event::EventType::DROPFILE:
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

namespace lx
{

namespace Event
{

const uint32_t UTYPE_ERR = static_cast<uint32_t>( -1 );
// Type of the user event
uint32_t utype = UTYPE_ERR;

// Event

EventHandler::EventHandler() noexcept: event( new SDL_Event() )
{
    SDL_zerop( event );
}

EventHandler::~EventHandler()
{
    delete event;
}


bool EventHandler::pollEvent() noexcept
{
    return SDL_PollEvent( event ) == 1;
}


bool EventHandler::waitEvent() noexcept
{
    return SDL_WaitEvent( event ) == 1;
}


bool EventHandler::waitEventTimeout( int timeout ) noexcept
{
    return SDL_WaitEventTimeout( event, timeout ) == 1;
}


bool EventHandler::pushUserEvent( UserEvent& uevent ) noexcept
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


void EventHandler::processEvent( const EventType ty ) noexcept
{
    eventState( ty, true );
}


void EventHandler::ignoreEvent( const EventType ty ) noexcept
{
    eventState( ty, false );
}


uint32_t EventHandler::getWindowID() const noexcept
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


EventType EventHandler::getEventType() const noexcept
{
    EventType ty;
    const SDL_Event& EV = ( *event );

    switch ( EV.type )
    {
    case SDL_QUIT:
        ty = EventType::QUIT;
        break;
    case SDL_WINDOWEVENT:
        ty = EventType::WINDOWEVENT;
        break;

    /* Keyboard events */
    case SDL_KEYDOWN:
        ty = EventType::KEYDOWN;
        break;
    case SDL_KEYUP:
        ty = EventType::KEYUP;
        break;
    case SDL_TEXTEDITING:
        ty = EventType::TEXTEDITING;
        break;
    case SDL_TEXTINPUT:
        ty = EventType::TEXTINPUT;
        break;

    /* Mouse events */
    case SDL_MOUSEMOTION:
        ty = EventType::MOUSEMOTION;
        break;
    case SDL_MOUSEBUTTONDOWN:
        ty = EventType::MOUSEBUTTONDOWN;
        break;
    case SDL_MOUSEBUTTONUP:
        ty = EventType::MOUSEBUTTONUP;
        break;
    case SDL_MOUSEWHEEL:
        ty = EventType::MOUSEWHEEL;
        break;

    /* Game controller events */
    case SDL_CONTROLLERAXISMOTION:
        ty = EventType::CONTROLLERAXISMOTION;
        break;
    case SDL_CONTROLLERBUTTONDOWN:
        ty = EventType::CONTROLLERBUTTONDOWN;
        break;
    case SDL_CONTROLLERBUTTONUP:
        ty = EventType::CONTROLLERBUTTONUP;
        break;

    case SDL_CONTROLLERDEVICEADDED:
        ty = EventType::CONTROLLERDEVICEADDED;
        break;

    case SDL_CONTROLLERDEVICEREMOVED:
        ty = EventType::CONTROLLERDEVICEREMOVED;
        break;

    /* Drag and drop events */
    case SDL_DROPFILE:
        ty = EventType::DROPFILE;
        break;
    case SDL_USEREVENT:
        ty = EventType::USEREVENT;
        break;

    default:
        ty = EventType::UNKNOWN;
        break;
    }

    return ty;
}


const KeyboardState EventHandler::getKeyboardState() noexcept
{
    int sz;
    KeyboardState ks = { SDL_GetKeyboardState( &sz ), sz };
    return ks;
}

KeyCode EventHandler::getKeyCode() const noexcept
{
    return ( *event ).key.keysym.sym;
}

ScanCode EventHandler::getScanCode() const noexcept
{
    return ( *event ).key.keysym.scancode;
}

GamepadID EventHandler::getGamepadID() const noexcept
{
    GamepadID id;
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


const GAxis EventHandler::getAxis() const noexcept
{
    const SDL_ControllerAxisEvent AX = ( *event ).caxis;
    const GAxis GAX = { AX.which, static_cast<GamepadAxis>( AX.axis ), AX.value };
    return GAX;
}

const GButton EventHandler::getButton() const noexcept
{
    const SDL_ControllerButtonEvent BU = ( *event ).cbutton;
    const GButton GBUTTON = { BU.which, static_cast<GamepadButton>( BU.button ), u8st( BU.state ) };
    return GBUTTON;
}

const MButton EventHandler::getMouseButton() const noexcept
{
    const SDL_MouseButtonEvent MB = ( *event ).button;
    const MouseButton B = toMouseButton( MB.button );
    const MButton MBUTTON = { MB.windowID, B, u8st( MB.state ), MB.clicks, MB.x, MB.y };
    return MBUTTON;
}

const MMotion EventHandler::getMouseMotion() const noexcept
{
    MMotion mmotion;
    const SDL_MouseMotionEvent MOUSE_MOTION_EVENT = ( *event ).motion;

    for ( int i = 0; i < MBUTTONS; i++ )
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

const MWheel EventHandler::getMouseWheel() const noexcept
{
    const SDL_MouseWheelEvent MOUSE_WHEEL_EVENT = ( *event ).wheel;
    return MWheel{MOUSE_WHEEL_EVENT.windowID, MOUSE_WHEEL_EVENT.x, MOUSE_WHEEL_EVENT.y};
}

const WEvent EventHandler::getWindowEvent() const noexcept
{
    const SDL_WindowEvent WIN_EVENT = ( *event ).window;
    return WEvent{ WIN_EVENT.windowID,
                   toWinEvent( WIN_EVENT.event ), WIN_EVENT.data1,
                   WIN_EVENT.data2
                 };
}

const UserEvent EventHandler::getUserEvent() const noexcept
{
    const SDL_UserEvent USR = ( *event ).user;
    return UserEvent{USR.type, USR.windowID, USR.code, USR.data1, USR.data2};
}

const TextEvent EventHandler::getTextEvent() const noexcept
{
    const SDL_Event EVENT = ( *event );

    if ( EVENT.type == SDL_TEXTINPUT )
    {
        const SDL_TextInputEvent TINPOUT = EVENT.text;
        return TextEvent{ TINPOUT.windowID, TINPOUT.text, 0, std::string( TINPOUT.text ).length() };
    }
    else
    {
        const SDL_TextEditingEvent TEDIT = EVENT.edit;
        return TextEvent{ TEDIT.windowID, TEDIT.text, TEDIT.start, static_cast<size_t>( TEDIT.length ) };
    }
}

const DropEvent EventHandler::getDropEvent() const noexcept
{
    DropEvent drop = {""};
    const SDL_DropEvent DROP_EVENT = ( *event ).drop;

    if ( ( *event ).type == SDL_DROPFILE && DROP_EVENT.file != nullptr )
    {
        drop.file = DROP_EVENT.file;
        SDL_free( DROP_EVENT.file );
    }

    return drop;
}


// Keyboard

KeyCode getKeyCodeFrom( ScanCode scancode ) noexcept
{
    return SDL_GetKeyFromScancode( scancode );
}

ScanCode getScanCodeFrom( KeyCode keycode ) noexcept
{
    return SDL_GetScancodeFromKey( keycode );
}

UTF8string stringOfScanCode( ScanCode scancode ) noexcept
{
    return UTF8string( SDL_GetScancodeName( scancode ) );
}

UTF8string stringOfKeyCode( KeyCode keycode ) noexcept
{
    return UTF8string( SDL_GetKeyName( keycode ) );
}


// Gamepad

UTF8string stringOfButton( GamepadButton button ) noexcept
{
    const char * S = SDL_GameControllerGetStringForButton( static_cast<SDL_GameControllerButton>( button ) );
    return UTF8string( S == nullptr ? "<null>" : S );
}

UTF8string stringOfAxis( GamepadAxis axis ) noexcept
{
    const char * S = SDL_GameControllerGetStringForAxis( static_cast<SDL_GameControllerAxis>( axis ) );
    return UTF8string( S == nullptr ? "<null>" : S );
}

}   // Event

}   // lx
