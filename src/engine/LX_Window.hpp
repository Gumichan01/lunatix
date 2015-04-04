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
*	@file LX_Window.hpp
*	@brief The LX_Window library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 7th, 2015
*
*
*/


struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

/**
*   @class LX_WindowException
*   @brief The Window_creation_exception class.
*
*   This class describes the exception occured when the window initialization fails.
*
*/
class LX_WindowException : public std::exception
{
    public :

    std::string str_err;                    /**< The string where the error message will be conteined*/

    LX_WindowException(std::string err);

    const char * what() const throw();

    ~LX_WindowException() throw();
};



/**
*   @class LX_Window
*   @brief The LX_Window class.
*
*   This class describes the window.
*
*   @note By default, the constructor of the LX _window class gets the different informations
*          from the LX_Configuration class
*
*   @warning The LX_Window class must be defined only after you initialized the LX_engine (calling LX_Init())
*   @warning A LX_WindowException will be occured if the window creation fails
*
*/
class LX_Window{

    SDL_Window *lxWindow;   /**< The internal window structure*/


    public :

    LX_Window();                    // The default constructor with default parameters
    LX_Window(SDL_Window *sdlWin);
    LX_Window(std::string title, int posX, int posY, int w, int h, bool screen_flag);

    void setTitle(std::string title);

    SDL_Renderer * getRenderer();
    SDL_Surface * getSurface();
    SDL_Window * getWindow();

    int getWidth();
    int getHeight();


    ~LX_Window();
};



#endif // LX_WINDOW_H_INCLUDED














