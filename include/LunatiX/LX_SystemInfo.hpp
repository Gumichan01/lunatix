#ifndef LX_SYSTEM_INFO_H_INCLUDED
#define LX_SYSTEM_INFO_H_INCLUDED


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
*    @file LX_SystemInfo.hpp
*    @brief The System information library
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <SDL2/SDL_video.h>


/**
*   @namespace LX_SystemInfo
*   @brief The System information module
*
*   This namespace describes a module that is able
*   to display information about the system
*   (Platform, CPU, RAM)
*/
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
const char * getPlatform(void);

/**
*   @fn int getCPUCacheLineSize(void)
*
*   Get the L1 cache line sizeof the CPU
*
*   @return The L1 cache size of the CPU, in kilobytes (KB)
*
*/
int getCPUCacheLineSize(void);

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
int getCPUCount(void);

/**
*   @fn int getSystemRAM(void)
*
*   Get the amount of Random Access Memory (RAM) in the system
*
*   @return The amount of RAM configured in the system in Megabytes (MB)
*
*/
int getSystemRAM(void);

/**
*   @fn const SDL_DisplayMode * getDisplayModes(int& size)
*
*   Get the list of possible displays on the screen
*
*   @param [out] size the preference to the size to fill in
*
*   @return The list of display modes if there is at least one display mode,
*           a null pointer otherwise, an error message can be got using
*           LX_GetError()
*
*   @note This function allocate a memory to create the list, so this list
*           must be freed whane it is not used to avoid a memory leak.
*
*/
const SDL_DisplayMode * getDisplayModes(int& size);

};

#endif // LX_SYSTEM_INFO_H_INCLUDED

