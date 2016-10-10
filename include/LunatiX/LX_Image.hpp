#ifndef LX_IMAGE_H_INCLUDED
#define LX_IMAGE_H_INCLUDED

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
*    @file LX_Image.hpp
*    @brief The Image
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <LunatiX/LX_AABB.hpp>
#include <SDL2/SDL_pixels.h>
#include <vector>

struct SDL_Surface;
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
};


namespace LX_Graphics
{

/// Flag to define no mirror while drawing an image
const short LX_MIRROR_NONE       = 0;
/// Flag to define horizontal mirror while drawing an image
const short LX_MIRROR_HORIZONTAL = 1;
/// Flag to define vertical mirror while drawing an image
const short LX_MIRROR_VERTICAL   = 2;

/// @todo (#6#) LX_Image and sub-classes - private implementation

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
    uint32_t _format;

    LX_Image(LX_Win::LX_Window& w, uint32_t format);
    SDL_Surface * loadSurface_(const std::string& filename);
    SDL_Surface * loadSurface_(LX_FileIO::LX_FileBuffer& buffer);

public:

    /**
    *   @fn LX_Image(const std::string& filename, LX_Win::LX_Window& w,
    *                uint32_t format=SDL_PIXELFORMAT_RGBA8888)
    *   @brief Constructor
    *
    *   Build an Image using a filename
    *
    *   @param [in] filename The name of the file
    *   @param [in] w The window the image will be drawn on (see draw())
    *   @param [in] format Optional argument that specified the format of the image
    *
    *   |        Format Values        |                                              |
    *   |             ---             |                      ---                     |
    *   | SDL_PIXELFORMAT_UNKNOWN     |                                              |
    *   | SDL_PIXELFORMAT_INDEX1LSB   |                                              |
    *   | SDL_PIXELFORMAT_INDEX1MSB   |                                              |
    *   | SDL_PIXELFORMAT_INDEX4LSB   |                                              |
    *   | SDL_PIXELFORMAT_INDEX4MSB   |                                              |
    *   | SDL_PIXELFORMAT_INDEX8      |                                              |
    *   | SDL_PIXELFORMAT_RGB332      |  RGB: 2 bit for blue, 3 bits for the others  |
    *   | SDL_PIXELFORMAT_RGB444      |            RGB : 4 bits per channel          |
    *   | SDL_PIXELFORMAT_RGB555      |            RGB : 5 bits per channel          |
    *   | SDL_PIXELFORMAT_BGR555      |            BGR : 5 bits per channel          |
    *   | SDL_PIXELFORMAT_ARGB4444    |            ARGB: 4 bits per channel          |
    *   | SDL_PIXELFORMAT_RGBA4444    |            RGBA: 4 bits per channel          |
    *   | SDL_PIXELFORMAT_ABGR4444    |            ABGR: 4 bits per channel          |
    *   | SDL_PIXELFORMAT_BGRA4444    |            BGRA: 4 bits per channel          |
    *   | SDL_PIXELFORMAT_ARGB1555    | ARGB: 1 bit for alpha, 5 bits for the others |
    *   | SDL_PIXELFORMAT_RGBA5551    | RGBA: 1 bit for alpha, 5 bits for the others |
    *   | SDL_PIXELFORMAT_ABGR1555    | ABGR: 1 bit for alpha, 5 bits for the others |
    *   | SDL_PIXELFORMAT_BGRA5551    | BGRA: 1 bit for alpha, 5 bits for the others |
    *   | SDL_PIXELFORMAT_RGB565      | RGB: 6 bit for green, 5 bits for the others  |
    *   | SDL_PIXELFORMAT_BGR565      | BGR: 6 bit for green, 5 bits for the others  |
    *   | SDL_PIXELFORMAT_RGB24       |                                              |
    *   | SDL_PIXELFORMAT_BGR24       |                                              |
    *   | SDL_PIXELFORMAT_RGB888      |                                              |
    *   | SDL_PIXELFORMAT_RGBX8888    |          RGBX: 8 bits per channel            |
    *   | SDL_PIXELFORMAT_BGR888      |          BGR:  8 bits per channel            |
    *   | SDL_PIXELFORMAT_BGRX8888    |          BGRX: 8 bits per channel            |
    *   | SDL_PIXELFORMAT_ARGB8888    |          ARGB: 8 bits per channel            |
    *   | SDL_PIXELFORMAT_RGBA8888    |          RGBA: 8 bits per channel            |
    *   | SDL_PIXELFORMAT_ABGR8888    |          ABGR: 8 bits per channel            |
    *   | SDL_PIXELFORMAT_BGRA8888    |          BGRA: 8 bits per channel            |
    *   | SDL_PIXELFORMAT_ARGB2101010 |                                              |
    *   | SDL_PIXELFORMAT_YV12        |      planar mode: Y + V + U (3 planes)       |
    *   | SDL_PIXELFORMAT_IYUV        |      planar mode: Y + U + V (3 planes)       |
    *   | SDL_PIXELFORMAT_YUY2        |      packed mode: Y0+U0+Y1+V0 (1 plane)      |
    *   | SDL_PIXELFORMAT_UYVY        |      packed mode: U0+Y0+V0+Y1 (1 plane)      |
    *   | SDL_PIXELFORMAT_YVYU        |      packed mode: Y0+V0+Y1+U0 (1 plane)      |
    *
    *   The default value is **SDL_PIXELFORMAT_RGBA8888**
    *
    */
    LX_Image(const std::string& filename, LX_Win::LX_Window& w,
             uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Constuctor with the filename (UTF-8)
    LX_Image(const UTF8string& filename, LX_Win::LX_Window& w,
             uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Image constuctor with a file buffer
    LX_Image(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
             uint32_t format=SDL_PIXELFORMAT_RGBA8888);

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

    /**
    *   @fn bool bind(float *iw = nullptr, float *ih = nullptr)
    *
    *   Bind an image (its internal texture) to the OpenGL context
    *   of the OpenGl window where the image is drawn on
    *   in order to use the OpenGL functions.
    *
    *   @param [out] iw (Optional) a pointer to a float value of which will be
    *          filled with the texture width. See notes.
    *   @param [out] ih (Optional) a pointer to a float value which will be
    *          filled with the texture width. See notes.
    *
    *   @return TRUE on success. FALSE if the operation is not supported.
    *
    *   @note 1 - If provided, **iw** and **ih** will be filled with
    *         the width and height values suitable for the provided texture.
    *         In most cases, both will be 1.0, however, on systems that support the
    *         GL_ARB_texture_rectangle extension, these values will actually be the
    *         pixel width and height used to create the texture, so this factor needs
    *         to be taken into account when providing texture coordinates to OpenGL.
    *
    *   @note 2 - This functions change the focused OpenGL window
    *         in order to bind the image to the OpenGL context of the window
    *         where it is usually drawn on.
    *         That is to say the function can be only called if the window is
    *         an OpenGL window. Otherwise, bind() returns FALSE.
    */
    bool bind(float *iw = nullptr, float *ih = nullptr);

    /**
    *   @fn bool unbind()
    *   Unbind an image
    *   @return TRUE on success.FALSE if the operation is not supported.
    */
    bool unbind();

    /// Destructor
    virtual ~LX_Image();
};


/**
*   @class LX_Sprite
*   @brief The sprite
*/
class LX_Sprite: public LX_Image
{

public:

    /// Sprite constuctor
    LX_Sprite(const std::string& filename, LX_Win::LX_Window& w,
              uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Sprite constuctor with the filename (UTF-8)
    LX_Sprite(const UTF8string& filename, LX_Win::LX_Window& w,
              uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Sprite constuctor with a file buffer
    LX_Sprite(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
              uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    virtual void draw();
    /**
    *   @fn virtual void draw(LX_AABB * box)
    *
    *   Draw the current sprite on the window
    *
    *   @param [in] box A pointer to the dimension (coordinates, size)
    *          of the sprite that will be drawn.
    *          If the box is NULL, then the sprite is drawn on the entire screen
    *
    *   @note The window is specified at object construction
    */
    virtual void draw(LX_AABB * box);
    /**
    *   @fn virtual void draw(LX_AABB * box, const double angle)
    *
    *   Draw an area of the current sprite on the window with rotation
    *
    *   @param [in] box A pointer to the dimension (coordinates, size)
    *          of the sprite that will be drawn.
    *          If the box is NULL, then the sprite is drawn on the entire screen
    *
    *   @param [in] angle The angle to rotate the sprite (in radian)
    *
    *   @note The window is specified at object construction
    */
    virtual void draw(LX_AABB * box, const double angle);
    /**
    *   @fn virtual void draw(LX_AABB * box, const double angle, const short mirror)
    *
    *   Draw the current sprite on the window with rotation
    *
    *   @param [in] box A pointer to the dimension (coordinates, size)
    *          of the sprite that will be drawn.
    *          If the box is NULL, then the sprite is drawn on the entire screen
    *
    *   @param [in] angle The angle to rotate the sprite (in radian)
    *   @param [in] mirror The flag that set the mirror effect:
    *          - LX_DRAW_MIRROR_NONE: No mirror effect
    *          - LX_MIRROR_HORIZONTAL: Horizontal mirror
    *          - LX_MIRROR_VERTICAL: Vertical mirror
    *
    *   @note The window is specified at object construction
    */
    virtual void draw(LX_AABB * box, const double angle, const short mirror);

    /// Destructor
    virtual ~LX_Sprite();
};


/**
*   @class LX_AnimatedSprite
*   @brief The animated sprite
*
*   This class describes a sprite sheet. It is used for animation.
*/
class LX_AnimatedSprite: public LX_Sprite
{
    const std::vector<LX_AABB> _coordinates;
    const size_t _SZ;
    uint32_t _delay;
    uint32_t _btime;
    size_t _iteration;
    bool _started;

public:

    /**
    *   @fn LX_AnimatedSprite(const std::string& filename, LX_Win::LX_Window& w,
    *                         const std::vector<LX_AABB>& coord, const uint32_t delay,
    *                         uint32_t format=SDL_PIXELFORMAT_RGBA8888)
    *
    *   Build an animated sprite using a filename
    *
    *   @param [in] filename The name of the file
    *   @param [in] w The window the image will be drawn on (see draw())
    *   @param [in] coord The list of coordinates for each sprite on the spritesheet
    *   @param [in] delay The delay to display each sprite of the animated image
    *   @param [in] format Optional argument that specified the format of the image
    *
    *   @sa LX_Image
    */
    LX_AnimatedSprite(const std::string& filename, LX_Win::LX_Window& w,
                      const std::vector<LX_AABB>& coord, const uint32_t delay,
                      uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Animated Sprite constuctor with the filename (UTF-8)
    LX_AnimatedSprite(const UTF8string& filename, LX_Win::LX_Window& w,
                      const std::vector<LX_AABB>& coord, const uint32_t delay,
                      uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Animated Sprite constuctor with a file buffer
    LX_AnimatedSprite(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
                      const std::vector<LX_AABB>& coord, const uint32_t delay,
                      uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    virtual bool isOpen() const;
    virtual void draw(LX_AABB * box);
    virtual void draw(LX_AABB * box, const double angle);
    virtual void draw(LX_AABB * box, const double angle, const short mirror);

    /// Destructor
    ~LX_AnimatedSprite() = default;
};


/**
*   @class LX_Surface
*   @brief The Surface
*
*   This class describes the surface for the texture streaming.
*/
class LX_Surface: private LX_Image
{
    friend class LX_StreamingImage;
    friend class LX_Device::LX_Mouse;
    SDL_Surface * _surface;

public:

    /// Surface constuctor
    LX_Surface(const std::string& filename, LX_Win::LX_Window& w,
               uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Surface Sprite constuctor with the filename (UTF-8)
    LX_Surface(const UTF8string& filename, LX_Win::LX_Window& w,
               uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Surface Sprite constuctor with a file buffer
    LX_Surface(LX_FileIO::LX_FileBuffer& buffer, LX_Win::LX_Window& w,
               uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    virtual bool isOpen() const;

    /// Destructor
    virtual ~LX_Surface();
};


/**
*   @class LX_StreamingImage
*   @brief A special image for texture streaming
*
*   This class describes an image used for texture streaming
*/
class LX_StreamingImage: public LX_Image
{
    SDL_Surface *_screen;
    bool _update;

public:

    /**
    *   @fn LX_StreamingImage(LX_Win::LX_Window& w, uint32_t format=SDL_PIXELFORMAT_RGBA8888)
    *
    *   Build the texture
    *
    *   @param [in] w The window the image will be drawn on (see draw())
    *   @param [in] format Optional argument that specified the format of the image
    *   @sa LX_Image
    */
    LX_StreamingImage(LX_Win::LX_Window& w, uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    virtual bool isOpen() const;
    /**
    *   @fn bool blit(LX_Surface& s, LX_AABB& rect)
    *
    *   Put the surface given in argument on the current texture
    *
    *   @param [in] s The surface to put
    *   @param [in] rect The area of the surface to put
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

    /// Destructor
    virtual ~LX_StreamingImage();
};


/**
*   @class LX_TextImage
*   @brief The text image
*
*   This abstract class describes an image build from a text.
*/
class LX_TextImage: public LX_Image
{

protected:

    UTF8string _text;
    LX_TrueTypeFont::LX_Font& _font;
    unsigned int _size;
    LX_AABB _dimension;

    virtual void updateTexture_() = 0;

public:

    /**
    *   @fn LX_TextImage(LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
    *                    uint32_t format=SDL_PIXELFORMAT_RGBA8888)
    *   @brief Constructor
    *
    *   @param [in] font The font that will be used for drawing the text
    *   @param [in] w The window the image will be drawn on (see draw())
    *   @param [in] format Optional argument that specified the format of the image
    *               See LX_Image for more information
    *
    */
    LX_TextImage(LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                 uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /**
    *   @fn LX_TextImage(std::string text, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
    *                    LX_Win::LX_Window& w, uint32_t format=SDL_PIXELFORMAT_RGBA8888)
    *   @brief Constructor
    *
    *   @param [in] text The text that will be drawn on the screen
    *   @param [in] sz The size of the text
    *   @param [in] font The font that will be used for drawing the text
    *   @param [in] w The window the image will be drawn on (see draw())
    *   @param [in] format Optional argument that specified the format of the image
    *               See LX_Image for more information
    *
    */
    LX_TextImage(std::string text, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
                 LX_Win::LX_Window& w, uint32_t format=SDL_PIXELFORMAT_RGBA8888);
    /**
    *   @fn LX_TextImage(const UTF8string& text, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
    *                    LX_Win::LX_Window& w, uint32_t format=SDL_PIXELFORMAT_RGBA8888)
    *   @brief Constructor
    *
    *   @param [in] text The text that will be drawn on the screen
    *   @param [in] sz The size of the text
    *   @param [in] font The font that will be used for drawing the text
    *   @param [in] w The window the image will be drawn on (see draw())
    *   @param [in] format Optional argument that specified the format of the image
    *               See LX_Image for more information
    *
    */
    LX_TextImage(const UTF8string& text, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
                 LX_Win::LX_Window& w, uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    virtual void draw();
    /**
    *   @fn virtual void draw(const double angle)
    *
    *   Draw the current text on the window with rotation and mirror effect
    *
    *   @param [in] angle The angle to rotate the sprite (in radian)
    *
    *   @note The window is specified at object construction
    */
    virtual void draw(const double angle);
    /**
    *   @fn virtual void draw(const double angle, const short mirror)
    *
    *   Draw the current text on the window with rotation and mirror effect
    *
    *   @param [in] angle The angle to rotate the sprite (in radian)
    *   @param [in] mirror The flag that set the mirror effect:
    *          - LX_DRAW_MIRROR_NONE: No mirror effect
    *          - LX_MIRROR_HORIZONTAL: Horizontal mirror
    *          - LX_MIRROR_VERTICAL: Vertical mirror
    *
    *   @note The window is specified at object construction
    */
    virtual void draw(const double angle, const short mirror);

    /**
    *   @fn const UTF8string getText() const
    *   Get the text
    *   @return the text
    */
    const UTF8string getText() const;

    /**
    *   @fn void setPosition(int x, int y)
    *
    *   Set the position of the current text
    *
    *   @param [in] x The new X position
    *   @param [in] y The new Y position
    *
    */
    void setPosition(int x, int y);
    /**
    *   @fn virtual void setText(std::string text, unsigned int sz) = 0
    *
    *   Set the text
    *
    *   @param [in] text The text to set
    *   @param [in] sz The new size of the text
    *
    *   @note This function updates the image of the text
    */
    virtual void setText(std::string text, unsigned int sz) = 0;
    /**
    *   @fn virtual void setText(const UTF8string& text, unsigned int sz) = 0;
    *
    *   Set the text
    *
    *   @param [in] text The utf-8 text to set
    *   @param [in] sz The new size of the text
    *
    *   @note This function updates the image of the text
    */
    virtual void setText(const UTF8string& text, unsigned int sz) = 0;
    /**
    *   @fn virtual void setSize(unsigned int sz) = 0
    *
    *   Set the size of the text
    *
    *   @param [in] sz The new size of the text
    *
    *   @note This function updates the image of the text
    */
    virtual void setSize(unsigned int sz) = 0;

    /// Destructor
    virtual ~LX_TextImage();
};


/**
*   @class LX_SolidTextImage
*   @brief The solid text image
*
*   This class describes a solid text image.
*   A solid text image is just a text that is quickly and dirty drawn on the screen.
*
*   Using this class for drawing text is fast.
*/
class LX_SolidTextImage: public LX_TextImage
{
protected:

    virtual void updateTexture_();

public:

    /// Constructor without the text
    LX_SolidTextImage(LX_TrueTypeFont::LX_Font& font,LX_Win::LX_Window& w,
                      uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Constructor using the text
    LX_SolidTextImage(std::string text, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
                      LX_Win::LX_Window& w, uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Constructor using the utf-8 text
    LX_SolidTextImage(const UTF8string& text, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
                      LX_Win::LX_Window& w, uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    virtual void setText(std::string text, unsigned int sz);
    virtual void setText(const UTF8string& text, unsigned int sz);
    virtual void setSize(unsigned int sz);

    /// Destructor
    ~LX_SolidTextImage() = default;
};


/**
*   @class LX_ShadedTextImage
*   @brief The shaded text image
*
*   This class describes a shaded text image.
*   A shaded text image is a text that is slowly but nicely drawn on the screen
*   with a background color that should be defined.
*
*   By default, at instantiation, the background color is black, bu it can be
*   set using LX_ShadedImage::setColor()
*/
class LX_ShadedTextImage: public LX_TextImage
{
    SDL_Color _bgcolor;

protected:

    virtual void updateTexture_();

public:

    /// Constructor without the text
    LX_ShadedTextImage(LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                       uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Constructor using the text
    LX_ShadedTextImage(std::string text, unsigned int sz,
                       LX_TrueTypeFont::LX_Font& font, SDL_Color& c,
                       LX_Win::LX_Window& w, uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Constructor using the utf-8 text
    LX_ShadedTextImage(const UTF8string& text, unsigned int sz,
                       LX_TrueTypeFont::LX_Font& font, SDL_Color& c,
                       LX_Win::LX_Window& w, uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    virtual void setText(std::string text, unsigned int sz);
    virtual void setText(const UTF8string& text, unsigned int sz);
    /**
    *   @fn virtual void setText(std::string text, SDL_Color c, unsigned int sz)
    *
    *   Set the text with its color
    *
    *   @param [in] text The text to set
    *   @param [in] c The color of the text
    *   @param [in] sz The new size of the text
    *
    *   @note This function updates the image of the text
    */
    virtual void setText(std::string text, SDL_Color c, unsigned int sz);
    /**
    *   @fn virtual void setText(const UTF8string& text, SDL_Color c, unsigned int sz)
    *
    *   Set the utf-8 text with its color
    *
    *   @param [in] text The utf-8 text to set
    *   @param [in] c The color of the text
    *   @param [in] sz The new size of the text
    *
    *   @note This function updates the image of the text
    */
    virtual void setText(const UTF8string& text, SDL_Color c, unsigned int sz);
    virtual void setSize(unsigned int sz);

    /**
    *   @fn void setBgColor(SDL_Color c)
    *
    *   Set the color of the background behind the text
    *
    *   @param [in] c The color of the text
    *
    *   @note 1 - This function updates the image of the text
    *   @note 2 - In order to
    */
    void setBgColor(SDL_Color c);

    /// Destructor
    ~LX_ShadedTextImage() = default;
};


/**
*   @class LX_BlendedTextImage
*   @brief The blended text image
*
*   This class describes a blended text image.
*   A blended text image is a text that is "very" slowly
*   but very nicely drawn on the screen.

*   Using this class for drawing text should be slow, in particular if
*   you call LX_BlendedImage::setText() and LX_BlendedImage::setSize() frequently.
*/
class LX_BlendedTextImage: public LX_TextImage
{
protected:

    virtual void updateTexture_();

public:

    /// Constructor without the text
    LX_BlendedTextImage(LX_TrueTypeFont::LX_Font& font,LX_Win::LX_Window& w,
                        uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Constructor using the text
    LX_BlendedTextImage(std::string text, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
                        LX_Win::LX_Window& w, uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    /// Constructor using the utf-8 text
    LX_BlendedTextImage(const UTF8string& text, unsigned int sz, LX_TrueTypeFont::LX_Font& font,
                        LX_Win::LX_Window& w, uint32_t format=SDL_PIXELFORMAT_RGBA8888);

    virtual void setText(std::string text, unsigned int sz);
    virtual void setText(const UTF8string& text, unsigned int sz);
    virtual void setSize(unsigned int sz);

    /// Destructor
    ~LX_BlendedTextImage() = default;
};

};

#endif  // LX_IMAGE_H_INCLUDED

