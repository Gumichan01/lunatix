/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

#include "LX_Gamepad.hpp"


namespace LX_Device
{


/**
*   @fn LX_Gamepad::LX_Gamepad(int index)
*
*   Load the gamepad
*
*   @param index The index of the joystick to query
*
*   @note You can check the success of the operation
*           calling LX_Gamepad::isConnected()
*/
LX_Gamepad::LX_Gamepad(int index)
{
    gc = NULL;
    joy = NULL;
    haptic = NULL;

    if(index < numberOfDevices() && SDL_IsGameController(index))
    {
        gc = SDL_GameControllerOpen(index);
    }

    if(gc == NULL)
    {
        joy = SDL_JoystickOpen(index);
        haptic = new LX_Haptic(joy);
    }
    else
        haptic = new LX_Haptic(index);
}



LX_Gamepad::~LX_Gamepad()
{
    delete haptic;

    if(gc != NULL)
        SDL_GameControllerClose(gc);
    else
        SDL_JoystickClose(joy);
}


/**
*   @fn bool LX_Gamepad::isConnected(void)
*
*   Get the status of the gamepad
*
*   @return TRUE if the gamepad is opened and connected
*           FALSE otherwise
*
*/
bool LX_Gamepad::isConnected(void)
{
    if(gc != NULL)
        return SDL_GameControllerGetAttached(gc) == SDL_TRUE;
    else
        return SDL_JoystickGetAttached(joy) == SDL_TRUE;
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
    if(gc != NULL)
        return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gc));
    else
        return SDL_JoystickInstanceID(joy);
}



LX_Haptic * LX_Gamepad::getHaptic(void)
{
    return haptic;
}



/**
*   @fn const char * LX_Gamepad::getName(void)
*
*   Get the name of the Gamepad
*
*   @return The name of the gamepad, NULL otherwise
*
*/
const char * LX_Gamepad::getName(void)
{
    if(gc != NULL)
        return nameOf(gc);
    else
        return nameOf(joy);
}


/**
*   @fn const char * LX_Gamepad::toString(void)
*
*   Get information about the gamepad
*
*   @return Always returns a valid string
*/
const char * LX_Gamepad::toString(void)
{
    LX_GamepadInfo gi;

    if(gc != NULL)
        statGamepad(gc,&gi);
    else
        statGamepad(joy,&gi);

    return gamepadToString(&gi);
}


};



