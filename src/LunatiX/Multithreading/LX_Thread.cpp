
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

#include <LunatiX/LX_Thread.hpp>
//#include <LunatiX/utils/tinythread/tinythread.h>
//#include <LunatiX/LX_Log.hpp>

#include <system_error>
//#include <functional>
//#include <stdexcept>


namespace LX_Multithreading
{

std::thread::id getCurrentThreadID() noexcept
{
    return std::this_thread::get_id();
}

// Class

template <class LX_Fun, class... LX_Args >
LX_Thread::LX_Thread(bool detach, LX_Fun&& fun, LX_Args&&... args)
: thread(fun, args...) {}


bool LX_Thread::joinable() const noexcept
{
    return thread.joinable();
}

void LX_Thread::join()
{
    thread.join();
}

std::thread::id LX_Thread::getID() noexcept
{
    return thread.get_id();
}

}
