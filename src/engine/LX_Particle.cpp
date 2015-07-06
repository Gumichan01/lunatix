

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Particle.cpp
*	@brief The particle implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>

#include "LX_Particle.hpp"
#include "LX_Physics.hpp"
#include "LX_Graphics.hpp"
#include "LX_Random.hpp"


using namespace LX_Graphics;
using namespace LX_Random;


namespace LX_ParticleEngine
{


/**
*   @fn LX_Particle::LX_Particle(const int x , const int y, const int w, const int h)
*
*   Create the instance using coordinates, width and height
*
*   @param x The X coordinate
*   @param y The Y coordinate
*   @param w The width
*   @param h The height
*
*/
LX_Particle::LX_Particle(const int x , const int y, const int w, const int h)
{
    init(x,y,w,h,0,0);
}


/**
*   @fn LX_Particle::LX_Particle(const LX_AABB *b)
*
*   Create the instance using an AABB
*
*   @param b The AABB that contains the coordinates, the width and the height
*
*/
LX_Particle::LX_Particle(const LX_AABB *b)
{
    init(b->x,b->y,b->w,b->h,0,0);
}


/**
*   @fn LX_Particle::LX_Particle(const int x , const int y, const int w, const int h, const LX_Vector2D *v)
*
*   Create the instance using coordinates, width, height and the velocity as a vector
*
*   @param x The X coordinate
*   @param y The Y coordinate
*   @param w The width
*   @param h The height
*   @param v The vector that store the velocity
*
*/
LX_Particle::LX_Particle(const int x , const int y, const int w, const int h,
                         const LX_Vector2D *v)
{
    init(x,y,w,h,v->vx,v->vy);
}


/**
*   @fn LX_Particle::LX_Particle(const int x , const int y, const int w, const int h, const int vx, const int vy)
*
*   Create the instance using coordinates, width, height and the velocity
*
*   @param x The X coordinate
*   @param y The Y coordinate
*   @param w The width
*   @param h The height
*   @param vx The X velocity
*   @param vy The Y velocity
*
*/
LX_Particle::LX_Particle(const int x , const int y, const int w,
                         const int h, const int vx , const int vy)
{
    init(x,y,w,h,vx,vy);
}


/**
*   @fn LX_Particle::LX_Particle(const LX_AABB *b, const int vx , const int vy)
*
*   Create the instance using an AABB and the velocity
*
*   @param b The AABB that contains the coordinates, the width and the height
*   @param vx The X velocity
*   @param vy The Y velocity
*
*/
LX_Particle::LX_Particle(const LX_AABB *b, const int vx , const int vy)
{
    init(b->x,b->y,b->w,b->h,vx,vy);
}


/**
*   @fn LX_Particle::LX_Particle(const LX_AABB *b, const LX_Vector2D *v)
*
*   Create the instance using an AABB and the velocity
*
*   @param b The AABB that contains the coordinates, the width and the height
*   @param v The vector that store the velocity
*
*/
LX_Particle::LX_Particle(const LX_AABB *b, const LX_Vector2D *v)
{
    init(b->x,b->y,b->w,b->h,v->vx,v->vy);
}


/**
*   @fn LX_Particle::init(const int x , const int y, const int w, const int h, const int vx, const int vy)
*
*   This private function initializes the particle
*
*   @param x The X coordinate
*   @param y The Y coordinate
*   @param w The width
*   @param h The height
*   @param vx The X velocity
*   @param vy The Y velocity
*
*   @note This function is automatically called by one of the following constructors
*           of the particle
*
*/
void LX_Particle::init(const int x , const int y, const int w,
                       const int h, const int vx, const int vy)
{
    box = {x,y,w,h};
    velocity = {vx,vy};

    lifetime = xorshiftRand()%DELAY;

    texture = NULL;
    surface = NULL;
}


/**
*   @fn LX_Particle::~LX_Particle()
*
*   Destroy the instance
*
*/
LX_Particle::~LX_Particle()
{
    if(surface != NULL)
    {
        SDL_FreeSurface(surface);
    }

    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
    }
}


/**
*   @fn void LX_Particle::update(void)
*
*   Update the particle statement
*
*/
void LX_Particle::update(void)
{
    if(lifetime > 0)
    {
        LX_Physics::moveRect(&box,velocity.vx,velocity.vy);
        lifetime--;
    }
}


/**
*   @fn bool LX_Particle::isDead(void)
*
*   Check if the particle is dead and must be destroyed
*
*   @return TRUE if the particle is dead, FALSE otherwise
*
*/
bool LX_Particle::isDead(void)
{
    return lifetime == 0;
}


/**
*   @fn bool LX_Particle::setTexture(const char * str, const unsigned int id)
*
*   Set a texture to the particle
*
*   @param str The file that contains the sprite to load
*   @param id The id of the window in the LX_WindowManager
*           used to get the texture according to its rendererer
*
*   @return TRUE if the particle texture was created, FALSE otherwise
*
*/
bool LX_Particle::setTexture(const char * str, const unsigned int id)
{
    texture = loadTextureFromFile(str,id);
    return texture != NULL;
}


/**
*   @fn bool LX_Particle::setSurface(const char * str)
*
*   Set a surface to the particle
*
*   @param str The file that contains the sprite to load
*
*   @return TRUE if the particle surface was created, FALSE otherwise
*
*/
bool LX_Particle::setSurface(const char * str)
{
    surface = loadSurface(str);
    return surface != NULL;
}


/**
*   @fn void LX_Particle::setSpeed(int x,int y)
*
*   Set the velocity
*
*   @param x The new X velocity
*   @param y The new Y velocity
*
*   @note This function is very useful to set gravity or acceleration
*
*/
void LX_Particle::setSpeed(int x,int y)
{
    velocity = {x, y};
}


/**
*   @fn SDL_Texture * LX_Particle::getTexture(void)
*
*   Get the texture
*
*   @return A pointer to the texture
*
*/
SDL_Texture * LX_Particle::getTexture(void)
{
    return texture;
}


/**
*   @fn SDL_Surface * LX_Particle::getSurface(void)
*
*   Get the surface
*
*   @return A pointer to the surface
*
*/
SDL_Surface * LX_Particle::getSurface(void)
{
    return surface;
}


/**
*   @fn LX_AABB * LX_Particle::getAABB()
*
*   Get the AABB
*
*   @return A pointer to the AABB
*
*/
LX_AABB * LX_Particle::getAABB()
{
    return &box;
}


/**
*   @fn const int LX_Particle::getX(void)
*
*   Get the X position
*
*   @return The X position
*
*/
const int LX_Particle::getX(void)
{
    return box.x;
}


/**
*   @fn const int LX_Particle::getY(void)
*
*   Get the Y position
*
*   @return The Y position
*
*/
const int LX_Particle::getY(void)
{
    return box.y;
}


/**
*   @fn const int LX_Particle::getW(void)
*
*   Get the width
*
*   @return The width
*
*/
const int LX_Particle::getW(void)
{
    return box.w;
}


/**
*   @fn const int LX_Particle::getH(void)
*
*   Get the height
*
*   @return The height
*
*/
const int LX_Particle::getH(void)
{
    return box.h;
}


/**
*   @fn const unsigned int LX_Particle::getDelay()
*
*   Get the lifetime of the particle
*
*   @return The lifetime
*
*/
const unsigned int LX_Particle::getDelay()
{
    return lifetime;
}


};
