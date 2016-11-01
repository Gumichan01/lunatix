#ifndef LX_PARTICLESYSTEM_HPP_INCLUDED
#define LX_PARTICLESYSTEM_HPP_INCLUDED


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
*    @file LX_ParticleSystem.hpp
*    @brief The Particle system file
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <memory>

/**
*   @namespace LX_ParticleEngine
*   @brief The particle engine
*
*   it handles a basic particle system
*
*/
namespace LX_ParticleEngine
{

class LX_Particle;
class LX_ParticleSystem_;

/**
*   @class LX_ParticleSystem
*   @brief The particle system
*/
class LX_ParticleSystem
{
    std::unique_ptr<LX_ParticleSystem_> _psimpl;

    LX_ParticleSystem(LX_ParticleSystem& ps);
    LX_ParticleSystem& operator =(LX_ParticleSystem& ps);

public:

    /**
    *   @fn LX_ParticleSystem(const unsigned int nbPart)
    *   @brief Constructor
    *
    *   Create the instance with a number of particles
    *
    *   @param [in] nbPart The number of particles to define in the system
    *
    */
    explicit LX_ParticleSystem(const unsigned int nbPart);

    /**
    *   @fn bool addParticle(LX_Particle *p)
    *
    *   Add a particle into the particle system
    *
    *   @param [in] p The particle to add
    *
    *   @return TRUE if the system had the particle with succes.
    *           FALSE if the particle is a null pointer or the system cannot add it
    *
    */
    bool addParticle(LX_Particle *p);

    /**
    *   @fn void updateParticles()
    *   Update the particles
    */
    void updateParticles();

    /**
    *   @fn void displayParticles() const
    *   Display the particles
    */
    void displayParticles() const;

    /**
    *   @fn unsigned int nbEmptyParticles() const
    *
    *   Get the number of empty slots to set particles
    *
    *   @return The number of available slots of the particle system
    */
    unsigned int nbEmptyParticles() const;

    /**
    *   @fn unsigned int nbActiveParticles() const
    *
    *   Get the number of initialized particles
    *
    *   @return The number of particles that are not null of the system
    */
    unsigned int nbActiveParticles() const;

    /**
    *   @fn unsigned int nbTotalParticles() const
    *
    *   Get the maximum number of particles
    *
    *   @return The total number of particles the current particle system can have
    */
    unsigned int nbTotalParticles() const;

    /// Destructor
    ~LX_ParticleSystem();
};

};

#endif // LX_PARTICLESYSTEM_HPP_INCLUDED
