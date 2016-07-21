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
*	@version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>
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

/**
*   @fn SDL_Surface * loadSurface(const std::string& filename)
*   @deprecated The engine will no longer support the display with surfaces
*
*   This function loads a SDL_Surface from any image file an optimized its format
*
*   @param filename The name of the image file
*
*   @return The loaded and optimized surface if there is no problem,
*           a null pointer otherwise
*
*   @note   When this function is called, the format optimization includes
*           the alpha channel.
*           No alpha value needs to be set on the surface after that.
*
*   @sa loadSurfaceFromFileBuffer
*/
SDL_Surface * loadSurface(const std::string& filename);

/**
*   @fn SDL_Surface * loadSurface(const UTF8string& filename)
*   @deprecated The engine will no longer support the display with surfaces
*
*   This function loads a SDL_Surface from any image file an optimized its format
*
*   @param filename The name of the image file
*
*   @return The loaded and optimized surface if there is no problem,
*           a null pointer otherwise
*
*   @note   When this function is called, the format optimization includes
*           the alpha channel.
*           No alpha value needs to be set on the surface after that.
*
*   @note The string given in argument is utf-8 encoded
*   @sa loadSurfaceFromFileBuffer
*/
SDL_Surface * loadSurface(const UTF8string& filename);

/**
*   @fn SDL_Surface * loadSurface(LX_FileIO::LX_File *file)
*
*   This function loads a SDL_Surface from memory
*
*   @param file The pointer to the LX_File structure
*
*   @return The loaded and optimized surface if there is no problem,
*           a null pointer otherwise
*
*   @note   When this function is called, the format optimization includes
*           the alpha channel.
*           No alpha needs to be set on the surface after that.
*
*   @sa loadSurfaceFromFileBuffer
*/
SDL_Surface * loadSurface(LX_FileIO::LX_File *file);

/**
*   @fn SDL_Surface * loadSurfaceFromFileBuffer(LX_FileIO::LX_FileBuffer *file)
*   @deprecated The engine will no longer support the display with surfaces
*
*   This function loads a SDL_Surface from a file buffer
*
*   @param file The pointer to a LX_FileBuffer structure
*
*   @return The loaded and optimized surface if there is no problem,
*           a null pointer otherwise
*
*   @note   When this function is called, the format optimization includes
*           the alpha channel.
*           No alpha needs to be set on the surface after that.
*
*/
SDL_Surface * loadSurfaceFromFileBuffer(LX_FileIO::LX_FileBuffer *file);

/**
*   @fn SDL_Surface * optimizeSurface(SDL_Surface * surface)
*   @deprecated The engine will no longer support the display with surfaces
*
*   Optimize the surface format
*
*   @param surface The surface to optimize
*
*   @return A valid poinetr to the optimized surface on success.
*           a null pointer on error or if the surface is not valid.
*
*   @note   The surface is automatically freed and become invalid.
*
*   @sa loadSurface
*   @sa loadSurfaceFromFileBuffer
*/
SDL_Surface * optimizeSurface(SDL_Surface * surface);

/**
*   @fn SDL_Texture * loadTextureFromSurface(SDL_Surface *target, LX_Win::LX_Window * w)
*
*   Load a texture from a surface using the renderer of the window
*
*   @param target The surface to create the texture from
*   @param w The window context
*
*   @return A new pointer to the texture if the loading is successful,
*           a null pointer otherwise
*
*   @sa loadTextureFromFile
*/
SDL_Texture * loadTextureFromSurface(SDL_Surface *target, LX_Win::LX_Window * w);

/**
*   @fn SDL_Texture * loadTextureFromSurface(SDL_Surface *target, unsigned int id)
*   @deprecated The engine will no longer support the display with surfaces
*
*   Load a texture from a surface using the renderer of the window
*   specified by its ID
*
*   @param target The surface to create the texture from
*   @param id The ID of the window that provide the rendering context
*
*   @return A new pointer to the texture if the loading is successful,
*           a null pointer otherwise
*
*   @note   If id is not given as argument to the function,
*            the default argument is used, that is to say 0
*
*   @sa loadTextureFromFile
*/
SDL_Texture * loadTextureFromSurface(SDL_Surface *target, unsigned int id = 0);

/**
*   @fn SDL_Texture * loadTextureFromFile(const std::string& filename, LX_Win::LX_Window * w)
*
*   Load a texture from a surface using the renderer of the window
*
*   @param filename The name of the file to create the texture from
*   @param w The window that provide the rendering context to create the texture
*
*   @return A pointer to a SDL_Texture if the loading works,
*           a null pointer otherwise
*
*   @sa loadTextureFromSurface
*/
SDL_Texture * loadTextureFromFile(const std::string& filename, LX_Win::LX_Window * w);

/**
*   @fn SDL_Texture * loadTextureFromFile(const UTF8string& filename, LX_Win::LX_Window * w)
*
*   Load a texture from a surface using the renderer of the window
*
*   @param filename The name of the file to create the texture from
*   @param w The window that provide the rendering context to create the texture
*
*   @return A pointer to a SDL_Texture if the loading works,
*           a null pointer otherwise
*
*   @note The string given in argument is utf-8 encoded
*   @sa loadTextureFromSurface
*/
SDL_Texture * loadTextureFromFile(const UTF8string& filename, LX_Win::LX_Window * w);

/**
*   @fn SDL_Texture * loadTextureFromFile(const std::string& filename, unsigned int id)
*
*   Load a new texture from a file using the renderer of the window
*   specified by its ID
*
*   @param filename The name of the file to create the texture from
*   @param id The ID of the window that provide the rendering context
*
*   @return A pointer to a SDL_Texture if the loading works,
*           a null pointer otherwise
*
*   @note   If id is not given as argument to the function,
*            the default argument is used, that is to say 0
*
*   @sa loadTextureFromSurface
*/
SDL_Texture * loadTextureFromFile(const std::string& filename, unsigned int id = 0);

/**
*   @fn SDL_Texture * loadTextureFromFile(const UTF8string& filename, unsigned int id)
*
*   Load a new texture from a file using the renderer of the window
*   specified by its ID
*
*   @param filename The name of the file to create the texture from
*   @param id The ID of the window that provide the rendering context
*
*   @return A pointer to a SDL_Texture if the loading works,
*           a null pointer otherwise
*
*   @note   If id is not given as argument to the function,
*           the default argument is used, that is to say 0
*
*   @note The string given in argument is utf-8 encoded
*   @sa loadTextureFromSurface
*/
SDL_Texture * loadTextureFromFile(const UTF8string& filename, unsigned int id = 0);

/**
*   @fn bool setAlpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue)
*   @deprecated The engine will no longer support the display with surfaces
*   This function set the alpha value on a SDL_surface
*
*   @param image The surface
*   @param red The the red component of the future transparent color
*   @param green The the green component of the future transparent color
*   @param blue The the blue component of the future transparent color
*
*   @return TRUE If the transparency was done without problem, FALSE otherwise
*
*   @note You can use any format for values (hexadecimal, digital,...).
*
*/
bool setAlpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue);

};

#endif // LX_GRAPHICS_H_INCLUDED
