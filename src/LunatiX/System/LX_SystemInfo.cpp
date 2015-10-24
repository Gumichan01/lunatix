

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_SystemInfo.cpp
*	@brief The implementation of the system information
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <iostream>
#include <new>

#include <SDL2/SDL_cpuinfo.h>

#include <LunatiX/LX_SystemInfo.hpp>
#include <LunatiX/LX_Error.hpp>


using namespace std;

namespace LX_SystemInfo
{

/**
*   @fn const char * getPlatform(void)
*
*   Return the name of the patform.
*
*   @return The name of the platform the program is running on.
*           Or a string beginning with "Unkownn" if the name
*           is not available.
*
*   @note The names returned by the function is one of
*           these following names :
*           - Windows
*           - Mac OS X
*           - Linux
*           - iOS
*           - Android
*
*/
const char * getPlatform(void)
{
    return SDL_GetPlatform();
}


/**
*   @fn int getCPUCacheLineSize(void)
*
*   Get the L1 cache line sizeof the CPU
*
*   @return The L1 cache size of the CPU, in kilobytes (KB)
*
*/
int getCPUCacheLineSize(void)
{
    return SDL_GetCPUCacheLineSize();
}


/**
*   @fn int getCPUCount(void)
*
*   Get the CPU cores
*
*   @return The number of logical cores of the CPU
*
*   @note On CPU that include hyperthreading technology,
*   the value may be higher than the number of physical cores
*
*/
int getCPUCount(void)
{
    return SDL_GetCPUCount();
}


/**
*   @fn int getSystemRAM(void)
*
*   Get the amount of Random Access Memory (RAM) in the system
*
*   @return The amount of RAM configured in the system in Megabytes (MB)
*
*/
int getSystemRAM(void)
{
    return SDL_GetSystemRAM();
}


/**
*   @fn const SDL_DisplayMode * getDisplayModes(int& size)
*
*   Get the list of possible displays on the screen
*
*   @param size the preference to the size to fill in
*
*   @return The list of display modes if there is at least one display mode,
*           a null pointer otherwise, you can get an error message using
*           LX_GetError()
*
*   @note This function allocate a memory to create the list, so you have
*           to free that list when you do not need it.
*
*/
const SDL_DisplayMode * getDisplayModes(int& size)
{
    const int numberOfDisplays = SDL_GetNumDisplayModes(0);
    SDL_DisplayMode *mode = NULL;

    if(numberOfDisplays == 0)
    {
        LX_SetError("No display available");
        return NULL;
    }
    else if(numberOfDisplays == 0)
    {
        LX_SetError("Cannot get the number of display modes");
        return NULL;
    }

    mode = new (nothrow) SDL_DisplayMode[numberOfDisplays];

    if(mode == NULL)
    {
        LX_SetError("Internal error : unavailable ressources");
        return NULL;
    }

    size = numberOfDisplays;

    for(int i = 0; i < numberOfDisplays; i++)
    {
        // Is that line useful ?
        mode[i].format = SDL_PIXELFORMAT_RGBA4444;

        if(SDL_GetDisplayMode(0,i,&mode[i]) < 0)
        {
            delete [] mode;
            return NULL;
        }
    }

    return mode;
}

};

