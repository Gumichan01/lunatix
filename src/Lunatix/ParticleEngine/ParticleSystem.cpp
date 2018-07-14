
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
    std::unique_ptr<std::unique_ptr<Particle>[]> m_particles;
    const unsigned int M_NB_PARTICLES;

public:

    explicit ParticleSystem_( const unsigned int nb_part ) noexcept
        : m_particles( new std::unique_ptr<Particle>[nb_part] ),
          M_NB_PARTICLES( nb_part ) {}

    bool addParticle( Particle * p ) const noexcept
    {
        if ( m_particles == nullptr || p == nullptr )
            return false;

        bool done = false;

        for ( unsigned int i = 0; i < M_NB_PARTICLES; i++ )
        {
            if ( m_particles[i] == nullptr )
            {
                m_particles[i].reset( p );
                done = true;
                break;
            }
        }

        return done;
    }

    bool rmParticle( unsigned int index ) const noexcept
    {
        if ( index > M_NB_PARTICLES || m_particles == nullptr
                || m_particles[index] == nullptr )
            return false;

        m_particles[index].reset();
        return true;
    }

    void updateParticles() const noexcept
    {
        if ( m_particles == nullptr )
            return;

        for ( unsigned int i = 0; i < M_NB_PARTICLES; i++ )
        {
            if ( m_particles[i] != nullptr )
            {
                if ( m_particles[i]->isDead() )
                    rmParticle( i );
                else
                    m_particles[i]->update();
            }
        }
    }

    void displayParticles() const noexcept
    {
        if ( m_particles == nullptr )
            return;

        for ( unsigned int i = 0; i < M_NB_PARTICLES; i++ )
        {
            if ( m_particles[i] != nullptr )
            {
                // Display the particle when the delay is a multiple of 2
                if ( m_particles[i]->getDelay() % 2 == 0 )
                    m_particles[i]->draw();
            }
        }
    }

    unsigned int nbEmptyParticles() const noexcept
    {
        if ( m_particles == nullptr )
            return 0;

        unsigned int nb = 0;

        for ( unsigned int i = 0; i < M_NB_PARTICLES; i++ )
        {
            if ( m_particles[i] == nullptr )
                nb++;
        }

        return nb;
    }

    unsigned int nbActiveParticles() const noexcept
    {
        return ( m_particles == nullptr ) ? 0 : M_NB_PARTICLES - nbEmptyParticles();
    }

    unsigned int nbTotalParticles() const noexcept
    {
        return M_NB_PARTICLES;
    }

    ~ParticleSystem_()
    {
        if ( m_particles != nullptr )
        {
            for ( unsigned int i = 0; i < M_NB_PARTICLES; i++ )
            {
                m_particles[i].reset();
            }
        }

        m_particles.reset();
    }
};


/* Public functions */

ParticleSystem::ParticleSystem( const unsigned int nbPart ) noexcept
    : m_psimpl( new ParticleSystem_( nbPart ) ) {}


ParticleSystem::~ParticleSystem()
{
    m_psimpl.reset();
}


bool ParticleSystem::addParticle( Particle * p ) noexcept
{
    return m_psimpl->addParticle( p );
}


void ParticleSystem::updateParticles() noexcept
{
    m_psimpl->updateParticles();
}


void ParticleSystem::displayParticles() const noexcept
{
    m_psimpl->displayParticles();
}


unsigned int ParticleSystem::nbEmptyParticles() const noexcept
{
    return m_psimpl->nbEmptyParticles();
}


unsigned int ParticleSystem::nbActiveParticles() const noexcept
{
    return m_psimpl->nbActiveParticles();
}


unsigned int ParticleSystem::nbTotalParticles() const noexcept
{
    return m_psimpl->nbTotalParticles();
}

}   // ParticleEngine

}   // lx
