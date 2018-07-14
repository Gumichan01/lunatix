
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


namespace lx
{

// Forward declarations

namespace Graphics
{
class Sprite;
}

namespace Physics
{
struct Vector2D;
struct FloatingBox;
}

//  Forward declarations (END)

namespace ParticleEngine
{

class Particle_;

/**
*   @class Particle
*   @brief The particle
*/
class Particle final
{
    std::unique_ptr<Particle_> m_pimpl;

    Particle( Particle& p ) = delete;
    Particle& operator =( Particle& p ) = delete;


public:

    /**
    *   @fn Particle(lx::Graphics::Sprite& sp, const lx::Physics::FloatingBox& b) noexcept
    *   @param [in] sp The sprite of the particle
    *   @param [in] b The AABB that contains the coordinates, the width and the height
    */
    Particle( lx::Graphics::Sprite& sp, const lx::Physics::FloatingBox& b ) noexcept;
    /**
    *   @fn Particle(lx::Graphics::Sprite& sp, const lx::Physics::FloatingBox& b,
    *                  const lx::Physics::Vector2D& v) noexcept
    *
    *   @param [in] sp The sprite of the particle
    *   @param [in] b The AABB that contains the coordinates, the width and the height
    *   @param [in] v The vector that store the velocity
    */
    Particle( lx::Graphics::Sprite& sp, const lx::Physics::FloatingBox& b,
              const lx::Physics::Vector2D& v ) noexcept;

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

    ~Particle();
};

}   // ParticleEngine

}   // lx

#endif // PARTICLE_HPP_INCLUDED
