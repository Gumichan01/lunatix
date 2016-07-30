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

#include <LunatiX/utils/utf8_string.hpp>
#include <vector>

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
    std::string _string_error;

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
    std::vector<LX_Point> _points;   /* A sequence of LX_Point objects   */
    bool _convex;                     /* If the polygon is convex         */

    LX_Polygon(LX_Polygon& p);
    LX_Polygon& operator =(LX_Polygon& p);

    void convexity_(void);

public :

    /**
    *   @fn LX_Polygon::LX_Polygon()
    *
    *   Create a new instance of LX_Polygon
    *
    */
    LX_Polygon();

    /**
    *   @fn void LX_Polygon::addPoint(const int x, const int y)
    *
    *   Set a new point into the polygon according to its coordinates
    *
    *   @param x The x position of the point
    *   @param y The y position of the point
    *
    */
    void addPoint(const int x, const int y);

    /**
    *   @fn void LX_Polygon::addPoint(const LX_Point& p)
    *
    *   Set a new point into the polygon
    *
    *   @param p The new edge to add
    *
    */
    void addPoint(const LX_Point& p);

    /**
    *   @fn unsigned long LX_Polygon::numberOfEdges(void) const
    *
    *   Get the number of points
    *
    *   @return The number of edges of the polygon
    *
    */
    unsigned long numberOfEdges(void) const;

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
    *   @fn bool LX_Polygon::isConvex(void) const
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
    bool isConvex(void) const;

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

    /// Destructor
    ~LX_Polygon() = default;
};

};

#endif
