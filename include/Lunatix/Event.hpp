
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

#ifndef LX_EVENT_HPP_INCLUDED
#define LX_EVENT_HPP_INCLUDED

/**
*   @file Event.hpp
*   @brief The Event namespace
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/utils/utf8_string.hpp>
#include <SDL2/SDL_keycode.h>

union SDL_Event;


/**
*   @defgroup Event Event
*   @brief Event handling module
*/

/**
*   @ingroup Event
*   @namespace LX_Event
*   @brief The event namespace
*
*   It handles every events (user input, window,...)
*
*   @warning In order to use this namespace, the *video* flag
*   in the configuration file must be set to 1, otherwise the behaviour of
*   the library is undefined.
*
*/
namespace LX_Event
{
using LX_KeyCode   = SDL_Keycode;   /**< Virtual key representation     */
using LX_ScanCode  = SDL_Scancode;  /**< Physical key representation    */
using LX_GamepadID = int32_t;       /**< Identifier of the gamepad      */


/**
*   @enum LX_GamepadAxis
*   @brief Gamepad axis value
*
*   Values:
*   - INVALID
*   - LEFTX:        X Left axis of the gamepad (left-right)
*   - LEFTY:        Y Left axis of the gamepad (top-down)
*   - RIGHTX:       X Left axis of the gamepad (left-right)
*   - RIGHTY:       Y Left axis of the gamepad (top-down)
*   - TRIGGERLEFT:  Left trigger
*   - TRIGGERRIGHT: Right trigger
*   - MAX
*
*/
enum class LX_GamepadAxis
{
    INVALID = -1,
    LEFTX,
    LEFTY,
    RIGHTX,
    RIGHTY,
    TRIGGERLEFT,
    TRIGGERRIGHT,
    MAX
};

/**
*   @enum LX_GamepadButton
*   @brief Gamepad button value
*
*   Values:
*   - INVALID
*   - A
*   - B
*   - X
*   - Y
*   - BACK
*   - GUIDE
*   - START
*   - LEFTSTICK
*   - RIGHTSTICK
*   - LEFTSHOULDER
*   - RIGHTSHOULDER
*   - DPAD_UP
*   - DPAD_DOWN
*   - DPAD_LEFT
*   - DPAD_RIGHT
*   - MAX
*/
enum class LX_GamepadButton
{
    INVALID = -1,
    A,
    B,
    X,
    Y,
    BACK,
    GUIDE,
    START,
    LEFTSTICK,
    RIGHTSTICK,
    LEFTSHOULDER,
    RIGHTSHOULDER,
    DPAD_UP,
    DPAD_DOWN,
    DPAD_LEFT,
    DPAD_RIGHT,
    MAX
};

/**
*   @enum LX_EventType
*   @brief Event type
*/
enum class LX_EventType
{
    UNKNOWN,                     /**< Unknown type           */
    QUIT,                        /**< User-requested quit    */
    WINDOWEVENT,                 /**< Window state change    */

    /* Keyboard events */
    KEYDOWN,                     /**< Key pressed                            */
    KEYUP,                       /**< Key released                           */
    TEXTEDITING,                 /**< Keyboard text editing (composition)    */
    TEXTINPUT,                   /**< Keyboard text input                    */

    /* Mouse events */
    MOUSEMOTION,                 /**< Mouse moved            */
    MOUSEBUTTONDOWN,             /**< Mouse button pressed   */
    MOUSEBUTTONUP,               /**< Mouse button released  */
    MOUSEWHEEL,                  /**< Mouse wheel motion     */

    /* Game controller events */
    CONTROLLERAXISMOTION,        /**< Game controller axis motion        */
    CONTROLLERBUTTONDOWN,        /**< Game controller button pressed     */
    CONTROLLERBUTTONUP,          /**< Game controller button released    */
    CONTROLLERDEVICEADDED,       /**< A new Game controller has been inserted into the system    */
    CONTROLLERDEVICEREMOVED,     /**< An opened Game controller has been removed                 */

