
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
#include <functional>


namespace LX_Multithreading
{

LX_Semaphore::LX_Semaphore(unsigned long value)
    : _mutex(), _cond(), _count(value) {}

void LX_Semaphore::wait()
{
    std::unique_lock<std::mutex> lock(_mutex);
    _cond.wait(lock, [this] { return _count != 0;});
    --_count;
}

void LX_Semaphore::notify()
{
    std::unique_lock<std::mutex> lock(_mutex);
    ++_count;
    _cond.notify_one();
}

}
