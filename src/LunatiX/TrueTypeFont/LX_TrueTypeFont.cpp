
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
*	@file LX_TrueTypeFont.cpp
*	@brief The LunatiX Engine True type Font (TTF) implementation.
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
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

using namespace LX_FileIO;

namespace LX_TrueTypeFont
{

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


LX_Font::LX_Font(std::string font_file,const SDL_Color& color)
    : LX_Font(font_file,color,LX_TTF_DEFAULT_FONT_SIZE) {}


LX_Font::LX_Font(std::string font_file,const SDL_Color& color, unsigned int size)
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
int LX_Font::sizeOfText_(TTF_Font *ttf, std::string text, int& w, int& h)
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
    return _font_buffer->getFontFromBuffer(size);
}


int LX_Font::sizeOfText(std::string text, int& w, int& h)
{
    return sizeOfText(text.c_str(),_font_size,w,h);
}


int LX_Font::sizeOfText(std::string text, unsigned int size, int& w, int& h)
{
    int sz;
    TTF_Font *ttf = nullptr;

    ttf = createInternalFont_(static_cast<int>(size));

    if(ttf == nullptr)
        return -1;

    sz = sizeOfText_(ttf,text.c_str(),w,h);

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
SDL_Surface * LX_Font::drawText_(LX_TTF_TypeText type, std::string text,
                                 unsigned int size,Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_Color bg = {r,g,b,a};
    TTF_Font *ttf = nullptr;
    SDL_Surface *loaded = nullptr;

    if(size == 0)
    {
        LX_SetError("drawText: Invalid size, must be a positive value");
        return nullptr;
    }
    else
        ttf = createInternalFont_(static_cast<int>(size));

    if(ttf == nullptr)
        return loaded;

    // Select the text to draw
    switch(type)
    {
    case LX_TTF_SOLID :
        loaded = TTF_RenderUTF8_Solid(ttf,text.c_str(),_font_color);
        break;

    case LX_TTF_SHADED :
        loaded = TTF_RenderUTF8_Shaded(ttf,text.c_str(),_font_color,bg);
        break;

    case LX_TTF_BLENDED:
        loaded = TTF_RenderUTF8_Blended(ttf,text.c_str(),_font_color);
        break;
    }

    TTF_CloseFont(ttf);
    return loaded;
}


SDL_Surface * LX_Font::drawSolidText(std::string text)
{
    if(_font_size == 0)
    {
        LX_SetError("LX_Font::drawBlendetText: cannot draw a text with a null size");
        return nullptr;
    }

    return drawSolidText(text.c_str(),_font_size);
}


SDL_Surface * LX_Font::drawSolidText(std::string text, unsigned int size)
{
    return drawText_(LX_TTF_SOLID,text.c_str(),size);
}


SDL_Surface * LX_Font::drawShadedText(std::string text, SDL_Color bg)
{
    return drawShadedText(text.c_str(), bg.r, bg.g, bg.b, bg.a);
}


SDL_Surface * LX_Font::drawShadedText(std::string text, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    if(_font_size == 0)
    {
        LX_SetError("LX_Font::drawBlendetText: cannot draw a text with a null size");
        return nullptr;
    }

    return drawText_(LX_TTF_SHADED,text.c_str(),_font_size,r,g,b,a);
}


SDL_Surface * LX_Font::drawShadedText(std::string text, Uint8 r, Uint8 g,
                                      Uint8 b, Uint8 a, unsigned int size)
{
    return drawText_(LX_TTF_SHADED,text.c_str(),size,r,g,b,a);
}


SDL_Surface * LX_Font::drawBlendedText(std::string text)
{
    if(_font_size == 0)
    {
        LX_SetError("LX_Font::drawBlendetText: cannot draw a text with a null size");
        return nullptr;
    }

    return drawBlendedText(text.c_str(),_font_size);
}


SDL_Surface * LX_Font::drawBlendedText(std::string text, unsigned int size)
{
    return drawText_(LX_TTF_BLENDED,text.c_str(),size);
}


SDL_Texture * LX_Font::drawTextToTexture(LX_TTF_TypeText type,std::string text,
        unsigned int size, unsigned int idWindow)
{
    LX_Win::LX_Window * target_window = nullptr;
    target_window = LX_Win::LX_WindowManager::getInstance()->getWindow(idWindow);

    return drawTextToTexture(type,text.c_str(),size,target_window);
}


SDL_Texture * LX_Font::drawTextToTexture(LX_TTF_TypeText type,std::string text,
        unsigned int size, LX_Win::LX_Window *win)
{
    Uint8 black = 0;
    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;

    if(win == nullptr)
    {
        LX_SetError("LX_Font::drawTextToTexture(): invalid window");
        return nullptr;
    }

    surface = drawText_(type,text.c_str(),size,black,black,black);

    if(surface == nullptr)
        return texture;

    // Get the texture
    texture = SDL_CreateTextureFromSurface(win->_renderer,surface);
    SDL_FreeSurface(surface);

    return texture;
}


void LX_Font::setColor(SDL_Color *color)
{
    if(color != nullptr)
    {
        _font_color.r = color->r;
        _font_color.g = color->g;
        _font_color.b = color->b;
    }
}


LX_Font::~LX_Font()
{
    delete _font_buffer;
}

};
