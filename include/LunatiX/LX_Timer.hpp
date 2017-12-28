
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_TIMER_HPP_INCLUDED
#define LX_TIMER_HPP_INCLUDED

/**
*   @file LX_Timer.hpp
*   @brief The timer interface
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <SDL2/SDL_timer.h>

/**
*   @ingroup System
*   @namespace LX_Timer
*   @brief Very simple namespace for handling time
*
*/
namespace LX_Timer
{
/// Get the number of milliseconds since the initialization of the engine
inline uint32_t getTicks()
{
    return SDL_GetTicks();
}

/// Wait for a certain number of milliseconds before returning
inline void delay(uint32_t ms)
{
    SDL_Delay(ms);
}

}

#endif // LX_TIMER_HPP_INCLUDED
