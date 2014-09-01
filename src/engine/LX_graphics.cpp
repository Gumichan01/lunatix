

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
*	@file LX_graphics.cpp
*	@brief The LunatiX_engine graphic module
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 13th, 2014
*
*
*/
#include "LX_graphics.h"


static LX_graphics *gInstance = NULL;

/**
*   @fn LX_graphics * LX_graphics::getInstance()
*
*   Get the unique instance of the LX_graphics class
*
*   @return the unique instance of LX_graphics
*
*/
LX_graphics * LX_graphics::getInstance()
{
    if(gInstance == NULL)
    {
        try
        {
            gInstance = new LX_graphics();
        }
        catch(std::exception & g_ex)
        {
            std::cerr << "exception occured in LX_graphics::getInstance : " << g_ex.what() << std::endl;
            return NULL;
        }
    }

    return gInstance;
}


/**
*
*   @fn void LX_graphics::destroy()
*
*   Destroy the unique instance
*
*   @warning you must call this function to prevent a memory leak if you called LX_graphics::getInstances()
*
*/
void LX_graphics::destroy()
{
    delete gInstance;
    gInstance = NULL;
}



/**
*
*   @fn SDL_Surface * LX_graphics::load_BMP(char *filename)
*
*   This function loads an SDL_Surface from a .bmp file an optimizes its format
*
*   @param filename : the .bmp file name which describe the image
*
*   @return the loaded and optimized surface if there is no problem, NULL otherwise
*
*   @warning If you try to load an other image file with this function, it will fail.
*
*/
SDL_Surface * LX_graphics::load_BMP(std::string filename)
{
    SDL_Surface *loaded = NULL;
    SDL_Surface *optimized = NULL;

    loaded = SDL_LoadBMP(filename.c_str());

    if(loaded == NULL)
    {
        std::cerr << "Error occurred in LX_graphics::load_BMP : " << SDL_GetError() << std::endl;
        return NULL;
    }

    optimized = SDL_DisplayFormat(loaded);

    SDL_FreeSurface(loaded);

    return optimized;
}


/**
*
*   @fn SDL_Surface * LX_graphics::load_image(char *filename)
*
*   This function loads an SDL_Surface from any image file an optimized its format
*
*   @param filename : the file name which describe the image
*
*   @return the loaded and optimized surface if there is no problem, NULL otherwise
*
*   @note You may use this function instead of load_BMP() to load a non .bmp file
*   @note If you want to load a .bmp file and use the transparency, please use load_BMP() and put_transparency()
*
*   @warning When you call this function, the format optimization includes the alpha canal.
*                   No transparency can be put on the surface after that
*
*/
SDL_Surface * LX_graphics::load_image(std::string filename)
{
    SDL_Surface *loaded = NULL;
    SDL_Surface *optimized = NULL;

    loaded = IMG_Load(filename.c_str());

    if(loaded == NULL)
    {
        std::cerr << "Error occurred in LX_graphics::load_image : " << SDL_GetError() << std::endl;
        return NULL;
    }

    optimized = SDL_DisplayFormatAlpha(loaded);

    SDL_FreeSurface(loaded);

    return optimized;
}


/**
*
*   @fn bool LX_graphics::put_transparency(SDL_Surface *image,unsigned int red, unsigned int green, unsigned int blue)
*
*   This function put the transparency on a SDL_surface
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
bool LX_graphics::put_transparency(SDL_Surface *image,unsigned int red, unsigned int green, unsigned int blue)
{

    Uint32 colorkey = SDL_MapRGB(image->format,red,green,blue);

    int err = SDL_SetColorKey(image,SDL_RLEACCEL|SDL_SRCCOLORKEY, colorkey);

    if(err == -1)
    {
        std::cerr << "Error occurred in LX_graphics::put_transparency : " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}



/**
*
*   @fn void LX_graphics::put_image(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos)
*
*   This function puts the surface on the screen according to its position and the area to put on it
*
*   @param image : the surface to put
*   @param area : the area of the surface to put on the screen
*   @param pos : the position of what you want to put
*
*   @note If you do not need to determine the area parameter of the surface, put NULL
*
*   @return TRUE if the image was put with success, FALSE otherwise
*/
bool LX_graphics::put_image(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos)
{
   int err;

    if(image == NULL)
    {
        std::cout << "image NULL" << std::endl;
    }

    if(screen == NULL)
    {
        std::cout << "screen NULL" << std::endl;
    }

   err = SDL_BlitSurface(image,area,screen,pos);

    if(err != 0)
    {
        std::cerr << "Error occurred in LX_graphics::put_image : " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

/**
*
*   @fn void LX_graphics::update()
*
*   This function update the screen display
*
*/
void LX_graphics::update()
{
    SDL_Flip(screen);
}

/**
*
*   @fn void LX_graphics::clear()
*
*   This function clears the screen
*
*/
void LX_graphics::clear()
{
    SDL_FillRect(screen,NULL, SDL_MapRGB(screen->format,0,0,0));
}




























