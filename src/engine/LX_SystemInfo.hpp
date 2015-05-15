#ifndef LX_SYSTEM_INFO_H_INCLUDED
#define LX_SYSTEM_INFO_H_INCLUDED



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
*	@brief The System information library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.4
*
*/

#include <iostream>

#include <SDL2/SDL.h>


namespace LX_SystemInfo{


    const char * getPlatform(void);

    int getCPUCacheLineSize(void);

    int getCPUCount(void);

    int getSystem_RAM(void);

};



#endif // LX_SYSTEM_INFO_H_INCLUDED
