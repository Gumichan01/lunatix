
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_POLYGON_H_INCLUDED
#define LX_POLYGON_H_INCLUDED

/**
*   @file LX_Polygon.hpp
*   @brief The polygon file
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <memory>

namespace LX_Physics
{

struct LX_Vector2D;
struct LX_Point;

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

public:

    /// Constructor
    explicit LX_PolygonException(std::string err);
    /// Copy constructor
    LX_PolygonException(const LX_PolygonException& pex);

    /// Get the error message
    const char * what() const noexcept;

    /// Destructor
    ~LX_PolygonException() noexcept;
};


class LX_Polygon_;

/**
*   @class LX_Polygon
*   @brief The polygon
*/
class LX_Polygon
{
    std::unique_ptr<LX_Polygon_> _polyimpl;

    LX_Polygon(LX_Polygon& p);
    LX_Polygon& operator =(LX_Polygon& p);

public:

    /// Constructor
    LX_Polygon();

    /**
    *   @fn void LX_Polygon::addPoint(const int x, const int y)
    *
    *   Set a new point into the polygon according to its coordinates
    *
    *   @param [in] x The x position of the point
    *   @param [in] y The y position of the point
    */
    void addPoint(const int x, const int y);
    /**
    *   @fn void LX_Polygon::addPoint(const LX_Point& p)
    *   Set a new point into the polygon
    *   @param [in] p The new edge to add
    */
    void addPoint(const LX_Point& p);

    /// @todo Add points using a unique function
    /**
    *   @note With this kind of signature
    *   addPoints(iterator beg, iterator end);
    */

    /**
    *   @fn unsigned long LX_Polygon::numberOfEdges() const
    *   Get the number of points
    *   @return The number of edges of the polygon
    */
    unsigned long numberOfEdges() const;

    /**
    *   @fn LX_Point LX_Polygon::getPoint(const unsigned int index) const
    *
    *   Get the point at a specified position
    *
    *   @param [in] index The index of the point
    *
    *   @return A copy of the point
    *
    *   @exception  LX_PolygonException If the index refers
    *              to an out of bounds position
    */
    LX_Point getPoint(const unsigned int index) const;

    /**
    *   @fn bool LX_Polygon::isConvex() const
    *
    *   Check the convexity of the polygon
    *
    *   @return TRUE if the polygon is convex, false otherwise
    *
    *   @note Actually, the convexity of the polygon is dynamically evaluated
    *        each time a new point in added using LX_Polygon::addPoint().
    *        The result is stored in an internal variable
    */
    bool isConvex() const;

    /**
    *   @fn void LX_Polygon::move(const float vx, const float vy)
    *
    *   Move the polygon to a direction
    *
    *   @param [in] vx The x direction
    *   @param [in] vy The y direction
    */
    void move(const float vx, const float vy);

    /**
    *   @fn void LX_Polygon::move(const LX_Vector2D& v)
    *   Move the polygon to a direction
    *   @param [in] v The vector that indicates the direction
    */
    void move(const LX_Vector2D& v);

    /**
    *   @fn void LX_Polygon::moveTo(int xpos, int ypos)
    *
    *   Move the polygon to a position
    *
    *   @param [in] xpos The x position
    *   @param [in] ypos The y position
    */
    void moveTo(int xpos, int ypos);

    /// Destructor
    ~LX_Polygon();
};

};

#endif
