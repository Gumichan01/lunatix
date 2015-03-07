

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Window.cpp
*	@brief The LX_Window class
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 7th, 2015
*
*
*/

#include <SDL2/SDL.h>

#include "LX_Config.h"
#include "LX_Window.h"



/**
*   @fn LX_WindowException::LX_WindowException(std::string err)
*
*   Build the LX_WindowException class
*
*   @param err the error string
*
*/
LX_WindowException::LX_WindowException(std::string err)
{
    str_err = err;
}


/**
*   @fn const char * LX_WindowException::what() const throw()
*   Get the error string
*   @return the error string
*/
const char * LX_WindowException::what() const throw()
{
    return str_err.c_str();
}


LX_WindowException::~LX_WindowException() throw(){}


/**
*   @fn LX_Window::LX_Window()
*
*   Create the window with the default configuration
*
*   @exception LX_WindowException
*/
LX_Window::LX_Window()
{
    Uint32 fullscreen_flag = 0x00000000;
    Uint32 position_flag = 0x00000000;

    int lxWidth = 0;
    int lxHeight = 0;

    LX_Configuration *win_config = LX_Configuration::getInstance();     // load the configuration

    lxWidth = win_config->getWinWidth();
    lxHeight = win_config->getWinHeight();

    // check the fullscreen flag
    if(win_config->getFullscreenFlag() == 1)
    {
        fullscreen_flag = SDL_WINDOW_FULLSCREEN;
    }

    // Is the fullscreen mode active
    if(fullscreen_flag == SDL_WINDOW_FULLSCREEN)
        position_flag = SDL_WINDOWPOS_UNDEFINED;
    else
        position_flag = SDL_WINDOWPOS_CENTERED;

    lxWindow = SDL_CreateWindow("Lunatix-engine with SDL 2",position_flag,position_flag,lxWidth,lxHeight,SDL_WINDOW_SHOWN|fullscreen_flag);

    if(lxWindow == NULL )
    {
        std::cerr << "exception occured in LX_Window constructor during the window creation : " << std::endl;
        throw LX_WindowException(SDL_GetError());
    }

    win_config->destroy();  // we do not need the LX_Configuration instance anymore

}


/**
*   @fn LX_Window::LX_Window(SDL_Window *sdlWin)
*
*   Create the window with an already set window
*
*   @param sdlWin the SDL_Window (must be a non-NULL pointer)
*
*   @note This constructor does not use the LX_config class
*   @warning If you contruct the LX_Window object with a NULL pointer, an exception will occur.
*
*   @exception LX_WindowException If sdlWin is NULL
*
*/
LX_Window::LX_Window(SDL_Window *sdlWin)
{
    if(sdlWin == NULL)
        throw LX_WindowException("exception occured in LX_Window : NULL value \n");

    lxWindow = sdlWin;
}

/**
*   @fn LX_Window::LX_Window(std::string title, int posX, int posY, int w, int h, bool screen_flag)
*
*   Create the window with custom configuration
*
*   @param title the title of the window
*   @param posX : the X position of the window on the monitor
*   @param posY : the Y position of the window on the monitor
*   @param w : the width of the window
*   @param h : the height of the window
*   @param screen_flag : a boolean that said if you want the fullscreen mode
*
*   @note This constructor does not use the LX_config class
*
*   @exception LX_WindowException If the window initialisation fails.
*
*/
LX_Window::LX_Window(std::string title, int posX, int posY, int w, int h, bool screen_flag)
{
    Uint32 fullscreen_flag = (( screen_flag == true ) ? SDL_WINDOW_FULLSCREEN : 0x00000000);

    lxWindow = SDL_CreateWindow(title.c_str(),posX,posY,w,h,SDL_WINDOW_SHOWN|fullscreen_flag);

    if(lxWindow == NULL )
    {
        std::cerr << "exception occured in LX_Window constructor during the render creation : " << std::endl;
        throw LX_WindowException(SDL_GetError());
    }

}


/**
*
*   @fn LX_Window::~LX_Window()
*
*   Destroy the window instance
*
*/
LX_Window::~LX_Window()
{
    SDL_DestroyWindow(lxWindow);
}

/**
*   @fn void LX_Window::setTitle(std::string title)
*
*   Set the title on the window sidebar
*
*   @param title : The title
*
*/
void LX_Window::setTitle(std::string title)
{
    SDL_SetWindowTitle(lxWindow,title.c_str());
}


/**
*
*   @fn SDL_Renderer * LX_Window::getRenderer()
*
*   Get the window renderer
*
*   @return a pointer to the renderer, NULL otherwise
*
*/
SDL_Renderer * LX_Window::getRenderer()
{
    return SDL_GetRenderer(lxWindow);
}


/**
*
*   @fn SDL_Surface * LX_Window::getSurface()
*
*   Get the window surface
*
*   @return a pointer to the SDL_Surface of the window, NULL otherwise
*
*/
SDL_Surface * LX_Window::getSurface()
{
    return SDL_GetWindowSurface(lxWindow);
}


/**
*
*   @fn SDL_Window * LX_Window::getWindow()
*
*   Get the window
*
*   @return a pointer to the SDL_Window, NULL otherwise
*
*/
SDL_Window * LX_Window::getWindow()
{
    return lxWindow;
}



/**
*   @fn int LX_Window::getWidth()
*
*   Return the width of the current window
*
*   @return the width
*
*/
int LX_Window::getWidth()
{
    int w;
    SDL_GetWindowSize(lxWindow,&w,NULL);

    return w;
}



/**
*   @fn int LX_Window::getHeight()
*
*   Return the height of the current window
*
*   @return the height
*
*/
int LX_Window::getHeight()
{
    int h;
    SDL_GetWindowSize(lxWindow,NULL,&h);

    return h;
}











