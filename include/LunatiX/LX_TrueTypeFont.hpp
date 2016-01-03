#ifndef LX_TTF_H_INCLUDED
#define LX_TTF_H_INCLUDED


/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_TrueTypeFont.hpp
*	@brief The LunatiX Engine True type Font (TTF) library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.7
*
*/

#include <string>
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



/**
*   @namespace LX_TrueTypeFont
*   @brief The LunatiX Engine True Type Font (TTF) module
*/
namespace LX_TrueTypeFont
{

/**
*   @enum LX_TTF_TypeText
*   @brief The type of text
*
*   This enumeration describes the type of the text to draw :
*    - LX_TTF_SOLID : Quick rendering and dirty text
*    - LX_TTF_SHADED : Slow rendering and nice text
*    - LX_TTF_BLENDED : Very slow rendering but very nice text
*
*/
typedef enum LX_TTF_TypeText {LX_TTF_SOLID,LX_TTF_SHADED,LX_TTF_BLENDED} LX_TTF_TypeText;


/**
*   @class LX_Font
*   @brief The Font class
*
*   This class describes the font. It manages the True type Font.
*
*   @note It supports the UTF-8 format
*
*/
class LX_Font
{
    std::string font_str;                   /* The font file    */
    unsigned int font_size;                 /* The font size    */
    SDL_Color font_color;                   /* The font color   */
    LX_FileIO::LX_FileBuffer *font_buffer;

    LX_Font(LX_Font& f);
    LX_Font& operator =(LX_Font& f);

    void createbuffer();
    int sizeOfText(TTF_Font *ttf, std::string text, int& w, int& h);
    TTF_Font * createInternalFont(int size);

    SDL_Surface * drawText(LX_TTF_TypeText type, std::string text,
                           unsigned int size = 0,
                           Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);

public:

    LX_Font(const SDL_Color& color, unsigned int size=0);
    LX_Font(std::string font_file,const SDL_Color& color);
    LX_Font(std::string font_file,const SDL_Color& color, unsigned int size);

    int sizeOfText(std::string text, int& w, int& h);
    int sizeOfText(std::string text, unsigned int size, int& w, int& h);

    SDL_Surface * drawSolidText(std::string text);
    SDL_Surface * drawSolidText(std::string text, unsigned int size);

    SDL_Surface * drawShadedText(std::string text, SDL_Color bg);
    SDL_Surface * drawShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b);
    SDL_Surface * drawShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b,
                                 unsigned int size);

    SDL_Surface * drawBlendedText(std::string text);
    SDL_Surface * drawBlendedText(std::string text, unsigned int size);

    SDL_Texture * drawTextToTexture(LX_TTF_TypeText type, std::string text,
                                    unsigned int size, unsigned int idWindow = 0);
    SDL_Texture * drawTextToTexture(LX_TTF_TypeText type, std::string text,
                                    unsigned int size, LX_Graphics::LX_Window *win);

    void setColor(SDL_Color *color);

    ~LX_Font();
};

};

#endif // LX_TTF_H_INCLUDED

