#ifndef POLY_HITBOX_H_INCLUDED
#define POLY_HITBOX_H_INCLUDED



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
*	@file LX_Polygon.h
*	@brief The polygon hitbox Library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 14th, 2014
*
*/

#include<new>

#include "LX_Point.h"

/**
*
*   @class LX_Polygon
*   @brief The LX_Polygon hitbox
*
*   This class describes the polygon hitbox
*/
class LX_Polygon{

        LX_Point *list_points;     /**<The list of all the points of the polygon*/
        unsigned int size;      /**<The size of the list*/
        unsigned int cursor;    /**<The curssor which keep the information of the position of the first available position*/

    public :

/**
*
*	@fn LX_Polygon(int nbLX_Points)
*
*	The LX_Polygon constructor
*
*   @param nbLX_Points : the points number
*
*/
        LX_Polygon(unsigned int nbLX_Points)
        {
            list_points = new (std::nothrow) LX_Point[nbLX_Points];

            if(list_points == NULL)
            {
                perror("Error occured in the Poly_Hit_box constructor while creating the points list ");
                delete this;        /// @todo put an exception class for Polygon
            }

            size = nbLX_Points;
            cursor = 0;
        }

        //LX_Point * getLX_Points();
        LX_Point * getLX_PointAt(unsigned int i);
        unsigned int getSize();
        bool putLX_Point(LX_Point *p);
        bool putLX_Point(int a, int b);


        ~LX_Polygon()
        {
            delete [] list_points;
        }

};

#endif // POLY_HITBOX_H_INCLUDED


