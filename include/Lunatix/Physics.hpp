
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

#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

/**
*   @file Physics.hpp
*   @brief The physics Library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/


/**
*   @defgroup Physics Physics
*   @brief Physics Module (collision detection, movement, ...)
*/

/**
*   @ingroup Physics
*   @namespace lx::Physics
*   @brief The physics namespace
*
*   It handles operations on bodies (collision, movement, ...)
*/

#include <Lunatix/utils/float.hpp>

namespace lx
{

namespace Physics
{

struct FloatPosition;
struct FloatingBox;
struct Segment;
struct Line;
struct Circle;
struct Vector2D;
class Polygon;

/**
*   @fn Float euclide_square_distance(const FloatPosition& p1,
*                                     const FloatPosition& p2) noexcept
*
*   @param [in] p1 The first point
*   @param [in] p2 The second point
*
*   @return The square distance
*/
Float euclide_square_distance( const FloatPosition& p1, const FloatPosition& p2 ) noexcept;
/**
*   @fn Float euclide_distance(const FloatPosition& p1, const FloatPosition& p2) noexcept
*
*   @param [in] p1 The first point
*   @param [in] p2 The second point
*
*   @return The distance (floating-point value)
*/
Float euclide_distance( const FloatPosition& p1, const FloatPosition& p2 ) noexcept;

/**
*   @fn Float segLength(const Segment& s) noexcept
*
*   @param [in] s The segment
*
*   @return The length of the segment (the euclidean distance betwwen its two points)
*/
Float segLength( const Segment& s ) noexcept;

/* Collision detection */

/**
*   @fn bool collisionPointBox(const FloatPosition& p, const FloatingBox& box) noexcept
*
*   Check if a point is in an Axis Aligned Bounding Box (AABB)
*
*   @param [in] p The point
*   @param [in] box The AABB
*
*   @return TRUE if there is a collision, FALSE otherwise
*/
bool collisionPointBox( const FloatPosition& p, const FloatingBox& box ) noexcept;
/**
*   @fn bool collisionPointCircle(const FloatPosition& p, const Circle& circle) noexcept
*
*   Check if a point is in a circle
*
*   @param [in] p The point
*   @param [in] circle The circle
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionPointCircle( const FloatPosition& p, const Circle& circle ) noexcept;
/**
*   @fn bool collisionBox(const FloatingBox& rect1, const FloatingBox& rect2) noexcept
*
*   Check the collision between two Axis Aligned Bounding Box (AABB)
*
*   @param [in] rect1 The first AABB
*   @param [in] rect2 The second AABB
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionBox( const FloatingBox& rect1, const FloatingBox& rect2 ) noexcept;

/**
*   @fn bool collisionCircle(const Circle& circle1, const Circle& circle2) noexcept
*
*   Check the collision between two circles
*
*   @param [in] circle1 The first circle
*   @param [in] circle2 The second circle
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionCircle( const Circle& circle1, const Circle& circle2 ) noexcept;
/**
*   @fn bool collisionSegCircle(const Circle& circle, const Segment& s) noexcept
*
*   Check the collision between a circle and the [AB] segment
*
*   @param [in] circle The circle
*   @param [in] s The segment
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionSegCircle( const Circle& circle, const Segment& s ) noexcept;
/**
*   @fn bool collisionLineCircle(const Circle& circle, const Line& l)
*
*   Check the collision between a circle and the [AB] segment
*
*   @param [in] circle The circle
*   @param [in] l The line
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionLineCircle( const Circle& circle, const Line& l ) noexcept;
/**
*   @fn bool collisionCircleBox(const Circle& circle, const FloatingBox& box) noexcept
*
*   Check the collision between a circle and a AABB
*
*   @param [in] circle The circle
*   @param [in] box The AABB
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionCircleBox( const Circle& circle, const FloatingBox& box ) noexcept;

/**
*   @fn bool intersectSegment(const Segment& s, const Segment& t) noexcept
*
*   Test the intersection between 2 segments
*
*   @param [in] s The first segment
*   @param [in] t The second segment
*
*   @return TRUE if there is an intersection, FALSE otherwise
*/
bool intersectSegment( const Segment& s, const Segment& t ) noexcept;
/**
*   @fn bool intersectLine(const Line& l1, const Line& l2)
*
*   @param [in] l1 the first line
*   @param [in] l2 the second line
*
*   @return TRUE if there is an intersection, FALSE otherwise
*
*   @note Actually, it just checks if the two lines are not parralel
*/
bool intersectLine( const Line& l1, const Line& l2 ) noexcept;

/**
*   @fn bool collisionPointPoly(const FloatPosition& p, const Polygon& poly)
*
*   Check if a point is in a polygon
*
*   @param [in] p The point to test
*   @param [in] poly The polygon
*
*   @return TRUE if there is an intersection, FALSE otherwise
*/
bool collisionPointPoly( const FloatPosition& p, const Polygon& poly );
/**
*   @fn bool collisionCirclePoly(const Circle& c, const Polygon& poly)
*
*   @param [in] c The circular hitbox
*   @param [in] poly The polygon
*
*   @return TRUE if there is a collision, FALSE otherwise
*/
bool collisionCirclePoly( const Circle& c, const Polygon& poly );
/**
*   @fn bool collisionBoxPoly(const FloatingBox& box, const Polygon& poly)
*
*   @param [in] box The AABB
*   @param [in] poly The polygon
*
*   @return TRUE if there is a collision, FALSE otherwise
*/
bool collisionBoxPoly( const FloatingBox& box, const Polygon& poly );
/**
*   @fn bool collisionPoly(const Polygon& poly1, const Polygon& poly2)
*
*   @param [in] poly1 The first polygon
*   @param [in] poly2 The second polygon
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*   @note The function only works on polygons with at least 3 sides.
*   @exception std::invalid_argument If a polygon has less than 3 sides
*/
bool collisionPoly( const Polygon& poly1, const Polygon& poly2 );

/**
*   @fn void movePoint(FloatPosition& p, const Vector2D& v) noexcept
*
*   Move a point to a direction using the vector
*
*   @param [in] p The point to move
*   @param [in] v The vector that indicates the direction
*/
void movePoint( FloatPosition& p, const Vector2D& v ) noexcept;
/**
*   @fn void moveBox(FloatingBox& box, const Vector2D& v) noexcept
*
*   Move an AABB to a direction using the vector
*
*   @param [in] box The AABB to move
*   @param [in] v The vector that indicates the direction
*/
void moveBox( FloatingBox& box, const Vector2D& v ) noexcept;
/**
*   @fn void moveCircle(Circle& c, const Vector2D& v) noexcept
*
*   Move the circle to a direction using the vector
*
*   @param [in] c The circle to move
*   @param [in] v The vector that indicates the direction
*/
void moveCircle( Circle& c, const Vector2D& v ) noexcept;
/**
*   @fn void movePoly(Polygon& poly, const Vector2D& v) noexcept
*
*   Move the polygon to a direction using the vector
*
*   @param [in] poly The polygon to move
*   @param [in] v The vector that indicates the direction
*/
void movePoly( Polygon& poly, const Vector2D& v ) noexcept;

/**
*   @fn void movePointTo(FloatPosition& p, const FloatPosition& dest) noexcept
*
*   Move a point to an absolute position
*
*   @param [in] p The point to move
*   @param [in] dest The position
*/
void movePointTo( FloatPosition& p, const FloatPosition& dest ) noexcept;
/**
*   @fn void moveBoxTo(FloatingBox& box, const FloatPosition& p) noexcept
*
*   Move an AABB to an absolute position
*
*   @param [in] box The AABB to move
*   @param [in] p The new position
*/
void moveBoxTo( FloatingBox& box, const FloatPosition& p ) noexcept;
/**
*   @fn void moveCircleTo(Circle& c, const FloatPosition& p) noexcept
*
*   Move a circle to an absolute position
*
*   @param [in] c The circle to move
*   @param [in] p The new position
*/
void moveCircleTo( Circle& c, const FloatPosition& p ) noexcept;
/**
*   @fn void movePolyTo(Polygon& poly, const FloatPosition& p) noexcept
*
*   Move a polygon to an absolute position
*
*   @param [in] poly The polygon to move
*   @param [in] p The new position
*/
void movePolyTo( Polygon& poly, const FloatPosition& p ) noexcept;

}   // Physics

}   // lx

#endif // PHYSICS_H_INCLUDED
