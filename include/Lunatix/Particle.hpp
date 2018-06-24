
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef PARTICLE_HPP_INCLUDED
#define PARTICLE_HPP_INCLUDED

/**
*   @file Particle.hpp
*   @brief The Particle file
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <memory>


namespace LX_FileIO
{
class LX_FileBuffer;
}

namespace LX_Graphics
{
class LX_Sprite;
}

namespace LX_Physics
{
struct LX_Vector2D;
struct LX_FloatingBox;
}

namespace LX_ParticleEngine
{

class LX_Particle_;

/**
*   @class LX_Particle
*   @brief The particle
*/
class LX_Particle final
{
    std::unique_ptr<LX_Particle_> _pimpl;

    LX_Particle( LX_Particle& p ) = delete;
    LX_Particle& operator =( LX_Particle& p ) = delete;


public:

    /**
    *   @fn LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_Physics::LX_FloatingBox& b) noexcept
    *   @param [in] sp The sprite of the particle
    *   @param [in] b The AABB that contains the coordinates, the width and the height
    */
    LX_Particle( LX_Graphics::LX_Sprite& sp, const LX_Physics::LX_FloatingBox& b ) noexcept;
    /**
    *   @fn LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_Physics::LX_FloatingBox& b,
    *                  const LX_Physics::LX_Vector2D& v) noexcept
    *
    *   @param [in] sp The sprite of the particle
    *   @param [in] b The AABB that contains the coordinates, the width and the height
    *   @param [in] v The vector that store the velocity
    */
    LX_Particle( LX_Graphics::LX_Sprite& sp, const LX_Physics::LX_FloatingBox& b,
                 const LX_Physics::LX_Vector2D& v ) noexcept;

    /**
    *   @fn void update() noexcept
    *   Update the particle state
    */
    void update() noexcept;
    /**
    *   @fn void draw() noexcept
    *   Draw the particle
    */
    void draw() noexcept;

    /**
    *   @fn bool isDead() const noexcept
    *   Check if the particle is dead and must be destroyed
    *   @return TRUE if the particle is dead, FALSE otherwise
    */
    bool isDead() const noexcept;
    /**
    *   @fn unsigned int getDelay() const noexcept
    *   Get the lifetime of the particle
    *   @return The lifetime
    */
    unsigned int getDelay() const noexcept;

    ~LX_Particle();
};

}

#endif // PARTICLE_HPP_INCLUDED
