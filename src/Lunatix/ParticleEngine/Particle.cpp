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
*   @version 0.13
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
    FloatingBox _box;
    unsigned int _lifetime;             /* The delay to stay displayable */
    lx::Physics::Vector2D _velocity;
    lx::Graphics::Sprite& _texture;

public:

    Particle_( lx::Graphics::Sprite& sp, const FloatingBox& b,
                  const lx::Physics::Vector2D& v ) noexcept
        : _box( b ), _lifetime( xrand<unsigned int>( 0, DELAY ) ), _velocity( v ),
          _texture( sp ) {}

    void update() noexcept
    {
        if ( _lifetime > 0 )
        {
            lx::Physics::moveBox( _box, _velocity );
            _lifetime--;
        }
    }

    void draw() noexcept
    {
        _texture.draw( lx::Graphics::toImgRect( _box ) );
    }

    bool isDead() const noexcept
    {
        return _lifetime == 0;
    }

    unsigned int getDelay() const noexcept
    {
        return _lifetime;
    }

    ~Particle_() = default;
};

/* Particle — public interface */

Particle::Particle( lx::Graphics::Sprite& sp, const FloatingBox& b ) noexcept
    : _pimpl( new Particle_( sp, b, VNULL ) ) {}


Particle::Particle( lx::Graphics::Sprite& sp, const FloatingBox& b,
                          const lx::Physics::Vector2D& v ) noexcept
    : _pimpl( new Particle_( sp, b, v ) ) {}


void Particle::update() noexcept
{
    _pimpl->update();
}


void Particle::draw() noexcept
{
    _pimpl->draw();
}


bool Particle::isDead() const noexcept
{
    return _pimpl->isDead();
}


unsigned int Particle::getDelay() const noexcept
{
    return _pimpl->getDelay();
}

Particle::~Particle()
{
    _pimpl.reset();
}

}   // ParticleEngine

}   // lx
