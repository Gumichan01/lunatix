

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
*	@file LX_ttf.cpp
*	@brief The LunatiX_engine True type Font (TTF) modules.
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 15th, 2014
*
*
*
*/

#include "LX_ttf.h"

/**
*
*   @fn bool LX_ttf::draw_SolidText(char *string, SDL_Rect *pos)
*
*   Render the UTF-8 encoded text in solid mode
*
*   @param text the text you want to display
*   @param pos the position of the text on the screen
*
*   @return TRUE if it is ok, FALSE otherwise
*
*/
bool LX_ttf::draw_SolidText(std::string text, SDL_Rect *pos)
{
    SDL_Surface *loaded;
    int err;

    loaded = TTF_RenderUTF8_Solid(font,text.c_str(), font_color);

    if( loaded == NULL)
    {
        fprintf(stderr,"\nError occured in LX_ttf::draw_SolidText : %s \n", TTF_GetError());
        return false;
    }

    err = SDL_BlitSurface(loaded,NULL,screen,pos);

    if(err)
    {
        fprintf(stderr,"\nError occurred in LX_ttf::draw_SolidText : %s",SDL_GetError());
        return false;
    }

    SDL_FreeSurface(loaded);

    return true;
}


/**
*
*   @fn bool LX_ttf::draw_ShadedText(std::string text, SDL_Rect *pos)
*
*   Render the UTF-8 encoded text in shaded mode
*
*   @param text the text you want to display
*   @param pos the position of the text on the screen
*
*   @return TRUE if it is ok, FALSE otherwise
*
*/
bool LX_ttf::draw_ShadedText(std::string text, SDL_Rect *pos)
{
    SDL_Surface *loaded;
    int err;
    SDL_Color grey={127,127,127};

    loaded = TTF_RenderUTF8_Shaded(font,text.c_str(), font_color, grey);

    if( loaded == NULL)
    {
        fprintf(stderr,"\nError occured in LX_ttf::draw_ShadedText : %s \n", TTF_GetError());
        return false;
    }

    err = SDL_BlitSurface(loaded,NULL,screen,pos);

    if(err)
    {
        fprintf(stderr,"\nError occurred in LX_ttf::draw_ShadedText : %s",SDL_GetError());
        return false;
    }

    SDL_FreeSurface(loaded);

    return true;
}


/**
*
*   @fn bool LX_ttf::draw_BlendedText(std::string text, SDL_Rect *pos)
*
*   Render the UTF-8 encoded text in blended mode
*
*   @param text the text you want to display
*   @param pos the position of the text on the screen
*
*   @return TRUE if it is ok, FALSE otherwise
*
*/
bool LX_ttf::draw_BlendedText(std::string text, SDL_Rect *pos)
{
    SDL_Surface *loaded;
    int err;

    loaded = TTF_RenderUTF8_Blended(font,text.c_str(), font_color);

    if( loaded == NULL)
    {
        fprintf(stderr,"\nError occured in LX_ttf::draw_BlendedText : %s \n", TTF_GetError());
        return false;
    }

    err = SDL_BlitSurface(loaded,NULL,screen,pos);

    if(err)
    {
        fprintf(stderr,"\nError occurred in LX_ttf::draw_BlendedText : %s",SDL_GetError());
        return false;
    }

    SDL_FreeSurface(loaded);

    return true;
}

/**
*
*   @fn bool LX_ttf::draw_SolidText_WithSize(std::string text, unsigned int size, SDL_Rect *pos)
*
*   Render the UTF-8 encoded text in solid mode. The size has to be specified.
*
*   @param text the text you want to display
*   @param size the size defined by the user
*   @param pos the position of the text on the screen
*
*   @return TRUE if it is ok, FALSE otherwise
*
*/
bool LX_ttf::draw_SolidText_WithSize(std::string text, unsigned int size, SDL_Rect *pos)
{
    TTF_Font *ttf;
    SDL_Surface *loaded;
    int err;


    ttf = TTF_OpenFont(font_str.c_str(), size);

    if(ttf == NULL)
    {
        fprintf(stderr,"\nError occured in LX_ttf::draw_SolidText_WithSize, sorry, I cannot open the font : %s \n", TTF_GetError());
        return false;
    }


    loaded = TTF_RenderUTF8_Solid(ttf,text.c_str(), font_color);

    if( loaded == NULL)
    {
        fprintf(stderr,"\nError occured in LX_ttf::draw_SolidText_WithSize : %s \n", TTF_GetError());
        return false;
    }

    err = SDL_BlitSurface(loaded,NULL,screen,pos);

    if(err)
    {
        fprintf(stderr,"\nError occurred in LX_ttf::draw_SolidText_WithSize : %s",SDL_GetError());
        return false;
    }

    SDL_FreeSurface(loaded);
    TTF_CloseFont(ttf);

    return true;
}



