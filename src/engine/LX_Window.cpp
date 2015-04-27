

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
*	@file LX_Window.cpp
*	@brief The LX_Window class
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 7th, 2015
*
*
*/

#include <SDL2/SDL.h>

#include "LX_Config.hpp"
#include "LX_Window.hpp"



namespace LX_Graphics{



    /**
    *   @fn LX_Window::LX_Window()
    *
    *   Create the window with the default configuration
    *
    *   @exception LX_WindowException
    *
    */
    LX_Window::LX_Window()
    {
        Uint32 option_flag = 0x00000000;
        Uint32 position_flag = 0x00000000;

        int lxWidth = 0;
        int lxHeight = 0;

        LX_Configuration *win_config = LX_Configuration::getInstance();     // load the configuration

        lxWidth = win_config->getWinWidth();
        lxHeight = win_config->getWinHeight();


        // check the fullscreen flag
        if(win_config->getFullscreenFlag() == 1)
        {
            option_flag |= SDL_WINDOW_FULLSCREEN;
        }


        // Is the fullscreen mode active ?
        if( (option_flag & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN)
            position_flag = SDL_WINDOWPOS_UNDEFINED;
        else
            position_flag = SDL_WINDOWPOS_CENTERED;


        // OpenGL flag
        if(win_config->getOpenGL_Flag() == 1)
        {
            option_flag |= SDL_WINDOW_OPENGL;
        }

        window = SDL_CreateWindow("LunatiX Engine with SDL 2",position_flag,position_flag,lxWidth,lxHeight,SDL_WINDOW_SHOWN|option_flag);

        if(window == NULL )
        {
            std::cerr << "LX_Window constructor - window creation : " << SDL_GetError() << std::endl;
        }

        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

        if(renderer == NULL)
        {
            std::cerr << "LX_Window constructor - renderer creation : " << SDL_GetError() << std::endl;
        }

        init2();
    }


    /**
    *   @fn LX_Window::LX_Window(std::string title)
    *
    *   Create the window setting the title
    *   using the default configuration
    *
    *   @exception LX_WindowException
    *
    */
    LX_Window::LX_Window(std::string title)
    {
        int w,h;
        Uint32 flag = 0x00000000;

        LX_Configuration *config = LX_Configuration::getInstance();

        w = config->getWinWidth();
        h = config->getWinHeight();

        if(config->getFullscreenFlag() == 1)
            flag |= LX_GRAPHICS_FULLSCREEN;

        if(config->getOpenGL_Flag() == 1)
            flag |= SDL_WINDOW_OPENGL;

        init(title.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,flag);
    }


    /**
    *   @fn LX_Window::LX_Window(SDL_Window *sdlWin)
    *
    *   Create the window with an already set window
    *
    *   @param sdlWin the SDL_Window (must be a non-NULL pointer)
    *
    *   @note This constructor does not use the LX_config class
    *   @warning If you contruct the LX_Window object with a NULL pointer, an exception will occur.
    *
    *   @exception LX_WindowException If sdlWin is NULL
    *
    */
    LX_Window::LX_Window(SDL_Window *sdlWin)
    {
        window = sdlWin;

        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

        if(renderer == NULL)
        {
            std::cerr << "LX_Window constructor - renderer creation : " << SDL_GetError() << std::endl;
        }

        init2();
    }


    /**
    *   @fn LX_Window::LX_Window(std::string title, int posX, int posY, int w, int h, Uint32 flag)
    *
    *   Create the window with custom configuration
    *
    *   @param title the title of the window
    *   @param posX : the X position of the window on the monitor
    *   @param posY : the Y position of the window on the monitor
    *   @param w : the width of the window
    *   @param h : the height of the window
    *   @param flag : one ofthese following flags :
    *           LX_GRAPHICS_FULLSCREEN_DESKTOP
    *           LX_GRAPHICS_FULLSCREEN
    *           LX_GRAPHICS_NO_FULLSCREEN
    *           And any SDL flags
    *
    *   @note This constructor does not use the LX_config class
    *
    *   @exception LX_WindowException If the window or redrering initialisation fails.
    *
    */
    LX_Window::LX_Window(std::string title, int posX, int posY, int w, int h, Uint32 flag)
    {
        init(title.c_str(),posX,posY,w,h,flag);
    }


     /**
    *   @fn LX_Window::init(std::string title, int posX, int posY, int w, int h, Uint32 flag)
    *
    *   Create the window with custom configuration
    *
    *   @param title the title of the window
    *   @param posX : the X position of the window on the monitor
    *   @param posY : the Y position of the window on the monitor
    *   @param w : the width of the window
    *   @param h : the height of the window
    *   @param flag : it is the same kind of flag used in LX_Window::LX_Window()
    *
    *   @note This constructor does not use the LX_config class
    *
    *   @exception LX_WindowException If the window or redrering initialisation fails.
    *
    */
    void LX_Window::init(std::string title, int posX, int posY, int w, int h, Uint32 flag)
    {
        window = SDL_CreateWindow(title.c_str(),posX,posY,w,h,SDL_WINDOW_SHOWN|flag);

        if(window == NULL )
        {
            std::cerr << "LX_Window constructor - window creation : " << SDL_GetError() << std::endl;
        }

        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

        if(renderer == NULL)
        {
            std::cerr << "LX_Window constructor - renderer creation : " << SDL_GetError() << std::endl;
        }

        init2();
    }


     /**
    *   @fn LX_Window::init2()
    *
    *   Initialize internal variables
    *
    */
    void LX_Window::init2()
    {
        originalWidth = getWidth();
        originalHeight = getHeight();
    }

    /**
    *
    *   @fn LX_Window::~LX_Window()
    *
    *   Destroy the window instance
    *
    */
    LX_Window::~LX_Window()
    {
        SDL_DestroyWindow(window);
    }

    /**
    *   @fn void LX_Window::setTitle(std::string title)
    *
    *   Set the title on the window sidebar
    *
    *   @param title : The title
    *
    */
    void LX_Window::setTitle(std::string title)
    {
        SDL_SetWindowTitle(window,title.c_str());
    }




    /**
    *
    *   @fn bool LX_Window::put_surface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos)
    *
    *   This function puts the surface on the surface according to its position and the area to put on it
    *
    *   @param image : the surface to put
    *   @param area : the area of the surface to put on the screen
    *   @param pos : the position of what you want to put
    *
    *   @note If you do not need to determine the area parameter of the surface, put NULL
    *
    *   @return TRUE if the image was put with success, FALSE otherwise
    */
    bool LX_Window::put_surface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos)
    {
        int err = 0;
        SDL_Rect offset;

        // I check if the image or the position is NULL
        if(image == NULL)
            return false;

        if(pos == NULL)
        {   // The texture will be set on the top-left of the main surface
            offset.x = 0;
            offset.y = 0;
            offset.w = 0;
            offset.h = 0;
        }
        else
        {
            offset.x = pos->x;
            offset.y = pos->y;
            offset.w = pos->w;
            offset.h = pos->h;
        }

        err = SDL_BlitSurface(image,area,SDL_GetWindowSurface(window),&offset);

        if(err < 0)
            return false;

        return true;
    }


