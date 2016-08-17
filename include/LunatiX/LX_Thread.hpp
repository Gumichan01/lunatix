#ifndef LX_THREAD_HPP_INCLUDED
#define LX_THREAD_HPP_INCLUDED

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
*    @file LX_Thread.hpp
*    @brief The multithreading API
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/


#include <LunatiX/utils/utf8_string.hpp>

class LX_Thread_;

/**
*   @namespace LX_Multithreading
*   @brief The Multithreading module
*
*   This namespace describes the multithreading module for anything
*   related to it (threads, mutexes, semaphores)
*   This module is entirely based on SDL2
*
*   @note This module is not available on Windows because the multithreading
*   subsystem ,that uses the Multithread Windows API, is not stable.
*/
namespace LX_Multithreading
{

using LX_Data = void *;
typedef void (* LX_ThreadFun) (void *data);

unsigned long getID();

class LX_Thread
{
    LX_Thread_ *_th;

public:

    LX_Thread(LX_ThreadFun fun, std::string name, LX_Multithreading::LX_Data data);

    void start();
    void startAndDetach();
    bool joinable();
    void join();

    const std::string& getName() const;

    ~LX_Thread();
};

};


#endif  // LX_THREAD_HPP_INCLUDED
