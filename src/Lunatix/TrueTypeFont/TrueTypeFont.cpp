
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
*   Calculation of the resulting size of the text
*   in order to display it by using the font given in parameter
*/
inline int sizeOfText( TTF_Font * ttf, const std::string& text, int& w, int& h ) noexcept
{
    return TTF_SizeUTF8( ttf, text.c_str(), &w, &h );
}

}

/*
    # About text rendering # (https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_frame.html)

    There are three modes of rendering:

    - Solid
    **Quick and Dirty**

    Create an 8-bit palettized surface and render the given text at fast quality with the given font and color.
    The pixel value of 0 is the colorkey, giving a transparent background when blitted.
    Pixel and colormap value 1 is set to the text foreground color.
    This allows you to change the color without having to render the text again.
    Palette index 0 is of course not drawn when blitted to another surface, since it is the colorkey,
    and thus transparent, though its actual color is 255 minus each of the RGB components of the foreground color.
    This is the fastest rendering speed of all the rendering modes. This results in no box around the text,
    but the text is not as smooth. The resulting surface should blit faster than the Blended one.
    Use this mode for FPS and other fast changing updating text displays.

    - Shaded
    **Slow and Nice, but with a Solid Box**

    Create an 8-bit palettized surface and render the given text at high quality with the given font and colors.
    The 0 pixel value is background, while other pixels have varying degrees of the foreground color
    from the background color. This results in a box of the background color around the text in the foreground color.
    The text is antialiased. This will render slower than Solid, but in about the same time as Blended mode.
    The resulting surface should blit as fast as Solid, once it is made. Use this when you need nice text,
    and can live with a box.

    - Blended
    **Slow Slow Slow, but Ultra Nice over another image**

    Create a 32-bit ARGB surface and render the given text at high quality,
    using alpha blending to dither the font with the given color. This results in a surface with alpha transparency,
    so you don't have a solid colored box around the text. The text is antialiased.
    This will render slower than Solid, but in about the same time as Shaded mode.
    The resulting surface will blit slower than if you had used Solid or Shaded.
    Use this when you want high quality, and the text isn't changing too fast.

*/


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
    UTF8string m_filename;
    unsigned int m_fsize;
    Graphics::Colour m_fcolour;
    std::unique_ptr<lx::FileIO::FileBuffer> m_fbuffer;


    Font_( const std::string& s, unsigned int sz, Graphics::Colour c )
        : m_filename( s ), m_fsize( sz ), m_fcolour( c ), m_fbuffer( nullptr ) {}

    /*
    *   This function creates a file buffer from the font file name.
    *   It can throw an IOException if the buffer cannot be loaded.
    */
    inline void createBuffer_()
    {
        m_fbuffer.reset( new FileBuffer( m_filename ) );
    }

    /*
    *   This function creates an internal and temporary font
    *   according to the font file in the class or the file buffer if it exists
    *
    *   note:
    *   createInternalFont_() returns a void pointer in order to hide
    *   the real type (TTF_Font*) in the public interface.
    *   So, the static cast was necessary to get the real type
    */
    inline TTF_Font * createInternalFont_( int size ) const noexcept
    {
        return static_cast<TTF_Font *>( m_fbuffer->getFontFromBuffer_( size ) );
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
                             unsigned int sz = 0, Graphics::Colour bg = { 0, 0, 0, 0 } ) noexcept
    {
        TTF_Font * ttf;
        SDL_Surface * loaded = nullptr;

        if ( sz == 0 )
            sz = m_fsize;

        ttf = createInternalFont_( static_cast<int>( sz ) );

        if ( ttf == nullptr )
            return nullptr;

        // Select the text to draw
        switch ( type )
        {
        case TTF_TypeText::TTF_SOLID:
            loaded = TTF_RenderUTF8_Solid( ttf, text.utf8_str(), m_fcolour );
            break;

        case TTF_TypeText::TTF_SHADED:
            loaded = TTF_RenderUTF8_Shaded( ttf, text.utf8_str(), m_fcolour, bg );
            SDL_SetSurfaceBlendMode( loaded, SDL_BLENDMODE_BLEND );
            break;

        case TTF_TypeText::TTF_BLENDED:
            loaded = TTF_RenderUTF8_Blended( ttf, text.utf8_str(), m_fcolour );
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
        m_fbuffer.reset();
    }
};


Font::Font( const std::string& font_file, const Graphics::Colour& colour, unsigned int size )
    : m_fimpl( new Font_( font_file, size, colour ) )
{
    m_fimpl->createBuffer_();
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
    return sizeOfText_( text, m_fimpl->m_fsize, w, h );
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
    TTF_Font * ttf = m_fimpl->createInternalFont_( static_cast<int>( size ) );

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
    SDL_Surface * s = m_fimpl->drawText_( TTF_TypeText::TTF_SOLID, text, size );

    if ( s == nullptr )
        return nullptr;

    SDL_Texture * t = SDL_CreateTextureFromSurface( render( w.getRenderingSys_() ), s );
    SDL_FreeSurface( s );

    return t;
}

/*
*   Render the text in shaded mode. The size has to be specified
*   @return An valid pointer to a texture, *nullptr* otherwise.
*/
SDL_Texture * Font::drawShadedText_( const std::string& text, unsigned int size,
                                     const Graphics::Colour& bg, lx::Win::Window& w ) noexcept
{
    return drawShadedText_( UTF8string( text ), size, bg, w );
}

/*
*   Render the UTF-8 encoded text in shaded mode. The size has to be specified
*   @return An valid pointer to a texture, NULL otherwise.
*/
SDL_Texture * Font::drawShadedText_( const UTF8string& text, unsigned int size,
                                     const Graphics::Colour& bg, lx::Win::Window& w ) noexcept
{
    SDL_Surface * s = m_fimpl->drawText_( TTF_TypeText::TTF_SHADED, text, size, bg );

    if ( s == nullptr )
        return nullptr;

    SDL_Texture * t = SDL_CreateTextureFromSurface( render( w.getRenderingSys_() ), s );
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
    SDL_Surface * s = m_fimpl->drawText_( TTF_TypeText::TTF_BLENDED, text, size );

    if ( s == nullptr )
        return nullptr;

    SDL_Texture * t = SDL_CreateTextureFromSurface( render( w.getRenderingSys_() ), s );
    SDL_FreeSurface( s );

    return t;
}

const Graphics::Colour Font::getColour_() const noexcept
{
    return m_fimpl->m_fcolour;
}

unsigned int Font::getSize_() const noexcept
{
    return m_fimpl->m_fsize;
}


/*
*   This function sets the new colour of texts.
*/
void Font::setColour_( const Graphics::Colour& colour ) noexcept
{
    m_fimpl->m_fcolour = colour;
}

UTF8string Font::getName( bool with_path ) const noexcept
{
    using namespace lx::FileSystem;
    return with_path ? m_fimpl->m_filename : basename( m_fimpl->m_filename );
}

Graphics::Colour Font::getColour() const noexcept
{
    return m_fimpl->m_fcolour;
}

Font::~Font()
{
    m_fimpl->m_fbuffer.reset();
}

}   // TrueTypeFont

}   // lx
