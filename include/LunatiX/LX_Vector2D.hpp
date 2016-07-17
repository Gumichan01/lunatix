#ifndef LX_VECTOR2D_HPP_INCLUDED
#define LX_VECTOR2D_HPP_INCLUDED


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
*	@file LX_Vector2D.hpp
*	@brief The vector 2D library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/


namespace LX_Physics
{

/**
*   @struct LX_Vector2D
*   @brief The vector2D structure
*
*   This structure describes a vector
*/
struct LX_Vector2D
{
    float vx;                   /**< The x velocity */
    float vy;                   /**< The y velocity */

    /// No argument constructor
    LX_Vector2D();

    /// Construct a vector using coordinates
    LX_Vector2D(float x,float y);

    /// Construct a vector using coordinates
    LX_Vector2D(const LX_Vector2D& v);

    /// Vector2D assignment
    LX_Vector2D& operator =(const LX_Vector2D v);

};

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
bool operator ==(const LX_Vector2D& u,const LX_Vector2D& v);

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
bool operator !=(const LX_Vector2D& u,const LX_Vector2D& v);

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
LX_Vector2D operator +(const LX_Vector2D& u,const LX_Vector2D& v);

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
LX_Vector2D operator +=(LX_Vector2D& u,const LX_Vector2D& v);

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
LX_Vector2D operator -(const LX_Vector2D& u,const LX_Vector2D& v);

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
LX_Vector2D operator -=(LX_Vector2D& u,const LX_Vector2D& v);

/**
*   @fn LX_Vector2D operator -(const LX_Vector2D& v)
*
*   Get the opposite of the vector
*
*   @param v The vector
*
*   @return The opposite vector
*
*/
LX_Vector2D operator -(const LX_Vector2D& v);

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
LX_Vector2D& operator ++(LX_Vector2D& v);

/**
*   @fn LX_Vector2D operator ++(LX_Vector2D& v,int)
*
*   Postfix increment
*
*   @param v The vector
*
*   @return The vector before the incrementation
*
*/
LX_Vector2D operator ++(LX_Vector2D& v,int);

/**
*   @fn LX_Vector2D& operator --(LX_Vector2D& v)
*
*   Prefix decrement
*
*   @param v The vector
*
*   @return The incremented vector
*
*/
LX_Vector2D& operator --(LX_Vector2D& v);

/**
*   @fn LX_Vector2D operator --(LX_Vector2D& v,int)
*
*   Postfix decrement
*
*   @param v The vector
*
*   @return The vector before the incrementation
*
*/
LX_Vector2D operator --(LX_Vector2D& v,int);

/**
*   @fn LX_Vector2D& operator *(LX_Vector2D& v,float lambda)
*
*   Scalar multiplication (syntactic sugar of multiply)
*
*   @param v The vector
*   @param lambda The scalar value
*
*   @return The new vector after the multiplication
*
*/
LX_Vector2D& operator *(LX_Vector2D& v,float lambda);

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
float scalar_product(const LX_Vector2D& u,const LX_Vector2D& v);

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
float vector_product(const LX_Vector2D& u,const LX_Vector2D& v);

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
float vector_norm(const LX_Vector2D& v);

/**
*   @fn bool isNullVector(const LX_Vector2D& v)
*
*   Check if the vector is a zero vector
*
*   @param v The vector
*
*   @return True if the vector has coordinates equal to 0, False otherwise
*
*/
bool isNullVector(const LX_Vector2D& v);

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
bool collinear(const LX_Vector2D& u,const LX_Vector2D& v);

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
LX_Vector2D& multiply(LX_Vector2D& v,float lambda);


/**
*   @fn LX_Vector2D& normalize(LX_Vector2D& v)
*
*   Vector normalization
*
*   @param v The vector
*
*   @return The normalized vector
*
*   @note If the vector is a null vector, then the same vector is returned
*
*/
LX_Vector2D& normalize(LX_Vector2D& v);

};

#endif // LX_VECTOR2D_HPP_INCLUDED
