
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_TTF_H_INCLUDED
#define LX_TTF_H_INCLUDED

/**
*   @file TrueTypeFont.hpp
*   @brief The True type Font (TTF) library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/utils/utf8_string.hpp>
#include <Lunatix/Colour.hpp>
#include <memory>


struct SDL_Surface;
struct SDL_Texture;

namespace LX_Win
{
class LX_Window;
}

namespace lx
{

namespace FileIO
{
class LX_FileBuffer;
}

}

namespace LX_Graphics
{
class LX_TextTexture;
class LX_SolidTextTexture;
class LX_ShadedTextTexture;
class LX_BlendedTextTexture;
}


namespace lx
{

/**
*   @ingroup Graphics
*   @namespace lx::TrueTypeFont
*   @brief The True Type Font (TTF) namespace.
*
*   @warning In order to use this namespace, the *ttf* flag
*   in the configuration file must be set to 1, otherwise the behaviour of
*   the library is undefined.
*/
namespace TrueTypeFont
{

const unsigned int LX_TTF_DEFAULT_SIZE = 24;   /**< The default value of the font size */

struct LX_Font_;
enum class LX_TTF_TypeText;

/**
*   @class LX_Font
*   @brief The Font class
*
*   This class describes the font.
*   @note It supports the UTF-8 format
*/
class LX_Font final
{
    friend class LX_Graphics::LX_TextTexture;
    friend class LX_Graphics::LX_SolidTextTexture;
    friend class LX_Graphics::LX_ShadedTextTexture;
    friend class LX_Graphics::LX_BlendedTextTexture;
    std::unique_ptr<LX_Font_> _fimpl;

    LX_Font( LX_Font& f ) = delete;
    LX_Font& operator =( LX_Font& f ) = delete;

    /* Private functions */
    int sizeOfText_( const std::string& text, int& w, int& h ) const noexcept;
    int sizeOfText_( const std::string& text, const unsigned int size,
                     int& w, int& h ) const noexcept;
    int sizeOfText_( const UTF8string& text, const unsigned int size,
                     int& w, int& h ) const noexcept;

    SDL_Texture * drawSolidText_( const std::string& text, unsigned int size,
                                  LX_Win::LX_Window& w ) noexcept;
    SDL_Texture * drawSolidText_( const UTF8string& text, unsigned int size,
                                  LX_Win::LX_Window& w ) noexcept;

    SDL_Texture * drawShadedText_( const std::string& text, unsigned int size,
                                   const LX_Colour& bg, LX_Win::LX_Window& w ) noexcept;
    SDL_Texture * drawShadedText_( const UTF8string& text, unsigned int size,
                                   const LX_Colour& bg, LX_Win::LX_Window& w ) noexcept;

    SDL_Texture * drawBlendedText_( const std::string& text, unsigned int size,
                                    LX_Win::LX_Window& w ) noexcept;
    SDL_Texture * drawBlendedText_( const UTF8string& text, unsigned int size,
                                    LX_Win::LX_Window& w ) noexcept;

    const LX_Colour getColour_() const noexcept;
    unsigned int getSize_() const noexcept;
    void setColour_( const LX_Colour& colour ) noexcept;

public:

    /**
    *   @fn LX_Font(const std::string& font_file, const LX_Colour& colour,
    *               unsigned int size)
    *
    *   @param [in] font_file The font file to load
    *   @param [in] colour The colour for rendering the text
    *   @param [in] size The size of the text to display
    *
    *   @warning It is necessary to initialize the SDL_TTF library setting
    *           the ttf flag to 1 in lunatix.cfg.
    *
    *   @exception lx::FileIO::IOException if the file cannot be loaded
    */
    LX_Font( const std::string& font_file, const LX_Colour& colour, unsigned int size );

    /**
    *   @fn UTF8string getName(bool with_path = false) noexcept
    *
    *   Get the name of the font file
    *
    *   @param [in] with_path Defines if file must be returned with or without its path
    *   @return The name of the font
    *   @note The defeult value of *with_path* is FALSE. So the name of the file, without
    *   its path is just returned.
    */
    UTF8string getName( bool with_path = false ) const noexcept;
    /**
    *   @fn LX_Colour getColour()
    *   Get the default colour for text rendering
    *   @return The colour
    */
    LX_Colour getColour()const noexcept;

    ~LX_Font();
};

}   // TrueTypeFont

}   // lx

#endif // LX_TTF_H_INCLUDED
