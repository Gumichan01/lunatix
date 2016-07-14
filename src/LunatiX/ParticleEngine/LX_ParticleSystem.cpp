

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
    : particles(nullptr), nbParticles(nbPart), idWin(id)
{
    allocateParticles(nbParticles);
}


LX_ParticleSystem::~LX_ParticleSystem()
{
    const unsigned int n = nbParticles;

    for(unsigned int i = 0; i < n; i++)
    {
        delete particles[i];
        particles[i] = nullptr;
    }

    delete [] particles;
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
    particles = new (nothrow) LX_Particle*[nbPart];

    if(particles == nullptr)
    {
        LX_SetError("LX_ParticleSystem constructor: Cannot allocate the particles\n");
        nbParticles = 0;
    }
    else
    {
        nbParticles = nbPart;

        for(unsigned int i = 0; i < nbParticles; i++)
            particles[i] = nullptr;
    }
}


bool LX_ParticleSystem::addParticle(LX_Particle *p)
{
    bool done = false;
    const unsigned int n = nbParticles;

    if(p == nullptr)
        return false;

    for(unsigned int i = 0; i < n; i++)
    {
        if(particles[i] == nullptr)
        {
            particles[i] = p;
            done = true;
            break;
        }
    }

    return done;
}


bool LX_ParticleSystem::rmParticle(unsigned int index)
{
    if(index > nbParticles || particles[index] == nullptr)
        return false;

    delete particles[index];
    particles[index] = nullptr;
    return true;
}


void LX_ParticleSystem::updateParticles(void)
{
    const unsigned int n = nbParticles;

    for(unsigned int i = 0; i < n; i++)
    {
        if(particles[i] != nullptr)
        {
            if(particles[i]->isDead())
                rmParticle(i);
            else
                particles[i]->update();
        }
    }
}


void LX_ParticleSystem::displayParticles(void)
{
    const unsigned int n = nbParticles;
    LX_Win::LX_WindowManager *wm = LX_Win::LX_WindowManager::getInstance();
    LX_Win::LX_Window * win = wm->getWindow(idWin);

    if(win == nullptr)
        return;

    for(unsigned int i = 0; i < n ; i++)
    {
        if(particles[i] == nullptr)
            continue;

        LX_AABB box = (particles[i]->getAABB());

        // Display the particle when the delay is a multiple of 2
        if(particles[i]->getDelay()%2 == 0)
        {
            if(particles[i]->getTexture() != nullptr)
            {
                win->putTexture(particles[i]->getTexture(),
                                nullptr,&box);
            }
            else if(particles[i]->getSurface() != nullptr)
            {
                win->putSurface(particles[i]->getSurface(),
                                nullptr,&box);
            }
        }
    }
}


unsigned int LX_ParticleSystem::nbEmptyParticles(void)
{
    const unsigned int n = nbParticles;
    unsigned int nb = 0;

    for(unsigned int i = 0; i < n; i++)
    {
        if(particles[i] == nullptr)
            nb++;
    }

    return nb;
}


unsigned int LX_ParticleSystem::nbActiveParticles(void)
{
    return nbParticles - nbEmptyParticles();
}


unsigned int LX_ParticleSystem::nbTotalParticles(void)
{
    return nbParticles;
}

};

