#ifndef LX_POLYGON_H_INCLUDED
#define LX_POLYGON_H_INCLUDED


/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/


/**
*	@file LX_Polygon.hpp
*	@brief The polygon file
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <string>

namespace LX_Physics
{

struct LX_Point;
struct LX_Vector2D;

/**
*   @class LX_PolygonException
*   @brief The exception class of LX_Window
*
*   This class describes the exception occured when
*   the polygon cannot be loaded.
*/
class LX_PolygonException : public std::exception
{
    std::string string_error;

public :

    /// Construct the exception
    LX_PolygonException(std::string err);

    /// Construct the exception by copy
    LX_PolygonException(const LX_PolygonException& pex);

    /// Get the error message
    const char * what() const noexcept;

    /// Destroy the exception
    ~LX_PolygonException() noexcept;
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

    /**
    *   @fn LX_Polygon::LX_Polygon(const unsigned int nb)
    *
    *   Create a new instance of LX_Polygon
    *
    *   @param nb The number of edges to build the polygon
    *
    */
    LX_Polygon(const unsigned int nb);

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
    bool addPoint(const int x, const int y);

    /**
    *   @fn bool LX_Polygon::addPoint(const LX_Point& p)
    *
    *   Set a new point into the polygon
    *
    *   @param p The new edge to add
    *
    *   @return TRUE if the point was added, FALSE otherwise
    *
    */
    bool addPoint(const LX_Point& p);

    /**
    *   @fn unsigned int LX_Polygon::numberOfEdges(void) const
    *
    *   Get the maximum number of edges
    *
    *   @return The maximum number of edges of the polygon
    *
    *   @note   The number of edges is the same as the defined value
    *           in the polygon constructor
    *
    */
    unsigned int numberOfEdges(void) const;

    /**
    *   @fn unsigned int LX_Polygon::numberOfRealEdges(void) const
    *
    *   Get the real number of defined edges
    *
    *   @return The real number of edges of the polygon
    *
    *   @note   The number of edges may be different from the defined value
    *           in the polygon constructor, because the points of the polygon
    *           are not completely set.
    *
    */
    unsigned int numberOfRealEdges(void) const;

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
    LX_Point getPoint(const unsigned int index) const;

    /**
    *   @fn bool LX_Polygon::isConvex(void)
    *
    *   Check the convexity of the polygon
    *
    *   @return TRUE if the polygon is convex, false otherwise
    *
    *   @note Actually, the convexity of the polygon is dynamically evaluated
    *           each time a new point in added using LX_Polygon::addPoint().
    *           The result is stored in an internal variable
    *
    */
    bool isConvex(void);

    /**
    *   @fn void LX_Polygon::move(const float vx, const float vy)
    *
    *   Move the polygon to a direction
    *
    *   @param vx The x direction
    *   @param vy The y direction
    */
    void move(const float vx, const float vy);

    /**
    *   @fn void LX_Polygon::move(const LX_Vector2D& v)
    *
    *   Move the polygon to a direction
    *
    *   @param v The vector that indicates the direction
    */
    void move(const LX_Vector2D& v);

    /**
    *   @fn void LX_Polygon::moveTo(int vx, int vy)
    *
    *   Move the polygon to a position
    *
    *   @param vx The x position
    *   @param vy The y position
    *
    */
    void moveTo(int vx, int vy);

    /**
    *   @fn LX_Polygon::~LX_Polygon()
    *
    *   Destroy the instance of the polygon
    *
    */
    ~LX_Polygon();
};

};

#endif
