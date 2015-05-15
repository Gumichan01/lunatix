

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_SystemInfo.hpp
*	@brief The implementation of the system information
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.4
*
*/

#include "LX_SystemInfo.hpp"
#include "LX_Error.hpp"

namespace LX_SystemInfo{


    const char * getPlatform(void)
    {
        return SDL_GetPlatform();
    }


    int getCPUCacheLineSize(void)
    {
        return SDL_GetCPUCacheLineSize();
    }


    int getCPUCount(void)
    {
        return SDL_GetCPUCount();
    }

    int getSystemRAM(void)
    {
        /// @todo Fix that issue. Bad version of SDL2 (2.0.0)
        return LX_SetError("Not supported in this compiled version");
    }

};










