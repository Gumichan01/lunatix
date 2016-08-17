
/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    The LunatiX Engine is a SDL2-based game engine.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/


#include <LunatiX/LX_Sync.hpp>
#include <LunatiX/utils/tinythread/tinythread.h>
#include <SDL2/SDL_mutex.h>


namespace LX_Multithreading
{

/* Mutex */

LX_Mutex::LX_Mutex() : _mutex(new tthread::mutex()) {}


void LX_Mutex::lock()
{
    _mutex->lock();
}


void LX_Mutex::unlock()
{
    _mutex->unlock();
}


LX_Mutex::~LX_Mutex()
{
    delete _mutex;
}


/* Condition variable */

LX_Cond::LX_Cond() : _condition(new tthread::condition_variable()) {}


void LX_Cond::wait(LX_Mutex& mutex)
{
    _condition->wait(*mutex._mutex);
}


void LX_Cond::signal()
{
    _condition->notify_one();
}


void LX_Cond::broadcast()
{
    _condition->notify_all();
}


LX_Cond::~LX_Cond()
{
    delete _condition;
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

