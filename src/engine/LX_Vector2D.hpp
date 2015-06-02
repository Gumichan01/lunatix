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
*	@version 0.5
*
*/



/**
*   @struct LX_Vector2D
*   @brief The vector2D structure
*
*   This structure describes a vector
*/
typedef struct LX_Vector2D
{

    int vx;                     /**< The x position */
    int vy;                     /**< The y position */

} LX_Vector2D;  /**< @brief The vector2D */



float scalar_product(LX_Vector2D *u,LX_Vector2D *v);

float vector_product(LX_Vector2D *u,LX_Vector2D *v);

float vector_norm(LX_Vector2D *u);


#endif // LX_VECTOR2D_HPP_INCLUDED
