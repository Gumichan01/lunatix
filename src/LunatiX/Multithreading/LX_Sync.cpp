
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

#include <LunatiX/LX_Sync.hpp>
#include <LunatiX/LX_Thread.hpp>
#include <functional>


namespace LX_Multithreading
{

/*
    This code uses the filter algorithme,
    an extended version of Peterson's algorithm
*/
void LX_Mutex::lock() noexcept
{
    int me = static_cast<int>(getCurrentThreadID() % MOD);

    for(int i = 1; i < SIZE - 1; ++i)
    {
        level[me] = i;
        victim[i] = me;
        while(_sameOrHigher(me, i) && victim[i] == me);
    }

    level[me] = SIZE - 1;
}

bool LX_Mutex::_sameOrHigher(int me, int my_level) noexcept
{
    for(int id = 0; id < SIZE; id += 1)
    {
        if(id != me && level[id] >= my_level)
            return true;
    }

    return false;
}

void LX_Mutex::unlock() noexcept
{
    level[static_cast<int>(getCurrentThreadID() % MOD)] = IDLE;
}

LX_Semaphore::LX_Semaphore(unsigned long value)
    : _mutex(), _cond(), _count(value) {}

void LX_Semaphore::wait()
{
    std::unique_lock<std::mutex> lock(_mutex);
    _cond.wait(lock, [this] { return _count > 0UL;});

    if(_count > 0UL)
        --_count;
}

void LX_Semaphore::notify()
{
    std::unique_lock<std::mutex> lock(_mutex);
    ++_count;
    _cond.notify_one();
}

}
