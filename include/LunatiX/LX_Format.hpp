
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

#include <SDL2/SDL_pixels.h>

enum class LX_PIXELFORMAT : SDL_PixelFormatEnum
{
    LX_PIXELFORMAT_UNKNOWN = SDL_PIXELFORMAT_UNKNOWN,
    LX_PIXELFORMAT_INDEX1LSB = SDL_PIXELFORMAT_INDEX1LSB,
    LX_PIXELFORMAT_INDEX1MSB = SDL_PIXELFORMAT_INDEX1MSB,
    LX_PIXELFORMAT_INDEX4LSB = SDL_PIXELFORMAT_INDEX4LSB,
    LX_PIXELFORMAT_INDEX4MSB = SDL_PIXELFORMAT_INDEX4MSB,
    LX_PIXELFORMAT_INDEX8 = SDL_PIXELFORMAT_INDEX8,
    LX_PIXELFORMAT_RGB332 = SDL_PIXELFORMAT_RGB332,
    LX_PIXELFORMAT_RGB444 = SDL_PIXELFORMAT_RGB444,
    LX_PIXELFORMAT_RGB555 = SDL_PIXELFORMAT_RGB555,
    LX_PIXELFORMAT_BGR555 = SDL_PIXELFORMAT_BGR555,
    LX_PIXELFORMAT_ARGB4444 = SDL_PIXELFORMAT_ARGB4444,
    LX_PIXELFORMAT_RGBA4444 = SDL_PIXELFORMAT_RGBA4444,
    LX_PIXELFORMAT_ABGR4444 = SDL_PIXELFORMAT_ABGR4444,
    LX_PIXELFORMAT_BGRA4444 = SDL_PIXELFORMAT_BGRA4444,
    LX_PIXELFORMAT_ARGB1555 = SDL_PIXELFORMAT_ARGB1555,
    LX_PIXELFORMAT_RGBA5551 = SDL_PIXELFORMAT_RGBA5551,
    LX_PIXELFORMAT_ABGR1555 = SDL_PIXELFORMAT_ABGR1555,
    LX_PIXELFORMAT_BGRA5551 = SDL_PIXELFORMAT_BGRA5551,
    LX_PIXELFORMAT_RGB565 = SDL_PIXELFORMAT_RGB565,
    LX_PIXELFORMAT_BGR565 = SDL_PIXELFORMAT_BGR565,
    LX_PIXELFORMAT_RGB24 = SDL_PIXELFORMAT_RGB24,
    LX_PIXELFORMAT_BGR24 = SDL_PIXELFORMAT_BGR24,
    LX_PIXELFORMAT_RGB888 = SDL_PIXELFORMAT_RGB888,
    LX_PIXELFORMAT_RGBX8888 = SDL_PIXELFORMAT_RGBX8888,
    LX_PIXELFORMAT_BGR888 = SDL_PIXELFORMAT_BGR888,
    LX_PIXELFORMAT_BGRX8888 = SDL_PIXELFORMAT_BGRX8888,
    LX_PIXELFORMAT_ARGB8888 = SDL_PIXELFORMAT_ARGB8888,
    LX_PIXELFORMAT_RGBA8888 = SDL_PIXELFORMAT_RGBA8888,
    LX_PIXELFORMAT_ABGR8888 = SDL_PIXELFORMAT_ABGR8888,
    LX_PIXELFORMAT_BGRA8888 = SDL_PIXELFORMAT_BGRA8888,
    LX_PIXELFORMAT_ARGB2101010 = SDL_PIXELFORMAT_ARGB2101010,
    LX_PIXELFORMAT_YV12 = SDL_PIXELFORMAT_YV12,
    LX_PIXELFORMAT_IYUV = SDL_PIXELFORMAT_IYUV,
    LX_PIXELFORMAT_YUY2 = SDL_PIXELFORMAT_YUY2,
    LX_PIXELFORMAT_UYVY = SDL_PIXELFORMAT_UYVY,
    LX_PIXELFORMAT_YVYU = SDL_PIXELFORMAT_YVYU,
};

