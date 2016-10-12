

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

#include <exception>
#include <array>
#include <new>


namespace LX_ParticleEngine
{

/* Private implementation */

class LX_ParticleSystem_
{
    // Array of particles
    std::unique_ptr<std::unique_ptr<LX_Particle>[]> _particles;
    // The number of particles
    const unsigned int _nb_particles;

    /*
    *   Allocate the particle array
    *
    *   This function is automatically called by
    *   the constructor of the particle system
    */
    inline void allocateParticles_()
    {
        _particles.reset(new (std::nothrow) std::unique_ptr<LX_Particle>[_nb_particles]);

        if(_particles == nullptr)
        {
            /// !!! This code must not be executed !!!
            LX_SetError("Particle system: Cannot allocate the particles\n");
            std::terminate();
        }
    }

public:

    explicit LX_ParticleSystem_(const unsigned int nbPart)
        : _particles(nullptr), _nb_particles(nbPart)
    {
        allocateParticles_();
    }

    bool addParticle(LX_Particle *p)
    {
        bool done = false;

        if(p == nullptr)
            return false;

        for(unsigned int i = 0; i < _nb_particles; i++)
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

    bool rmParticle(unsigned int index)
    {
        if(index > _nb_particles || _particles[index] == nullptr)
            return false;

        _particles[index].reset();
        return true;
    }

    void updateParticles()
    {
        for(unsigned int i = 0; i < _nb_particles; i++)
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

    void displayParticles()
    {
        for(unsigned int i = 0; i < _nb_particles; i++)
        {
            if(_particles[i] != nullptr)
            {
                // Display the particle when the delay is a multiple of 2
                if(_particles[i]->getDelay()%2 == 0)
                    _particles[i]->draw();
            }
        }
    }

    unsigned int nbEmptyParticles() const
    {
        unsigned int nb = 0;

        for(unsigned int i = 0; i < _nb_particles; i++)
        {
            if(_particles[i] == nullptr)
                nb++;
        }

        return nb;
    }

    unsigned int nbActiveParticles() const
    {
        return _nb_particles - nbEmptyParticles();
    }

    unsigned int nbTotalParticles() const
    {
        return _nb_particles;
    }

    ~LX_ParticleSystem_()
    {
        for(unsigned int i = 0; i < _nb_particles; i++)
        {
            _particles[i].reset();
        }

        _particles.reset();
    }
};


/* Public functions */

LX_ParticleSystem::LX_ParticleSystem(const unsigned int nbPart)
    : _psimpl(new LX_ParticleSystem_(nbPart)) {}


LX_ParticleSystem::~LX_ParticleSystem()
{
    _psimpl.reset();
}


bool LX_ParticleSystem::addParticle(LX_Particle *p)
{
    return _psimpl->addParticle(p);
}


void LX_ParticleSystem::updateParticles()
{
    _psimpl->updateParticles();
}


void LX_ParticleSystem::displayParticles()
{
    _psimpl->displayParticles();
}


unsigned int LX_ParticleSystem::nbEmptyParticles() const
{
    return _psimpl->nbEmptyParticles();
}


unsigned int LX_ParticleSystem::nbActiveParticles() const
{
    return _psimpl->nbActiveParticles();
}


unsigned int LX_ParticleSystem::nbTotalParticles() const
{
    return _psimpl->nbTotalParticles();
}

};
