

/*
*   Copyright (C) 2016 Luxon Jean-Pierre
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
*   @version 0.9
*
*/

#include <LunatiX/LX_Vector2D.hpp>
#include <LunatiX/LX_Hitbox.hpp>

#include <cmath>
#include <algorithm>
#include <limits>

namespace
{
const float EPSILON =  0.00001f;

/*
*   Implementation of a "safe" floating point comparison
*
*   This implementation is based on Nerdylicious's implementation
*   of floating point comparison program
*
*   https://github.com/Nerdylicious/FloatingPointComparison
*/
bool eq(float x, float y)
{
    float abs_x = fabsf(x);
    float abs_y = fabsf(y);
    float diff = fabsf(x - y);

    if(x == y)
    {
        return true;
    }
    else if(x == 0.0f || y == 0.0f || diff < std::numeric_limits<float>::min())
    {
        return diff < (EPSILON * std::numeric_limits<float>::min());
    }
    else
    {
        return (diff / std::min((abs_x + abs_y),
                                std::numeric_limits<float>::max())) < EPSILON;
    }
}
};

namespace LX_Physics
{

LX_Vector2D::LX_Vector2D(): LX_Vector2D(0.0f,0.0f) {}
LX_Vector2D::LX_Vector2D(float x,float y): vx(x), vy(y) {}
LX_Vector2D::LX_Vector2D(const LX_Vector2D& v): vx(v.vx), vy(v.vy) {}

LX_Vector2D::LX_Vector2D(const LX_Point& ori, const LX_Point& im)
    : vx(im.x - ori.x), vy(im.y - ori.y) {}


LX_Vector2D& LX_Vector2D::operator =(const LX_Vector2D& v)
{
    vx = v.vx;
    vy = v.vy;
    return *this;
}


bool operator ==(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return (((u.vx >= 0.0f && v.vx >= 0.0f) || (u.vx < 0.0f && v.vx < 0.0f))
            && ((u.vy >= 0.0f && v.vy >= 0.0f) || (u.vy < 0.0f && v.vy < 0.0f)))
           && (eq(u.vx,v.vx) && eq(u.vy,v.vy));
}


bool operator !=(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return !(u == v);
}


LX_Vector2D operator +(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return LX_Vector2D(u.vx + v.vx,u.vy + v.vy);
}


LX_Vector2D& operator +=(LX_Vector2D& u,const LX_Vector2D& v)
{
    u = u + v;
    return u;
}


LX_Vector2D operator -(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return LX_Vector2D(u.vx - v.vx,u.vy - v.vy);
}


LX_Vector2D& operator -=(LX_Vector2D& u,const LX_Vector2D& v)
{
    u = u - v;
    return u;
}


LX_Vector2D operator -(const LX_Vector2D& v)
{
    return LX_Vector2D(-v.vx,-v.vy);
}


LX_Vector2D& operator ++(LX_Vector2D& v)
{
    v.vx += 1;
    v.vy += 1;
    return v;
}


LX_Vector2D operator ++(LX_Vector2D& v,int)
{
    LX_Vector2D t = v;
    ++v;
    return t;
}


LX_Vector2D& operator --(LX_Vector2D& v)
{
    v.vx -= 1;
    v.vy -= 1;
    return v;
}


LX_Vector2D operator --(LX_Vector2D& v,int)
{
    LX_Vector2D t = v;
    --v;
    return t;
}


LX_Vector2D& operator *(LX_Vector2D& v,float lambda)
{
    return multiply(v, lambda);
}


float scalar_product(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return (u.vx * v.vx) + (u.vy * v.vy);
}


float vector_product(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return (u.vx * v.vy) - (v.vx * u.vy);
}


float vector_norm(const LX_Vector2D& v)
{
    return static_cast<float>(sqrt(scalar_product(v,v)));
}


bool isNullVector(const LX_Vector2D& v)
{
    return eq(v.vx,0.0f) && eq(v.vy,0.0f);
}


bool collinear(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return eq(vector_product(u,v),0.0f);
}


LX_Vector2D& multiply(LX_Vector2D& v,float lambda)
{
    v = LX_Vector2D(lambda * v.vx,lambda * v.vy);
    return v;
}


LX_Vector2D& normalize(LX_Vector2D& v)
{
    if(isNullVector(v))
        return v;

    float inverted_norm = 1.0f/ vector_norm(v);
    return multiply(v,inverted_norm);
}

};
