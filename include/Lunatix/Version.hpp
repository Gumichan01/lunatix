
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
*
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
*   @struct SDLVersion
*   @brief Information about SDL (main version or plugin)
*   The current version of the library
*/
struct SDLVersion final
{
    Version compiled;
    Version linked;
    std::string plugin_name;    /**< Plugin name (optionnal)    */
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
*   @fn const SDLVersion getSDLVersion noexcept
*   @return Information about the version
*/
const SDLVersion getSDLVersion() noexcept;
/**
*   @fn const SDLVersion getSDLImageVersion noexcept
*   @return Information about the version
*/
const SDLVersion getSDLImageVersion() noexcept;
/**
*   @fn const SDLVersion getSDLTTFVersion() noexcept
*   @return Information about the version
*/
const SDLVersion getSDLTTFVersion() noexcept;
/**
*   @fn const SDLVersion getSDLMixerVersion noexcept
*   @return Information about the version
*/
const SDLVersion getSDLMixerVersion() noexcept;

/**
*   @fn void dependencies() noexcept
*   Display information about the library and its dependencies
*/
void dependencies() noexcept;

}   // VersionInfo

}   // lx

#endif // VERSION_HPP_INCLUDED
