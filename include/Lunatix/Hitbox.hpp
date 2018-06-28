
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

#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED

/**
*   @file Hitbox.hpp
*   @brief The hitbox library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/Vector2D.hpp>


namespace lx
{

namespace Graphics
{
struct ImgCoord;
struct ImgRect;
}


namespace Physics
{

/**
*   @struct FloatPosition
*   @brief The position in floating-point value
*/
struct FloatPosition final
{
    Float x;    /**< X coordinates  */
    Float y;    /**< Y coordinates  */
};

/**
*   @struct FloatingBox
*   @brief The logical hitbox (Axis-Aligned Bounding Box)
*
*   @note If you want to use an Oriented Bounding Box (OBB),
*         you need to use Polygon instead
*/
struct FloatingBox final
{
    FloatPosition p;         /**< Position   */
    int w;                      /**< Width      */
    int h;                      /**< Height     */
};


/**
*   @fn FloatPosition toFloatPosition(const lx::Graphics::ImgCoord& coord) noexcept
*   @param coord
*   @return The float position
*/
FloatPosition toFloatPosition( const lx::Graphics::ImgCoord& coord ) noexcept;
/**
*   @fn FloatingBox toFloatingBox(const lx::Graphics::ImgRect& rect) noexcept
*   @param rect
*   @return The floating box
*/
FloatingBox toFloatingBox( const lx::Graphics::ImgRect& rect ) noexcept;

/**
*   @struct Segment
*   @brief The segment
*
*   @note If you want to use an inifinite line, use Line instead
*/
struct Segment final
{
    FloatPosition p;     /**< First point    */
    FloatPosition q;     /**< Second point   */
};

/**
*   @struct Line
*   @brief The line
*/
struct Line final
{
    FloatPosition o; /**< Origin point       */
    Vector2D v;      /**< Direction vector   */

    /**
    *   @fn bool isParralelWith(const Line& l) const noexcept
    *
    *   @param [in] l The line to compare
    *   @return TRUE if the two lines are parralel, FALSE otherwise
    */
    bool isParralelWith( const Line& l ) const noexcept;
    /**
    *   @fn bool isPerpendicularTo(const Line& l) const noexcept
    *
    *   @param [in] l The line to compare
    *   @return TRUE if the two lines are perpendicular, FALSE otherwise
    */
    bool isPerpendicularTo( const Line& l ) const noexcept;
};


/**
*   @struct Circle
*   @brief The circle structure
*/
struct Circle final
{
    FloatPosition center;    /**< The point that represents the center   */
    unsigned int radius;        /**< The circle radius                      */
};


// Operators of points and circles
/**
*   @fn bool operator ==(const FloatPosition& a, const FloatPosition& b) noexcept

*   @param [in] a The first point
*   @param [in] b The second point
*
*   @return TRUE If these points have exactly the same coordinates,
*          FALSE otherwise
*/
bool operator ==( const FloatPosition& a, const FloatPosition& b ) noexcept;
/**
*   @fn bool operator !=(const FloatPosition& a, const FloatPosition& b) noexcept
*
*   @param [in] a The first point
*   @param [in] b The second point
*
*   @return TRUE If these points have not the same coordinates, FALSE otherwise
*/
bool operator !=( const FloatPosition& a, const FloatPosition& b ) noexcept;
/**
*   @fn bool operator ==(const Circle& a, const Circle& b) noexcept
*
*   Check If two circles are exactly identical (same coordinates and same radius)
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If these circles are idendital, FALSE otherwise
*/
bool operator ==( const Circle& a, const Circle& b ) noexcept;
/**
*   @fn bool operator !=(const Circle& a, const Circle& b) noexcept
*
*   Check If two circles are exactly identical (same coordinates and same radius)
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If these circles are idendital, FALSE otherwise
*/
bool operator !=( const Circle& a, const Circle& b ) noexcept;
/**
*   @fn bool operator >(const Circle& a, const Circle& b) noexcept
*
*   Check If the first circle has a greater radius than the second one
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If the first circle is greater than the second circle,
*          FALSE otherwise
*/
bool operator >( const Circle& a, const Circle& b ) noexcept;
/**
*   @fn bool operator <(const Circle& a, const Circle& b) noexcept
*
*   Check If the first circle radius is smaller than the second one
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If the first circle is smaller than the second circle,
*          FALSE otherwise
*/
bool operator <( const Circle& a, const Circle& b ) noexcept;
/**
*   @fn bool operator >=(const Circle& a, const Circle& b) noexcept
*
*   Check If the first circle has a greater radius than the second one
*   or if they have the same radius length
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If the first circle is greater than the second circle,
*          or if have the same radius length, FALSE otherwise
*
*/
bool operator >=( const Circle& a, const Circle& b ) noexcept;
/**
*   @fn bool operator <=(const Circle& a, const Circle& b) noexcept
*
*   Check If the first circle radius is smaller than the second one
*   or if they have the same radius length
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If the first circle is smaller than the second circle,
*          or if the two circles have the same radius length, FALSE otherwise
*/
bool operator <=( const Circle& a, const Circle& b ) noexcept;

}   // Physics

}   // lx

#endif // HITBOX_H_INCLUDED
