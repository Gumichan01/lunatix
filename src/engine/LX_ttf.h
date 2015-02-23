#ifndef LX_TTF_H_INCLUDED
#define LX_TTF_H_INCLUDED



/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
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

#define LX_DEFAULT_FONT_SIZE 24    /**< The default value of the font size, used when the size defined in the configuration file is 0*/
#define LX_WHITE_COLOR 255
#define LX_BLACK_COLOR 0

typedef enum{LX_TTF_SOLID,LX_TTF_SHADED,LX_TTF_BLENDED} LX_TTF_TypeText;

/**
*   @class LX_TTF_exception
*   @brief The LX_TTF_exception class.
*
*   This class describes the exception occured when the font loading fails.
*
*/
class LX_TTF_exception : public std::exception
{
    public :

    std::string str_err;                        /**< The string where the error message will be conteined*/

    LX_TTF_exception(std::string err);

    const char * what() const throw();

    ~LX_TTF_exception() throw();
};

/// @todo [LX_ttf]Load a texture from a files

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

    std::string font_str;       /**< The font file */
    unsigned int font_size;     /**< The font size */
    SDL_Color font_color;       /**< The font color */

    TTF_Font *font;             /**< The font structure created */


    void init(std::string font_file, SDL_Color *color, int size);
    SDL_Surface * drawText(LX_TTF_TypeText type, std::string text, Uint8 r, Uint8 g, Uint8 b, unsigned int size);

    public:

    LX_ttf(SDL_Color *color);
    LX_ttf(std::string font_file, SDL_Color *color);
    LX_ttf(std::string font_file, SDL_Color *color, int size);

    int sizeOfText(std::string text, int *w, int *h);
    int sizeOfText(TTF_Font *ttf, std::string text, int *w, int *h);

    SDL_Surface * draw_SolidText(std::string text);
    SDL_Surface * draw_SolidText(std::string text, unsigned int size);

    SDL_Surface * draw_ShadedText(std::string text, SDL_Color bg);
    SDL_Surface * draw_ShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b);
    SDL_Surface * draw_ShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b, unsigned int size);

    SDL_Surface * draw_BlendedText(std::string text);
    SDL_Surface * draw_BlendedText(std::string text, unsigned int size);

    void setTTF_Font(std::string ttf_filename);
    void setColor(SDL_Color *color);

    ~LX_ttf();

};


#endif // LX_TTF_H_INCLUDED














