
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

#include <Lunatix/Thread.hpp>
#include <system_error>


namespace lx
{

namespace Multithreading
{

size_t getCurrentThreadID() noexcept
{
    return std::hash<std::thread::id>()( std::this_thread::get_id() );
}

bool Thread::joinable() const noexcept
{
    return m_thread.joinable();
}

void Thread::join()
{
    m_thread.join();
}

size_t Thread::getID() const noexcept
{
    return std::hash<std::thread::id>()( m_thread.get_id() );
}

}   // Multithreading

}   // lx
