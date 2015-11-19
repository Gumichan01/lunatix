

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
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
*	@version 0.6
*
*/

#include <cmath>

#include <LunatiX/LX_Vector2D.hpp>


namespace LX_Physics{


/**
*   @fn LX_Vector2D::LX_Vector2D()
*
*   Default constructor
*
*/
LX_Vector2D::LX_Vector2D(): LX_Vector2D(0.0f,0.0f)
{
    // Empty
}


/**
*   @fn LX_Vector2D::LX_Vector2D(float x,float y)
*
*   Build a vector from the coordinates
*
*   @param x The x velocity
*   @param y The y velocity
*
*/
LX_Vector2D::LX_Vector2D(float x,float y): vx(x), vy(y)
{
    // Empty
}


/**
*   @fn LX_Vector2D::LX_Vector2D(const LX_Vector2D& v)
*
*   Build a vector from another vector
*
*   @param v The vector
*
*/
LX_Vector2D::LX_Vector2D(const LX_Vector2D& v): vx(v.vx), vy(v.vy)
{
    // Empty
}



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


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"

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


#pragma clang diagnostic pop

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
*   @fn LX_Vector2D operator -(LX_Vector2D& v)
*
*   Get the opposite of the vector
*
*   @param v The vector
*
*   @return The opposite vector
*
*/
LX_Vector2D operator -(LX_Vector2D& v)
{
    return {-v.vx,-v.vy};
}




/**
*   @fn LX_Vector2D& operator ++(LX_Vector2D& v)
*
*   Prefix increment
*
*   @param v The vector
*
*   @return The incremented vector
*
*/
LX_Vector2D& operator ++(LX_Vector2D& v)
{
    v.vx += 1;
    v.vy += 1;

    return v;
}


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

/**
*   @fn LX_Vector2D operator ++(LX_Vector2D& v,int d)
*
*   Postfix increment
*
*   @param v The vector
*   @param d dummy parameter (not used)
*
*   @return The vector before the incrementation
*
*/
LX_Vector2D operator ++(LX_Vector2D& v,int d)
{
    LX_Vector2D t = v;
    ++v;

    return t;
}

#pragma clang diagnostic pop


/**
*   @fn LX_Vector2D& operator --(LX_Vector2D& v)
*
*   Prefix increment
*
*   @param v The vector
*
*   @return The incremented vector
*
*/
LX_Vector2D& operator --(LX_Vector2D& v)
{
    v.vx -= 1;
    v.vy -= 1;

    return v;
}


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

/**
*   @fn LX_Vector2D operator --(LX_Vector2D& v,int d)
*
*   Postfix increment
*
*   @param v The vector
*   @param d dummy parameter (not used)
*
*   @return The vector before the incrementation
*
*/
LX_Vector2D operator --(LX_Vector2D& v,int d)
{
    LX_Vector2D t = v;
    --v;

    return t;
}

#pragma clang diagnostic pop


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
*   @fn float vector_norm(const LX_Vector2D& v)
*
*   Calculate the norm of a vector
*
*   @param v The vector
*
*   @return The norm of the vector
*
*/
float vector_norm(const LX_Vector2D& v)
{
    return static_cast<float>(sqrt(scalar_product(v,v)));
}


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"

/**
*   @fn bool isZeroVector(const LX_Vector2D& v)
*
*   Check if the vector is a zero vector
*
*   @param v The vector
*
*   @return True if the vector has coordinates equal to 0, False otherwise
*
*/
bool isZeroVector(const LX_Vector2D& v)
{
    return v.vx == 0 && v.vy ==0;
}

#pragma clang diagnostic pop


/**
*   @fn bool collinear(const LX_Vector2D& u,const LX_Vector2D& v)
*
*   Check if two vectors are colinear
*
*   @param u The first vector
*   @param v The second vector
*
*   @return True if they are colinear, False otherwise
*
*/
bool collinear(const LX_Vector2D& u,const LX_Vector2D& v)
{
    return vector_product(u,v) == 0.0f;
}


/**
*   @fn LX_Vector2D& multiply(LX_Vector2D& v, float lambda)
*
*   Scalar multiplication
*
*   @param v The vector
*   @param lambda The scalar value
*
*   @return The new vector after the multiplication
*
*/
LX_Vector2D& multiply(LX_Vector2D& v,float lambda)
{
    v = {lambda * v.vx,lambda * v.vy};
    return v;
}


/**
*   @fn LX_Vector2D& normalize(LX_Vector2D& v)
*
*   Vector normalization
*
*   @param v The vector
*
*   @return The normalized vector
*
*/
LX_Vector2D& normalize(LX_Vector2D& v)
{
    if(isZeroVector(v))
        return v;

    float inverted_norm = 1.0f/vector_norm(v);
    return multiply(v,inverted_norm);
}


};


