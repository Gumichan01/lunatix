

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

LX_Gamepad::LX_Gamepad(int index): _gc(nullptr),_joy(nullptr),_haptic(nullptr)
{
    if(index < numberOfDevices() && SDL_IsGameController(index))
        _gc = SDL_GameControllerOpen(index);

    if(_gc == nullptr)
    {
        _joy = SDL_JoystickOpen(index);
        _haptic = new LX_Haptic(_joy);
    }
    else
        _haptic = new LX_Haptic(_gc);
}


LX_Gamepad::~LX_Gamepad()
{
    delete _haptic;

    if(_gc != nullptr)
        SDL_GameControllerClose(_gc);
    else
        SDL_JoystickClose(_joy);
}


const char * LX_Gamepad::nameOf(SDL_Joystick * joy)
{
    return SDL_JoystickName(joy);
}


const char * LX_Gamepad::nameOf(SDL_GameController * controller)
{
    return SDL_GameControllerName(controller);
}


int LX_Gamepad::lx_stat(SDL_Joystick * joy, LX_GamepadInfo& info)
{
    if(joy == nullptr)
        return LX_SetError("Invalid joystick\n");

    // Get information
    info.id = SDL_JoystickInstanceID(joy);
    info.uid = SDL_JoystickGetGUID(joy);
    info.nb_axis = SDL_JoystickNumAxes(joy);
    info.nb_balls = SDL_JoystickNumBalls(joy);
    info.nb_buttons = SDL_JoystickNumButtons(joy);
    info.nb_hats = SDL_JoystickNumHats(joy);

    if(info.id == -1 || info.nb_axis == -1 || info.nb_balls == -1
            || info.nb_buttons == -1 || info.nb_hats == -1)
    {
        return LX_SetError("Cannot get information\n");
    }

    return 0;
}


int LX_Gamepad::gstat(SDL_Joystick * joy, SDL_GameController * gc,
          LX_GamepadInfo& info)
{
    if(joy != nullptr)
    {
        info.name = nameOf(joy);
        return lx_stat(joy,info);
    }
    else if(gc != nullptr)
    {
        info.name = nameOf(gc);
        return lx_stat(SDL_GameControllerGetJoystick(gc),info);
    }
    else
        return LX_SetError("Invalid joystick/game controller\n");
}


int LX_Gamepad::statGamepad(SDL_Joystick * joy, LX_GamepadInfo& info)
{
    return gstat(joy,nullptr,info);
}


int LX_Gamepad::statGamepad(SDL_GameController * gc, LX_GamepadInfo& info)
{
    return gstat(nullptr,gc,info);
}


bool LX_Gamepad::isConnected(void)
{
    if(_gc != nullptr)
        return SDL_GameControllerGetAttached(_gc) == SDL_TRUE;
    else
        return SDL_JoystickGetAttached(_joy) == SDL_TRUE;
}


bool LX_Gamepad::isHaptic(void)
{
    return _haptic->isOpened();
}


SDL_JoystickID LX_Gamepad::getID(void)
{
    if(_gc != nullptr)
        return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(_gc));
    else
        return SDL_JoystickInstanceID(_joy);
}


LX_Haptic * LX_Gamepad::getHaptic(void)
{
    return _haptic;
}


const char * LX_Gamepad::getName(void)
{
    if(_gc != nullptr)
        return nameOf(_gc);
    else
        return nameOf(_joy);
}


UTF8string LX_Gamepad::toString(void)
{
    LX_GamepadInfo gi;
    int err = 0;

    if(_gc != nullptr)
        err = statGamepad(_gc,gi);
    else
        err = statGamepad(_joy,gi);

    if(err == -1)
        return UTF8string(std::string("Cannot get gamepad information: ")
                          + LX_GetError());

    return gamepadToString(gi);
}

};
