

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

#include <LunatiX/LX_WindowManager.hpp>
#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_ParticleSystem.hpp>
#include <LunatiX/LX_Particle.hpp>
#include <LunatiX/LX_Error.hpp>

using namespace std;
//using namespace LX_Graphics;


namespace LX_ParticleEngine
{


/**
*   @fn LX_ParticleSystem::LX_ParticleSystem(const unsigned int nbPart)
*
*   Create the instance with a number of particles
*
*   @param nbPart The number of particles to define in the system
*
*/
LX_ParticleSystem::LX_ParticleSystem(const unsigned int nbPart)
    : LX_ParticleSystem(nbPart,0)

{
    // Empty
}


/**
*   @fn LX_ParticleSystem::LX_ParticleSystem(const unsigned int nbPart,const unsigned int id)
*
*   Create the instance with a number of particles and the id of the window
*
*   @param  nbPart The number of particles to define in the system
*   @param  id The id of the window in the LX_WindowManager
*           to get the rendeering context
*
*/
LX_ParticleSystem::LX_ParticleSystem(const unsigned int nbPart,const unsigned int id)
    : particles(nullptr), nbParticles(nbPart), idWin(id)
{
    allocateParticles(nbParticles);
}


/**
*   @fn LX_ParticleSystem::~LX_ParticleSystem()
*
*   Destroy the instance cleaning up the particles
*
*/
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


/**
*   @fn bool LX_ParticleSystem::addParticle(LX_Particle *p)
*
*   Add a particle into the particle system
*
*   @param p The particle to add
*
*   @return TRUE if the system had the particle with succes.
*           FALSE if the particle is a null pointer or the system cannot add it
*
*/
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


/**
*   @fn bool LX_ParticleSystem::rmParticle(unsigned int index)
*
*   Destroy a particle from the particle system according to its index
*
*   @param index the index of the particle in the list
*
*   @return TRUE if the system found the particle and destroyed it.
*           FALSE if the index is invalid
*
*/
bool LX_ParticleSystem::rmParticle(unsigned int index)
{
    if(index > nbParticles || particles[index] == nullptr)
        return false;

    delete particles[index];
    particles[index] = nullptr;
    return true;
}


/**
*   @fn void LX_ParticleSystem::updateParticles(void)
*
*   Update the particles
*
*/
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


/**
*   @fn void LX_ParticleSystem::displayParticles(void)
*
*   Display the particles
*
*/
void LX_ParticleSystem::displayParticles(void)
{
    const unsigned int n = nbParticles;

    LX_Win::LX_Window * win = LX_Win::LX_WindowManager::getInstance()->getWindow(idWin);

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


/**
*   @fn unsigned int LX_ParticleSystem::nbEmptyParticles(void)
*
*   Get the number of empty slots to set particles
*
*   @return The number of available slots of the particle system
*
*/
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


/**
*   @fn unsigned int LX_ParticleSystem::nbActiveParticles(void)
*
*   Get the number of initialized particles
*
*   @return The number of particles that are not null of the system
*
*/
unsigned int LX_ParticleSystem::nbActiveParticles(void)
{
    return nbParticles - nbEmptyParticles();
}


/**
*   @fn unsigned int LX_ParticleSystem::nbTotalParticles(void)
*
*   Get the maximum number of particles
*
*   @return The total number of particles the current particle system can have
*
*/
unsigned int LX_ParticleSystem::nbTotalParticles(void)
{
    return nbParticles;
}

};

