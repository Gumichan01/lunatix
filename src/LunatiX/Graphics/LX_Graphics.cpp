

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
*	@version 0.8
*
*/


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

SDL_Surface * loadSurface(const std::string& filename)
{
    SDL_Surface *loaded = IMG_Load(filename.c_str());
    SDL_Surface *optimized = optimizeSurface(loaded);
    SDL_FreeSurface(loaded);

    return optimized;
}

SDL_Surface * loadSurface(const UTF8string& filename)
{
    return loadSurface(filename.utf8_str());
}

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


SDL_Texture * loadTextureFromSurface(SDL_Surface *target, LX_Window * w)
{
    return SDL_CreateTextureFromSurface(w->getRenderer(),target);
}


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


SDL_Texture * loadTextureFromFile(const std::string& filename, LX_Window * w)
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


SDL_Texture * loadTextureFromFile(const UTF8string& filename, LX_Win::LX_Window * w)
{
    return loadTextureFromFile(filename.utf8_str(),w);
}


SDL_Texture * loadTextureFromFile(const std::string& filename, unsigned int id)
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


SDL_Texture * loadTextureFromFile(const UTF8string& filename, unsigned int id)
{
    return loadTextureFromFile(filename.utf8_str(),id);
}


bool setAlpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue)
{
    return SDL_SetColorKey(image,SDL_TRUE, SDL_MapRGB(image->format,red,green,blue)) == 0;
}

};
