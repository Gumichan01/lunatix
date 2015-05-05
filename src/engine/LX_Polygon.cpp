

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Polygon.cpp
*	@brief The LX_Polygon Implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.4
*
*/

#include <new>

#include "LX_Hitbox.hpp"
#include "LX_Polygon.hpp"
#include "LX_Error.hpp"

using namespace std;


LX_Polygon::LX_Polygon(const unsigned int nb)
{
    if(nb > 2)
    {
        points = new (nothrow) LX_Point[nb];

        if(points == NULL)
        {
            LX_SetError("LX_Polygon constructor: Cannot allocate the points\n");
            nbPoints = 0;
            cursor = nbPoints;
        }
        else
        {
            nbPoints = nb;
            cursor = 0;
        }

    }
}



bool LX_Polygon::addPoint(const int x, const int y)
{
    if(cursor < nbPoints)
    {
        points[cursor].x = x;
        points[cursor].y = y;

        cursor++;

        return true;
    }

    return false;
}



bool LX_Polygon::addPoint(LX_Point *p)
{
    return addPoint(p->x,p->y);
}



LX_Polygon::~LX_Polygon()
{
    delete [] points;
}



























