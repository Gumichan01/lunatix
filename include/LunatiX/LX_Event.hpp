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
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_gamecontroller.h>

union SDL_Event;

/**
*   @namespace LX_Event
*   @brief The event module
*/
namespace LX_Event
{
using LX_KeyCode = SDL_Keycode;                     /**< Virtual key representation     */
using LX_ScanCode = SDL_Scancode;                   /**< Physical key representation    */
using LX_GamepadID = int32_t;                       /**< Identifier of the gamepad      */


/**
*   @typedef LX_GamepadAxis
*   @brief Gamepad axis
*
*   Values:
*   - LX_AXIS_INVALID
*   - LX_AXIS_LEFTX
*   - LX_AXIS_LEFTY
*   - LX_AXIS_RIGHTX
*   - LX_AXIS_RIGHTY
*   - LX_AXIS_TRIGGERLEFT
*   - LX_AXIS_TRIGGERRIGHT
*   - LX_AXIS_MAX
*
*/
using LX_GamepadAxis = SDL_GameControllerAxis;

/**
*   @typedef LX_GamepadButton
*   @brief Gamepad button
*
*   Values:
*   - LX_BUTTON_INVALID
*   - LX_BUTTON_A
*   - LX_BUTTON_B
*   - LX_BUTTON_X
*   - LX_BUTTON_Y
*   - LX_BUTTON_BACK
*   - LX_BUTTON_GUIDE
*   - LX_BUTTON_START
*   - LX_BUTTON_LEFTSTICK
*   - LX_BUTTON_RIGHTSTICK
*   - LX_BUTTON_LEFTSHOULDER
*   - LX_BUTTON_RIGHTSHOULDER
*   - LX_BUTTON_DPAD_UP
*   - LX_BUTTON_DPAD_DOWN
*   - LX_BUTTON_DPAD_LEFT
*   - LX_BUTTON_DPAD_RIGHT
*   - LX_BUTTON_MAX
*
*/
using LX_GamepadButton = SDL_GameControllerButton;

/**
*   @enum LX_EventType
*   @brief Event type
*/
enum LX_EventType: uint32_t
{
    LX_UNKNOWN,                     /**< Unknown type           */
    LX_QUIT,                        /**< User-requested quit    */
    LX_WINDOWEVENT,                 /**< Window state change    */

    /* Keyboard events */
    LX_KEYDOWN,                     /**< Key pressed                            */
    LX_KEYUP,                       /**< Key released                           */
    LX_TEXTEDITING,                 /**< Keyboard text editing (composition)    */
    LX_TEXTINPUT,                   /**< Keyboard text input                    */

    /* Mouse events */
    LX_MOUSEMOTION,                 /**< Mouse moved            */
    LX_MOUSEBUTTONDOWN,             /**< Mouse button pressed   */
    LX_MOUSEBUTTONUP,               /**< Mouse button released  */
    LX_MOUSEWHEEL,                  /**< Mouse wheel motion     */

    /* Game controller events */
    LX_CONTROLLERAXISMOTION,        /**< Game controller axis motion        */
    LX_CONTROLLERBUTTONDOWN,        /**< Game controller button pressed     */
    LX_CONTROLLERBUTTONUP,          /**< Game controller button released    */
    LX_CONTROLLERDEVICEADDED,       /**< A new Game controller has been inserted into the system    */
    LX_CONTROLLERDEVICEREMOVED,     /**< An opened Game controller has been removed                 */

