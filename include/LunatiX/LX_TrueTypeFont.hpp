#ifndef LX_TTF_H_INCLUDED
#define LX_TTF_H_INCLUDED


/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_TrueTypeFont.hpp
*    @brief The LunatiX True type Font (TTF) library
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <SDL2/SDL_ttf.h>
#include <memory>

const unsigned int LX_TTF_DEFAULT_FONT_SIZE = 24;   /**< The default value of the font size */
const uint8_t LX_WHITE_COLOR = 255;                 /**< The white color value              */
const uint8_t LX_BLACK_COLOR = 0;                   /**< The black color value              */

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
*   @brief The LunatiX True Type Font (TTF) module
*/
namespace LX_TrueTypeFont
{

enum LX_TTF_TypeText: short;

/// @todo LX_Font - private implementation

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
    std::unique_ptr<LX_FileIO::LX_FileBuffer> _font_buffer;

    LX_Font(LX_Font& f);
    LX_Font& operator =(LX_Font& f);

    void createBuffer_();
    int sizeOfText_(TTF_Font *ttf, const std::string& text, int& w, int& h) const;
    TTF_Font * createInternalFont_(int size) const;

    SDL_Surface * drawText_(LX_TTF_TypeText type, const UTF8string& text,
                            unsigned int size = 0, SDL_Color bg = {0,0,0,0});

public:

    /**
    *   @fn LX_Font(const SDL_Color& color, unsigned int size)
    *   @brief Constructor
    *
    *   Construct the font with color and the size of the text
    *
    *   @param [in] color The default color font
    *   @param [in] size the size of the text
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
    *   @fn LX_Font(const std::string& font_file,const SDL_Color& color)
    *   @brief Constructor
    *
    *   Construct the font with font file and color
    *
    *   @param [in] font_file The font file to use
    *   @param [in] color The default color font
    *
    *   @warning    You must  initialize the SDL_TTF library
    *               setting the TTF flag to 1 in lxsdl.cfg
    *
    *   @exception  LX_FileIO::IOException if the file cannot be loaded
    *
    */
    LX_Font(const std::string& font_file,const SDL_Color& color);

    /**
    *   @fn LX_Font(const std::string& font_file,const SDL_Color& color, unsigned int size)
    *   @brief Constructor
    *
    *  Construct the font with a font file, a color and a size.
    *
    *   @param [in] font_file The font file to load
    *   @param [in] color The color font needed
    *   @param [in] size The size of the text to display
    *
    *   @warning    It is necessary to initialize the SDL_TTF library setting
    *               the ttf flag to 1 in lxsdl.cfg.
    *
    *   @exception  LX_FileIO::IOException if the file cannot be loaded
    *
    */
    LX_Font(const std::string& font_file,const SDL_Color& color, unsigned int size);

    /**
    *   @fn int sizeOfText(std::string text, int& w, int& h) const
    *
    *   Calculate the resulting texture dimension of the
    *   text rendererd using the default font
    *
    *   @param [in] text The string to size up
    *   @param [out] w The reference of an integral to fill in the text width
    *   @param [out] h The reference of an integral to fill in the text height
    *
    *   @return A control value, 0 on success, -1 on failure
    *
    */
    int sizeOfText(std::string text, int& w, int& h) const;
    /**
    *   @fn int sizeOfText(const std::string& text, const unsigned int size, int& w, int& h) const
    *
    *   Calculate the resulting texture dimension of the
    *   text rendererd using the default font
    *
    *   @param [in] text The string to size up
    *   @param [in] size The size of the text
    *   @param [out] w The reference of an integral to fill in the text width
    *   @param [out] h The reference of an integral to fill in the text height
    *
    *   @return A control value, 0 on success, -1 on failure
    *
    */
    int sizeOfText(const std::string& text, const unsigned int size, int& w, int& h) const;
    /**
    *   @fn int sizeOfText(const UTF8string& text, const unsigned int size, int& w, int& h) const
    *
    *   Calculate the resulting texture dimension of the
    *   utf-8 text rendererd using the default font
    *
    *   @param [in] text The utf-8 string to size up
    *   @param [in] size The size of the text
    *   @param [out] w The reference of an integral to fill in the text width
    *   @param [out] h The reference of an integral to fill in the text height
    *
    *   @return A control value, 0 on success, -1 on failure
    *
    */
    int sizeOfText(const UTF8string& text, const unsigned int size, int& w, int& h) const;

