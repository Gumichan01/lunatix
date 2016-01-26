

/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Log.cpp
*	@brief The Log file
*	@author Luxon Jean-Pierre(Gumichan01)
*
*/


#include <LunatiX/LX_Log.hpp>
#include <SDL2/SDL_Log.h>

namespace LX_Log
{

// Private field in the namespace
bool debug_mode = false;


bool isDebugMode()
{
    return debug_mode;
}

void setDefaultMode(bool debug)
{
    if(debug)
        SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
    else
        setDefaultPriority();

    debug_mode = debug;
}

// Set the default priorities defined by SDL2 to the application
void setDefaultPriority(void)
{
    SDL_LogResetPriorities();
}

};



