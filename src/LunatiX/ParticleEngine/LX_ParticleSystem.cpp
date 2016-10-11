

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
    unsigned int _nb_particles;
    // The id of the window to put particles
    unsigned int _idwin;

    /*
    *   Allocate the particle array
    *
    *   This function is automatically called by
    *   the constructor of the particle system
    */
    inline void allocateParticles_(unsigned int nbPart)
    {
        _particles.reset(new (std::nothrow) std::unique_ptr<LX_Particle>[nbPart]);

        if(_particles == nullptr)
        {
            /// !!! This code must not be executed !!!
            LX_SetError("Particle system: Cannot allocate the particles\n");
            std::terminate();
        }
    }

public:

    explicit LX_ParticleSystem_(const unsigned int nbPart,const unsigned int id)
        : _particles(nullptr), _nb_particles(nbPart), _idwin(id)
    {
        allocateParticles_(_nb_particles);
    }

    bool addParticle(LX_Particle *p)
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

    bool rmParticle(unsigned int index)
    {
        if(index > _nb_particles || _particles[index] == nullptr)
            return false;

        _particles[index].reset();
        return true;
    }

    void updateParticles()
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

    void displayParticles()
    {
        const unsigned int N = _nb_particles;

        for(unsigned int i = 0; i < N; i++) /// Refactor the foreach
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
        const unsigned int n = _nb_particles;
        unsigned int nb = 0;

        for(unsigned int i = 0; i < n; i++)
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
        const unsigned int n = _nb_particles;

        for(unsigned int i = 0; i < n; i++) /// Refactor the foreach
        {
            _particles[i].reset();
        }

        _particles.reset();
    }
};


/* Public functions */

LX_ParticleSystem::LX_ParticleSystem(const unsigned int nbPart)
    : LX_ParticleSystem(nbPart,0) {}


LX_ParticleSystem::LX_ParticleSystem(const unsigned int nbPart,
                                     const unsigned int id)
    : _psimpl(new LX_ParticleSystem_(nbPart,id)) {}


LX_ParticleSystem::~LX_ParticleSystem()
{
    _psimpl.reset();
}


bool LX_ParticleSystem::addParticle(LX_Particle *p)
{
    return _psimpl->addParticle(p);
}


bool LX_ParticleSystem::rmParticle(unsigned int index)
{
    return _psimpl->rmParticle(index);
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
