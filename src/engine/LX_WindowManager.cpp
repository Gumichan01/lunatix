

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_WindowManager.cpp
*	@brief The window manager implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/


#include <cstring>

#include "LX_WindowManager.hpp"
#include "LX_Window.hpp"
#include "LX_Error.hpp"


static LX_Graphics::LX_WindowManager *winInstance = NULL;


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
*   Initialize the singleton
*
*/
void LX_WindowManager::init(void)
{
    if(winInstance == NULL)
    {
        winInstance = new LX_WindowManager();
    }
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
*/
void LX_WindowManager::destroy(void)
{
    delete winInstance;
}


/**
*   @fn LX_WindowManager::~LX_WindowManager()
*
*   Destroy all windows managed by the class
*
*/
LX_WindowManager::~LX_WindowManager()
{
    if(nb_windows != 0)
    {
        for(unsigned int i = 0;i < size; i++)
        {
            deleteWindow(i);
        }
    }
}


/**
*   @fn LX_WindowManager::LX_WindowManager()
*
*   Initialize the class
*
*/
LX_WindowManager::LX_WindowManager()
{
    size = 0;
    nb_windows = 0;
    memset(windows,0,LX_NBMAX_WINDOWS);
}


/**
*   @fn int LX_WindowManager::addWindow(LX_Window *w)
*
*   Add a window to the list
*
*   @param w The window
*
*   @return The ID of the window you added if the instance is valid
*           -1 otherwise
*
*/
int LX_WindowManager::addWindow(LX_Window *w)
{
    int id;
    if(w == NULL || size >= LX_NBMAX_WINDOWS)
        return -1;

    windows[size] = w;
    id = size;

    size++;
    nb_windows += 1;

    return id;
}


/**
*   @fn int LX_WindowManager::deleteWindow(unsigned int id)
*
*   Delete a window from the list acording to its ID
*
*   @param id The ID of the window you want to delete
*
*   @return 0 If the ID refers to a valid window, -1 otherwise
*
*/
int LX_WindowManager::deleteWindow(unsigned int id)
{
    if(id > size)
        return -1;

    if(windows[id] != NULL)
    {
        delete windows[id];

        windows[id] = NULL;
        nb_windows -= 1;

        return 0;
    }

    return -1;
}


/**
*   @fn unsigned int LX_WindowManager::nbWindow()
*
*   Count the number of opened windows
*
*   @return The number of opened windows
*
*/
unsigned int LX_WindowManager::nbWindow()
{
    return nb_windows;
}


/**
*   @fn LX_Window * LX_WindowManager::getWindow(unsigned int id)
*
*   Get a window according to its ID
*
*   @return A reference to a LX_Window instance if it exists,
*           NULL otherwise
*
*/
LX_Window * LX_WindowManager::getWindow(unsigned int id)
{
    return (id > size) ? NULL : windows[id];
}


};




