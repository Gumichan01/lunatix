

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
*	@file LX_TrueTypeFont.cpp
*	@brief The LunatiX Engine graphic module
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date January 28th, 2015
*
*/

#include <iostream>
#include <string>

#include <SDL2/SDL_image.h>

#include "LX_Graphics.hpp"
#include "LX_Window.hpp"
#include "LX_WindowManager.hpp"


/**
*   @namespace LX_Graphics
*
*   @brief The graphics module
*
*/
namespace LX_Graphics{


    /**
    *   @fn SDL_Surface * loadSurface(std::string filename)
    *
    *   This function loads an SDL_Surface from any image file an optimized its format
    *
    *   @param filename : the file name which describe the image
    *
    *   @return the loaded and optimized surface if there is no problem, NULL otherwise
    *
    *   @note You may use this function instead of load_surfaceFromBMP() to load a non .bmp file
    *   @note If you want to load a .bmp file and use the transparency,
    *           please use load_surfaceFromBMP and set_alpha()
    *
    *   @warning When you call this function, the format optimization includes the alpha canal.
    *               No alpha needs to be set on the surface after that, except if you want to modify it
    *
    */
    SDL_Surface * loadSurface(std::string filename)
    {
        SDL_Surface *loaded = NULL;
        SDL_Surface *optimized = NULL;

        loaded = IMG_Load(filename.c_str());

        if(loaded == NULL)
        {
            return NULL;
        }

        optimized = SDL_ConvertSurfaceFormat(loaded,SDL_PIXELFORMAT_RGBA4444,0x00000000);

        SDL_FreeSurface(loaded);

        return optimized;
    }


    /**
    *   @fn SDL_Texture * loadTextureFromSurface(SDL_Surface *target, int id)
    *
    *   Loads create a texture from a surface
    *
    *   @param target : the surface you want to use to create the texture
    *   @param id : The ID of the window you create your texture from
    *
    *   @return  a new pointer to the texture if the loading is successful, NULL otherwise
    *
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
    *   Load a new texture from a file
    *
    *   @param filename : the name of the file you need to use for the texture creation
    *   @param id : The ID of the window you create your texture from
    *
    *   @return a pointer to a SDL_Texture if the loading works, NULL otherwise
    *
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
    *
    *   @fn bool set_alpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue)
    *
    *   This function set the alpha value on a SDL_surface
    *
    *   @param image : the surface
    *   @param red : the the red color canal of the future transparent color
    *   @param green : the the green color canal of the future transparent color
    *   @param blue : the the blue color canal of the future transparent color
    *
    *   @return TRUE if the transparency was done without problem, FALSE otherwise
    *
    *   @note You may use any format for values (hexadecimal, digital,...).
    *
    */
    bool set_alpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue)
    {
        if(SDL_SetColorKey(image,SDL_TRUE, SDL_MapRGB(image->format,red,green,blue)) == -1)
            return false;

        return true;
    }

};


















