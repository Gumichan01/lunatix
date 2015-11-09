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
*	@file LX_Particle.cpp
*	@brief The particle implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
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
    : box({x,y,w,h}),velocity(LX_Vector2D(0.0f,0.0f)), lifetime(xorshiftRand()%DELAY),
texture(NULL), surface(NULL)
{
    // Empty
}


/**
*   @fn LX_Particle::LX_Particle(const LX_AABB& b)
*
*   Create the instance using an AABB
*
*   @param b The AABB that contains the coordinates, the width and the height
*
*/
LX_Particle::LX_Particle(const LX_AABB& b)
    : box(b),velocity(LX_Vector2D{0.0f,0.0f}), lifetime(xorshiftRand()%DELAY),
texture(NULL), surface(NULL)
{
    // Empty
}


/**
*   @fn LX_Particle::LX_Particle(const int x , const int y, const int w, const int h, const LX_Vector2D& v)
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
                         const LX_Vector2D& v)
    : box({x,y,w,h}),velocity(v), lifetime(xorshiftRand()%DELAY),
texture(NULL), surface(NULL)
{
    // Empty
}


/**
*   @fn LX_Particle::LX_Particle(const int x , const int y, const int w,
*                                const int h, const float vx, const float vy)
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
                         const int h, const float vx , const float vy)
    : box({x,y,w,h}),velocity({vx,vy}), lifetime(xorshiftRand()%DELAY),
texture(NULL), surface(NULL)
{
    // Empty
}


/**
*   @fn LX_Particle::LX_Particle(const LX_AABB& b, const float vx , const float vy)
*
*   Create the instance using an AABB and the velocity
*
*   @param b The AABB that contains the coordinates, the width and the height
*   @param vx The X velocity
*   @param vy The Y velocity
*
*/
LX_Particle::LX_Particle(const LX_AABB& b, const float vx , const float vy)
    : box(b), velocity({vx,vy}), lifetime(xorshiftRand()%DELAY),
texture(NULL), surface(NULL)
{
    // Empty
}


/**
*   @fn LX_Particle::LX_Particle(const LX_AABB& b, const LX_Vector2D& v)
*
*   Create the instance using an AABB and the velocity
*
*   @param b The AABB that contains the coordinates, the width and the height
*   @param v The vector that store the velocity
*
*/
LX_Particle::LX_Particle(const LX_AABB& b, const LX_Vector2D& v)
    : box(b), velocity(v), lifetime(xorshiftRand()%DELAY),
texture(NULL), surface(NULL)
{
    // Empty
}


/**
*   @fn LX_Particle::~LX_Particle()
*
*   Destroy the instance
*
*/
LX_Particle::~LX_Particle()
{
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
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
*
*/
bool LX_Particle::setTexture(LX_FileBuffer *buffer)
{
    SDL_Surface * s = NULL;

    s = loadSurfaceFromFileBuffer(buffer);
    texture = loadTextureFromSurface(s);
    SDL_FreeSurface(s);

    return texture != NULL;
}


/**
*   @fn bool LX_Particle::setSurface(LX_FileBuffer *buffer)
*
*   Set a surface to the particle
*
*   @param buffer The file buffer that contains the sprite to load
*
*   @return TRUE if the particle surface was created, FALSE otherwise
*
*/
bool LX_Particle::setSurface(LX_FileBuffer *buffer)
{
    surface = loadSurfaceFromFileBuffer(buffer);
    return surface != NULL;
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
*   @fn void LX_Particle::setSpeed(float x,float y)
*
*   Set the velocity
*
*   @param x The new X velocity
*   @param y The new Y velocity
*
*   @note This function is very useful to set gravity or acceleration
*
*/
void LX_Particle::setSpeed(float x,float y)
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
*   @fn const LX_AABB * LX_Particle::getAABB()
*
*   Get the AABB
*
*   @return A pointer to the AABB
*
*/
LX_AABB LX_Particle::getAABB()
{
    return box;
}


/**
*   @fn int LX_Particle::getX(void)
*
*   Get the X position
*
*   @return The X position
*
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
*
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
*
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
*
*/
int LX_Particle::getH(void)
{
    return box.h;
}


/**
*   @fn unsigned int LX_Particle::getDelay()
*
*   Get the lifetime of the particle
*
*   @return The lifetime
*
*/
unsigned int LX_Particle::getDelay()
{
    return lifetime;
}


};
