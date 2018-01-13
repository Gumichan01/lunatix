
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

#ifndef LX_SYNC_HPP_INCLUDED
#define LX_SYNC_HPP_INCLUDED

/**
*   @file LX_Sync.hpp
*   @brief The thread synchronization API
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/


#include <thread>
#include <mutex>
#include <condition_variable>


namespace LX_Multithreading
{

class LX_Semaphore
{
    std::mutex _mutex;
    std::condition_variable _cond;
    unsigned long _count;

    LX_Semaphore(const LX_Semaphore&) = delete;
    LX_Semaphore(const LX_Semaphore&&) = delete;
    LX_Semaphore& operator =(const LX_Semaphore&) = delete;
    LX_Semaphore&& operator =(const LX_Semaphore&&) = delete;

private:

    LX_Semaphore(unsigned long value = 0);

    void wait();
    void notify();

    ~LX_Semaphore() = default;
};

}

#endif  // LX_SYNC_HPP_INCLUDED
