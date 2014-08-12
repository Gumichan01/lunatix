#ifndef LX_TTF_H_INCLUDED
#define LX_TTF_H_INCLUDED



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
*	@file LX_ttf.h
*	@brief The LX_ttf library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 15th, 2014
*
*
*
*/

#include <SDL/SDL_ttf.h>
#include <cstring>
#include <string>

#include "LX_error.h"

#define DEFAULT_FONT_SIZE 24    /**<The default value of the font size*/

/**
*   @class LX_ttf
*   @brief The LunatiX_engine True type Font (TTF) module.
*
*   This class describes the LX_ttf library. It manages the True type Font.
*
*   @note This class supports UTF-8
*
*/
class LX_ttf{

    std::string font_str;
    unsigned int size_font;
    SDL_Color font_color;

    TTF_Font *font;

    SDL_Surface *screen;

    public:

/**
*
*   @fn LX_ttf(std::string ttf_filename, unsigned int size, SDL_Color *color, SDL_Surface *window )
*
*   This constructor initializes The SDL_TTF plugin.
*
*   @param ttf_filename the name of the .ttf file
*   @param size the default size of the font when it will be displayed
*   @param color the default color font
*   @param window the window where will be put the font, generally the LX_graphics object's screen
*
*   @note If you do not need to specify the font file name, you may put NULL instaed of the file name
*   @note If you do not need to specify the font color, you may put NULL instead of this color
*   @note If the size value is 0, size get the default value, defined by DEFAULT_FONT_SIZE
*
*   @warning If you put NULL in window, a LX_FONT_SCREEN_ERROR exception will be occured
*
*/
    LX_ttf(std::string ttf_filename, unsigned int size, SDL_Color *color, SDL_Surface *window )
    {

        if(TTF_Init() == -1)
        {
            fprintf(stderr,"\nException occured in LX_graphics constructor, TTF_Init : %s \n", SDL_GetError());
            throw LX_TTF_INIT_ERROR;
        }

        if(!ttf_filename.empty())
            font_str.assign(ttf_filename);

        if(size != 0)
            size_font = size;
        else
            size_font = DEFAULT_FONT_SIZE;


        font = TTF_OpenFont(font_str.c_str(), size_font);

        if(font == NULL)
        {
            fprintf(stderr,"\nException occured in LX_graphics constructor, TTF_OpenFont : %s \n", TTF_GetError());
            throw LX_FONT_ERROR;
        }

        if( color != NULL )
        {
            font_color.r = color->r;
            font_color.g = color->g;
            font_color.b = color->b;
        }


        if(window ==NULL)
        {
            fprintf(stderr,"\nException occured in LX_graphics constructor : No screen has been defined \n");
            TTF_CloseFont(font);
            TTF_Quit();

            throw LX_FONT_SCREEN_ERROR;
        }

        screen = window;

        SDL_EnableUNICODE(SDL_ENABLE);
    }



    bool draw_SolidText(std::string text, SDL_Rect *pos);
    bool draw_ShadedText(std::string text, SDL_Rect *pos);
    bool draw_BlendedText(std::string text, SDL_Rect *pos);

    bool draw_SolidText_WithSize(std::string text, unsigned int size, SDL_Rect *pos);
    bool draw_ShadedText_WithSize(std::string text, unsigned int size, SDL_Rect *pos);
    bool draw_BlendedText_WithSize(std::string text, unsigned int size, SDL_Rect *pos);

    bool setTTF_filename(std::string ttf_filename);
    bool setColor(SDL_Color *color);

    ~LX_ttf()
    {
        SDL_EnableUNICODE(SDL_DISABLE);

        TTF_CloseFont(font);

        TTF_Quit();
    }

};




#endif // LX_TTF_H_INCLUDED














