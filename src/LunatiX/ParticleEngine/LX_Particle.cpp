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
*   @file LX_Particle.cpp
*   @brief The particle implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/LX_Particle.hpp>
#include <LunatiX/LX_Vector2D.hpp>
#include <LunatiX/LX_Physics.hpp>
#include <LunatiX/LX_Random.hpp>
#include <LunatiX/LX_Texture.hpp>

using namespace LX_Random;
using namespace LX_Physics;


namespace LX_ParticleEngine
{

const int DELAY = 16;
const LX_Vector2D V0{0.0f, 0.0f};

/* LX_Particle — private implementation */

class LX_Particle_
{
    LX_AABB _box;                       /* The box of the particle                 */
    unsigned int _lifetime;             /* The delay to stay displayable           */
    LX_Physics::LX_Vector2D _velocity;  /* The velocity of the particle            */
    LX_Graphics::LX_Sprite& _texture;   /* The texture (for the texture rendering) */

public:

    LX_Particle_(LX_Graphics::LX_Sprite& sp, const LX_AABB& b,
                 const LX_Physics::LX_Vector2D& v) noexcept
        : _box(b), _lifetime(xorshiftRand()%DELAY), _velocity(v), _texture(sp) {}

    void update() noexcept
    {
        if(_lifetime > 0)
        {
            LX_Physics::moveRect(_box, _velocity);
            _lifetime--;
        }
    }

    void draw() noexcept
    {
        _texture.draw(&_box);
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

LX_Particle::LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_AABB& b) noexcept
    : _pimpl(new LX_Particle_(sp, b, V0)) {}


LX_Particle::LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_AABB& b,
                         const float vx, const float vy) noexcept
    : _pimpl(new LX_Particle_(sp, b, LX_Vector2D{vx, vy})) {}


LX_Particle::LX_Particle(LX_Graphics::LX_Sprite& sp, const LX_AABB& b,
                         const LX_Physics::LX_Vector2D& v) noexcept
    : _pimpl(new LX_Particle_(sp, b, v)) {}


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
