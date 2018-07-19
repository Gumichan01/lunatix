
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

#ifndef VECTOR2D_HPP_INCLUDED
#define VECTOR2D_HPP_INCLUDED

/**
*   @file Vector2D.hpp
*   @brief The vector 2D library
*   @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <Lunatix/utils/float.hpp>

namespace lx
{

namespace Physics
{

/**
*   @struct Vector2D
*   @brief The vector2D structure
*
*   This structure describes a 2-dimension vector
*/
struct Vector2D final
{
    Float vx;   /**< X velocity */
    Float vy;   /**< Y velocity */
};

/**
*   @fn bool operator ==(const Vector2D& u, const Vector2D& v) noexcept
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return TRUE if they are equal, FALSE otherwise

*/
bool operator ==( const Vector2D& u, const Vector2D& v ) noexcept;
/**
*   @fn bool operator !=(const Vector2D& u, const Vector2D& v) noexcept
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return TRUE if they are not equal, FALSE otherwise
*/
bool operator !=( const Vector2D& u, const Vector2D& v ) noexcept;
/**
*   @fn Vector2D operator +(const Vector2D u,const Vector2D v) noexcept
*
*   Addition between two vectors
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return The resulting vector
*/
Vector2D operator +( const Vector2D u, const Vector2D v ) noexcept;
/**
*   @fn Vector2D& operator +=(Vector2D& u, const Vector2D& v) noexcept
*
*   Addition between two vectors -> 'u += v' <=> 'u = u + v'
*
*   @param [in,out] u The vector that will be modified
*   @param [in] v The second vector
*
*   @return The resulting vector
*/
Vector2D& operator +=( Vector2D& u, const Vector2D& v ) noexcept;
/**
*   @fn Vector2D operator -(const Vector2D u, const Vector2D v) noexcept
*
*   Substraction between two vectors
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return The resulting vector
*/
Vector2D operator -( const Vector2D u, const Vector2D v ) noexcept;
/**
*   @fn Vector2D& operator -=(Vector2D& u, const Vector2D& v) noexcept
*
*   Substraction between two vectors -> 'u -= v' <=> 'u = u - v'
*
*   @param [in, out] u The vector that will be modified
*   @param [in] v The second vector
*
*   @return The resulting vector
*/
Vector2D& operator -=( Vector2D& u, const Vector2D& v ) noexcept;
/**
*   @fn Vector2D operator -(const Vector2D& v) noexcept
*
*   The opposite of the vector
*
*   @param [in] v The vector
*
*   @return The opposite vector
*/
Vector2D operator -( const Vector2D& v ) noexcept;
/**
*   @fn Vector2D& operator ++(Vector2D& v) noexcept
*
*   Prefix increment
*
*   @param [in, out] v The vector
*
*   @return The incremented vector
*/
Vector2D& operator ++( Vector2D& v ) noexcept;
/**
*   @fn Vector2D operator ++(Vector2D& v,int) noexcept
*
*   Postfix increment
*
*   @param [in] v The vector
*
*   @return The vector before the incrementation
*/
Vector2D operator ++( Vector2D& v, int ) noexcept;
/**
*   @fn Vector2D& operator --(Vector2D& v) noexcept
*
*   Prefix decrement
*
*   @param [in, out] v The vector
*
*   @return The incremented vector
*/
Vector2D& operator --( Vector2D& v ) noexcept;
/**
*   @fn Vector2D operator --(Vector2D& v, int) noexcept
*
*   Postfix decrement
*
*   @param [in] v The vector
*
*   @return The vector before the incrementation
*/
Vector2D operator --( Vector2D& v, int ) noexcept;
/**
*   @fn Vector2D operator *(Vector2D v, float lambda) noexcept
*
*   Scalar multiplication
*
*   @param [in] v The vector
*   @param [in] lambda The scalar value
*
*   @return A new vector after the multiplication
*/
Vector2D operator *( Vector2D v, float lambda ) noexcept;
/**
*   @fn Vector2D& operator *=(Vector2D& v, float lambda) noexcept
*
*   Scalar multiplication -> 'u *= λ' <=> 'u = u * λ'
*
*   @param [in, out] v The vector
*   @param [in] lambda The scalar value
*
*   @return A new vector after the multiplication
*/
Vector2D& operator *=( Vector2D& v, float lambda ) noexcept;
/**
*   @fn Vector2D& operator /(Vector2D v, float lambda) noexcept
*
*   Scalar division
*
*   @param [in] v The vector
*   @param [in] lambda The scalar value
*
*   @return The vector after the division
*/
Vector2D operator /( Vector2D v, float lambda ) noexcept;
/**
*   @fn Vector2D& operator /=(Vector2D& v, float lambda) noexcept
*
*   Scalar division -> 'u /= λ' <=> 'u = u / λ'
*
*   @param [in, out] v The vector
*   @param [in] lambda The scalar value
*
*   @return The vector after the division
*/
Vector2D& operator /=( Vector2D& v, float lambda ) noexcept;

/**
*   @fn Float scalar_product(const Vector2D& u,const Vector2D& v) noexcept
*
*   Calculate the scalar product of 2 vectors
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return The scalar product
*/
Float scalar_product( const Vector2D& u, const Vector2D& v ) noexcept;
/**
*   @fn Float vector_product(const Vector2D& u, const Vector2D& v) noexcept
*
*   Calculate the vector product of 2 vectors
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return The vector product
*/
Float vector_product( const Vector2D& u, const Vector2D& v ) noexcept;
/**
*   @fn Float vector_norm(const Vector2D& v) noexcept
*
*   @param [in] v The vector
*
*   @return The norm of the vector
*/
Float vector_norm( const Vector2D& v ) noexcept;

/**
*   @fn bool isNullVector(const Vector2D& v) noexcept
*
*   @param [in] v The vector
*
*   @return True if the vector has coordinates equal to 0, False otherwise
*/
bool isNullVector( const Vector2D& v ) noexcept;
/**
*   @fn bool collinear(const Vector2D& u, const Vector2D& v) noexcept
*
*   @param [in] u The first vector
*   @param [in] v The second vector
*
*   @return True if they are colinear, False otherwise
*/
bool collinear( const Vector2D& u, const Vector2D& v ) noexcept;
/**
*   @fn Vector2D& normalize(Vector2D& v) noexcept
*
*   @param [in, out] v The vector
*
*   @return The normalized vector
*
*   @note If the vector is a null vector, then the same vector is returned
*/
Vector2D& normalize( Vector2D& v ) noexcept;

}   // Physics

}   // lx

#endif // VECTOR2D_HPP_INCLUDED
