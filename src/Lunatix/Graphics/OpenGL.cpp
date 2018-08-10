

/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file OpenGL.cpp
*   @brief The implementation of the Lunatix/OpenGL interface
*   @author Luxon Jean-Pierre(Gumichan01)
*/

#include <Lunatix/OpenGL.hpp>
#include <SDL2/SDL_render.h>

namespace lx
{

namespace Graphics
{

namespace OpenGL
{

bool extensionSupported( std::string extension ) noexcept
{
    return SDL_GL_ExtensionSupported( extension.c_str() );
}


bool loadDefaultLibrary() noexcept
{
    return SDL_GL_LoadLibrary( nullptr ) == 0;
}


bool loadLibrary( std::string path ) noexcept
{
    return SDL_GL_LoadLibrary( path.c_str() ) == 0;
}


void UnloadLibrary() noexcept
{
    SDL_GL_UnloadLibrary();
}


GLContext getCurrentContext() noexcept
{
    return SDL_GL_GetCurrentContext();
}


GL_SwapInterval getSwapInterval() noexcept
{
    int tmp = SDL_GL_GetSwapInterval();

    return tmp == -1 ? GL_SwapInterval::NOT_SUPPORTED :
           static_cast<GL_SwapInterval>( tmp );
}


bool setSwapInterval( const GL_SwapInterval& interval ) noexcept
{
    return SDL_GL_SetSwapInterval( static_cast<int>( interval ) ) == 0;
}


bool getAttribute( GLattr attr, int& value ) noexcept
{
    return SDL_GL_GetAttribute( attr, &value ) == 0;
}


bool setAttribute( GLattr attr, int value ) noexcept
{
    return SDL_GL_SetAttribute( attr, value ) == 0;
}

}   // OpenGL

}   // Graphics

}   // lx
