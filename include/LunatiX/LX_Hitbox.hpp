
/*
*   Copyright (C) 2016 Luxon Jean-Pierre
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
*   @version 0.10
*/

#include <LunatiX/LX_AABB.hpp>

namespace LX_Physics
{

/**
*   @struct LX_Point
*   @brief The point structure
*   This point is described by the x and y field
*/
struct LX_Point
{
    int x;      /**< The x position of the point */
    int y;      /**< The y position of the point */

    /// No argument constructor
    LX_Point();
    /// Construct a point using coordinates
    LX_Point(int xpos, int ypos);
    /// Construct a point using another point
    LX_Point(const LX_Point& p);
    /// Point assignment
    LX_Point& operator=(const LX_Point& p);
};


/**
*   @struct LX_Circle
*   @brief The circle structure
*   This structure describe the circle
*/
struct LX_Circle
{
    LX_Point center;            /**< The point that represents the center   */
    unsigned int radius;        /**< The circle radius                      */
    unsigned int square_radius; /**< The square radius                      */

    /// No argument constructor
    LX_Circle();
    /// Construct a circle using a point and a radius
    LX_Circle(const LX_Point& p, unsigned int rad);
    /// Construct a circle using another circle
    LX_Circle(const LX_Circle& c);
    /// Circle assignment
    LX_Circle& operator=(const LX_Circle& c);
};


// Operators of points and circles
/**
*   @fn bool operator ==(const LX_Point& a, const LX_Point& b)
*
*   Check If two points are identical
*
*   @param [in] a The first point
*   @param [in] b The second point
*
*   @return TRUE If these points have exactly the same coordinates,
*          FALSE otherwise
*/
bool operator ==(const LX_Point& a, const LX_Point& b);
/**
*   @fn bool operator !=(const LX_Point& a, const LX_Point& b)
*
*   Check If two points are dIfferent
*
*   @param [in] a The first point
*   @param [in] b The second point
*
*   @return TRUE If these points have not the same coordinates, FALSE otherwise
*/
bool operator !=(const LX_Point& a, const LX_Point& b);
/**
*   @fn bool operator ==(const LX_Circle& a, const LX_Circle& b)
*
*   Check If two circles are exactly identical (same coordinates and same radius)
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If these circles are idendital, FALSE otherwise
*/
bool operator ==(const LX_Circle& a, const LX_Circle& b);
/**
*   @fn bool operator !=(const LX_Circle& a, const LX_Circle& b)
*
*   Check If two circles are exactly identical (same coordinates and same radius)
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If these circles are idendital, FALSE otherwise
*/
bool operator !=(const LX_Circle& a, const LX_Circle& b);
/**
*   @fn bool operator >(const LX_Circle& a, const LX_Circle& b)
*
*   Check If the first circle has a greater radius than the second one
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If the first circle is greater than the second circle,
*          FALSE otherwise
*/
bool operator >(const LX_Circle& a, const LX_Circle& b);
/**
*   @fn bool operator <(const LX_Circle& a, const LX_Circle& b)
*
*   Check If the first circle radius is smaller than the second one
*
*   @param [in] a The first circle
*   @param [in] b The second circle
*
*   @return TRUE If the first circle is smaller than the second circle,
*          FALSE otherwise
*/
bool operator <(const LX_Circle& a, const LX_Circle& b);
/**
*   @fn bool operator >=(const LX_Circle& a, const LX_Circle& b)
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
bool operator >=(const LX_Circle& a, const LX_Circle& b);
/**
*   @fn bool operator <=(const LX_Circle& a, const LX_Circle& b)
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
bool operator <=(const LX_Circle& a, const LX_Circle& b);

};

#endif // HITBOX_H_INCLUDED
