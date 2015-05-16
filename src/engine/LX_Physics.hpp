

#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED


/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*
*	@file LX_Physics.hpp
*	@brief The LX_Physics Library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.3
*
*/

#include "LX_Hitbox.hpp"

class LX_Polygon;

#define RECT_SIDES 4    /**< The number of the AABB sides */



/**
*
*   @namespace LX_Physics
*   @brief The physics engine
*
*   This namespace describes LX_Physics, the physics module of Lunatix Engine.
*
*/
namespace LX_Physics{


        unsigned int euclide_square_distance( int x1, int y1, int x2, int y2);
        float euclide_distance(int x1, int y1, int x2, int y2);
        unsigned int euclide_square_distance( LX_Point *p1, LX_Point *p2);
        float euclide_distance(LX_Point *p1, LX_Point *p2);

        bool collisionPointRect(const int x_pos, const int y_pos, const LX_AABB *rect);             // collision point/AABB
        bool collisionPointRect(const LX_Point *p,const LX_AABB *rect);

        bool collisionPointCircle(const int x_pos, const int y_pos, const LX_Circle *circle);       // collision point/circle
        bool collisionPointCircle(const LX_Point *p, const LX_Circle *circle);

        bool collisionRect(const LX_AABB *rect1, const LX_AABB *rect2);                             // collision AABB/AABB
        bool collisionCircle(const LX_Circle *circle1, const LX_Circle *circle2);                   // collision circle/circle
        bool collisionSegCircle(const LX_Circle *circle, const LX_Point *A, const LX_Point *B);     // collision circle/segment
        bool collisionCircleRect(const LX_Circle *circle, const LX_AABB *rect);                     // collision circle/AABB


        bool intersectSegLine(const LX_Point *A, const LX_Point *B,
                                const LX_Point *C, const LX_Point *D);                              // collision segment/segment
        bool intersectSegment(const LX_Point *A, const LX_Point *B,
                                const LX_Point *C, const LX_Point *D);                              // collision segment/segment

        bool collisionPointPoly(const LX_Point *P, const LX_Polygon *poly);                         // collision point/polygon
        bool collisionCirclePoly(const LX_Circle *C, const LX_Polygon *poly);                       // collision circle/polygon

        bool collisionRectPoly(const LX_AABB *rect, const LX_Polygon *poly);                        // collision AABB/polygon
        bool collisionPoly(const LX_Polygon *poly1, const LX_Polygon *poly2);                       // collision polygon/polygon

        void movePoint(LX_Point *P, const int vx, const int vy);
        void moveRect(LX_AABB *rect, const int vx, const int vy);
        void moveCircle(LX_Circle *C, const int vx, const int vy);
        void movePoly(LX_Polygon *poly, const int vx, const int vy);

        void movePointTo(LX_Point *P, const int xpos, const int ypos);
        void moveRectTo(LX_AABB *rect, const int xpos, const int ypos);
        void moveCircleTo(LX_Circle *C, const int xpos, const int ypos);
        void movePolyTo(LX_Polygon *poly, const int xpos, const int ypos);

};

#endif // PHYSICS_H_INCLUDED












