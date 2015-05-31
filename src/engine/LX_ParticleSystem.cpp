

/*
*	Copyright (C)  Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*
*/

/**
*	@file LX_ParticleSystem.cpp
*	@brief The Particle system implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include <new>
#include <cstring>

#include "LX_WindowManager.hpp"
#include "LX_Window.hpp"
#include "LX_ParticleSystem.hpp"
#include "LX_Particle.hpp"
#include "LX_Error.hpp"

using namespace std;
using namespace LX_Graphics;


/**
*   @fn LX_ParticleSystem::LX_ParticleSystem(unsigned int nbPart)
*
*   Create the instance with a number of particles
*
*   @param nbPart The number of particles you want to get
*
*/
LX_ParticleSystem::LX_ParticleSystem(unsigned int nbPart)
{
    init(nbPart,0);
}


/**
*   @fn LX_ParticleSystem::LX_ParticleSystem(unsigned int nbPart,unsigned int id)
*
*   Create the instance with a number of particles and the id of the window
*
*   @param nbPart The number of particles you want to get
*   @param id The id of the window in the LX_WindowManager
*
*/
LX_ParticleSystem::LX_ParticleSystem(unsigned int nbPart,unsigned int id)
{
    init(nbPart,id);
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
        if(particles[i] != NULL)
        {
            delete particles[i];
            particles[i] = NULL;
        }
    }

    delete [] particles;
}


/**
*   @fn void LX_ParticleSystem::init(unsigned int nbPart,unsigned int id)
*
*   Initialize the particle system
*
*   @param nbPart The number of particles you want to get
*   @param id The id of the window in the @link LX_WindowManager window manager @endlink
*
*   @note This function is automatically called by one of the following constructors
*           of the particle system
*
*/
void LX_ParticleSystem::init(unsigned int nbPart,unsigned int id)
{
    idWin = id;
    particles = new (nothrow) LX_Particle*[nbPart];

    if(particles == NULL)
    {
        LX_SetError("LX_ParticleSystem constructor: Cannot allocate the particles\n");
        nbParticles = 0;
    }
    else
    {
        LX_SetError("LX_ParticleSystem constructor: SUCCESS\n");
        nbParticles = nbPart;
        memset(particles,0,sizeof(LX_Particle*)*nbParticles);
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
*           FALSE if the particle is NULL or the system cannot add it
*
*/
bool LX_ParticleSystem::addParticle(LX_Particle *p)
{
    bool done = false;
    const unsigned int n = nbParticles;

    if(p == NULL)
        return false;

    for(unsigned int i = 0; i < n; i++)
    {
        if(particles[i] ==  NULL)
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
*   Destroy a particle the particle system according to its index
*
*   @param index the index of the particle in the list
*
*   @return TRUE if the system found the particle and destroyed it.
*           FALSE if the index is invalid
*
*/
bool LX_ParticleSystem::rmParticle(unsigned int index)
{
    if(index > nbParticles || particles[index] == NULL)
        return false;

    delete particles[index];
    particles[index] = NULL;
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
        if(particles[i] != NULL)
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

    LX_Window * win = LX_WindowManager::getInstance()->getWindow(idWin);

    if(win == NULL)
        return;

    for(unsigned int i = 0; i < n ; i++)
    {
        if(particles[i] == NULL)
            continue;

        if(particles[i]->getDelay()%2 == 0)
        {
            if(particles[i]->getTexture() != NULL)
            {
                win->putTexture(particles[i]->getTexture(),NULL,particles[i]->getAABB());
            }
            else if(particles[i]->getSurface() != NULL)
            {
                win->putSurface(particles[i]->getSurface(),NULL,particles[i]->getAABB());
            }
        }
    }
}



