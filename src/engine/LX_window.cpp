

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
*	@date January 28th, 2015
*
*
*/

#include "LX_window.h"


/**
*   @fn LX_window()
*
*   Create the window with the default configuration
*
*/
LX_window::LX_window()
{
    Uint32 fullscreen_flag = 0x00000000;
    Uint32 position_flag = 0x00000000;

    int lxWidth = 0;
    int lxHeight = 0;
    int lxBitsPerPixel = 0;

    LX_configuration *win_config = LX_configuration::getInstance();     // load the configuration

    lxWidth = win_config->getWinWidth();
    lxHeight = win_config->getWinHeight();
    lxBitsPerPixel = BPP;


    // check the fullscreen flag
    if(win_config->getFullscreenFlag() == 1)
    {
        fullscreen_flag = SDL_WINDOW_FULLSCREEN;
    }

    //lxWindow=SDL_SetVideoMode(lxWidth,lxHeight,BPP,SDL_HWSURFACE|SDL_DOUBLEBUF|fullscreen_flag);

    // Is the fullscreen mode active
    if(fullscreen_flag == SDL_WINDOW_FULLSCREEN)
        position_flag = SDL_WINDOWPOS_UNDEFINED;
    else
        position_flag = SDL_WINDOWPOS_CENTERED;

    lxWindow = SDL_CreateWindow("Lunatix-engine with SDL 2",position_flag,position_flag,lxWidth,lxHeight,SDL_WINDOW_SHOWN|fullscreen_flag);

    if(lxWindow == NULL )
    {
        std::cerr << "exception occured in LX_window constructor during the window creation : " << std::endl;
        throw LX_window_exception(SDL_GetError());
    }

    win_config->destroy();  // we do not need the LX_configuration instance anymore

}


/**
*   @fn LX_window(std::string title, int posX, int posY, int w, int h, bool screen_flag)
*
*   Create the window with an already set window
*
*   @param sdlWin the SDL_Window (must be a non-NUL pointer)
*
*   @warning If you contruct the LX_Window object with a NULL pointer, an exception will occur.
*/
LX_window::LX_window(SDL_Window *sdlWin)
{
    if(sdlWin == NULL)
        throw LX_window_exception("exception occured in LX_window : NULL value \n");

}

/**
*   @fn LX_window(std::string title, int posX, int posY, int w, int h, bool screen_flag)
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
*/
LX_window::LX_window(std::string title, int posX, int posY, int w, int h, bool screen_flag)
{
    Uint32 fullscreen_flag = (( screen_flag == true ) ? SDL_WINDOW_FULLSCREEN : 0x00000000);

    lxWindow = SDL_CreateWindow(title.c_str(),posX,posY,w,h,SDL_WINDOW_SHOWN|fullscreen_flag);

    if(lxWindow == NULL )
    {
        std::cerr << "exception occured in LX_window constructor during the render creation : " << std::endl;
        throw LX_window_exception(SDL_GetError());
    }

}


/**
*   @fn LX_window(std::string title, int w, int h, bool full_flag)
*
*   Create the window with only the name and te fullscreen flag
*
*   @param title : the title of the window
*   @param w : the width of the window
*   @param h : the height of the window
*   @param full_flag : a boolean tha said if you want the fullscreen mode
*
*   @note This constructor does not use also the LX_config class
*/
LX_window::LX_window(std::string title, int w, int h, bool full_flag)
{
    LX_window(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,full_flag);
}




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
    SDL_SetWindowTitle(lxWindow,title.c_str());
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
    return SDL_GetRenderer(lxWindow);
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
    return SDL_GetWindowSurface(lxWindow);
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
    return lxWindow;
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
    SDL_GetWindowSize(lxWindow,&w,NULL);

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
    SDL_GetWindowSize(lxWindow,NULL,&h);

    return h;
}











