
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

#ifndef LX_FORMAT_H_INCLUDED
#define LX_FORMAT_H_INCLUDED

/**
*   @file Format.hpp
*   @brief The Format
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <SDL2/SDL_pixels.h>


namespace LX_Graphics
{

/**
*   @enum LX_PixelFormat
*   @brief Enumerate values related to the pixel format
*/
enum class LX_PixelFormat
{
    UNKNOWN     = SDL_PIXELFORMAT_UNKNOWN,
    INDEX1LSB   = SDL_PIXELFORMAT_INDEX1LSB,
    INDEX1MSB   = SDL_PIXELFORMAT_INDEX1MSB,
    INDEX4LSB   = SDL_PIXELFORMAT_INDEX4LSB,
    INDEX4MSB   = SDL_PIXELFORMAT_INDEX4MSB,
    INDEX8      = SDL_PIXELFORMAT_INDEX8,
    RGB332      = SDL_PIXELFORMAT_RGB332,   /**<  RGB: 2 bit for blue, 3 bits for the others  */
    RGB444      = SDL_PIXELFORMAT_RGB444,   /**<         RGB : 4 bits per channel             */
    RGB555      = SDL_PIXELFORMAT_RGB555,   /**<         RGB : 5 bits per channel             */
    BGR555      = SDL_PIXELFORMAT_BGR555,   /**<         BGR : 5 bits per channel             */
    ARGB4444    = SDL_PIXELFORMAT_ARGB4444, /**<         ARGB : 4 bits per channel            */
    RGBA4444    = SDL_PIXELFORMAT_RGBA4444, /**<         RGBA : 4 bits per channel            */
    ABGR4444    = SDL_PIXELFORMAT_ABGR4444, /**<         ABGR : 4 bits per channel            */
    BGRA4444    = SDL_PIXELFORMAT_BGRA4444, /**<         BGRA : 4 bits per channel            */
    ARGB1555    = SDL_PIXELFORMAT_ARGB1555, /**< ARGB: 1 bit for alpha, 5 bits for the others */
    RGBA5551    = SDL_PIXELFORMAT_RGBA5551, /**< RGBA: 1 bit for alpha, 5 bits for the others */
    ABGR1555    = SDL_PIXELFORMAT_ABGR1555, /**< ABGR: 1 bit for alpha, 5 bits for the others */
    BGRA5551    = SDL_PIXELFORMAT_BGRA5551, /**< BGRA: 1 bit for alpha, 5 bits for the others */
    RGB565      = SDL_PIXELFORMAT_RGB565,   /**< RGB: 6 bits for green, 5 bits for the others */
    BGR565      = SDL_PIXELFORMAT_BGR565,   /**< BGR: 6 bits for green, 5 bits for the others */
    RGB24       = SDL_PIXELFORMAT_RGB24,
    BGR24       = SDL_PIXELFORMAT_BGR24,
    RGB888      = SDL_PIXELFORMAT_RGB888,   /**<          RGB: 8 bits per channel             */
    RGBX8888    = SDL_PIXELFORMAT_RGBX8888, /**<          RGBX: 8 bits per channel            */
    BGR888      = SDL_PIXELFORMAT_BGR888,   /**<          BGR: 8 bits per channel             */
    BGRX8888    = SDL_PIXELFORMAT_BGRX8888, /**<          BGRX: 8 bits per channel            */
    ARGB8888    = SDL_PIXELFORMAT_ARGB8888, /**<          ARGB: 8 bits per channel            */
    RGBA8888    = SDL_PIXELFORMAT_RGBA8888, /**<          RGBA: 8 bits per channel            */
    ABGR8888    = SDL_PIXELFORMAT_ABGR8888, /**<          ABGR: 8 bits per channel            */
    BGRA8888    = SDL_PIXELFORMAT_BGRA8888, /**<          BGRA: 8 bits per channel            */
    ARGB2101010 = SDL_PIXELFORMAT_ARGB2101010,
    YV12        = SDL_PIXELFORMAT_YV12,     /**<      planar mode: Y + V + U (3 planes)       */
    IYUV        = SDL_PIXELFORMAT_IYUV,     /**<      planar mode: Y + U + V (3 planes)       */
    YUY2        = SDL_PIXELFORMAT_YUY2,     /**<      packed mode: Y0+U0+Y1+V0 (1 plane)      */
    UYVY        = SDL_PIXELFORMAT_UYVY,     /**<      packed mode: U0+Y0+V0+Y1 (1 plane)      */
    YVYU        = SDL_PIXELFORMAT_YVYU      /**<      packed mode: Y0+V0+Y1+U0 (1 plane)      */
};

}

#endif  // LX_IMAGE_H_INCLUDED
