#ifndef LX_PARTICLESYSTEM_HPP_INCLUDED
#define LX_PARTICLESYSTEM_HPP_INCLUDED


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
*	@file LX_ParticleSystem.hpp
*	@brief The Particle system file
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

/**
*   @namespace LX_ParticleEngine
*   @brief The particle engine
*
*   This namespace describes the particle engine
*
*/
namespace LX_ParticleEngine
{

class LX_Particle;


/**
*   @class LX_ParticleSystem
*   @brief The particle system
*/
class LX_ParticleSystem
{
    LX_Particle **_particles;        /* The array of particles                   */
    unsigned int _nb_particles;       /* The number of particles                  */
    unsigned int _idwin;             /* The id of the window to put particles    */

    LX_ParticleSystem(LX_ParticleSystem& ps);
    LX_ParticleSystem& operator =(LX_ParticleSystem& ps);

    void allocateParticles(unsigned int nbPart);

public:

    /**
    *   @fn LX_ParticleSystem(const unsigned int nbPart)
    *
    *   Create the instance with a number of particles
    *
    *   @param nbPart The number of particles to define in the system
    *
    */
    LX_ParticleSystem(const unsigned int nbPart);

    /**
    *   @fn LX_ParticleSystem(const unsigned int nbPart,const unsigned int id)
    *
    *   Create the instance with a number of particles and the id of the window
    *
    *   @param  nbPart The number of particles to define in the system
    *   @param  id The id of the window in the LX_WindowManager
    *           to get the rendeering context
    *
    */
    LX_ParticleSystem(const unsigned int nbPart,const unsigned int id);

    /**
    *   @fn bool addParticle(LX_Particle *p)
    *
    *   Add a particle into the particle system
    *
    *   @param p The particle to add
    *
    *   @return TRUE if the system had the particle with succes.
    *           FALSE if the particle is a null pointer or the system cannot add it
    *
    */
    bool addParticle(LX_Particle *p);

    /**
    *   @fn bool rmParticle(unsigned int index)
    *
    *   Destroy a particle from the particle system according to its index
    *
    *   @param index the index of the particle in the list
    *
    *   @return TRUE if the system found the particle and destroyed it.
    *           FALSE if the index is invalid
    *
    */
    bool rmParticle(unsigned int index);

    /**
    *   @fn void updateParticles(void)
    *
    *   Update the particles
    *
    */
    void updateParticles(void);

    /**
    *   @fn void displayParticles(void)
    *
    *   Display the particles
    *
    */
    void displayParticles(void);

    /**
    *   @fn unsigned int nbEmptyParticles(void)
    *
    *   Get the number of empty slots to set particles
    *
    *   @return The number of available slots of the particle system
    *
    */
    unsigned int nbEmptyParticles(void);

    /**
    *   @fn unsigned int nbActiveParticles(void)
    *
    *   Get the number of initialized particles
    *
    *   @return The number of particles that are not null of the system
    *
    */
    unsigned int nbActiveParticles(void);

    /**
    *   @fn unsigned int nbTotalParticles(void)
    *
    *   Get the maximum number of particles
    *
    *   @return The total number of particles the current particle system can have
    *
    */
    unsigned int nbTotalParticles(void);

    /**
    *   @fn ~LX_ParticleSystem()
    *
    *   Destroy the instance cleaning up the particles
    *
    */
    ~LX_ParticleSystem();
};

};

#endif // LX_PARTICLESYSTEM_HPP_INCLUDED
