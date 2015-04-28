

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

#define RECT_SIDES 4    /**< The number of the AABB sides */

// todo : gravity, wind, strengh, friction

/**
*
*   @namespace LX_Physics
*   @brief The physics engine
*
*   This namespace describes the LX_Physics, the physics module of the Lunatix engine.
*
*/
namespace LX_Physics{


        int euclide_square_distance( int x1, int y1, int x2, int y2);
        int euclide_distance( int x1, int y1, int x2, int y2);
        int euclide_square_distance( LX_Point *p1, LX_Point *p2);
        int euclide_distance( LX_Point *p1, LX_Point *p2);

        bool collision(int x_pos, int y_pos, const LX_AABB *rect);                          // collision point/AABB
        bool collision(int x_pos, int y_pos, const LX_Circle *circle);                      // collision point/circle
        bool collision(const LX_AABB *rect1, const LX_AABB *rect2);                         // collision AABB/AABB
        bool collision(const LX_Circle *circle1, const LX_Circle *circle2);                 // collision circle/circle
        bool collision(const LX_Circle *circle, const LX_Point *A, const LX_Point *B);      // collision circle/segment
        bool collision(const LX_Circle *circle, const LX_AABB *rect);                       // collision circle/AABB

};

#endif // PHYSICS_H_INCLUDED












