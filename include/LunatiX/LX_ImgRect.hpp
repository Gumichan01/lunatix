
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

#ifndef LX_IMGRECT_H_INCLUDED
#define LX_IMGRECT_H_INCLUDED

/**
*   @file LX_ImgRect.hpp
*   @todo remove this file?
*   @brief The definition of LX_ImgRect
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

// LX_ImgRect is just an alias of SDL_Rect
struct SDL_Rect;
/**
*   @ingroup Graphics
*   @typedef LX_ImgRect
*   @brief The Image box
*
*   This box, defined as an Axis-Aligned Bounding Box (AABB) contains information
*   about the position and the dimension of the image to display
*/
using LX_ImgRect = SDL_Rect;

/// @todo Create an ImgRect from LX_Graphics
/**
    This structure will be used by LX_Texture

    ImgRect
    {
        LX_Point p;
        int w, h;
    }

    + conversion ImgRect → SDL_Rect + vice-versa?
*/

#include <SDL2/SDL_rect.h>

#endif  /* LX_IMGRECT_H_INCLUDED */
