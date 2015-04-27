#ifndef LX_WINDOWMANAGER_HPP_INCLUDED
#define LX_WINDOWMANAGER_HPP_INCLUDED



/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_WindowManager.hpp
*	@brief The window manager
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.3
*	@date April 24th, 2015
*
*/


#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "LX_Window.hpp"


#define LX_NBMAX_WINDOWS 100


namespace LX_Graphics{

    /**
    *   @class LX_WindowManager
    *
    *   @brief The window manager class
    *
    *   It handles various windows
    *
    */
    class LX_WindowManager{

        LX_Window * mainWindow;
        unsigned int size;
        unsigned int nb_windows;
        LX_Window *windows[LX_NBMAX_WINDOWS];

        LX_WindowManager();
        ~LX_WindowManager();

        public:

        static void init();
        static LX_WindowManager * getInstance();
        static void destroy();

        int addWindow(LX_Window *w);
        int deleteWindow(unsigned int id);

        unsigned int nbWindow(void);

        LX_Window * getWindow(unsigned int id);

    };


    LX_WindowManager * getWindowManager();

};



#endif // LX_WINDOWMANAGER_HPP_INCLUDED

