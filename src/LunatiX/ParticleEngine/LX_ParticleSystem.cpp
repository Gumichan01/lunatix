

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
*    @file LX_ParticleSystem.cpp
*    @brief The Particle system implementation
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/LX_ParticleSystem.hpp>
#include <LunatiX/LX_Particle.hpp>
#include <LunatiX/LX_Error.hpp>

#include <array>
#include <new>


namespace LX_ParticleEngine
{

LX_ParticleSystem::LX_ParticleSystem(const unsigned int nbPart)
    : LX_ParticleSystem(nbPart,0) {}


LX_ParticleSystem::LX_ParticleSystem(const unsigned int nbPart,const unsigned int id)
    : _particles(nullptr), _nb_particles(nbPart), _idwin(id)
{
    allocateParticles_(_nb_particles);
}


LX_ParticleSystem::~LX_ParticleSystem()
{
    const unsigned int n = _nb_particles;

    for(unsigned int i = 0; i < n; i++)
    {
        _particles[i].reset();
    }

    _particles.reset();
}


/*
*   Allocate the particle array
*
*   This function is automatically called by one of
*   the following constructors of the particle system
*
*/
void LX_ParticleSystem::allocateParticles_(unsigned int nbPart)
{
    _particles.reset(new (std::nothrow) std::unique_ptr<LX_Particle>[nbPart]);

    if(_particles == nullptr)
    {
        LX_SetError("LX_ParticleSystem constructor: Cannot allocate the particles\n");
        _nb_particles = 0;
    }
}


bool LX_ParticleSystem::addParticle(LX_Particle *p)
{
    bool done = false;
    const unsigned int n = _nb_particles;

    if(p == nullptr)
        return false;

    for(unsigned int i = 0; i < n; i++)
    {
        if(_particles[i] == nullptr)
        {
            _particles[i].reset(p);
            done = true;
            break;
        }
    }

    return done;
}


bool LX_ParticleSystem::rmParticle(unsigned int index)
{
    if(index > _nb_particles || _particles[index] == nullptr)
        return false;

    _particles[index].reset();
    return true;
}


void LX_ParticleSystem::updateParticles()
{
    const unsigned int n = _nb_particles;

    for(unsigned int i = 0; i < n; i++)
    {
        if(_particles[i] != nullptr)
        {
            if(_particles[i]->isDead())
                rmParticle(i);
            else
                _particles[i]->update();
        }
    }
}


void LX_ParticleSystem::displayParticles()
{
    const unsigned int N = _nb_particles;

    for(unsigned int i = 0; i < N; i++)
    {
        if(_particles[i] != nullptr)
        {
            // Display the particle when the delay is a multiple of 2
            if(_particles[i]->getDelay()%2 == 0)
                _particles[i]->draw();
        }
    }
}


unsigned int LX_ParticleSystem::nbEmptyParticles() const
{
    const unsigned int n = _nb_particles;
    unsigned int nb = 0;

    for(unsigned int i = 0; i < n; i++)
    {
        if(_particles[i] == nullptr)
            nb++;
    }

    return nb;
}


unsigned int LX_ParticleSystem::nbActiveParticles() const
{
    return _nb_particles - nbEmptyParticles();
}


unsigned int LX_ParticleSystem::nbTotalParticles() const
{
    return _nb_particles;
}

};
