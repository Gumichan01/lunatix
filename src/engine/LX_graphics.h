#ifndef LX_GRAPHICS_H_INCLUDED
#define LX_GRAPHICS_H_INCLUDED



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
*	@file LX_graphics.h
*	@brief The LX_graphics library, it will be linked with the SDL library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date January 28th, 2015
*
*
*/

#include "LX_window.h"


#define LX_GRAPHICS_FULLSCREEN_DESKTOP SDL_WINDOW_FULLSCREEN_DESKTOP
#define LX_GRAPHICS_FULLSCREEN SDL_WINDOW_FULLSCREEN
#define LX_GRAPHICS_NO_FULLSCREEN 0



/**
*   @class LX_graphics
*   @brief The LunatiX_engine graphic module.
*
*   This class describes the LX_graphics engine.
*
*   @note : The LX_graphics class uses an instance of LX_window to get the main window information
*   @warning Because of the LX_window and SDL functions use, LX_graphics class must be built only after you initialized the LX_engine (calling LX_Init())
*/
class LX_graphics{

    LX_window *mainWindow;  /**< The main window */
    SDL_Renderer *renderer; /**< The main renderer */
    //std::vector<LX_window *> vectorWindows;    /**< The vector of other windows*/

    int originalWidth;
    int originalHeight;

    ///@todo [vector] Implement the windowVector
    LX_graphics();
    LX_graphics(LX_window *win);

    bool isBMPFile(std::string filename);

    public:

    //get the instance
    static LX_graphics * createInstance();
    static LX_graphics * createInstance(LX_window * win);
    static LX_graphics * getInstance();
    static void destroy();


    // The static functions
    SDL_Surface * loadSurface(std::string filename);

    SDL_Texture * loadTextureFromSurface(SDL_Surface *target);
    SDL_Texture * loadTextureFromFile(std::string filename);

    /// @todo [vector] implement the texture creation for a specific window
    // If wd == -1 > main window
    //SDL_Texure * laodTextureFomFile(std::string filename, int wd);

    bool set_alpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue);

    /// @todo [vector] implement the main operation on LX_window and SDL_Window
    int addLXWindow(LX_window *win);
    //int addSDLWindow(SDL_Window *win);
    bool destroySDLWindow(unsigned int wd);
    // End static functions

    // put the sprite on the screen
    bool put_surface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos);
    bool putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos);

    /// @todo [vector] define the surface and texture blit on other windows
    // If wd == -1 > main window
    //bool put_surfaceOn(int wd,SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos);
    //bool putTextureOn(int wd,SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos);

    void setWindowSize(int w, int h);
    void setFullscreen(Uint32 flag);

    // the update and clearing functions
    void updateMainWindow();
    void updateMainRenderer();

    /// @todo [vector] define the update function on other windows
    // void updateWindow(int wd);
    //void updateRenderer(int wd);

    void clearMainWindow();
    void clearMainRenderer();


    SDL_Surface * getMainSurface();

    ~LX_graphics();

};


#endif // LX_GRAPHICS_H_INCLUDED












