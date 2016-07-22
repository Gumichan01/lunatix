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

enum LX_ImageAccess
{
    LX_IMG_STATIC,
    LX_IMG_STREAMING,
    LX_IMG_TARGET
};

class LX_Image
{
    SDL_Surface * loadSurface_(const std::string& filename);
    SDL_Surface * loadSurface_(LX_FileIO::LX_FileBuffer& buffer);
    SDL_Texture * loadTexture_(const std::string& filename, LX_Win::LX_Window& w);

protected:

    SDL_Texture * _texture;
    LX_Win::LX_Window& _win;
    Uint32 _format;


public:

    LX_Image(const std::string filename, LX_Win::LX_Window& w,
             Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_Image(const UTF8string& filename, LX_Win::LX_Window& w,
             Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_Image(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
             Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    bool isOpen() const;

    void update();

    virtual void draw(LX_AABB * box= nullptr, const double angle = 0.0);

    virtual ~LX_Image();
};


class LX_Static_Image: public LX_Image
{

public:

    LX_Static_Image(const std::string filename, LX_Win::LX_Window& w,
                    Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_Static_Image(const UTF8string& filename, LX_Win::LX_Window& w,
                    Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_Static_Image(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
             Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    virtual ~LX_Static_Image();
};

};

#endif  // LX_IMAGE_H_INCLUDED