    /* Drag and drop events */
    LX_DROPFILE,                    /**< The system requests a file open    */
    LX_USEREVENT                    /**< User-defined event                 */
};

/**
*   @enum LX_WinEventID
*   @brief Window Event type
*/
enum LX_WinEventID: uint8_t
{
    LX_WINEV_NONE,           /**< Never used                                            */
    LX_WINEV_SHOWN,          /**< Window has been shown                                 */
    LX_WINEV_HIDDEN,         /**< Window has been hidden                                */
    LX_WINEV_EXPOSED,        /**< Window has been exposed and should be redrawn         */
    LX_WINEV_MOVED,          /**< Window has been moved to a position (data1,data2)     */
    LX_WINEV_RESIZED,        /**< Window has been resized to data1 × data2              */
    LX_WINEV_SIZE_CHANGED,   /**< The window size has changed.                          */
    LX_WINEV_MINIMIZED,      /**< Window has been minimized                             */
    LX_WINEV_MAXIMIZED,      /**< Window has been maximized                             */
    LX_WINEV_RESTORED,       /**< Window has been restored to normal size and position  */
    LX_WINEV_ENTER,          /**< Window has gained mouse focus                         */
    LX_WINEV_LEAVE,          /**< Window has lost mouse focus                           */
    LX_WINEV_FOCUS_GAINED,   /**< Window has gained keyboard focus                      */
    LX_WINEV_FOCUS_LOST,     /**< Window has lost keyboard focus                        */
    LX_WINEV_CLOSE           /**< The window manager requests that the window be closed */
};


/**
*   @enum LX_MouseButton
*   @brief Representation of mouse butons
*/
enum LX_MouseButton: uint8_t
{
    LX_MOUSE_LBUTTON = SDL_BUTTON_LEFT,   /**< Left mouse button    */
    LX_MOUSE_MBUTTON = SDL_BUTTON_MIDDLE, /**< Middle mouse button  */
    LX_MOUSE_RBUTTON = SDL_BUTTON_RIGHT,  /**< Right mouse button   */
    LX_MOUSE_X1 = SDL_BUTTON_X1,          /**< X1 mouse button      */
    LX_MOUSE_X2 = SDL_BUTTON_X2,          /**< X2 mouse button      */
    LX_MOUSE_UNKNWON                      /**< Unknown mouse button */
};

/**
*   @struct LX_GAxis
*   @brief Axis of a gamepad
*/
struct LX_GAxis
{
    SDL_JoystickID id;      /**< ID of the gamepad        */
    LX_GamepadAxis axis;    /**< Axis type                */
    int16_t value;          /**< Value [-32768 ↔ 32768]   */
};


/**
*   @struct LX_GButton
*   @brief Button of a gamepad
*/
struct LX_GButton
{
    SDL_JoystickID which;   /**< ID of the gamepad                                        */
    LX_GamepadButton value; /**< Button value                                             */
    int16_t state;          /**< Button state : LX_BUTTON_PRESSED or LX_BUTTON_RELEASE    */
};


/**
*   @struct LX_MButton
*   @brief Button of a mouse
*/
struct LX_MButton
{
    uint32_t wid;           /**< Identifier of the window where the event occured         */
    LX_MouseButton button;  /**< Type of button                                           */
    uint8_t state;          /**< Button state : LX_BUTTON_PRESSED or LX_BUTTON_RELEASE    */
    uint8_t clicks;         /**< Number of clicks (1: single-click, 2: double-click, ...) */
    int x;                  /**< X position of the mouse                                  */
    int y;                  /**< Y position of the mouse                                  */
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
*       LX_EventHandler evh;
*
*       while(true)
*       {
*           while(evh.pollEvent())
*           {
*               switch(evh.getEventType())
*               {
*                   case SDL_MOUSEMOTION:
*                       ...
*                       LX_Log::log("state → %d %d %d %d %d",
*                                   evh.getMouseMotion().state[LX_MOUSE_LBUTTON],
*                                   evh.getMouseMotion().state[LX_MOUSE_MBUTTON],
*                                   evh.getMouseMotion().state[LX_MOUSE_RBUTTON],
*                                   evh.getMouseMotion().state[LX_MOUSE_X1],
*                                   evh.getMouseMotion().state[LX_MOUSE_X2]);
*                       ...
*                       break;
*               }
*           }
*       }
*
*/
struct LX_MMotion
{
    uint32_t wid;               /**< Identifier of the window where the event occured   */
    bool state[LX_MBUTTONS];    /**< The possible states of the mouse                   */
    int x;                      /**< X position of the mouse                            */
    int y;                      /**< Y position of the mouse                            */
    int xrel;                   /**< X relative position of the mouse                   */
    int yrel;                   /**< Y relative position of the mouse                   */
};


/**
*   @struct LX_MWheel
*   @brief Mouse wheel
*/
struct LX_MWheel
{
    uint32_t wid;   /**< Identifier of the window where the event occured   */
    int x;          /**< X direction of the wheel                           */
    int y;          /**< Y direction of the wheel                           */
};


/**
*   @struct LX_WEvent
*   @brief Window event
*/
struct LX_WEvent
{
    uint32_t wid;       /**< Identifier of the window where the event occured   */
    LX_WinEventID evid; /**< Type of window event                               */
    int data1;          /**< Event dependant data                               */
    int data2;          /**< Event dependant data                               */
};


/**
*   @struct LX_UserEvent
*   @brief User-defined event
*/
struct LX_UserEvent
{
    uint32_t type;  /* User defined type (internal use)                     */
    uint32_t wid;   /**< Identifier of the window where the event occured   */
    int code;       /**< User defined event code                            */
    void *data1;    /**< user defined data pointer                          */
    void *data2;    /**< user defined data pointer                          */
};


/**
*   @struct LX_TextEvent
*   @brief Text event
*/
struct LX_TextEvent
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
struct LX_DropEvent
{
    std::string file;   /**< The name of the file that is requested             */
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
class LX_EventHandler
{
    SDL_Event *event;

