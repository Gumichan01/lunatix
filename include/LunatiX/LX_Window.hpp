#ifndef LX_WINDOW_H_INCLUDED
#define LX_WINDOW_H_INCLUDED


/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Window.hpp
*	@brief The window library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.7
*
*/

#include <string>
#include <SDL2/SDL_stdinc.h>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Rect;


#define LX_GRAPHICS_FULLSCREEN_DESKTOP SDL_WINDOW_FULLSCREEN_DESKTOP    /**< Fullscreen with desktop resolution */
#define LX_GRAPHICS_FULLSCREEN SDL_WINDOW_FULLSCREEN                    /**< Fullscreen mode with original resolution */
#define LX_GRAPHICS_NO_FULLSCREEN 0                                     /**< Original resolution in window */

#define LX_WINDOW_SURFACE 0x01                                          /**< The flag to use the surface */
#define LX_WINDOW_RENDERING 0x10                                        /**< The flag to use the rendering */
#define LX_WINDOW_DEFAULT_MODE LX_WINDOW_RENDERING                      /**< Default mode (Rendering) */


namespace LX_Graphics
{


/**
*   @class LX_WindowException
*   @brief The exception class of LX_Window
*
*   This class describes the exception occured when
*   the SDL_Window instance cannot be loaded.
*
*/
class LX_WindowException : public std::exception
{
    std::string stringError;

public :

    LX_WindowException(std::string err);
    LX_WindowException(const LX_WindowException& w);

    const char * what() const noexcept;

    ~LX_WindowException() noexcept;
};


/**
*   @class LX_Window
*   @brief The window
*
*   @note By default, the constructor retrieves information from the configuration file
*
*   @warning The LX_Window class must be defined only after
*               the initialization of the engine (calling LX_Init())
*   @warning A LX_WindowException may be occured if the window creation fails
*
*/
class LX_Window
{
    SDL_Window *window;         /* The internal window structure  */
    SDL_Renderer *renderer;     /* The main renderer              */

    int original_width;          /* The width of the window        */
    int original_height;         /* The height of the window       */
    bool render_method;         /* Use Surface or Rendering       */

    LX_Window(LX_Window& w);
    LX_Window& operator =(LX_Window& w);

    void createWindow(std::string title, int posX, int posY, int w, int h,
              const Uint32 mode, Uint32 flag, bool accel = true);

    void createRendering(bool accel);

    void updateWindow(void);
    void updateRenderer(void);
    void clearSurface(void);
    void clearRenderer(void);

    bool screenshotUsingRenderer(std::string& filename);
    bool screenshotUsingSurface(std::string& filename);


public :

    LX_Window(const Uint32 mode, bool accel = true);
    LX_Window(std::string title, const Uint32 mode, bool accel = true);
    LX_Window(std::string title, int posX, int posY, int w, int h,
              const Uint32 mode, const Uint32 flag, bool accel = true);

    void setTitle(std::string title);

    // Put the sprite on the screen
    bool putSurface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos);
    bool putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos);
    bool putTextureAndRotate(SDL_Texture *origin, const SDL_Rect *area, const SDL_Rect *pos,
                             const double angle);

    void setWindowSize(int w, int h);
    void setFullscreen(Uint32 flag);

    // Update and clear window
    void update(void);
    void clearWindow(void);
    bool screenshot(std::string filename);

    SDL_Renderer * getRenderer(void);
    SDL_Surface * getSurface(void);
    SDL_Window * getWindow(void);

    int getWidth(void);
    int getHeight(void);

    ~LX_Window();
};

};

#endif // LX_WINDOW_H_INCLUDED

