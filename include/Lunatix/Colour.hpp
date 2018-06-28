
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

#ifndef COLOUR_HPP_INCLUDED
#define COLOUR_HPP_INCLUDED

/**
*   @file Colour.hpp
*   @brief The colour representation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <SDL2/SDL_pixels.h>

/**
*   @ingroup Graphics
*   @typedef Colour
*   @brief Colour representation (in 8-bit notation)
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
*       ⇒ Colour: { r = 255, g = 165, b = 0, a = 255 }
*
*   Orange (hexadecimal value)
*
*       #FFA500
*       ⇒ Colour: { r = 0xFF, g = 0xA5, b = 0x00, a = 0xFF }
*/
using Colour = SDL_Colour;

/**
*   @ingroup Graphics
*   @struct glColour
*   @brief Colour representation (in OpenGL format)
*
*   This representation defines the colour as three floating-point values
*   between 0.0 and 1.0
*
*   Examples:
*
*   Orange colour
*
*      ⇒ Colour: { r = 1.0f, g = 0.647058f, b = 1.0f, a = 1.0f }
*
*/
struct glColour final
{
    float r;    /**< Red      */
    float g;    /**< Green    */
    float b;    /**< Blue     */
    float a;    /**< Alpha    */
};


/**
*   @ingroup Graphics
*   @fn inline constexpr bool operator ==(const Colour& a, const Colour& b) noexcept
*
*   Check if two colors are identical
*
*   @param [in] a The colour in 8-bit notation
*   @param [in] b Another colour in 8-bit notation
*   @return TRUE if they are identical, FALSE otherwise
*
*/
inline constexpr bool operator ==( const Colour& a, const Colour& b ) noexcept
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

/**
*   @ingroup Graphics
*   @fn inline constexpr bool operator !=(const Colour& a, const Colour& b) noexcept
*
*   Check if two colors are different
*
*   @param [in] a The colour in 8-bit notation
*   @param [in] b Another colour in 8-bit notation
*   @return TRUE if they are different, FALSE otherwise
*
*/
inline constexpr bool operator !=( const Colour& a, const Colour& b ) noexcept
{
    return !( a == b );
}

/**
*   @ingroup Graphics
*   @fn inline constexpr glColour from8BitColour(const Colour& colour) noexcept
*
*   Convert a colour in 8-bit notation to a colour in floating-point notation
*
*   @param [in] colour Colour in 8-bit notation
*   @return The colour in floating-point notation
*
*   @note This function is very useful when the program uses colours in OpenGL
*   representation (floating-point)
*
*   @sa fromGLColour
*/
inline constexpr glColour from8BitColour( const Colour& colour ) noexcept
{
    // 255.0f is the max Max 8-bit colour
    return glColour{static_cast<float>( colour.r ) / 255.0f,
                       static_cast<float>( colour.g ) / 255.0f,
                       static_cast<float>( colour.b ) / 255.0f,
                       static_cast<float>( colour.a ) / 255.0f
                      };
}
/**
*   @ingroup Graphics
*   @fn inline constexpr Colour fromGLColour(const glColour& colour) noexcept
*
*   Convert a colour in floating-point notation to a colour in 8-bit notation
*
*   @param [in] colour Colour floating-point notation
*   @return The colour in 8-bit notation
*
*   @note This function is very useful when the program uses colours in OpenGL
*   representation (floating-point)
*
*   @sa from8BitColour
*/
inline constexpr Colour fromGLColour( const glColour& colour ) noexcept
{
    // 255.0f is the max Max 8-bit colour
    return Colour{static_cast<uint8_t>( colour.r * 255.0f ),
                     static_cast<uint8_t>( colour.g * 255.0f ),
                     static_cast<uint8_t>( colour.b * 255.0f ),
                     static_cast<uint8_t>( colour.a * 255.0f )
                    };
}

/**
*   @ingroup Graphics
*   @fn inline constexpr uint32_t toRGBAvalue(const Colour& colour) noexcept
*
*   Get the colour value in one unsigned integer value
*
*   @param [in] colour Colour in 8-bit notation
*   @return The colour in RGBA notation in one integer value
*/
inline constexpr uint32_t toRGBAvalue( const Colour& colour ) noexcept
{
    return static_cast<uint32_t>( ( colour.r << 24 ) | ( colour.g << 16 ) |
                                  ( colour.b << 8 ) | colour.a );
}
/**
*   @ingroup Graphics
*   @fn inline Colour fromRGBAvalue(const uint32_t rgba) noexcept
*
*   Get the colour structure from an integer value
*
*   @param [in] rgba The colour in one unsigned integer value
*   @return The colour structure
*/
inline Colour fromRGBAvalue( const uint32_t rgba ) noexcept
{
    const uint8_t r = static_cast<uint8_t>( ( rgba >> 24 ) & 0x000000FF );
    const uint8_t g = static_cast<uint8_t>( ( rgba >> 16 ) & 0x000000FF );
    const uint8_t b = static_cast<uint8_t>( ( rgba >> 8 ) & 0x000000FF );
    const uint8_t a = static_cast<uint8_t>( rgba & 0x000000FF );

    return Colour{r, g, b, a};
}

#endif // COLOUR_HPP_INCLUDED
