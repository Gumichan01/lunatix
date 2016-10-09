
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
#include <LunatiX/LX_Error.hpp>

#include <SDL2/SDL_mouse.h>
#include <sstream>


namespace LX_Device
{

const short GUID_SIZE = 33;          // Size of the data in SDL_JoystickGUID

int numberOfDevices()
{
    return SDL_NumJoysticks();
}


UTF8string stringOfButton(LX_GamepadButton button)
{
    const char * s = SDL_GameControllerGetStringForButton(button);
    return UTF8string(s == nullptr ? "null" : s);
}

UTF8string stringOfButton(uint8_t button)
{
    return stringOfButton(static_cast<LX_GamepadButton>(button));
}


UTF8string stringOfAxis(LX_GamepadAxis axis)
{
    const char * s = SDL_GameControllerGetStringForAxis(axis);
    return UTF8string(s == nullptr ? "null" : s);
}

UTF8string stringOfAxis(uint8_t axis)
{
    return stringOfAxis(static_cast<LX_GamepadAxis>(axis));
}


UTF8string stringOfPhysicalKey(LX_KeyboardPhysicalKey key)
{
    return UTF8string(SDL_GetScancodeName(key));
}


UTF8string stringOfVirtualKey(LX_KeyboardVirtualKey key)
{
    return UTF8string(SDL_GetKeyName(key));
}


LX_KeyboardVirtualKey getVirtualKey(LX_KeyboardPhysicalKey key)
{
    return SDL_GetKeyFromScancode(key);
}


LX_KeyboardPhysicalKey getPhysicalKey(LX_KeyboardVirtualKey key)
{
    return SDL_GetScancodeFromKey(key);
}


UTF8string gamepadToString(LX_GamepadInfo& info)
{
    std::ostringstream stream;
    char guid[GUID_SIZE] = {'\0'};
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
