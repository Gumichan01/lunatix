
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

/**
*   @file LX_TrueTypeFont.cpp
*   @brief The LunatiX True type Font (TTF) implementation.
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*
*/

#include <LunatiX/LX_TrueTypeFont.hpp>
#include <LunatiX/LX_FileBuffer.hpp>
#include <LunatiX/LX_FileSystem.hpp>
#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_Config.hpp>

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#define RENDER(x) static_cast<SDL_Renderer*>(x)

using namespace LX_Config;
using namespace LX_FileIO;

namespace
{
/*
*   Calculation of the resulting surface size of the text
*   in order to display using the font given in parameter
*/
inline int sizeOfText(TTF_Font *ttf, const std::string& text, int& w, int& h)
{
    return TTF_SizeUTF8(ttf,text.c_str(),&w,&h);
}
};


namespace LX_TrueTypeFont
{

enum LX_TTF_TypeText: short {LX_TTF_SOLID,LX_TTF_SHADED,LX_TTF_BLENDED};

/* Private implementation */

struct LX_Font_
{
    UTF8string _font_str;                    /* The font file       */
    unsigned int _font_size;                 /* The font size       */
    LX_Colour _font_colour;                  /* The font colour     */
    std::unique_ptr<LX_FileIO::LX_FileBuffer> _font_buffer;


    LX_Font_(const std::string& s, unsigned int sz, LX_Colour c)
        : _font_str(s), _font_size(sz), _font_colour(c), _font_buffer(nullptr) {}

