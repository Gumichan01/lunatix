#ifndef LX_GRAPHICS_H_INCLUDED
#define LX_GRAPHICS_H_INCLUDED



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
*	@file LX_graphics.h
*	@brief The LX_graphics library, it will be linked with the SDL library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 13th, 2014
*
*
*/
#include<iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

//#include "LX_error.h"
#include "LX_window.h"

/**
*   @class LX_graphics
*   @brief The LunatiX_engine graphic module.
*
*   This class describes the LX_graphics engine.
*/
class LX_graphics{

    SDL_Surface *screen;    /**< The main surface (for the window creation)*/



/**
*
*   @fn LX_graphics(unsigned int width, unsigned int height, unsigned int bpp)
*
*   This constructor initializes The SDL subsystems and create the window of the game
*
*   @param width : The width of the future window
*   @param height : the height of the future window
*   @param bpp : bits per pixels
*
*/
    LX_graphics()
    {
        LX_window *win = LX_window::getInstance();

        if(win != NULL)
        {
            screen = win->getWindow();
        }

        delete win;
    }

    public:

    //get the instance
    static LX_graphics * getInstance();


    // The static functions

    static SDL_Surface * load_BMP(std::string filename);
    static SDL_Surface * load_image(std::string filename);

    static bool put_transparency(SDL_Surface *image,unsigned int red, unsigned int green, unsigned int blue);

    // put the image on the screen
    bool put_image(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos);

    // the update and clearing functions
    void update();

    void clear();


    SDL_Surface * getScreen(){return screen;}

    ~LX_graphics()
    {
        delete screen;
    }

};









#endif // LX_GRAPHICS_H_INCLUDED












