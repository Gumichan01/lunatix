
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
*   @file Device.cpp
*   @brief The implementation of the device
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/Device.hpp>
#include <Lunatix/Error.hpp>

#include <SDL2/SDL_mouse.h>


namespace lx
{

namespace Device
{

int numberOfDevices() noexcept
{
    return SDL_NumJoysticks();
}

MouseToggle mouseCursorDisplay( const MouseToggle& toggle ) noexcept
{
    return static_cast<MouseToggle>( SDL_ShowCursor( static_cast<int>( toggle ) ) );
}

}   // Device

}   // lx
