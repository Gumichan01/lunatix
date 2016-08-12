#ifndef LX_SYNC_HPP_INCLUDED
#define LX_SYNC_HPP_INCLUDED

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
*	@file LX_Sync.hpp
*	@brief The thread synchroization API
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

struct SDL_mutex;

namespace LX_Multithreading
{

class LX_Mutex
{
    SDL_mutex * _mutex;

public:

    LX_Mutex();
    void lock();
    void unlock();
    ~LX_Mutex();
};

};

#endif // LX_SYNC_HPP_INCLUDED
