
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
*    @file LX_Texture.cpp
*    @brief The implementation of the image
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*
*/

#include <LunatiX/LX_Texture.hpp>
#include <LunatiX/LX_FileBuffer.hpp>
#include <LunatiX/LX_TrueTypeFont.hpp>
#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_Error.hpp>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>


namespace
{
SDL_RendererFlip shortToFlip_(const short mirror)
{
    if(mirror == 1)
        return SDL_FLIP_HORIZONTAL;
    else if(mirror == 2)
        return SDL_FLIP_VERTICAL;

    return SDL_FLIP_NONE;
}

double radianToDegree(const double angle)
{
    return angle * 180 / M_PI;
}

};

namespace LX_Graphics
{

/* LX_Texture */

// protected zero-argument construtor
LX_Texture::LX_Texture(LX_Win::LX_Window& w, uint32_t format)
    : _texture(nullptr), _win(w), _format(format) {}


LX_Texture::LX_Texture(const std::string& filename, LX_Win::LX_Window& w,
                   uint32_t format)
    : _texture(nullptr), _win(w), _format(format)
{
    _texture = loadTexture_(filename,_win);
}


LX_Texture::LX_Texture(const UTF8string& filename, LX_Win::LX_Window& w,
                   uint32_t format)
    : LX_Texture(filename.utf8_str(),w,format) {}


LX_Texture::LX_Texture(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
                   uint32_t format)
    : _texture(nullptr), _win(w), _format(format)
{
    SDL_Surface *tmp = loadSurface_(buffer);
    _texture = SDL_CreateTextureFromSurface(w._renderer,tmp);
    SDL_FreeSurface(tmp);
}

// private function
SDL_Surface * LX_Texture::loadSurface_(const std::string& filename)
{
    SDL_Surface *loaded = IMG_Load(filename.c_str());

    if(loaded == nullptr)
        return nullptr;

    SDL_Surface *optimized = SDL_ConvertSurfaceFormat(loaded,_format,0);
    SDL_FreeSurface(loaded);
    return optimized;
}

// private function
SDL_Surface * LX_Texture::loadSurface_(LX_FileIO::LX_FileBuffer& buffer)
{
    SDL_Surface * surface = static_cast<SDL_Surface*>(buffer.getSurfaceFromBuffer_());

    if(surface == nullptr)
        return nullptr;

    SDL_Surface *optimized = SDL_ConvertSurfaceFormat(surface,_format,0);
    SDL_FreeSurface(surface);
    return optimized;
}

// private function
SDL_Texture * LX_Texture::loadTexture_(const std::string& filename, LX_Win::LX_Window& w)
{
    SDL_Surface *tmpS = nullptr;
    SDL_Texture *tmpT = nullptr;
    tmpS = loadSurface_(filename.c_str());

    if(tmpS == nullptr)
        return nullptr;

    tmpT = SDL_CreateTextureFromSurface(w._renderer,tmpS);
    SDL_FreeSurface(tmpS);
    return tmpT;
}


bool LX_Texture::isOpen() const
{
    return _texture != nullptr;
}


void LX_Texture::draw()
{
    SDL_RenderCopy(_win._renderer,_texture,nullptr,nullptr);
}


bool LX_Texture::bind(float *iw, float *ih)
{
    return _win.glMakeCurrent() && SDL_GL_BindTexture(_texture,iw,ih) == 0;
}


bool LX_Texture::unbind()
{
    return SDL_GL_UnbindTexture(_texture) == 0;
}


LX_Texture::~LX_Texture()
{
    SDL_DestroyTexture(_texture);
}


/* LX_Sprite */

LX_Sprite::LX_Sprite(const std::string& filename, LX_Win::LX_Window& w,
                     uint32_t format)
    : LX_Texture(filename,w,format) {}


LX_Sprite::LX_Sprite(const UTF8string& filename, LX_Win::LX_Window& w,
                     uint32_t format)
    : LX_Texture(filename,w,format) {}


LX_Sprite::LX_Sprite(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
                     uint32_t format)
    : LX_Texture(buffer,w,format) {}


void LX_Sprite::draw()
{
    LX_Texture::draw();
}


void LX_Sprite::draw(LX_AABB * box)
{
    draw(box,0.0);
}


void LX_Sprite::draw(LX_AABB * box, const double angle)
{
    draw(box,angle,LX_MIRROR_NONE);
}

void LX_Sprite::draw(LX_AABB * box, const double angle, const short mirror)
{
    SDL_RenderCopyEx(_win._renderer,_texture,nullptr,box,
                     (-radianToDegree(angle)),nullptr,shortToFlip_(mirror));
}


LX_Sprite::~LX_Sprite() {}


/* LX_AnimatedSprite */

LX_AnimatedSprite::LX_AnimatedSprite(const std::string& filename, LX_Win::LX_Window& w,
                                     const std::vector<LX_AABB>& coord, const uint32_t delay,
                                     uint32_t format)
    : LX_Sprite(filename,w,format), _coordinates(coord), _SZ(coord.size()), _delay(delay),
      _btime(0), _iteration(0), _started(false) {}


LX_AnimatedSprite::LX_AnimatedSprite(const UTF8string& filename, LX_Win::LX_Window& w,
                                     const std::vector<LX_AABB>& coord,
                                     const uint32_t delay, uint32_t format)
    : LX_Sprite(filename,w,format), _coordinates(coord), _SZ(coord.size()), _delay(delay),
      _btime(0), _iteration(0), _started(false) {}


LX_AnimatedSprite::LX_AnimatedSprite(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
                                     const std::vector<LX_AABB>& coord,
                                     const uint32_t delay, uint32_t format)
    : LX_Sprite(buffer,w,format), _coordinates(coord), _SZ(coord.size()), _delay(delay),
      _btime(0), _iteration(0), _started(false) {}


bool LX_AnimatedSprite::isOpen() const
{
    return LX_Texture::isOpen();
}


void LX_AnimatedSprite::draw(LX_AABB * box)
{
    draw(box,0.0);
}


void LX_AnimatedSprite::draw(LX_AABB * box, const double angle)
{
    draw(box,angle,LX_MIRROR_NONE);
}


void LX_AnimatedSprite::draw(LX_AABB * box, const double angle, const short mirror)
{
    if(!_started)
    {
        _started = true;
        _btime = SDL_GetTicks();
    }
    else if(SDL_GetTicks() - _btime > _delay)
    {
        _btime = SDL_GetTicks();

        if(_iteration == _SZ - 1)
            _iteration = 0;
        else
            _iteration += 1;
    }

    SDL_RenderCopyEx(_win._renderer,_texture,&_coordinates[_iteration],
                     box,(-radianToDegree(angle)),nullptr,shortToFlip_(mirror));
}



/* LX_Surface */

LX_Surface::LX_Surface(const std::string& filename, LX_Win::LX_Window& w,
                       uint32_t format)
    : LX_Texture(w,format), _surface(nullptr)
{
    _surface = loadSurface_(filename);
}


LX_Surface::LX_Surface(const UTF8string& filename, LX_Win::LX_Window& w,
                       uint32_t format)
    : LX_Surface(filename.utf8_str(),w,format) {}


LX_Surface::LX_Surface(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
                       uint32_t format)
    : LX_Texture(w,format), _surface(nullptr)
{
    _surface = loadSurface_(buffer);
}


bool LX_Surface::isOpen() const
{
    return _surface != nullptr;
}


LX_Surface::~LX_Surface()
{
    SDL_FreeSurface(_surface);
}



/* LX_StreamingTexture */

LX_StreamingTexture::LX_StreamingTexture(LX_Win::LX_Window& w, uint32_t format)
    : LX_Texture(w,format), _screen(nullptr), _update(false)
{
    int bpp, width, height;
    uint32_t r,g,b,a;

    if(SDL_PixelFormatEnumToMasks(_format,&bpp,&r,&g,&b,&a) != SDL_TRUE)
    {
        SDL_PixelFormatEnumToMasks(SDL_PIXELFORMAT_RGBA8888,&bpp,&r,&g,&b,&a);
        _format = SDL_PIXELFORMAT_RGBA8888;
    }

    LX_Win::LX_WindowInfo info;
    _win.getInfo(info);

    if(info.lw == 0 && info.lh == 0)
    {
        width  = _win.getWidth();
        height = _win.getHeight();
    }
    else
    {
        width  = info.lw;
        height = info.lh;
    }

    if(width <= 0 || height <= 0)
        LX_SetError("LX_StreamingTexture - bad dimensions");
    else
    {
        _screen  = SDL_CreateRGBSurface(0,width,height,bpp,r,g,b,a);
        _texture = SDL_CreateTexture(_win._renderer,_format,
                                     SDL_TEXTUREACCESS_STREAMING,width,height);
    }
}


bool LX_StreamingTexture::isOpen() const
{
    return _screen != nullptr && LX_Texture::isOpen();
}


bool LX_StreamingTexture::blit(LX_Surface& s, LX_AABB& rect)
{
    bool b = (SDL_BlitScaled(s._surface,nullptr,_screen,&rect) == 0);

    if(!_update)
        _update = b;

    return b;
}

void LX_StreamingTexture::update()
{
    if(_update)
    {
        SDL_UpdateTexture(_texture,nullptr,_screen->pixels,_screen->pitch);
        SDL_FillRect(_screen,nullptr,SDL_MapRGBA(_screen->format,0,0,0,0));
        _update = false;
    }
}


LX_StreamingTexture::~LX_StreamingTexture()
{
    SDL_FreeSurface(_screen);
}



/* LX_TextTexture */

LX_TextTexture::LX_TextTexture(LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                           uint32_t format)
    : LX_Texture(w,format), _text(""), _font(font), _size(0),_dimension({0,0,0,0}) {}


LX_TextTexture::LX_TextTexture(std::string text, unsigned int sz,
                           LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                           uint32_t format)
    : LX_TextTexture(UTF8string(text),sz,font,w,format) {}


LX_TextTexture::LX_TextTexture(const UTF8string& text, unsigned int sz,
                           LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                           uint32_t format)
    : LX_Texture(w,format), _text(text), _font(font), _size(sz),_dimension({0,0,0,0}) {}


void LX_TextTexture::draw()
{
    draw(0.0);
}


void LX_TextTexture::draw(const double angle)
{
    draw(angle,LX_MIRROR_NONE);
}


void LX_TextTexture::draw(const double angle, const short mirror)
{
    SDL_RenderCopyEx(_win._renderer,_texture,nullptr,&_dimension,
                     (-radianToDegree(angle)),nullptr,shortToFlip_(mirror));
}

const UTF8string LX_TextTexture::getText() const
{
    return _text;
}

void LX_TextTexture::setPosition(int x, int y)
{
    _dimension.x = x;
    _dimension.y = y;
}


LX_TextTexture::~LX_TextTexture() {}



/* LX_SolidTextTexture */

LX_SolidTextTexture::LX_SolidTextTexture(LX_TrueTypeFont::LX_Font& font,
                                     LX_Win::LX_Window& w, uint32_t format)
    : LX_TextTexture(font,w,format) {}


LX_SolidTextTexture::LX_SolidTextTexture(std::string text, unsigned int sz,
                                     LX_TrueTypeFont::LX_Font& font,
                                     LX_Win::LX_Window& w, uint32_t format)
    : LX_SolidTextTexture(UTF8string(text),sz,font,w,format) {}


LX_SolidTextTexture::LX_SolidTextTexture(const UTF8string& text, unsigned int sz,
                                     LX_TrueTypeFont::LX_Font& font,
                                     LX_Win::LX_Window& w,uint32_t format)
    : LX_TextTexture(text,sz,font,w,format)
{
    _texture = _font.drawSolidText(_text,_size,_win);
    _font.sizeOfText(_text,_size,_dimension.w,_dimension.h);
}


void LX_SolidTextTexture::updateTexture_()
{
    SDL_DestroyTexture(_texture);
    _texture = _font.drawSolidText(_text,_size,_win);
    _font.sizeOfText(_text,_size,_dimension.w,_dimension.h);
}


void LX_SolidTextTexture::setText(std::string text, unsigned int sz)
{
    setText(UTF8string(text),sz);
}


void LX_SolidTextTexture::setText(const UTF8string& text, unsigned int sz)
{
    _text = text;
    _size = sz;
    updateTexture_();
}

void LX_SolidTextTexture::setSize(unsigned int sz)
{
    _size = sz;
    updateTexture_();
}



/* LX_ShadedTextTexture */

LX_ShadedTextTexture::LX_ShadedTextTexture(LX_TrueTypeFont::LX_Font& font,
                                       LX_Win::LX_Window& w, uint32_t format)
    : LX_TextTexture(font,w,format), _bgcolour({0,0,0,0}) {}


LX_ShadedTextTexture::LX_ShadedTextTexture(std::string text, unsigned int sz,
                                       LX_TrueTypeFont::LX_Font& font,LX_Colour& c,
                                       LX_Win::LX_Window& w, uint32_t format)
    : LX_ShadedTextTexture(UTF8string(text),sz,font,c,w,format) {}


LX_ShadedTextTexture::LX_ShadedTextTexture(const UTF8string& text, unsigned int sz,
                                       LX_TrueTypeFont::LX_Font& font,LX_Colour& c,
                                       LX_Win::LX_Window& w,uint32_t format)
    : LX_TextTexture(text,sz,font,w,format), _bgcolour(c)
{
    updateTexture_();
}


void LX_ShadedTextTexture::updateTexture_()
{
    SDL_DestroyTexture(_texture);
    _texture = _font.drawShadedText(_text,_size,_bgcolour,_win);
    _font.sizeOfText(_text,_size,_dimension.w,_dimension.h);
}


void LX_ShadedTextTexture::setText(std::string text, unsigned int sz)
{
    setText(UTF8string(text),sz);
}


void LX_ShadedTextTexture::setText(const UTF8string& text, unsigned int sz)
{
    const LX_Colour GREY = {127,127,127,255};
    setText(text,GREY,sz);
}


void LX_ShadedTextTexture::setText(std::string text, LX_Colour c, unsigned int sz)
{
    setText(UTF8string(text),c,sz);
}


void LX_ShadedTextTexture::setText(const UTF8string& text, LX_Colour c, unsigned int sz)
{
    _text = text;
    _size = sz;
    _bgcolour = c;
    updateTexture_();
}


void LX_ShadedTextTexture::setSize(unsigned int sz)
{
    _size = sz;
    updateTexture_();
}

void LX_ShadedTextTexture::setBgColor(LX_Colour c)
{
    _bgcolour = c;
    updateTexture_();
}


/* LX_BlendedTextTexture */

LX_BlendedTextTexture::LX_BlendedTextTexture(LX_TrueTypeFont::LX_Font& font,
                                         LX_Win::LX_Window& w, uint32_t format)
    : LX_TextTexture(font,w,format) {}


LX_BlendedTextTexture::LX_BlendedTextTexture(std::string text, unsigned int sz,
                                         LX_TrueTypeFont::LX_Font& font,
                                         LX_Win::LX_Window& w, uint32_t format)
    : LX_BlendedTextTexture(UTF8string(text),sz,font,w,format) {}


LX_BlendedTextTexture::LX_BlendedTextTexture(const UTF8string& text, unsigned int sz,
                                         LX_TrueTypeFont::LX_Font& font,
                                         LX_Win::LX_Window& w,uint32_t format)
    : LX_TextTexture(text,sz,font,w,format)
{
    _texture = _font.drawBlendedText(_text,_size,_win);
    _font.sizeOfText(_text,_size,_dimension.w,_dimension.h);
}


void LX_BlendedTextTexture::updateTexture_()
{
    SDL_DestroyTexture(_texture);
    _texture = _font.drawBlendedText(_text,_size,_win);
    _font.sizeOfText(_text,_size,_dimension.w,_dimension.h);
}


void LX_BlendedTextTexture::setText(std::string text, unsigned int sz)
{
    setText(UTF8string(text),sz);
}


void LX_BlendedTextTexture::setText(const UTF8string& text, unsigned int sz)
{
    _text = text;
    _size = sz;
    updateTexture_();
}

void LX_BlendedTextTexture::setSize(unsigned int sz)
{
    _size = sz;
    updateTexture_();
}

};
