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


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "LX_config.h"

#define DEFAULT_FONT_SIZE 24    /**<The default value of the font size, used when the size defined in the configuration file is 0*/



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

/**
*   @fn LX_OpenFont_exception(std::string err)
*   Build the LX_OpenFont_exception class
*   @param err the error string
*/
    LX_OpenFont_exception(std::string err)
    {
        str_err = err;
    }

/**
*   @fn const char * what() const throw()
*   Get the error string
*   @return the error string
*/
    const char * what() const throw() {return str_err.c_str() ;}

    ~LX_OpenFont_exception() throw(){}
};




/**
*   @class LX_ttf
*   @brief The LunatiX_engine True type Font (TTF) module.
*
*   This class describes the LX_ttf library. It manages the True type Font.
*
*   @note This class supports the UTF-8 format
*
*/
class LX_ttf{

    std::string font_str;       /**< The font file*/
    unsigned int font_size;     /**< The font size*/
    SDL_Color font_color;       /**< The font color*/

    TTF_Font *font;             /**< The font structure created*/

/**
*
*   @fn LX_ttf(SDL_Color *color)
*
*   This constructor initializes The LX_TTF module.
*
*   @param color the default color font
*
*   @note If you do not need to specify the font color, you may put NULL instead of this color
*   @warning You must initialize the SDL_TTF library putting the ttf flag to 1 in sdl_conf.cfg.
*            Otherwise, a LX_OpenFont_exception will be occured.
*   @warning A LX_OpenFont_exception may also be occured if thefilename or the font size is invalid
*
*/
    LX_ttf(SDL_Color *color)
    {
        font = NULL;

        // load the configuration
        LX_configuration *ttf_config = LX_configuration::getInstance();

        font_str = ttf_config->getFontFile();
        font_size = ttf_config->getFontSize();

        ttf_config->destroy();

        if(font_size == 0)
        {
             font_size = DEFAULT_FONT_SIZE;
        }

        font = TTF_OpenFont(font_str.c_str(), font_size);

        if(font == NULL)
        {
            throw LX_OpenFont_exception(TTF_GetError());
        }

        //put color if it is not null
        if( color != NULL )
        {
            font_color.r = color->r;
            font_color.g = color->g;
            font_color.b = color->b;
        }
        else
        {
            font_color.r = 127;
            font_color.g = 127;
            font_color.b = 127;
        }

    }


    public:

    //get the instance
    static LX_ttf * getInstance();
    static void destroy();

    SDL_Surface * draw_SolidText(std::string text);
    SDL_Surface * draw_ShadedText(std::string text);
    SDL_Surface * draw_BlendedText(std::string text);

    SDL_Surface * draw_SolidText_WithSize(std::string text, unsigned int size);
    SDL_Surface * draw_ShadedText_WithSize(std::string text, unsigned int size);
    SDL_Surface * draw_BlendedText_WithSize(std::string text, unsigned int size);

    bool setTTF_filename(std::string ttf_filename);
    bool setColor(SDL_Color *color);

    ~LX_ttf()
    {
        TTF_CloseFont(font);
    }

};


#endif // LX_TTF_H_INCLUDED














