

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
*    @file LX_Hitbox.cpp
*    @brief The Hitbox operators implementation
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*
*/

#include <LunatiX/LX_Hitbox.hpp>


namespace LX_Physics
{

LX_Point::LX_Point(): LX_Point(0,0) {}

LX_Point::LX_Point(int xpos, int ypos): x(xpos), y(ypos) {}

LX_Point::LX_Point(const LX_Point& p): x(p.x), y(p.y) {}

LX_Circle::LX_Circle() : LX_Circle(LX_Point(0,0),0) {}

LX_Circle::LX_Circle(const LX_Point& p, unsigned int rad)
    : center(p), radius(rad), square_radius(rad*rad) {}

LX_Circle::LX_Circle(const LX_Circle& c)
    : center(c.center),radius(c.radius),square_radius(c.square_radius) {}


LX_Point& LX_Point::operator =(const LX_Point& p)
{
    x = p.x;
    y = p.y;

    return *this;
}

LX_Circle& LX_Circle::operator =(const LX_Circle& c)
{
    center = c.center;
    radius = c.radius;
    square_radius = c.square_radius;

    return *this;
}


bool operator ==(const LX_Point& a, const LX_Point& b)
{
    return a.x == b.x && a.y == b.y;
}


bool operator !=(const LX_Point& a, const LX_Point& b)
{
    return a.x != b.x || a.y != b.y;
}


bool operator ==(const LX_Circle& a, const LX_Circle& b)
{
    return a.center == b.center && a.radius == b.radius
           && a.square_radius == b.square_radius;
}


bool operator !=(const LX_Circle& a, const LX_Circle& b)
{
    return a.center != b.center || a.radius != b.radius
           || a.square_radius != b.square_radius;
}


bool operator >(const LX_Circle& a, const LX_Circle& b)
{
    return a.radius > b.radius && a.square_radius > b.square_radius;
}


bool operator <(const LX_Circle& a, const LX_Circle& b)
{
    return a.radius < b.radius && a.square_radius < b.square_radius;
}


bool operator >=(const LX_Circle& a, const LX_Circle& b)
{
    return a.radius >= b.radius && a.square_radius >= b.square_radius;
}


bool operator <=(const LX_Circle& a, const LX_Circle& b)
{
    return a.radius <= b.radius && a.square_radius <= b.square_radius;
}

};

