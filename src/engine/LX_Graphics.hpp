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
*	@version 0.4
*
*/

#include <iostream>

#include "LX_Window.hpp"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;


/**
*
*   @namespace LX_Graphics
*   @brief The graphics module
*
*   This namespace describes LX_Graphics, the graphics module of Lunatix Engine.
*
*/
namespace LX_Graphics{


    SDL_Surface * loadSurface(std::string filename);

    // To use when you work with a window without using the window manager
    SDL_Texture * loadTextureFromSurface(SDL_Surface *target, LX_Window * w);
    SDL_Texture * loadTextureFromFile(std::string filename, LX_Window * w);

    // To use when you work with the window manager
    SDL_Texture * loadTextureFromSurface(SDL_Surface *target, int id);
    SDL_Texture * loadTextureFromFile(std::string filename, int id);

    bool setAlpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue);

};

#endif // LX_GRAPHICS_H_INCLUDED












