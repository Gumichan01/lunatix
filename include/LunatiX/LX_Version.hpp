
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_VERSION_HPP_INCLUDED
#define LX_VERSION_HPP_INCLUDED

/**
*   @file LX_Version.hpp
*   @brief The version library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*/

/**
*   @ingroup Config
*   @namespace LX_VersionInfo
*   @brief Information about the library
*/
namespace LX_VersionInfo
{

const int STATUS_LEN = 8;

/**
*   @struct LX_Version
*   @brief The version structure
*   The current version of the library
*/
struct LX_Version
{
    short major;         /**< Information about the major version */
    short minor;         /**< Information about the minor version */
    short patch;         /**< Information about the patch version */
    char status[STATUS_LEN];
};

/**
*   @fn void info()
*   Get information about the library
*/
void info();

/**
*   @fn void getVersion(LX_Version& version)
*   Get the version of the library
*   @param [out] version The structure to fill in.
*/
void getVersion(LX_Version& version);

/**
*   @fn void dependencies()
*   Display information about the library and its dependencies
*/
void dependencies();

};

#endif // LX_VERSION_HPP_INCLUDED
