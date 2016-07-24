
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
*	@file LX_Device.cpp
*	@brief The implementation of the device
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <sstream>

#include <SDL2/SDL_mouse.h>

#include <LunatiX/LX_Device.hpp>
#include <LunatiX/LX_Error.hpp>

const short GUID_SIZE = 16;          // Size of the data in SDL_JoystickGUID


namespace
{

int lx_stat(SDL_Joystick * joy, LX_Device::LX_GamepadInfo& info)
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


int gstat(SDL_Joystick * joy, SDL_GameController * gc,
          LX_Device::LX_GamepadInfo& info)
{
    if(joy != nullptr)
    {
        info.name = LX_Device::nameOf(joy);
        return lx_stat(joy,info);
    }
    else if(gc != nullptr)
    {
        info.name = LX_Device::nameOf(gc);
        return lx_stat(SDL_GameControllerGetJoystick(gc),info);
    }
    else
        return LX_SetError("Invalid joystick/game controller\n");
}
};


namespace LX_Device
{

int numberOfDevices(void)
{
    return SDL_NumJoysticks();
}


const char * nameOf(SDL_Joystick * joy)
{
    return SDL_JoystickName(joy);
}


const char * nameOf(SDL_GameController * controller)
{
    return SDL_GameControllerName(controller);
}


int statGamepad(SDL_Joystick * joy, LX_GamepadInfo& info)
{
    return gstat(joy,nullptr,info);
}


int statGamepad(SDL_GameController * gc, LX_GamepadInfo& info)
{
    return gstat(nullptr,gc,info);
}


UTF8string gamepadToString(LX_GamepadInfo& info)
{
    std::ostringstream stream;
    char guid[GUID_SIZE+1] = {'\0'};
    SDL_JoystickGetGUIDString(info.uid,guid,GUID_SIZE);

    stream << std::endl << " ==== Gamepad Information ==== " << std::endl
           << "Gamepad - ID : " << info.id << std::endl
           << "Gamepad - UID : " << guid << std::endl
           << "Gamepad - Name : " << info.name << std::endl
           << "Gamepad - Number of Axes : " << info.nb_axis << std::endl
           << "Gamepad - Number of Balls : " << info.nb_balls << std::endl
           << "Gamepad - Number of Buttons : " << info.nb_buttons << std::endl
           << "Gamepad - Number of Hats : " << info.nb_hats << std::endl;

    return UTF8string(stream.str());
}


int mouseCursorDisplay(int toggle)
{
    return SDL_ShowCursor(toggle);
}

};
