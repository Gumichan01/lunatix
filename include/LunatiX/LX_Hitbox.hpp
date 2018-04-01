
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

#include <LunatiX/LX_Vector2D.hpp>

namespace LX_Graphics
{
struct LX_ImgCoord;
struct LX_ImgRect;
}

namespace LX_Physics
{

/**
*   @struct LX_FloatPosition final
*   @brief The position in floating-point value
*/
struct LX_FloatPosition final
{
    Float x = FloatBox::FNIL;   /**< X coordinates  */
    Float y = FloatBox::FNIL;   /**< Y coordinates  */
};

/**
*   @struct LX_FloatingBox final
*   @brief The logical hitbox (Axis-Aligned Bounding Box)
*
*   @note If you want to use an Oriented Bounding Box (OBB),
*         you need to use LX_Polygon instead
*/
struct LX_FloatingBox final
{
    LX_FloatPosition p;         /**< Position   */
    int w = 0;                  /**< Width      */
    int h = 0;                  /**< Height     */
};


/**
*   @fn LX_FloatPosition toFloatPosition(const LX_Graphics::LX_ImgCoord& coord) noexcept
*   @param coord
*   @return The float position
*/
LX_FloatPosition toFloatPosition(const LX_Graphics::LX_ImgCoord& coord) noexcept;
/**
*   @fn LX_FloatingBox toFloatingBox(const LX_Graphics::LX_ImgRect& rect) noexcept
*   @param rect
*   @return The floating box
*/
LX_FloatingBox toFloatingBox(const LX_Graphics::LX_ImgRect& rect) noexcept;

/**
*   @struct LX_Segment final
*   @brief The segment
*
*   @note If you want to use an inifinite line, use LX_Line instead
*/
struct LX_Segment final
{
    LX_FloatPosition p;     /**< First point    */
    LX_FloatPosition q;     /**< Second point   */
};

/**
*   @struct LX_Line final
*   @brief The line
*/
struct LX_Line final
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
*   @struct LX_Circle final
*   @brief The circle structure
*/
struct LX_Circle final
{
    LX_FloatPosition center;    /**< The point that represents the center   */
    unsigned int radius;        /**< The circle radius                      */
};


// Operators of points and circles
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
