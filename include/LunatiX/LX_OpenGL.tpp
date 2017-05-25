
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#include <SDL2/SDL_video.h>

namespace LX_Graphics
{
namespace LX_OpenGL
{

template<typename T>
T getProcAddress(const std::string proc)
{
    T t = (T) SDL_GL_GetProcAddress(proc.c_str());
    return t;
}

}
}
