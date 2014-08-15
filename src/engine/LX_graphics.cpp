

/*
*
*	Copyright (C)  Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*
*/

/**
*	@file LX_graphics.cpp
*	@brief The LunatiX_engine graphic module
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 13th, 2014
*
*
*
*/
#include "LX_graphics.h"



/**
*   @fn LX_graphics * LX_graphics::getInstance()
*
*   Get the unique instance of the LX_graphics class
*
*   @return the instance of LX_graphics
*
*/
LX_graphics * LX_graphics::getInstance()
{
    static LX_graphics *instance = NULL;

    if(instance == NULL)
    {
        instance = new LX_graphics();
    }

    return instance;
}




/**
*
*   @fn SDL_Surface * LX_graphics::load_BMP(char *filename)
*
*   This function loads an SDL_Surface from a .bmp file an optimizes its format
*
*   @param filename : the .bmp file name which describe the image
*
*   @return the surface loaded and optimized, NULL otherwise
*
*   @warning If you try to load an other imge file with this function, it will fail.
*
*/
SDL_Surface * LX_graphics::load_BMP(std::string filename)
{
    SDL_Surface *loaded = NULL;
    SDL_Surface *optimized = NULL;

    loaded = SDL_LoadBMP(filename.c_str());

    if(loaded == NULL)
    {
        fprintf(stderr,"\nException occurred in LX_graphics::load_BMP : %s",SDL_GetError());
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
*   @return the surface loaded and optimized, NULL otherwise
*
*   @note You may use this function instead of load_BMP to load a non BMP surface.
*   @warning 1. When you call this function, the format optimization includes the alpha canal.
*                   No transparency can be put on the surface after that
*   @warning 2. If you want to load a bmp file and use the transparency, you should call load_BMP() instead of it and put_transparency()
*
*/
SDL_Surface * LX_graphics::load_image(std::string filename)
{
    SDL_Surface *loaded = NULL;
    SDL_Surface *optimized = NULL;

    loaded = IMG_Load(filename.c_str());

    if(loaded == NULL)
    {
        fprintf(stderr,"\nException occurred in LX_graphics::load_image : %s",SDL_GetError());
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
*   @param red : the the red color canal which go to be transparent
*   @param green : the the green color canal which go to be transparent
*   @param blue : the the blue color canal which go to be transparent
*
*   @return TRUE if all was done without problem, FALSE otherwise
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
        fprintf(stderr,"\nException occurred in LX_graphics::put_transparency : I cannot load the image : %s",SDL_GetError());
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
*   @return TRUE if all is ok, FALSE otherwise
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
        fprintf(stderr,"\nException occurred in LX_graphics::put_image : %s",SDL_GetError());
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
*   This function clear the screen
*
*/
void LX_graphics::clear()
{
    SDL_FillRect(screen,NULL, SDL_MapRGB(screen->format,0,0,0));
    //SDL_FillRect(screen,NULL, SDL_MapRGB(screen->format,100,100,100));
}




























