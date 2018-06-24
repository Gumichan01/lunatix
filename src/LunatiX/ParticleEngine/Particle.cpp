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

#include <LunatiX/Particle.hpp>
#include <LunatiX/Vector2D.hpp>
#include <LunatiX/Physics.hpp>
#include <LunatiX/Hitbox.hpp>
#include <LunatiX/Random.hpp>
#include <LunatiX/Texture.hpp>

using namespace LX_Random;
using namespace LX_Physics;


namespace LX_ParticleEngine
{
using FloatBox::FNIL;
const unsigned int DELAY = 16;
constexpr LX_Vector2D VNULL = {FNIL, FNIL};

/* LX_Particle — private implementation */

class LX_Particle_ final
{
    LX_FloatingBox _box;
    unsigned int _lifetime;             /* The delay to stay displayable */
    LX_Physics::LX_Vector2D _velocity;
    LX_Graphics::LX_Sprite& _texture;

public:

    LX_Particle_( LX_Graphics::LX_Sprite& sp, const LX_FloatingBox& b,
                  const LX_Physics::LX_Vector2D& v ) noexcept
        : _box( b ), _lifetime( xrand<unsigned int>( 0, DELAY ) ), _velocity( v ),
          _texture( sp ) {}

    void update() noexcept
    {
        if ( _lifetime > 0 )
        {
            LX_Physics::moveBox( _box, _velocity );
            _lifetime--;
        }
    }

    void draw() noexcept
    {
        _texture.draw( LX_Graphics::toImgRect( _box ) );
    }

    bool isDead() const noexcept
    {
        return _lifetime == 0;
    }

    unsigned int getDelay() const noexcept
    {
        return _lifetime;
    }

    ~LX_Particle_() = default;
};

/* LX_Particle — public interface */

LX_Particle::LX_Particle( LX_Graphics::LX_Sprite& sp, const LX_FloatingBox& b ) noexcept
    : _pimpl( new LX_Particle_( sp, b, VNULL ) ) {}


LX_Particle::LX_Particle( LX_Graphics::LX_Sprite& sp, const LX_FloatingBox& b,
                          const LX_Physics::LX_Vector2D& v ) noexcept
    : _pimpl( new LX_Particle_( sp, b, v ) ) {}


void LX_Particle::update() noexcept
{
    _pimpl->update();
}


void LX_Particle::draw() noexcept
{
    _pimpl->draw();
}


bool LX_Particle::isDead() const noexcept
{
    return _pimpl->isDead();
}


unsigned int LX_Particle::getDelay() const noexcept
{
    return _pimpl->getDelay();
}

LX_Particle::~LX_Particle()
{
    _pimpl.reset();
}

}
