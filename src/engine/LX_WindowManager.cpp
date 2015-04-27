

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_WindowManager.cpp
*	@brief The window manager
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.3
*	@date April 24th, 2015
*
*/


#include <cstring>

#include "LX_WindowManager.hpp"


static LX_Graphics::LX_WindowManager *winInstance = NULL;


namespace LX_Graphics{


    /**
    *   @fn LX_WindowManager * getWindowManager()
    *
    *   Return an instance of the singleton LX_WindowManager
    *
    *   @return the unique instance of LX_WindowManager
    *
    *   @note This function is equivalent to LX_WindowManager::getInstance.
    *           It is just a less verbose function
    *
    */
    LX_WindowManager * getWindowManager()
    {
        return LX_WindowManager::getInstance();
    }

    /**
    *   @fn void LX_WindowManager::init()
    *
    *   Initialize the instance of LX_WindowManager
    *
    */
    void LX_WindowManager::init()
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
    *   @return the unique instance of LX_WindowManager
    *
    */
    LX_WindowManager * LX_WindowManager::getInstance()
    {
        return winInstance;
    }


    /**
    *   @fn void LX_WindowManager::destroy()
    *
    *   Destroy the instance of the singleton LX_WindowManager
    *
    */
    void LX_WindowManager::destroy()
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
        unsigned int i;

        if(nb_windows != 0)
        {
            for(i = 0; nb_windows != 0 && i < size;i++)
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
        mainWindow = NULL;
        size = 0;
        nb_windows = 0;
        memset(windows,0,LX_NBMAX_WINDOWS);
    }


    /**
    *   @fn int LX_WindowManager::addWindow(LX_Window *w)
    *
    *   Add a window to the list
    *
    *   @param w the window
    *
    *   @return the id of the window if the parameter is valid and
    *           LX_WindowManager can add it, -1 otherwise
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
    *   Delete a window from the list acording to its ID number
    *
    *   @param id the id
    *
    *   @return 0 if the parameter is valid and LX_WindowManager can remove
    *           the window, -1 otherwise
    *
    */
    int LX_WindowManager::deleteWindow(unsigned int id)
    {
        if(id > size || mainWindow == NULL)
            return -1;
        else if(windows[id] != NULL)
        {
            delete windows[id];
            windows[id] = NULL;
            nb_windows -= 1;
            return 0;
        }

        return 0;
    }


    /**
    *   @fn unsigned int LX_WindowManager::nbWindow()
    *
    *   Count the number of windows
    *
    *   @return the number of active windows
    *
    */
    unsigned int LX_WindowManager::nbWindow()
    {
        return nb_windows;
    }


    /**
    *   @fn LX_Window * LX_WindowManager::getWindow(unsigned int id)
    *
    *   Get a window according to its ID number
    *
    *   @return a reference to a LX_Window instance if it exists,
    *           NULL otherwise
    *
    */
    LX_Window * LX_WindowManager::getWindow(unsigned int id)
    {
        return (id > size ) ? NULL: windows[id];
    }


};















