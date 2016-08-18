
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
*    @file LX_Device.cpp
*    @brief The implementation of the device
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/LX_Device.hpp>
#include <LunatiX/LX_Image.hpp>
#include <LunatiX/LX_Error.hpp>

#include <SDL2/SDL_mouse.h>
#include <sstream>

const short GUID_SIZE = 16;          // Size of the data in SDL_JoystickGUID


namespace LX_Device
{

LX_Mouse::LX_Mouse(LX_Graphics::LX_Surface& surface, int hot_x, int hot_y)
    : _cursor(nullptr)
{
    _cursor = SDL_CreateColorCursor(surface._surface,hot_x,hot_y);
}


bool LX_Mouse::isOpen()
{
    return _cursor != nullptr;
}


void LX_Mouse::setMouse()
{
    SDL_SetCursor(_cursor);
}


LX_Mouse::~LX_Mouse()
{
    SDL_FreeCursor(_cursor);
}


int numberOfDevices(void)
{
    return SDL_NumJoysticks();
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
           << "Gamepad - Is haptic : " << info.is_haptic << std::endl
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
