

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is an SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/


/**
*	@file LX_Hitbox.cpp
*	@brief The Hitbox operators implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <LunatiX/LX_Hitbox.hpp>


namespace LX_Physics
{

LX_Point& LX_Point::operator=(LX_Point p)
{
    x = p.x;
    y = p.y;

    return *this;
}



};



