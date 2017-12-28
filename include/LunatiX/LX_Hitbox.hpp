
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

#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED

/**
*   @file LX_Hitbox.hpp
*   @brief The hitbox library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/LX_AABB.hpp>
#include <LunatiX/LX_Vector2D.hpp>

namespace LX_Physics
{

/**
*   @struct LX_Point
*   @brief The point structure
*/
struct LX_Point
{
    int x;      /**< The x position of the point */
    int y;      /**< The y position of the point */

    /// No argument constructor
    LX_Point() noexcept;
    /// Construct a point using coordinates
    LX_Point(int xpos, int ypos) noexcept;
    /// Construct a point using another point
    LX_Point(const LX_Point& p) noexcept;
    /// Point assignment
    LX_Point& operator=(const LX_Point& p) noexcept;
};


/**
*   @struct LX_Line
*   @brief The line structure
*/
struct LX_Line
{
    LX_Point o;     /**< Origin point       */
    LX_Vector2D v;  /**< Direction vector   */

    /// Default Constructor
    LX_Line() noexcept;
    /// Copy destructor
    LX_Line(const LX_Line& l) noexcept;
    /// Construct the line using the point and the direction vector
    LX_Line(const LX_Point& p, const LX_Vector2D& dv) noexcept;
    /// Line assignment
    LX_Line& operator=(const LX_Line& l) noexcept;

    /**
    *   @fn bool isParralelWith(const LX_Line& l) const noexcept
    *
    *   Check if the line is parralel with the line given in argument
    *
    *   @param [in] l The line to compare
    *   @return TRUE if the two lines are paralel, FALSE otherwise
    */
    bool isParralelWith(const LX_Line& l) const noexcept;
    /**
    *   @fn bool isPerpendicularTo(const LX_Line& l) const noexcept
    *
    *   Check if the line is perpendicular to the line given in argument
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
    LX_Point center;            /**< The point that represents the center   */
    unsigned int radius;        /**< The circle radius                      */
    unsigned int square_radius; /**< The square radius                      */

    /// No argument constructor
    LX_Circle() noexcept;
    /// Construct a circle using a point and a radius
    LX_Circle(const LX_Point& p, unsigned int rad) noexcept;
    /// Construct a circle using another circle
    LX_Circle(const LX_Circle& c) noexcept;
    /// Circle assignment
    LX_Circle& operator=(const LX_Circle& c) noexcept;
};


// Operators of points and circles
/**
*   @fn bool operator ==(const LX_Point& a, const LX_Point& b) noexcept
*
*   Check If two points are identical
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
*   Check If two points are dIfferent
*
*   @param [in] a The first point
*   @param [in] b The second point
*
*   @return TRUE If these points have not the same coordinates, FALSE otherwise
*/
bool operator !=(const LX_Point& a, const LX_Point& b) noexcept;
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