    LX_EventHandler(const LX_EventHandler&);

public:

    /// Constructor
    LX_EventHandler();

    /**
    *   @fn bool pollEvent()
    *   Pool for currently pending events
    *
    *   @return TRUE if there is a pending event, FALSE otherwise
    *
    *   @note If there is an event, it is retrieved and internally stored.
    *   The event is removed from the event queue
    */
    bool pollEvent();
    /**
    *   @fn bool waitEvent()
    *   Wait for currently pending event
    *
    *   @return TRUE on success, FALSE otherwise
    *
    *   @note On success, an event is retrieved and internally stored.
    *   The event is removed from the event queue.
    *   @sa pollEvent()
    */
    bool waitEvent();
    /**
    *   @fn bool waitEventTimeout(int timeout)
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
    bool waitEventTimeout(int timeout);
    /**
    *   @fn bool pushUserEvent(LX_UserEvent& uevent)
    *   Push a user event to the event queue
    *
    *   @param uevent The user event to push
    *
    *   @return TRUE on success, FALSE otherwise.
    *   Use LX_GetError() for more information on failure.
    */
    bool pushUserEvent(LX_UserEvent& uevent);

    /**
    *   @fn uint32_t getWindowID()
    *   Get the id of a window where an event happened in
    *
    *   @return The window ID, 0 on failure.
    *   @note This function can returns 0 if the current event
    *   is not window-dependant
    */
    uint32_t getWindowID();
    /**
    *   @fn LX_EventType getEventType()
    *   Get the type of the current event after
    *   @return The type of event
    */
    LX_EventType getEventType();
    /**
    *   @fn LX_KeyCode getKeyCode()
    *
    *   Get the key code value (virtual keyboard value) of the keyboard button,
    *   assuming that the event is a keyboard event
    *
    *   @return The key code value
    */
    LX_KeyCode getKeyCode();
    /**
    *   @fn LX_ScanCode getScanCode()
    *
    *   Get the scan code value (physical keyboard value) of the keyboard button,
    *   assuming that the event is a keyboard event
    *
    *   @return The scan code value
    */
    LX_ScanCode getScanCode();
    /**
    *   @fn LX_GamepadID getGamepadID()
    *   Get the gamepad identifier related to the current event.
    *   @return The gamepad ID
    */
    LX_GamepadID getGamepadID();

    /**
    *   @fn const LX_GAxis getAxis()
    *   Get information about the gamepad axis related to the current event
    *   @return The structure describing the gamepad axis
    *   @sa getButton
    */
    const LX_GAxis getAxis();
    /**
    *   @fn const LX_GButton getButton()
    *   Get information about the gamepad button related to the current event
    *   @return The structure describing the gamepad button
    *   @sa getAxis
    */
    const LX_GButton getButton();

