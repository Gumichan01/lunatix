
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
*   @file Vector2D.cpp
*   @brief The vector 2D implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/Vector2D.hpp>

using namespace FloatBox;

namespace lx
{

namespace Physics
{

bool operator ==( const Vector2D& u, const Vector2D& v ) noexcept
{
    return u.vx == v.vx && u.vy == v.vy;
}


bool operator !=( const Vector2D& u, const Vector2D& v ) noexcept
{
    return !( u == v );
}


Vector2D operator +( const Vector2D u, const Vector2D v ) noexcept
{
    return Vector2D{u.vx + v.vx, u.vy + v.vy};
}


Vector2D& operator +=( Vector2D& u, const Vector2D& v ) noexcept
{
    u = u + v;
    return u;
}


Vector2D operator -( const Vector2D u, const Vector2D v ) noexcept
{
    return Vector2D{u.vx - v.vx, u.vy - v.vy};
}


Vector2D& operator -=( Vector2D& u, const Vector2D& v ) noexcept
{
    u = u - v;
    return u;
}


Vector2D operator -( const Vector2D& v ) noexcept
{
    return Vector2D{ -v.vx, -v.vy};
}


Vector2D& operator ++( Vector2D& v ) noexcept
{
    v.vx += fbox( 1.0f );
    v.vy += fbox( 1.0f );
    return v;
}


Vector2D operator ++( Vector2D& v, int ) noexcept
{
    Vector2D t = v;
    ++v;
    return t;
}


Vector2D& operator --( Vector2D& v ) noexcept
{
    v.vx -= fbox( 1.0f );
    v.vy -= fbox( 1.0f );
    return v;
}


Vector2D operator --( Vector2D& v, int ) noexcept
{
    Vector2D t = v;
    --v;
    return t;
}


Vector2D operator *( Vector2D v, float lambda ) noexcept
{
    return Vector2D{v.vx * lambda, v.vy * lambda};
}

Vector2D& operator *=( Vector2D& v, float lambda ) noexcept
{
    v.vx *= fbox( lambda );
    v.vy *= fbox( lambda );
    return v;
}

Vector2D operator /( Vector2D v, float lambda ) noexcept
{
    return Vector2D{v.vx / lambda, v.vy / lambda};
}

Vector2D& operator /=( Vector2D& v, float lambda ) noexcept
{
    v.vx /= fbox( lambda );
    v.vy /= fbox( lambda );
    return v;
}

Float scalar_product( const Vector2D& u, const Vector2D& v ) noexcept
{
    return ( u.vx * v.vx ) + ( u.vy * v.vy );
}


Float vector_product( const Vector2D& u, const Vector2D& v ) noexcept
{
    return ( u.vx * v.vy ) - ( v.vx * u.vy );
}


Float vector_norm( const Vector2D& v ) noexcept
{
    Float tmp = scalar_product( v, v );
    return FloatMath::sqrt( tmp );
}


bool isNullVector( const Vector2D& v ) noexcept
{
    return v.vx == FNIL && v.vy == FNIL;
}


bool collinear( const Vector2D& u, const Vector2D& v ) noexcept
{
    return vector_product( u, v ) == FNIL;
}

Vector2D& normalize( Vector2D& v ) noexcept
{
    if ( isNullVector( v ) )
        return v;

    v *= ( fbox( 1.0f ) / vector_norm( v ) );
    return v;
}

}   // Physics

}   // lx
