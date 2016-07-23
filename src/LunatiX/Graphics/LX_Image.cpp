

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
*	@file LX_Image.cpp
*	@brief The implementation of the image
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/LX_Image.hpp>
#include <LunatiX/LX_FileBuffer.hpp>
#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_Error.hpp>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>


namespace LX_Graphics
{

/* LX_Image */

// protected zero-argument construtor
LX_Image::LX_Image(LX_Win::LX_Window& w, Uint32 format)
    : _texture(nullptr), _win(w), _format(format) {}


LX_Image::LX_Image(const std::string filename, LX_Win::LX_Window& w,
                   Uint32 format)
    : _texture(nullptr), _win(w), _format(format)
{
    _texture = loadTexture_(filename,_win);
}


LX_Image::LX_Image(const UTF8string& filename, LX_Win::LX_Window& w,
                   Uint32 format)
    : LX_Image(filename.utf8_str(),w,format) {}


LX_Image::LX_Image(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
         Uint32 format)
    : _texture(nullptr), _win(w), _format(format)
{
    SDL_Surface *tmp = loadSurface_(buffer);
    _texture = SDL_CreateTextureFromSurface(w.getRenderer(),tmp);
    SDL_FreeSurface(tmp);
}

// private function
SDL_Surface * LX_Image::loadSurface_(const std::string& filename)
{
    SDL_Surface *loaded = IMG_Load(filename.c_str());

    if(loaded == nullptr)
        return nullptr;

    SDL_Surface *optimized = SDL_ConvertSurfaceFormat(loaded,_format,0);
    SDL_FreeSurface(loaded);
    return optimized;
}

// private function
SDL_Surface * LX_Image::loadSurface_(LX_FileIO::LX_FileBuffer& buffer)
{
    SDL_Surface * surface = buffer.getSurfaceFromBuffer();

    if(surface == nullptr)
        return nullptr;

    SDL_Surface *optimized = SDL_ConvertSurfaceFormat(surface,_format,0);
    SDL_FreeSurface(surface);
    return optimized;
}

// private function
SDL_Texture * LX_Image::loadTexture_(const std::string& filename, LX_Win::LX_Window& w)
{
    SDL_Surface *tmpS = nullptr;
    SDL_Texture *tmpT = nullptr;
    tmpS = loadSurface_(filename.c_str());

    if(tmpS == nullptr)
        return nullptr;

    tmpT = SDL_CreateTextureFromSurface(w.getRenderer(),tmpS);
    SDL_FreeSurface(tmpS);
    return tmpT;
}


bool LX_Image::isOpen() const
{
    return _texture != nullptr;
}


void LX_Image::draw()
{
    SDL_RenderCopy(_win.getRenderer(),_texture,nullptr,nullptr);
}


LX_Image::~LX_Image()
{
    SDL_DestroyTexture(_texture);
}


/* LX_Sprite */

LX_Sprite::LX_Sprite(const std::string filename, LX_Win::LX_Window& w,
                                 Uint32 format)
    : LX_Image(filename,w,format) {}


LX_Sprite::LX_Sprite(const UTF8string& filename, LX_Win::LX_Window& w,
                                 Uint32 format)
    : LX_Image(filename,w,format) {}


LX_Sprite::LX_Sprite(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
                                 Uint32 format)
    : LX_Image(buffer,w,format) {}


void LX_Sprite::draw()
{
    LX_Image::draw();
}


void LX_Sprite::draw(LX_AABB * box)
{
    draw(box,0.0);
}


void LX_Sprite::draw(LX_AABB * box, const double angle)
{
    SDL_RenderCopyEx(_win.getRenderer(),_texture,nullptr,box,(-angle),nullptr,
                     SDL_FLIP_NONE);
}


LX_Sprite::~LX_Sprite() {}


/* LX_AnimatedSprite */

LX_AnimatedSprite::LX_AnimatedSprite(const std::string filename, LX_Win::LX_Window& w,
                                    std::vector<LX_AABB>& coord, Uint32 delay,
                                    Uint32 format)
    : LX_Sprite(filename,w,format), _coordinates(coord), _SZ(coord.size()), _delay(delay),
    _btime(0), _iteration(0), _started(false) {}


LX_AnimatedSprite::LX_AnimatedSprite(const UTF8string& filename, LX_Win::LX_Window& w,
                                    std::vector<LX_AABB>& coord, Uint32 delay,
                                    Uint32 format)
    : LX_Sprite(filename,w,format), _coordinates(coord), _SZ(coord.size()), _delay(delay),
    _btime(0), _iteration(0), _started(false) {}


LX_AnimatedSprite::LX_AnimatedSprite(LX_FileIO::LX_FileBuffer& buffer,
                                     LX_Win::LX_Window& w,
                                     std::vector<LX_AABB>& coord, Uint32 delay,
                                     Uint32 format)
    : LX_Sprite(buffer,w,format), _coordinates(coord), _SZ(coord.size()), _delay(delay),
    _btime(0), _iteration(0), _started(false) {}


bool LX_AnimatedSprite::isOpen() const
{
    return LX_Image::isOpen();
}


void LX_AnimatedSprite::draw(LX_AABB * box)
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

    SDL_RenderCopy(_win.getRenderer(),_texture,&_coordinates[_iteration],box);
}


LX_AnimatedSprite::~LX_AnimatedSprite() {}


/* LX_Surface */

LX_Surface::LX_Surface(const std::string filename, LX_Win::LX_Window& w,
                                 Uint32 format)
    : LX_Image(w,format), _surface(nullptr)
{
    _surface = loadSurface_(filename);
}


LX_Surface::LX_Surface(const UTF8string& filename, LX_Win::LX_Window& w,
                                 Uint32 format)
    : LX_Surface(filename.utf8_str(),w,format) {}


LX_Surface::LX_Surface(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
                                 Uint32 format)
    : LX_Image(w,format), _surface(nullptr)
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


/* LX_Streaming_Image */

LX_Streaming_Image::LX_Streaming_Image(LX_Win::LX_Window& w, Uint32 format)
    : LX_Image(w,format), _screen(nullptr), _update(false)
{
    int bpp, width, height;
    Uint32 r,g,b,a;

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
        LX_SetError("LX_Streaming_Image - bad dimensions");
    else
    {
        _screen  = SDL_CreateRGBSurface(0,width,height,bpp,r,g,b,a);
        _texture = SDL_CreateTexture(_win.getRenderer(),_format,
                                     SDL_TEXTUREACCESS_STREAMING,width,height);
    }
}


bool LX_Streaming_Image::isOpen() const
{
    return _screen != nullptr && LX_Image::isOpen();
}


bool LX_Streaming_Image::blit(LX_Surface& s, LX_AABB& rect)
{
    bool b = (SDL_BlitScaled(s._surface,nullptr,_screen,&rect) == 0);

    if(!_update)
        _update = b;

    return b;
}

void LX_Streaming_Image::update()
{
    if(_update)
    {
        SDL_UpdateTexture(_texture,nullptr,_screen->pixels,_screen->pitch);
        SDL_FillRect(_screen,nullptr,SDL_MapRGBA(_screen->format,0,0,0,0));
        _update = false;
    }
}


LX_Streaming_Image::~LX_Streaming_Image()
{
    SDL_FreeSurface(_screen);
}

};