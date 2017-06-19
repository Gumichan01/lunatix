
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_VECTOR2D_HPP_INCLUDED
#define LX_VECTOR2D_HPP_INCLUDED

/**
*   @file LX_Vector2D.hpp
*   @brief The vector 2D library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*/


namespace LX_Physics
{

struct LX_Point;

/**
*   @struct LX_Vector2D
*   @brief The vector2D structure
*
*   This structure describes a 2-dimension vector
*/
struct LX_Vector2D
{
    float vx;   /**< The x velocity */
    float vy;   /**< The y velocity */

    /// No argument constructor
    LX_Vector2D();
    /// Construct a vector using coordinates
    LX_Vector2D(float x, float y);
    /// Construct a vector using points
    LX_Vector2D(const LX_Point& ori, const LX_Point& im);
    /// Construct a vector using coordinates
    LX_Vector2D(const LX_Vector2D& v);
    /// Vector2D assignment
    LX_Vector2D& operator =(const LX_Vector2D& v);
};

/**
*   @fn bool operator ==(const LX_Vector2D& u,const LX_Vector2D& v)
*
*   Check if two vectors are equal
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return TRUE if they are equal, FALSE otherwise

*/
bool operator ==(const LX_Vector2D& u,const LX_Vector2D& v);
/**
*   @fn bool operator !=(const LX_Vector2D& u,const LX_Vector2D& v)
*
*   Check if two vectors are not equal
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return TRUE if they are not equal, FALSE otherwise
*/
bool operator !=(const LX_Vector2D& u,const LX_Vector2D& v);
/**
*   @fn LX_Vector2D operator +(const LX_Vector2D& u,const LX_Vector2D& v)
*
*   Addition between two vectors
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return The resulting vector
*/
LX_Vector2D operator +(const LX_Vector2D& u,const LX_Vector2D& v);
/**
*   @fn LX_Vector2D& operator +=(LX_Vector2D& u,const LX_Vector2D& v)
*
*   Addition between two vectors -> 'u += v' <=> 'u = u + v'
*
*   @param [in,out] u The vector that will be modified
*   @param [in] v The second vector
*
*   @return The resulting vector
*/
LX_Vector2D& operator +=(LX_Vector2D& u,const LX_Vector2D& v);
/**
*   @fn LX_Vector2D operator -(const LX_Vector2D& u,const LX_Vector2D& v)
*
*   Substraction between two vectors
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return The resulting vector
*/
LX_Vector2D operator -(const LX_Vector2D& u,const LX_Vector2D& v);
/**
*   @fn LX_Vector2D& operator -=(LX_Vector2D& u,const LX_Vector2D& v)
*
*   Substraction between two vectors -> 'u -= v' <=> 'u = u - v'
*
*   @param [in,out] u The vector that will be modified
*   @param [in] v The second vector
*
*   @return The resulting vector
*/
LX_Vector2D& operator -=(LX_Vector2D& u,const LX_Vector2D& v);
/**
*   @fn LX_Vector2D operator -(const LX_Vector2D& v)
*
*   Get the opposite of the vector
*
*   @param [in] v The vector
*
*   @return The opposite vector
*/
LX_Vector2D operator -(const LX_Vector2D& v);
/**
*   @fn LX_Vector2D& operator ++(LX_Vector2D& v)
*
*   Prefix increment
*
*   @param [in,out] v The vector
*
*   @return The incremented vector
*/
LX_Vector2D& operator ++(LX_Vector2D& v);
/**
*   @fn LX_Vector2D operator ++(LX_Vector2D& v,int)
*
*   Postfix increment
*
*   @param [in] v The vector
*
*   @return The vector before the incrementation
*/
LX_Vector2D operator ++(LX_Vector2D& v,int);
/**
*   @fn LX_Vector2D& operator --(LX_Vector2D& v)
*
*   Prefix decrement
*
*   @param [in,out] v The vector
*
*   @return The incremented vector
*/
LX_Vector2D& operator --(LX_Vector2D& v);
/**
*   @fn LX_Vector2D operator --(LX_Vector2D& v,int)
*
*   Postfix decrement
*
*   @param [in] v The vector
*
*   @return The vector before the incrementation
*/
LX_Vector2D operator --(LX_Vector2D& v,int);
/**
*   @fn LX_Vector2D operator *(LX_Vector2D& v,float lambda)
*
*   Scalar multiplication (syntactic sugar of multiply)
*
*   @param [in] v The vector
*   @param [in] lambda The scalar value
*
*   @return A new vector after the multiplication
*/
LX_Vector2D operator *(LX_Vector2D& v,float lambda);
/**
*   @fn LX_Vector2D& operator *(LX_Vector2D& v,float lambda)
*
*   Scalar multiplication (syntactic sugar of multiply) -> 'u *= λ' <=> 'u = u * λ'
*
*   @param [in,out] v The vector
*   @param [in] lambda The scalar value
*
*   @return A new vector after the multiplication
*/
LX_Vector2D& operator *=(LX_Vector2D& v,float lambda);
/**
*   @fn LX_Vector2D& operator /(LX_Vector2D& v,float lambda)
*
*   Scalar division
*
*   @param [in] v The vector
*   @param [in] lambda The scalar value
*
*   @return The vector after the division
*/
LX_Vector2D operator /(LX_Vector2D& v,float lambda);
/**
*   @fn LX_Vector2D& operator /(LX_Vector2D& v,float lambda)
*
*   Scalar division -> 'u /= λ' <=> 'u = u / λ'
*
*   @param [in,out] v The vector
*   @param [in] lambda The scalar value
*
*   @return The vector after the division
*/
LX_Vector2D& operator /=(LX_Vector2D& v,float lambda);

/**
*   @fn float scalar_product(const LX_Vector2D& u,const LX_Vector2D& v)
*
*   Calculate the scalar product of 2 vectors
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return The scalar product
*/
float scalar_product(const LX_Vector2D& u,const LX_Vector2D& v);
/**
*   @fn float vector_product(const LX_Vector2D& u,const LX_Vector2D& v)
*
*   Calculate the vector product of 2 vectors
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return The vector product
*/
float vector_product(const LX_Vector2D& u,const LX_Vector2D& v);
/**
*   @fn float vector_norm(const LX_Vector2D& v)
*
*   Calculate the norm of a vector
*
*   @param [in] v The vector
*
*   @return The norm of the vector
*/
float vector_norm(const LX_Vector2D& v);

/**
*   @fn bool isNullVector(const LX_Vector2D& v)
*
*   Check if the vector is a zero vector
*
*   @param [in] v The vector
*
*   @return True if the vector has coordinates equal to 0, False otherwise
*/
bool isNullVector(const LX_Vector2D& v);
/**
*   @fn bool collinear(const LX_Vector2D& u,const LX_Vector2D& v)
*
*   Check if two vectors are colinear
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return True if they are colinear, False otherwise
*/
bool collinear(const LX_Vector2D& u,const LX_Vector2D& v);

/**
*   @fn LX_Vector2D& multiply(LX_Vector2D& v, float lambda)
*
*   Scalar multiplication
*
*   @param [in,out] v The vector
*   @param [in] lambda The scalar value
*
*   @return The new vector after the multiplication
*/
LX_Vector2D& multiply(LX_Vector2D& v,float lambda);
/**
*   @fn LX_Vector2D& normalize(LX_Vector2D& v)
*
*   Vector normalization
*
*   @param [in,out] v The vector
*
*   @return The normalized vector
*
*   @note If the vector is a null vector, then the same vector is returned
*/
LX_Vector2D& normalize(LX_Vector2D& v);

}

#endif // LX_VECTOR2D_HPP_INCLUDED