    /*
    *   This function creates a file buffer from _font_str.
    *   It can throw an IOException if the buffer cannot be loaded.
    */
    inline void createBuffer_()
    {
        _font_buffer.reset(new LX_FileBuffer(_font_str));
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
    inline TTF_Font * createInternalFont_(int size) const
    {
        return static_cast<TTF_Font*>(_font_buffer->getFontFromBuffer_(size));
    }

    /*
    *   This function creates a text surface according to the type,
    *   the colour background, if necessary, and its size.
    *
    *   If size is 0, then the font size set by the user is used.
    *   r, g, b and size are optionnal.
    *
    */
    SDL_Surface * drawText_(LX_TTF_TypeText type, const UTF8string& text,
                            unsigned int sz = 0, LX_Colour bg = {0,0,0,0})
    {
        TTF_Font *ttf = nullptr;
        SDL_Surface *loaded = nullptr;

        if(sz == 0)
            sz = _font_size;

        ttf = createInternalFont_(static_cast<int>(sz));

        if(ttf == nullptr)
            return nullptr;

        // Select the text to draw
        switch(type)
        {
        case LX_TTF_SOLID :
            loaded = TTF_RenderUTF8_Solid(ttf,text.utf8_str(),_font_colour);
            break;

        case LX_TTF_SHADED :
            loaded = TTF_RenderUTF8_Shaded(ttf,text.utf8_str(),_font_colour,bg);
            break;

        case LX_TTF_BLENDED:
            loaded = TTF_RenderUTF8_Blended(ttf,text.utf8_str(),_font_colour);
            break;
        }

        TTF_CloseFont(ttf);
        return loaded;
    }

    ~LX_Font_()
    {
        _font_buffer.reset();
    }
};


LX_Font::LX_Font(const std::string& font_file,const LX_Colour& colour, unsigned int size)
    : _fimpl(new LX_Font_(font_file,size,colour))
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
int LX_Font::sizeOfText_(std::string text, int& w, int& h) const
{
    return sizeOfText_(text,_fimpl->_font_size,w,h);
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
int LX_Font::sizeOfText_(const std::string& text, const unsigned int size, int& w, int& h) const
{
    int sz;
    TTF_Font *ttf = _fimpl->createInternalFont_(static_cast<int>(size));

    if(ttf == nullptr)
        return -1;

    sz = sizeOfText(ttf,text,w,h);

    TTF_CloseFont(ttf);
    ttf = nullptr;
    return sz;
}

/*
*   Calculate the resulting texture dimension of the utf-8 text
*   rendererd using the default font
*
*   @param [in] text The utf-8 string to size up
*   @param [in] size The size of the text
*   @param [out] w The reference of an integral to fill in the text width
*   @param [out] h The reference of an integral to fill in the text height
*
*   @return A control value, 0 on success, -1 on failure
*/
int LX_Font::sizeOfText_(const UTF8string& text, const unsigned int size, int& w, int& h) const
{
    const std::string s = text.utf8_str();
    return sizeOfText_(s,size,w,h);
}

/*
*   Render the text in solid mode. The size has to be specified
*
*   @param [in] text The string to display
*   @param [in] size The size defined by the user
*   @param [in] w The window to link the texture with
*
*   @return An valid pointer to a texture, NULL otherwise.
*/
SDL_Texture * LX_Font::drawSolidText_(const std::string& text, unsigned int size,
                                      LX_Win::LX_Window& w)
{
    return drawSolidText_(UTF8string(text),size,w);
}

/*
*   Render the UTF-8 encoded text in solid mode. The size has to be specified
*
*   @param [in] text The utf-8 string to display
*   @param [in] size The size defined by the user
*   @param [in] w The window to link the texture with
*
*   @return An valid pointer to a texture, NULL otherwise.
*/
SDL_Texture * LX_Font::drawSolidText_(const UTF8string& text, unsigned int size,
                                      LX_Win::LX_Window& w)
{
    SDL_Surface *s = _fimpl->drawText_(LX_TTF_SOLID,text,size);

    if(s == nullptr)
        return nullptr;

    SDL_Texture *t = SDL_CreateTextureFromSurface(RENDER(w.getRenderingSys()),s);
    SDL_FreeSurface(s);

    return t;
}

/*
*   Render the text in shaded mode. The size has to be specified
*
*   @param [in] text The string to display
*   @param [in] size The size defined by the user
*   @param [in] bg The background colour behind the text
*   @param [in] w The window to link the texture with
*
*   @return An valid pointer to a texture, *nullptr* otherwise.
*/
SDL_Texture * LX_Font::drawShadedText_(const std::string& text, unsigned int size,
                                       const LX_Colour& bg, LX_Win::LX_Window& w)
{
    return drawShadedText_(UTF8string(text),size,bg,w);
}

/*
*   Render the UTF-8 encoded text in shaded mode. The size has to be specified
*
*   @param [in] text The utf-8 string to display
*   @param [in] size The size defined by the user
*   @param [in] bg The background colour behind the text
*   @param [in] w The window to link the texture with
*
*   @return An valid pointer to a texture, NULL otherwise.
*/
SDL_Texture * LX_Font::drawShadedText_(const UTF8string& text, unsigned int size,
                                       const LX_Colour& bg, LX_Win::LX_Window& w)
{
    SDL_Surface *s = _fimpl->drawText_(LX_TTF_SHADED,text,size,bg);

    if(s == nullptr)
        return nullptr;

    SDL_Texture *t = SDL_CreateTextureFromSurface(RENDER(w.getRenderingSys()),s);
    SDL_FreeSurface(s);

    return t;
}

/*
*   Render the text in blended mode. The size has to be specified
*
*   @param [in] text The string to display
*   @param [in] size The size defined by the user
*   @param [in] w The window to link the texture with
*
*   @return An valid pointer to a texture, *nullptr* otherwise.
*/
SDL_Texture * LX_Font::drawBlendedText_(const std::string& text, unsigned int size,
                                        LX_Win::LX_Window& w)
{
    return drawBlendedText_(UTF8string(text),size,w);
}

/*
*   Render the UTF-8 encoded text in blended mode. The size has to be specified
*
*   @param [in] text The utf-8 string to display
*   @param [in] size The size defined by the user
*   @param [in] w The window to link the texture with
*
*   @return An valid pointer to a texture, *nullptr* otherwise.
*/
SDL_Texture * LX_Font::drawBlendedText_(const UTF8string& text, unsigned int size,
                                        LX_Win::LX_Window& w)
{
    SDL_Surface *s = _fimpl->drawText_(LX_TTF_BLENDED,text,size);

    if(s == nullptr)
        return nullptr;

    SDL_Texture *t = SDL_CreateTextureFromSurface(RENDER(w.getRenderingSys()),s);
    SDL_FreeSurface(s);

    return t;
}


const LX_Colour LX_Font::getColour_()
{
    return _fimpl->_font_colour;
}


unsigned int LX_Font::getSize_()
{
    return _fimpl->_font_size;
}


/*
*   This function sets the new colour of texts.
*/
void LX_Font::setColour_(const LX_Colour& colour)
{
    _fimpl->_font_colour = colour;
}

UTF8string LX_Font::getName(bool with_path)
{
    using namespace LX_FileSystem;
    return with_path ? _fimpl->_font_str : basename(_fimpl->_font_str);
}

LX_Colour LX_Font::getColour()
{
    return _fimpl->_font_colour;
}

LX_Font::~LX_Font()
{
    _fimpl->_font_buffer.reset();
}

};
