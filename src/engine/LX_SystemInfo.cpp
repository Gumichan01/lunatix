

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_SystemInfo.hpp
*	@brief The implementation of the system information
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.4
*
*/

#include "LX_SystemInfo.hpp"
#include "LX_Error.hpp"


namespace LX_SystemInfo{


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
    *   @return The amount of RAM configured int the system in Megabytes (MB)
    *
    */
    int getSystemRAM(void)
    {
        return SDL_GetSystemRAM();
    }

};










