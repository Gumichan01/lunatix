
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
#include <system_error>


namespace LX_Multithreading
{

size_t getCurrentThreadID() noexcept
{
    return std::hash<std::thread::id>()(std::this_thread::get_id());
}

// Class

bool LX_Thread::joinable() const noexcept
{
    return thread.joinable();
}

void LX_Thread::join()
{
    thread.join();
}

size_t LX_Thread::getID() noexcept
{
    return std::hash<std::thread::id>()(thread.get_id());
}

}