/**
*
*   @fn bool bool LX_ttf::draw_ShadedText_WithSize(std::string text, unsigned int size, SDL_Rect *pos)
*
*   Render the UTF-8 encoded text in solid mode. The size has to be specified.
*
*   @param text the text you want to display
*   @param size the size defined by the user
*   @param pos the position of the text on the screen
*
*   @return TRUE if it is ok, FALSE otherwise
*
*/
bool LX_ttf::draw_ShadedText_WithSize(std::string text, unsigned int size, SDL_Rect *pos)
{
    TTF_Font *ttf;
    SDL_Surface *loaded;
    int err;
    SDL_Color grey={127,127,127};

    ttf = TTF_OpenFont(font_str.c_str(), size); //Open the font

    if(ttf == NULL)
    {
        fprintf(stderr,"\nError occured in LX_ttf::draw_ShadedText_WithSize, sorry, I cannot open the font : %s \n", TTF_GetError());
        return false;
    }


    loaded = TTF_RenderUTF8_Shaded(ttf,text.c_str(), font_color, grey); //load the text into a surface

    if( loaded == NULL)
    {
        fprintf(stderr,"\nError occured in LX_ttf::draw_ShadedText_WithSize : %s \n", TTF_GetError());
        return false;
    }

    err = SDL_BlitSurface(loaded,NULL,screen,pos);

    if(err)
    {
        fprintf(stderr,"\nError occurred in LX_ttf::draw_ShadedText_WithSize : %s",SDL_GetError());
        return false;
    }

    SDL_FreeSurface(loaded);
    TTF_CloseFont(ttf);

    return true;
}


/**
*
*   @fn bool LX_ttf::draw_BlendedText_WithSize(std::string text, unsigned int size, SDL_Rect *pos)
*
*   Render the UTF-8 encoded text in solid mode. The size has to be specified.
*
*   @param text the text you want to display
*   @param size the size defined by the user
*   @param pos the position of the text on the screen
*
*   @return TRUE if it is ok, FALSE otherwise
*
*/
bool LX_ttf::draw_BlendedText_WithSize(std::string text, unsigned int size, SDL_Rect *pos)
{
    TTF_Font *ttf;
    SDL_Surface *loaded;
    int err;


    ttf = TTF_OpenFont(font_str.c_str(), size);

    if(ttf == NULL)
    {
        fprintf(stderr,"\nError occured in LX_ttf::draw_SolidText_WithSize, sorry, I cannot open the font : %s \n", TTF_GetError());
        return false;
    }


    loaded = TTF_RenderUTF8_Solid(ttf,text.c_str(), font_color);

    if( loaded == NULL)
    {
        fprintf(stderr,"\nError occured in LX_ttf::draw_SolidText_WithSize : %s \n", TTF_GetError());
        return false;
    }

    err = SDL_BlitSurface(loaded,NULL,screen,pos);

    if(err)
    {
        fprintf(stderr,"\nError occurred in LX_ttf::draw_SolidText_WithSize : %s",SDL_GetError());
        return false;
    }

    SDL_FreeSurface(loaded);
    TTF_CloseFont(ttf);

    return true;
}










/**
*
*   @fn bool LX_ttf::setTTF_filename(std::string ttf_filename)
*
*   This function sets the name of the ttf file which will be used.
*
*   @param ttf_filename the new name
*
*   @return TRUE if it is ok, FALSE otherwise
*
*/
bool LX_ttf::setTTF_filename(std::string ttf_filename)
{
    if(!ttf_filename.empty() )
    {
        font_str.clear();

        font_str.assign(ttf_filename);

        return true;
    }

    return false;
}


/**
*
*   @fn bool LX_ttf::setColor(SDL_Color *color)
*
*   This function sets the new color of texts.
*
*   @param color the new color
*
*   @return TRUE if it is ok, FALSE otherwise
*
*/
bool LX_ttf::setColor(SDL_Color *color)
{
    if( color != NULL )
    {
        font_color.r = color->r;
        font_color.g = color->g;
        font_color.b = color->b;

        return true;
    }
    return false;
}





























