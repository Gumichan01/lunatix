#ifndef LX_IMAGE_H_INCLUDED
#define LX_IMAGE_H_INCLUDED

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
*	@file LX_Image.hpp
*	@brief The Image
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <LunatiX/LX_AABB.hpp>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <vector>

struct SDL_Texture;

namespace LX_FileIO
{
class LX_FileBuffer;
};

namespace LX_Win
{
class LX_Window;
};


namespace LX_Graphics
{

class LX_Image
{
    LX_Image(LX_Image&);
    LX_Image& operator =(LX_Image&);
    SDL_Texture * loadTexture_(const std::string& filename, LX_Win::LX_Window& w);

protected:

    SDL_Texture * _texture;
    LX_Win::LX_Window& _win;
    Uint32 _format;

    LX_Image(LX_Win::LX_Window& w, Uint32 format);
    SDL_Surface * loadSurface_(const std::string& filename);
    SDL_Surface * loadSurface_(LX_FileIO::LX_FileBuffer& buffer);

public:

    LX_Image(const std::string filename, LX_Win::LX_Window& w,
             Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_Image(const UTF8string& filename, LX_Win::LX_Window& w,
             Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_Image(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
             Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    virtual bool isOpen() const;
    virtual void draw();

    virtual ~LX_Image();
};


class LX_Sprite: public LX_Image
{

public:

    LX_Sprite(const std::string filename, LX_Win::LX_Window& w,
              Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_Sprite(const UTF8string& filename, LX_Win::LX_Window& w,
              Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_Sprite(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
              Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    virtual void draw();
    virtual void draw(LX_AABB * box);
    virtual void draw(LX_AABB * box, const double angle);

    virtual ~LX_Sprite();
};


class LX_AnimatedSprite: protected LX_Sprite
{
    std::vector<LX_AABB>& _coordinates;
    const size_t _SZ;
    Uint32 _delay;
    Uint32 _btime;
    size_t _iteration;
    bool _started;

public:

    LX_AnimatedSprite(const std::string filename, LX_Win::LX_Window& w,
                      std::vector<LX_AABB>& coord, Uint32 delay,
                      Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_AnimatedSprite(const UTF8string& filename, LX_Win::LX_Window& w,
                      std::vector<LX_AABB>& coord, Uint32 delay,
                      Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_AnimatedSprite(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
                      std::vector<LX_AABB>& coord, Uint32 delay,
                      Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    virtual bool isOpen() const;
    virtual void draw(LX_AABB * box);

    virtual ~LX_AnimatedSprite();
};


class LX_Surface: private LX_Image
{
    friend class LX_Streaming_Image;
    SDL_Surface * _surface;

public:

    LX_Surface(const std::string filename, LX_Win::LX_Window& w,
               Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_Surface(const UTF8string& filename, LX_Win::LX_Window& w,
               Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_Surface(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
               Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    virtual bool isOpen() const;

    virtual ~LX_Surface();
};


class LX_Streaming_Image: public LX_Image
{
    SDL_Surface * _screen;
    bool _update;

public:

    LX_Streaming_Image(LX_Win::LX_Window& w, Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    virtual bool isOpen() const;
    bool blit(LX_Surface& s, LX_AABB& rect);
    void update();

    virtual ~LX_Streaming_Image();
};

};

#endif  // LX_IMAGE_H_INCLUDED