    /* Drag and drop events */
    DROPFILE,                    /**< The system requests a file open    */
    USEREVENT                    /**< User-defined event                 */
};

/**
*   @enum LX_WinEventType
*   @brief Window Event type
*/
enum class LX_WinEventType
{
    WIN_NONE,           /**< Never used                                            */
    WIN_SHOWN,          /**< Window has been shown                                 */
    WIN_HIDDEN,         /**< Window has been hidden                                */
    WIN_EXPOSED,        /**< Window has been exposed and should be redrawn         */
    WIN_MOVED,          /**< Window has been moved to a position (data1, data2)    */
    WIN_RESIZED,        /**< Window has been resized to data1 × data2              */
    WIN_SIZE_CHANGED,   /**< The window size has changed.                          */
    WIN_MINIMIZED,      /**< Window has been minimized                             */
    WIN_MAXIMIZED,      /**< Window has been maximized                             */
    WIN_RESTORED,       /**< Window has been restored to normal size and position  */
    WIN_ENTER,          /**< Window has gained mouse focus                         */
    WIN_LEAVE,          /**< Window has lost mouse focus                           */
    WIN_FOCUS_GAINED,   /**< Window has gained keyboard focus                      */
    WIN_FOCUS_LOST,     /**< Window has lost keyboard focus                        */
    WIN_CLOSE           /**< The window manager requests that the window be closed */
};


/**
*   @enum LX_MouseButton
*   @brief Representation of mouse butons
*/
enum class LX_MouseButton
{
    LBUTTON = 1,   /**< Left mouse button    */
    MBUTTON = 2,   /**< Middle mouse button  */
    RBUTTON = 3,   /**< Right mouse button   */
    X1      = 4,   /**< X1 mouse button      */
    X2      = 5,   /**< X2 mouse button      */
    UNKNWON = 0    /**< Unknown mouse button */
};

/// Convert LX_MouseButton to int
inline uint8_t LX_MBIndex( const LX_MouseButton& b )
{
    return static_cast<uint8_t>( b );
}

/**
    @enum LX_State
    @brief Button state (keyboard, mouse, gamepad)
*/
enum class LX_State
{
    PRESSED  = 1,   /**< The button is pressed  */
    RELEASED = 0    /**< The button is released */
};


/**
*   @struct LX_GAxis
*   @brief Axis of a gamepad
*/
struct LX_GAxis final
{
    LX_GamepadID id;        /**< ID of the gamepad        */
    LX_GamepadAxis axis;    /**< Axis type                */
    int16_t value;          /**< Value [-32768 ↔ 32768]   */
};


/**
*   @struct LX_GButton
*   @brief Button of a gamepad
*/
struct LX_GButton final
{
    LX_GamepadID which;     /**< ID of the gamepad  */
    LX_GamepadButton value; /**< Button value       */
    LX_State state;         /**< Button state       */
};

/**
*   @struct LX_MButton
*   @brief Button of a mouse
*/
struct LX_MButton final
{
    uint32_t wid;           /**< Identifier of the window where the event occured           */
    LX_MouseButton button;  /**< Type of button                                             */
    LX_State state;         /**< Button state                                               */
    uint8_t clicks;         /**< Number of clicks (1: single-click, 2: double-click, ...)   */
    int x;                  /**< X position of the mouse                                    */
    int y;                  /**< Y position of the mouse                                    */
};

const int LX_MBUTTONS = 6;

/**
*   @struct LX_MMotion
*   @brief Mouse movement
*
*   @note state is a boolean array that contains information
*   about each button state of the mouse.
*
*   In order to know the state of a specific button,
*   the use of one of the following values of ::LX_MouseButton as
*   the index is necessary.
*
*   Example of code (from test-input.cpp):
*
*      LX_EventHandler evh;
*
*      while(true)
*      {
*          while(evh.pollEvent())
*          {
*              switch(evh.getEventType())
*              {
*                  case LX_MOUSEMOTION:
*                      ...
*                      LX_Log::log("state → %d %d %d %d %d",
*                                  evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::LBUTTON)],
*                                  evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::MBUTTON)],
*                                  evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::RBUTTON)],
*                                  evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::X1)],
*                                  evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::X2)]);
*                      ...
*                      break;
*              }
*          }
*      }
*
*/
struct LX_MMotion final
{
    uint32_t wid;               /**< Identifier of the window where the event occured   */
    bool state[LX_MBUTTONS];    /**< The state of each button of the mouse              */
    int x;                      /**< X position of the mouse                            */
    int y;                      /**< Y position of the mouse                            */
    int xrel;                   /**< X relative position of the mouse                   */
    int yrel;                   /**< Y relative position of the mouse                   */
};


/**
*   @struct LX_MWheel
*   @brief Mouse wheel
*/
struct LX_MWheel final
{
    uint32_t wid;   /**< Identifier of the window where the event occured   */
    int x;          /**< X direction of the wheel                           */
    int y;          /**< Y direction of the wheel                           */
};


/**
*   @struct LX_WEvent
*   @brief Window event
*/
struct LX_WEvent final
{
    uint32_t wid;           /**< Identifier of the window where the event occured   */
    LX_WinEventType evid;   /**< Type of window event                               */
    int data1;              /**< Event dependant data                               */
    int data2;              /**< Event dependant data                               */
};


/**
*   @struct LX_UserEvent
*   @brief User-defined event
*/
struct LX_UserEvent final
{
    uint32_t type;  /* User defined type (internal use)                     */
    uint32_t wid;   /**< Identifier of the window where the event occured   */
    int code;       /**< User defined event code                            */
    void * data1;   /**< user defined data pointer                          */
    void * data2;   /**< user defined data pointer                          */
};


/**
*   @struct LX_TextEvent
*   @brief Text event
*/
struct LX_TextEvent final
{
    uint32_t wid;       /**< Identifier of the window where the event occured   */
    std::string text;   /**< UTF-8 string                                       */
    int start;          /**< Begining of the text (for editing)                 */
    size_t length;      /**< Length of the string from the start                */
};

/**
*   @struct LX_DropEvent
*   @brief Drop event (file request)
*/
struct LX_DropEvent final
{
    std::string file;   /**< The name of the file that is requested */
};

/**
*   @struct LX_KeyboardState
*   @brief Keyboard state
*/
struct LX_KeyboardState final
{
    const uint8_t * state;  /**< The state of each key (Scan Code) of the keyboard  */
    const int sz;           /**< The number of states (size of the array)           */
};

/**
*   @class LX_EventHandler
*   @brief The class for event handling
*
*   This class is reponsible of handling event (pushing, retrieving)
*
*   @note Every getter functions must be called after
*   calling pollEvent()/waitEvent*(). If not, the behaviour is undefined.
*
*/
class LX_EventHandler final
{
    SDL_Event * event;

