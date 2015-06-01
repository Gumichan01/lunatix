

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
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
*	@brief The implementation of the window
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

#include "LX_Config.hpp"
#include "LX_Window.hpp"
#include "LX_Error.hpp"



namespace LX_Graphics{


    /**
    *   @fn LX_WindowException::LX_WindowException(std::string err)
    *
    *   Build the LX_WindowException class
    *
    *   @param err The error string
    *
    */
    LX_WindowException::LX_WindowException(std::string err)
    {
        str_err = err;
    }


    /**
    *   @fn const char * LX_WindowException::what() const throw()
    *
    *   Get the error string
    *
    *   @return The error string
    */
    const char * LX_WindowException::what() const throw()
    {
        return str_err.c_str();
    }


    LX_WindowException::~LX_WindowException() throw(){}



    /**
    *   @fn LX_Window::LX_Window(const Uint32 mode)
    *
    *   Create the window with the default configuration
    *
    *   @param mode The display mode
    *           - LX_WINDOW_SURFACE : to use surfaces
    *           - LX_WINDOW_RENDERING : to use the renderer
    *
    *   @exception LX_WindowException
    *
    */
    LX_Window::LX_Window(const Uint32 mode)
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

        window = SDL_CreateWindow("LunatiX Engine v0.3",position_flag,position_flag,lxWidth,lxHeight,SDL_WINDOW_SHOWN|option_flag);

        if(window == NULL )
        {
            std::cerr << "LX_Window constructor - window creation " << std::endl;
            throw LX_WindowException(LX_GetError());
        }

        if(mode == LX_WINDOW_RENDERING)
        {
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

            if(renderer == NULL)
            {
                std::cerr << "LX_Window constructor - renderer creation : " << LX_GetError() << std::endl;
            }
        }

