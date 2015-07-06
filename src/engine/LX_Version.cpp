
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
*	@version 0.5
*
*/

#include "LX_Version.hpp"


namespace LX_VersionInfo
{

/**
*   @fn void LX_EngineVersion(LX_Version *version)
*
*   Get the version of the engine
*
*   @param version The structure to fill in. Must be not NULL
*
*/
void LX_EngineVersion(LX_Version *version)
{
    version->major = LX_MAJOR_VERSION;
    version->minor = LX_MINOR_VERSION;
    version->patch = LX_PATCH_VERSION;
}

};
