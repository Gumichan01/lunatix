

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
*	@file LX_window.cpp
*	@brief The LX_window class
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date August 14th, 2014
*
*
*
*/

#include "LX_window.h"


/**
*   @fn LX_window * LX_window::getInstance()
*
*   Get the unique instance of the LX_window class
*
*   @return the instance of LX_window
*
*/
LX_window * LX_window::getInstance()
{
    static LX_window *instance = NULL;

    if(instance == NULL)
    {
        try
        {
            instance = new LX_window();
        }
        catch(std::exception & ex)
        {
            std::cerr << "exception occured : " << ex.what() << std::endl;
            return NULL;
        }
    }

    return instance;
}


/**
*
*   @fn SDL_Surface * LX_window::getWindow()
*
*   Get the window
*
*/
SDL_Surface * LX_window::getWindow()
{
    return window;
}



/**
*   @fn int LX_window::getWidth()
*
*   Return the width of the current window
*
*   @return the width
*
*/
int LX_window::getWidth()
{
    return LX_width;
}



/**
*   @fn int LX_window::getHeight()
*
*   Return the height of the current window
*
*   @return the height
*
*/
int LX_window::getHeight()
{
    return LX_height;
}











