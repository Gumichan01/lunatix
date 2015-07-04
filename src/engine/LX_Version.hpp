#ifndef LX_VERSION_HPP_INCLUDED
#define LX_VERSION_HPP_INCLUDED



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
*	@file LX_Version.hpp
*	@brief The version library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

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


#define LX_MAJOR_VERSION 0      /**< The major version of the engine */
#define LX_MINOR_VERSION 5      /**< The minor version of the engine */
#define LX_PATCH_VERSION 2      /**< The patch of the engine */

void LX_EngineVersion(LX_Version *version);


#endif // LX_VERSION_HPP_INCLUDED


