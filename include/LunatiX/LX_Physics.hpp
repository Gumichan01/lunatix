#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED


/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*
*	@file LX_Physics.hpp
*	@brief The physics Library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/LX_Hitbox.hpp>

/**
*   @namespace LX_Physics
*   @brief The physics module
*/
namespace LX_Physics
{

struct LX_Vector2D;
class LX_Polygon;

/**
*	@fn unsigned int euclide_square_distance(const int x1, const int y1,
*                                            const int x2, const int y2)
*
*	This function calculates the euclidean square distance between 2 coordinates
*
*	@param x1 The x location of the first point
*	@param y1 The y location of the first point
*	@param x2 The x location of the second point
*	@param y2 The y location of the second point
*
*	@return An integer value
*
*/
unsigned int euclide_square_distance(const int x1,const int y1,const int x2,const int y2);

/**
*	@fn float euclide_distance(const int x1, const int y1,
*                              const int x2, const int y2)
*
*	This function calculates the euclidean distance with accuracy
*
*	@param x1 The x location of the first point
*	@param y1 The y location of the first point
*	@param x2 The x location of the second point
*	@param y2 The y location of the second point
*
*	@return An float value
*
*/
unsigned int euclide_square_distance(const LX_Point& p1, const LX_Point& p2);

/**
*	@fn unsigned int euclide_square_distance(const LX_Point& p1,
*                                            const LX_Point& p2)
*
*	This function calculates the euclidean square distance
*
*	@param	p1 The first point
*	@param	p2 The second point
*
*	@return An integer value
*
*/
float euclide_distance(int const x1, const int y1, const int x2, const int y2);

/**
*	@fn float euclide_distance(const LX_Point& p1, const LX_Point& p2)
*
*	This function calculates the euclidean distance with accuracy
*
*	@param p1 The first point
*	@param p2 The second point
*
*	@return An integer value
*
*/
float euclide_distance(const LX_Point& p1,const LX_Point& p2);


/* Collision detection */


/**
*	@fn bool collisionPointRect(const int x_pos, const int y_pos,
*                               const LX_AABB& rect)
*
*	Check the collision between a point and an Axis Aligned Bouding Box (AABB)
*
*	@param x_pos The x position of the point
*	@param y_pos The y position of the point
*	@param rect The AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionPointRect(const int x_pos, const int y_pos, const LX_AABB& rect);

/**
*	@fn bool collisionPointRect(const LX_Point& p,const LX_AABB& rect)
*
*	Check the collision between a point and an AABB
*
*	@param p The point
*	@param rect The AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionPointRect(const LX_Point& p,const LX_AABB& rect);


/**
*	@fn bool collisionPointCircle(const int x_pos, const int y_pos,
*                                 const LX_Circle& circle)
*
*	Check the collision between a point and a circle
*
*	@param x_pos The x position of the point
*	@param y_pos The y position of the point
*	@param circle The circle
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionPointCircle(const int x_pos, const int y_pos, const LX_Circle& circle);

/**
*	@fn bool collisionPointCircle(const LX_Point& p, const LX_Circle& circle)
*
*	Check the collision between a point and a circle
*
*	@param p The point
*	@param circle The circle
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionPointCircle(const LX_Point& p, const LX_Circle& circle);


/**
*	@fn bool collisionRect(const LX_AABB& rect1, const LX_AABB& rect2)
*
*	Check the collision between two Axis Aligned Bounding Box (AABB)
*
*	@param rect1 The first AABB
*	@param rect2 The second AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionRect(const LX_AABB& rect1, const LX_AABB& rect2);

/**
*	@fn bool collisionCircle(const LX_Circle& circle1, const LX_Circle& circle2)
*
*	Check the collision between two circles
*
*	@param circle1 The first circle
*	@param circle2 The second circle
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionCircle(const LX_Circle& circle1, const LX_Circle& circle2);

/**
*	@fn bool collisionSegCircle(const LX_Circle& circle,
*                               const LX_Point& A, const LX_Point& B)
*
*	Check the collision between a circle and the [AB] segment
*
*	@param circle The circle
*	@param A The first point of the segment
*	@param B The other point of the segment
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionSegCircle(const LX_Circle& circle, const LX_Point& A, const LX_Point& B);


/**
*	@fn bool collisionCircleRect(const LX_Circle& circle, const LX_AABB& rect)
*
*	Check the collision between a circle and a AABB
*
*	@param circle The circle
*	@param rect The AABB
*
*	@return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionCircleRect(const LX_Circle& circle, const LX_AABB& rect);


/**
*   @fn bool intersectSegLine(const LX_Point& A, const LX_Point& B,
*                             const LX_Point& C, const LX_Point& D)
*
*   Test the intersection between a line and a segment
*
*   @param A the first point of the segment
*   @param B the second point of the segment
*   @param C the first point of the line
*   @param D the second point of the line
*
*   @return TRUE if there is an intersection, FALSE otherwise
*
*/
bool intersectSegLine(const LX_Point& A, const LX_Point& B,
                      const LX_Point& C, const LX_Point& D);

/**
*   @fn bool intersectSegment(const LX_Point& A, const LX_Point& B,
*                             const LX_Point& C, const LX_Point& D)
*
*   Test the intersection between 2 segments
*
*   @param A the first point of the first segment
*   @param B the second point of the first segment
*   @param C the first point of the second segment
*   @param D the second point of the second segment
*
*   @return TRUE if there is an intersection, FALSE otherwise
*
*/
bool intersectSegment(const LX_Point& A, const LX_Point& B,
                      const LX_Point& C, const LX_Point& D);


/**
*   @fn bool collisionPointPoly(const LX_Point& P, const LX_Polygon& poly)
*
*   Test the collision between a point and a polygon
*
*   @param P The point to test
*   @param poly The polygon
*
*   @return TRUE if there is an intersection, FALSE otherwise
*
*/
bool collisionPointPoly(const LX_Point& P, const LX_Polygon& poly);

/**
*   @fn bool collisionCirclePoly(const LX_Circle& C, const LX_Polygon& poly)
*
*   Test the intersection between a circle and a polygon
*
*   @param C The circular hitbox
*   @param poly The polygon
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionCirclePoly(const LX_Circle& C, const LX_Polygon& poly);

/**
*   @fn bool collisionRectPoly(const LX_AABB& rect, const LX_Polygon& poly)
*
*   Test the intersection between an AABB and a polygon
*
*   @param rect The AABB
*   @param poly The polygon
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*/
bool collisionRectPoly(const LX_AABB& rect, const LX_Polygon& poly);

/**
*   @fn bool collisionPoly(const LX_Polygon& poly1, const LX_Polygon& poly2)
*
*   Test the intersection between 2 polygons
*
*   @param poly1 The first polygon
*   @param poly2 The second polygon
*
*   @return TRUE if there is a collision, FALSE otherwise
*
*   @note The function only works on polygons with at least 3 sides.
*   @exception std::invalid_argument If a polygon has not at least 3 sides
*/
bool collisionPoly(const LX_Polygon& poly1, const LX_Polygon& poly2);

/**
*   @fn void movePoint(LX_Point& P, const int vx, const int vy)
*
*   Move a point to a direction
*
*   @param P The point to move
*   @param vx The x direction
*   @param vy The y direction
*
*/
void movePoint(LX_Point& P, const int vx, const int vy);

/**
*   @fn void moveRect(LX_AABB& rect, const int vx, const int vy)
*
*   Move an AABB to a direction
*
*   @param rect The AABB to move
*   @param vx The x direction
*   @param vy The y direction
*
*/
void moveRect(LX_AABB& rect, const int vx, const int vy);

/**
*   @fn void moveCircle(LX_Circle& C, const int vx, const int vy)
*
*   Move the circle to a direction
*
*   @param C The circle to move
*   @param vx The x direction
*   @param vy The y direction
*
*/
void moveCircle(LX_Circle& C, const int vx, const int vy);

/**
*   @fn void movePoly(LX_Polygon& poly, const float vx, const float vy)
*
*   Move the polygon to a direction
*
*   @param poly The polygon to move
*   @param vx The x direction
*   @param vy The y direction
*
*/
void movePoly(LX_Polygon& poly, const float vx, const float vy);

/**
*   @fn void movePoint(LX_Point& P, const LX_Vector2D& v)
*
*   Move a point to a direction using the vector
*
*   @param P The point to move
*   @param v The vector that indicates the direction
*
*/
void movePoint(LX_Point& P, const LX_Vector2D& v);

/**
*   @fn void moveRect(LX_AABB& rect, const LX_Vector2D& v)
*
*   Move an AABB to a direction using the vector
*
*   @param rect The AABB to move
*   @param v The vector that indicates the direction
*
*/
void moveRect(LX_AABB& rect, const LX_Vector2D& v);

/**
*   @fn void moveCircle(LX_Circle& C, const LX_Vector2D& v)
*
*   Move the circle to a direction using the vector
*
*   @param C The circle to move
*   @param v The vector that indicates the direction
*
*/
void moveCircle(LX_Circle& C, const LX_Vector2D& v);

/**
*   @fn void movePoly(LX_Polygon& poly, const LX_Vector2D& v)
*
*   Move the polygon to a direction using the vector
*
*   @param poly The polygon to move
*   @param v The vector that indicates the direction
*
*/
void movePoly(LX_Polygon& poly, const LX_Vector2D& v);

/**
*   @fn void movePointTo(LX_Point& P, const int xpos, const int ypos)
*
*   Move a point to an absolute position
*
*   @param P The point to move
*   @param xpos The x position
*   @param ypos The y position
*
*/
void movePointTo(LX_Point& P, const int xpos, const int ypos);

/**
*   @fn void moveRectTo(LX_AABB& rect, const int xpos, const int ypos)
*
*   Move an AABB to an absolute position
*
*   @param rect The AABB to move
*   @param xpos The x position
*   @param ypos The y position
*
*/
void moveRectTo(LX_AABB& rect, const int xpos, const int ypos);

/**
*   @fn void moveCircleTo(LX_Circle& C, const int xpos, const int ypos)
*
*   Move a circle to an absolute position
*
*   @param C The circle to move
*   @param xpos The x position
*   @param ypos The y position
*
*/
void moveCircleTo(LX_Circle& C, const int xpos, const int ypos);

/**
*   @fn void movePolyTo(LX_Polygon& poly, const int xpos, const int ypos)
*
*   Move a polygon to an absolute position
*
*   @param poly The polygon to move
*   @param xpos The x position
*   @param ypos The y position
*
*/
void movePolyTo(LX_Polygon& poly, const int xpos, const int ypos);

};

#endif // PHYSICS_H_INCLUDED
