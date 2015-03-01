

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
*	@file LX_Polygon.cpp
*	@brief The LX_Polygon file
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 14th, 2014
*/


#include "LX_Polygon.h"

/*
*
*	@fn LX_Point * LX_Polygon::getLX_Points()
*
*	Returns the points of the polygon
*
*
*	@return the points array
*

LX_Point * LX_Polygon::getLX_Points()
{
    return list_points;
}*/


/**
*
*	@fn LX_Point * LX_Polygon::getLX_PointAt(unsigned int i)
*
*	Returns the point at the position specified
*
*   @param i : the position of the point in the array
*
*	@return the center
*/

LX_Point * LX_Polygon::getLX_PointAt(unsigned int i)
{
    if (i <= cursor)
    {
        return &list_points[i];
    }

    return NULL;

}

/**
*
*	@fn unsigned int LX_Polygon::getSize()
*
*	returns the size of the array
*
*	@return the size
*/

unsigned int LX_Polygon::getSize()
{
    return cursor;
}

/**
*
*	@fn bool LX_Polygon::putLX_Point(LX_Point *p)
*
*	Puts the point into the array
*
*   @param p : the point
*
*	@return TRUE if it is OK, FALSE otherwise
*/

bool LX_Polygon::putLX_Point(LX_Point *p)
{
    return putLX_Point(p->x, p->y);
}


/**
*
*	@fn bool LX_Polygon::putLX_Point(int x, int y)
*
*	Puts the point into the array
*
*   @param x : the x position
*   @param y : the y position
*
*	@return TRUE if it is OK, FALSE otherwise
*/

bool LX_Polygon::putLX_Point(int x, int y)
{

    if(cursor < size)
    {
        list_points[cursor].x = x;
        list_points[cursor].y = y;
        cursor++;
        return true;
    }

    return false;

}





