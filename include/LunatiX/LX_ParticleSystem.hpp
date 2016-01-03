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
*	@version 0.7
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
    LX_Particle **particles;        /* The array of particles                   */
    unsigned int nbParticles;       /* The number of particles                  */
    unsigned int idWin;             /* The id of the window to put particles    */

    LX_ParticleSystem(LX_ParticleSystem& ps);
    LX_ParticleSystem& operator =(LX_ParticleSystem& ps);

    void allocateParticles(unsigned int nbPart);

public:

    LX_ParticleSystem(const unsigned int nbPart);
    LX_ParticleSystem(const unsigned int nbPart,const unsigned int id);

    bool addParticle(LX_Particle *p);
    bool rmParticle(unsigned int index);

    void updateParticles(void);
    void displayParticles(void);

    unsigned int nbEmptyParticles(void);
    unsigned int nbActiveParticles(void);
    unsigned int nbTotalParticles(void);

    ~LX_ParticleSystem();
};

};

#endif // LX_PARTICLESYSTEM_HPP_INCLUDED
