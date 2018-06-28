
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

#ifndef THREAD_HPP_INCLUDED
#define THREAD_HPP_INCLUDED

/**
*   @file Thread.hpp
*   @brief The multithreading API
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <thread>
#include <future>


/**
*   @ingroup System
*   @defgroup Multithread Multithreading
*   @brief Multithreading and synchronization
*/

namespace lx
{

/**
    @ingroup Multithread
*   @namespace lx::Multithreading
*   @brief The Multithreading namespace
*
*   It handles multithreading and threadsynchronization primitives
*   (mutexes, condition variables, channels)
*/
namespace Multithreading
{

/**
*   @fn size_t getCurrentThreadID() noexcept
*   The the id of the current thread
*   @return The thread identifier of the current thread
*/
size_t getCurrentThreadID() noexcept;

/**
*   @class Thread
*   @brief The thread
*
*   Thread is a simple wrapper of std::thread
*/
class Thread final
{
    std::thread _thread;

    Thread() = delete;
    Thread( const Thread& ) = delete;
    Thread( const Thread&& ) = delete;
    Thread& operator =( const Thread& ) = delete;
    Thread&& operator =( const Thread&& ) = delete;

public:
    /**
    *   @fn template <class Fun, class... Args> Thread(bool detach, Fun&& fun, Args&&... args)
    *
    *   @param [in] detach It specifies if the thread must be detached
    *   @param [in] fun The function to launch
    *   @param [in] args arguments
    *
    *   @exception std::system_error If the thread cannot be started
    *
    *   @note Any return value from the function is ignored.
    *         If the function throws an exception, std::terminate is called.
    *         In order to pass return values or exceptions back to the calling thread,
    *         ASyncTask may be used.
    */
    template <class Fun, class... Args>
    Thread( bool detach, Fun&& fun, Args&& ... args );

    /**
    *   @fn bool joinable() const noexcept
    *
    *   Check if the thread is joinable (not joined and not detached)
    *
    *   @return true if the thread is joinable, false otherwise
    *   @sa join
    */
    bool joinable() const noexcept;
    /**
    *   @fn void join()
    *
    *   Wait for the thread to terminate
    *
    *   @exception std::system_error if one of those errors occurred:
    *               - the thread tries to join itself
    *               - the thread is not valid
    *               - the thread is not joinable
    *   @sa joinable
    */
    void join();
    /**
    *   @fn size_t getID() const noexcept
    *   @return the identifier of the thread
    */
    size_t getID() const noexcept;

    ~Thread() = default;
};

/**
*   @class ASyncTask
*   @brief Asynchronous task
*/
template <class ReturnValue>
class ASyncTask final
{
    std::future<ReturnValue> _future;

    ASyncTask() = delete;
    ASyncTask( const ASyncTask& ) = delete;
    ASyncTask( const ASyncTask&& ) = delete;
    ASyncTask& operator =( const ASyncTask& ) = delete;
    ASyncTask&& operator =( const ASyncTask&& ) = delete;

public:

    /**
    *   @fn template <class Fun, class... Args> ASyncTask(Fun&& fun, Args&&... args)
    *
    *   @param [in] fun The function launched by the thread
    *   @param [in] args arguments of the function
    *
    *   @exception std::system_error If the thread cannot be started
    */
    template <class Fun, class... Args>
    ASyncTask( Fun&& fun, Args&& ... args );

    /**
    *   @fn ReturnValue getResult()
    *
    *   @return The result, or throw an exception
    *
    *   @exception If an exception occured during the execution of the function
    *              in the asynchronous task, then this exception is thrown.
    */
    ReturnValue getResult();

    ~ASyncTask() = default;
};

#include "Thread.tpp"

}   // Multithreading

}   // lx

#endif  // THREAD_HPP_INCLUDED
