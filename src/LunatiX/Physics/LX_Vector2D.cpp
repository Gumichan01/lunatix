

/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/


/**
*	@file LX_Vector2D.cpp
*	@brief The vector 2D implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <cmath>
#include <LunatiX/LX_Vector2D.hpp>


namespace LX_Physics
{

LX_Vector2D::LX_Vector2D(): LX_Vector2D(0.0f,0.0f) {}

LX_Vector2D::LX_Vector2D(float x,float y): vx(x), vy(y) {}

LX_Vector2D::LX_Vector2D(const LX_Vector2D& v): vx(v.vx), vy(v.vy) {}

LX_Vector2D& LX_Vector2D::operator =(const LX_Vector2D v)
{
    vx = v.vx;
    vy = v.vy;
    return *this;
}


bool operator ==(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return (((u.vx >= 0 && v.vx >= 0) || (u.vx < 0 && v.vx < 0))
            && ((u.vy >= 0 && v.vy >= 0) || (u.vy < 0 && v.vy < 0) ))
           && (u.vx == v.vx && u.vy == v.vy);
}


bool operator !=(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return !(u == v);
}


LX_Vector2D operator +(LX_Vector2D& u,LX_Vector2D& v)
{
    return LX_Vector2D(u.vx + v.vx,u.vy + v.vy);
}


LX_Vector2D operator +=(LX_Vector2D& u,LX_Vector2D& v)
{
    u = u + v;
    return u;
}


LX_Vector2D operator -(LX_Vector2D& u,LX_Vector2D& v)
{
    return LX_Vector2D(u.vx - v.vx,u.vy - v.vy);
}


LX_Vector2D operator -=(LX_Vector2D& u,LX_Vector2D& v)
{
    u = u - v;
    return u;
}


LX_Vector2D operator -(LX_Vector2D& v)
{
    return LX_Vector2D(-v.vx,-v.vy);
}


LX_Vector2D& operator ++(LX_Vector2D& v)
{
    v.vx += 1;
    v.vy += 1;
    return v;
}


LX_Vector2D operator ++(LX_Vector2D& v,int d)
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


LX_Vector2D operator --(LX_Vector2D& v,int d)
{
    LX_Vector2D t = v;
    --v;
    return t;
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
    return v.vx == 0.0f && v.vy == 0.0f;
}


bool collinear(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return vector_product(u,v) == 0.0f;
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
