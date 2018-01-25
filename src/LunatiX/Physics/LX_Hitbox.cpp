
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

/**
*   @file LX_Hitbox.cpp
*   @brief The Hitbox operators implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/LX_Hitbox.hpp>


namespace LX_Physics
{

LX_Circle::LX_Circle() noexcept: LX_Circle(LX_FloatPosition{0,0}, 0) {}

LX_Circle::LX_Circle(const LX_FloatPosition& p, unsigned int rad) noexcept
    : center(p), radius(rad), square_radius(rad*rad) {}

LX_Circle::LX_Circle(const LX_Circle& c) noexcept
    : center(c.center),radius(c.radius),square_radius(c.square_radius) {}


bool LX_Line::isParralelWith(const LX_Line& l) const noexcept
{
    return collinear(v, l.v);
}

bool LX_Line::isPerpendicularTo(const LX_Line& l) const noexcept
{
    return scalar_product(v, l.v) == fbox(0.0f);
}

LX_Circle& LX_Circle::operator =(const LX_Circle& c) noexcept
{
    center = c.center;
    radius = c.radius;
    square_radius = c.square_radius;
    return *this;
}


bool operator ==(const LX_FloatPosition& a, const LX_FloatPosition& b) noexcept
{
    return a.x == b.x && a.y == b.y;
}


bool operator !=(const LX_FloatPosition& a, const LX_FloatPosition& b) noexcept
{
    return a.x != b.x || a.y != b.y;
}


bool operator ==(const LX_Circle& a, const LX_Circle& b) noexcept
{
    return a.center == b.center && a.radius == b.radius
           && a.square_radius == b.square_radius;
}


bool operator !=(const LX_Circle& a, const LX_Circle& b) noexcept
{
    return a.center != b.center || a.radius != b.radius
           || a.square_radius != b.square_radius;
}


bool operator >(const LX_Circle& a, const LX_Circle& b) noexcept
{
    return a.radius > b.radius && a.square_radius > b.square_radius;
}


bool operator <(const LX_Circle& a, const LX_Circle& b) noexcept
{
    return a.radius < b.radius && a.square_radius < b.square_radius;
}


bool operator >=(const LX_Circle& a, const LX_Circle& b) noexcept
{
    return a.radius >= b.radius && a.square_radius >= b.square_radius;
}


bool operator <=(const LX_Circle& a, const LX_Circle& b) noexcept
{
    return a.radius <= b.radius && a.square_radius <= b.square_radius;
}

}
