#ifndef LX_LIBRARY_H_INCLUDED
#define LX_LIBRARY_H_INCLUDED



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
*	@file LX_Library.hpp
*	@brief The Library header. It manages the engine ressources (load and shut down)
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <GL/glu.h>

#define LX_GL_MAJOR_VERSION 3
#define LX_GL_MINOR_VERSION 1


bool LX_Init(void);
void LX_Quit(void);


#endif // LX_LIBRARY_H_INCLUDED
