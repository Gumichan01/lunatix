
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

/**
*   @file Time.cpp
*   @brief The implementation of the timer
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/Time.hpp>


namespace lx
{

namespace Time
{

void Timer::start() noexcept
{
    if ( m_stopped )
    {
        m_start = SDL_GetTicks();
        m_stopped = false;
    }
}

void Timer::pause() noexcept
{
    if ( !m_stopped && !m_paused )
    {
        m_pause  = getTicks();
        m_paused = true;
    }
}


void Timer::resume() noexcept
{
    if ( !m_stopped && m_paused )
    {
        m_paused = false;
        m_tradeoff += getTicks() - m_pause;
    }
}

uint32_t Timer::lap() noexcept
{
    uint32_t t = getTicks();
    stop();
    reset();
    start();
    return t;
}

uint32_t Timer::getTicks() noexcept
{
    if ( m_stopped || m_paused )
        return m_pause;

    return SDL_GetTicks() - m_start - m_tradeoff;
}

bool Timer::isStopped() noexcept
{
    return m_stopped;
}

bool Timer::isPaused() noexcept
{
    return m_paused;
}

void Timer::stop() noexcept
{
    pause();
    m_stopped = true;
    m_paused  = false;
}

void Timer::reset() noexcept
{
    m_start    = 0U;
    m_pause    = 0U;
    m_tradeoff = 0U;
    m_stopped  = true;
    m_paused   = false;
}

}   // Time

}   // lx
