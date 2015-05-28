

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

#include<new>
#include <cstring>

#include "LX_WindowManager.hpp"
#include "LX_ParticleSystem.hpp"
#include "LX_Particle.hpp"
#include "LX_Error.hpp"

using namespace std;
using namespace LX_Graphics;



LX_ParticleSystem::LX_ParticleSystem(unsigned int nbPart)
{
    init(nbPart,0);
}


LX_ParticleSystem::LX_ParticleSystem(unsigned int nbPart,unsigned int id)
{
    init(nbPart,id);
}



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
        nbParticles = nbPart;
        memset(particles,0,sizeof(LX_Particle*)*nbParticles);
    }
}



bool LX_ParticleSystem::addParticle(LX_Particle *p)
{
    bool done = false;
    const unsigned int n = nbParticles;

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


bool LX_ParticleSystem::rmParticle(unsigned int id)
{
    if(id > nbParticles || particles[id] == NULL)
        return false;

    delete particles[id];
    particles[id] = NULL;
    return true;
}


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




