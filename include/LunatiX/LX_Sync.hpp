#ifndef LX_SYNC_HPP_INCLUDED
#define LX_SYNC_HPP_INCLUDED

/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
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

namespace tthread
{
class mutex;
class condition_variable;
};


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

};

#endif  // LX_SYNC_HPP_INCLUDED
