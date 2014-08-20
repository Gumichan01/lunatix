

#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED


/*
*	Copyright (C) 2014 Luxon Jean-Pierre
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
*	@version 0.1
*	@date July 28th, 2014
*
*
*/

#include <SDL/SDL.h>

/*
typedef struct SDL_Rect{

    short x,y,w,h;

}LX_AABB;*/

typedef SDL_Rect LX_AABB;       /**< The rectangle hitbox (SDL_Rect)*/


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
    unsigned int square_radius; /**<The square radius (for a collision optimization)*/



}LX_Circle;     /**< */



#endif // HITBOX_H_INCLUDED






























