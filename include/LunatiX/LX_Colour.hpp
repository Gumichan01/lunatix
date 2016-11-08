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
*    @version 0.9
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
*       ⇒ LX_Colour: { r = 255, g = 165, b = 0, a = 255 }
*
*   Orange (hexadecimal value)
*
*       #FFA500
*       ⇒ LX_Colour: { r = 0xFF, g = 0xA5, b = 0x00, a = 0xFF }
*/
using LX_Colour = SDL_Colour;

/**
*   @struct LX_glColour
*   @brief Colour representation (in OpenGL format)
*
*   This representation defines the colour as three floating-point values
*   between 0.0 and 1.0
*
*   Examples:
*
*   Orange colour
*
*       ⇒ LX_Colour: { r = 1.0f, g = 0.647058f, b = 1.0f, a = 1.0f }
*
*/
struct LX_glColour
{
    float r;    /**< Red      */
    float g;    /**< Green    */
    float b;    /**< Blue     */
    float a;    /**< Alpha    */
};


/**
*   @fn inline LX_glColour from8BitColor(const LX_Colour& colour)
*
*   Convert a colour in 8-bit notation to a colour in floating-point notation
*
*   @param [in] colour Colour in 8-bit notation
*   @return The colour in floating-point notation
*
*   @note This function is very useful when the program uses colours in OpenGL
*   representation (floating-point)
*
*   @sa fromGLColor
*/
inline LX_glColour from8BitColor(const LX_Colour& colour)
{
    const float M = 255.0f;  // Max 8-it colour
    LX_glColour c = {static_cast<float>(colour.r) / M,
                     static_cast<float>(colour.g) / M,
                     static_cast<float>(colour.b) / M,
                     static_cast<float>(colour.a) / M
                    };
    return c;
}
/**
*   @fn inline LX_Colour fromGLColor(const LX_glColour& colour)
*
*   Convert a colour in floating-point notation to a colour in 8-bit notation
*
*   @param [in] colour Colour floating-point notation
*   @return The colour in 8-bit notation
*
*   @note This function is very useful when the program uses colours in OpenGL
*   representation (floating-point)
*
*   @sa from8BitColor
*/
inline LX_Colour fromGLColor(const LX_glColour& colour)
{
    const float N = 255.0f;
    LX_Colour c = {static_cast<uint8_t>(colour.r * N),
                   static_cast<uint8_t>(colour.g * N),
                   static_cast<uint8_t>(colour.b * N),
                   static_cast<uint8_t>(colour.a * N)
                  };

    return c;
}

/**
*   @fn inline uint32_t toRGBAvalue(const LX_Colour& colour)
*
*   Get the colour value in one unsigned integer value
*
*   @param [in] colour Colour in 8-bit notation
*   @return The colour in RGBA notation in one integer value
*/
inline uint32_t toRGBAvalue(const LX_Colour& colour)
{
    uint32_t rvalue = colour.r;
    uint32_t gvalue = colour.g;
    uint32_t bvalue = colour.b;
    uint32_t avalue = colour.a;

    return (rvalue << 24) | (gvalue << 16) | (bvalue << 8) | avalue;
}
/**
*   @fn inline LX_Colour fromRGBAvalue(const uint32_t rgba)
*
*   Get the colour structure from an integer value
*
*   @param [in] rgba The color in one unsignd interger value
*   @return The colour structure
*/
inline LX_Colour fromRGBAvalue(const uint32_t rgba)
{
    uint8_t r = (rgba >> 24) & 0x000000FF;
    uint8_t g = (rgba >> 16) & 0x000000FF;
    uint8_t b = (rgba >> 8) & 0x000000FF;
    uint8_t a = rgba & 0x000000FF;

    return LX_Colour {r,g,b,a};
}


#endif // LX_COLOUR_HPP_INCLUDED
