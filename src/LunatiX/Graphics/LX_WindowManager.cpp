

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
*   @file LX_WindowManager.cpp
*   @brief The window manager implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*
*/

#include <LunatiX/LX_WindowManager.hpp>
#include <LunatiX/LX_Window.hpp>

#include <algorithm>
#include <unordered_map>


namespace LX_Win
{

struct LX_WM_
{
std::unordered_map<uint32_t, LX_Win::LX_Window&> windows;
};

LX_WindowManager& getWindowManager() noexcept
{
    return LX_WindowManager::getInstance();
}


LX_WindowManager& LX_WindowManager::getInstance() noexcept
{
    static LX_WindowManager singleton;
    return singleton;
}


bool LX_WindowManager::addWindow(LX_Window& w) noexcept
{
    //_wmpimpl->windows.insert(&w);
    return true;
}


bool LX_WindowManager::removeWindow(const uint32_t id) noexcept
{
    /*LX_Window *w = nullptr;

    if(_wmpimpl->windows.empty())
        return false;

    const auto wend = _wmpimpl->windows.end();
    auto it = std::find_if(_wmpimpl->windows.begin(), wend, [&id](const LX_Window * win) noexcept
    {
        return win->getID() == id;
    });

    if(it != wend)
    {
        w = *it;
        _wmpimpl->windows.erase(it);
    }*/

    return true;
}


std::size_t LX_WindowManager::nbWindows() const noexcept
{
    return _wmpimpl->windows.size();
}


void LX_WindowManager::updateWindows() noexcept
{
    /*std::for_each(_wmpimpl->windows.begin(), _wmpimpl->windows.end(), [](LX_Window *w) noexcept
    {
        w->update();
    });*/
}


void LX_WindowManager::clearWindows() noexcept
{
    /*std::for_each(_wmpimpl->windows.begin(), _wmpimpl->windows.end(), [](LX_Window *w) noexcept
    {
        w->clearWindow();
    });*/
}


LX_Window * LX_WindowManager::getWindow(uint32_t id) const noexcept
{
    LX_Window *w = nullptr;
    /*const auto wend = _wmpimpl->windows.cend();

    auto it = std::find_if(_wmpimpl->windows.cbegin(), wend, [&id](const LX_Window * win) noexcept
    {
        return win->getID() == id;
    });

    if(it != wend)
        w = (*it);*/

    return w;
}

}
