
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

#ifndef SYSTEM_INFO_H_INCLUDED
#define SYSTEM_INFO_H_INCLUDED

/**
*   @file SystemInfo.hpp
*   @brief The System information library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/utils/utf8_string.hpp>
#include <vector>

/**
*   @defgroup System System
*   @brief System module (File system, Multithreading, ...)
*/

namespace lx
{

/**
*   @ingroup System
*   @namespace lx::SystemInfo
*   @brief The System information namespace
*
*   This namespace provides information about the system
*   (Platform, CPU, RAM)
*/
namespace SystemInfo
{
/**
*   @struct DisplayMode
*   @brief Information about a display mode
*/
struct DisplayMode final
{
    int w;              /**< width  */
    int h;              /**< height */
    int refresh_rate;   /**< refresh rate (or zero for unspecified) */

};

/**
*   @typedef DisplayModes
*   @brief Array of modes
*/
using DisplayModes = std::vector<lx::SystemInfo::DisplayMode>;

/**
*   @fn const UTF8string getPlatform()
*
*   Return the name of the patform.
*
*   @return The name of the platform the program is running on.
*          Or a string beginning with "Unkownn" if the name
*          is not available.
*
*   @note The names returned by the function is one of
*          these following names :
*          - Windows
*          - Mac OS X
*          - Linux
*/
const UTF8string getPlatform();

/**
*   @fn int getCPUCacheLineSize() noexcept
*   Get the L1 cache line size of the CPU
*   @return The L1 cache size of the CPU, in kilobytes (KB)
*/
int getCPUCacheLineSize() noexcept;
/**
*   @fn int getCPUCount() noexcept
*   Get the CPU cores
*   @return The number of logical cores of the CPU
*
*   @note On CPU that include hyperthreading technology,
*   the value may be higher than the number of physical cores
*/
int getCPUCount() noexcept;
/**
*   @fn int getSystemRAM() noexcept
*   Get the amount of Random Access Memory (RAM) in the system
*   @return The amount of RAM configured in the system in Megabytes (MB)
*/
int getSystemRAM() noexcept;

/**
*   @fn void getAvailableDisplayModes(DisplayModes& modes)
*
*   Get the list of available display modes on the screen
*
*   @param [in,out] modes the different modes of display to fill in
*
*   @note DisplayMode is a struture that contains every available
*        display modes. In order to get these following modes, you should
*        use iterators.
*   @note Example
*
*       DisplayMode modes;
*       getAvailableDisplayModes(modes);
*
*       lx::Log::log("Display modes: ");
*       for(auto mode: modes)
*       {
*           lx::Log::log("%d × %d @ ~%d Hz", mode->w, mode->h, mode->refresh_rate);
*       }
*
*/
void getAvailableDisplayModes( DisplayModes& modes );

}   // SystemInfo

}   // lx

#endif // SYSTEM_INFO_H_INCLUDED
