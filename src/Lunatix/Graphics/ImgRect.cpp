
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

#include <Lunatix/ImgRect.hpp>
#include <Lunatix/Hitbox.hpp>


namespace LX_Graphics
{

LX_ImgCoord toPixelPosition( const lx::Physics::LX_FloatPosition& p ) noexcept
{
    return LX_ImgCoord{static_cast<int>( p.x.v ), static_cast<int>( p.y.v )};
}

LX_ImgRect toImgRect( const lx::Physics::LX_FloatingBox& b ) noexcept
{
    return LX_ImgRect{toPixelPosition( b.p ), b.w, b.h};
}

bool operator ==( const LX_ImgCoord& a, const LX_ImgCoord& b ) noexcept
{
    return a.x == b.x && a.y == b.y;
}

bool operator !=( const LX_ImgCoord& a, const LX_ImgCoord& b ) noexcept
{
    return !( a == b );
}

bool operator ==( const LX_ImgRect& a, const LX_ImgRect& b ) noexcept
{
    return a.p == b.p && a.w == b.w && a.h == b.h;
}

bool operator !=( const LX_ImgRect& a, const LX_ImgRect& b ) noexcept
{
    return !( a == b );
}

}
