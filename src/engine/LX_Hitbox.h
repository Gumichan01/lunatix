

#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED


/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Hitbox.h
*	@brief The hitbox library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date July 28th, 2014
*
*
*/


struct SDL_Rect;
typedef SDL_Rect LX_AABB;       /**< The rectangle hitbox (SDL_Rect)*/


/**
*   @struct LX_Point
*   @brief The point structure
*
*   This point is described by the x and y field
*/
typedef struct LX_Point{

    int x;      /**<The x position of the point*/
    int y;      /**<The y position of the point*/

}LX_Point;      /**< */



/**
*   @struct LX_Circle
*
*   @brief The circle structure
*
*/
typedef struct LX_Circle{

    int xCenter;                /**<The x position of circle center*/
    int yCenter;                /**<The y position of circle center*/
    unsigned int radius;        /**<The circle radius*/

    // The square radius will never be less than 0
    int square_radius; /**<The square radius (for a collision optimization)*/


}LX_Circle;     /**< */



#endif // HITBOX_H_INCLUDED






























