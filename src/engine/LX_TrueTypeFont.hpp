#ifndef LX_TTF_H_INCLUDED
#define LX_TTF_H_INCLUDED



/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_TrueTypeFont.hpp
*	@brief The LunatiX Engine True type Font (TTF) library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <iostream>

#include <SDL2/SDL_ttf.h>

#define LX_TTF_DEFAULT_FONT_SIZE 24     /**< The default value of the font size */
#define LX_WHITE_COLOR 255              /**< The white color value */
#define LX_BLACK_COLOR 0                /**< The black color value */


struct SDL_Surface;
struct SDL_Texture;
struct SDL_Color;


namespace LX_Graphics
{

class LX_Window;

};


namespace LX_FileIO
{

class LX_FileBuffer;

};


using namespace std;
using namespace LX_Graphics;
using namespace LX_FileIO;

/**
*   @namespace LX_TrueTypeFont
*   @brief The LunatiX Engine True Type Font (TTF) module
*
*/
namespace LX_TrueTypeFont
{

/**
*   @enum LX_TTF_TypeText
*   @brief The type of text enumeration
*
*   This enumeration describes the type of the text you want to draw.
*
*   LX_TTF_SOLID : Quick and dirty text
*   LX_TTF_SHADED : Slow and nice text
*   LX_TTF_BLENDED : Very slow but very nice text
*
*/
typedef enum {LX_TTF_SOLID,LX_TTF_SHADED,LX_TTF_BLENDED} LX_TTF_TypeText;



/**
*   @class LX_Font
*   @brief The Font class.
*
*   This class describes the font. It manages the True type Font.
*
*   @note It supports the UTF-8 format
*
*/
class LX_Font
{

    string font_str;            /**< The font file */
    unsigned int font_size;     /**< The font size */
    SDL_Color font_color;       /**< The font color */
    LX_FileBuffer *font_buffer;


    void init(string font_file, SDL_Color *color, int size);
    SDL_Surface * drawText(LX_TTF_TypeText type, string text, Uint8 r, Uint8 g, Uint8 b, unsigned int size);

public:

    LX_Font(SDL_Color *color);
    LX_Font(string font_file, SDL_Color *color);
    LX_Font(string font_file, SDL_Color *color, int size);

    int sizeOfText(string text, int *w, int *h);
    int sizeOfText(string text, int size, int *w, int *h);
    int sizeOfText(TTF_Font *ttf, string text, int *w, int *h);

    SDL_Surface * drawSolidText(string text);
    SDL_Surface * drawSolidText(string text, unsigned int size);

    SDL_Surface * drawShadedText(string text, SDL_Color bg);
    SDL_Surface * drawShadedText(string text, Uint8 r, Uint8 g, Uint8 b);
    SDL_Surface * drawShadedText(string text, Uint8 r, Uint8 g, Uint8 b, unsigned int size);

    SDL_Surface * drawBlendedText(string text);
    SDL_Surface * drawBlendedText(string text, unsigned int size);

    SDL_Texture * drawTextToTexture(LX_TTF_TypeText type,string text, unsigned int size, int idWindow);
    SDL_Texture * drawTextToTexture(LX_TTF_TypeText type,string text, unsigned int size, LX_Window *win);

    void setColor(SDL_Color *color);

    ~LX_Font();

};


};


#endif // LX_TTF_H_INCLUDED



