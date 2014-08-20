#ifndef LX_EUCLIDE_H_INCLUDED
#define LX_EUCLIDE_H_INCLUDED



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
*	@file LX_euclide.h
*	@brief The library includes different non-standard mathemetic operation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 28th, 2014
*
*
*
*/

#include "Point.h"
#include <cmath>

/**
*
*	@fn int euclide_square_distance( int x1, int y1, int x2, int y2)
*
*	This function calculates the Euclide square distance
*
*	@param	x1 The x location of object no 1
*   @param  y1 The y location of object no 1
*	@param	x2 The x location of object no 2
*   @param	y2 The y location of object no 2
*
*	@return an integer value
*
*/
int euclide_square_distance( int x1, int y1, int x2, int y2)
{
    return( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
}


/**
*
*	@fn int euclide_distance( int x1, int y1, int x2, int y2)
*
*	This function calculates the Euclide distance
*
*	@param	x1 The x location of object no 1
*   @param  y1 The y location of object no 1
*	@param	x2 The x location of object no 2
*   @param	y2 The y location of object no 2
*
*	@return an integer value
*
*/
int euclide_distance( int x1, int y1, int x2, int y2)
{
    return sqrt(euclide_square_distance(x1,y1,x2,y2));
}


/**
*
*	@fn int euclide_square_distance( Point *p1, Point *p2)
*
*	This function calculates the Euclide square distance
*
*	@param	p1 The point no 1
*   @param	p2 The point no 2
*
*	@return an integer value
*
*/
int euclide_square_distance( Point *p1, Point *p2)
{
    return euclide_square_distance(p1->x,p1->y,p2->x,p2->y);
}


/**
*
*	@fn int euclide_distance( Point *p1, Point *p2)
*
*	This function calculates the Euclide square distance
*
*	@param	p1 The point no 1
*   @param	p2 The point no 2
*
*	@return an integer value
*
*/
int euclide_distance( Point *p1, Point *p2)
{
    return sqrt(euclide_square_distance(p1,p2));
}


#endif // LX_EUCLIDE_H_INCLUDED











