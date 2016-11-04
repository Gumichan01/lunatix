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
#include <LunatiX/LX_Colour.hpp>
#include <memory>

const unsigned int LX_TTF_DEFAULT_FONT_SIZE = 24;   /**< The default value of the font size */
const uint8_t LX_WHITE_COLOUR = 255;                /**< The white colour value             */
const uint8_t LX_BLACK_COLOUR = 0;                  /**< The black colour value             */

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Colour;

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
*
*   It handles True Type Font texts manipulation.
*
*   @warning In order to use this module, the *ttf* flag
*   in the configuration file must be set to 1, otherwise the behaviour of
*   the library is undefined.
*/
namespace LX_TrueTypeFont
{

struct LX_Font_;
enum LX_TTF_TypeText: short;

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
    std::unique_ptr<LX_Font_> _fimpl;

    LX_Font(LX_Font& f);
    LX_Font& operator =(LX_Font& f);

public:

    /**
    *   @fn LX_Font(const LX_Colour& colour, unsigned int size)
    *   @brief Constructor
    *
    *   Construct the font with colour and the size of the text
    *
    *   @param [in] colour The default colour font
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
    LX_Font(const LX_Colour& colour, unsigned int size=0);

    /**
    *   @fn LX_Font(const std::string& font_file,const LX_Colour& colour)
    *   @brief Constructor
    *
    *   Construct the font with font file and colour
    *
    *   @param [in] font_file The font file to use
    *   @param [in] colour The default colour font
    *
    *   @warning    You must  initialize the SDL_TTF library
    *               setting the TTF flag to 1 in lxsdl.cfg
    *
    *   @exception  LX_FileIO::IOException if the file cannot be loaded
    *
    */
    LX_Font(const std::string& font_file,const LX_Colour& colour);

    /**
    *   @fn LX_Font(const std::string& font_file,const LX_Colour& colour, unsigned int size)
    *   @brief Constructor
    *
    *  Construct the font with a font file, a colour and a size.
    *
    *   @param [in] font_file The font file to load
    *   @param [in] colour The colour font needed
    *   @param [in] size The size of the text to display
    *
    *   @warning    It is necessary to initialize the SDL_TTF library setting
    *               the ttf flag to 1 in lxsdl.cfg.
    *
    *   @exception  LX_FileIO::IOException if the file cannot be loaded
    *
    */
    LX_Font(const std::string& font_file,const LX_Colour& colour, unsigned int size);

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
    *                                    const LX_Colour& bg, LX_Win::LX_Window& w)
    *
    *   Render the text in shaded mode. The size has to be specified
    *
    *   @param [in] text The string to display
    *   @param [in] size The size defined by the user
    *   @param [in] bg The background colour behind the text
    *   @param [in] w The window to link the texture with
    *
    *   @return An valid pointer to a texture, NULL otherwise.
    *           Call LX_GetError to get error information
    */
    SDL_Texture * drawShadedText(const std::string& text, unsigned int size,
                                 const LX_Colour& bg, LX_Win::LX_Window& w);
    /**
    *   @fn SDL_Texture * drawShadedText(const UTF8string& text, unsigned int size,
    *                                    const LX_Colour& bg, LX_Win::LX_Window& w)
    *
    *   Render the UTF-8 encoded text in shaded mode. The size has to be specified
    *
    *   @param [in] text The utf-8 string to display
    *   @param [in] size The size defined by the user
    *   @param [in] bg The background colour behind the text
    *   @param [in] w The window to link the texture with
    *
    *   @return An valid pointer to a texture, NULL otherwise.
    *           Call LX_GetError to get error information
    */
    SDL_Texture * drawShadedText(const UTF8string& text, unsigned int size,
                                 const LX_Colour& bg, LX_Win::LX_Window& w);

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
    *   @fn void setColor(const LX_Colour& colour)
    *
    *   This function sets the new colour of texts.
    *
    *   @param [in] colour The new colour
    */
    void setColor(const LX_Colour& colour);

    /// Destructor
    ~LX_Font();
};

};

#endif // LX_TTF_H_INCLUDED
