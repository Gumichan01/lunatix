

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Graphics.cpp
*	@brief The implementation of the graphics engine
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/


#include <string>

#include <SDL2/SDL_image.h>

#include "LX_Graphics.hpp"
#include "LX_Window.hpp"
#include "LX_WindowManager.hpp"
#include "LX_Error.hpp"
#include "LX_FileIO.hpp"
#include "LX_FileBuffer.hpp"

using namespace LX_FileIO;

namespace LX_Graphics
{


/**
*   @fn SDL_Surface * loadSurface(std::string filename)
*
*   This function loads a SDL_Surface from any image file an optimized its format
*
*   @param filename The name of the image file
*
*   @return The loaded and optimized surface if there is no problem, NULL otherwise
*
*   @note When you call this function, the format optimization includes the alpha channel.
*               No alpha needs to be set on the surface after that.
*
*   @sa loadSurfaceFromFileBuffer
*/
SDL_Surface * loadSurface(std::string filename)
{
    SDL_Surface *loaded = NULL;

    loaded = IMG_Load(filename.c_str());

    if(loaded == NULL)
    {
        return NULL;
    }

    return optimizeSurface(loaded);
}


/**
*   @fn SDL_Surface * loadSurface(LX_File *file)
*
*   This function loads a SDL_Surface from memory
*
*   @param file The data you want to load the surface from
*
*   @return The loaded and optimized surface if there is no problem, NULL otherwise
*
*   @note When you call this function, the format optimization includes the alpha channel.
*               No alpha needs to be set on the surface after that.
*
*   @sa loadSurfaceFromFileBuffer
*/
SDL_Surface * loadSurface(LX_File *file)
{
    if(file == NULL)
    {
        LX_SetError("Invalid pointer : NULL reference of LX_File\n");
        return NULL;
    }

    return optimizeSurface(file->getSurfaceFromData());
}


/**
*   @fn SDL_Surface * loadSurfaceFromFileBuffer(LX_FileBuffer *file)
*
*   This function loads a SDL_Surface from a file buffer
*
*   @param file The buffer you want to load the surface from
*
*   @return The loaded and optimized surface if there is no problem, NULL otherwise
*
*   @note When you call this function, the format optimization includes the alpha channel.
*               No alpha needs to be set on the surface after that.
*
*/
SDL_Surface * loadSurfaceFromFileBuffer(LX_FileBuffer *file)
{
    if(file == NULL)
    {
        LX_SetError("Invalid pointer : NULL reference of LX_FileBuffer\n");
        return NULL;
    }

    return optimizeSurface(file->getSurfaceFromBuffer());
}



/**
*   @fn SDL_Surface * optimizeSurface(SDL_Surface * surface)
*
*   Optimize the surface format
*
*   @param surface The surface to optimize
*
*   @return A valid poinetr to the optimized surface on success.
*           NULL on error or if the surface is NULL.
*
*   @note The function frees the surface if it is not NULL.
*           So the surface becomes invalid.
*
*   @sa loadSurface
*   @sa loadSurfaceFromFileBuffer
*/
SDL_Surface * optimizeSurface(SDL_Surface * surface)
{
    SDL_Surface * optimized = NULL;

    if(surface == NULL)
    {
        LX_SetError("Invalid pointer : NULL surface\n");
        return NULL;
    }

    optimized = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_RGBA4444,0x00000000);
    SDL_FreeSurface(surface);
    surface = NULL;

    return optimized;
}



/**
*   @fn SDL_Texture * loadTextureFromSurface(SDL_Surface *target, LX_Window * w)
*
*   Loads create a texture from a surface using the renderer of the window
*
*   @param target The surface you want to use to create the texture
*   @param w The window you create your texture from
*
*   @return A new pointer to the texture if the loading is successful, NULL otherwise
*
*   @sa loadTextureFromFile
*/
SDL_Texture * loadTextureFromSurface(SDL_Surface *target, LX_Window * w)
{
    return SDL_CreateTextureFromSurface(w->getRenderer(),target);
}



/**
*   @fn SDL_Texture * loadTextureFromSurface(SDL_Surface *target, int id)
*
*   Loads create a texture from a surface using the renderer of the window
*   specified by its ID
*
*   @param target The surface you want to use to create the texture
*   @param id The ID of the window renderer you create your texture from
*
*   @return A new pointer to the texture if the loading is successful, NULL otherwise
*
*   @sa loadTextureFromFile
*/
SDL_Texture * loadTextureFromSurface(SDL_Surface *target, int id)
{
    LX_Window *tmp = NULL;

    if(id < 0)
        return NULL;

    tmp = LX_WindowManager::getInstance()->getWindow(id);

    if(tmp == NULL)
        return NULL;

    return SDL_CreateTextureFromSurface(tmp->getRenderer(),target);
}


/**
*   @fn SDL_Texture * loadTextureFromFile(std::string filename, int id)
*
*   Load a new texture from a file using the renderer of the window
*   specified by its ID
*
*   @param filename The name of the file you need to use for the texture creation
*   @param id The ID of the window renderer you create your texture from
*
*   @return A pointer to a SDL_Texture if the loading works, NULL otherwise
*
*   @sa loadTextureFromSurface
*/
SDL_Texture * loadTextureFromFile(std::string filename, int id)
{
    SDL_Surface *tmpS = NULL;
    SDL_Texture *tmpT = NULL;

    tmpS = loadSurface(filename.c_str());

    if(tmpS == NULL)
    {
        return NULL;
    }

    tmpT = loadTextureFromSurface(tmpS,id);

    SDL_FreeSurface(tmpS);

    return tmpT;
}


/**
*   @fn SDL_Texture * loadTextureFromFile(std::string filename, LX_Window * w)
*
*   Loads create a texture from a surface using the renderer of the window
*
*   @param filename The name of the file you need to use for the texture creation
*   @param w The window renderer you create your texture from
*
*   @return A pointer to a SDL_Texture if the loading works, NULL otherwise
*
*   @sa loadTextureFromSurface
*/
SDL_Texture * loadTextureFromFile(std::string filename, LX_Window * w)
{
    SDL_Surface *tmpS = NULL;
    SDL_Texture *tmpT = NULL;

    tmpS = loadSurface(filename.c_str());

    if(tmpS == NULL)
    {
        return NULL;
    }

    tmpT = loadTextureFromSurface(tmpS,w);

    SDL_FreeSurface(tmpS);

    return tmpT;
}

/**
*
*   @fn bool setAlpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue)
*
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
bool setAlpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue)
{
    return (SDL_SetColorKey(image,SDL_TRUE, SDL_MapRGB(image->format,red,green,blue)) == 0);
}

};


