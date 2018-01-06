
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
*   @brief The thread synchroization API
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/


#include <thread>
#include <mutex>
#include <condition_variable>


namespace LX_Multithreading
{

/**
*   @class LX_Mutex
*   @brief The mutex
*/
class LX_Mutex
{
    friend class LX_Cond;
    std::mutex _lock;
    std::unique_lock<std::mutex> _mutex;

    LX_Mutex(const LX_Mutex& m) = delete;
    LX_Mutex(const LX_Mutex&& m) = delete;
    LX_Mutex& operator =(const LX_Mutex& m) = delete;
    LX_Mutex&& operator =(const LX_Mutex&& m) = delete;

public:

    /// Constructor
    LX_Mutex();
    /**
    *   @fn void lock()
    *   Take the mutex (lock)
    */
    void lock();
    /**
    *   @fn void unlock()
    *   Release the mutex (unlock)
    */
    void unlock();
    /**
    *   @fn ~LX_Mutex() = default
    *   @brief Destructor
    *
    *   @note If a thread owns the mutex, tit is automatically unlocked
    */
    ~LX_Mutex() = default;
};


/**
*   @class LX_Cond
*   @brief The condition variable
*/
class LX_Cond
{
    std::condition_variable _cond;

    LX_Cond(const LX_Cond& c) = delete;
    LX_Cond(const LX_Cond&& c) = delete;
    LX_Cond& operator =(const LX_Cond& c) = delete;
    LX_Cond&& operator =(const LX_Cond&& c) = delete;

public:

    /// Constructor
    LX_Cond();
    /**
    *   @fn void wait(LX_Mutex& mutex)
    *
    *   Wait on the current condition variable
    *
    *   @param [in] mutex The mutex to associate the condition variable with.
    *
    *   @note 1 - The mutex given in argument must be locked.
    *        Otherwise the behaviour is undefined.
    *   @note 2 - This function atomically releases the mutex in argument
    *        and cause the calling thread to block on the current condition variable;
    *        atomically here means
    *        "atomically with respect to access by another thread to the mutex and then the condition variable".
    *        That is, if another thread is able to acquire the mutex
    *        after the about-to-block thread has released it,
    *        then a subsequent call to broadcast() or signal()
    *        in that thread shall behave as if it were issued
    *        after the about-to-block thread has blocked.
    *   @note 3 - The effect os using more than one mutex for concurrent
    *        signal() or broadcat() operations on the same condition variable is undefined.
    *        Because the condition variable is bound to a unique mutex when
    *        a thread waits on this condition variable, and this binding ends
    *        when the wait "returns"
    *
    *   @sa signal
    *   @sa broadcast
    */
    void wait(LX_Mutex& mutex);
    /**
    *   @fn void signal()
    *
    *   Unblock a thread taht is blocked on the current condition variable
    *
    *   @note 1 - If more than one thread is blocked on the condition variable
    *        the scheduling policy shall determine which thread is unblocked
    *   @note 2 - The function does nothing if no threads are blocked
    *        on the condition variable
    *
    *   @sa broadcast
    */
    void signal();
    /**
    *   @fn void broadcast()
    *
    *   Unblock all threads that are blocked on the current condition variable
    *
    *   @note 1 - If more than one thread is blocked on the condition variable
    *        the scheduling policy shall determine the order in
    *        which thread is unblocked.
    *   @note 2 - The function does nothing if no threads are blocked
    *        on the condition variable
    *
    *   @sa signal
    */
    void broadcast();
    /// Destructor
    ~LX_Cond() = default;
};

}

#endif  // LX_SYNC_HPP_INCLUDED
