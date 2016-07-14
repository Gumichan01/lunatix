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

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>

#include <LunatiX/LX_Particle.hpp>
#include <LunatiX/LX_Physics.hpp>
#include <LunatiX/LX_Graphics.hpp>
#include <LunatiX/LX_Random.hpp>
#include <LunatiX/LX_FileBuffer.hpp>


using namespace LX_FileIO;
using namespace LX_Graphics;
using namespace LX_Physics;
using namespace LX_Random;


namespace LX_ParticleEngine
{

LX_Particle::LX_Particle(const int x, const int y, const int w, const int h)
    : LX_Particle({x,y,w,h}) {}


LX_Particle::LX_Particle(const LX_AABB& b): LX_Particle(b,0.0f,0.0f) {}


LX_Particle::LX_Particle(const int x, const int y, const int w, const int h,
                         const LX_Vector2D& v)
    : LX_Particle({x,y,w,h},v) {}


LX_Particle::LX_Particle(const int x , const int y, const int w,
                         const int h, const float vx , const float vy)
    : LX_Particle({x,y,w,h},LX_Vector2D(vx,vy)) {}


LX_Particle::LX_Particle(const LX_AABB& b, const float vx , const float vy)
    : LX_Particle(b,LX_Vector2D(vx,vy)) {}


LX_Particle::LX_Particle(const LX_AABB& b, const LX_Vector2D& v)
    : box(b)
{
    velocity = v;
    texture_from_outside = false;
    lifetime = xorshiftRand()%DELAY;
    texture = nullptr;
    surface = nullptr;
}


void LX_Particle::update(void)
{
    if(lifetime > 0)
    {
        LX_Physics::moveRect(box,velocity);
        lifetime--;
    }
}


bool LX_Particle::isDead(void)
{
    return lifetime == 0;
}


bool LX_Particle::setTexture(LX_FileBuffer *buffer)
{
    SDL_Surface * s = nullptr;

    s = loadSurfaceFromFileBuffer(buffer);
    texture = loadTextureFromSurface(s);
    SDL_FreeSurface(s);

    return texture != nullptr;
}


bool LX_Particle::setTexture(SDL_Texture * t)
{
    texture = t;
    texture_from_outside = true;
    return texture != nullptr;
}


bool LX_Particle::setTexture(SDL_Surface * s)
{
    texture = loadTextureFromSurface(s);
    return texture != nullptr;
}


bool LX_Particle::setSurface(LX_FileBuffer *buffer)
{
    surface = loadSurfaceFromFileBuffer(buffer);
    return surface != nullptr;
}


void LX_Particle::setSpeed(const float vx,const float vy)
{
    velocity = LX_Vector2D(vx, vy);
}


SDL_Texture * LX_Particle::getTexture(void)
{
    return texture;
}


SDL_Surface * LX_Particle::getSurface(void)
{
    return surface;
}


LX_AABB LX_Particle::getAABB(void)
{
    return box;
}


int LX_Particle::getX(void)
{
    return box.x;
}


int LX_Particle::getY(void)
{
    return box.y;
}


int LX_Particle::getW(void)
{
    return box.w;
}


int LX_Particle::getH(void)
{
    return box.h;
}


unsigned int LX_Particle::getDelay(void)
{
    return lifetime;
}


LX_Particle::~LX_Particle()
{
    SDL_FreeSurface(surface);

    if(!texture_from_outside)
        SDL_DestroyTexture(texture);
}

};
