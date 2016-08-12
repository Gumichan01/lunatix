

/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    The LunatiX Engine is a SDL2-based game engine.
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

const char * getPlatform(void)
{
    return SDL_GetPlatform();
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


const SDL_DisplayMode * getDisplayModes(int& size)
{
    const int numberOfDisplays = SDL_GetNumDisplayModes(0);
    SDL_DisplayMode *mode = nullptr;

    if(numberOfDisplays == 0)
    {
        LX_SetError("No display available");
        return nullptr;
    }
    else if(numberOfDisplays < 0)
    {
        LX_SetError("Cannot get the number of display modes");
        return nullptr;
    }

    size = numberOfDisplays;
    mode = new (std::nothrow) SDL_DisplayMode[numberOfDisplays];

    if(mode == nullptr)
    {
        LX_SetError("Internal error : unavailable ressources");
        return nullptr;
    }

    for(int i = 0; i < numberOfDisplays; i++)
    {
        // Is that line useful ?
        mode[i].format = SDL_PIXELFORMAT_RGBA4444;

        if(SDL_GetDisplayMode(0,i,&mode[i]) < 0)
        {
            delete [] mode;
            return nullptr;
        }
    }

    return mode;
}

};
