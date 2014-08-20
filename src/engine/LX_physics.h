

#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED


/*
*	Copyright (C) 2014 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*
*	@file LX_physics.h
*	@brief The LX_physics Library, it will be linked with the SDL library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 14th, 2014
*
*/

#include "LX_Hitbox.h"
#include "LX_Polygon.h"

#define RECT_SIDES 4    /**<The number of the AABB sides*/

// todo : gravity, wind, strengh, friction

/**
*
*   @class LX_physics
*   @brief The Target_Xplosion physic engine
*
*   This class describes the LX_physics, a LunatiX_engine physics module. It mainly calculates collisions so far.
*
*/
class LX_physics{

    public :

        LX_physics(){}

        int euclide_square_distance( int x1, int y1, int x2, int y2);
        int euclide_distance( int x1, int y1, int x2, int y2);

        bool collision(int x_pos, int y_pos, const LX_AABB *rect);                          // collision point/AABB
        bool collision(int x_pos, int y_pos, const LX_Circle *circle);                      // collision point/circle
        bool collision(const LX_AABB *rect1, const LX_AABB *rect2);                         // collision AABB/AABB
        bool collision(const LX_Circle *circle1, const LX_Circle *circle2);                 // collision circle/circle
        bool collision(const LX_Circle *circle, const LX_Point *A, const LX_Point *B);      // collision circle/segment
        bool collision(const LX_Circle *circle, const LX_AABB *rect);                       // collision circle/AABB
        bool collision(const LX_Circle *circle, LX_Polygon *polygon);                       // collision circle/polygon

        ~LX_physics(){}
};





#endif // PHYSICS_H_INCLUDED































