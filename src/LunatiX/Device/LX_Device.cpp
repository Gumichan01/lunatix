
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file LX_Device.cpp
*   @brief The implementation of the device
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*
*/

#include <LunatiX/LX_Device.hpp>
#include <LunatiX/LX_Error.hpp>

#include <SDL2/SDL_mouse.h>
#include <sstream>


namespace LX_Device
{

int numberOfDevices() noexcept
{
    return SDL_NumJoysticks();
}

UTF8string gamepadToString(LX_GamepadInfo& info)
{
    const int GUID_SIZE = 33;       // Size of the data in SDL_JoystickGUID
    char guid[GUID_SIZE] = {'\0'};
    SDL_JoystickGetGUIDString(info.uid, guid, GUID_SIZE);

    std::ostringstream stream;
    stream << "\n ==== Gamepad Information ==== "
           << "\nGamepad - ID : "                << info.id
           << "\nGamepad - UID : "               << guid
           << "\nGamepad - Name : "              << info.name
           << "\nGamepad - Is haptic : "         << info.is_haptic
           << "\nGamepad - Number of Axes : "    << info.nb_axis
           << "\nGamepad - Number of Balls : "   << info.nb_balls
           << "\nGamepad - Number of Buttons : " << info.nb_buttons
           << "\nGamepad - Number of Hats : "    << info.nb_hats << "\n";

    return UTF8string(stream.str());
}

LX_MouseToggle mouseCursorDisplay(const LX_MouseToggle& toggle) noexcept
{
    return static_cast<LX_MouseToggle>(SDL_ShowCursor(static_cast<int>(toggle)));
}

}
