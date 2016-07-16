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
    LX_AABB _box;                        /* The box of the particle         */
    LX_Physics::LX_Vector2D _velocity;   /* The velocity of the particle    */

    /*  Boolean variable defined to check if
        the texture of the particle was allocatedd outside
        of the particle */
    bool _texture_from_outside;

    unsigned int _lifetime;              /* The delay to stay displayable            */
    SDL_Texture *_texture;               /* The texture (for the texture rendering)  */
    SDL_Surface *_surface;               /* The surface (for the surface rendering)  */

    LX_Particle(LX_Particle& p);
    LX_Particle& operator =(LX_Particle& p);


public :

    /**
    *   @fn LX_Particle(const int x, const int y, const int w, const int h)
    *
    *   Create the instance using coordinates, width and height
    *
    *   @param x The X coordinate
    *   @param y The Y coordinate
    *   @param w The width
    *   @param h The height
    *
    */
    LX_Particle(const int x , const int y, const int w, const int h);

    /**
    *   @fn LX_Particle(const LX_AABB& b)
    *
    *   Create the instance using an AABB
    *
    *   @param b The AABB that contains the coordinates, the width and the height
    *
    */
    LX_Particle(const LX_AABB& b);

    /**
    *   @fn LX_Particle(const int x, const int y, const int w, const int h,
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
    *   @fn LX_Particle(const int x, const int y, const int w,
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
    *   @fn LX_Particle(const LX_AABB& b, const float vx, const float vy)
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
    *   @fn LX_Particle(const LX_AABB& b, const LX_Physics::LX_Vector2D& v)
    *
    *   Create the instance using an AABB and the velocity
    *
    *   @param b The AABB that contains the coordinates, the width and the height
    *   @param v The vector that store the velocity
    *
    */
    LX_Particle(const LX_AABB& b, const LX_Physics::LX_Vector2D& v);

    /**
    *   @fn void update(void)
    *
    *   Update the particle statement
    */
    void update(void);

    /**
    *   @fn bool isDead(void)
    *
    *   Check if the particle is dead and must be destroyed
    *
    *   @return TRUE if the particle is dead, FALSE otherwise
    *
    */
    bool isDead(void);

    /**
    *   @fn bool setTexture(LX_FileIO::LX_FileBuffer *buffer)
    *
    *   Set a texture to the particle
    *
    *   @param buffer The file buffer that contains the sprite to load
    *
    *   @return TRUE if the particle texture was created, FALSE otherwise
    */
    bool setTexture(LX_FileIO::LX_FileBuffer *buffer);

    /**
    *   @fn bool setTexture(SDL_Texture * t)
    *
    *   Set a texture to the particle
    *
    *   @param t the texture
    *
    *   @return TRUE if the particle texture in argument is valid, FALSE otherwise
    */
    bool setTexture(SDL_Texture * t);

    /**
    *   @fn bool setTexture(SDL_Surface * s)
    *
    *   Set a texture to the particle
    *
    *   @param s the surface
    *
    *   @return TRUE if the particle texture was created, FALSE otherwise
    */
    bool setTexture(SDL_Surface * s);

    /**
    *   @fn bool setSurface(LX_FileBuffer *buffer)
    *
    *   Set a surface to the particle
    *
    *   @param buffer The file buffer that contains the sprite to load
    *
    *   @return TRUE if the particle surface was created, FALSE otherwise
    */
    bool setSurface(LX_FileIO::LX_FileBuffer *buffer);

    /**
    *   @fn void setSpeed(const float vx,const float vy)
    *
    *   Set the velocity of the particle
    *
    *   @param vx The new X velocity
    *   @param vy The new Y velocity
    *
    *   @note This function is very useful to set gravity or acceleration
    */
    void setSpeed(const float vx,const float vy);

    /**
    *   @fn SDL_Texture * getTexture(void)
    *
    *   Get the texture
    *
    *   @return A pointer to the texture
    *
    */
    SDL_Texture * getTexture(void);

    /**
    *   @fn SDL_Surface * getSurface(void)
    *
    *   Get the surface
    *
    *   @return A pointer to the surface
    */
    SDL_Surface * getSurface(void);

    /**
    *   @fn const LX_AABB * getAABB(void)
    *
    *   Get the AABB
    *
    *   @return A pointer to the AABB
    */
    LX_AABB getAABB(void);

    /**
    *   @fn int getX(void)
    *
    *   Get the X position
    *
    *   @return The X position
    */
    int getX(void);

    /**
    *   @fn int getY(void)
    *
    *   Get the Y position
    *
    *   @return The Y position
    */
    int getY(void);

    /**
    *   @fn int getW(void)
    *
    *   Get the width
    *
    *   @return The width
    */
    int getW(void);

    /**
    *   @fn int getH(void)
    *
    *   Get the height
    *
    *   @return The height
    */
    int getH(void);

    /**
    *   @fn unsigned int getDelay(void)
    *
    *   Get the lifetime of the particle
    *
    *   @return The lifetime
    */
    unsigned int getDelay(void);

    /**
    *   @fn ~LX_Particle()
    *
    *   Destroy the instance
    */
    ~LX_Particle();
};

};

#endif // PARTICLE_HPP_INCLUDED
