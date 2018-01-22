

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
#include <LunatiX/LX_Hitbox.hpp>

#include <cmath>
#include <algorithm>
#include <limits>

namespace
{

Float fc(float x)
{
    return {x};
}

}

namespace LX_Physics
{

const Float ZERO{0.0f};


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
    return LX_Vector2D{v.vx + v.vx, u.vy + v.vy};
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
    v.vx += 1.0f;
    v.vy += 1.0f;
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
    v.vx -= 1.0f;
    v.vy -= 1.0f;
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
    v.vx *= lambda;
    v.vy *= lambda;
    return v;
}

LX_Vector2D operator /(LX_Vector2D v, float lambda) noexcept
{
    return LX_Vector2D{v.vx / lambda, v.vy / lambda};
}

LX_Vector2D& operator /=(LX_Vector2D& v, float lambda) noexcept
{
    v.vx /= lambda;
    v.vy /= lambda;
    return v;
}

float scalar_product(const LX_Vector2D& u, const LX_Vector2D& v) noexcept
{
    return (u.vx * v.vx) + (u.vy * v.vy);
}


float vector_product(const LX_Vector2D& u, const LX_Vector2D& v) noexcept
{
    return (u.vx * v.vy) - (v.vx * u.vy);
}


float vector_norm(const LX_Vector2D& v) noexcept
{
    return static_cast<float>(sqrt(scalar_product(v, v)));
}


bool isNullVector(const LX_Vector2D& v) noexcept
{
    return v.vx == ZERO && v.vy == ZERO;
}


bool collinear(const LX_Vector2D& u,const LX_Vector2D& v) noexcept
{
    return vector_product(u, v) == ZERO;
}


LX_Vector2D& multiply(LX_Vector2D& v, float lambda) noexcept
{
    //v = LX_Vector2D(lambda * v.vx, lambda * v.vy);
    return v;
}


LX_Vector2D& normalize(LX_Vector2D& v) noexcept
{
    if(isNullVector(v))
        return v;

    v *= (1.0f / vector_norm(v));
    return v;
}

}
