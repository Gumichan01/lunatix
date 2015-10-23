

#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED


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
*	@file LX_Hitbox.hpp
*	@brief The hitbox library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/


struct SDL_Rect;
typedef SDL_Rect LX_AABB;       /**< The rectangle hitbox (SDL_Rect) */


/**
*   @todo operators of LX_Point :
*   - '==' : same coordinates
*   - '!=' : not same coordinates
*/

/**
*   @struct LX_Point
*   @brief The point structure
*
*   This point is described by the x and y field
*/
typedef struct LX_Point
{

    int x;      /**< The x position of the point */
    int y;      /**< The y position of the point */

} LX_Point;     /**< The point */


/**
*   @todo operators of LX_Circle :
*   - '=' : assignment
*   - '==' : same coordinates and same radius
*   - '!=' : not same coordinates or not same radius
*   - '>' : first radius > second radius
*   - '<' : first radius < second radius
*   - '>=' : first radius >= second radius
*   - '<=' : first radius <= second radius
*/


/**
*   @struct LX_Circle
*   @brief The circle structure
*
*   This structure describe the circle
*/
typedef struct LX_Circle
{

    int xCenter;                /**< The x position of circle center */
    int yCenter;                /**< The y position of circle center */
    unsigned int radius;        /**< The circle radius */
    unsigned int square_radius; /**< The square radius */

} LX_Circle;    /**< @brief The circle */


#endif // HITBOX_H_INCLUDED


