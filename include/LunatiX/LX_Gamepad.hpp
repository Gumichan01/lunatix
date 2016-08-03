#ifndef LX_GAMEPAD_HPP_INCLUDED
#define LX_GAMEPAD_HPP_INCLUDED


/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Gamepad.hpp
*	@brief The file that contains the declaration of LX_Gamepad
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>

#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_gamecontroller.h>


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
    LX_Haptic *_haptic;


    const char * nameOf_(SDL_Joystick * joy);
    const char * nameOf_(SDL_GameController * controller);
    bool lx_stat(SDL_Joystick * joy, LX_GamepadInfo& info);
    bool gstat_(SDL_Joystick * joy, SDL_GameController * gc, LX_GamepadInfo& info);
    bool statGamepad_(SDL_Joystick * joy, LX_GamepadInfo& info);
    bool statGamepad_(SDL_GameController * gp, LX_GamepadInfo& info);


public :

    /**
    *   @fn LX_Gamepad(int index)
    *
    *   Load the gamepad
    *
    *   @param index The index of the joystick to query
    *
    *   @note   You can check the success of the operation
    *           calling isConnected()
    */
    LX_Gamepad(int index=0);

    /**
    *   @fn bool isConnected(void)
    *
    *   Get the status of the gamepad
    *
    *   @return TRUE if the gamepad is opened and connected,
    *           FALSE otherwise
    *
    */
    bool isConnected(void);

    /**
    *   @fn bool isHaptic(void)
    *
    *   Check if the gamepad is haptic
    *
    *   @return TRUE if the gamepad has force feedback support,
    *           FALSE otherwise
    *
    */
    bool isHaptic(void);

    /**
    *   @fn SDL_JoystickID getID(void)
    *
    *   Get the ID of the gamepad
    *
    *   @return The ID of the gamepad, -1 otherwise
    *
    */
    SDL_JoystickID getID(void);

    /**
    *   @fn LX_Haptic * getHaptic(void)
    *
    *   Get the haptic system of the gamepad
    *
    *   @return The haptic system
    *
    *   @note The system can be inexistent, so check the returned value
    */
    LX_Haptic * getHaptic(void);

    /**
    *   @fn const char * getName(void)
    *
    *   Get the name of the Gamepad
    *
    *   @return The name of the gamepad, a null pointer otherwise
    *
    *   @sa toString
    */
    const char * getName(void);

    /**
    *   @fn bool stat(LX_GamepadInfo& info)
    *
    *   Get information about the gamepad
    *
    *   @param[in,out] info The information structure to fill
    *   @return TRUE on success, FALSE otherwise.
    *           Call LX_GetError() to get the error message
    *
    */
    bool stat(LX_GamepadInfo& info);

    /**
    *   @fn UTF8string toString(void)
    *
    *   Get information about the gamepad in string format
    *
    *   @return Always returns a valid string
    */
    UTF8string toString(void);

    ~LX_Gamepad();
};

};

#endif  // LX_GAMEPAD_HPP_INCLUDED
