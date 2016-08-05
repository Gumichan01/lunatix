
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

#include <SDL2/SDL_video.h>

namespace LX_Graphics
{
namespace LX_OpenGL
{

template<typename T>
T getProcAddress(std::string proc)
{
    T t = (T) SDL_GL_GetProcAddress(proc.c_str());
    return t;
}

};

};
