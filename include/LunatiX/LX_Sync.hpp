
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
#include <atomic>
#include <mutex>
#include <condition_variable>



namespace LX_Multithreading
{

class LX_Mutex
{
    const static int IDLE = -1;
    constexpr static int MAX_LEVEL = 1000;
    constexpr static size_t MOD = static_cast<size_t>(MAX_LEVEL) + 1U;
    constexpr static int SIZE = MAX_LEVEL;
    std::atomic<int> level[SIZE];
    std::atomic<int> victim[SIZE - 1];

    LX_Mutex(const LX_Mutex&)  = delete;
    LX_Mutex(const LX_Mutex&&) = delete;
    LX_Mutex& operator =(const LX_Mutex&)  = delete;
    LX_Mutex& operator =(const LX_Mutex&&) = delete;

    bool _sameOrHigher(int me, int my_level) noexcept;

public:

    LX_Mutex() = default;
    void lock() noexcept;
    void unlock() noexcept;
    ~LX_Mutex() = default;

};

/**
*   @class LX_Semaphore
*   @brief Semaphore
*/
class LX_Semaphore
{
    std::mutex _mutex;
    std::condition_variable _cond;
    volatile unsigned long _count;

    LX_Semaphore(const LX_Semaphore&)  = delete;
    LX_Semaphore(const LX_Semaphore&&) = delete;
    LX_Semaphore& operator =(const LX_Semaphore&)  = delete;
    LX_Semaphore& operator =(const LX_Semaphore&&) = delete;

public:

    /**
    *   @fn LX_Semaphore(unsigned long value = 0)
    *   @param value
    */
    LX_Semaphore(unsigned long value = 0);

    /// Decrement the counter, if > 0, block otherwise
    void wait();
    /// Increment the counter, and awake a blocked thread
    void notify();

    ~LX_Semaphore() = default;
};

}

#endif  // LX_SYNC_HPP_INCLUDED
