
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

/**
*   @file TrueTypeFont.cpp
*   @brief The LunatiX True type Font (TTF) implementation.
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/TrueTypeFont.hpp>
#include <Lunatix/FileBuffer.hpp>
#include <Lunatix/FileSystem.hpp>
#include <Lunatix/Window.hpp>
#include <Lunatix/Config.hpp>

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>


using namespace lx::Config;
using namespace lx::FileIO;

namespace
{

inline constexpr SDL_Renderer * render( void * renderer )
{
    return static_cast<SDL_Renderer *>( renderer );
}

/*
*   Calculation of the resulting surface size of the text
*   in order to display using the font given in parameter
*/
inline int sizeOfText( TTF_Font * ttf, const std::string& text, int& w, int& h ) noexcept
{
    return TTF_SizeUTF8( ttf, text.c_str(), &w, &h );
}

}


namespace lx
{

namespace TrueTypeFont
{

enum class TTF_TypeText
{
    TTF_SOLID, TTF_SHADED, TTF_BLENDED
};

/* Private implementation */

struct Font_ final
{
    UTF8string _font_str;                    /* The font file       */
    unsigned int _font_size;                 /* The font size       */
    Colour _font_colour;                  /* The font colour     */
    std::unique_ptr<lx::FileIO::FileBuffer> _font_buffer;


    Font_( const std::string& s, unsigned int sz, Colour c )
        : _font_str( s ), _font_size( sz ), _font_colour( c ), _font_buffer( nullptr ) {}

    /*
    *   This function creates a file buffer from _font_str.
    *   It can throw an IOException if the buffer cannot be loaded.
    */
    inline void createBuffer_()
    {
        _font_buffer.reset( new FileBuffer( _font_str ) );
    }

    /*
    *   This function creates an internal and temporary font
    *   according to the font file in the class or the file buffer if it exists
    *
    *   note:
    *   getFontFromBuffer() returns a void pointer in order to hide
    *   the real type (TTF_Font*) in the public interface.
    *   So, the static cast was necessary to get the real type
    */
    inline TTF_Font * createInternalFont_( int size ) const noexcept
    {
        return static_cast<TTF_Font *>( _font_buffer->getFontFromBuffer_( size ) );
    }

    /*
    *   This function creates a text surface according to the type,
    *   the colour background, if necessary, and its size.
    *
    *   If size is 0, then the font size set by the user is used.
    *   r, g, b and size are optionnal.
    *
    */
    SDL_Surface * drawText_( TTF_TypeText type, const UTF8string& text,
                             unsigned int sz = 0, Colour bg = {0, 0, 0, 0} ) noexcept
    {
        TTF_Font * ttf;
        SDL_Surface * loaded = nullptr;

        if ( sz == 0 )
            sz = _font_size;

        ttf = createInternalFont_( static_cast<int>( sz ) );

        if ( ttf == nullptr )
            return nullptr;

        // Select the text to draw
        switch ( type )
        {
        case TTF_TypeText::TTF_SOLID:
            loaded = TTF_RenderUTF8_Solid( ttf, text.utf8_str(), _font_colour );
            break;

        case TTF_TypeText::TTF_SHADED:
            loaded = TTF_RenderUTF8_Shaded( ttf, text.utf8_str(), _font_colour, bg );
            SDL_SetSurfaceBlendMode( loaded, SDL_BLENDMODE_BLEND );
            break;

        case TTF_TypeText::TTF_BLENDED:
            loaded = TTF_RenderUTF8_Blended( ttf, text.utf8_str(), _font_colour );
            SDL_SetSurfaceBlendMode( loaded, SDL_BLENDMODE_BLEND );
            break;

        default:
            break;
        }

        TTF_CloseFont( ttf );
        return loaded;
    }

