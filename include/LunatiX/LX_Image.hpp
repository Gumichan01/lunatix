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

namespace LX_Device
{
class LX_Mouse;
};

namespace LX_TrueTypeFont
{
class LX_Font;
enum LX_TTF_TypeText: short;
};

/**
*   @namespace LX_Graphics
*   @brief The graphics module
*/
namespace LX_Graphics
{

/**
*   @class LX_Image
*   @brief The image object
*
*   This class describes an image
*/
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

    /**
    *   @fn LX_Image(const std::string filename, LX_Win::LX_Window& w,
    *                Uint32 format=SDL_PIXELFORMAT_RGBA8888)
    *
    *   Build an Image using a filename
    *
    *   @param filename The name of the file
    *   @param w The window the image will be drawn on (see draw())
    *   @param format Optional argument that specified the format of the image
    *
    *   |        Format Values        |                                              |
    *   |             ---             |                      ---                     |
    *   | SDL_PIXELFORMAT_UNKNOWN	  |                                              |
    *   | SDL_PIXELFORMAT_INDEX1LSB	  |                                              |
    *   | SDL_PIXELFORMAT_INDEX1MSB	  |                                              |
    *   | SDL_PIXELFORMAT_INDEX4LSB	  |                                              |
    *   | SDL_PIXELFORMAT_INDEX4MSB	  |                                              |
    *   | SDL_PIXELFORMAT_INDEX8	  |                                              |
    *   | SDL_PIXELFORMAT_RGB332	  |  RGB: 2 bit for blue, 3 bits for the others  |
    *   | SDL_PIXELFORMAT_RGB444	  |            RGB : 4 bits per channel          |
    *   | SDL_PIXELFORMAT_RGB555	  |            RGB : 5 bits per channel          |
    *   | SDL_PIXELFORMAT_BGR555	  |            BGR : 5 bits per channel          |
    *   | SDL_PIXELFORMAT_ARGB4444	  |            ARGB: 4 bits per channel          |
    *   | SDL_PIXELFORMAT_RGBA4444	  |            RGBA: 4 bits per channel          |
    *   | SDL_PIXELFORMAT_ABGR4444	  |            ABGR: 4 bits per channel          |
    *   | SDL_PIXELFORMAT_BGRA4444	  |            BGRA: 4 bits per channel          |
    *   | SDL_PIXELFORMAT_ARGB1555	  | ARGB: 1 bit for alpha, 5 bits for the others |
    *   | SDL_PIXELFORMAT_RGBA5551	  | RGBA: 1 bit for alpha, 5 bits for the others |
    *   | SDL_PIXELFORMAT_ABGR1555	  | ABGR: 1 bit for alpha, 5 bits for the others |
    *   | SDL_PIXELFORMAT_BGRA5551	  | BGRA: 1 bit for alpha, 5 bits for the others |
    *   | SDL_PIXELFORMAT_RGB565      | RGB: 6 bit for green, 5 bits for the others  |
    *   | SDL_PIXELFORMAT_BGR565      | BGR: 6 bit for green, 5 bits for the others  |
    *   | SDL_PIXELFORMAT_RGB24	      |                                              |
    *   | SDL_PIXELFORMAT_BGR24	      |                                              |
    *   | SDL_PIXELFORMAT_RGB888	  |                                              |
    *   | SDL_PIXELFORMAT_RGBX8888	  |          RGBX: 8 bits per channel            |
    *   | SDL_PIXELFORMAT_BGR888	  |          BGR:  8 bits per channel            |
    *   | SDL_PIXELFORMAT_BGRX8888	  |          BGRX: 8 bits per channel            |
    *   | SDL_PIXELFORMAT_ARGB8888	  |          ARGB: 8 bits per channel            |
    *   | SDL_PIXELFORMAT_RGBA8888	  |          RGBA: 8 bits per channel            |
    *   | SDL_PIXELFORMAT_ABGR8888    |          ABGR: 8 bits per channel            |
    *   | SDL_PIXELFORMAT_BGRA8888    |          BGRA: 8 bits per channel            |
    *   | SDL_PIXELFORMAT_ARGB2101010 |                                              |
    *   | SDL_PIXELFORMAT_YV12        |      planar mode: Y + V + U (3 planes)       |
    *   | SDL_PIXELFORMAT_IYUV        |      planar mode: Y + U + V (3 planes)       |
    *   | SDL_PIXELFORMAT_YUY2        |      packed mode: Y0+U0+Y1+V0 (1 plane)      |
    *   | SDL_PIXELFORMAT_UYVY        |      packed mode: U0+Y0+V0+Y1 (1 plane)      |
    *   | SDL_PIXELFORMAT_YVYU        |      packed mode: Y0+V0+Y1+U0 (1 plane)      |
    *
    *   The default value is SDL_PIXELFORMAT_RGBA8888
    *
    */
    LX_Image(const std::string filename, LX_Win::LX_Window& w,
             Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    /// Constuctor with the filename (UTF-8)
    LX_Image(const UTF8string& filename, LX_Win::LX_Window& w,
             Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    /// Image constuctor with a file buffer
    LX_Image(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
             Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    /**
    *   @fn virtual bool isOpen() const
    *   Check if the image has been loaded
    *   @return TRUE on success, FALSE otherwise
    */
    virtual bool isOpen() const;
    /**
    *   @fn virtual void draw()
    *   Draw an image on the window
    *   @note The window is specified at object construction
    */
    virtual void draw();

    virtual ~LX_Image();
};


/**
*   @class LX_Sprite
*   @brief The sprite
*
*   This class describes a specific image : the sprite
*/
class LX_Sprite: public LX_Image
{

public:

    /// Sprite constuctor with the filename in any encoding
    LX_Sprite(const std::string filename, LX_Win::LX_Window& w,
              Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    /// Sprite constuctor with the filename (UTF-8)
    LX_Sprite(const UTF8string& filename, LX_Win::LX_Window& w,
              Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    /// Sprite constuctor with a file buffer
    LX_Sprite(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
              Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    virtual void draw();
    /**
    *   @fn virtual void draw(LX_AABB * box)
    *   Draw an area of the current sprite on the window
    *
    *   @param box A pointer to the area of the sprite that will be drawn
    *          If the box is NULL, then the entire sprit is drawn
    *
    *   @note The window is specified at object construction
    */
    virtual void draw(LX_AABB * box);

    /**
    *   @fn virtual void draw(LX_AABB * box, const double angle)
    *   Draw an area of the current sprite on the window with rotation
    *
    *   @param box A pointer to the area of the sprite that will be drawn
    *          If the box is NULL, then the entire sprit is drawn
    *
    *   @param angle The angle to rotate the sprite
    *
    *   @note The window is specified at object construction
    */
    virtual void draw(LX_AABB * box, const double angle);

    virtual ~LX_Sprite();
};


/**
*   @class LX_AnimatedSprite
*   @brief The animated sprite
*
*   This class describes a sprite sheet. It is used for animation.
*/
class LX_AnimatedSprite: protected LX_Sprite
{
    std::vector<LX_AABB>& _coordinates;
    const size_t _SZ;
    Uint32 _delay;
    Uint32 _btime;
    size_t _iteration;
    bool _started;

public:

    /**
    *   @fn LX_AnimatedSprite(const std::string filename, LX_Win::LX_Window& w,
    *                         std::vector<LX_AABB>& coord, Uint32 delay,
    *                         Uint32 format=SDL_PIXELFORMAT_RGBA8888)
    *
    *   Build an animated sprite using a filename
    *
    *   @param filename The name of the file
    *   @param w The window the image will be drawn on (see draw())
    *   @param coord The list of coordinates for each sprite on the spritesheet
    *   @param delay The delay to display each sprite of the animated image
    *   @param format Optional argument that specified the format of the image
    *
    *   @sa LX_Image
    */
    LX_AnimatedSprite(const std::string filename, LX_Win::LX_Window& w,
                      std::vector<LX_AABB>& coord, Uint32 delay,
                      Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    /// Animated Sprite constuctor with the filename (UTF-8)
    LX_AnimatedSprite(const UTF8string& filename, LX_Win::LX_Window& w,
                      std::vector<LX_AABB>& coord, Uint32 delay,
                      Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    /// Animated Sprite constuctor with a file buffer
    LX_AnimatedSprite(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
                      std::vector<LX_AABB>& coord, Uint32 delay,
                      Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    virtual bool isOpen() const;
    virtual void draw(LX_AABB * box);

    virtual ~LX_AnimatedSprite();
};


/**
*   @class LX_Surface
*   @brief The Surface
*
*   This class describes a kind of image used in texture streaming: surface.
*/
class LX_Surface: private LX_Image
{
    friend class LX_Streaming_Image;
    friend class LX_Device::LX_Mouse;
    SDL_Surface * _surface;

public:

    /// Surface constuctor with the filename in any encoding
    LX_Surface(const std::string filename, LX_Win::LX_Window& w,
               Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    /// Surface Sprite constuctor with the filename (UTF-8)
    LX_Surface(const UTF8string& filename, LX_Win::LX_Window& w,
               Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    /// Surface Sprite constuctor with a file buffer
    LX_Surface(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
               Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    virtual bool isOpen() const;

    virtual ~LX_Surface();
};


/**
*   @class LX_Streaming_Image
*   @brief The texture
*
*   This class describes an image used for texture streaming
*/
class LX_Streaming_Image: public LX_Image
{
    SDL_Surface * _screen;
    bool _update;

public:

    /**
    *   @fn LX_Streaming_Image(LX_Win::LX_Window& w, Uint32 format=SDL_PIXELFORMAT_RGBA8888)
    *
    *   Build the texture
    *
    *   @param w The window the image will be drawn on (see draw())
    *   @param format Optional argument that specified the format of the image
    *   @sa LX_Image
    */
    LX_Streaming_Image(LX_Win::LX_Window& w, Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    virtual bool isOpen() const;
    /**
    *   @fn bool blit(LX_Surface& s, LX_AABB& rect)
    *
    *   Put the surface given in argument on the current texture
    *
    *   @param s The surface to put
    *   @param rect The area of the surface to put
    *
    *   @return TRUE on success, FALSE otherwise
    */
    bool blit(LX_Surface& s, LX_AABB& rect);
    /**
    *   @fn void update()
    *   Update the texture in order to be drawn on the window
    *
    *   @note After each call of update(), you ned to call LX_Image::draw()
    *         in order to draw the new texture on the window
    */
    void update();

    virtual ~LX_Streaming_Image();
};


class LX_TextImage: public LX_Image
{

protected:

    UTF8string _text;
    LX_TrueTypeFont::LX_Font& _font;
    unsigned int _size;
    LX_AABB _dimension;

    virtual void updateTexture_() = 0;

public:

    LX_TextImage(LX_TrueTypeFont::LX_Font& font,LX_Win::LX_Window& w,
                 Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_TextImage(std::string str, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
                 LX_Win::LX_Window& w, Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_TextImage(const UTF8string& str, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
                 LX_Win::LX_Window& w, Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    virtual void draw();
    virtual void draw(const double angle);

    void setPosition(int x, int y);
    virtual void setText(std::string str, unsigned int sz) = 0;
    virtual void setText(const UTF8string& str, unsigned int sz) = 0;
    virtual void setSize(unsigned int sz) = 0;

    virtual ~LX_TextImage();
};


class LX_SolidTextImage: public LX_TextImage
{
protected:

    virtual void updateTexture_();

public:

    LX_SolidTextImage(LX_TrueTypeFont::LX_Font& font,LX_Win::LX_Window& w,
                      Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_SolidTextImage(std::string str, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
                      LX_Win::LX_Window& w, Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_SolidTextImage(const UTF8string& str, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
                     LX_Win::LX_Window& w, Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    virtual void setText(std::string str, unsigned int sz = 0);
    virtual void setText(const UTF8string& str, unsigned int sz = 0);
    virtual void setSize(unsigned int sz);

    virtual ~LX_SolidTextImage();
};


class LX_ShadedTextImage: public LX_TextImage
{
    SDL_Color _bgcolor;

protected:

    virtual void updateTexture_();

public:

    LX_ShadedTextImage(LX_TrueTypeFont::LX_Font& font,LX_Win::LX_Window& w,
                       Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_ShadedTextImage(std::string str, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
                       LX_Win::LX_Window& w, Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    LX_ShadedTextImage(const UTF8string& str, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
                       LX_Win::LX_Window& w, Uint32 format=SDL_PIXELFORMAT_RGBA8888);

    virtual void setText(std::string str, unsigned int sz = 0);
    virtual void setText(const UTF8string& str, unsigned int sz = 0);
    virtual void setText(std::string str, SDL_Color c, unsigned int sz = 0);
    virtual void setText(const UTF8string& str, SDL_Color c, unsigned int sz = 0);
    virtual void setSize(unsigned int sz);

    virtual ~LX_ShadedTextImage();
};

};

#endif  // LX_IMAGE_H_INCLUDED

