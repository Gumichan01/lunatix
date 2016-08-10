#ifndef LX_THREAD_HPP_INCLUDED
#define LX_THREAD_HPP_INCLUDED

/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Thread.hpp
*	@brief The multithreading API
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>

/**
*   @namespace LX_Multithreading
*   @brief The Multithreading module
*
*   This namespace describes the multithreading module for anything
*   related to it (threads, mutexes, semaphores)
*/
namespace LX_Multithreading
{

class LX_Thread_;

using LX_Data = void *;
typedef int (* LX_ThreadFun) (void *data);

class LX_Thread
{
    LX_Thread_ *th;

public:

    LX_Thread(LX_ThreadFun fun, std::string name, LX_Multithreading::LX_Data data); // exception : invalid_argument, system_error

    void start(LX_Data data);
    bool joinable();
    void join(int& ret);
    void detach();

    unsigned long getID() const;
    std::string getName() const;

    ~LX_Thread();
};

};

#endif // LX_THREAD_HPP_INCLUDED
