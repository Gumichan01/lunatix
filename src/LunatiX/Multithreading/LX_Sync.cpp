
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

LX_Mutex::LX_Mutex() : _lock(), _mutex(_lock, std::defer_lock_t()) {}


void LX_Mutex::lock()
{
    _mutex.lock();
}


void LX_Mutex::unlock()
{
    _mutex.unlock();
}

// Condition variable
/*LX_Cond::LX_Cond() : _cond() {}


void LX_Cond::wait(LX_Mutex& mutex)
{
    _cond.wait(std::unique_lock(mutex._mutex, std::adopt_lock_t));
}


void LX_Cond::signal()
{
    _cond.notify_one();
}


void LX_Cond::broadcast()
{
    _cond.notify_all();
}*/

}
