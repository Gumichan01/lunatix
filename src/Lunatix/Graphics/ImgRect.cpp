
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


namespace lx
{

namespace Graphics
{

ImgCoord toPixelPosition( const lx::Physics::FloatPosition& p ) noexcept
{
    return ImgCoord{static_cast<int>( p.x.v ), static_cast<int>( p.y.v )};
}

ImgRect toImgRect( const lx::Physics::FloatingBox& b ) noexcept
{
    return ImgRect{toPixelPosition( b.p ), b.w, b.h};
}

bool operator ==( const ImgCoord& a, const ImgCoord& b ) noexcept
{
    return a.x == b.x && a.y == b.y;
}

bool operator !=( const ImgCoord& a, const ImgCoord& b ) noexcept
{
    return !( a == b );
}

bool operator ==( const ImgRect& a, const ImgRect& b ) noexcept
{
    return a.p == b.p && a.w == b.w && a.h == b.h;
}

bool operator !=( const ImgRect& a, const ImgRect& b ) noexcept
{
    return !( a == b );
}

}   // Graphics

}   // lx
