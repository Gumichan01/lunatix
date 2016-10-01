

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
*    @file LX_SystemInfo.cpp
*    @brief The implementation of the system information
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <SDL2/SDL_cpuinfo.h>
#include <LunatiX/LX_SystemInfo.hpp>
#include <LunatiX/LX_Error.hpp>
#include <new>

namespace LX_SystemInfo
{

const UTF8string getPlatform(void)
{
    return UTF8string(SDL_GetPlatform());
}


int getCPUCacheLineSize(void)
{
    return SDL_GetCPUCacheLineSize();
}


int getCPUCount(void)
{
    return SDL_GetCPUCount();
}


int getSystemRAM(void)
{
    return SDL_GetSystemRAM();
}


void getAvailableDisplayModes(LX_DisplayMode& modes)
{
    const int nb_displays = SDL_GetNumDisplayModes(0);
    modes.clear();

    if(nb_displays == 0)
    {
        LX_SetError("No display available");
        return;
    }
    else if(nb_displays < 0)
    {
        LX_SetError("Cannot get the number of display modes");
        return;
    }

    SDL_DisplayMode mode;
    for(int i = 0; i < nb_displays; i++)
    {
        if(SDL_GetDisplayMode(0,i,&mode) == 0)
        {
            modes.push_back(mode);
        }
    }
}

};
