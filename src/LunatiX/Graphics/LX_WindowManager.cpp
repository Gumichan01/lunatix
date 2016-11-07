

/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_WindowManager.cpp
*    @brief The window manager implementation
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*
*/

#include <LunatiX/LX_WindowManager.hpp>
#include <LunatiX/LX_Window.hpp>

static LX_Win::LX_WindowManager *win_instance = nullptr;

/*namespace
{

}*/

namespace LX_Win
{

LX_WindowManager * getWindowManager()
{
    return LX_WindowManager::getInstance();
}


void LX_WindowManager::init()
{
    if(win_instance == nullptr)
        win_instance = new LX_WindowManager();
}


LX_WindowManager * LX_WindowManager::getInstance()
{
    return win_instance;
}


void LX_WindowManager::destroy()
{
    delete win_instance;
}


// Create the instance
LX_WindowManager::LX_WindowManager() {}

// Destroy the instance,
LX_WindowManager::~LX_WindowManager() {}


uint32_t LX_WindowManager::addWindow(LX_Window *w)
{
    const auto wend = _windows.end();
    const uint32_t no = static_cast<uint32_t>(-1);

    if(w == nullptr)
        return no;

    bool found = std::any_of(_windows.begin(), wend, [&w](const LX_Window * win)
    {
        return win->getID() == w->getID();
    });

    if(found)
        return no;

    _windows.push_back(w);
    return w->getID();
}


LX_Window * LX_WindowManager::removeWindow(const uint32_t id)
{
    LX_Window *w = nullptr;

    if(_windows.empty())
        return nullptr;

    const auto wend = _windows.end();
    auto it = std::find_if(_windows.begin(), wend, [&id](const LX_Window * win)
    {
        return win->getID() == id;
    });

    if(it != wend)
    {
        w = *it;
        _windows.erase(it);
    }

    return w;
}


std::size_t LX_WindowManager::nbWindows()
{
    return _windows.size();
}


void LX_WindowManager::updateWindows()
{
    map([](LX_Window *w){w->update();});
}


void LX_WindowManager::clearWindows()
{
    map([](LX_Window *w){w->clearWindow();});
}


LX_Window * LX_WindowManager::getWindow(uint32_t id)
{
    LX_Window *w = nullptr;
    const auto wend = _windows.end();

    auto it = std::find_if(_windows.begin(), wend, [&id](const LX_Window * win)
    {
        return win->getID() == id;
    });

    if(it != wend)
        w = (*it);

    return w;
}

};
