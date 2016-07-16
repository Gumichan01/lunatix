

/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_ParticleSystem.cpp
*	@brief The Particle system implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <new>

#include <LunatiX/LX_ParticleSystem.hpp>
#include <LunatiX/LX_Particle.hpp>

#include <LunatiX/LX_WindowManager.hpp>
#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_Error.hpp>

using namespace std;


namespace LX_ParticleEngine
{

LX_ParticleSystem::LX_ParticleSystem(const unsigned int nbPart)
    : LX_ParticleSystem(nbPart,0) {}


LX_ParticleSystem::LX_ParticleSystem(const unsigned int nbPart,const unsigned int id)
    : _particles(nullptr), _nb_particles(nbPart), _idwin(id)
{
    allocateParticles(_nb_particles);
}


LX_ParticleSystem::~LX_ParticleSystem()
{
    const unsigned int n = _nb_particles;

    for(unsigned int i = 0; i < n; i++)
    {
        delete _particles[i];
        _particles[i] = nullptr;
    }

    delete [] _particles;
}


/*
*   Allocate the particle array
*
*   This function is automatically called by one of
*   the following constructors of the particle system
*
*/
void LX_ParticleSystem::allocateParticles(unsigned int nbPart)
{
    _particles = new (nothrow) LX_Particle*[nbPart];

    if(_particles == nullptr)
    {
        LX_SetError("LX_ParticleSystem constructor: Cannot allocate the _particles\n");
        _nb_particles = 0;
    }
    else
    {
        _nb_particles = nbPart;

        for(unsigned int i = 0; i < _nb_particles; i++)
            _particles[i] = nullptr;
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
            _particles[i] = p;
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

    delete _particles[index];
    _particles[index] = nullptr;
    return true;
}


void LX_ParticleSystem::updateParticles(void)
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


void LX_ParticleSystem::displayParticles(void)
{
    const unsigned int n = _nb_particles;
    LX_Win::LX_WindowManager *wm = LX_Win::LX_WindowManager::getInstance();
    LX_Win::LX_Window * win = wm->getWindow(_idwin);

    if(win == nullptr)
        return;

    for(unsigned int i = 0; i < n ; i++)
    {
        if(_particles[i] == nullptr)
            continue;

        LX_AABB box = (_particles[i]->getAABB());

        // Display the particle when the delay is a multiple of 2
        if(_particles[i]->getDelay()%2 == 0)
        {
            if(_particles[i]->getTexture() != nullptr)
            {
                win->putTexture(_particles[i]->getTexture(),
                                nullptr,&box);
            }
            else if(_particles[i]->getSurface() != nullptr)
            {
                win->putSurface(_particles[i]->getSurface(),
                                nullptr,&box);
            }
        }
    }
}


unsigned int LX_ParticleSystem::nbEmptyParticles(void)
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


unsigned int LX_ParticleSystem::nbActiveParticles(void)
{
    return _nb_particles - nbEmptyParticles();
}


unsigned int LX_ParticleSystem::nbTotalParticles(void)
{
    return _nb_particles;
}

};
