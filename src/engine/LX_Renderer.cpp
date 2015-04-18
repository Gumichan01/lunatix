

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Renderer.cpp
*	@brief The LunatiX_engine graphic module
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date January 28th, 2015
*
*
*/

#include <iostream>
#include <string>

#include <SDL2/SDL_image.h>

#include "LX_Renderer.hpp"
#include "LX_Window.hpp"


static LX_Graphics::LX_Renderer *gInstance = NULL;


namespace LX_Graphics{


    /**
    *   @fn static LX_Renderer * LX_Renderer::createInstance()
    *
    *   Get the unique instance of the LX_Renderer class
    *
    *   @return the unique instance of LX_Renderer
    *
    */
    LX_Renderer * LX_Renderer::createInstance()
    {
        if(gInstance == NULL)
        {
            gInstance = new LX_Renderer();
        }

        return gInstance;
    }


    /**
    *   @fn static LX_Renderer * LX_Renderer::createInstance(LX_Window * win)
    *
    *   Get the unique instance of the LX_Renderer class setting the SDL_Window
    *
    *   @param win the main SDL_window you want to use
    *
    *   @return the unique instance of LX_Renderer
    *
    */
    LX_Renderer * LX_Renderer::createInstance(LX_Window * win)
    {
        if(gInstance == NULL && win != NULL)
        {
            gInstance = new LX_Renderer(win);
        }

        return gInstance;
    }



    /**
    *   @fn LX_Renderer * LX_Renderer::getInstance()
    *
    *   Get the unique instance of the LX_Renderer class
    *
    *   @return the unique instance of LX_Renderer
    *
    */
    LX_Renderer * LX_Renderer::getInstance()
    {
        return gInstance;
    }



    /**
    *   @fn void LX_Renderer::destroy()
    *
    *   Destroy the unique instance
    *
    *   @warning you must call this function to prevent a memory leak if you called LX_Renderer::getInstances()
    *
    */
    void LX_Renderer::destroy()
    {
        delete gInstance;
        gInstance = NULL;
    }



    /**
    *   @fn LX_Renderer::LX_Renderer()
    *
    *   Create the instance
    *
    */
    LX_Renderer::LX_Renderer()
    {
        mainWindow = new LX_Window();
        init();
    }



    /**
    *   @fn LX_Renderer::LX_Renderer(LX_Window *win)
    *
    *   Create the instance
    *
    *   @param win the LX_Window you created before
    *
    */
    LX_Renderer::LX_Renderer(LX_Window *win)
    {
        mainWindow = win;
        init();
    }



    /**
    *   @fn LX_Renderer::~LX_Renderer()
    *
    *   Destroy the instance
    *
    */
    LX_Renderer::~LX_Renderer()
    {
        delete mainWindow;
        mainWindow = NULL;
    }

    /**
    *   @fn void LX_Renderer::init()
    *
    *   Initialise the window
    *
    */
    void LX_Renderer::init()
    {
        renderer = SDL_CreateRenderer(mainWindow->getWindow(),-1,SDL_RENDERER_ACCELERATED);

        originalWidth = mainWindow->getWidth();
        originalHeight = mainWindow->getHeight();
    }



    /**
    *
    *   @fn SDL_Surface * LX_Renderer::loadSurface(std::string filename)
    *
    *   This function loads an SDL_Surface from any image file an optimized its format
    *
    *   @param filename : the file name which describe the image
    *
    *   @return the loaded and optimized surface if there is no problem, NULL otherwise
    *
    *   @note You may use this function instead of load_surfaceFromBMP() to load a non .bmp file
    *   @note If you want to load a .bmp file and use the transparency,
    *           please use load_surfaceFromBMP and set_alpha()
    *
    *   @warning When you call this function, the format optimization includes the alpha canal.
    *               No alpha needs to be set on the surface after that, except if you want to modify it
    *
    */
    SDL_Surface * LX_Renderer::loadSurface(std::string filename)
    {
        SDL_Surface *loaded = NULL;
        SDL_Surface *optimized = NULL;

        loaded = IMG_Load(filename.c_str());

        if(loaded == NULL)
        {
            return NULL;
        }

        optimized = SDL_ConvertSurfaceFormat(loaded,SDL_PIXELFORMAT_RGBA4444,0x00000000);

        SDL_FreeSurface(loaded);

        return optimized;
    }


    /**
    *   @fn SDL_Texture * LX_Renderer::loadTextureFromSurface(SDL_Surface *target)
    *
    *   Loads create a texture from a surface
    *
    *   @param target : the surface you want to use to create the texture
    *
    *   @return  a new pointer to the texture if the loading is successful, NULL otherwise
    *
    */
    SDL_Texture * LX_Renderer::loadTextureFromSurface(SDL_Surface *target)
    {
        return SDL_CreateTextureFromSurface(renderer,target);
    }


