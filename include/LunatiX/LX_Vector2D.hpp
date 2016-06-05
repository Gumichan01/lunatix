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
*	@version 0.7
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
typedef struct LX_Vector2D
{
    float vx;                     /**< The x velocity */
    float vy;                     /**< The y velocity */

    LX_Vector2D();
    LX_Vector2D(float x,float y);
    LX_Vector2D& operator =(const LX_Vector2D v);
    LX_Vector2D(const LX_Vector2D& v);

} LX_Vector2D;  /**< @brief The vector2D */


bool operator ==(const LX_Vector2D& u,const LX_Vector2D& v);
bool operator !=(const LX_Vector2D& u,const LX_Vector2D& v);

LX_Vector2D operator  +(LX_Vector2D& u,LX_Vector2D& v);
LX_Vector2D operator +=(LX_Vector2D& u,LX_Vector2D& v);
LX_Vector2D operator  -(LX_Vector2D& u,LX_Vector2D& v);
LX_Vector2D operator -=(LX_Vector2D& u,LX_Vector2D& v);

LX_Vector2D  operator  -(LX_Vector2D& v);
LX_Vector2D& operator ++(LX_Vector2D& v);
LX_Vector2D  operator ++(LX_Vector2D& v,int d);
LX_Vector2D& operator --(LX_Vector2D& v);
LX_Vector2D  operator --(LX_Vector2D& v,int d);

float scalar_product(const LX_Vector2D& u,const LX_Vector2D& v);
float vector_product(const LX_Vector2D& u,const LX_Vector2D& v);
float vector_norm(const LX_Vector2D& v);

bool isNullVector(const LX_Vector2D& v);
bool collinear(const LX_Vector2D& u,const LX_Vector2D& v);

LX_Vector2D& multiply(LX_Vector2D& v,float lambda);
LX_Vector2D& normalize(LX_Vector2D& v);

};

#endif // LX_VECTOR2D_HPP_INCLUDED
