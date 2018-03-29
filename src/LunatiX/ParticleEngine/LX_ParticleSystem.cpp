
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

/**
*   @file LX_ParticleSystem.cpp
*   @brief The Particle system implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/LX_ParticleSystem.hpp>
#include <LunatiX/LX_Particle.hpp>
#include <LunatiX/LX_Log.hpp>
#include <LunatiX/LX_Error.hpp>

#include <exception>
#include <array>


namespace LX_ParticleEngine
{

/* Private implementation */

class LX_ParticleSystem_ final
{
    std::unique_ptr<std::unique_ptr<LX_Particle>[]> _particles;
    const unsigned int _NB_PARTICLES;

public:

    explicit LX_ParticleSystem_(const unsigned int nb_part) noexcept
        : _particles(new std::unique_ptr<LX_Particle>[nb_part]),
          _NB_PARTICLES(nb_part) {}

    bool addParticle(LX_Particle *p) const noexcept
    {
        if(_particles == nullptr || p == nullptr)
            return false;

        bool done = false;

        for(unsigned int i = 0; i < _NB_PARTICLES; i++)
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

    bool rmParticle(unsigned int index) const noexcept
    {
        if(index > _NB_PARTICLES || _particles == nullptr
                || _particles[index] == nullptr)
            return false;

        _particles[index].reset();
        return true;
    }

    void updateParticles() const noexcept
    {
        if(_particles == nullptr)
            return;

        for(unsigned int i = 0; i < _NB_PARTICLES; i++)
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

    void displayParticles() const noexcept
    {
        if(_particles == nullptr)
            return;

        for(unsigned int i = 0; i < _NB_PARTICLES; i++)
        {
            if(_particles[i] != nullptr)
            {
                // Display the particle when the delay is a multiple of 2
                if(_particles[i]->getDelay()%2 == 0)
                    _particles[i]->draw();
            }
        }
    }

    unsigned int nbEmptyParticles() const noexcept
    {
        if(_particles == nullptr)
            return 0;

        unsigned int nb = 0;

        for(unsigned int i = 0; i < _NB_PARTICLES; i++)
        {
            if(_particles[i] == nullptr)
                nb++;
        }

        return nb;
    }

    unsigned int nbActiveParticles() const noexcept
    {
        return (_particles == nullptr) ? 0 : _NB_PARTICLES - nbEmptyParticles();
    }

    unsigned int nbTotalParticles() const noexcept
    {
        return _NB_PARTICLES;
    }

    ~LX_ParticleSystem_()
    {
        if(_particles != nullptr)
        {
            for(unsigned int i = 0; i < _NB_PARTICLES; i++)
            {
                _particles[i].reset();
            }
        }

        _particles.reset();
    }
};


/* Public functions */

LX_ParticleSystem::LX_ParticleSystem(const unsigned int nbPart) noexcept
    : _psimpl(new LX_ParticleSystem_(nbPart)) {}


LX_ParticleSystem::~LX_ParticleSystem()
{
    _psimpl.reset();
}


bool LX_ParticleSystem::addParticle(LX_Particle *p) noexcept
{
    return _psimpl->addParticle(p);
}


void LX_ParticleSystem::updateParticles() noexcept
{
    _psimpl->updateParticles();
}


void LX_ParticleSystem::displayParticles() const noexcept
{
    _psimpl->displayParticles();
}


unsigned int LX_ParticleSystem::nbEmptyParticles() const noexcept
{
    return _psimpl->nbEmptyParticles();
}


unsigned int LX_ParticleSystem::nbActiveParticles() const noexcept
{
    return _psimpl->nbActiveParticles();
}


unsigned int LX_ParticleSystem::nbTotalParticles() const noexcept
{
    return _psimpl->nbTotalParticles();
}

}
