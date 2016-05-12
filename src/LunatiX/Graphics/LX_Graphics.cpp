

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
*	@file LX_Graphics.cpp
*	@brief The implementation of the graphics engine
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.7
*
*/


#include <string>
#include <SDL2/SDL_image.h>

#include <LunatiX/LX_Graphics.hpp>
#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_WindowManager.hpp>
#include <LunatiX/LX_FileIO.hpp>
#include <LunatiX/LX_FileBuffer.hpp>
#include <LunatiX/LX_Error.hpp>

using namespace LX_FileIO;
using namespace LX_Win;

namespace LX_Graphics
{


/**
*   @fn SDL_Surface * loadSurface(std::string filename)
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
SDL_Surface * loadSurface(std::string filename)
{
    SDL_Surface *loaded = IMG_Load(filename.c_str());
    SDL_Surface *optimized = optimizeSurface(loaded);
    SDL_FreeSurface(loaded);

    return optimized;
}


/**
*   @fn SDL_Surface * loadSurface(LX_File *file)
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
SDL_Surface * loadSurface(LX_File *file)
{
    if(file == nullptr)
    {
        LX_SetError("Invalid pointer : nullptr reference of LX_File\n");
        return nullptr;
    }

    SDL_Surface * surface = file->getSurfaceFromData();
    SDL_Surface *optimized = optimizeSurface(surface);
    SDL_FreeSurface(surface);

    return optimized;
}


/**
*   @fn SDL_Surface * loadSurfaceFromFileBuffer(LX_FileBuffer *file)
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
SDL_Surface * loadSurfaceFromFileBuffer(LX_FileBuffer *file)
{
    if(file == nullptr)
    {
        LX_SetError("Invalid pointer : nullptr reference of LX_FileBuffer\n");
        return nullptr;
    }

    SDL_Surface * surface = file->getSurfaceFromBuffer();
    SDL_Surface *optimized = optimizeSurface(surface);
    SDL_FreeSurface(surface);

    return optimized;
}



/**
*   @fn SDL_Surface * optimizeSurface(SDL_Surface * surface)
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
SDL_Surface * optimizeSurface(SDL_Surface * surface)
{
    SDL_Surface * optimized = nullptr;

    if(surface == nullptr)
    {
        LX_SetError("Invalid pointer : invalid surface\n");
        return nullptr;
    }

    optimized = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_RGBA4444,0x00000000);

    return optimized;
}



/**
*   @fn SDL_Texture * loadTextureFromSurface(SDL_Surface *target, LX_Window * w)
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
SDL_Texture * loadTextureFromSurface(SDL_Surface *target, LX_Window * w)
{
    return SDL_CreateTextureFromSurface(w->getRenderer(),target);
}



/**
*   @fn SDL_Texture * loadTextureFromSurface(SDL_Surface *target, unsigned int id)
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
SDL_Texture * loadTextureFromSurface(SDL_Surface *target, unsigned int id)
{
    LX_Window *tmp = nullptr;

    tmp = LX_WindowManager::getInstance()->getWindow(id);

    if(tmp == nullptr)
    {
        LX_SetError("LX_Graphics::loadTextureFromSurface - invalid window");
        return nullptr;
    }

    return SDL_CreateTextureFromSurface(tmp->getRenderer(),target);
}


/**
*   @fn SDL_Texture * loadTextureFromFile(const std::string filename, unsigned int id)
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
SDL_Texture * loadTextureFromFile(const std::string filename, unsigned int id)
{
    SDL_Surface *tmpS = nullptr;
    SDL_Texture *tmpT = nullptr;

    tmpS = loadSurface(filename.c_str());

    if(tmpS == nullptr)
        return nullptr;

    tmpT = loadTextureFromSurface(tmpS,id);
    SDL_FreeSurface(tmpS);

    return tmpT;
}


/**
*   @fn SDL_Texture * loadTextureFromFile(const std::string filename, LX_Window * w)
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
SDL_Texture * loadTextureFromFile(const std::string filename, LX_Window * w)
{
    SDL_Surface *tmpS = nullptr;
    SDL_Texture *tmpT = nullptr;

    tmpS = loadSurface(filename.c_str());

    if(tmpS == nullptr)
        return nullptr;

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

