
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
*   @file LX_Hitbox.hpp
*   @brief The hitbox library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/LX_ImgRect.hpp>
#include <LunatiX/LX_Vector2D.hpp>
#include <LunatiX/utils/float.hpp>

#include <SDL2/SDL_rect.h>


namespace LX_Physics
{

/**
*   @struct LX_Point
*   @brief The position
*/
struct LX_Point
{
    int x;      /**< X position */
    int y;      /**< Y position */
};

/**
*   @struct LX_FloatPosition
*   @brief The position in floating-point value
*/
struct LX_FloatPosition
{
    Float x;
    Float y;
};

/**
*   @fn LX_Point toPixelPosition(const LX_FloatPosition& p) noexcept
*
*   @param p
*   @return The LX_Point
*/
LX_Point toPixelPosition(const LX_FloatPosition& p) noexcept;

/// @todo conversion LX_FloatingBox → LX_Graphics::ImgRect

/**
*   @struct LX_FloatingBox
*   @brief The logical hitbox (Axis-Aligned Bounding Box)
*
*   @note If you want to use an Oriented Bounding Box (OBB),
*         you need to use ::LX_Polygon instead
*/
struct LX_FloatingBox
{
    LX_FloatPosition fpoint;    /**< Position   */
    int w;                      /**< Width      */
    int h;                      /**< Height     */
};

/**
*   @fn LX_ImgRect toImgRect(const LX_FloatingBox& b) noexcept
*
*   @param b
*   @return The LX_ImgRect
*/
LX_ImgRect toImgRect(const LX_FloatingBox& b) noexcept;

/**
*   @struct LX_Segment
*   @brief The segment
*
*   @note If you want to use an inifinite line, use LX_Line instead
*/
struct LX_Segment
{
    LX_FloatPosition p;
    LX_FloatPosition q;
};

/**
*   @struct LX_Line
*   @brief The line
*/
struct LX_Line
{
    LX_FloatPosition o; /**< Origin point       */
    LX_Vector2D v;      /**< Direction vector   */

    /**
    *   @fn bool isParralelWith(const LX_Line& l) const noexcept
    *
    *   @param [in] l The line to compare
    *   @return TRUE if the two lines are parralel, FALSE otherwise
    */
    bool isParralelWith(const LX_Line& l) const noexcept;
    /**
    *   @fn bool isPerpendicularTo(const LX_Line& l) const noexcept
    *
    *   @param [in] l The line to compare
    *   @return TRUE if the two lines are perpendicular, FALSE otherwise
    */
    bool isPerpendicularTo(const LX_Line& l) const noexcept;
};


/**
*   @struct LX_Circle
*   @brief The circle structure
*/
struct LX_Circle
{
    LX_FloatPosition center;    /**< The point that represents the center   */
    unsigned int radius;        /**< The circle radius                      */
};


// Operators of points and circles
/**
*   @fn bool operator ==(const LX_Point& a, const LX_Point& b) noexcept
*
*   @param [in] a The first point
*   @param [in] b The second point
*
*   @return TRUE If these points have exactly the same coordinates,
*          FALSE otherwise
*/
bool operator ==(const LX_Point& a, const LX_Point& b) noexcept;
/**
*   @fn bool operator !=(const LX_Point& a, const LX_Point& b) noexcept
*
*   @param [in] a The first point
*   @param [in] b The second point
*
*   @return TRUE If these points have not the same coordinates, FALSE otherwise
*/
bool operator !=(const LX_Point& a, const LX_Point& b) noexcept;

/**
*   @fn bool operator ==(const LX_FloatPosition& a, const LX_FloatPosition& b) noexcept

*   @param [in] a The first point
*   @param [in] b The second point
*
*   @return TRUE If these points have exactly the same coordinates,
*          FALSE otherwise
*/
bool operator ==(const LX_FloatPosition& a, const LX_FloatPosition& b) noexcept;
/**
*   @fn bool operator !=(const LX_FloatPosition& a, const LX_FloatPosition& b) noexcept
*
*   @param [in] a The first point
*   @param [in] b The second point
*
*   @return TRUE If these points have not the same coordinates, FALSE otherwise
*/
bool operator !=(const LX_FloatPosition& a, const LX_FloatPosition& b) noexcept;
/**
*   @fn bool operator ==(const LX_Circle& a, const LX_Circle& b) noexcept
*
*   Check If two circles are exactly identical (same coordinates and same radius)
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If these circles are idendital, FALSE otherwise
*/
bool operator ==(const LX_Circle& a, const LX_Circle& b) noexcept;
/**
*   @fn bool operator !=(const LX_Circle& a, const LX_Circle& b) noexcept
*
*   Check If two circles are exactly identical (same coordinates and same radius)
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If these circles are idendital, FALSE otherwise
*/
bool operator !=(const LX_Circle& a, const LX_Circle& b) noexcept;
/**
*   @fn bool operator >(const LX_Circle& a, const LX_Circle& b) noexcept
*
*   Check If the first circle has a greater radius than the second one
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If the first circle is greater than the second circle,
*          FALSE otherwise
*/
bool operator >(const LX_Circle& a, const LX_Circle& b) noexcept;
/**
*   @fn bool operator <(const LX_Circle& a, const LX_Circle& b) noexcept
*
*   Check If the first circle radius is smaller than the second one
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If the first circle is smaller than the second circle,
*          FALSE otherwise
*/
bool operator <(const LX_Circle& a, const LX_Circle& b) noexcept;
/**
*   @fn bool operator >=(const LX_Circle& a, const LX_Circle& b) noexcept
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
bool operator >=(const LX_Circle& a, const LX_Circle& b) noexcept;
/**
*   @fn bool operator <=(const LX_Circle& a, const LX_Circle& b) noexcept
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
bool operator <=(const LX_Circle& a, const LX_Circle& b) noexcept;

}

#endif // HITBOX_H_INCLUDED
