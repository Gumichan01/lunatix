
/*
*   Copyright © 2017 Luxon Jean-Pierre
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
*   @file LX_Gamepad.hpp
*   @brief The gamepad interface
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <memory>

namespace LX_Device
{

class LX_Haptic;
struct LX_Gamepad_;
struct LX_GamepadInfo;

/**
*   @class LX_Gamepad
*   @brief The gamepad
*/
class LX_Gamepad
{
    std::unique_ptr<LX_Gamepad_> _gpimpl;

    LX_Gamepad(const LX_Gamepad& g);
    LX_Gamepad& operator =(const LX_Gamepad&);

public:

    /**
    *   @fn LX_Gamepad()
    *   @brief Constructor
    */
    LX_Gamepad();

    /**
    *   @fn bool open(int index)
    *
    *   Open the gamepad
    *
    *   @param [in] index The index of the joystick to query
    *
    *   @return TRUE on success, FALSE if the gamepad is already opened and
    *          connected to another device.
    *
    *   @note   You can also check the success of the operation
    *          calling isConnected()
    *
    *   @sa close()
    */
    bool open(int index);

    /**
    *   @fn void close()
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
    void close();

    /**
    *   @fn bool isConnected() const
    *
    *   Get the status of the gamepad
    *
    *   @return TRUE if the gamepad is opened and connected,
    *          FALSE otherwise
    */
    bool isConnected() const;

    /**
    *   @fn bool isHaptic() const
    *
    *   Check if the gamepad is haptic
    *
    *   @return TRUE if the gamepad has force feedback support,
    *          FALSE otherwise
    */
    bool isHaptic() const;

    /**
    *   @fn int32_t getID() const
    *   Get the ID of the gamepad
    *   @return The ID of the gamepad, -1 otherwise
    */
    int32_t getID() const;

    /**
    *   @fn LX_Haptic * getHaptic() const
    *   Get the haptic system of the gamepad
    *   @return The haptic system
    *
    *   @note The system can be inexistent, so check the returned value
    */
    LX_Haptic * getHaptic() const;

    /**
    *   @fn const char * getName() const
    *   Get the name of the Gamepad
    *   @return The name of the gamepad, a null pointer otherwise
    *
    *   @sa toString
    */
    const char * getName() const;

    /**
    *   @fn bool stat(LX_GamepadInfo& info) const
    *
    *   Get information about the gamepad
    *
    *   @param [out] info The information structure to fill
    *   @return TRUE on success, FALSE otherwise.
    *          Call LX_GetError() to get the error message
    */
    bool stat(LX_GamepadInfo& info) const;

    /**
    *   @fn UTF8string toString() const
    *   Get information about the gamepad in string format
    *   @return Always returns a valid string
    */
    UTF8string toString() const;

    /// Destructor
    ~LX_Gamepad();
};

};

#endif  // LX_GAMEPAD_HPP_INCLUDED