    /**
    *   @fn SDL_Texture * LX_Renderer::loadTextureFromFile(std::string filename)
    *
    *   Load a new texture from a file
    *
    *   @param filename : the name of the file you need to use for the texture creation
    *
    *   @return a pointer to a SDL_Texture if the loading works, NULL otherwise
    *
    */
    SDL_Texture * LX_Renderer::loadTextureFromFile(std::string filename)
    {
        SDL_Surface *tmpS = NULL;
        SDL_Texture *tmpT = NULL;

        tmpS = loadSurface(filename.c_str());

        if(tmpS == NULL)
        {
            return NULL;
        }

        tmpT = loadTextureFromSurface(tmpS);

        SDL_FreeSurface(tmpS);

        return tmpT;
    }


    /**
    *
    *   @fn bool LX_Renderer::set_alpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue)
    *
    *   This function set the alpha value on a SDL_surface
    *
    *   @param image : the surface
    *   @param red : the the red color canal of the future transparent color
    *   @param green : the the green color canal of the future transparent color
    *   @param blue : the the blue color canal of the future transparent color
    *
    *   @return TRUE if the transparency was done without problem, FALSE otherwise
    *
    *   @note You may use any format for values (hexadecimal, digital,...).
    *
    */
    bool LX_Renderer::set_alpha(SDL_Surface *image,Uint8 red, Uint8 green, Uint8 blue)
    {
        if(SDL_SetColorKey(image,SDL_TRUE, SDL_MapRGB(image->format,red,green,blue)) == -1)
            return false;

        return true;
    }



    /**
    *
    *   @fn void LX_Renderer::put_surface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos)
    *
    *   This function puts the surface on the main surface according to its position and the area to put on it
    *
    *   @param image : the surface to put
    *   @param area : the area of the surface to put on the screen
    *   @param pos : the position of what you want to put
    *
    *   @note If you do not need to determine the area parameter of the surface, put NULL
    *
    *   @return TRUE if the image was put with success, FALSE otherwise
    */
    bool LX_Renderer::put_surface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos)
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

        err = SDL_BlitSurface(image,area,mainWindow->getSurface(),&offset);

        if(err < 0)
            return false;

        return true;
    }


    /**
    *   @fn bool LX_Renderer::putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos)
    *
    *   This function puts the texture on the main window according to its position and the area to put on it
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
    bool LX_Renderer::putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos)
    {

        if(SDL_RenderCopy(renderer,origin,area,pos) < 0)
            return false;

        return true;
    }


    /**
    *   @fn void LX_Renderer::setWindowSize(int w, int h)
    *
    *   Set the size of the main window
    *
    *   @param w the width of the window
    *   @param h the height of the window
    *
    */
    void LX_Renderer::setWindowSize(int w, int h)
    {
        SDL_SetWindowSize(mainWindow->getWindow(),w,h);
    }


    /**
    *   @fn void LX_Renderer::setFullscreen(Uint32 flag)
    *
    *   Set the fullscreen to the main window
    *
    *   @param flag the flag you want to use in this function
    *
    */
    void LX_Renderer::setFullscreen(Uint32 flag)
    {
        SDL_SetWindowFullscreen(mainWindow->getWindow(),flag);

        if(flag == LX_GRAPHICS_NO_FULLSCREEN)   // set the window at the original size
        {
            setWindowSize(originalWidth,originalHeight);
        }
    }




    /**
    *   @fn void LX_Renderer::updateRenderer()
    *
    *   Updates the main renderer
    *
    */
    void LX_Renderer::updateRenderer()
    {
        SDL_RenderPresent(renderer);
    }


    /**
    *
    *   @fn void LX_Renderer::updateWindow()
    *
    *   This function updates the main window
    *
    */
    void LX_Renderer::updateWindow()
    {
        SDL_UpdateWindowSurface(mainWindow->getWindow());
    }

    /**
    *
    *   @fn void LX_Renderer::clearWindow()
    *
    *   This function clears the main window
    *
    */
    void LX_Renderer::clearWindow()
    {
        SDL_FillRect(mainWindow->getSurface(),NULL, SDL_MapRGB(mainWindow->getSurface()->format,0,0,0));
    }


    /**
    *
    *   @fn void LX_Renderer::clearRenderer()
    *
    *   This function clears the main renderer
    *
    */
    void LX_Renderer::clearRenderer()
    {
        SDL_RenderClear(renderer);
    }


    /**
    *   @fn SDL_Surface * LX_Renderer::getSurface()
    *
    *   Returns the surface of the main window
    *
    *   @return the main surface
    *
    **/
    SDL_Surface * LX_Renderer::getSurface()
    {
        return mainWindow->getSurface();
    }


    /**
    *   @fn SDL_Renderer * LX_Renderer::getRenderer()
    *
    *   Returns the renderer of the main window
    *
    *   @return the main renderer
    *
    */
    SDL_Renderer * LX_Renderer::getRenderer()
    {
        return mainWindow->getRenderer();
    }


};


