    LX_EventHandler( const LX_EventHandler& ) = delete;
    LX_EventHandler& operator =( const LX_EventHandler& ) = delete;

public:

    LX_EventHandler() noexcept;

    /**
    *   @fn bool pollEvent() noexcept
    *   Pool for currently pending events
    *
    *   @return TRUE if there is a pending event, FALSE otherwise
    *
    *   @note If there is an event, it is retrieved and internally stored.
    *   The event is removed from the event queue
    *
    *   @sa waitEvent()
    *   @sa waitEventTimeout()
    */
    bool pollEvent() noexcept;
    /**
    *   @fn bool waitEvent() noexcept
    *   Wait for currently pending event
    *
    *   @return TRUE on success, FALSE otherwise
    *
    *   @note On success, an event is retrieved and internally stored.
    *   The event is removed from the event queue.
    *   @sa pollEvent()
    */
    bool waitEvent() noexcept;
    /**
    *   @fn bool waitEventTimeout(int timeout) noexcept
    *   Wait for currently pending event during a certein number of milliseconds
    *
    *   @param [in] timeout The time to wait (in milliseconds)
    *
    *   @return TRUE on success, FALSE otherwise, or if the time is up.
    *
    *   @note On success, an event is retrieved and internally stored.
    *   The event is removed from the event queue.
    *   @sa pollEvent()
    */
    bool waitEventTimeout( int timeout ) noexcept;
    /**
    *   @fn bool pushUserEvent(LX_UserEvent& uevent) noexcept
    *   Push a user event to the event queue
    *
    *   @param uevent The user event to push
    *
    *   @return TRUE on success, FALSE otherwise.
    *   Use LX_getError() for more information on failure.
    */
    bool pushUserEvent( LX_UserEvent& uevent ) noexcept;

