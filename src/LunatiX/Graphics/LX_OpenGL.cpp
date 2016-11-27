

/*
*   Copyright (C) 2016 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file LX_OpenGL.cpp
*   @brief The implementation of the LunatiX/OpenGL interface
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.9
*
*/

#include <LunatiX/LX_OpenGL.hpp>
#include <SDL2/SDL_render.h>

namespace LX_Graphics
{

namespace LX_OpenGL
{

bool extensionSupported(std::string extension)
{
    return SDL_GL_ExtensionSupported(extension.c_str());
}


bool loadDefaultLibrary()
{
    return SDL_GL_LoadLibrary(nullptr) == 0;
}


bool loadLibrary(std::string path)
{
    return SDL_GL_LoadLibrary(path.c_str()) == 0;
}


void UnloadLibrary()
{
    SDL_GL_UnloadLibrary();
}


LX_GLContext getCurrentContext()
{
    return SDL_GL_GetCurrentContext();
}


int getSwapInterval()
{
    return SDL_GL_GetSwapInterval();
}


bool setSwapInterval(int interval)
{
    return SDL_GL_SetSwapInterval(interval) == 0;
}


bool getAttribute(LX_GLattr attr, int& value)
{
    return SDL_GL_GetAttribute(attr,&value) == 0;
}


bool setAttribute(LX_GLattr attr, int value)
{
    return SDL_GL_SetAttribute(attr,value) == 0;
}

};

};
