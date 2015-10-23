#ifndef LX_POLYGON_H_INCLUDED
#define LX_POLYGON_H_INCLUDED



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
*	@file LX_Polygon.hpp
*	@brief The polygon file
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

/// @todo Modifiy the signature of the polygon getter

struct LX_Point;

#include <iostream>


/**
*   @class LX_PolygonException
*   @brief The exception class of LX_Window
*
*   This class describes the exception occured when
*   the SDL_Window instance cannot be loaded.
*
*/
class LX_PolygonException : public std::exception
{
    std::string stringError;

public :

    LX_PolygonException(std::string err);

    const char * what() const throw();

    ~LX_PolygonException() throw();
};




/**
*	@class LX_Polygon
*	@brief The polygon
*
*   This class defines a polygon
*
*/
class LX_Polygon
{

    LX_Point *points;               /* An array of LX_Point     */
    unsigned int nbPoints;          /* The number of points     */
    unsigned int cursor;            /* The size                 */
    bool convex;                    /* If the polygon is convex */

    LX_Polygon(LX_Polygon& p);
    LX_Polygon& operator =(LX_Polygon& p);

    void convexity(void);

public :

    LX_Polygon(const unsigned int nb);

    bool addPoint(const int x, const int y);
    bool addPoint(LX_Point *p);

    unsigned int numberOfEdges(void) const;
    unsigned int numberOfRealEdges(void) const;

    LX_Point * getPoint(const unsigned int index) const;

    bool isConvex(void);

    ~LX_Polygon();

};


#endif


