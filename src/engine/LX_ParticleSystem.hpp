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
*	@version 0.5
*
*/


class LX_Particle;


class LX_ParticleSystem{


    LX_Particle **particles;
    unsigned int nbParticles;
    unsigned int idWin;

    void init(unsigned int nbPart,unsigned int id);

    public:

    LX_ParticleSystem(unsigned int nbPart);
    LX_ParticleSystem(unsigned int nbPart,unsigned int id);

    bool addParticle(LX_Particle *p);
    bool rmParticle(unsigned int id);

    void updateParticles(void);
    void displayParticles(void);

    ~LX_ParticleSystem();

};


#endif // LX_PARTICLESYSTEM_HPP_INCLUDED
