

#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED


/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is an SDL2-based game engine.
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
*	@version 0.6
*
*/

#include <LunatiX/LX_AABB.hpp>

/**
*
*   @namespace LX_Physics
*   @brief The physics engine
*
*   This namespace describes LX_Physics, the physics module of Lunatix Engine.
*
*/
namespace LX_Physics
{

struct LX_Point;
struct LX_Circle;
struct LX_Vector2D;
class LX_Polygon;

/* Distances */
unsigned int euclide_square_distance(const int x1,const int y1,const int x2,const int y2);
unsigned int euclide_square_distance(const LX_Point& p1, const LX_Point& p2);
float euclide_distance(int const x1, const int y1, const int x2, const int y2);
float euclide_distance(const LX_Point& p1,const LX_Point& p2);


/* Collision detection */

// Point/Rect
bool collisionPointRect(const int x_pos, const int y_pos, const LX_AABB& rect);
bool collisionPointRect(const LX_Point& p,const LX_AABB& rect);

// Point/Circle
bool collisionPointCircle(const int x_pos, const int y_pos, const LX_Circle& circle);
bool collisionPointCircle(const LX_Point& p, const LX_Circle& circle);

// AABB/AABB ; Circle/Circle ; Circle/Segment; Circle/AABB
bool collisionRect(const LX_AABB& rect1, const LX_AABB& rect2);
bool collisionCircle(const LX_Circle& circle1, const LX_Circle& circle2);
bool collisionSegCircle(const LX_Circle& circle, const LX_Point& A, const LX_Point& B);
bool collisionCircleRect(const LX_Circle& circle, const LX_AABB& rect);

// Segment/Line ; Segment/Segment
// A segment is a part of a line, so two point are needed to get a line
bool intersectSegLine(const LX_Point& A, const LX_Point& B,
                      const LX_Point& C, const LX_Point& D);
bool intersectSegment(const LX_Point& A, const LX_Point& B,
                      const LX_Point& C, const LX_Point& D);

// Point/Polygon ; Circle/Polygon
bool collisionPointPoly(const LX_Point& P, const LX_Polygon& poly);
bool collisionCirclePoly(const LX_Circle& C, const LX_Polygon& poly);

// AABB/Polygon ; Polygon/Polygon
bool collisionRectPoly(const LX_AABB& rect, const LX_Polygon& poly);
bool collisionPoly(const LX_Polygon& poly1, const LX_Polygon& poly2);


/* Move the entities */

// Using coordinates
void movePoint(LX_Point& P, const int vx, const int vy);
void moveRect(LX_AABB& rect, const int vx, const int vy);
void moveCircle(LX_Circle& C, const int vx, const int vy);
void movePoly(LX_Polygon& poly, const float vx, const float vy);

// Using vector2D
void movePoint(LX_Point& P, const LX_Vector2D& v);
void moveRect(LX_AABB& rect, const LX_Vector2D& v);
void moveCircle(LX_Circle& C, const LX_Vector2D& v);
void movePoly(LX_Polygon& poly, const LX_Vector2D& v);

// Go to a specific position
void movePointTo(LX_Point& P, const int xpos, const int ypos);
void moveRectTo(LX_AABB& rect, const int xpos, const int ypos);
void moveCircleTo(LX_Circle& C, const int xpos, const int ypos);
void movePolyTo(LX_Polygon& poly, const int xpos, const int ypos);

};

#endif // PHYSICS_H_INCLUDED


