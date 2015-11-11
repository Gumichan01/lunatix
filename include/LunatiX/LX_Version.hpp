#ifndef LX_VERSION_HPP_INCLUDED
#define LX_VERSION_HPP_INCLUDED



/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is an SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Version.hpp
*	@brief The version library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
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
typedef struct LX_Version
{
    char major;         /**< Information about the major version */
    char minor;         /**< Information about the minor version */
    char patch;         /**< Information about the patch version */

} LX_Version;   /**< The version */

void LX_EngineVersion(LX_Version& version);

};


#endif // LX_VERSION_HPP_INCLUDED

