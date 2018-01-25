
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

#include <LunatiX/LX_AABB.hpp>


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
namespace LX_Physics
{

struct LX_FloatPosition;
struct LX_Line;
struct LX_Circle;
struct LX_Vector2D;
class LX_Polygon;

/**
*   @fn float euclide_square_distance(const LX_FloatPosition& p1,
*                                     const LX_FloatPosition& p2) noexcept
*
*   Euclidean square distance
*
*   @param [in] p1 The first point
*   @param [in] p2 The second point
*
*   @return The square distance
*/
float euclide_square_distance(const LX_FloatPosition& p1, const LX_FloatPosition& p2) noexcept;
/**
*   @fn float euclide_distance(const LX_FloatPosition& p1, const LX_FloatPosition& p2) noexcept
*
*   Euclidean distance
*
*   @param [in] p1 The first point
*   @param [in] p2 The second point
*
*   @return The distance (floating-point value)
*/
float euclide_distance(const LX_FloatPosition& p1, const LX_FloatPosition& p2) noexcept;


/* Collision detection */

/**
*   @fn bool collisionPointRect(const LX_FloatPosition& p,const LX_AABB& rect) noexcept
*
*   Check the collision between a point and an AABB
*
*   @param [in] p The point
*   @param [in] rect The AABB
*
*   @return TRUE if there is a collision, FALSE otherwise
*/
bool collisionPointRect(const LX_FloatPosition& p, const LX_AABB& rect) noexcept;
/**
*   @fn bool collisionPointCircle(const LX_FloatPosition& p, const LX_Circle& circle) noexcept
*
*   Check the collision between a point and a circle
*
*   @param [in] p The point
*   @param [in] circle The circle
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionPointCircle(const LX_FloatPosition& p, const LX_Circle& circle) noexcept;
/**
*   @fn bool collisionRect(const LX_AABB& rect1, const LX_AABB& rect2) noexcept
*
*   Check the collision between two Axis Aligned Bounding Box (AABB)
*
*   @param [in] rect1 The first AABB
*   @param [in] rect2 The second AABB
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionRect(const LX_AABB& rect1, const LX_AABB& rect2) noexcept;

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
*   @fn bool collisionSegCircle(const LX_Circle& circle,
*                               const LX_FloatPosition& A, const LX_FloatPosition& B) noexcept
*
*   Check the collision between a circle and the [AB] segment
*
*   @param [in] circle The circle
*   @param [in] A The first point of the segment
*   @param [in] B The other point of the segment
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionSegCircle(const LX_Circle& circle, const LX_FloatPosition& A, const LX_FloatPosition& B) noexcept;
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
*   @fn bool collisionCircleRect(const LX_Circle& circle, const LX_AABB& rect) noexcept
*
*   Check the collision between a circle and a AABB
*
*   @param [in] circle The circle
*   @param [in] rect The AABB
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionCircleRect(const LX_Circle& circle, const LX_AABB& rect) noexcept;

/**
*   @fn bool intersectSegLine(const LX_FloatPosition& A, const LX_FloatPosition& B,
*                            const LX_FloatPosition& C, const LX_FloatPosition& D) noexcept
*
*   Test the intersection between a line and a segment
*
*   @param [in] A the first point of the segment
*   @param [in] B the second point of the segment
*   @param [in] C the first point of the line
*   @param [in] D the second point of the line
*
*   @return TRUE if there is an intersection, FALSE otherwise
*
*/
bool intersectSegLine(const LX_FloatPosition& A, const LX_FloatPosition& B,
                      const LX_FloatPosition& C, const LX_FloatPosition& D) noexcept;

/**
*   @fn bool intersectSegment(const LX_FloatPosition& A, const LX_FloatPosition& B,
*                            const LX_FloatPosition& C, const LX_FloatPosition& D) noexcept
*
*   Test the intersection between 2 segments
*
*   @param [in] A the first point of the first segment
*   @param [in] B the second point of the first segment
*   @param [in] C the first point of the second segment
*   @param [in] D the second point of the second segment
*
*   @return TRUE if there is an intersection, FALSE otherwise
*/
bool intersectSegment(const LX_FloatPosition& A, const LX_FloatPosition& B,
                      const LX_FloatPosition& C, const LX_FloatPosition& D) noexcept;
/**
*   @fn bool intersectLine(const LX_Line& L1, const LX_Line& L2)
*
*   Test the intersection between 2 lines
*
*   @param [in] L1 the first line
*   @param [in] L2 the second line
*
*   @return TRUE if there is an intersection, FALSE otherwise
*/
bool intersectLine(const LX_Line& L1, const LX_Line& L2) noexcept;

/**
*   @fn bool collisionPointPoly(const LX_FloatPosition& P, const LX_Polygon& poly)
*
*   Test the collision between a point and a polygon
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
*   Test the intersection between a circle and a polygon
*
*   @param [in] C The circular hitbox
*   @param [in] poly The polygon
*
*   @return TRUE if there is a collision, FALSE otherwise
*/
bool collisionCirclePoly(const LX_Circle& C, const LX_Polygon& poly);
/**
*   @fn bool collisionRectPoly(const LX_AABB& rect, const LX_Polygon& poly)
*
*   Test the intersection between an AABB and a polygon
*
*   @param [in] rect The AABB
*   @param [in] poly The polygon
*
*   @return TRUE if there is a collision, FALSE otherwise
*/
bool collisionRectPoly(const LX_AABB& rect, const LX_Polygon& poly);
/**
*   @fn bool collisionPoly(const LX_Polygon& poly1, const LX_Polygon& poly2)
*
*   Test the intersection between 2 polygons
*
*   @param [in] poly1 The first polygon
*   @param [in] poly2 The second polygon
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*   @note The function only works on polygons with at least 3 sides.
*   @exception std::invalid_argument If a polygon has not at least 3 sides
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
*   @fn void moveRect(LX_AABB& rect, const LX_Vector2D& v) noexcept
*
*   Move an AABB to a direction using the vector
*
*   @param [in] rect The AABB to move
*   @param [in] v The vector that indicates the direction
*/
void moveRect(LX_AABB& rect, const LX_Vector2D& v) noexcept;
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
*   @fn void moveRectTo(LX_AABB& rect, const LX_FloatPosition& P) noexcept
*
*   Move an AABB to an absolute position
*
*   @param [in] rect The AABB to move
*   @param [in] P The new position
*/
void moveRectTo(LX_AABB& rect, const LX_FloatPosition& P) noexcept;
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
*   @fn void movePolyTo(LX_Polygon& poly, const LX_FloatPosition& P)
*
*   Move a polygon to an absolute position
*
*   @param [in] poly The polygon to move
*   @param [in] P The new position
*/
void movePolyTo(LX_Polygon& poly, const LX_FloatPosition& P);

}

#endif // PHYSICS_H_INCLUDED
