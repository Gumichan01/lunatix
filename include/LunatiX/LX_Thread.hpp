#ifndef LX_THREAD_HPP_INCLUDED
#define LX_THREAD_HPP_INCLUDED

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
*    @file LX_Thread.hpp
*    @brief The multithreading API
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <memory>

class LX_Thread_;

/**
*   @namespace LX_Multithreading
*   @brief The Multithreading module
*/
namespace LX_Multithreading
{

/// Data used in argument in the function executed by the thread
using LX_Data = void *;

/// Signature of the function executed by the thread
typedef void (* LX_ThreadFun) (void *data);

/**
*   @fn unsigned long getID();
*   The the id of the current thread
*   @return The thread identifier of the current thread
*/
unsigned long getID();

/**
*   @class LX_Thread
*   @brief The thread
*/
class LX_Thread
{
    std::unique_ptr<LX_Thread_> _th;

    LX_Thread(const LX_Thread& m);
    LX_Thread& operator=(const LX_Thread& m);

public:

    /**
    *   @fn LX_Thread(LX_ThreadFun fun, const std::string& name, LX_Multithreading::LX_Data data)
    *   @brief Constructor
    *
    *   @param [in] fun The function launched by the thread
    *   @param [in] name The name of the thread
    *   @param [in] data argument of the function (fun)
    *
    *   @exception std::invalid_argument If the function given in argument is not defined
    */
    LX_Thread(LX_ThreadFun fun, const std::string& name, LX_Multithreading::LX_Data data);

    /**
    *   @fn void start()
    *
    *   Start the thread
    *
    *   @note This function does nothing if the thread is already running
    *   @sa startAndDetach
    *   @sa join
    */
    void start();
    /**
    *   @fn void startAndDetach()
    *
    *   Start the thread and detach it
    *
    *   @sa start
    */
    void startAndDetach();
    /**
    *   @fn bool joinable() const
    *
    *   Check if the thread is joinable (not joined and not detached)
    *
    *   @return TRUE if the thread is joinable, false otherwise
    *   @sa join
    */
    bool joinable() const;
    /**
    *   @fn void join()
    *
    *   Wait for the thread to terminate
    *
    *   @exception std::invalid_argument If the thread is not joinable (joined or detached)
    *   @sa joinable
    */
    void join();

    /**
    *   @fn const std::string& getName() const
    *
    *   Get the name of the thread
    *
    *   @return The name of the thread
    *   @sa LX_Multithreading::getID
    */
    const std::string& getName() const;

    /// Destructor
    ~LX_Thread();
};

};


#endif  // LX_THREAD_HPP_INCLUDED
