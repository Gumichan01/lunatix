#ifndef LX_VECTOR2D_HPP_INCLUDED
#define LX_VECTOR2D_HPP_INCLUDED


/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Vector2D.hpp
*	@brief The vector 2D library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

/**
*   @todo operators of LX_Vector2D :
*   - '=' : assignment (it should be explicitly defined into the library)
*   - '==' : same direction and same norm
*   - '!=' : not same direction or (||) not same norm
*   - '>' : same direction and first norm > second norm
*   - '<' : same direction and first norm < second norm
*   - '>=' : same direction and first norm >= second norm
*   - '<=' : same direction and first norm <= second norm
*   - '+' : addition of x and y between two vectors
*   - '-' : substraction of x and y between two vectors
*   - '++' : vector's coordinates + 1
*   - '--' : vector's coordinates - 1
*   - '+=' : vector's coordinates + 2nd vector's coordinates
*/

/**
*   @todo functions of LX_Vector2D :
*   - LX_Vector2D add(LX_Vector2D&, float)
*   - LX_Vector2D sub(LX_Vector2D&, float)
*   - LX_Vector2D multiply(LX_Vector2D&, float)
*   - LX_Vector2D divide(LX_Vector2D&, float)
*   - LX_Vector2D normalize(LX_Vector2D&)
*   - bool isZeroVector(LX_Vector2D&)
*/

/**
*   @struct LX_Vector2D
*   @brief The vector2D structure
*
*   This structure describes a vector
*/
typedef struct LX_Vector2D
{
    float vx;                     /**< The x position */
    float vy;                     /**< The y position */

} LX_Vector2D;  /**< @brief The vector2D */


float scalar_product(LX_Vector2D& u,LX_Vector2D& v);
float vector_product(LX_Vector2D& u,LX_Vector2D& v);
float vector_norm(LX_Vector2D& u);


#endif // LX_VECTOR2D_HPP_INCLUDED
