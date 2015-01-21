#ifndef LX_WINDOWMANAGER_H_INCLUDED
#define LX_WINDOWMANAGER_H_INCLUDED



/*
*
*	Copyright (C)  Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*
*/

/**
*	@file LX_windowManager.h
*	@brief This file will contain a structure which contain different windows
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date January 18 th, 2015
*
*
*
*/


#include<vector>
#include<SDL2/SDL.h>

#include "LX_window.h"


/**
*   @struct LX_windowManager
*   @brief The structure that contians all windows
*
*   This structure, internally used by the LX_graphics module, gathers all windows created by the user
*
*   @note it is possible to do not let the LX_graphics manage the windows by handle the widows yourself
*           but it should be better to let it do that.
*
*/
class LX_windowManager{

    public :

    LX_window *mainWindow;                      /**< The main window*/
    std::vector<LX_window *> vectorWindows;    /**< The vector of other windows*/


    /*void clean_up()
    {
        delete mainWindow;
        mainWindow = NULL;

        if(vectorWindows != NULL)
        {
            for(std::vector<LX_window *>::size_type i = 0; i < vectorWindows->size(); i++)
            {
                delete vectorWindows->at(i);
                //vectorWindows[i] = NULL;
            }

            vectorWindows->clear();
            delete vectorWindows;
        }


    }*/
};




#endif // LX_WINDOWMANAGER_H_INCLUDED
