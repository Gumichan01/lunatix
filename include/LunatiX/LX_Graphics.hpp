#ifndef LX_GRAPHICS_H_INCLUDED
#define LX_GRAPHICS_H_INCLUDED


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
*	@file LX_Graphics.hpp
*	@brief The graphics engine
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.7
*
*/

#include <string>
#include <SDL2/SDL_stdinc.h>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;


namespace LX_FileIO
{

class LX_File;
class LX_FileBuffer;

};

namespace LX_Win
{
class LX_Window;
}


/**
*   @namespace LX_Graphics
*   @brief The graphics module
*/
namespace LX_Graphics
{

SDL_Surface * loadSurface(std::string filename);
SDL_Surface * loadSurface(LX_FileIO::LX_File *file);
SDL_Surface * loadSurfaceFromFileBuffer(LX_FileIO::LX_FileBuffer *file);

SDL_Surface * optimizeSurface(SDL_Surface * surface);

// To use when you work with a window without using the window manager
SDL_Texture * loadTextureFromSurface(SDL_Surface *target, LX_Win::LX_Window * w);
SDL_Texture * loadTextureFromFile(const std::string filename, LX_Win::LX_Window * w);

// To use when you work with the window manager
SDL_Texture * loadTextureFromSurface(SDL_Surface *target, unsigned int id = 0);
SDL_Texture * loadTextureFromFile(const std::string filename, unsigned int id = 0);

bool setAlpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue);

};

#endif // LX_GRAPHICS_H_INCLUDED

