#ifndef PARTICLE_HPP_INCLUDED
#define PARTICLE_HPP_INCLUDED


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
*	@file LX_Particle.hpp
*	@brief The Particle file
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include "LX_AABB.hpp"
#include "LX_Vector2D.hpp"

#define DELAY 16        /**< The delay of the particle to stay alive */

struct SDL_Texture;
struct SDL_Surface;

namespace LX_FileIO
{

class LX_FileBuffer;

};


namespace LX_ParticleEngine
{

/**
*   @class LX_Particle
*   @brief The particle
*/
class LX_Particle
{
    LX_AABB box;                        /* The box of the particle                  */
    LX_Physics::LX_Vector2D velocity;   /* The velocity of the particle             */

    /*  Boolean variable defined to check if
        the texture of the particle was allocatedd outside
        of the particle */
    bool texture_from_outside;

    unsigned int lifetime;              /* The delay to stay displayable            */
    SDL_Texture *texture;               /* The texture (for the texture rendering)  */
    SDL_Surface *surface;               /* The surface (for the surface rendering)  */

    LX_Particle(LX_Particle& p);
    LX_Particle& operator =(LX_Particle& p);


public :

    LX_Particle(const int x , const int y, const int w, const int h);

    /**
    *   @fn LX_Particle::LX_Particle(const LX_AABB& b)
    *
    *   Create the instance using an AABB
    *
    *   @param b The AABB that contains the coordinates, the width and the height
    *
    */
    LX_Particle(const LX_AABB& b);

    /**
    *   @fn LX_Particle::LX_Particle(const int x, const int y, const int w, const int h,
    *                                const LX_Physics::LX_Vector2D& v)
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
    LX_Particle(const int x, const int y, const int w, const int h,
                const LX_Physics::LX_Vector2D& v);

    /**
    *   @fn LX_Particle::LX_Particle(const int x, const int y, const int w,
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
    LX_Particle(const int x, const int y, const int w, const int h,
                const float vx, const float vy);

    /**
    *   @fn LX_Particle::LX_Particle(const LX_AABB& b, const float vx, const float vy)
    *
    *   Create the instance using an AABB and the velocity
    *
    *   @param b The AABB that contains the coordinates, the width and the height
    *   @param vx The X velocity
    *   @param vy The Y velocity
    *
    */
    LX_Particle(const LX_AABB& b, const float vx, const float vy);

    /**
    *   @fn LX_Particle::LX_Particle(const LX_AABB& b, const LX_Physics::LX_Vector2D& v)
    *
    *   Create the instance using an AABB and the velocity
    *
    *   @param b The AABB that contains the coordinates, the width and the height
    *   @param v The vector that store the velocity
    *
    */
    LX_Particle(const LX_AABB& b, const LX_Physics::LX_Vector2D& v);

    void update(void);
    bool isDead(void);

    bool setTexture(LX_FileIO::LX_FileBuffer *buffer);
    bool setTexture(SDL_Texture * t);
    bool setTexture(SDL_Surface * s);
    bool setSurface(LX_FileIO::LX_FileBuffer *buffer);
    void setSpeed(const float vx,const float vy);

    SDL_Texture * getTexture(void);
    SDL_Surface * getSurface(void);
    LX_AABB getAABB(void);

    int getX(void);
    int getY(void);
    int getW(void);
    int getH(void);
    unsigned int getDelay(void);

    ~LX_Particle();
};

};

#endif // PARTICLE_HPP_INCLUDED

