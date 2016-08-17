#ifndef LX_SYNC_HPP_INCLUDED
#define LX_SYNC_HPP_INCLUDED

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

/**
*    @file LX_Sync.hpp
*    @brief The thread synchroization API
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

//#ifdef __linux__

namespace tthread
{
class mutex;
class condition_variable;
};

/*struct SDL_mutex;
struct SDL_cond;*/
struct SDL_semaphore;

namespace LX_Multithreading
{

class LX_Mutex
{
    friend class LX_Cond;
    tthread::mutex * _mutex;

public:

    LX_Mutex();
    void lock();
    void unlock();
    ~LX_Mutex();
};


class LX_Cond
{
    tthread::condition_variable * _condition;

public:

    LX_Cond();
    void wait(LX_Mutex& mutex);
    void signal();
    void broadcast();
    ~LX_Cond();
};


class LX_Semaphore
{
    SDL_semaphore * _sem;

public:

    LX_Semaphore(unsigned int v);
    void wait();
    void post();
    ~LX_Semaphore();
};

};

//#else
//#pragma message("LunatiX: No thread synchronization primitives support for Windows")
//#endif  // __linux__

#endif  // LX_SYNC_HPP_INCLUDED
