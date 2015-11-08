

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is an SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/


/**
*	@file LX_Vector2D.cpp
*	@brief The vector 2D implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <cmath>

#include <LunatiX/LX_Vector2D.hpp>


namespace LX_Physics{

/**
*   @fn LX_Vector2D& LX_Vector2D::operator =(const LX_Vector2D v)
*
*   Assign a vector to another vector
*
*   @param v The vector
*
*   @return The new vector
*
*/
LX_Vector2D& LX_Vector2D::operator =(const LX_Vector2D v)
{
    vx = v.vx;
    vy = v.vy;

    return *this;
}


/**
*   @fn bool operator ==(const LX_Vector2D& u,const LX_Vector2D& v)
*
*   Check if two vectors are equal
*
*   @param u The first vector
*   @param v The second vector
*
*   @return TRUE if they are equal, FALSE otherwise
*
*/
bool operator ==(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return (((u.vx >= 0 && v.vx >= 0) || (u.vx < 0 && v.vx < 0))
            && ((u.vy >= 0 && v.vy >= 0) || (u.vy < 0 && v.vy < 0) ))
            && (u.vx == v.vx && u.vy == v.vy);
}


/**
*   @fn bool operator !=(const LX_Vector2D& u,const LX_Vector2D& v)
*
*   Check if two vectors are not equal
*
*   @param u The first vector
*   @param v The second vector
*
*   @return TRUE if they are not equal, FALSE otherwise
*
*/
bool operator !=(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return !(u == v);
}


/**
*   @fn LX_Vector2D operator +(LX_Vector2D& u,LX_Vector2D& v)
*
*   Addition betwwen two vectors
*
*   @param u The first vector
*   @param v The second vector
*
*   @return The resulting vector
*
*/
LX_Vector2D operator +(LX_Vector2D& u,LX_Vector2D& v)
{
    return {u.vx + v.vx,u.vy + v.vy};
}


/**
*   @fn LX_Vector2D operator +=(LX_Vector2D& u,LX_Vector2D& v)
*
*   Addition betwwen two vectors -> 'u += v' <=> 'u = u + v'
*
*   @param u The vector that will be modified
*   @param v The second vector
*
*   @return The resulting vector
*
*/
LX_Vector2D operator +=(LX_Vector2D& u,LX_Vector2D& v)
{
    u = u + v;
    return u;
}


/**
*   @fn LX_Vector2D operator -(LX_Vector2D& u,LX_Vector2D& v)
*
*   Substraction betwwen two vectors
*
*   @param u The first vector
*   @param v The second vector
*
*   @return The resulting vector
*
*/
LX_Vector2D operator -(LX_Vector2D& u,LX_Vector2D& v)
{
    return {u.vx - v.vx,u.vy - v.vy};
}


/**
*   @fn LX_Vector2D operator -=(LX_Vector2D& u,LX_Vector2D& v)
*
*   Substraction betwwen two vectors -> 'u -= v' <=> 'u = u - v'
*
*   @param u The vector that will be modified
*   @param v The second vector
*
*   @return The resulting vector
*
*/
LX_Vector2D operator -=(LX_Vector2D& u,LX_Vector2D& v)
{
    u = u - v;
    return u;
}


/**
*   @fn LX_Vector2D operator -(LX_Vector2D& u)
*
*   Get the opposite of the vector
*
*   @param u The vector
*
*   @return The opposite vector
*
*/
LX_Vector2D operator -(LX_Vector2D& u)
{
    return {-u.vx,-u.vy};
}


/**
*   @fn LX_Vector2D& operator ++(LX_Vector2D& u)
*
*   Prefix increment
*
*   @param u The vector
*
*   @return The incremented vector
*
*/
LX_Vector2D& operator ++(LX_Vector2D& u)
{
    u.vx += 1;
    u.vy += 1;

    return u;
}


/**
*   @fn LX_Vector2D operator ++(LX_Vector2D& u,int d)
*
*   Postfix increment
*
*   @param u The vector
*   @param d dummy parameter (not used)
*
*   @return The vector before the incrementation
*
*/
LX_Vector2D operator ++(LX_Vector2D& u,int d)
{
    LX_Vector2D t = u;
    ++u;

    return t;
}


/**
*   @fn LX_Vector2D& operator --(LX_Vector2D& u)
*
*   Prefix increment
*
*   @param u The vector
*
*   @return The incremented vector
*
*/
LX_Vector2D& operator --(LX_Vector2D& u)
{
    u.vx -= 1;
    u.vy -= 1;

    return u;
}


/**
*   @fn LX_Vector2D operator --(LX_Vector2D& u,int d)
*
*   Postfix increment
*
*   @param u The vector
*   @param d dummy parameter (not used)
*
*   @return The vector before the incrementation
*
*/
LX_Vector2D operator --(LX_Vector2D& u,int d)
{
    LX_Vector2D t = u;
    --u;

    return t;
}


/**
*   @fn float scalar_product(const LX_Vector2D& u,const LX_Vector2D& v)
*
*   Calculate the scalar product of 2 vectors
*
*   @param u The first vector
*   @param v The second vector
*
*   @return The scalar product
*
*/
float scalar_product(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return (u.vx * v.vx) + (u.vy * v.vy);
}


/**
*   @fn float vector_product(const LX_Vector2D& u,const LX_Vector2D& v)
*
*   Calculate the vector product of 2 vectors
*
*   @param u The first vector
*   @param v The second vector
*
*   @return The vector product
*
*/
float vector_product(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return (u.vx * v.vy) - (v.vx * u.vy);
}


/**
*   @fn float vector_norm(const LX_Vector2D& u)
*
*   Calculate the norm of a vector
*
*   @param u The vector
*
*   @return The norm of the vector
*
*/
float vector_norm(const LX_Vector2D& u)
{
    return sqrt(scalar_product(u,u));
}


/**
*   @fn bool isZeroVector(const LX_Vector2D& u)
*
*   Check if the vector is a zero vector
*
*   @param u The vector
*
*   @return True if the vector has coordinates equal to 0, FALSE otherwise
*
*/
bool isZeroVector(const LX_Vector2D& u)
{
    return u.vx == 0 && u.vy ==0;
}


};





