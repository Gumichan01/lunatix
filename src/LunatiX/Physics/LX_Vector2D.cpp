

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
*   @file LX_Vector2D.cpp
*   @brief The vector 2D implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*
*/

#include <LunatiX/LX_Vector2D.hpp>
#include <cmath>

using namespace FloatBox;

namespace LX_Physics
{

bool operator ==(const LX_Vector2D& u, const LX_Vector2D& v) noexcept
{
    return u.vx == v.vx && u.vy == v.vy;
}


bool operator !=(const LX_Vector2D& u, const LX_Vector2D& v) noexcept
{
    return !(u == v);
}


LX_Vector2D operator +(const LX_Vector2D u,const LX_Vector2D v) noexcept
{
    return LX_Vector2D{u.vx + v.vx, u.vy + v.vy};
}


LX_Vector2D& operator +=(LX_Vector2D& u, const LX_Vector2D& v) noexcept
{
    u = u + v;
    return u;
}


LX_Vector2D operator -(const LX_Vector2D u, const LX_Vector2D v) noexcept
{
    return LX_Vector2D{u.vx - v.vx, u.vy - v.vy};
}


LX_Vector2D& operator -=(LX_Vector2D& u, const LX_Vector2D& v) noexcept
{
    u = u - v;
    return u;
}


LX_Vector2D operator -(const LX_Vector2D& v) noexcept
{
    return LX_Vector2D{-v.vx, -v.vy};
}


LX_Vector2D& operator ++(LX_Vector2D& v) noexcept
{
    v.vx += fbox(1.0f);
    v.vy += fbox(1.0f);
    return v;
}


LX_Vector2D operator ++(LX_Vector2D& v, int) noexcept
{
    LX_Vector2D t = v;
    ++v;
    return t;
}


LX_Vector2D& operator --(LX_Vector2D& v) noexcept
{
    v.vx -= fbox(1.0f);
    v.vy -= fbox(1.0f);
    return v;
}


LX_Vector2D operator --(LX_Vector2D& v, int) noexcept
{
    LX_Vector2D t = v;
    --v;
    return t;
}


LX_Vector2D operator *(LX_Vector2D v, float lambda) noexcept
{
    return LX_Vector2D{v.vx * lambda, v.vy * lambda};
}

LX_Vector2D& operator *=(LX_Vector2D& v, float lambda) noexcept
{
    v.vx *= fbox(lambda);
    v.vy *= fbox(lambda);
    return v;
}

LX_Vector2D operator /(LX_Vector2D v, float lambda) noexcept
{
    return LX_Vector2D{v.vx / lambda, v.vy / lambda};
}

LX_Vector2D& operator /=(LX_Vector2D& v, float lambda) noexcept
{
    v.vx /= fbox(lambda);
    v.vy /= fbox(lambda);
    return v;
}

Float scalar_product(const LX_Vector2D& u, const LX_Vector2D& v) noexcept
{
    return (u.vx * v.vx) + (u.vy * v.vy);
}


Float vector_product(const LX_Vector2D& u, const LX_Vector2D& v) noexcept
{
    return (u.vx * v.vy) - (v.vx * u.vy);
}


Float vector_norm(const LX_Vector2D& v) noexcept
{
    Float tmp = scalar_product(v, v);
    return FloatMath::sqrt(tmp);
}


bool isNullVector(const LX_Vector2D& v) noexcept
{
    return v.vx == FNIL && v.vy == FNIL;
}


bool collinear(const LX_Vector2D& u,const LX_Vector2D& v) noexcept
{
    return vector_product(u, v) == FNIL;
}

LX_Vector2D& normalize(LX_Vector2D& v) noexcept
{
    if(isNullVector(v))
        return v;

    v *= ( fbox(1.0f) / vector_norm(v) );
    return v;
}

}
