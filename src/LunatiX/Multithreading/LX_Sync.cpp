
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


#include <LunatiX/LX_Sync.hpp>
#include <SDL2/SDL_mutex.h>


namespace LX_Multithreading
{

/* Mutex */

LX_Mutex::LX_Mutex() : _mutex(SDL_CreateMutex()) {}


void LX_Mutex::lock()
{
    SDL_LockMutex(_mutex);
}


void LX_Mutex::unlock()
{
    SDL_UnlockMutex(_mutex);
}


LX_Mutex::~LX_Mutex()
{
    SDL_DestroyMutex(_mutex);
}


/* Condition variable */

LX_Cond::LX_Cond() : _condition(SDL_CreateCond()) {}


void LX_Cond::wait(LX_Mutex& mutex)
{
    SDL_CondWait(_condition,mutex._mutex);
}


void LX_Cond::signal()
{
    SDL_CondSignal(_condition);
}


void LX_Cond::broadcast()
{
    SDL_CondBroadcast(_condition);
}


LX_Cond::~LX_Cond()
{
    SDL_DestroyCond(_condition);
}


/* Semaphore */

LX_Semaphore::LX_Semaphore(unsigned int v) : _sem(SDL_CreateSemaphore(v)) {}


void LX_Semaphore::wait()
{
    SDL_SemWait(_sem);
}


void LX_Semaphore::post()
{
    SDL_SemPost(_sem);
}


LX_Semaphore::~LX_Semaphore()
{
    SDL_DestroySemaphore(_sem);
}

};
