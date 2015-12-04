#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED


/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Hitbox.hpp
*	@brief The hitbox library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.7
*
*/


namespace LX_Physics{

/**
*   @struct LX_Point
*   @brief The point structure
*
*   This point is described by the x and y field
*/
typedef struct LX_Point
{
    int x;      /**< The x position of the point */
    int y;      /**< The y position of the point */

    LX_Point();
    LX_Point(int xpos, int ypos);
    LX_Point(const LX_Point& p);
    LX_Point& operator=(const LX_Point p);

} LX_Point;     /**< The point */




/**
*   @struct LX_Circle
*   @brief The circle structure
*
*   This structure describe the circle
*/
typedef struct LX_Circle
{
    LX_Point center;            /**< The point that represents the center   */
    unsigned int radius;        /**< The circle radius                      */
    unsigned int square_radius; /**< The square radius                      */

    LX_Circle();
    LX_Circle(const LX_Point& p, unsigned int rad);
    LX_Circle(const LX_Circle& c);
    LX_Circle& operator=(const LX_Circle c);

} LX_Circle;    /**< @brief The circle */


// Operators of points and circles
bool operator ==(const LX_Point& a, const LX_Point& b);
bool operator !=(const LX_Point& a, const LX_Point& b);

bool operator ==(const LX_Circle& a, const LX_Circle& b);
bool operator !=(const LX_Circle& a, const LX_Circle& b);
bool operator >(const LX_Circle& a, const LX_Circle& b);
bool operator <(const LX_Circle& a, const LX_Circle& b);
bool operator >=(const LX_Circle& a, const LX_Circle& b);
bool operator <=(const LX_Circle& a, const LX_Circle& b);

};

#endif // HITBOX_H_INCLUDED

