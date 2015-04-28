#ifndef LX_GRAPHICS_H_INCLUDED
#define LX_GRAPHICS_H_INCLUDED



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
*	@file LX_Graphics.hpp
*	@brief The LX_Graphics library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.3
*
*/

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "LX_Window.hpp"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;



namespace LX_Graphics{


    SDL_Surface * loadSurface(std::string filename);

    SDL_Texture * loadTextureFromSurface(SDL_Surface *target, int id);
    SDL_Texture * loadTextureFromFile(std::string filename, int id);

    bool set_alpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue);

};

#endif // LX_GRAPHICS_H_INCLUDED












