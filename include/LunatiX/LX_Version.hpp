#ifndef LX_VERSION_HPP_INCLUDED
#define LX_VERSION_HPP_INCLUDED


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
*    @file LX_Version.hpp
*    @brief The version library
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/


/**
*   @namespace LX_VersionInfo
*   @brief Information about the version of the engine
*/
namespace LX_VersionInfo
{

/**
*   @struct LX_Version
*   @brief The version structure
*
*   The current version of the engine
*/
struct LX_Version
{
    short major;         /**< Information about the major version */
    short minor;         /**< Information about the minor version */
    short patch;         /**< Information about the patch version */

};

/**
*   @fn void LX_EngineInfo(void)
*
*   Get information about the engine
*/
void LX_EngineInfo(void);

/**
*   @fn void LX_EngineVersion(LX_Version& version)
*
*   Get the version of the engine
*
*   @param [out] version The structure to fill in.
*/
void LX_EngineVersion(LX_Version& version);

/**
*   @fn void LX_VersionDependencies(void)
*
*   Display information about the engine and its dependencies
*/
void LX_VersionDependencies(void);

};

#endif // LX_VERSION_HPP_INCLUDED
