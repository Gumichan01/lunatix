


/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/


/**
*	@file LX_Vector2D.cpp
*	@brief The vector 2D implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.4
*
*/

#include <cmath>

#include "LX_Vector2D.hpp"


float scalar_product(LX_Vector2D *u,LX_Vector2D *v)
{
    return (u->vx * v->vx) + (u->vy * v->vy);
}


float vector_product(LX_Vector2D *u,LX_Vector2D *v)
{
    return (u->vx * v->vy) - (v->vx * u->vy);
}


float vector_norm(LX_Vector2D *u)
{
    return sqrt(scalar_product(u,u));
}
