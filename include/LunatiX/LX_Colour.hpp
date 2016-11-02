#ifndef LX_COLOUR_HPP_INCLUDED
#define LX_COLOUR_HPP_INCLUDED


/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_Colour.hpp
*    @brief The colour representation
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <SDL2/SDL_pixels.h>

/**
*   @typedef LX_Colour
*   @brief Colour representation
*
*   Internal structure:
*
*       uint8_t r;
*       uint8_t g;
*       uint8_t b;
*       uint8_t a;  // 255: opaque; 0: transparent
*
*   Examples:
*
*   Orange (decimal value)
*
*       R,G,B: 255,165,0
*       ⇒ LX_Colour: { r=255, g=165, b=0, a=255 }
*
*   Orange (hexadecimal value)
*
*       #FFA500
*       ⇒ LX_Colour: { r=0xFF, g=0xA5, b=0x00, a=0xFF }
*/
using LX_Colour = SDL_Colour;

/// @todo (#5#) Conversion RGBA → colour value
/// @todo (#5#) Conversion colour value → RGBA
/// @todo (#5#) Conversion 8-bit colour value → floating point colour value


#endif // LX_COLOUR_HPP_INCLUDED
