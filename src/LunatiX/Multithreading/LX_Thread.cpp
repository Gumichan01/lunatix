
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

#include <LunatiX/LX_Thread.hpp>
#include <SDL2/SDL_thread.h>

#include <functional>


namespace
{

using LX_ThreadFun_ = int(void *);

class LX_Thread_
{
    std::function<LX_ThreadFun_> _f;
    bool _joinable;                 // TRUE at construction
    SDL_Thread * _thread;           // nullptr before SDL_CreateThread

public:

    LX_Thread_(const std::function<LX_ThreadFun_>& f, std::string name); // exception : invalid_argument, system_error

    void start();
    bool joinable();        // TRUE si ni detach() ni join() a été appelé
    void join();            // invalid_argument if the thread is not joinable
    void detach();          // invalid_argument if the thread is not joinable

    unsigned long getID() const;
    std::string getName() const;

    ~LX_Thread_();
};

};




namespace LX_Multithreading
{




};
