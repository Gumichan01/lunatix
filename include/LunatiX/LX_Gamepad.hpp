#ifndef LX_GAMEPAD_HPP_INCLUDED
#define LX_GAMEPAD_HPP_INCLUDED


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
*    @file LX_Gamepad.hpp
*    @brief The file that contains the declaration of LX_Gamepad
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>

#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_gamecontroller.h>

#include <memory>

namespace LX_Device
{

class LX_Haptic;
struct LX_GamepadInfo;

/**
*   @class LX_Gamepad
*   @brief The gamepad (joystick, game controller)
*
*   It handles any type of gamepad
*/
class LX_Gamepad
{
    SDL_GameController *_gc;
    SDL_Joystick *_joy;
    std::unique_ptr<LX_Haptic> _haptic;


    const char * nameOf_(SDL_Joystick * joy) const;
    const char * nameOf_(SDL_GameController * controller) const;
    bool lx_stat_(SDL_Joystick * joy, LX_GamepadInfo& info) const;
    bool gstat_(SDL_Joystick * joy, SDL_GameController * gc, LX_GamepadInfo& info) const;
    bool statGamepad_(SDL_Joystick * joy, LX_GamepadInfo& info) const;
    bool statGamepad_(SDL_GameController * gp, LX_GamepadInfo& info) const;

    LX_Gamepad(const LX_Gamepad& g);

public :

    /**
    *   @fn LX_Gamepad()
    *   @brief Constructor
    */
    LX_Gamepad();

    /**
    *   @fn void open(int index)
    *
    *   Open the gamepad
    *
    *   @param [in] index The index of the joystick to query
    *
    *   @note   You can check the success of the operation
    *           calling isConnected()
    */
    void open(int index);

    /**
    *   @fn void close()
    *   Close the gamepad
    */
    void close();

    /**
    *   @fn bool isConnected() const
    *
    *   Get the status of the gamepad
    *
    *   @return TRUE if the gamepad is opened and connected,
    *           FALSE otherwise
    *
    */
    bool isConnected() const;

    /**
    *   @fn bool isHaptic() const
    *
    *   Check if the gamepad is haptic
    *
    *   @return TRUE if the gamepad has force feedback support,
    *           FALSE otherwise
    *
    */
    bool isHaptic() const;

    /**
    *   @fn SDL_JoystickID getID() const
    *
    *   Get the ID of the gamepad
    *
    *   @return The ID of the gamepad, -1 otherwise
    *
    */
    SDL_JoystickID getID() const;

    /**
    *   @fn LX_Haptic * getHaptic() const
    *
    *   Get the haptic system of the gamepad
    *
    *   @return The haptic system
    *
    *   @note The system can be inexistent, so check the returned value
    */
    LX_Haptic * getHaptic() const;

    /**
    *   @fn const char * getName() const
    *
    *   Get the name of the Gamepad
    *
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
    *           Call LX_GetError() to get the error message
    *
    */
    bool stat(LX_GamepadInfo& info) const;

    /**
    *   @fn UTF8string toString() const
    *
    *   Get information about the gamepad in string format
    *
    *   @return Always returns a valid string
    */
    UTF8string toString() const;

    /// Destructor
    ~LX_Gamepad();
};

};

#endif  // LX_GAMEPAD_HPP_INCLUDED
