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

#include <iostream> // For debug display
#include "LX_Gamepad.hpp"


namespace LX_Device
{



LX_Gamepad::LX_Gamepad(int index)
{
    gc = NULL;
    joy = NULL;

    if(SDL_IsGameController(index))
    {
        std::cout << "The gamepad is supported by the game controller interface!" << std::endl;
        gc = SDL_GameControllerOpen(index);
    }

    if(gc == NULL)
    {
        joy = SDL_JoystickOpen(index);
    }
}



LX_Gamepad::~LX_Gamepad()
{
    if(gc != NULL)
        SDL_GameControllerClose(gc);
    else
        SDL_JoystickClose(joy);
}



bool LX_Gamepad::isConnected(void)
{
    if(gc != NULL)
        return SDL_GameControllerGetAttached(gc);
    else
        return SDL_JoystickGetAttached(joy);
}



const char * LX_Gamepad::getName(void)
{
    if(gc != NULL)
        return nameOf(gc);
    else
        return nameOf(joy);
}


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








