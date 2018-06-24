
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
*   @version 0.13
*/

#include <LunatiX/Hitbox.hpp>
#include <LunatiX/ImgRect.hpp>

using namespace FloatBox;

namespace LX_Physics
{

LX_FloatPosition toFloatPosition( const LX_Graphics::LX_ImgCoord& coord ) noexcept
{
    return LX_FloatPosition{ fbox<decltype( coord.x )>( coord.x ), fbox<decltype( coord.x )>( coord.y ) };
}


LX_FloatingBox toFloatingBox( const LX_Graphics::LX_ImgRect& rect ) noexcept
{
    return LX_FloatingBox{ toFloatPosition( rect.p ), rect.w, rect.h };
}


bool LX_Line::isParralelWith( const LX_Line& l ) const noexcept
{
    return collinear( v, l.v );
}

bool LX_Line::isPerpendicularTo( const LX_Line& l ) const noexcept
{
    return scalar_product( v, l.v ) == FNIL;
}


bool operator ==( const LX_FloatPosition& a, const LX_FloatPosition& b ) noexcept
{
    return a.x == b.x && a.y == b.y;
}

bool operator !=( const LX_FloatPosition& a, const LX_FloatPosition& b ) noexcept
{
    return a.x != b.x || a.y != b.y;
}


bool operator ==( const LX_Circle& a, const LX_Circle& b ) noexcept
{
    return a.center == b.center && a.radius == b.radius;
}

bool operator !=( const LX_Circle& a, const LX_Circle& b ) noexcept
{
    return a.center != b.center || a.radius != b.radius;
}

bool operator >( const LX_Circle& a, const LX_Circle& b ) noexcept
{
    return a.radius > b.radius;
}

bool operator <( const LX_Circle& a, const LX_Circle& b ) noexcept
{
    return a.radius < b.radius;
}

bool operator >=( const LX_Circle& a, const LX_Circle& b ) noexcept
{
    return a.radius >= b.radius;
}

bool operator <=( const LX_Circle& a, const LX_Circle& b ) noexcept
{
    return a.radius <= b.radius;
}

}
