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


/**
*   @fn LX_Particle::LX_Particle(const int x, const int y, const int w, const int h)
*
*   Create the instance using coordinates, width and height
*
*   @param x The X coordinate
*   @param y The Y coordinate
*   @param w The width
*   @param h The height
*
*/
LX_Particle::LX_Particle(const int x, const int y, const int w, const int h)
    : LX_Particle({x,y,w,h})
{
    // Empty
}

LX_Particle::LX_Particle(const LX_AABB& b): LX_Particle(b,0.0f,0.0f)
{
    // Empty
}

LX_Particle::LX_Particle(const int x, const int y, const int w, const int h,
                         const LX_Vector2D& v)
    : LX_Particle({x,y,w,h},v)
{
    // Empty
}

LX_Particle::LX_Particle(const int x , const int y, const int w,
                         const int h, const float vx , const float vy)
    : LX_Particle({x,y,w,h},LX_Vector2D(vx,vy))
{
    // Empty
}

LX_Particle::LX_Particle(const LX_AABB& b, const float vx , const float vy)
    : LX_Particle(b,LX_Vector2D(vx,vy))
{
    // Empty
}

LX_Particle::LX_Particle(const LX_AABB& b, const LX_Vector2D& v)
    : box(b), velocity(v), lifetime(xorshiftRand()%DELAY),
      texture(nullptr), surface(nullptr),texture_from_outside(false)
{
    // Empty
}


/**
*   @fn LX_Particle::~LX_Particle()
*
*   Destroy the instance
*/
LX_Particle::~LX_Particle()
{
    SDL_FreeSurface(surface);

    if(!texture_from_outside)
        SDL_DestroyTexture(texture);
}


/**
*   @fn void LX_Particle::update(void)
*
*   Update the particle statement
*/
void LX_Particle::update(void)
{
    if(lifetime > 0)
    {
        LX_Physics::moveRect(box,velocity);
        lifetime--;
    }
}


/**
*   @fn bool LX_Particle::setTexture(LX_FileBuffer *buffer)
*
*   Set a texture to the particle
*
*   @param buffer The file buffer that contains the sprite to load
*
*   @return TRUE if the particle texture was created, FALSE otherwise
*/
bool LX_Particle::setTexture(LX_FileBuffer *buffer)
{
    SDL_Surface * s = nullptr;

    s = loadSurfaceFromFileBuffer(buffer);
    texture = loadTextureFromSurface(s);
    SDL_FreeSurface(s);

    return texture != nullptr;
}

/**
*   @fn bool LX_Particle::setTexture(SDL_Texture * t)
*
*   Set a texture to the particle
*
*   @param t the texture
*
*   @return TRUE if the particle texture in argument is valid, FALSE otherwise
*/
bool LX_Particle::setTexture(SDL_Texture * t)
{
    texture = t;
    texture_from_outside = true;
    return texture != nullptr;
}

/**
*   @fn bool LX_Particle::setTexture(SDL_Surface * s)
*
*   Set a texture to the particle
*
*   @param s the surface
*
*   @return TRUE if the particle texture was created, FALSE otherwise
*/
bool LX_Particle::setTexture(SDL_Surface * s)
{
    texture = loadTextureFromSurface(s);
    return texture != nullptr;
}


/**
*   @fn bool LX_Particle::setSurface(LX_FileBuffer *buffer)
*
*   Set a surface to the particle
*
*   @param buffer The file buffer that contains the sprite to load
*
*   @return TRUE if the particle surface was created, FALSE otherwise
*/
bool LX_Particle::setSurface(LX_FileBuffer *buffer)
{
    surface = loadSurfaceFromFileBuffer(buffer);
    return surface != nullptr;
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
*   @fn void LX_Particle::setSpeed(const float vx,const float vy)
*
*   Set the velocity of the particle
*
*   @param vx The new X velocity
*   @param vy The new Y velocity
*
*   @note This function is very useful to set gravity or acceleration
*/
void LX_Particle::setSpeed(const float vx,const float vy)
{
    velocity = LX_Vector2D(vx, vy);
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
*/
SDL_Surface * LX_Particle::getSurface(void)
{
    return surface;
}


/**
*   @fn const LX_AABB * LX_Particle::getAABB(void)
*
*   Get the AABB
*
*   @return A pointer to the AABB
*/
LX_AABB LX_Particle::getAABB(void)
{
    return box;
}


/**
*   @fn int LX_Particle::getX(void)
*
*   Get the X position
*
*   @return The X position
*/
int LX_Particle::getX(void)
{
    return box.x;
}


/**
*   @fn int LX_Particle::getY(void)
*
*   Get the Y position
*
*   @return The Y position
*/
int LX_Particle::getY(void)
{
    return box.y;
}


/**
*   @fn int LX_Particle::getW(void)
*
*   Get the width
*
*   @return The width
*/
int LX_Particle::getW(void)
{
    return box.w;
}


/**
*   @fn int LX_Particle::getH(void)
*
*   Get the height
*
*   @return The height
*/
int LX_Particle::getH(void)
{
    return box.h;
}


/**
*   @fn unsigned int LX_Particle::getDelay(void)
*
*   Get the lifetime of the particle
*
*   @return The lifetime
*/
unsigned int LX_Particle::getDelay(void)
{
    return lifetime;
}

};
