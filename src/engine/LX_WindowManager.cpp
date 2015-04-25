

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


    void LX_WindowManager::init()
    {
        if(winInstance == NULL)
        {
                winInstance = new LX_WindowManager();
        }
    }


    LX_WindowManager * LX_WindowManager::getInstance()
    {
        return winInstance;
    }


    void LX_WindowManager::destroy()
    {
        delete winInstance;
    }


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

    LX_WindowManager::LX_WindowManager()
    {
        mainWindow = NULL;
        size = 0;
        nb_windows = 0;
        memset(windows,NULL,LX_NBMAX_WINDOWS);
    }


    int LX_WindowManager::addWindow(LX_Window *w)
    {
        if(w == NULL || size >= LX_NBMAX_WINDOWS)
            return -1;

        windows[size] = w;
        size++;
        nb_windows += 1;

        return 0;
    }

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

    unsigned int LX_WindowManager::nbWindow()
    {
        return nb_windows;
    }


    LX_Window * LX_WindowManager::getWindow(unsigned int id)
    {
        return (id > size ) ? NULL: windows[id];
    }


};