    /**
    *   @fn static void processEvent(const LX_EventType ty) noexcept
    *
    *   Activate the event processing for a type of event
    *
    *   @param ty The type of event to process
    *   @note 1 — By default, every events are enabled by default
    *   @note 2 — ::TEXTEDITING and ::TEXTINPUT cannot be set for processing
    *   using this function because the operation is done by LX_Text
    *
    *   @sa ignoreEvent
    */
    static void processEvent( const LX_EventType ty ) noexcept;
    /**
    *   @fn static void ignoreEvent(const LX_EventType ty) noexcept
    *
    *   Ingore a type of event
    *
    *   @param ty The type of event to ignore
    *   @note ::TEXTEDITING and ::TEXTINPUT cannot be ignored using
    *   this function because the operation is done by LX_Text
    *
    *   @sa processEvent
    */
    static void ignoreEvent( const LX_EventType ty ) noexcept;

    /**
    *   @fn uint32_t getWindowID() const noexcept
    *   Get the id of a window where an event happened in
    *
    *   @return The window ID, 0 on failure.
    *   @note This function can returns 0 if the current event
    *   is not window-dependant
    */
    uint32_t getWindowID() const noexcept;
    /**
    *   @fn LX_EventType getEventType() const noexcept
    *   Get the type of the current event after
    *   @return The type of event
    */
    LX_EventType getEventType() const noexcept;
    /**
    *   @fn const LX_KeyboardState getKeyboardState() const noexcept
    *   Get the current state of the keyboard
    *   @return The keyboard state
    */
    static const LX_KeyboardState getKeyboardState() noexcept;
    /**
    *   @fn LX_KeyCode getKeyCode() const noexcept
    *
    *   Get the key code value (virtual keyboard value) of the keyboard button,
    *   assuming that the event is a keyboard event
    *
    *   @return The key code value
    */
    LX_KeyCode getKeyCode() const noexcept;
    /**
    *   @fn LX_ScanCode getScanCode() const noexcept
    *
    *   Get the scan code value (physical keyboard value) of the keyboard button,
    *   assuming that the event is a keyboard event
    *
    *   @return The scan code value
    */
    LX_ScanCode getScanCode() const noexcept;

    /**
    *   @fn LX_GamepadID getGamepadID() const noexcept
    *   Get the gamepad identifier related to the current event.
    *   @return The gamepad ID
    */
    LX_GamepadID getGamepadID() const noexcept;

    /**
    *   @fn const LX_GAxis getAxis() const noexcept
    *   Get information about the gamepad axis related to the current event
    *   @return The structure describing the gamepad axis
    *   @sa getButton
    */
    const LX_GAxis getAxis() const noexcept;
    /**
    *   @fn const LX_GButton getButton() const
    *   Get information about the gamepad button related to the current event
    *   @return The structure describing the gamepad button
    *   @sa getAxis
    */
    const LX_GButton getButton() const noexcept;

