#ifndef PARTICLE_HPP_INCLUDED
#define PARTICLE_HPP_INCLUDED


/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_Particle.hpp
*    @brief The Particle file
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*
*/

#include <LunatiX/LX_AABB.hpp>
#include <LunatiX/LX_Vector2D.hpp>

#define DELAY 16        /**< The delay of the particle to stay alive */


namespace LX_FileIO
{
class LX_FileBuffer;
};

namespace LX_Graphics
{
class LX_Sprite;
}


namespace LX_ParticleEngine
{

/**
*   @class LX_Particle
*   @brief The particle
*/
class LX_Particle
{
    LX_AABB _box;                       /* The box of the particle                 */
    unsigned int _lifetime;             /* The delay to stay displayable           */
    LX_Physics::LX_Vector2D _velocity;  /* The velocity of the particle            */
    LX_Graphics::LX_Sprite& _texture;   /* The texture (for the texture rendering) */

    LX_Particle(LX_Particle& p);
    LX_Particle& operator =(LX_Particle& p);


public :

    /**
    *   @fn LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_AABB& b)
    *   @brief Constructor
    *
    *   Create the instance using an AABB
    *
    *   @param [in] sp The sprite of the particle
    *   @param [in] b The AABB that contains the coordinates, the width and the height
    *
    */
    LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_AABB& b);

    /**
    *   @fn LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_AABB& b, const float vx, const float vy)
    *
    *   Create the instance using an AABB and the velocity
    *
    *   @param [in] sp The sprite of the particle
    *   @param [in] b The AABB that contains the coordinates, the width and the height
    *   @param [in] vx The X velocity
    *   @param [in] vy The Y velocity
    *
    */
    LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_AABB& b, const float vx, const float vy);

    /**
    *   @fn LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_AABB& b, const LX_Physics::LX_Vector2D& v)
    *
    *   Create the instance using an AABB and the velocity
    *
    *   @param [in] sp The sprite of the particle
    *   @param [in] b The AABB that contains the coordinates, the width and the height
    *   @param [in] v The vector that store the velocity
    *
    */
    LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_AABB& b, const LX_Physics::LX_Vector2D& v);

    /**
    *   @fn void update()
    *
    *   Update the particle statement
    */
    void update();

    /**
    *   @fn void draw()
    *
    *   Draw the particle
    */
    void draw();

    /**
    *   @fn bool isDead() const
    *
    *   Check if the particle is dead and must be destroyed
    *
    *   @return TRUE if the particle is dead, FALSE otherwise
    *
    */
    bool isDead() const;

    /**
    *   @fn unsigned int getDelay() const
    *
    *   Get the lifetime of the particle
    *
    *   @return The lifetime
    */
    unsigned int getDelay() const;

    /// Destructor
    ~LX_Particle() = default;
};

};

#endif // PARTICLE_HPP_INCLUDED
