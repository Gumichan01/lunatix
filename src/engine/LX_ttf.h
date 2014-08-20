#ifndef LX_TTF_H_INCLUDED
#define LX_TTF_H_INCLUDED



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
*	@file LX_ttf.h
*	@brief The LX_ttf library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 15th, 2014
*
*
*
*/


#include <cstring>
#include <string>

#include <iostream>
#include <exception>

#include<SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#define DEFAULT_FONT_SIZE 24    /**<The default value of the font size*/



/**
*   @class LX_OpenFont_exception
*   @brief The LX_OpenFont_exception class.
*
*   This class describes the exception occured when the font loading fails.
*
*/
class LX_OpenFont_exception : public std::exception
{
    public :

    std::string str_err;                        /**< The string where the error message will be conteined*/

    LX_OpenFont_exception( std::string err)
    {
        str_err = err;
    }

    const char * what() const throw() {return str_err.c_str() ;}

    ~LX_OpenFont_exception() throw(){}
};




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

    SDL_Surface *screen;

    TTF_Font *font;

    public:

/**
*
*   @fn LX_ttf(std::string ttf_filename, unsigned int size, SDL_Color *color)
*
*   This constructor initializes The LX_TTF module.
*
*   @param ttf_filename the name of the .ttf file
*   @param size the default size of the font when it will be displayed
*   @param color the default color font
*
*   @note If you do not need to specify the font file name, you may put NULL instead of the file name
*   @note If you do not need to specify the font color, you may put NULL instead of this color
*   @note If the size value is 0, size get the default value, defined by DEFAULT_FONT_SIZE
*
*   @warning If you put NULL in window, a LX_FONT_SCREEN_ERROR exception will be occured
*
*/
    LX_ttf(std::string ttf_filename, unsigned int size, SDL_Color *color)
    {

        if(size != 0)
            size_font = size;
        else
            size_font = DEFAULT_FONT_SIZE;

        if(!ttf_filename.empty())
        {
            font_str.assign(ttf_filename);

            font = TTF_OpenFont(font_str.c_str(), size_font);

            if(font == NULL)
            {
                throw LX_OpenFont_exception(TTF_GetError());
            }
        }

        std::cout << " str : " << font_str.c_str() << std::endl;

        if( color != NULL )
        {
            font_color.r = color->r;
            font_color.g = color->g;
            font_color.b = color->b;
        }

        SDL_EnableUNICODE(SDL_ENABLE);
    }



    SDL_Surface * draw_SolidText(std::string text);
    SDL_Surface * draw_ShadedText(std::string text);
    SDL_Surface * draw_BlendedText(std::string text);

    bool draw_SolidText_WithSize(std::string text, unsigned int size, SDL_Rect *pos);
    bool draw_ShadedText_WithSize(std::string text, unsigned int size, SDL_Rect *pos);
    bool draw_BlendedText_WithSize(std::string text, unsigned int size, SDL_Rect *pos);

    bool setTTF_filename(std::string ttf_filename);
    bool setColor(SDL_Color *color);

    ~LX_ttf()
    {
        SDL_EnableUNICODE(SDL_DISABLE);

        TTF_CloseFont(font);
    }

};




#endif // LX_TTF_H_INCLUDED














