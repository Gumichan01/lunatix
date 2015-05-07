

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
#include "LX_Vector2D.hpp"
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

        // Update the convexity when the polygon has at least 3 edges
        if(cursor == 3)
            convexity();

        return true;
    }

    return false;
}



bool LX_Polygon::addPoint(LX_Point *p)
{
    return addPoint(p->x,p->y);
}



unsigned int LX_Polygon::numberOfPoints(void)
{
    return nbPoints;
}



LX_Point * LX_Polygon::getPoint(const unsigned int index)
{
    if(index < cursor)
    {
        return &points[index];
    }

    return NULL;
}



bool LX_Polygon::isConvex(void)
{
    return convex;
}



void LX_Polygon::convexity(void)
{
    // Vectors
    LX_Vector2D AO;
    LX_Vector2D OB;

    // Distance
    float distanceAO;
    float distanceOB;

    // Scalar product and angle
    int cross_product;
    float cosAngle;
    int angle;

    bool haveSign = false;
    enum Sign{POSITIVE,NEGATIVE} s;

    const unsigned int n = (cursor == nbPoints) ? nbPoints : cursor;


    for(int i = 0; i < n; i++)
    {
        if(i = 0)
        {
            AO.vx = points[i].x - points[n-1].x;
            AO.vy = points[i].y - points[n-1].y;
        }
        else
        {
            AO.vx = points[i].x - points[i-1].x;
            AO.vy = points[i].y - points[i-1].y;
        }

        if(i = n-1)
        {
            OB.vx = points[0].x - points[i].x;
            OB.vy = points[0].y - points[i].y;
        }
        else
        {
            OB.vx = points[i+1].x - points[i].x;
            OB.vy = points[i+1].y - points[i].y;
        }

        cross_product = (int) vector_product(&AO,&OB);

        if(!haveSign)
        {
            if(cross_product > 0)
                s = POSITIVE;
            else if(cross_product < 0)
                s = NEGATIVE;
            else
            {
                convex = false;
                return;
            }

            haveSign = true;
        }
        else
        {
            switch(s)
            {
                case POSITIVE : if(cross_product < 0)
                                {
                                    convex = false;
                                    return;
                                }
                                break;

                case NEGATIVE : if(cross_product > 0)
                                {
                                    convex = false;
                                    return;
                                }
                                break;

                default : break;
            }
        }

    }

    convex = true;
}


LX_Polygon::~LX_Polygon()
{
    delete [] points;
}



























