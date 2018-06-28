
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
*   @file ParticleSystem.cpp
*   @brief The Particle system implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/ParticleSystem.hpp>
#include <Lunatix/Particle.hpp>
#include <Lunatix/Log.hpp>
#include <Lunatix/Error.hpp>

#include <exception>
#include <array>


namespace lx
{

namespace ParticleEngine
{

/* Private implementation */

class ParticleSystem_ final
{
    std::unique_ptr<std::unique_ptr<Particle>[]> _particles;
    const unsigned int _NB_PARTICLES;

public:

    explicit ParticleSystem_( const unsigned int nb_part ) noexcept
        : _particles( new std::unique_ptr<Particle>[nb_part] ),
          _NB_PARTICLES( nb_part ) {}

    bool addParticle( Particle * p ) const noexcept
    {
        if ( _particles == nullptr || p == nullptr )
            return false;

        bool done = false;

        for ( unsigned int i = 0; i < _NB_PARTICLES; i++ )
        {
            if ( _particles[i] == nullptr )
            {
                _particles[i].reset( p );
                done = true;
                break;
            }
        }

        return done;
    }

    bool rmParticle( unsigned int index ) const noexcept
    {
        if ( index > _NB_PARTICLES || _particles == nullptr
                || _particles[index] == nullptr )
            return false;

        _particles[index].reset();
        return true;
    }

    void updateParticles() const noexcept
    {
        if ( _particles == nullptr )
            return;

        for ( unsigned int i = 0; i < _NB_PARTICLES; i++ )
        {
            if ( _particles[i] != nullptr )
            {
                if ( _particles[i]->isDead() )
                    rmParticle( i );
                else
                    _particles[i]->update();
            }
        }
    }

    void displayParticles() const noexcept
    {
        if ( _particles == nullptr )
            return;

        for ( unsigned int i = 0; i < _NB_PARTICLES; i++ )
        {
            if ( _particles[i] != nullptr )
            {
                // Display the particle when the delay is a multiple of 2
                if ( _particles[i]->getDelay() % 2 == 0 )
                    _particles[i]->draw();
            }
        }
    }

    unsigned int nbEmptyParticles() const noexcept
    {
        if ( _particles == nullptr )
            return 0;

        unsigned int nb = 0;

        for ( unsigned int i = 0; i < _NB_PARTICLES; i++ )
        {
            if ( _particles[i] == nullptr )
                nb++;
        }

        return nb;
    }

    unsigned int nbActiveParticles() const noexcept
    {
        return ( _particles == nullptr ) ? 0 : _NB_PARTICLES - nbEmptyParticles();
    }

    unsigned int nbTotalParticles() const noexcept
    {
        return _NB_PARTICLES;
    }

    ~ParticleSystem_()
    {
        if ( _particles != nullptr )
        {
            for ( unsigned int i = 0; i < _NB_PARTICLES; i++ )
            {
                _particles[i].reset();
            }
        }

        _particles.reset();
    }
};


/* Public functions */

ParticleSystem::ParticleSystem( const unsigned int nbPart ) noexcept
    : _psimpl( new ParticleSystem_( nbPart ) ) {}


ParticleSystem::~ParticleSystem()
{
    _psimpl.reset();
}


bool ParticleSystem::addParticle( Particle * p ) noexcept
{
    return _psimpl->addParticle( p );
}


void ParticleSystem::updateParticles() noexcept
{
    _psimpl->updateParticles();
}


void ParticleSystem::displayParticles() const noexcept
{
    _psimpl->displayParticles();
}


unsigned int ParticleSystem::nbEmptyParticles() const noexcept
{
    return _psimpl->nbEmptyParticles();
}


unsigned int ParticleSystem::nbActiveParticles() const noexcept
{
    return _psimpl->nbActiveParticles();
}


unsigned int ParticleSystem::nbTotalParticles() const noexcept
{
    return _psimpl->nbTotalParticles();
}

}   // ParticleEngine

}   // lx
