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
*	@date January 18th, 2015
*
*
*/

#include "LX_window.h"

#include <SDL2/SDL_image.h>

//struct LX_windowManager;


/**
*   @class LX_graphics
*   @brief The LunatiX_engine graphic module.
*
*   This class describes the LX_graphics engine.
*
*   @note : The LX_graphics class uses an instance of LX_window to get the main window information
*   @warning Because of the LX_window use, LX_graphics class must be built only after you initialized the LX_engine (calling LX_Init())
*/
class LX_graphics{

    //SDL_Window *window;     /**< Th main SDL_window */
    //SDL_Surface *surface;   /**< The main surface */

    LX_window *mainWindow;  /**< The main window */
    SDL_Renderer *renderer; /**< The main renderer */
    //std::vector<LX_window *> vectorWindows;    /**< The vector of other windows*/

    ///@todo [vector] Implement the vectorWindow
    LX_graphics();

    bool isBMPFile(std::string filename);

    public:

    //get the instance
    static LX_graphics * getInstance();
    static void destroy();


    // The static functions
    SDL_Surface * loadSurfaceFromBMP(std::string filename);
    SDL_Surface * loadSurface(std::string filename);

    SDL_Texture * loadTextureFromSurface(SDL_Surface *target);
    SDL_Texture * loadTextureFromFile(std::string filename);

    bool set_alpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue);

    int addSDLWindow(LX_window *win);
    bool destroySDLWindow(unsigned int wd);
    // End static functions

    // put the sprite on the screen
    bool put_surface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos);
    bool putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos);

    // the update and clearing functions
    void updateMainWindow();
    void updateMainRenderer();

    /// @todo [vector] define the update function on other windows
    // void updateWindow(int wd);
    //void updateRenderer(int wd);

    void clearMainWindow();
    void clearMainRenderer();

/**
*   @fn SDL_Surface * getMainSurface()
*
*   Returns the surface of the main window
*
*   @return the main surface
*
**/
    SDL_Surface * getMainSurface(){return mainWindow->getSurface();}


    ~LX_graphics();

};


#endif // LX_GRAPHICS_H_INCLUDED












