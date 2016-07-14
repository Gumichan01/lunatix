

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
*	@file LX_Gamepad.cpp
*	@brief The LX_Gamepad implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/


#include <LunatiX/LX_Gamepad.hpp>
#include <LunatiX/LX_Haptic.hpp>
#include <LunatiX/LX_Device.hpp>
#include <LunatiX/LX_Error.hpp>


namespace LX_Device
{

LX_Gamepad::LX_Gamepad(int index): gc(nullptr),joy(nullptr),haptic(nullptr)
{
    if(index < numberOfDevices() && SDL_IsGameController(index))
        gc = SDL_GameControllerOpen(index);

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


bool LX_Gamepad::isConnected(void)
{
    if(gc != nullptr)
        return SDL_GameControllerGetAttached(gc) == SDL_TRUE;
    else
        return SDL_JoystickGetAttached(joy) == SDL_TRUE;
}


bool LX_Gamepad::isHaptic(void)
{
    return haptic->isOpened();
}


SDL_JoystickID LX_Gamepad::getID(void)
{
    if(gc != nullptr)
        return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gc));
    else
        return SDL_JoystickInstanceID(joy);
}


LX_Haptic * LX_Gamepad::getHaptic(void)
{
    return haptic;
}


const char * LX_Gamepad::getName(void)
{
    if(gc != nullptr)
        return nameOf(gc);
    else
        return nameOf(joy);
}


UTF8string LX_Gamepad::toString(void)
{
    LX_GamepadInfo gi;
    int err = 0;

    if(gc != nullptr)
        err = statGamepad(gc,gi);
    else
        err = statGamepad(joy,gi);

    if(err == -1)
        return UTF8string(std::string("Cannot get gamepad information: ")
                          + LX_GetError());

    return gamepadToString(gi);
}

};