    /**
    *   @fn const LX_MButton getMouseButton() const noexcept
    *   Get information about the mouse button related to the current event
    *   @return The structure describing the mouse button
    *
    *   @sa getMouseMotion
    *   @sa getMouseWheel
    */
    const LX_MButton getMouseButton() const noexcept;
    /**
    *   @fn const LX_MMotion getMouseMotion() const noexcept
    *   Get information about the mouse movement related to the current event
    *   @return The structure describing the mouse movement
    *
    *   @sa getMouseButton
    *   @sa getMouseWheel
    */
    const LX_MMotion getMouseMotion() const noexcept;
    /**
    *   @fn const LX_MWheel getMouseWheel() const noexcept
    *   Get information about the mouse wheel related to the current event
    *   @return The structure describing the mouse wheel
    *
    *   @sa getMouseButton
    *   @sa getMouseMotion
    */
    const LX_MWheel getMouseWheel() const noexcept;
    /**
    *   @fn const LX_WEvent getWindowEvent() const noexcept
    *   Get information about the window event
    *   @return The structure describing the window event
    */
    const LX_WEvent getWindowEvent() const noexcept;
    /**
    *   @fn const LX_UserEvent getUserEvent() const noexcept
    *   Get information about the user event
    *   @return The structure describing the user event
    */
    const LX_UserEvent getUserEvent() const noexcept;
    /**
    *   @fn const LX_TextEvent getTextEvent() const noexcept
    *   Get information about the text event
    *   @return The structure describing the text event
    */
    const LX_TextEvent getTextEvent() const noexcept;
    /**
    *   @fn const LX_DropEvent getDropEvent() const noexcept
    *   Get information about the drop event (drag & drop a file)
    *   @return The structure describing the event
    */
    const LX_DropEvent getDropEvent() const noexcept;

    ~LX_EventHandler();
};


// Keyboard
/**
*   @fn LX_KeyCode getKeyCodeFrom(LX_ScanCode scancode) noexcept
*
*   Get the virtual key (key code) that corresponds to
*   the physical key (scan code) given in argument
*
*   @param [in] scancode The virtual key value
*   @return The virtual key that corresponds to the physical key
*   @sa getScanCodeFrom()
*/
LX_KeyCode getKeyCodeFrom( LX_ScanCode scancode ) noexcept;
/**
*   @fn LX_ScanCode getScanCodeFrom(LX_KeyCode keycode) noexcept
*
*   Get the physical key (scan code) that corresponds to
*   the virtual key (key code) given in argument
*
*   @param [in] keycode The physical key value
*   @return The physical key that corresponds to the virtual key
*/
LX_ScanCode getScanCodeFrom( LX_KeyCode keycode ) noexcept;

/**
*   @fn UTF8string stringOfScanCode(LX_ScanCode scancode) noexcept
*
*   Get the string value of the physical key value given in argument
*
*   @param [in] scancode The physical key value to get the string from
*   @return A non-empty string on success, "" otherwise
*/
UTF8string stringOfScanCode( LX_ScanCode scancode ) noexcept;
/**
*   @fn UTF8string stringOfKeyCode(LX_KeyCode keycode) noexcept
*
*   Get the string value of the virtual key value given in argument
*
*   @param [in] keycode The virtual key value to get the string from
*   @return A non-empty string on success, "" otherwise
*/
UTF8string stringOfKeyCode( LX_KeyCode keycode ) noexcept;


// Gamepad
/**
*   @fn UTF8string stringOfButton(LX_GamepadButton button) noexcept
*
*   Get the string value of a button specified by the enum
*   given in argument
*
*   @param [in] button The enumeration to get the string from
*   @return The string on success, "<null>" otherwise
*/
UTF8string stringOfButton( LX_GamepadButton button ) noexcept;
/**
*   @fn UTF8string stringOfAxis(LX_GamepadAxis axis) noexcept
*
*   Get the string value of an axis specified by the enum
*   given in argument
*
*   @param [in] axis The enumeration to get the string from
*   @return The string on success, "<null>" otherwise
*/
UTF8string stringOfAxis( LX_GamepadAxis axis ) noexcept;

}

#endif // LX_EVENT_HPP_INCLUDED