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
*	@brief The LX_Polygon file
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.4
*
*/


struct LX_Point;



/**
*	@class LX_Polygon
*	@brief The LX_Polygon class
*
*   This class defines a polygon
*
*/
class LX_Polygon{


    LX_Point *points;               /**< An array of LX_Point */
    unsigned int nbPoints;          /**< The number of points */
    unsigned int cursor;            /**< The size */
    bool convex;                    /**< this flag show if the polygon is convex or not */

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


