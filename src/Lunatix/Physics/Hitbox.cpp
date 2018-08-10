
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
*   @file Hitbox.cpp
*   @brief The Hitbox operators implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <Lunatix/Hitbox.hpp>
#include <Lunatix/ImgRect.hpp>

using namespace FloatBox;

namespace lx
{

namespace Physics
{

FloatPosition toFloatPosition( const lx::Graphics::ImgCoord& coord ) noexcept
{
    return FloatPosition{ fbox<decltype( coord.x )>( coord.x ), fbox<decltype( coord.x )>( coord.y ) };
}


FloatingBox toFloatingBox( const lx::Graphics::ImgRect& rect ) noexcept
{
    return FloatingBox{ toFloatPosition( rect.p ), rect.w, rect.h };
}


bool Line::isParralelWith( const Line& l ) const noexcept
{
    return collinear( v, l.v );
}

bool Line::isPerpendicularTo( const Line& l ) const noexcept
{
    return scalar_product( v, l.v ) == FNIL;
}


bool operator ==( const FloatPosition& a, const FloatPosition& b ) noexcept
{
    return a.x == b.x && a.y == b.y;
}

bool operator !=( const FloatPosition& a, const FloatPosition& b ) noexcept
{
    return a.x != b.x || a.y != b.y;
}


bool operator ==( const Circle& a, const Circle& b ) noexcept
{
    return a.center == b.center && a.radius == b.radius;
}

bool operator !=( const Circle& a, const Circle& b ) noexcept
{
    return a.center != b.center || a.radius != b.radius;
}

bool operator >( const Circle& a, const Circle& b ) noexcept
{
    return a.radius > b.radius;
}

bool operator <( const Circle& a, const Circle& b ) noexcept
{
    return a.radius < b.radius;
}

bool operator >=( const Circle& a, const Circle& b ) noexcept
{
    return a.radius >= b.radius;
}

bool operator <=( const Circle& a, const Circle& b ) noexcept
{
    return a.radius <= b.radius;
}

}   // Physics

}   // lx
