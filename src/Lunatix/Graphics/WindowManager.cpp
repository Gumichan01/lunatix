
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


namespace LX_Win
{

LX_WindowNotFoundException::LX_WindowNotFoundException( const std::string& err )
    : _string_error( err ) {}

const char * LX_WindowNotFoundException::what() const noexcept
{
    return _string_error.c_str();
}


/* LX_Window implementation */

struct LX_WM_ final
{
    std::unordered_map<uint32_t, LX_Win::LX_Window&> windows{};
};

LX_WindowManager& getWindowManager() noexcept
{
    return LX_WindowManager::getInstance();
}

LX_WindowManager::LX_WindowManager(): _wmpimpl( new LX_WM_() ) {}

LX_WindowManager::~LX_WindowManager()
{
    _wmpimpl->windows.clear();
}

LX_WindowManager& LX_WindowManager::getInstance() noexcept
{
    static LX_WindowManager singleton;
    return singleton;
}


bool LX_WindowManager::addWindow( LX_Window& w ) noexcept
{
    _wmpimpl->windows.insert( {w.getID(), w} );
    return true;
}


bool LX_WindowManager::removeWindow( const uint32_t id ) noexcept
{
    auto it = _wmpimpl->windows.find( id );

    if ( it != _wmpimpl->windows.end() )
    {
        _wmpimpl->windows.erase( it );
        return true;
    }

    return false;
}


std::size_t LX_WindowManager::nbWindows() const noexcept
{
    return _wmpimpl->windows.size();
}


void LX_WindowManager::updateWindows() noexcept
{
    for ( auto& it : _wmpimpl->windows )
    {
        it.second.update();
    }
}


void LX_WindowManager::clearWindows() noexcept
{
    for ( auto& it : _wmpimpl->windows )
    {
        it.second.clearWindow();
    }
}


LX_Window& LX_WindowManager::getWindow( const uint32_t id ) const
{
    auto it = _wmpimpl->windows.find( id );

    if ( it == _wmpimpl->windows.end() )
    {
        const std::string errstr( "Not found window with identifer: " + id );
        throw LX_WindowNotFoundException( errstr );
    }

    return it->second;
}

}
