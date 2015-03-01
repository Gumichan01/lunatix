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

#include <new>
#include <exception>
#include <iostream>

#include "LX_Point.h"


/**
*   @class LX_Polygon_Point_exception
*   @brief The LX_Polygon_Point_exception class.
*
*   This class describes the exception occured when the font loading fails.
*
*/
class LX_Polygon_Point_exception : public std::exception
{
    public :

    std::string str_err;                        /**< The string where the error message will be conteined*/

/**
*   @fn LX_Polygon_Point_exception(std::string err)
*   Build the LX_Polygon_Point_exception class
*   @param err the error string
*/
    LX_Polygon_Point_exception(std::string err)
    {
        str_err = err;
    }

/**
*   @fn const char * what() const throw()
*   Get the error string
*   @return the error string
*/
    const char * what() const throw() {return str_err.c_str() ;}

    ~LX_Polygon_Point_exception() throw(){}
};




/**
*
*   @class LX_Polygon
*   @brief The LX_Polygon hitbox
*
*   This class describes the polygon hitbox
*/
class LX_Polygon{
        ///@todo change the LX_Point array to a truly LX_Point vector
        LX_Point *list_points;      /**<The list of all the points of the polygon*/
        unsigned int size;          /**<The size of the list*/
        unsigned int cursor;        /**<The curssor which keep the information of the position of the first available position*/

    public :

/**
*
*	@fn LX_Polygon(int nb_Points)
*
*	The LX_Polygon constructor
*
*   @param nb_Points : the points number
*
*/
        LX_Polygon(unsigned int nb_Points)
        {
            list_points = new (std::nothrow) LX_Point[nb_Points];

            if(list_points == NULL)
            {
                throw LX_Polygon_Point_exception("The points list initialization fails");
            }

            size = nb_Points;
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


