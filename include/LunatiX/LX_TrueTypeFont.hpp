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
*	@version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <SDL2/SDL_ttf.h>

#define LX_TTF_DEFAULT_FONT_SIZE 24     /**< The default value of the font size */
#define LX_WHITE_COLOR 255              /**< The white color value */
#define LX_BLACK_COLOR 0                /**< The black color value */

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Color;

namespace LX_Win
{
class LX_Window;
};

namespace LX_FileIO
{
class LX_FileBuffer;
};

namespace LX_Graphics
{
class LX_TextImage;
}


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
*    - LX_TTF_SOLID   : Quick rendering and dirty text
*    - LX_TTF_SHADED  : Slow rendering and nice text
*    - LX_TTF_BLENDED : Very slow rendering but very nice text
*
*/
enum LX_TTF_TypeText: short {LX_TTF_SOLID,LX_TTF_SHADED,LX_TTF_BLENDED};


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
    UTF8string _font_str;                    /* The font file    */
    unsigned int _font_size;                 /* The font size    */
    SDL_Color _font_color;                   /* The font color   */
    LX_FileIO::LX_FileBuffer *_font_buffer;

    LX_Font(LX_Font& f);
    LX_Font& operator =(LX_Font& f);

    void createBuffer_();
    int sizeOfText_(TTF_Font *ttf, std::string text, int& w, int& h);
    TTF_Font * createInternalFont_(int size);

    SDL_Surface * drawText_(LX_TTF_TypeText type, std::string text,
                            unsigned int size = 0,
                            Uint8 r = 0, Uint8 g = 0, Uint8 b = 0,Uint8 a = 0);