    /**
    *   @fn bool LX_Window::putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos)
    *
    *   This function puts the texture on the window according to its position and the area to put on it
    *
    *   @param origin : the texture to put
    *   @param area : the area of the surface to put on the renderer
    *   @param pos : the position of what you want to put
    *
    *   @note If you do not need to determine the area parameter of the surface, put NULL
    *   @warning The width and the height defined in the SDL_Rect are important, the function uses it
    *               to display the texture according to its dimension
    *
    *   @return TRUE if the texture was put with success, FALSE otherwise
    **/
    bool LX_Window::putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos)
    {

        if(SDL_RenderCopy(renderer,origin,area,pos) < 0)
            return false;

        return true;
    }


    /**
    *   @fn void LX_Window::setWindowSize(int w, int h)
    *
    *   Set the size of the main window
    *
    *   @param w the width of the window
    *   @param h the height of the window
    *
    */
    void LX_Window::setWindowSize(int w, int h)
    {
        SDL_SetWindowSize(window,w,h);
    }


    /**
    *   @fn void LX_Window::setFullscreen(Uint32 flag)
    *
    *   Set the fullscreen to the main window
    *
    *   @param flag the flag you want to use in this function
    *
    */
    void LX_Window::setFullscreen(Uint32 flag)
    {
        SDL_SetWindowFullscreen(window,flag);

        if(flag == LX_GRAPHICS_NO_FULLSCREEN)   // set the window at the original size
        {
            setWindowSize(originalWidth,originalHeight);
        }
    }



    /**
    *   @fn void LX_Window::updateRenderer()
    *
    *   Updates the renderer of the window
    *
    *   @note This fonction must be used only if you manipulate textures
    *   on the current window. So you cannot use this function and
    *   LX_Window::updateWindow() together.
    *
    */
    void LX_Window::updateRenderer()
    {
        SDL_RenderPresent(renderer);
    }



    /**
    *
    *   @fn void LX_Window::clearWindow()
    *
    *   This function clears the main window
    *
    */
    void LX_Window::clearWindow()
    {
        SDL_Surface *tmp = SDL_GetWindowSurface(window);
        SDL_FillRect(tmp,NULL, SDL_MapRGB(tmp->format,0,0,0));
    }


    /**
    *
    *   @fn void LX_Window::clearRenderer()
    *
    *   This function clears the main renderer
    *
    */
    void LX_Window::clearRenderer()
    {
        SDL_RenderClear(renderer);
    }

    /**
    *
    *   @fn void LX_Window::updateWindow()
    *
    *   This function updates the surface of the window
    *
    *   @note This fonction must be used only if you manipulate surfaces
    *   on the current window. So you cannot use this function and
    *   LX_Window::updateRenderer() together.
    *
    */
    void LX_Window::updateWindow()
    {
        SDL_UpdateWindowSurface(window);
    }


    /**
    *
    *   @fn SDL_Renderer * LX_Window::getRenderer()
    *
    *   Get the window renderer
    *
    *   @return a pointer to the renderer, NULL otherwise
    *
    */
    SDL_Renderer * LX_Window::getRenderer()
    {
        return SDL_GetRenderer(window);
    }


    /**
    *
    *   @fn SDL_Surface * LX_Window::getSurface()
    *
    *   Get the window surface
    *
    *   @return a pointer to the SDL_Surface of the window, NULL otherwise
    *
    */
    SDL_Surface * LX_Window::getSurface()
    {
        return SDL_GetWindowSurface(window);
    }


    /**
    *
    *   @fn SDL_Window * LX_Window::getWindow()
    *
    *   Get the window
    *
    *   @return a pointer to the SDL_Window, NULL otherwise
    *
    */
    SDL_Window * LX_Window::getWindow()
    {
        return window;
    }



    /**
    *   @fn int LX_Window::getWidth()
    *
    *   Return the width of the current window
    *
    *   @return the width
    *
    */
    int LX_Window::getWidth()
    {
        int w;
        SDL_GetWindowSize(window,&w,NULL);

        return w;
    }



    /**
    *   @fn int LX_Window::getHeight()
    *
    *   Return the height of the current window
    *
    *   @return the height
    *
    */
    int LX_Window::getHeight()
    {
        int h;
        SDL_GetWindowSize(window,NULL,&h);

        return h;
    }


};







