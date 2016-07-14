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

/**
*   @class LX_Gamepad
*   @brief The gamepad (joystick, game controller)
*
*   It handles any type of gamepad
*/
class LX_Gamepad
{
    SDL_GameController *gc;
    SDL_Joystick *joy;
    LX_Haptic *haptic;


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
    *   @fn UTF8string toString(void)
    *
    *   Get information about the gamepad
    *
    *   @return Always returns a valid string
    */
    UTF8string toString(void);

    ~LX_Gamepad();
};

};

#endif  // LX_GAMEPAD_HPP_INCLUDED

