

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is an SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Gamepad.cpp
*	@brief The LX_Gamepad implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/


#include <LunatiX/LX_Gamepad.hpp>
#include <LunatiX/LX_Haptic.hpp>
#include <LunatiX/LX_Device.hpp>
#include <LunatiX/LX_Error.hpp>


namespace LX_Device
{


/**
*   @fn LX_Gamepad::LX_Gamepad(int index)
*
*   Load the gamepad
*
*   @param index The index of the joystick to query
*
*   @note   You can check the success of the operation
*           calling LX_Gamepad::isConnected()
*/
LX_Gamepad::LX_Gamepad(int index): gc(nullptr),joy(nullptr),haptic(nullptr)
{
    if(index < numberOfDevices() && SDL_IsGameController(index))
    {
        gc = SDL_GameControllerOpen(index);
    }

    if(gc == nullptr)
    {
        joy = SDL_JoystickOpen(index);
        haptic = new LX_Haptic(joy);
    }
    else
        haptic = new LX_Haptic(gc);
}


LX_Gamepad::~LX_Gamepad()
{
    delete haptic;

    if(gc != nullptr)
        SDL_GameControllerClose(gc);
    else
        SDL_JoystickClose(joy);
}


/**
*   @fn bool LX_Gamepad::isConnected(void)
*
*   Get the status of the gamepad
*
*   @return TRUE if the gamepad is opened and connected,
*           FALSE otherwise
*
*/
bool LX_Gamepad::isConnected(void)
{
    if(gc != nullptr)
        return SDL_GameControllerGetAttached(gc) == SDL_TRUE;
    else
        return SDL_JoystickGetAttached(joy) == SDL_TRUE;
}


/**
*   @fn bool LX_Gamepad::isHaptic(void)
*
*   Check if the gamepad is haptic
*
*   @return TRUE if the gamepad has force feedback support,
*           FALSE otherwise
*
*/
bool LX_Gamepad::isHaptic(void)
{
    return haptic->isOpened();
}


/**
*   @fn SDL_JoystickID LX_Gamepad::getID(void)
*
*   Get the ID of the gamepad
*
*   @return The ID of the gamepad, -1 otherwise
*
*/
SDL_JoystickID LX_Gamepad::getID(void)
{
    if(gc != nullptr)
        return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gc));
    else
        return SDL_JoystickInstanceID(joy);
}


/**
*   @fn LX_Haptic * LX_Gamepad::getHaptic(void)
*
*   Get the haptic system of the gamepad
*
*   @return The haptic system
*
*   @note The system can be inexistent, so check the returned value
*/
LX_Haptic * LX_Gamepad::getHaptic(void)
{
    return haptic;
}



/**
*   @fn const char * LX_Gamepad::getName(void)
*
*   Get the name of the Gamepad
*
*   @return The name of the gamepad, a null pointer otherwise
*
*   @sa toString
*/
const char * LX_Gamepad::getName(void)
{
    if(gc != nullptr)
        return nameOf(gc);
    else
        return nameOf(joy);
}


/**
*   @fn const char * LX_Gamepad::toString(char *str)
*
*   Get information about the gamepad
*
*   @param str the string to fill information in
*
*   @return Always returns a valid string
*/
const char * LX_Gamepad::toString(char *str)
{
    LX_GamepadInfo gi;
    int err = 0;

    if(str == nullptr)
    {
        LX_SetError("Invalid string pointer");
        return nullptr;
    }

    if(gc != nullptr)
        err = statGamepad(gc,gi);
    else
        err = statGamepad(joy,gi);

    if(err == -1)
        return nullptr;

    return gamepadToString(gi,str);
}


};



