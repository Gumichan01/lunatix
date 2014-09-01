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
*	@date August 14th, 2014
*
*
*/

#include "LX_config.h"

#include <SDL/SDL.h>


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
*   @warning The LX_window class must be defined only after you initialized the LX_engine (calling LX_Init())
*   @warning A LX_window_exception will be occured if the window fcreation fails
*
*/
class LX_window{

    SDL_Surface *window;    /**< The main surface (for the window creation)*/

    int LX_width;           /**< The width of the window*/
    int LX_height;          /**< The height of the window*/
    int LX_bpp;             /**< The format (bits per pixel) of the window*/


/**
*   @fn LX_window()
*
*   Create the window
*
*/
    LX_window()
    {
        Uint32 fullscreen_flag = 0x00000000;
        LX_configuration *win_config = LX_configuration::getInstance();     // load the configuration

        LX_width = win_config->getWinWidth();
        LX_height = win_config->getWinHeight();
        LX_bpp = BPP;



        // check the fullscreen flag
        if(win_config->getFullscreenFlag() == 1)
        {
            fullscreen_flag = SDL_FULLSCREEN;
        }

        window=SDL_SetVideoMode(LX_width,LX_height,BPP,SDL_HWSURFACE|SDL_DOUBLEBUF|fullscreen_flag);

        if(window == NULL )
        {
            std::cerr << "exception occured in LX_window constructor : " << std::endl;
            throw LX_window_exception(SDL_GetError());
        }

        win_config->destroy();

    }

    public:

    static LX_window * getInstance();
    static void destroy();

    static void setTitle(std::string title);
    static void setTitle(std::string title, std::string icon);

    SDL_Surface * getWindow();

    int getWidth();
    int getHeight();


    ~LX_window()
    {
        SDL_FreeSurface(window);
    }
};













#endif // LX_WINDOW_H_INCLUDED