    /**
    *   @fn const LX_MButton getMouseButton()
    *   Get information about the mouse button related to the current event
    *   @return The structure describing the mouse button
    *
    *   @sa getMouseMotion
    *   @sa getMouseWheel
    */
    const LX_MButton getMouseButton();
    /**
    *   @fn const LX_MMotion getMouseMotion()
    *   Get information about the mouse movement related to the current event
    *   @return The structure describing the mouse movement
    *
    *   @sa getMouseButton
    *   @sa getMouseWheel
    */
    const LX_MMotion getMouseMotion();
    /**
    *   @fn const LX_MWheel getMouseWheel()
    *   Get information about the mouse wheel related to the current event
    *   @return The structure describing the mouse wheel
    *
    *   @sa getMouseButton
    *   @sa getMouseMotion
    */
    const LX_MWheel getMouseWheel();
    /**
    *   @fn const LX_WEvent getWindowEvent()
    *   Get information about the window event
    *   @return The structure describing the window event
    */
    const LX_WEvent getWindowEvent();
    /**
    *   @fn const LX_UserEvent getUserEvent()
    *   Get information about the user event
    *   @return The structure describing the user event
    */
    const LX_UserEvent getUserEvent();
    /**
    *   @fn const LX_TextEvent getTextEvent()
    *   Get information about the text event
    *   @return The structure describing the text event
    */
    const LX_TextEvent getTextEvent();
    /**
    *   @fn const LX_DropEvent getDropEvent()
    *   Get information about the drop event (drag & drop a file)
    *   @return The structure describing the event
    */
    const LX_DropEvent getDropEvent();

    /// Default Destructor
    ~LX_EventHandler();
};


// Keyboard
/**
*   @fn LX_KeyCode getKeyCodeFrom(LX_ScanCode scancode)
*
*   Get the virtual key (key code) that corresponds to
*   the physical key (scan code) given in argument
*
*   @param [in] scancode The virtual key value
*   @return The virtual key that corresponds to the physical key
*   @sa getScanCodeFrom()
*/
LX_KeyCode getKeyCodeFrom(LX_ScanCode scancode);
/**
*   @fn LX_ScanCode getScanCodeFrom(LX_KeyCode keycode)
*
*   Get the physical key (scan code) that corresponds to
*   the virtual key (key code) given in argument
*
*   @param [in] keycode The physical key value
*   @return The physical key that corresponds to the virtual key
*/
LX_ScanCode getScanCodeFrom(LX_KeyCode keycode);

/**
*   @fn UTF8string stringOfScanCode(LX_ScanCode scancode)
*
*   Get the string value of the physical key value given in argument
*
*   @param [in] scancode The physical key value to get the string from
*   @return A non-empty string on success, "" otherwise
*/
UTF8string stringOfScanCode(LX_ScanCode scancode);
/**
*   @fn UTF8string stringOfKeyCode(LX_KeyCode keycode)
*
*   Get the string value of the virtual key value given in argument
*
*   @param [in] keycode The virtual key value to get the string from
*   @return A non-empty string on success, "" otherwise
*/
UTF8string stringOfKeyCode(LX_KeyCode keycode);


// Gamepad
/**
*   @fn UTF8string stringOfButton(LX_GamepadButton button)
*
*   Get the string value of a button specified by the enum
*   given in argument
*
*   @param [in] button The enumeration to get the string from
*   @return The string on success, "null" otherwise
*/
UTF8string stringOfButton(LX_GamepadButton button);
/**
*   @fn UTF8string stringOfAxis(LX_GamepadAxis axis)
*
*   Get the string value of an axis specified by the enum
*   given in argument
*
*   @param [in] axis The enumeration to get the string from
*   @return The string on success, "null" otherwise
*/
UTF8string stringOfAxis(LX_GamepadAxis axis);

#include "LX_Event.inl"

};

#endif // LX_EVENT_HPP_INCLUDED
