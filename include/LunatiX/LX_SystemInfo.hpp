#ifndef LX_SYSTEM_INFO_H_INCLUDED
#define LX_SYSTEM_INFO_H_INCLUDED


/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_SystemInfo.hpp
*	@brief The System information library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <SDL2/SDL_video.h>


/**
*   @namespace LX_SystemInfo
*   @brief The System information module
*
*   This namespace describes a module that is able
*   to display information about the system
*   (Platform, CPU, RAM)
*/
namespace LX_SystemInfo
{

const char * getPlatform(void);
int getCPUCacheLineSize(void);
int getCPUCount(void);
int getSystemRAM(void);

const SDL_DisplayMode * getDisplayModes(int& size);

};

#endif // LX_SYSTEM_INFO_H_INCLUDED

