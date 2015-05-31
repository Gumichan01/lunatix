#ifndef PARTICLE_HPP_INCLUDED
#define PARTICLE_HPP_INCLUDED



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
*	@file LX_Particle.hpp
*	@brief The Particle file
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*
*/

#include <SDL2/SDL_rect.h>

#include "LX_Hitbox.hpp"
#include "LX_Vector2D.hpp"

#define DELAY 16        /**< The delay of the particle The delay to stay alive */


struct SDL_Texture;
struct SDL_Surface;


/**
*   @class LX_Particle
*   @brief The particle class
*
*   This class describes a particle
*/
class LX_Particle{

    LX_AABB box;                    /**< The box of the particle */
    LX_Vector2D velocity;           /**< The velocity of the particle */
    unsigned int lifetime;          /**< The delay to stay displayable */

    SDL_Texture *texture;           /**< The texture (for the texture rendering) */
    SDL_Surface *surface;           /**< The surface (for the surface rendering) */

    void init(const int x , const int y, const int w, const int h, const int vx, const int vy);

    public :


    LX_Particle(const int x , const int y, const int w, const int h);
    LX_Particle(const LX_AABB *b);
    LX_Particle(const int x , const int y, const int w, const int h, const LX_Vector2D *v);
    LX_Particle(const int x , const int y, const int w, const int h, const int vx , const int vy);

    LX_Particle(const LX_AABB *b, const int vx , const int vy);
    LX_Particle(const LX_AABB *b, const LX_Vector2D *v);

    void update(void);

    bool setTexture(const char * str, const unsigned int id);
    bool setSurface(const char * str);
    void setSpeed(int x,int y);

    bool isDead(void);

    SDL_Texture * getTexture(void);
    SDL_Surface * getSurface(void);
    LX_AABB * getAABB();

    const int getX(void);
    const int getY(void);
    const int getW(void);
    const int getH(void);
    const unsigned int getDelay();


    ~LX_Particle();

};


#endif // PARTICLE_HPP_INCLUDED

