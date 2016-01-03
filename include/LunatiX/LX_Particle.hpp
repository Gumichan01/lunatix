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
*	@version 0.7
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

    unsigned int lifetime;              /* The delay to stay displayable            */
    SDL_Texture *texture;               /* The texture (for the texture rendering)  */
    SDL_Surface *surface;               /* The surface (for the surface rendering)  */

    LX_Particle(LX_Particle& p);
    LX_Particle& operator =(LX_Particle& p);


public :

    LX_Particle(const int x , const int y, const int w, const int h);
    LX_Particle(const LX_AABB& b);
    LX_Particle(const int x , const int y, const int w, const int h,
                const LX_Physics::LX_Vector2D& v);
    LX_Particle(const int x , const int y, const int w, const int h,
                const float vx , const float vy);

    LX_Particle(const LX_AABB& b, const float vx , const float vy);
    LX_Particle(const LX_AABB& b, const LX_Physics::LX_Vector2D& v);

    void update(void);
    bool isDead(void);

    bool setTexture(LX_FileIO::LX_FileBuffer *buffer);
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

