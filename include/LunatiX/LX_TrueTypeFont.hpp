
/*
*   Copyright © 2017 Luxon Jean-Pierre
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
*   @file LX_TrueTypeFont.hpp
*   @brief The True type Font (TTF) library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <LunatiX/LX_Colour.hpp>
#include <memory>


struct SDL_Surface;
struct SDL_Texture;

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
class LX_TextTexture;
class LX_SolidTextTexture;
class LX_ShadedTextTexture;
class LX_BlendedTextTexture;
}


/**
*   @ingroup Graphics
*   @namespace LX_TrueTypeFont
*   @brief The True Type Font (TTF) namespace.
*
*   @warning In order to use this namespace, the *ttf* flag
*   in the configuration file must be set to 1, otherwise the behaviour of
*   the library is undefined.
*/
namespace LX_TrueTypeFont
{

const unsigned int LX_TTF_DEFAULT_SIZE = 24;   /**< The default value of the font size */

struct LX_Font_;
enum LX_TTF_TypeText: short;

/**
*   @class LX_Font
*   @brief The Font class
*
*   This class describes the font.
*   @note It supports the UTF-8 format
*/
class LX_Font
{
    friend class LX_Graphics::LX_TextTexture;
    friend class LX_Graphics::LX_SolidTextTexture;
    friend class LX_Graphics::LX_ShadedTextTexture;
    friend class LX_Graphics::LX_BlendedTextTexture;
    std::unique_ptr<LX_Font_> _fimpl;

    LX_Font(LX_Font& f);
    LX_Font& operator =(LX_Font& f);

    /* Private functions */
    int sizeOfText_(std::string text, int& w, int& h) const;
    int sizeOfText_(const std::string& text, const unsigned int size,
                    int& w, int& h) const;
    int sizeOfText_(const UTF8string& text, const unsigned int size,
                    int& w, int& h) const;

    SDL_Texture * drawSolidText_(const std::string& text, unsigned int size,
                                 LX_Win::LX_Window& w);
    SDL_Texture * drawSolidText_(const UTF8string& text, unsigned int size,
                                 LX_Win::LX_Window& w);

    SDL_Texture * drawShadedText_(const std::string& text, unsigned int size,
                                  const LX_Colour& bg, LX_Win::LX_Window& w);
    SDL_Texture * drawShadedText_(const UTF8string& text, unsigned int size,
                                  const LX_Colour& bg, LX_Win::LX_Window& w);

    SDL_Texture * drawBlendedText_(const std::string& text, unsigned int size,
                                   LX_Win::LX_Window& w);
    SDL_Texture * drawBlendedText_(const UTF8string& text, unsigned int size,
                                   LX_Win::LX_Window& w);

    const LX_Colour getColour_();
    unsigned int getSize_();
    void setColour_(const LX_Colour& colour);

public:

    /**
    *   @fn LX_Font(const std::string& font_file, const LX_Colour& colour,
    *               unsigned int size)
    *   @brief Constructor
    *
    *   Construct the font with a font file, a colour and a size.
    *
    *   @param [in] font_file The font file to load
    *   @param [in] colour The colour for rendering the text
    *   @param [in] size The size of the text to display
    *
    *   @warning It is necessary to initialize the SDL_TTF library setting
    *           the ttf flag to 1 in lunatix.cfg.
    *
    *   @exception LX_FileIO::IOException if the file cannot be loaded
    */
    LX_Font(const std::string& font_file, const LX_Colour& colour, unsigned int size);

    /// Destructor
    ~LX_Font();
};

};

#endif // LX_TTF_H_INCLUDED
