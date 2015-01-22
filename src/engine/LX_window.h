#ifndef LX_WINDOW_H_INCLUDED
#define LX_WINDOW_H_INCLUDED



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
*	@file LX_window.h
*	@brief The LX_window library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date January 18th, 2015
*
*
*/

#include "LX_config.h"

#include <SDL2/SDL.h>


#define BPP 32      /**< The bits per pixel*/


/**
*   @class LX_window_exception
*   @brief The Window_creation_exception class.
*
*   This class describes the exception occured when the window initialization fails.
*
*/
class LX_window_exception : public std::exception
{
    public :

    std::string str_err;                    /**< The string where the error message will be conteined*/

/**
*   @fn LX_window_exception(std::string err)
*   Build the LX_window_exception class
*   @param err the error string
*/
    LX_window_exception(std::string err)
    {
        str_err = err;
    }

/**
*   @fn const char * what() const throw()
*   Get the error string
*   @return the error string
*/
    const char * what() const throw() {return str_err.c_str() ;}

    ~LX_window_exception() throw(){}
};



/**
*   @class LX_window
*   @brief The LX_window class.
*
*   This class describes the window.
*
*   @note By default, the constructor of the LX _window class gets the different informations
*          from the LX_configuration class
*
*   @warning The LX_window class must be defined only after you initialized the LX_engine (calling LX_Init())
*   @warning A LX_window_exception will be occured if the window creation fails
*
*/
class LX_window{

    SDL_Window *lxWindow;    /**< The main surface (for the window creation)*/

    int LX_width;           /**< The width of the lxWindow*/
    int LX_height;          /**< The height of the window*/
    int LX_bpp;             /**< The format (bits per pixel) of the window*/



    public :

/**
*   @fn LX_window()
*
*   Create the window with the default configuration
*
*/
    LX_window()
    {
        Uint32 fullscreen_flag = 0x00000000;
        Uint32 position_flag = 0x00000000;
        LX_configuration *win_config = LX_configuration::getInstance();     // load the configuration

        LX_width = win_config->getWinWidth();
        LX_height = win_config->getWinHeight();
        LX_bpp = BPP;


        // check the fullscreen flag
        if(win_config->getFullscreenFlag() == 1)
        {
            fullscreen_flag = SDL_WINDOW_FULLSCREEN;
        }

        //lxWindow=SDL_SetVideoMode(LX_width,LX_height,BPP,SDL_HWSURFACE|SDL_DOUBLEBUF|fullscreen_flag);

        // Is the fullscreen mode active
        if(fullscreen_flag == SDL_WINDOW_FULLSCREEN)
            position_flag = SDL_WINDOWPOS_UNDEFINED;
        else
            position_flag = SDL_WINDOWPOS_CENTERED;

        lxWindow = SDL_CreateWindow("Lunatix-engine with SDL 2",position_flag,position_flag,LX_width,LX_height,SDL_WINDOW_SHOWN|fullscreen_flag);

        if(lxWindow == NULL )
        {
            std::cerr << "exception occured in LX_window constructor during the window creation : " << std::endl;
            throw LX_window_exception(SDL_GetError());
        }

        win_config->destroy();  // we do not need the LX_configuration instance anymore

    }

/**
*   @fn LX_window(std::string title, int posX, int posY, int w, int h, bool full_flag)
*
*   Create the window with custom configuration
*
*   @param title the title of the window
*   @param posX : the X position of the window on the monitor
*   @param posY : the Y position of the window on the monitor
*   @param w : the width of the window
*   @param h : the height of the window
*   @param full_flag : a boolean tha said if you want the fullscreen mode
*
*   @note This constructor does not use the LX_config class
*/
    LX_window(std::string title, int posX, int posY, int w, int h, bool full_flag)
    {
        Uint32 fullscreen_flag = (( full_flag == true ) ? SDL_WINDOW_FULLSCREEN : 0x00000000);

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
    LX_window(std::string title, int w, int h, bool full_flag)
    {
        LX_window(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,full_flag);
    }


    void setTitle(std::string title);


    SDL_Renderer * getRenderer();
    SDL_Surface * getSurface();
    SDL_Window * getWindow();

    int getWidth();
    int getHeight();


    ~LX_window()
    {
        SDL_DestroyWindow(lxWindow);
    }
};













#endif // LX_WINDOW_H_INCLUDED














