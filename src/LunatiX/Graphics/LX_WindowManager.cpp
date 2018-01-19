

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
#include <list>


namespace LX_Win
{

// Lit of windows
std::list<LX_Win::LX_Window*> _windows;

LX_WindowManager * getWindowManager() noexcept
{
    return LX_WindowManager::getInstance();
}


LX_WindowManager * LX_WindowManager::getInstance() noexcept
{
    static LX_WindowManager *win_instance = nullptr;
    return win_instance;
}


bool LX_WindowManager::addWindow(LX_Window& w) noexcept
{
    const auto wend = _windows.cend();
    const uint32_t no = static_cast<uint32_t>(-1);

    bool found = std::any_of(_windows.cbegin(), wend, [&w](const LX_Window * win) noexcept
    {
        return win->getID() == w.getID();
    });

    if(found)
        return no;

    _windows.push_back(&w);
    return true;
}


bool LX_WindowManager::removeWindow(const uint32_t id) noexcept
{
    LX_Window *w = nullptr;

    if(_windows.empty())
        return false;

    const auto wend = _windows.end();
    auto it = std::find_if(_windows.begin(), wend, [&id](const LX_Window * win) noexcept
    {
        return win->getID() == id;
    });

    if(it != wend)
    {
        w = *it;
        _windows.erase(it);
    }

    return true;
}


std::size_t LX_WindowManager::nbWindows() const noexcept
{
    return _windows.size();
}


void LX_WindowManager::updateWindows() noexcept
{
    std::for_each(_windows.begin(), _windows.end(), [](LX_Window *w) noexcept
    {
        w->update();
    });
}


void LX_WindowManager::clearWindows() noexcept
{
    std::for_each(_windows.begin(), _windows.end(), [](LX_Window *w) noexcept
    {
        w->clearWindow();
    });
}


LX_Window * LX_WindowManager::getWindow(uint32_t id) const noexcept
{
    LX_Window *w = nullptr;
    const auto wend = _windows.cend();

    auto it = std::find_if(_windows.cbegin(), wend, [&id](const LX_Window * win) noexcept
    {
        return win->getID() == id;
    });

    if(it != wend)
        w = (*it);

    return w;
}

}
