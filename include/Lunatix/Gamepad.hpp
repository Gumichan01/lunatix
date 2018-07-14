
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

#ifndef GAMEPAD_HPP_INCLUDED
#define GAMEPAD_HPP_INCLUDED

/**
*   @file Gamepad.hpp
*   @brief The gamepad interface
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/utils/utf8_string.hpp>
#include <SDL2/SDL_joystick.h>
#include <memory>

namespace lx
{

namespace Device
{

class Haptic;
struct Gamepad_;
struct GamepadInfo;

/**
*   @enum BatteryLevel
*   @brief Battery level of a gamepad
*/
enum class BatteryLevel
{
    UNKNOWN = SDL_JOYSTICK_POWER_UNKNOWN,
    EMPTY   = SDL_JOYSTICK_POWER_EMPTY,
    LOW     = SDL_JOYSTICK_POWER_LOW,
    MEDIUM  = SDL_JOYSTICK_POWER_MEDIUM,
    FULL    = SDL_JOYSTICK_POWER_FULL,
    WIRED   = SDL_JOYSTICK_POWER_WIRED,
    MAX     = SDL_JOYSTICK_POWER_MAX
};

using DeviceID = int32_t;
using DeviceGUID = SDL_JoystickGUID;

/**
*   @struct GamepadInfo
*   @brief Information about gamepad
*/
struct GamepadInfo final
{
    DeviceID id = 0;                /**< The joystick ID            */
    DeviceGUID uid = {{0}};         /**< The joystick UID           */
    UTF8string name = {""};         /**< The name of the joystick   */
    UTF8string is_haptic = {""};    /**< Haptic joystick or not     */
    BatteryLevel battery = {};      /**< Battery level              */
    int nb_axis = 0;                /**< The number of axes         */
    int nb_balls = 0;               /**< The number of balls        */
    int nb_buttons = 0;             /**< The number of buttons      */
    int nb_hats = 0;                /**< The number of hats         */
};


/**
*   @fn UTF8string gamepadToString(GamepadInfo& info) noexcept
*
*   Get the string format of the information structure
*
*   @param [in] info The information structure
*   @return Always returns a valid string
*
*   @post The returned string is valid
*   @sa statGamepad
*/
UTF8string gamepadToString( GamepadInfo& info ) noexcept;


/**
*   @class Gamepad
*   @brief The gamepad
*/
class Gamepad final
{
    std::unique_ptr<Gamepad_> m_gpimpl;

    Gamepad( const Gamepad& g ) = delete;
    Gamepad& operator =( const Gamepad& ) = delete;

public:

    Gamepad() noexcept;

    /**
    *   @fn bool open(int index)
    *
    *   Get access to a gamepad
    *
    *   @param [in] index The index of the gamepad to query
    *
    *   @return TRUE on success, FALSE if the gamepad is already opened and
    *          connected to another device.
    *
    *   @note   You can also check the success of the operation
    *          calling isConnected()
    *
    *   @sa close()
    */
    bool open( int index ) noexcept;
    /**
    *   @fn void close() noexcept
    *   Close the gamepad
    *
    *   @note An opened gamepad contains resources that
    *   are dynamiccally allocated. So, it is very important to close its resources.
    *
    *   @warning If the instance is destroyed without closing the gamepad,
    *   a memory leak will happen.
    *
    *   @sa open()
    */
    void close() noexcept;
    /**
    *   @fn bool isConnected() const noexcept
    *
    *   @return TRUE if the gamepad is opened and connected,
    *          FALSE otherwise
    */
    bool isConnected() const noexcept;
    /**
    *   @fn bool isHaptic() const noexcept
    *
    *   Check if the gamepad has force feedback support
    *
    *   @return TRUE if the gamepad has force feedback support,
    *          FALSE otherwise
    */
    bool isHaptic() const noexcept;
    /**
    *   @fn int32_t getID() const noexcept
    *   @return The ID of the gamepad, -1 otherwise
    */
    int32_t getID() const noexcept;
    /**
    *   @fn Haptic * getHaptic() const noexcept
    *   @return The haptic system if the gamepad support it, nullptr otherwise
    */
    Haptic * getHaptic() const noexcept;
    /**
    *   @fn BatteryLevel getBatteryLevel() noexcept
    *   @return The battery level
    */
    BatteryLevel getBatteryLevel() noexcept;
    /**
    *   @fn const char * getName() const noexcept
    *   @return The name of the gamepad, a null pointer otherwise
    *   @sa toString
    */
    const char * getName() const noexcept;
    /**
    *   @fn bool stat(GamepadInfo& info) const noexcept
    *
    *   Get information about the gamepad
    *
    *   @param [out] info The information structure to fill
    *   @return TRUE on success, FALSE otherwise.
    *          Call lx::getError() to get the error message
    */
    bool stat( GamepadInfo& info ) const noexcept;

    /**
    *   @fn UTF8string toString() const noexcept
    *   Get information about the gamepad in string format
    *   @return Always returns a valid string
    */
    UTF8string toString() const noexcept;

    ~Gamepad();
};

}   // Device

}   // lx

#endif  // GAMEPAD_HPP_INCLUDED
