
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED

/**
*   @file Polygon.hpp
*   @brief The polygon file
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/utils/utf8_string.hpp>
#include <Lunatix/Hitbox.hpp>
#include <memory>

namespace lx
{

namespace Physics
{

struct Vector2D;
struct FloatPosition;

/**
*   @class PolygonException
*   @brief The exception class of Window
*
*   This class describes the exception occured when
*   the polygon cannot be loaded.
*/
class PolygonException final : public std::exception
{
    std::string m_msg;

public:

    explicit PolygonException( std::string err );
    PolygonException( const PolygonException& pex );
    PolygonException& operator =( const PolygonException& pex );
    const char * what() const noexcept override;
    ~PolygonException() noexcept;
};


class Polygon_;

/**
*   @class Polygon
*   @brief The polygon
*/
class Polygon final
{
    std::unique_ptr<Polygon_> m_polyimpl;

    Polygon( Polygon& p ) = delete;
    Polygon& operator =( Polygon& p ) = delete;

    void convexity_() noexcept;
    void addPoint_( const FloatPosition& p );

public:

    Polygon() noexcept;

    /**
    *   @fn void Polygon::addPoint(const FloatPosition& p)
    *   Set a new point into the polygon
    *   @param [in] p The new edge to add
    *
    *   @note 1 - This function is not very efficient it you use it to add multiple points,
    *             because at each addition of the point,
    *             the convexity of the polygon is updated.
    *   @note 2 - Complexity: O(n) if n >= 3, O(1) otherwise,
    *             **n** is the number of edges of the polygon.
    */
    void addPoint( const FloatPosition& p );
    /**
    *   @fn template <typename Iterator> void addPoints(Iterator first, Iterator last)
    *
    *   Add every points iterated into the polygon
    *
    *   @param [in] first Iterator of the structure pointing to the first point
    *   @param [in] last Iterator of the structure pointing to the position after the last point
    *
    *   @note 1 - This function is efficient because it adds every points in a row
    *             and calculate the convexity only after the operation
    *   @note 2 - Complexity: Amortized O(n + m) if n + m > 3, O(m) otherwise,
    *             **n** is the number of edges of the polygon,
    *             **m** is the number of points to add.
    */
    template <typename Iterator>
    void addPoints( Iterator first, Iterator last );

    /**
    *   @fn unsigned long Polygon::numberOfEdges() const noexcept
    *   @return The number of edges of the polygon
    */
    unsigned long numberOfEdges() const noexcept;
    /**
    *   @fn FloatPosition Polygon::getPoint(const unsigned long index) const
    *
    *   @param [in] index The index of the point
    *
    *   @return A copy of the point
    *
    *   @exception  PolygonException If the index is out of bounds
    */
    FloatPosition getPoint( const unsigned long index ) const;
    /**
    *   @fn FloatingBox getEnclosingBox() const
    *
    *   Get the axis-aligned minimum bounding box (AABB) that enclose the polygon
    *   See — https://en.wikipedia.org/wiki/Minimum_bounding_box
    *
    *   @return The enclosing box
    *
    *   @note Complexity: O(n) with n > 2. n is the number of vertices in the polygon
    *   @exception  PolygonException If the polygon has less than 3 sides
    */
    FloatingBox getEnclosingBox() const;
    /**
    *   @fn bool Polygon::isConvex() const noexcept
    *
    *   Check the convexity of the polygon
    *
    *   @return TRUE if the polygon is convex, false otherwise
    *
    *   @note Actually, the convexity of the polygon is dynamically evaluated
    *        each time a new point in added using addPoint() or addPoints().
    *        The result is stored in an internal variable.
    */
    bool isConvex() const noexcept;

    /**
    *   @fn void Polygon::move(const Vector2D& v) noexcept
    *   @param [in] v The vector that indicates the direction
    *   @note Complexity: O(n), n the number of vertices of the polygon
    */
    void move( const Vector2D& v ) noexcept;
    /**
    *   @fn void moveTo(const FloatPosition& p)
    *   @param [in] p The new position
    *   @note Complexity: O(n), n is the number of vertices of the polygon
    *   @exception  PolygonException If the polygon has less than 3 sides
    */
    void moveTo( const FloatPosition& p );

    ~Polygon();
};

}   // Physics

}   // lx

#include <Lunatix/Polygon.tpp>

#endif