    /**
    *   @fn SDL_Texture * drawSolidText(const std::string& text,
    *                                   unsigned int size, LX_Win::LX_Window& w)
    *
    *   Render the text in solid mode. The size has to be specified
    *
    *   @param [in] text The string to display
    *   @param [in] size The size defined by the user
    *   @param [in] w The window to link the texture with
    *
    *   @return An valid pointer to a texture, NULL otherwise.
    *           Call LX_GetError to get error information
    */
    SDL_Texture * drawSolidText(const std::string& text, unsigned int size, LX_Win::LX_Window& w);
    /**
    *   @fn SDL_Texture * drawSolidText(const UTF8string& text, unsigned int size,
    *                                   LX_Win::LX_Window& w)
    *
    *   Render the UTF-8 encoded text in solid mode. The size has to be specified
    *
    *   @param [in] text The utf-8 string to display
    *   @param [in] size The size defined by the user
    *   @param [in] w The window to link the texture with
    *
    *   @return An valid pointer to a texture, NULL otherwise.
    *           Call LX_GetError to get error information
    */
    SDL_Texture * drawSolidText(const UTF8string& text, unsigned int size, LX_Win::LX_Window& w);

    /**
    *   @fn SDL_Texture * drawShadedText(const std::string& text, unsigned int size,
    *                                    SDL_Color bg, LX_Win::LX_Window& w)
    *
    *   Render the text in shaded mode. The size has to be specified
    *
    *   @param [in] text The string to display
    *   @param [in] size The size defined by the user
    *   @param [in] bg The background color behind the text
    *   @param [in] w The window to link the texture with
    *
    *   @return An valid pointer to a texture, NULL otherwise.
    *           Call LX_GetError to get error information
    */
    SDL_Texture * drawShadedText(const std::string& text, unsigned int size,
                                 SDL_Color bg, LX_Win::LX_Window& w);
    /**
    *   @fn SDL_Texture * drawShadedText(const UTF8string& text, unsigned int size,
    *                                    SDL_Color bg, LX_Win::LX_Window& w)
    *
    *   Render the UTF-8 encoded text in shaded mode. The size has to be specified
    *
    *   @param [in] text The utf-8 string to display
    *   @param [in] size The size defined by the user
    *   @param [in] bg The background color behind the text
    *   @param [in] w The window to link the texture with
    *
    *   @return An valid pointer to a texture, NULL otherwise.
    *           Call LX_GetError to get error information
    */
    SDL_Texture * drawShadedText(const UTF8string& text, unsigned int size,
                                 SDL_Color bg, LX_Win::LX_Window& w);

    /**
    *   @fn SDL_Texture * drawBlendedText(const std::string& text, unsigned int size,
    *                                     LX_Win::LX_Window& w)
    *
    *   Render the text in blended mode. The size has to be specified
    *
    *   @param [in] text The string to display
    *   @param [in] size The size defined by the user
    *   @param [in] w The window to link the texture with
    *
    *   @return An valid pointer to a texture, NULL otherwise.
    *           Call LX_GetError to get error information
    */
    SDL_Texture * drawBlendedText(const std::string& text, unsigned int size,
                                  LX_Win::LX_Window& w);
    /**
    *   @fn SDL_Texture * drawBlendedText(const UTF8string& text, unsigned int size,
    *                                     LX_Win::LX_Window& w)
    *
    *   Render the UTF-8 encoded text in blended mode. The size has to be specified
    *
    *   @param [in] text The utf-8 string to display
    *   @param [in] size The size defined by the user
    *   @param [in] w The window to link the texture with
    *
    *   @return An valid pointer to a texture, NULL otherwise.
    *           Call LX_GetError to get error information
    */
    SDL_Texture * drawBlendedText(const UTF8string& text, unsigned int size,
                                  LX_Win::LX_Window& w);

    /**
    *   @fn void setColor(const SDL_Color& color)
    *
    *   This function sets the new color of texts.
    *
    *   @param [in] color The new color
    */
    void setColor(const SDL_Color& color);

    /// Destructor
    ~LX_Font();
};

};

#endif // LX_TTF_H_INCLUDED
