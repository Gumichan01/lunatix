
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
*    @file LX_TrueTypeFont.cpp
*    @brief The LunatiX True type Font (TTF) implementation.
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>

#include <LunatiX/LX_Config.hpp>
#include <LunatiX/LX_TrueTypeFont.hpp>
#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_WindowManager.hpp>
#include <LunatiX/LX_FileBuffer.hpp>
#include <LunatiX/LX_Error.hpp>

using namespace LX_Config;
using namespace LX_FileIO;

namespace LX_TrueTypeFont
{

enum LX_TTF_TypeText: short {LX_TTF_SOLID,LX_TTF_SHADED,LX_TTF_BLENDED};

LX_Font::LX_Font(const SDL_Color& color, unsigned int size)
    : _font_str(""), _font_size(size),
      _font_color(color), _font_buffer(nullptr)
{
    // Load the configuration
    LX_Configuration *ttf_config = LX_Configuration::getInstance();

    if(ttf_config != nullptr)
    {
        _font_str = ttf_config->getFontFile();

        if(_font_size == 0)
        {
            int sz = ttf_config->getFontSize();

            if(sz <= 0)
                _font_size = LX_TTF_DEFAULT_FONT_SIZE;
            else
                _font_size = static_cast<unsigned int>(sz);
        }
    }

    createBuffer_();
}


LX_Font::LX_Font(const std::string font_file,const SDL_Color& color)
    : LX_Font(font_file,color,LX_TTF_DEFAULT_FONT_SIZE) {}


LX_Font::LX_Font(const std::string& font_file,const SDL_Color& color, unsigned int size)
    : _font_str(font_file), _font_size(size),
      _font_color(color), _font_buffer(nullptr)
{
    createBuffer_();
}


/*
*
*   This private function creates a file buffer from _font_str.
*   This function can throw an IOException instance if the buffer cannot
*   be loaded.
*
*   This function can throw an IOException
*
*/
void LX_Font::createBuffer_()
{
    _font_buffer = new LX_FileBuffer(_font_str);
}


/*
*   Private function that calculates the resulting surface size
*   of the text to display using the font given in parameter
*/
int LX_Font::sizeOfText_(TTF_Font *ttf, const std::string& text, int& w, int& h)
{
    return TTF_SizeUTF8(ttf,text.c_str(),&w,&h);
}


/*
*   Private function that creates an internal and temporary font
*   according to the font file in the class or the file buffer if it exists
*/
TTF_Font * LX_Font::createInternalFont_(int size)
{
    if(_font_buffer == nullptr)
        return nullptr;        // This code will normally never be executed

    // The font buffer exists
    return _font_buffer->getFontFromBuffer_(size);
}


int LX_Font::sizeOfText(const std::string text, int& w, int& h)
{
    return sizeOfText(text,_font_size,w,h);
}


int LX_Font::sizeOfText(const std::string& text, unsigned int size, int& w, int& h)
{
    int sz;
    TTF_Font *ttf = nullptr;

    ttf = createInternalFont_(static_cast<int>(size));

    if(ttf == nullptr)
        return -1;

    sz = sizeOfText_(ttf,text,w,h);

    TTF_CloseFont(ttf);
    ttf = nullptr;
    return sz;
}


/*
*   Private function that creates a text surface according to the type,
*   the color bakground, if necessary, and its size.
*
*   If size is 0, then the font size set by the user is used
*   r, g, b and size are optionnal in this private function.
*
*/
SDL_Surface * LX_Font::drawText_(LX_TTF_TypeText type, const UTF8string& text,
                                 unsigned int size, SDL_Color bg)
{
    TTF_Font *ttf = nullptr;
    SDL_Surface *loaded = nullptr;

    if(size == 0)
    {
        size = _font_size;
    }

    ttf = createInternalFont_(static_cast<int>(size));

    if(ttf == nullptr)
        return nullptr;

    // Select the text to draw
    switch(type)
    {
    case LX_TTF_SOLID :
        loaded = TTF_RenderUTF8_Solid(ttf,text.utf8_str(),_font_color);
        break;

    case LX_TTF_SHADED :
        loaded = TTF_RenderUTF8_Shaded(ttf,text.utf8_str(),_font_color,bg);
        break;

    case LX_TTF_BLENDED:
        loaded = TTF_RenderUTF8_Blended(ttf,text.utf8_str(),_font_color);
        break;
    }

    TTF_CloseFont(ttf);
    return loaded;
}


SDL_Texture * LX_Font::drawSolidText(const std::string text, unsigned int size,
                                     LX_Win::LX_Window& w)
{
    return drawSolidText(UTF8string(text),size,w);
}


SDL_Texture * LX_Font::drawSolidText(const UTF8string& text, unsigned int size,
                                     LX_Win::LX_Window& w)
{
    SDL_Surface *s = drawText_(LX_TTF_SOLID,text,size);

    if(s == nullptr)
        return nullptr;

    SDL_Texture *t = SDL_CreateTextureFromSurface(w._renderer,s);
    SDL_FreeSurface(s);

    return t;
}


SDL_Texture * LX_Font::drawShadedText(const std::string text, unsigned int size, SDL_Color bg,
                                      LX_Win::LX_Window& w)
{
    return drawShadedText(UTF8string(text),size,bg,w);
}


SDL_Texture * LX_Font::drawShadedText(const UTF8string& text, unsigned int size, SDL_Color bg,
                                      LX_Win::LX_Window& w)
{
    SDL_Surface *s = drawText_(LX_TTF_SHADED,text,size,bg);

    if(s == nullptr)
        return nullptr;

    SDL_Texture *t = SDL_CreateTextureFromSurface(w._renderer,s);
    SDL_FreeSurface(s);

    return t;
}


SDL_Texture * LX_Font::drawBlendedText(const std::string text, unsigned int size,
                                       LX_Win::LX_Window& w)
{
    return drawBlendedText(UTF8string(text),size,w);
}


SDL_Texture * LX_Font::drawBlendedText(const UTF8string& text, unsigned int size,
                                       LX_Win::LX_Window& w)
{
    SDL_Surface *s = drawText_(LX_TTF_BLENDED,text,size);

    if(s == nullptr)
        return nullptr;

    SDL_Texture *t = SDL_CreateTextureFromSurface(w._renderer,s);
    SDL_FreeSurface(s);

    return t;
}


void LX_Font::setColor(const SDL_Color& color)
{
    _font_color.r = color.r;
    _font_color.g = color.g;
    _font_color.b = color.b;
}


LX_Font::~LX_Font()
{
    delete _font_buffer;
}

};
