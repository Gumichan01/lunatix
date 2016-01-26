#ifndef LX_LOG_HPP_INCLUDED
#define LX_LOG_HPP_INCLUDED

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
*	@file LX_Log.hpp
*	@brief The Log file header
*	@author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <SDL2/SDL_Log.h>

/// @todo Documentation + static analysis

namespace LX_Log
{

// Category of log
enum LX_CATEGORY{LX_LOG_APPLICATION = SDL_LOG_CATEGORY_APPLICATION,
                 LX_LOG_ERROR = SDL_LOG_CATEGORY_ERROR,
                 LX_LOG_SYSTEM = SDL_LOG_CATEGORY_SYSTEM,
                 LX_LOG_AUDIO = SDL_LOG_CATEGORY_AUDIO,
                 LX_LOG_VIDEO = SDL_LOG_CATEGORY_VIDEO,
                 LX_LOG_RENDER = SDL_LOG_CATEGORY_RENDER,
                 LX_LOG_INPUT = SDL_LOG_CATEGORY_INPUT};

bool isDebugMode(void);
void setDefaultMode(bool debug = true);
void setDefaultPriority(void);

void setVerbosePriority(LX_CATEGORY category);
void setDebugPriority(LX_CATEGORY category);
void setInfoPriority(LX_CATEGORY category);
void setWarningPriority(LX_CATEGORY category);
void setErrorPriority(LX_CATEGORY category);
void setCriticalPriority(LX_CATEGORY category);

};

#endif // LX_LOG_HPP_INCLUDED
