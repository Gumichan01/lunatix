

/*
*	Copyright (C) 2014 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_window.cpp
*	@brief The LX_window class
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date January 18th, 2015
*
*
*/

#include "LX_window.h"


/**
*   @fn void LX_window::setTitle(std::string title)
*
*   Set the title on the window sidebar
*
*   @param title : The title
*
*/
void LX_window::setTitle(std::string title)
{
    SDL_SetWindowTitle(window,title.c_str());
}


/**
*
*   @fn SDL_Renderer * LX_window::getRenderer()
*
*   Get the window renderer
*
*   @return a pointer to the renderer, NULL otherwise
*
*/
SDL_Renderer * LX_window::getRenderer()
{
    return SDL_GetRenderer(window);
}


/**
*
*   @fn SDL_Surface * LX_window::getSurface()
*
*   Get the window surface
*
*   @return a pointer to the SDL_Surface of the window, NULL otherwise
*
*/
SDL_Surface * LX_window::getSurface()
{
    return SDL_GetWindowSurface(window);
}


/**
*
*   @fn SDL_Window * LX_window::getWindow()
*
*   Get the window
*
*   @return a pointer to the SDL_Window, NULL otherwise
*
*/
SDL_Window * LX_window::getWindow()
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
    int w;
    SDL_GetWindowSize(window,&w,NULL);

    return w;
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
    int h;
    SDL_GetWindowSize(window,NULL,&h);

    return h;
}