        init2();
    }


    /**
    *   @fn LX_Window::LX_Window(std::string title, const Uint32 mode)
    *
    *   Create the window setting the title
    *
    *   @param title The title of the window
    *   @param mode The display mode :
    *           - LX_WINDOW_SURFACE : to use surfaces
    *           - LX_WINDOW_RENDERING : to use the renderer
    *
    *   @note The default configuration is used during the creation of the window
    *
    */
    LX_Window::LX_Window(std::string title, const Uint32 mode)
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

        init(title.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,mode,flag);
    }


    /**
    *   @fn LX_Window::LX_Window(SDL_Window *sdlWin, const Uint32 mode)
    *
    *   Create the window with an already set window
    *
    *   @param sdlWin The SDL_Window (must be a non-NULL pointer)
    *   @param mode The display mode
    *           - LX_WINDOW_SURFACE : to use surfaces
    *           - LX_WINDOW_RENDERING : to use the renderer
    *
    *   @note This constructor does not use the LX_config class
    *
    */
    LX_Window::LX_Window(SDL_Window *sdlWin, const Uint32 mode)
    {
        window = sdlWin;
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

        if(renderer == NULL)
        {
            std::cerr << "LX_Window constructor - renderer creation : " << LX_GetError() << std::endl;
        }

        init2();
    }


    /**
    *   @fn LX_Window::LX_Window(std::string title, int posX, int posY, int w, int h, const Uint32 mode, Uint32 flag)
    *
    *   Create the window with custom configuration
    *
    *   @param title The title of the window
    *   @param posX The X position of the window on the desktop
    *   @param posY The Y position of the window on the desktop
    *   @param w The width of the window
    *   @param h The height of the window
    *   @param mode The display mode
    *           - LX_WINDOW_SURFACE : to use surfaces
    *           - LX_WINDOW_RENDERING : to use the renderer
    *   @param flag One of these following flags
    *           - LX_GRAPHICS_FULLSCREEN_DESKTOP
    *           - LX_GRAPHICS_FULLSCREEN
    *           - LX_GRAPHICS_NO_FULLSCREEN
    *           - And any SDL flags
    *
    *   @note This constructor does not use the LX_config class
    *
    */
    LX_Window::LX_Window(std::string title, int posX, int posY, int w, int h, const Uint32 mode, Uint32 flag)
    {
        init(title.c_str(),posX,posY,w,h,mode,flag);
    }


    /**
    *   @fn LX_Window::init(std::string title, int posX, int posY, int w, int h, const Uint32 mode, Uint32 flag)
    *
    *   Create the window with custom configuration
    *
    *   @param title The title of the window
    *   @param posX The X position of the window on the monitor
    *   @param posY The Y position of the window on the monitor
    *   @param w The width of the window
    *   @param h The height of the window
    *   @param mode The display mode
    *           - LX_WINDOW_SURFACE : to use surfaces
    *           - LX_WINDOW_RENDERING : to use the renderer
    *   @param flag It is the same kind of flag used in LX_Window::LX_Window()
    *
    *   @note This constructor does not use the LX_config class
    *
    *   @exception LX_WindowException
    *
    */
    void LX_Window::init(std::string title, int posX, int posY, int w, int h, const Uint32 mode, Uint32 flag)
    {
        window = SDL_CreateWindow(title.c_str(),posX,posY,w,h,SDL_WINDOW_SHOWN|flag);

        if(window == NULL )
        {
            std::cerr << "LX_Window constructor - window creation " << std::endl;
            throw LX_WindowException(LX_GetError());
        }

        if(mode == LX_WINDOW_RENDERING)
        {
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

            if(renderer == NULL)
            {
                std::cerr << "LX_Window constructor - renderer creation : " << LX_GetError() << std::endl;
            }
        }

        init2();
    }


    /**
    *   @fn LX_Window::init2(void)
    *
    *   Initialize internal variables
    *
    */
    void LX_Window::init2(void)
    {
        originalWidth = getWidth();
        originalHeight = getHeight();
    }


    /**
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
    *   @fn bool LX_Window::putSurface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos)
    *
    *   This function puts a area of the surface on the window surface at a specified position
    *
    *   @param image The surface to put
    *   @param area The area of the surface to put on the screen
    *   @param pos The position of what you want to put
    *
    *   @return TRUE If the image was put with success, FALSE otherwise
    *
    *   @note If you do not need to determine the area parameter of the surface, put NULL
    *   @note You can give a LX_AABB object to the function instead of a SDL_Rect object.
    *           Actually, LX_AABB is just an alias of SDL_Rect
    *
    */
    bool LX_Window::putSurface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos)
    {
        int err = 0;
        SDL_Rect offset;

        if(image == NULL)
            return false;

        if(pos == NULL)
        {
            // The texture will be set on the top-left of the main surface
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
    *   This function puts an area of the texture on the window
    *
    *   @param origin The texture to put
    *   @param area The area of the surface to put on the renderer
    *   @param pos The position of what you want to put
    *
    *   @return TRUE If the texture was put with success, FALSE otherwise
    *
    *   @note If you do not need to determine the area parameter of the surface, put NULL
    *   @note You can give a LX_AABB object to the function instead of a SDL_Rect object.
    *           Actually, LX_AABB is just an alias of SDL_Rect
    *   @warning The width and the height defined in the SDL_Rect are important, the function uses it
    *               to display the texture according to its dimension
    *
    */
    bool LX_Window::putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos)
    {

        return(SDL_RenderCopy(renderer,origin,area,pos) == 0);
    }


    /**
    *   @fn bool LX_Window::putTextureAndRotate(SDL_Texture *origin, const SDL_Rect *area, const SDL_Rect *pos,const double angle)
    *
    *   This function puts an area of the texture on the window and optionnaly rotate it
    *
    *   @param origin The texture to put
    *   @param area The area of the surface to put on the renderer
    *   @param pos The position of what you want to put
    *   @param angle an angle in degrees that indicate the rotation
    *
    *   @return TRUE If the texture was put with success, FALSE otherwise
    *
    *   @note If you do not need to determine the area parameter of the surface, put NULL
    *   @note You can give a LX_AABB object to the function instead of a SDL_Rect object.
    *           Actually, LX_AABB is just an alias of SDL_Rect
    *   @warning The width and the height defined in the SDL_Rect are important, the function uses it
    *               to display the texture according to its dimension
    *
    */
    bool LX_Window::putTextureAndRotate(SDL_Texture *origin, const SDL_Rect *area, const SDL_Rect *pos,
                        const double angle)
    {
        return(SDL_RenderCopyEx(renderer,origin,area,pos, (-angle), NULL,SDL_FLIP_NONE) == 0);
    }



    /**
    *   @fn void LX_Window::setTitle(std::string title)
    *
    *   Set the title of the window
    *
    *   @param title The title
    *
    */
    void LX_Window::setTitle(std::string title)
    {
        SDL_SetWindowTitle(window,title.c_str());
    }



    /**
    *   @fn void LX_Window::setWindowSize(int w, int h)
    *
    *   Set the size of the window
    *
    *   @param w The width of the window
    *   @param h The height of the window
    *
    */
    void LX_Window::setWindowSize(int w, int h)
    {
        SDL_SetWindowSize(window,w,h);
    }


    /**
    *   @fn void LX_Window::setFullscreen(Uint32 flag)
    *
    *   Set the window's fullscreen state
    *
    *   @param flag The flag you want to use in this function
    *           - LX_GRAPHICS_FULLSCREEN_DESKTOP
    *           - LX_GRAPHICS_FULLSCREEN
    *           - LX_GRAPHICS_NO_FULLSCREEN
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
    *   @fn void LX_Window::updateRenderer(void)
    *
    *   Updates the renderer of the window
    *
    *   @note This fonction must be used only if you manipulate textures
    *   on the current window. So you cannot use this function and
    *   LX_Window::updateWindow() together on a same window.
    *
    */
    void LX_Window::updateRenderer(void)
    {
        SDL_RenderPresent(renderer);
    }


    /**
    *   @fn void LX_Window::updateWindow(void)
    *
    *   This function updates the surface of the window
    *
    *   @note This fonction must be used only if you manipulate surfaces
    *   on the current window. So you cannot use this function and
    *   LX_Window::updateRenderer() together on a same window.
    *
    */
    void LX_Window::updateWindow(void)
    {
        SDL_UpdateWindowSurface(window);
    }


    /**
    *   @fn void LX_Window::clearWindow(void)
    *
    *   This function clears the main window
    *
    */
    void LX_Window::clearWindow(void)
    {
        SDL_Surface *tmp = SDL_GetWindowSurface(window);
        SDL_FillRect(tmp,NULL, SDL_MapRGB(tmp->format,0,0,0));
    }


    /**
    *   @fn void LX_Window::clearRenderer(void)
    *
    *   This function clears the renderer
    *
    */
    void LX_Window::clearRenderer(void)
    {
        SDL_RenderClear(renderer);
    }


    /**
    *   @fn SDL_Renderer * LX_Window::getRenderer(void)
    *
    *   Get the window renderer
    *
    *   @return A valid pointer to the renderer if the window internally use it
    *
    */
    SDL_Renderer * LX_Window::getRenderer(void)
    {
        return SDL_GetRenderer(window);
    }


    /**
    *   @fn SDL_Surface * LX_Window::getSurface(void)
    *
    *   Get the window surface
    *
    *   @return A valid pointer to the SDL_Surface if the window internally use it
    *
    */
    SDL_Surface * LX_Window::getSurface(void)
    {
        return SDL_GetWindowSurface(window);
    }


    /**
    *
    *   @fn SDL_Window * LX_Window::getWindow(void)
    *
    *   Get the window
    *
    *   @return A pointer to the SDL_Window instance
    *
    *   @note Normally, the function never returns a NULL pointer,
    *           but it is better to check the pointer value
    *
    */
    SDL_Window * LX_Window::getWindow(void)
    {
        return window;
    }



    /**
    *   @fn int LX_Window::getWidth(void)
    *
    *   Get the width of the window
    *
    *   @return the width
    *
    */
    int LX_Window::getWidth(void)
    {
        int w;
        SDL_GetWindowSize(window,&w,NULL);

        return w;
    }



    /**
    *   @fn int LX_Window::getHeight(void)
    *
    *   Get the height of the window
    *
    *   @return the height
    *
    */
    int LX_Window::getHeight(void)
    {
        int h;
        SDL_GetWindowSize(window,NULL,&h);

        return h;
    }


};



