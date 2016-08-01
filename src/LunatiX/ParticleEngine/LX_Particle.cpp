/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Particle.cpp
*	@brief The particle implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/LX_Particle.hpp>
#include <LunatiX/LX_Physics.hpp>
#include <LunatiX/LX_Image.hpp>
#include <LunatiX/LX_Random.hpp>

using namespace LX_FileIO;
using namespace LX_Graphics;
using namespace LX_Physics;
using namespace LX_Random;


namespace LX_ParticleEngine
{

LX_Particle::LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_AABB& b)
    : LX_Particle(sp,b,0.0f,0.0f) {}


LX_Particle::LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_AABB& b,
                         const float vx , const float vy)
    : LX_Particle(sp,b,LX_Vector2D(vx,vy)) {}


LX_Particle::LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_AABB& b,
                         const LX_Vector2D& v)
    : _box(b), _lifetime(xorshiftRand()%DELAY), _velocity(v), _texture(sp) {}


void LX_Particle::update(void)
{
    if(_lifetime > 0)
    {
        LX_Physics::moveRect(_box,_velocity);
        _lifetime--;
    }
}


void LX_Particle::draw(void)
{
    _texture.draw(&_box);
}


bool LX_Particle::isDead(void)
{
    return _lifetime == 0;
}


unsigned int LX_Particle::getDelay(void)
{
    return _lifetime;
}

};
