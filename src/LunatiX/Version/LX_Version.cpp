
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
*	@file LX_Version.cpp
*	@brief The version implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <LunatiX/LX_Version.hpp>


#define LX_MAJOR_VERSION 0      /**< The major version of the engine */
#define LX_MINOR_VERSION 6      /**< The minor version of the engine */
#define LX_PATCH_VERSION 2      /**< The patch of the engine */


namespace LX_VersionInfo
{

/**
*   @fn void LX_EngineVersion(LX_Version& version)
*
*   Get the version of the engine
*
*   @param version The structure to fill in.
*
*/
void LX_EngineVersion(LX_Version& version)
{
    version.major = LX_MAJOR_VERSION;
    version.minor = LX_MINOR_VERSION;
    version.patch = LX_PATCH_VERSION;
}

};
