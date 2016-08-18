

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
*    @version 0.8
*
*/


#include <LunatiX/LX_WindowManager.hpp>
#include <LunatiX/LX_Window.hpp>

static LX_Win::LX_WindowManager *win_instance = nullptr;

namespace LX_Win
{

LX_WindowManager * getWindowManager()
{
    return LX_WindowManager::getInstance();
}


void LX_WindowManager::init(void)
{
    if(win_instance == nullptr)
        win_instance = new LX_WindowManager();
}


LX_WindowManager * LX_WindowManager::getInstance()
{
    return win_instance;
}


void LX_WindowManager::destroy(void)
{
    delete win_instance;
}


// Create the instance
LX_WindowManager::LX_WindowManager()
    : _size(0), _nbwin(0)
{
    _windows.fill(nullptr);
}


// Destroy the instance,
LX_WindowManager::~LX_WindowManager()
{
    // Emty
}


int LX_WindowManager::addWindow(LX_Window *w)
{
    int id;
    if(w == nullptr || _size >= _LX_NBMAX_WINDOWS)
        return -1;

    _windows[_size] = w;
    id = static_cast<int>(_size);

    _size++;
    _nbwin += 1;

    return id;
}


LX_Window * LX_WindowManager::removeWindow(unsigned int id)
{
    LX_Window *w = nullptr;

    if(id > _size || _windows[id] == nullptr)
        return nullptr;

    w = _windows[id];
    _windows[id] = nullptr;
    _nbwin -= 1;

    return w;
}


unsigned int LX_WindowManager::nbWindows(void)
{
    return _nbwin;
}


void LX_WindowManager::updateWindows()
{
    for(unsigned int i = 0; i < _nbwin; i++)
    {
        if(_windows[i] != nullptr)
            _windows[i]->update();
    }
}


void LX_WindowManager::clearWindows()
{
    for(unsigned int i = 0; i < _nbwin; i++)
    {
        if(_windows[i] != nullptr)
            _windows[i]->clearWindow();
    }
}


LX_Window * LX_WindowManager::getWindow(unsigned int id)
{
    return (id > _size) ? nullptr : _windows[id];
}

};