public:

    /**
    *   @fn LX_Font(const SDL_Color& color, unsigned int size)
    *
    *   Construct the font with color and the size of the text
    *
    *   @param color The default color font
    *   @param size the size of the text
    *
    *   @note   If size is 0, then the default value defined in the configuratnion
    *           file is used.
    *
    *   @note   The constructor uses the configuration file to get the TTF file
    *
    *   @warning    You must initialize the SDL_TTF library
    *               setting the TTF flag to 1 in lxsdl.cfg.
    *
    *   @exception LX_FileIO::IOException if the file cannot be loaded
    *
    */
    LX_Font(const SDL_Color& color, unsigned int size=0);

    /**
    *   @fn LX_Font(std::string font_file,const SDL_Color& color)
    *
    *   Construct the font with font file and color
    *
    *   @param font_file The font file to use
    *   @param color The default color font
    *
    *   @warning    It is necessary to initialize the SDL_TTF library
    *               setting the TTF flag to 1 in lxsdl.cfg
    *
    *   @exception  LX_FileIO::IOException if the file cannot be loaded
    *
    */
    LX_Font(std::string font_file,const SDL_Color& color);

    /**
    *   @fn LX_Font(std::string font_file,const SDL_Color& color, unsigned int size)
    *
    *  Construct the font with a font file, a color and a size.
    *
    *   @param font_file The font file to load
    *   @param color The color font needed
    *   @param size The size of the text to display
    *
    *   @warning    It is necessary to initialize the SDL_TTF library setting
    *               the ttf flag to 1 in lxsdl.cfg.
    *
    *   @exception  LX_FileIO::IOException if the file cannot be loaded
    *
    */
    LX_Font(std::string font_file,const SDL_Color& color, unsigned int size);

    /**
    *   @fn int sizeOfText(std::string text, int& w, int& h)
    *
    *   Calculate the resulting texture dimension of the
    *   text rendererd using the default font
    *
    *   @param text The std::string to size up
    *   @param w The reference of an integral to fill in the text width
    *   @param h The reference of an integral to fill in the text height
    *
    *   @return A control value, 0 on success, -1 on failure
    *
    */
    int sizeOfText(std::string text, int& w, int& h);

    /**
    *   @fn int sizeOfText(std::string text, unsigned int size, int& w, int& h)
    *
    *   Calculate the resulting texture dimension of the
    *   text rendererd using the default font
    *
    *   @param text The std::string to size up
    *   @param size The size of the text
    *   @param w The reference of an integral to fill in the text width
    *   @param h The reference of an integral to fill in the text height
    *
    *   @return A control value, 0 on success, -1 on failure
    *
    */
    int sizeOfText(std::string text, unsigned int size, int& w, int& h);

    /**
    *   @fn SDL_Surface * drawSolidText(std::string text)
    *
    *   Create an UTF-8 encoded text in solid mode
    *
    *   @param text The std::string to display
    *
    *   @return An instance of SDL_Surface on success, a null pointer otherwise
    *
    */
    SDL_Surface * drawSolidText(std::string text);

    /**
    *   @fn SDL_Surface * drawSolidText(std::string text, unsigned int size)
    *
    *   Render the UTF-8 encoded text in solid mode. The size has to be specified
    *
    *   @param text The std::string to display
    *   @param size The size defined by the user
    *
    *   @return An instance of SDL_Surface on success, a null pointer otherwise
    *
    */
    SDL_Surface * drawSolidText(std::string text, unsigned int size);

    /**
    *   @fn SDL_Surface * drawShadedText(std::string text, SDL_Color bg)
    *
    *   Create an UTF-8 encoded text in shaded mode
    *
    *   @param text The std::string to display
    *   @param bg The background color
    *
    *   @return An instance of SDL_Surface on success, a null pointer otherwise
    *
    */
    SDL_Surface * drawShadedText(std::string text, SDL_Color bg);

    /**
    *   @fn SDL_Surface * drawShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b,
                                         Uint8 a)
    *
    *   Create an UTF-8 encoded text in shaded mode
    *
    *   @param text The text to display
    *   @param r The red channel
    *   @param g The green channel
    *   @param b The blue channel
    *   @param a The alpha channel
    *
    *   @return An instance of SDL_Surface on success, a null pointer otherwise
    *
    */
    SDL_Surface * drawShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /**
    *   @fn SDL_Surface * drawShadedText(std::string text, Uint8 r, Uint8 g,
    *                                             Uint8 b, Uint8 a, unsigned int size)
    *
    *   Render the UTF-8 encoded text in shaded mode. The size has to be specified.
    *
    *   @param text The text to display
    *   @param r The red color of the background
    *   @param g The green color of the background
    *   @param b The blue color of the background
    *   @param a The alpha channel
    *   @param size The size defined by the user
    *
    *   @return An instance of SDL_Surface on success, a null pointer otherwise
    *
    */
    SDL_Surface * drawShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b, Uint8 a,
                                 unsigned int size);

    /**
    *   @fn SDL_Surface * drawBlendedText(std::string text)
    *
    *   Create an UTF-8 encoded text surface in blended mode
    *
    *   @param text The text to display
    *
    *   @return An instance of SDL_Surface on success, a null pointer otherwise
    *
    */
    SDL_Surface * drawBlendedText(std::string text);

    /**
    *   @fn SDL_Surface * drawBlendedText(std::string text, unsigned int size)
    *
    *   Render the UTF-8 encoded text in blended mode. The size has to be specified.
    *
    *   @param text The text to display
    *   @param size The size defined by the user
    *
    *   @return An instance of SDL_Surface on success, a null pointer otherwise
    *
    */
    SDL_Surface * drawBlendedText(std::string text, unsigned int size);

    /**
    *   @fn SDL_Texture * drawTextToTexture(LX_TTF_TypeText type,
    *                                                std::string text, unsigned int size,
    *                                                unsigned int idWindow)
    *
    *   Create a Texture from a text according to the type and the size
    *
    *   @param type The type of the text(Solid, Shaded, or Blended)
    *   @param text The std::string to draw
    *   @param size The size of the text on the window
    *   @param idWindow The ID of the window to get the renderer from.
    *                   Optional argument
    *
    *   @return An instance of SDL_Texture on success, a null pointer
    *           if the window is not valid or if something wrong happened
    *
    */
    SDL_Texture * drawTextToTexture(LX_TTF_TypeText type, std::string text,
                                    unsigned int size, unsigned int idWindow = 0);

    /**
    *   @fn SDL_Texture * drawTextToTexture(LX_TTF_TypeText type,
    *                                                std::string text,
    *                                                unsigned int size,
    *                                                LX_Win::LX_Window *win)
    *
    *   Create a Texture from a text according to the type and the size
    *
    *   @param type The type of the text(Solid, Shaded, or Blended)
    *   @param text The std::string to draw
    *   @param size The size of the text on the window
    *   @param win The window to get the renderer from
    *
    *   @return An instance of SDL_Texture on success,
    *           a null pointer if the window is not valid
    *           or if something wrong happened
    *
    */
    SDL_Texture * drawTextToTexture(LX_TTF_TypeText type, std::string text,
                                    unsigned int size, LX_Win::LX_Window *win);

    /**
    *   @fn void setColor(SDL_Color *color)
    *
    *   This function sets the new color of texts.
    *
    *   @param color The new color
    */
    void setColor(SDL_Color *color);

    /**
    *   @fn ~LX_Font()
    *   Destroy the instance
    */
    ~LX_Font();
};

};

#endif // LX_TTF_H_INCLUDED
