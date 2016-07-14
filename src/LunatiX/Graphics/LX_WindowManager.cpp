

/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_WindowManager.cpp
*	@brief The window manager implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/


#include <LunatiX/LX_WindowManager.hpp>
#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_Error.hpp>

static LX_Win::LX_WindowManager *winInstance = nullptr;

namespace LX_Win
{

LX_WindowManager * getWindowManager()
{
    return LX_WindowManager::getInstance();
}


void LX_WindowManager::init(void)
{
    if(winInstance == nullptr)
        winInstance = new LX_WindowManager();
}


LX_WindowManager * LX_WindowManager::getInstance()
{
    return winInstance;
}


void LX_WindowManager::destroy(void)
{
    delete winInstance;
}


// Create the instance
LX_WindowManager::LX_WindowManager()
    : size(0), nbWin(0)
{
    windows.fill(nullptr);
}


// Destroy the instance,
LX_WindowManager::~LX_WindowManager()
{
    // Emty
}


int LX_WindowManager::addWindow(LX_Window *w)
{
    int id;
    if(w == nullptr || size >= LX_NBMAX_WINDOWS)
        return -1;

    windows[size] = w;
    id = static_cast<int>(size);

    size++;
    nbWin += 1;

    return id;
}


LX_Window * LX_WindowManager::removeWindow(unsigned int id)
{
    LX_Window *w = nullptr;

    if(id > size || windows[id] == nullptr)
        return nullptr;

    w = windows[id];
    windows[id] = nullptr;
    nbWin -= 1;

    return w;
}


unsigned int LX_WindowManager::nbWindows(void)
{
    return nbWin;
}


void LX_WindowManager::updateWindows()
{
    for(unsigned int i = 0; i < nbWin; i++)
    {
        if(windows[i] != nullptr)
            windows[i]->update();
    }
}


void LX_WindowManager::clearWindows()
{
    for(unsigned int i = 0; i < nbWin; i++)
    {
        if(windows[i] != nullptr)
            windows[i]->clearWindow();
    }
}


LX_Window * LX_WindowManager::getWindow(unsigned int id)
{
    return (id > size) ? nullptr : windows[id];
}

};