    ~Font_()
    {
        _font_buffer.reset();
    }
};


Font::Font( const std::string& font_file, const Colour& colour, unsigned int size )
    : _fimpl( new Font_( font_file, size, colour ) )
{
    _fimpl->createBuffer_();
}

/*
*   Calculate the resulting texture dimension of the text
*   rendererd using the default font
*
*   @param [in] text The string to size up
*   @param [out] w The reference of an integral to fill in the text width
*   @param [out] h The reference of an integral to fill in the text height
*
*   @return A control value, 0 on success, -1 on failure
*/
int Font::sizeOfText_( const std::string& text, int& w, int& h ) const noexcept
{
    return sizeOfText_( text, _fimpl->_font_size, w, h );
}

/*
*   Calculate the resulting texture dimension of the text rendererd
*   using the default font
*
*   @param [in] text The string to size up
*   @param [in] size The size of the text
*   @param [out] w The reference of an integral to fill in the text width
*   @param [out] h The reference of an integral to fill in the text height
*
*   @return A control value, 0 on success, -1 on failure
*/
int Font::sizeOfText_( const std::string& text, const unsigned int size, int& w, int& h ) const noexcept
{
    int sz;
    TTF_Font * ttf = _fimpl->createInternalFont_( static_cast<int>( size ) );

    if ( ttf == nullptr )
        return -1;

    sz = sizeOfText( ttf, text, w, h );

    TTF_CloseFont( ttf );
    ttf = nullptr;
    return sz;
}

/*
*   Calculate the resulting texture dimension of the utf-8 text
*   rendererd using the default font
*
*   @return A control value, 0 on success, -1 on failure
*/
int Font::sizeOfText_( const UTF8string& text, const unsigned int size, int& w, int& h ) const noexcept
{
    return sizeOfText_( text.utf8_sstring(), size, w, h );
}

/*
*   Render the text in solid mode. The size has to be specified
*   @return An valid pointer to a texture, NULL otherwise.
*/
SDL_Texture * Font::drawSolidText_( const std::string& text, unsigned int size,
                                       lx::Win::Window& w ) noexcept
{
    return drawSolidText_( UTF8string( text ), size, w );
}

/*
*   Render the UTF-8 encoded text in solid mode. The size has to be specified
*   @return An valid pointer to a texture, NULL otherwise.
*/
SDL_Texture * Font::drawSolidText_( const UTF8string& text, unsigned int size,
                                       lx::Win::Window& w ) noexcept
{
    SDL_Surface * s = _fimpl->drawText_( TTF_TypeText::TTF_SOLID, text, size );

    if ( s == nullptr )
        return nullptr;

    SDL_Texture * t = SDL_CreateTextureFromSurface( render( w.getRenderingSys() ), s );
    SDL_FreeSurface( s );

    return t;
}

/*
*   Render the text in shaded mode. The size has to be specified
*   @return An valid pointer to a texture, *nullptr* otherwise.
*/
SDL_Texture * Font::drawShadedText_( const std::string& text, unsigned int size,
                                        const Colour& bg, lx::Win::Window& w ) noexcept
{
    return drawShadedText_( UTF8string( text ), size, bg, w );
}

/*
*   Render the UTF-8 encoded text in shaded mode. The size has to be specified
*   @return An valid pointer to a texture, NULL otherwise.
*/
SDL_Texture * Font::drawShadedText_( const UTF8string& text, unsigned int size,
                                        const Colour& bg, lx::Win::Window& w ) noexcept
{
    SDL_Surface * s = _fimpl->drawText_( TTF_TypeText::TTF_SHADED, text, size, bg );

    if ( s == nullptr )
        return nullptr;

    SDL_Texture * t = SDL_CreateTextureFromSurface( render( w.getRenderingSys() ), s );
    SDL_FreeSurface( s );

    return t;
}

/*
*   Render the text in blended mode. The size has to be specified
*   @return An valid pointer to a texture, *nullptr* otherwise.
*/
SDL_Texture * Font::drawBlendedText_( const std::string& text, unsigned int size,
        lx::Win::Window& w ) noexcept
{
    return drawBlendedText_( UTF8string( text ), size, w );
}

/*
*   Render the UTF-8 encoded text in blended mode. The size has to be specified
*   @return An valid pointer to a texture, *nullptr* otherwise.
*/
SDL_Texture * Font::drawBlendedText_( const UTF8string& text, unsigned int size,
        lx::Win::Window& w ) noexcept
{
    SDL_Surface * s = _fimpl->drawText_( TTF_TypeText::TTF_BLENDED, text, size );

    if ( s == nullptr )
        return nullptr;

    SDL_Texture * t = SDL_CreateTextureFromSurface( render( w.getRenderingSys() ), s );
    SDL_FreeSurface( s );

    return t;
}


const Colour Font::getColour_() const noexcept
{
    return _fimpl->_font_colour;
}


unsigned int Font::getSize_() const noexcept
{
    return _fimpl->_font_size;
}


/*
*   This function sets the new colour of texts.
*/
void Font::setColour_( const Colour& colour ) noexcept
{
    _fimpl->_font_colour = colour;
}

UTF8string Font::getName( bool with_path ) const noexcept
{
    using namespace lx::FileSystem;
    return with_path ? _fimpl->_font_str : basename( _fimpl->_font_str );
}

Colour Font::getColour() const noexcept
{
    return _fimpl->_font_colour;
}

Font::~Font()
{
    _fimpl->_font_buffer.reset();
}

}   // TrueTypeFont

}   // lx
