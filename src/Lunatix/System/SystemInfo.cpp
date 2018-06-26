
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
*   @file SystemInfo.cpp
*   @brief The implementation of the system information
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/SystemInfo.hpp>
#include <Lunatix/Error.hpp>

#include <SDL2/SDL_cpuinfo.h>
#include <SDL2/SDL_video.h>
#include <new>

namespace
{

lx::SystemInfo::LX_DisplayMode fromSDL_DisplayMode( SDL_DisplayMode& sdlmode )
{
    return { sdlmode.w, sdlmode.h, sdlmode.refresh_rate };
}

}

namespace lx
{

namespace SystemInfo
{

const UTF8string getPlatform()
{
    return UTF8string( SDL_GetPlatform() );
}

int getCPUCacheLineSize() noexcept
{
    return SDL_GetCPUCacheLineSize();
}

int getCPUCount() noexcept
{
    return SDL_GetCPUCount();
}

int getSystemRAM() noexcept
{
    return SDL_GetSystemRAM();
}

void getAvailableDisplayModes( LX_DisplayModes& modes )
{
    const int NB_DISPLAYS = SDL_GetNumDisplayModes( 0 );
    modes.clear();

    if ( NB_DISPLAYS == 0 )
    {
        LX_setError( "No display available" );
        return;
    }
    else if ( NB_DISPLAYS < 0 )
    {
        LX_setError( "Cannot get the number of display modes" );
        return;
    }

    SDL_DisplayMode mode;
    for ( int i = 0; i < NB_DISPLAYS; i++ )
    {
        if ( SDL_GetDisplayMode( 0, i, &mode ) == 0 )
        {
            modes.push_back( fromSDL_DisplayMode( mode ) );
        }
    }
}

}   // SystemInfo

}   // lx
