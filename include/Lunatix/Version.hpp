
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

#ifndef VERSION_HPP_INCLUDED
#define VERSION_HPP_INCLUDED

/**
*   @file Version.hpp
*   @brief The version library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <string>

namespace lx
{

/**
*   @ingroup Config
*   @namespace lx::VersionInfo
*   @brief Information about the library
*/
namespace VersionInfo
{

/**
*   @struct Version
*   @brief The version structure
*   The current version of the library
*/
struct Version final
{
    short major;        /**< Major version  */
    short minor;        /**< Minor version  */
    short patch;        /**< Patch version  */
    std::string status; /**< Status         */
};

/**
*   @fn void info() noexcept
*   Display information about the library
*/
void info() noexcept;
/**
*   @fn const Version getVersion() noexcept
*   Get the version of the library
*   @return Information about the version
*/
const Version getVersion() noexcept;
/**
*   @fn void dependencies() noexcept
*   Display information about the library and its dependencies
*/
void dependencies() noexcept;

}   // VersionInfo

}   // lx

#endif // VERSION_HPP_INCLUDED
