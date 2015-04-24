

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
        deleteWindow(0);
    }

    LX_WindowManager::LX_WindowManager()
    {
        mainWindow = NULL;
    }


    int LX_WindowManager::addWindow(LX_Window *w)
    {
        if(w == NULL)
            return -1;

        mainWindow = w;

        return 0;
    }

    int LX_WindowManager::deleteWindow(int id)
    {
        if(id != 0 || mainWindow == NULL)
            return -1;
        else
        {
            delete mainWindow;
            mainWindow = NULL;
            return 0;
        }

        return 0;
    }

    int LX_WindowManager::nbWindow()
    {
        return 0;
    }


    LX_Window * LX_WindowManager::getWindow(int id)
    {
        return (id != 0) ? NULL: mainWindow;
    }


};















