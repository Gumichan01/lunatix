
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
*   @file LX_Physics.hpp
*   @brief The physics Library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/


/**
*   @defgroup Physics Physics
*   @brief Physics Module (collision detection, movement, ...)
*/

/**
*   @ingroup Physics
*   @namespace LX_Physics
*   @brief The physics namespace
*
*   It handles operations on bodies (collision, movement, ...)
*/

#include <LunatiX/utils/float.hpp>

namespace LX_Physics
{

struct LX_FloatPosition;
struct LX_FloatingBox;
struct LX_Segment;
struct LX_Line;
struct LX_Circle;
struct LX_Vector2D;
class LX_Polygon;

/**
*   @fn Float euclide_square_distance(const LX_FloatPosition& p1,
*                                     const LX_FloatPosition& p2) noexcept
*
*   @param [in] p1 The first point
*   @param [in] p2 The second point
*
*   @return The square distance
*/
Float euclide_square_distance(const LX_FloatPosition& p1, const LX_FloatPosition& p2) noexcept;
/**
*   @fn Float euclide_distance(const LX_FloatPosition& p1, const LX_FloatPosition& p2) noexcept
*
*   @param [in] p1 The first point
*   @param [in] p2 The second point
*
*   @return The distance (floating-point value)
*/
Float euclide_distance(const LX_FloatPosition& p1, const LX_FloatPosition& p2) noexcept;

/**
*   @fn Float segLength(const LX_Segment& S) noexcept
*
*   @param [in] S The segment
*
*   @return The length of the segment (the euclidean distance betwwen its two points)
*/
Float segLength(const LX_Segment& S) noexcept;

/* Collision detection */

/**
*   @fn bool collisionPointBox(const LX_FloatPosition& p, const LX_FloatingBox& box) noexcept
*
*   Check if a point is in an Axis Aligned Bounding Box (AABB)
*
*   @param [in] p The point
*   @param [in] box The AABB
*
*   @return TRUE if there is a collision, FALSE otherwise
*/
bool collisionPointBox(const LX_FloatPosition& p, const LX_FloatingBox& box) noexcept;
/**
*   @fn bool collisionPointCircle(const LX_FloatPosition& p, const LX_Circle& circle) noexcept
*
*   Check if a point is in a circle
*
*   @param [in] p The point
*   @param [in] circle The circle
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionPointCircle(const LX_FloatPosition& p, const LX_Circle& circle) noexcept;
/**
*   @fn bool collisionBox(const LX_FloatingBox& rect1, const LX_FloatingBox& rect2) noexcept
*
*   Check the collision between two Axis Aligned Bounding Box (AABB)
*
*   @param [in] rect1 The first AABB
*   @param [in] rect2 The second AABB
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionBox(const LX_FloatingBox& rect1, const LX_FloatingBox& rect2) noexcept;

/**
*   @fn bool collisionCircle(const LX_Circle& circle1, const LX_Circle& circle2) noexcept
*
*   Check the collision between two circles
*
*   @param [in] circle1 The first circle
*   @param [in] circle2 The second circle
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionCircle(const LX_Circle& circle1, const LX_Circle& circle2) noexcept;
/**
*   @fn bool collisionSegCircle(const LX_Circle& circle, const LX_Segment& S) noexcept
*
*   Check the collision between a circle and the [AB] segment
*
*   @param [in] circle The circle
*   @param [in] S The segment
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionSegCircle(const LX_Circle& circle, const LX_Segment& S) noexcept;
/**
*   @fn bool collisionLineCircle(const LX_Circle& circle, const LX_Line& L)
*
*   Check the collision between a circle and the [AB] segment
*
*   @param [in] circle The circle
*   @param [in] L The line
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionLineCircle(const LX_Circle& circle, const LX_Line& L) noexcept;
/**
*   @fn bool collisionCircleBox(const LX_Circle& circle, const LX_FloatingBox& box) noexcept
*
*   Check the collision between a circle and a AABB
*
*   @param [in] circle The circle
*   @param [in] box The AABB
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionCircleBox(const LX_Circle& circle, const LX_FloatingBox& box) noexcept;

/**
*   @fn bool intersectSegment(const LX_Segment& S, const LX_Segment& T) noexcept
*
*   Test the intersection between 2 segments
*
*   @param [in] S The first segment
*   @param [in] T The second segment
*
*   @return TRUE if there is an intersection, FALSE otherwise
*/
bool intersectSegment(const LX_Segment& S, const LX_Segment& T) noexcept;
/**
*   @fn bool intersectLine(const LX_Line& L1, const LX_Line& L2)
*
*   @param [in] L1 the first line
*   @param [in] L2 the second line
*
*   @return TRUE if there is an intersection, FALSE otherwise
*
*   @note Actually, it just checks if the two lines are not parralel
*/
bool intersectLine(const LX_Line& L1, const LX_Line& L2) noexcept;

/**
*   @fn bool collisionPointPoly(const LX_FloatPosition& P, const LX_Polygon& poly)
*
*   Check if a point is in a polygon
*
*   @param [in] P The point to test
*   @param [in] poly The polygon
*
*   @return TRUE if there is an intersection, FALSE otherwise
*/
bool collisionPointPoly(const LX_FloatPosition& P, const LX_Polygon& poly);
/**
*   @fn bool collisionCirclePoly(const LX_Circle& C, const LX_Polygon& poly)
*
*   @param [in] C The circular hitbox
*   @param [in] poly The polygon
*
*   @return TRUE if there is a collision, FALSE otherwise
*/
bool collisionCirclePoly(const LX_Circle& C, const LX_Polygon& poly);
/**
*   @fn bool collisionBoxPoly(const LX_FloatingBox& box, const LX_Polygon& poly)
*
*   @param [in] box The AABB
*   @param [in] poly The polygon
*
*   @return TRUE if there is a collision, FALSE otherwise
*/
bool collisionBoxPoly(const LX_FloatingBox& box, const LX_Polygon& poly);
/**
*   @fn bool collisionPoly(const LX_Polygon& poly1, const LX_Polygon& poly2)
*
*   @param [in] poly1 The first polygon
*   @param [in] poly2 The second polygon
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*   @note The function only works on polygons with at least 3 sides.
*   @exception std::invalid_argument If a polygon has less than 3 sides
*/
bool collisionPoly(const LX_Polygon& poly1, const LX_Polygon& poly2);

/**
*   @fn void movePoint(LX_FloatPosition& P, const LX_Vector2D& v) noexcept
*
*   Move a point to a direction using the vector
*
*   @param [in] P The point to move
*   @param [in] v The vector that indicates the direction
*/
void movePoint(LX_FloatPosition& P, const LX_Vector2D& v) noexcept;
/**
*   @fn void moveBox(LX_FloatingBox& box, const LX_Vector2D& v) noexcept
*
*   Move an AABB to a direction using the vector
*
*   @param [in] box The AABB to move
*   @param [in] v The vector that indicates the direction
*/
void moveBox(LX_FloatingBox& box, const LX_Vector2D& v) noexcept;
/**
*   @fn void moveCircle(LX_Circle& C, const LX_Vector2D& v) noexcept
*
*   Move the circle to a direction using the vector
*
*   @param [in] C The circle to move
*   @param [in] v The vector that indicates the direction
*/
void moveCircle(LX_Circle& C, const LX_Vector2D& v) noexcept;
/**
*   @fn void movePoly(LX_Polygon& poly, const LX_Vector2D& v) noexcept
*
*   Move the polygon to a direction using the vector
*
*   @param [in] poly The polygon to move
*   @param [in] v The vector that indicates the direction
*/
void movePoly(LX_Polygon& poly, const LX_Vector2D& v) noexcept;

/**
*   @fn void movePointTo(LX_FloatPosition& P, const LX_FloatPosition& dest) noexcept
*
*   Move a point to an absolute position
*
*   @param [in] P The point to move
*   @param [in] dest The position
*/
void movePointTo(LX_FloatPosition& P, const LX_FloatPosition& dest) noexcept;
/**
*   @fn void moveBoxTo(LX_FloatingBox& box, const LX_FloatPosition& P) noexcept
*
*   Move an AABB to an absolute position
*
*   @param [in] box The AABB to move
*   @param [in] P The new position
*/
void moveBoxTo(LX_FloatingBox& box, const LX_FloatPosition& P) noexcept;
/**
*   @fn void moveCircleTo(LX_Circle& C, const LX_FloatPosition& P) noexcept
*
*   Move a circle to an absolute position
*
*   @param [in] C The circle to move
*   @param [in] P The new position
*/
void moveCircleTo(LX_Circle& C, const LX_FloatPosition& P) noexcept;
/**
*   @fn void movePolyTo(LX_Polygon& poly, const LX_FloatPosition& P) noexcept
*
*   Move a polygon to an absolute position
*
*   @param [in] poly The polygon to move
*   @param [in] P The new position
*/
void movePolyTo(LX_Polygon& poly, const LX_FloatPosition& P) noexcept;

}

#endif // PHYSICS_H_INCLUDED
