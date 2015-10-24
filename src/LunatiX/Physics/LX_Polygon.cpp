

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
*	@file LX_Polygon.cpp
*	@brief The Implementation of the polygon
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <new>

#include <LunatiX/LX_Hitbox.hpp>
#include <LunatiX/LX_Polygon.hpp>
#include <LunatiX/LX_Vector2D.hpp>
#include <LunatiX/LX_Physics.hpp>
#include <LunatiX/LX_Error.hpp>

using namespace std;
using namespace LX_Physics;


/**
*   @fn LX_PolygonException::LX_PolygonException(std::string err)
*
*   Build the LX_PolygonException class
*
*   @param err The error string
*
*/
LX_PolygonException::LX_PolygonException(std::string err)
{
    stringError = err;
}


/**
*   @fn const char * LX_PolygonException::what() const throw()
*
*   Get the error string
*
*   @return The error string
*/
const char * LX_PolygonException::what() const throw()
{
    return stringError.c_str();
}


LX_PolygonException::~LX_PolygonException() throw() {}



/**
*   @fn LX_Polygon::LX_Polygon(const unsigned int nb)
*
*   Create a new instance of LX_Polygon
*
*   @param nb The number of edges to build the polygon
*
*/
LX_Polygon::LX_Polygon(const unsigned int nb)
    : points(NULL),nbPoints(nb), cursor(0), convex(false)
{
    if(nb > 2)
    {
        points = new (nothrow) LX_Point[nb];

        if(points == NULL)
            throw LX_PolygonException("constr: Cannot allocate the points\n");

    }
    else
        throw LX_PolygonException("constr: Not enough points in the polygon\n");
}


/**
*   @fn bool LX_Polygon::addPoint(const int x, const int y)
*
*   Set a new point into the polygon according to its coordinates
*
*   @param x The x position of the point
*   @param y The y position of the point
*
*   @return TRUE if the point was added, FALSE otherwise
*
*/
bool LX_Polygon::addPoint(const int x, const int y)
{
    if(cursor < nbPoints)
    {
        points[cursor].x = x;
        points[cursor].y = y;

        cursor++;

        // Update the convexity when the polygon has at least 3 edges
        if(cursor >= 3)
            convexity();

        return true;
    }

    return false;
}


/**
*   @fn bool LX_Polygon::addPoint(LX_Point *p)
*
*   Set a new point into the polygon
*
*   @param p The new edge to add
*
*   @return TRUE if the point was added, FALSE otherwise
*
*/
bool LX_Polygon::addPoint(LX_Point *p)
{
    return addPoint(p->x,p->y);
}


/**
*   @fn unsigned int LX_Polygon::numberOfEdges(void) const
*
*   Get the maximum number of edges
*
*   @return The maximum number of edges of the polygon
*
*   @note The number of edges is the same as
*           what you sent to the polygon constructor
*
*/
unsigned int LX_Polygon::numberOfEdges(void) const
{
    return nbPoints;
}


/**
*   @fn unsigned int LX_Polygon::numberOfRealEdges(void) const
*
*   Get the real number of defined edges
*
*   @return The real number of edges of the polygon
*
*   @note The number of edges may be different from the number
*           you gave to the polygon constructor, becauce you have not
*           defined all points.
*
*/
unsigned int LX_Polygon::numberOfRealEdges(void) const
{
    return cursor;
}


/**
*   @fn LX_Point LX_Polygon::getPoint(const unsigned int index) const
*
*   Get the point at a specified position
*
*   @param index The index of the point
*
*   @return A copy of the point
*
*   @exception  LX_PolygonException If the index refers
*               to an out of bounds position
*
*/
LX_Point LX_Polygon::getPoint(const unsigned int index) const
{
    if(index < cursor)
    {
        return points[index];
    }

    throw LX_PolygonException("getPoint: index Out of bounds ");
}


/**
*   @fn bool LX_Polygon::isConvex(void)
*
*   Check the convexity of the polygon
*
*   @return TRUE if the polygon is convex, false otherwise
*
*   @note Actually, the convexity of the polygon is dynamically evaluated
*           each time you define a new point.
*           The result is stored in an internal variable
*
*/
bool LX_Polygon::isConvex(void)
{
    return convex;
}


/*
*
*   Evaluate the convexity of the polygon
*
*/
void LX_Polygon::convexity(void)
{
    // Vectors
    LX_Vector2D AO;
    LX_Vector2D OB;

    // Scalar product and angle
    int cross_product;

    bool haveSign = false;
    enum Sign {POSITIVE,NEGATIVE,NONE} s = NONE;

    const unsigned int n = (cursor == nbPoints) ? nbPoints : cursor;


    for(unsigned int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            AO.vx = points[i].x - points[n-1].x;
            AO.vy = points[i].y - points[n-1].y;
        }
        else
        {
            AO.vx = points[i].x - points[i-1].x;
            AO.vy = points[i].y - points[i-1].y;
        }

        if(i == n-1)
        {
            OB.vx = points[0].x - points[i].x;
            OB.vy = points[0].y - points[i].y;
        }
        else
        {
            OB.vx = points[i+1].x - points[i].x;
            OB.vy = points[i+1].y - points[i].y;
        }

        cross_product = static_cast<int>(vector_product(AO,OB));

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
                case POSITIVE :
                    if(cross_product < 0)
                    {
                        convex = false;
                        return;
                    }
                    break;

                case NEGATIVE :
                    if(cross_product > 0)
                    {
                        convex = false;
                        return;
                    }
                    break;

                default :
                    break;
            }
        }
    }

    convex = true;
}


/**
*   @fn void LX_Polygon::move(int vx, int vy)
*
*   Move the polygon to a direction
*
*   @param vx The x direction
*   @param vy The y direction
*
*/
void LX_Polygon::move(const int vx, const int vy)
{
    movePoint(points[0],vx,vy);
    movePoint(points[1],vx,vy);
    movePoint(points[2],vx,vy);

    const unsigned int n = numberOfEdges();

    for(unsigned int i = 3; i < n; i++)
    {
        movePoint(points[i],vx,vy);
    }
}


/**
*   @fn void LX_Polygon::move(const LX_Vector2D& v)
*
*   Move the polygon to a direction
*
*   @param v The vector that indicates the direction
*
*/
void LX_Polygon::move(const LX_Vector2D& v)
{
    move(v.vx, v.vy);
}


/**
*   @fn void LX_Polygon::move(int vx, int vy)
*
*   Move the polygon to a position
*
*   @param vx The x position
*   @param vy The y position
*
*/
void LX_Polygon::moveTo(int vx, int vy)
{
    movePointTo(points[0],vx,vy);
    movePointTo(points[1],vx,vy);
    movePointTo(points[2],vx,vy);

    const unsigned int n = numberOfEdges();

    for(unsigned int i = 3; i < n; i++)
    {
        movePointTo(points[i],vx,vy);
    }
}



/**
*   @fn LX_Polygon::~LX_Polygon()
*
*   Destroy the instance of the polygon
*
*/
LX_Polygon::~LX_Polygon()
{
    delete [] points;
}

