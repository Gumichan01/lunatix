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
*
*/

#include <iostream>
#include <exception>

#include <SDL/SDL.h>



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

    LX_window_exception( std::string err)
    {
        str_err = err;
    }

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
*
*/
class LX_window
{
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

        window=SDL_SetVideoMode(1024,768,32,SDL_HWSURFACE|SDL_DOUBLEBUF/*|SDL_FULLSCREEN*/);
        //window=SDL_SetVideoMode(width,height,bpp,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);

        if(window == NULL )
        {
            throw LX_window_exception(SDL_GetError());
        }

        LX_width = 1;
        LX_height = 2;
        LX_bpp = 0;

    }

    public:

    static LX_window * getInstance();
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














