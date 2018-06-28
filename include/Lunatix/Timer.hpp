
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

#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED

/**
*   @file Timer.hpp
*   @brief The timer interface
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <SDL2/SDL_timer.h>

/**
*   @ingroup System
*   @namespace lx::Time
*   @brief Very simple namespace for handling time
*
*/
namespace lx
{

namespace Time
{
/**
*   @fn inline uint32_t getTicks()
*   Get the number of milliseconds since the initialization of the engine
*   @return The tick
*/
inline uint32_t getTicks()
{
    return SDL_GetTicks();
}
/**
*   @fn inline void delay(uint32_t ms)
*   Wait for a certain number of milliseconds before returning
*   @param ms The delay
*/
inline void delay( uint32_t ms )
{
    SDL_Delay( ms );
}

}   //Time

}   // lx

#endif // TIMER_HPP_INCLUDED
