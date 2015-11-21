

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
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
*	@version 0.7
*
*/


#include <LunatiX/LX_WindowManager.hpp>
#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_Error.hpp>


static LX_Graphics::LX_WindowManager *winInstance = nullptr;


namespace LX_Graphics
{


/**
*   @fn LX_WindowManager * getWindowManager()
*
*   Return an instance of the singleton LX_WindowManager
*
*   @return The unique instance of LX_WindowManager
*
*   @note This function is equivalent to LX_WindowManager::getInstance
*
*/
LX_WindowManager * getWindowManager()
{
    return LX_WindowManager::getInstance();
}


/**
*   @fn void LX_WindowManager::init(void)
*
*   Initialize the window manager
*
*/
void LX_WindowManager::init(void)
{
    if(winInstance == nullptr)
        winInstance = new LX_WindowManager();
}


/**
*   @fn LX_WindowManager * LX_WindowManager::getInstance()
*
*   Return an instance of the singleton LX_WindowManager
*
*   @return The singleton
*
*/
LX_WindowManager * LX_WindowManager::getInstance()
{
    return winInstance;
}


/**
*   @fn void LX_WindowManager::destroy(void)
*
*   Destroy the instance of the singleton
*
*   @warning    The windows contained in the window manager
*               are not destroyed. So it is necessary to keep an external
*               pointer to the windows added in the manager.
*
*/
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


/**
*   @fn int LX_WindowManager::addWindow(LX_Window *w)
*
*   Add a window to the list
*
*   @param w The window
*
*   @return The ID of the window that was added if the instance is valid
*           -1 otherwise
*
*   @sa LX_Window
*   @sa removeWindow
*/
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


/**
*   @fn LX_Window * LX_WindowManager::removeWindow(unsigned int id)
*
*   Delete a window from the list acording to its ID
*   and returns the pointer to it.
*
*   @param id The ID of the window that must be deleted
*
*   @return A valid pointer to a window if the ID refers to a valid window,
*           a null pointer otherwise
*
*   @sa addWindow
*/
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


/**
*   @fn unsigned int LX_WindowManager::nbWindows(void)
*
*   Count the number of opened windows
*
*   @return The number of opened windows
*
*/
unsigned int LX_WindowManager::nbWindows(void)
{
    return nbWin;
}


/**
*   @fn void LX_WindowManager::updateWindows()
*
*   Update the windows
*
*/
void LX_WindowManager::updateWindows()
{
    for(unsigned int i = 0; i < nbWin; i++)
    {
        if(windows[i] != nullptr)
            windows[i]->update();
    }
}


/**
*   @fn void LX_WindowManager::clearWindows()
*
*   Clear the content of the windows
*
*/
void LX_WindowManager::clearWindows()
{
    for(unsigned int i = 0; i < nbWin; i++)
    {
        if(windows[i] != nullptr)
            windows[i]->clearWindow();
    }
}


/**
*   @fn LX_Window * LX_WindowManager::getWindow(unsigned int id)
*
*   Get a window according to its ID
*
*   @return A reference to a LX_Window instance if it exists,
*           a null pointer otherwise
*
*/
LX_Window * LX_WindowManager::getWindow(unsigned int id)
{
    return (id > size) ? nullptr : windows[id];
}


};

