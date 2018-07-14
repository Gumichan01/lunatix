
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
*   @file WindowManager.cpp
*   @brief The window manager implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/WindowManager.hpp>
#include <Lunatix/Window.hpp>

#include <unordered_map>

namespace lx
{

namespace Win
{

WindowNotFoundException::WindowNotFoundException( const std::string& err )
    : _string_error( err ) {}

const char * WindowNotFoundException::what() const noexcept
{
    return _string_error.c_str();
}


/* Window implementation */

struct WinManager_ final
{
    std::unordered_map<uint32_t, Window&> windows{};
};

WindowManager& getWindowManager() noexcept
{
    return WindowManager::getInstance();
}

WindowManager::WindowManager(): m_wmpimpl( new WinManager_() ) {}

WindowManager::~WindowManager()
{
    m_wmpimpl->windows.clear();
}

WindowManager& WindowManager::getInstance() noexcept
{
    static WindowManager singleton;
    return singleton;
}


bool WindowManager::addWindow( Window& w ) noexcept
{
    m_wmpimpl->windows.insert( { w.getID(), w } );
    return true;
}


bool WindowManager::removeWindow( const uint32_t id ) noexcept
{
    auto it = m_wmpimpl->windows.find( id );

    if ( it != m_wmpimpl->windows.end() )
    {
        m_wmpimpl->windows.erase( it );
        return true;
    }

    return false;
}


std::size_t WindowManager::nbWindows() const noexcept
{
    return m_wmpimpl->windows.size();
}


void WindowManager::updateWindows() noexcept
{
    for ( auto& it : m_wmpimpl->windows )
    {
        it.second.update();
    }
}


void WindowManager::clearWindows() noexcept
{
    for ( auto& it : m_wmpimpl->windows )
    {
        it.second.clearWindow();
    }
}


Window& WindowManager::getWindow( const uint32_t id ) const
{
    auto it = m_wmpimpl->windows.find( id );

    if ( it == m_wmpimpl->windows.end() )
    {
        const std::string errstr( "Not found window with identifer: " + id );
        throw WindowNotFoundException( errstr );
    }

    return it->second;
}

}   // Win

}  // lx
