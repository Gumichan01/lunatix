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
*   @file Particle.cpp
*   @brief The particle implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <Lunatix/Particle.hpp>
#include <Lunatix/Vector2D.hpp>
#include <Lunatix/Physics.hpp>
#include <Lunatix/Hitbox.hpp>
#include <Lunatix/Random.hpp>
#include <Lunatix/Texture.hpp>

using namespace lx::Random;
using namespace lx::Physics;


namespace lx
{

namespace ParticleEngine
{

using FloatBox::FNIL;
const unsigned int DELAY = 16;
constexpr Vector2D VNULL = {FNIL, FNIL};

/* Particle — private implementation */

class Particle_ final
{
    FloatingBox m_fbox;
    unsigned int m_lifetime;             /* The delay to stay displayable */
    lx::Physics::Vector2D m_velocity;
    lx::Graphics::Sprite& m_texture;

public:

    Particle_( lx::Graphics::Sprite& sp, const FloatingBox& b,
               const lx::Physics::Vector2D& v ) noexcept
        : m_fbox( b ), m_lifetime( xrand<unsigned int>( 0, DELAY ) ), m_velocity( v ),
          m_texture( sp ) {}

    void update() noexcept
    {
        if ( m_lifetime > 0 )
        {
            lx::Physics::moveBox( m_fbox, m_velocity );
            m_lifetime--;
        }
    }

    void draw() noexcept
    {
        m_texture.draw( lx::Graphics::toImgRect( m_fbox ) );
    }

    bool isDead() const noexcept
    {
        return m_lifetime == 0;
    }

    unsigned int getDelay() const noexcept
    {
        return m_lifetime;
    }

    ~Particle_() = default;
};

/* Particle — public interface */

Particle::Particle( lx::Graphics::Sprite& sp, const FloatingBox& b ) noexcept
    : m_pimpl( new Particle_( sp, b, VNULL ) ) {}


Particle::Particle( lx::Graphics::Sprite& sp, const FloatingBox& b,
                    const lx::Physics::Vector2D& v ) noexcept
    : m_pimpl( new Particle_( sp, b, v ) ) {}


void Particle::update() noexcept
{
    m_pimpl->update();
}


void Particle::draw() noexcept
{
    m_pimpl->draw();
}


bool Particle::isDead() const noexcept
{
    return m_pimpl->isDead();
}


unsigned int Particle::getDelay() const noexcept
{
    return m_pimpl->getDelay();
}

Particle::~Particle()
{
    m_pimpl.reset();
}

}   // ParticleEngine

}   // lx
