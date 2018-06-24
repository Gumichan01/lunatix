
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

#ifndef LX_POLYGON_H_INCLUDED
#define LX_POLYGON_H_INCLUDED

/**
*   @file Polygon.hpp
*   @brief The polygon file
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/utils/utf8_string.hpp>
#include <Lunatix/Hitbox.hpp>
#include <memory>

namespace LX_Physics
{

struct LX_Vector2D;
struct LX_FloatPosition;

/**
*   @class LX_PolygonException
*   @brief The exception class of LX_Window
*
*   This class describes the exception occured when
*   the polygon cannot be loaded.
*/
class LX_PolygonException final : public std::exception
{
    std::string _string_error;

public:

    explicit LX_PolygonException( std::string err );
    LX_PolygonException( const LX_PolygonException& pex );
    LX_PolygonException& operator =( const LX_PolygonException& pex );
    const char * what() const noexcept override;
    ~LX_PolygonException() noexcept;
};


class LX_Polygon_;

/**
*   @class LX_Polygon
*   @brief The polygon
*/
class LX_Polygon final
{
    std::unique_ptr<LX_Polygon_> _polyimpl;

    LX_Polygon( LX_Polygon& p ) = delete;
    LX_Polygon& operator =( LX_Polygon& p ) = delete;

    void convexity_() noexcept;
    void addPoint_( const LX_FloatPosition& p );

public:

    LX_Polygon() noexcept;

    /**
    *   @fn void LX_Polygon::addPoint(const LX_FloatPosition& p)
    *   Set a new point into the polygon
    *   @param [in] p The new edge to add
    *
    *   @note 1 - This function is not very efficient it you use it to add multiple points,
    *             because at each addition of the point,
    *             the convexity of the polygon is updated.
    *   @note 2 - Complexity: O(n) if n >= 3, O(1) otherwise,
    *             **n** is the number of edges of the polygon.
    */
    void addPoint( const LX_FloatPosition& p );
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
    *   @fn unsigned long LX_Polygon::numberOfEdges() const noexcept
    *   @return The number of edges of the polygon
    */
    unsigned long numberOfEdges() const noexcept;
    /**
    *   @fn LX_FloatPosition LX_Polygon::getPoint(const unsigned long index) const
    *
    *   @param [in] index The index of the point
    *
    *   @return A copy of the point
    *
    *   @exception  LX_PolygonException If the index is out of bounds
    */
    LX_FloatPosition getPoint( const unsigned long index ) const;
    /**
    *   @fn LX_FloatingBox getEnclosingBox() const
    *
    *   Get the axis-aligned minimum bounding box (AABB) that enclose the polygon
    *   See — https://en.wikipedia.org/wiki/Minimum_bounding_box
    *
    *   @return The enclosing box
    *
    *   @note Complexity: O(n) with n > 2. n is the number of vertices in the polygon
    *   @exception  LX_PolygonException If the polygon has less than 3 sides
    */
    LX_FloatingBox getEnclosingBox() const;
    /**
    *   @fn bool LX_Polygon::isConvex() const noexcept
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
    *   @fn void LX_Polygon::move(const LX_Vector2D& v) noexcept
    *   @param [in] v The vector that indicates the direction
    *   @note Complexity: O(n), n the number of vertices of the polygon
    */
    void move( const LX_Vector2D& v ) noexcept;
    /**
    *   @fn void moveTo(const LX_FloatPosition& p)
    *   @param [in] p The new position
    *   @note Complexity: O(n), n is the number of vertices of the polygon
    *   @exception  LX_PolygonException If the polygon has less than 3 sides
    */
    void moveTo( const LX_FloatPosition& p );

    ~LX_Polygon();
};

}

#include <Lunatix/Polygon.tpp>

#endif
