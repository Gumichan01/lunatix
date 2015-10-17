#ifndef LX_PARTICLESYSTEM_HPP_INCLUDED
#define LX_PARTICLESYSTEM_HPP_INCLUDED



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
*	@file LX_ParticleSystem.hpp
*	@brief The Particle system file
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
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
*   @brief The particle system class
*
*   This class describes a particle system
*/
class LX_ParticleSystem
{


    LX_Particle **particles;            /**< The array of particles */
    unsigned int nbParticles;           /**< The number of particles */
    unsigned int idWin;                 /**< The id of the window to put the particles */

    void init(unsigned int nbPart,unsigned int id);

public:

    LX_ParticleSystem(unsigned int nbPart);
    LX_ParticleSystem(unsigned int nbPart,unsigned int id);

    bool addParticle(LX_Particle *p);
    bool rmParticle(unsigned int index);

    void updateParticles(void);
    void displayParticles(void);

    unsigned int nbEmptyParticles(void);
    unsigned int nbActiveParticles(void);
    const unsigned int nbTotalParticles(void);

    ~LX_ParticleSystem();

};

};

#endif // LX_PARTICLESYSTEM_HPP_INCLUDED
