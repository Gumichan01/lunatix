
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
*/

#include <Lunatix/Time.hpp>
#include <SDL2/SDL_timer.h>

namespace lx
{

namespace Time
{

// 1 second in millisecond
constexpr uint32_t SECOND = 1000;
// 1 minute in millisecond
constexpr uint32_t MINUTE = 60 * SECOND;
// 1 hour in millisecond
constexpr uint32_t HOUR = 60 * MINUTE;

uint32_t getTicks() noexcept
{
    return SDL_GetTicks();
}

void delay( uint32_t ms ) noexcept
{
    SDL_Delay( ms );
}

uint32_t seconds( uint32_t ms ) noexcept
{
    return ms / SECOND;
}

uint32_t minutes( uint32_t ms ) noexcept
{
    return ms / MINUTE;
}

uint32_t hours( uint32_t ms ) noexcept
{
    return ms / HOUR;
}

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

}   // Time

}   // lx
