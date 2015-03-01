#ifndef LX_WINDOW_H_INCLUDED
#define LX_WINDOW_H_INCLUDED



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
*	@file LX_window.h
*	@brief The LX_window library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 7th, 2015
*
*
*/

#include <SDL2/SDL.h>



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

    LX_window_exception(std::string err);

    const char * what() const throw();

    ~LX_window_exception() throw();
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

    SDL_Window *lxWindow;   /**< The main surface (for the window creation)*/


    public :

    LX_window();                    // The default constructor with default parameters
    LX_window(SDL_Window *sdlWin);
    LX_window(std::string title, int posX, int posY, int w, int h, bool screen_flag);
    LX_window(std::string title, int w, int h, bool full_flag);

    void setTitle(std::string title);

    SDL_Renderer * getRenderer();
    SDL_Surface * getSurface();
    SDL_Window * getWindow();

    int getWidth();
    int getHeight();


    ~LX_window();
};



#endif // LX_WINDOW_H_INCLUDED














