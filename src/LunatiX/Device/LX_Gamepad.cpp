

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


const char * LX_Gamepad::nameOf_(SDL_Joystick * joy)
{
    return SDL_JoystickName(joy);
}


const char * LX_Gamepad::nameOf_(SDL_GameController * controller)
{
    return SDL_GameControllerName(controller);
}


bool LX_Gamepad::lx_stat(SDL_Joystick * joy, LX_GamepadInfo& info)
{
    if(joy == nullptr)
    {
        LX_SetError("Invalid joystick\n");
        return false;
    }

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
        LX_SetError("Cannot get information\n");
        return false;
    }

    return true;
}


bool LX_Gamepad::gstat_(SDL_Joystick * joy, SDL_GameController * gc,
                        LX_GamepadInfo& info)
{
    if(joy != nullptr)
    {
        info.name = nameOf_(joy);
        return lx_stat(joy,info);
    }
    else if(gc != nullptr)
    {
        info.name = nameOf_(gc);
        return lx_stat(SDL_GameControllerGetJoystick(gc),info);
    }
    else
    {
        // This case should not happen
        LX_SetError("Invalid joystick/game controller\n");
    }
}


bool LX_Gamepad::statGamepad_(SDL_Joystick * joy, LX_GamepadInfo& info)
{
    return gstat_(joy,nullptr,info);
}


bool LX_Gamepad::statGamepad_(SDL_GameController * gc, LX_GamepadInfo& info)
{
    return gstat_(nullptr,gc,info);
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
        return nameOf_(_gc);
    else
        return nameOf_(_joy);
}


UTF8string LX_Gamepad::toString(void)
{
    LX_GamepadInfo gi;
    int err = 0;

    if(_gc != nullptr)
        err = statGamepad_(_gc,gi);
    else
        err = statGamepad_(_joy,gi);

    if(err == -1)
        return UTF8string(std::string("Cannot get gamepad information: ")
                          + LX_GetError());

    return gamepadToString(gi);
}

};
