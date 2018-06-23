
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

#ifndef LX_PARTICLESYSTEM_HPP_INCLUDED
#define LX_PARTICLESYSTEM_HPP_INCLUDED

/**
*   @file LX_ParticleSystem.hpp
*   @brief The Particle system file
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <memory>

/**
*   @ingroup Graphics
*   @namespace LX_ParticleEngine
*   @brief The particle engine
*
*   It handles a basic particle system
*/
namespace LX_ParticleEngine
{

class LX_Particle;
class LX_ParticleSystem_;

/**
*   @class LX_ParticleSystem
*   @brief The particle system
*/
class LX_ParticleSystem final
{
    std::unique_ptr<LX_ParticleSystem_> _psimpl;

    LX_ParticleSystem( LX_ParticleSystem& ps ) = delete;
    LX_ParticleSystem& operator =( LX_ParticleSystem& ps ) = delete;

public:

    /**
    *   @fn LX_ParticleSystem(const unsigned int nbPart) noexcept
    *   @param [in] nbPart The number of particles to define in the system
    */
    explicit LX_ParticleSystem( const unsigned int nbPart ) noexcept;

    /**
    *   @fn bool addParticle(LX_Particle *p) noexcept
    *   @param [in] p The particle to add
    *
    *   @return TRUE if the system had the particle with succes.
    *          FALSE if the particle is a null pointer or the system cannot add it
    */
    bool addParticle( LX_Particle * p ) noexcept;
    /**
    *   @fn void updateParticles() noexcept
    *   Update the status of the particles
    */
    void updateParticles() noexcept;
    /**
    *   @fn void displayParticles() const noexcept
    *   Display the particles
    */
    void displayParticles() const noexcept;

    /**
    *   @fn unsigned int nbEmptyParticles() const noexcept
    *   Get the number of empty slots to set particles
    *   @return The number of available slots of the particle system
    */
    unsigned int nbEmptyParticles() const noexcept;
    /**
    *   @fn unsigned int nbActiveParticles() const noexcept
    *   Get the number of initialized particles
    *   @return The number of particles that are not null of the system
    */
    unsigned int nbActiveParticles() const noexcept;
    /**
    *   @fn unsigned int nbTotalParticles() const noexcept
    *   Get the maximum number of particles
    *   @return The total number of particles the current particle system can have
    */
    unsigned int nbTotalParticles() const noexcept;

    ~LX_ParticleSystem();
};

}

#endif // LX_PARTICLESYSTEM_HPP_INCLUDED
