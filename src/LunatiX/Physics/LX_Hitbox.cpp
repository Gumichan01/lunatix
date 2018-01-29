
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

LX_Point toPixelPosition(const LX_FloatPosition& p) noexcept
{
    return LX_Point{static_cast<int>(p.x.v), static_cast<int>(p.y.v)};
}

LX_ImgRect toImgRect(const LX_FloatingBox& b) noexcept
{
    // The idea is to get this line of code
    ///return LX_ImgRect{toPixelPosition(b.fpoint), b.w, b.h};
    return LX_ImgRect{static_cast<int>(b.fpoint.x),static_cast<int>(b.fpoint.y), b.w, b.h};
}

bool LX_Line::isParralelWith(const LX_Line& l) const noexcept
{
    return collinear(v, l.v);
}

bool LX_Line::isPerpendicularTo(const LX_Line& l) const noexcept
{
    return scalar_product(v, l.v) == fbox(0.0f);
}


bool operator ==(const LX_Point& a, const LX_Point& b) noexcept
{
    return a.x == b.x && a.y == b.y;
}

bool operator !=(const LX_Point& a, const LX_Point& b) noexcept
{
    return !(a == b);
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
    return a.center == b.center && a.radius == b.radius;
}

bool operator !=(const LX_Circle& a, const LX_Circle& b) noexcept
{
    return a.center != b.center || a.radius != b.radius;
}

bool operator >(const LX_Circle& a, const LX_Circle& b) noexcept
{
    return a.radius > b.radius;
}

bool operator <(const LX_Circle& a, const LX_Circle& b) noexcept
{
    return a.radius < b.radius;
}

bool operator >=(const LX_Circle& a, const LX_Circle& b) noexcept
{
    return a.radius >= b.radius;
}

bool operator <=(const LX_Circle& a, const LX_Circle& b) noexcept
{
    return a.radius <= b.radius;
}

}
