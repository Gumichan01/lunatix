
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

#ifndef LX_GAMEPAD_HPP_INCLUDED
#define LX_GAMEPAD_HPP_INCLUDED

/**
*   @file Gamepad.hpp
*   @brief The gamepad interface
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/utils/utf8_string.hpp>
#include <memory>

namespace lx
{

namespace Device
{

class LX_Haptic;
struct LX_Gamepad_;
struct LX_GamepadInfo;

/**
*   @class LX_Gamepad
*   @brief The gamepad
*/
class LX_Gamepad final
{
    std::unique_ptr<LX_Gamepad_> _gpimpl;

    LX_Gamepad( const LX_Gamepad& g ) = delete;
    LX_Gamepad& operator =( const LX_Gamepad& ) = delete;

public:

    LX_Gamepad() noexcept;

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
    *   @fn LX_Haptic * getHaptic() const noexcept
    *   @return The haptic system if the gamepad support it, nullptr otherwise
    */
    LX_Haptic * getHaptic() const noexcept;
    /**
    *   @fn const char * getName() const noexcept
    *   @return The name of the gamepad, a null pointer otherwise
    *   @sa toString
    */
    const char * getName() const noexcept;
    /**
    *   @fn bool stat(LX_GamepadInfo& info) const noexcept
    *
    *   Get information about the gamepad
    *
    *   @param [out] info The information structure to fill
    *   @return TRUE on success, FALSE otherwise.
    *          Call LX_getError() to get the error message
    */
    bool stat( LX_GamepadInfo& info ) const noexcept;

    /**
    *   @fn UTF8string toString() const noexcept
    *   Get information about the gamepad in string format
    *   @return Always returns a valid string
    */
    UTF8string toString() const noexcept;

    ~LX_Gamepad();
};

}   // Device

}   // lx

#endif  // LX_GAMEPAD_HPP_INCLUDED
