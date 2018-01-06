
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

#ifndef LX_THREAD_HPP_INCLUDED
#define LX_THREAD_HPP_INCLUDED

/**
*   @file LX_Thread.hpp
*   @brief The multithreading API
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <thread>


/**
    @ingroup Multithread
*   @namespace LX_Multithreading
*   @brief The Multithreading namespace
*
*   It handles multithreading and threadsynchronization primitives
*   (mutexes, condition variables, channels)
*/
namespace LX_Multithreading
{

/**
*   @fn size_t getCurrentThreadID() noexcept
*   The the id of the current thread
*   @return The thread identifier of the current thread
*/
size_t getCurrentThreadID() noexcept;

/**
*   @class LX_Thread
*   @brief The thread
*/
class LX_Thread
{

    std::thread thread;

    LX_Thread() = delete;
    LX_Thread(const LX_Thread&) = delete;
    LX_Thread& operator =(const LX_Thread&) = delete;

public:
    /*
    *   @todo Thread with variadic template
    *   @fn template <class LX_Fun, class... LX_Args> LX_Thread(bool detach, LX_Fun fun, const std::string& name, LX_Args args);
    *   @brief Constructor
    *
    *   @param [in] detach It specifies if the thread must be detached
    *   @param [in] fun The function launched by the thread
    *   @param [in] args arguments of the function
    *
    *   @exception std::invalid_argument If the function given in argument is not defined
    */
    template <class LX_Fun, class... LX_Args >
    LX_Thread(bool detach, LX_Fun&& fun, LX_Args&&... args);

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
    *   @fn size_t getD() noexcept
    *   The the id of the thread
    *   @return The thread identifier of the thread
    */
    size_t getID() noexcept;

    /// Destructor
    ~LX_Thread() = default;
};

#include "LX_Thread.tpp"

}

#endif  // LX_THREAD_HPP_INCLUDED
