

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is an SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/


/**
*	@file LX_Hitbox.cpp
*	@brief The Hitbox operators implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <LunatiX/LX_Hitbox.hpp>


namespace LX_Physics
{


/**
*   @fn LX_Point::LX_Point()
*
*   No argument constructor of the point
*
*/
LX_Point::LX_Point(): LX_Point(0,0)
{
    // Empty
}


/**
*   @fn LX_Point::LX_Point(int xpos, int ypos)
*
*   2-argument constructor of the point
*
*   @param xpos X position
*   @param xpos Y position
*
*/
LX_Point::LX_Point(int xpos, int ypos): x(xpos), y(ypos)
{
    // Empty
}


/**
*   @fn LX_Point::LX_Point(const LX_Point& p)
*
*   Copy constructor of the point
*
*   @param p The point
*
*/
LX_Point::LX_Point(const LX_Point& p)
{
    x = p.x;
    y = p.y;
}


/**
*   @fn LX_Point& LX_Point::operator=(const LX_Point p)
*
*   Assign a point to another point
*
*   @param p The point
*
*   @return The new point
*
*/
LX_Point& LX_Point::operator =(LX_Point p)
{
    x = p.x;
    y = p.y;

    return *this;
}


/**
*   @fn LX_Circle(const LX_Point p, unsigned int rad)
*
*   Construct the circle with a point and the radius
*
*   @param p The center of the circle
*   @param rad The radius
*
*/
LX_Circle::LX_Circle(const LX_Point p, unsigned int rad)
    : center(p), radius(rad), square_radius(rad*rad)
{
    // Empty
}


/**
*   @fn LX_Circle::LX_Circle(const LX_Circle& c)
*
*   Copy constructor of the circle
*
*   @param c The circle
*
*/
LX_Circle::LX_Circle(const LX_Circle& c)
    : center(c.center),radius(c.radius),square_radius(c.square_radius)
{
    // Empty
}


/**
*   @fn LX_Circle& LX_Circle::operator =(const LX_Circle c)
*
*   Assign a circle to another circle
*
*   @param c The circle
*
*   @return The new circle
*
*/
LX_Circle& LX_Circle::operator =(const LX_Circle c)
{
    center = c.center;
    radius = c.radius;
    square_radius = c.square_radius;

    return *this;
}

};



/**
*   @fn bool operator ==(const LX_Physics::LX_Point& a, const LX_Physics::LX_Point& b)
*
*   Check If two points are identical
*
*   @param a The first point
*   @param b The second point
*
*   @return TRUE If these points have exactly the same coordinates,
*           FALSE otherwise
*
*/
bool operator ==(const LX_Physics::LX_Point& a, const LX_Physics::LX_Point& b)
{
    return a.x == b.x && a.y == b.y;
}


/**
*   @fn bool operator !=(const LX_Physics::LX_Point& a, const LX_Physics::LX_Point& b)
*
*   Check If two points are dIfferent
*
*   @param a The first point
*   @param b The second point
*
*   @return TRUE If these points have not the same coordinates, FALSE otherwise
*
*/
bool operator !=(const LX_Physics::LX_Point& a, const LX_Physics::LX_Point& b)
{
    return a.x != b.x || a.y != b.y;
}


/**
*   @fn bool operator ==(const LX_Physics::LX_Circle& a, const LX_Physics::LX_Circle& b)
*
*   Check If two circles are exactly identical (same coordinates and same radius)
*
*   @param a The first circle
*   @param b The second circle
*
*   @return TRUE If these circles are idendital, FALSE otherwise
*
*/
bool operator ==(const LX_Physics::LX_Circle& a, const LX_Physics::LX_Circle& b)
{
    return a.center == b.center && a.radius == b.radius
           && a.square_radius == b.square_radius;
}


/**
*   @fn bool operator !=(const LX_Physics::LX_Circle& a, const LX_Physics::LX_Circle& b)
*
*   Check If two circles are exactly identical (same coordinates and same radius)
*
*   @param a The first circle
*   @param b The second circle
*
*   @return TRUE If these circles are idendital, FALSE otherwise
*
*/
bool operator !=(const LX_Physics::LX_Circle& a, const LX_Physics::LX_Circle& b)
{
    return a.center != b.center || a.radius != b.radius
           || a.square_radius != b.square_radius;
}


/**
*   @fn bool operator >(const LX_Physics::LX_Circle& a, const LX_Physics::LX_Circle& b)
*
*   Check If the first circle has a greater radius than the second one
*
*   @param a The first circle
*   @param b The second circle
*
*   @return TRUE If the first circle is greater than the second circle,
*           FALSE otherwise
*
*/
bool operator >(const LX_Physics::LX_Circle& a, const LX_Physics::LX_Circle& b)
{
    return a.radius > b.radius && a.square_radius > b.square_radius;
}



/**
*   @fn bool operator <(const LX_Physics::LX_Circle& a, const LX_Physics::LX_Circle& b)
*
*   Check If the first circle radius is smaller than the second one
*
*   @param a The first circle
*   @param b The second circle
*
*   @return TRUE If the first circle is smaller than the second circle,
*           FALSE otherwise
*
*/
bool operator <(const LX_Physics::LX_Circle& a, const LX_Physics::LX_Circle& b)
{
    return a.radius < b.radius && a.square_radius < b.square_radius;
}



/**
*   @fn bool operator >=(const LX_Physics::LX_Circle& a, const LX_Physics::LX_Circle& b)
*
*   Check If the first circle has a greater radius than the second one
*   or if they have the same radius length
*
*   @param a The first circle
*   @param b The second circle
*
*   @return TRUE If the first circle is greater than the second circle,
*           or if have the same radius length, FALSE otherwise
*
*/
bool operator >=(const LX_Physics::LX_Circle& a, const LX_Physics::LX_Circle& b)
{
    return a.radius >= b.radius && a.square_radius >= b.square_radius;
}



/**
*   @fn bool operator <=(const LX_Physics::LX_Circle& a, const LX_Physics::LX_Circle& b)
*
*   Check If the first circle radius is smaller than the second one
*   or if they have the same radius length
*
*   @param a The first circle
*   @param b The second circle
*
*   @return TRUE If the first circle is smaller than the second circle,
*           or if the two circles have the same radius length, FALSE otherwise
*
*/
bool operator <=(const LX_Physics::LX_Circle& a, const LX_Physics::LX_Circle& b)
{
    return a.radius <= b.radius && a.square_radius <= b.square_radius;
}



































