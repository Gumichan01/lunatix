
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

#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

/**
*   @file Texture.hpp
*   @brief The Texture header file
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/Colour.hpp>
#include <Lunatix/Format.hpp>
#include <Lunatix/ImgRect.hpp>
#include <Lunatix/utils/utf8_string.hpp>

#include <utility>
#include <exception>
#include <vector>


struct SDL_Surface;
struct SDL_Texture;


namespace lx
{

//  Forward declaration

namespace Win
{
class Window;
}

namespace Device
{
class Mouse;
}

namespace TrueTypeFont
{
class Font;
}

namespace FileIO
{
class FileBuffer;
}

//  Forward declaration (END)

namespace Graphics
{

enum class MIRROR
{
    /// Flag to define no mirror while drawing a texture
    NONE       = 0,
    /// Flag to define horizontal mirror while drawing a texture
    HORIZONTAL = 1,
    /// Flag to define vertical mirror while drawing a texture
    VERTICAL   = 2,
};

/// Not supposed to be used
static constexpr ImgRect RNULL = {{0, 0}, 0, 0};

/**
*   @class ImageException
*   @brief Exception class related to the image handling
*/
class ImageException final : public std::exception
{
    std::string _string_error;

public:

    explicit ImageException( std::string err );
    ImageException( const ImageException& me );
    /// Get the error message
    virtual const char * what() const noexcept override;
    ~ImageException() = default;
};


/**
*   @class Texture
*   @brief The texture object
*
*   This class describes a texture.
*/
class Texture
{
    friend class BufferedImage;

    Texture( Texture& ) = delete;
    Texture( Texture&& ) = delete;
    Texture& operator =( const Texture& ) = delete;
    Texture&& operator =( const Texture&& ) = delete;

protected:

    SDL_Texture * _texture;
    lx::Win::Window& _win;
    PixelFormat _format;

    Texture( lx::Win::Window& w, PixelFormat format );
    Texture( SDL_Texture * t, lx::Win::Window& w,
             PixelFormat format = PixelFormat::RGBA8888 );

    Texture( const std::string& filename, lx::Win::Window& w,
             PixelFormat format = PixelFormat::RGBA8888 );

    Texture( const UTF8string& filename, lx::Win::Window& w,
             PixelFormat format = PixelFormat::RGBA8888 );
public:

    virtual void draw() noexcept = 0;

    /**
    *   @deprecated bind() will be put in a new sub-class and removed from Texture in 0.14.0
    *
    *   @fn bool bind(float *iw = nullptr, float *ih = nullptr) noexcept
    *
    *   Bind a texture (its internal texture) to the OpenGL context
    *   of the OpenGl window where the texture is drawn on
    *   in order to use the OpenGL functions.
    *
    *   @param [out] iw (Optional) a pointer to a float value of which will be
    *         filled with the texture width. See notes.
    *   @param [out] ih (Optional) a pointer to a float value which will be
    *         filled with the texture width. See notes.
    *
    *   @return TRUE on success. FALSE if the operation is not supported.
    *
    *   @note 1 - If provided, **iw** and **ih** will be filled with
    *        the width and height values suitable for the provided texture.
    *        In most cases, both will be 1.0, however, on systems that support the
    *        GL_ARB_texture_rectangle extension, these values will actually be the
    *        pixel width and height used to create the texture, so this factor needs
    *        to be taken into account when providing texture coordinates to OpenGL.
    *
    *   @note 2 - This functions change the focused OpenGL window
    *        in order to bind the texture to the OpenGL context of the window
    *        where it is usually drawn on.
    *        That is to say the function can be only called if the window is
    *        an OpenGL window. Otherwise, bind() returns FALSE.
    */
    bool bind( float * iw = nullptr, float * ih = nullptr ) noexcept;
    /**
    *   @deprecated unbind() will be put in a new sub-class and removed from Texture in 0.14.0
    *
    *   @fn bool unbind() noexcept
    *
    *   Unbind a texture
    *
    *   @return TRUE on success.FALSE if the operation is not supported.
    */
    bool unbind() noexcept;

    /**
    *   @fn lx::Win::Window& getWindow() const noexcept
    *   Get the window where the texture is drawn on
    *   @return The window
    */
    lx::Win::Window& getWindow() const noexcept;
    /**
    *   @fn PixelFormat getFormat() const noexcept
    *   Get the format of the texture
    *   @return The format
    */
    PixelFormat getFormat() const noexcept;


    virtual ~Texture();
};


/**
*   @class Sprite
*   @brief The sprite
*/
class Sprite: public Texture
{
    friend class BufferedImage;
    ImgRect _img_rect;
    UTF8string _filename;

protected:

    Sprite( SDL_Texture * t, lx::Win::Window& w, const UTF8string& filename,
            const ImgRect& img_rect,
            PixelFormat format = PixelFormat::RGBA8888 );

public:

    /**
    *   @exception ImageException On failure
    */
    Sprite( const std::string& filename, lx::Win::Window& w,
            PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    Sprite( const std::string& filename, lx::Win::Window& w,
            const ImgRect& img_rect,
            PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    Sprite( const UTF8string& filename, lx::Win::Window& w,
            PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    Sprite( const UTF8string& filename, lx::Win::Window& w,
            const ImgRect& img_rect,
            PixelFormat format = PixelFormat::RGBA8888 );

    virtual void draw() noexcept override;
    /**
    *   @fn virtual void draw(const ImgRect& box) noexcept
    *
    *   Draw the current sprite on the window
    *
    *   @param [in] box A pointer to the dimension (coordinates, size)
    *         of the sprite that will be drawn. If the box is *nullptr*,
    *         then the sprite is drawn on the entire screen
    *
    *   @note The window is specified at object construction
    */
    virtual void draw( const ImgRect& box ) noexcept;
    /**
    *   @fn virtual void draw(const ImgRect& box, const double angle) noexcept
    *
    *   Draw an area of the current sprite on the window with rotation
    *
    *   @param [in] box A pointer to the dimension (coordinates, size)
    *         of the sprite that will be drawn. If the box is *nullptr*,
    *         then the sprite is drawn on the entire screen
    *
    *   @param [in] angle The angle to rotate the sprite (in radian)
    *
    *   @note The window is specified at object construction
    */
    virtual void draw( const ImgRect& box, const double angle ) noexcept;
    /**
    *   @fn virtual void draw(const ImgRect& box, const double angle, const MIRROR mirror) noexcept
    *
    *   Draw the current sprite on the window with rotation
    *
    *   @param [in] box A pointer to the dimension (coordinates, size)
    *         of the sprite that will be drawn. If the box is *nullptr*,
    *         then the sprite is drawn on the entire screen
    *
    *   @param [in] angle The angle to rotate the sprite (in radian)
    *   @param [in] mirror The flag that set the mirror effect:
    *         - MIRROR_NONE: No mirror effect
    *         - MIRROR_HORIZONTAL: Horizontal mirror
    *         - MIRROR_VERTICAL: Vertical mirror
    *
    *   @note The window is specified at object construction
    */
    virtual void draw( const ImgRect& box, const double angle, const MIRROR mirror ) noexcept;

    /**
    *   @fn UTF8string getFileName() noexcept
    *   Returns the name of the file associated with this texture
    *   @return The name of the file (UTF-8 format)
    */
    UTF8string getFileName() noexcept;

    virtual ~Sprite() = default;
};


/**
*   @class AnimatedSprite
*   @brief The animated sprite
*
*   This class describes a sprite sheet used for animation.
*/
class AnimatedSprite final : public Sprite
{
    friend class BufferedImage;
    const std::vector<ImgRect> _coordinates;
    const size_t _SZ;
    uint32_t _delay;    // Delay to display a part of the sprite sheet
    uint32_t _btime;
    size_t _frame;
    bool _started;
    bool _loop;         // TRUE: Infinite loop - FALSE: one loop
    bool _drawable;

    AnimatedSprite( SDL_Texture * t, lx::Win::Window& w,
                    const std::vector<ImgRect>& coord, const uint32_t delay,
                    bool loop, const UTF8string& filename,
                    PixelFormat format = PixelFormat::RGBA8888 );

public:

    /**
    *   @fn AnimatedSprite(const std::string& filename, lx::Win::Window& w,
    *                        const std::vector<ImgRect>& coord, const uint32_t delay,
    *                        bool loop, PixelFormat format = PixelFormat::RGBA8888)
    *
    *   Build an animated sprite from a sprite sheet
    *
    *   @param [in] filename The sprite sheet file to load
    *   @param [in] w The window the animated sprite will be drawn on → see *draw()*
    *   @param [in] coord The list of coordinates for each sprite on the sprite sheet
    *   @param [in] delay The delay to display each sprite of the sprite sheet
    *   @param [in] loop Boolean value that specify if the animation must be looped infinitely
    *   @param [in] format Optional argument that specified the format of every sprites
    *
    *   @exception ImageException On failure
    *
    *   @sa Sprite
    *   @sa Texture
    */
    AnimatedSprite( const std::string& filename, lx::Win::Window& w,
                    const std::vector<ImgRect>& coord, const uint32_t delay,
                    bool loop, PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    AnimatedSprite( const UTF8string& filename, lx::Win::Window& w,
                    const std::vector<ImgRect>& coord, const uint32_t delay,
                    bool loop, PixelFormat format = PixelFormat::RGBA8888 );

    using Sprite::draw;
    virtual void draw( const ImgRect& box ) noexcept override;
    virtual void draw( const ImgRect& box, const double angle ) noexcept override;
    virtual void draw( const ImgRect& box, const double angle,
                       const MIRROR mirror ) noexcept override;

    /**
    *   @fn void resetAnimation() noexcept
    *   Reset the animation to the beginning
    */
    void resetAnimation() noexcept;

    /**
    *   @fn uint32_t getFrameDelay() const noexcept
    *   Get the delay to display each frame of the sprite sheet
    *   @return The delay
    */
    uint32_t getFrameDelay() const noexcept;
    /**
    *   @fn bool isInfinitelyLooped() const noexcept
    *   Check the animation is infinitely looped
    *   @return TRUE if the animation is looped infinitely, FALSE otherwise
    */
    bool isInfinitelyLooped() const noexcept;

    ~AnimatedSprite() = default;
};


/**
*   @class BufferedImage
*   @brief The Buffered image
*
*   This class describes an image stored in memory.
*   Any texture can be generated from this buffered.
*
*   @note This class throws ImageException if an object cannot be created
*/
class BufferedImage final
{
    friend class StreamingTexture;
    friend class lx::Device::Mouse;
    friend class lx::FileIO::FileBuffer;
    friend class lx::Win::Window;

    SDL_Surface * _surface = nullptr;
    UTF8string _filename{""};

    BufferedImage( const BufferedImage& ) = delete;
    BufferedImage& operator =( const BufferedImage& ) = delete;

    BufferedImage( SDL_Surface * s,
                   PixelFormat format = PixelFormat::RGBA8888 );
    BufferedImage( SDL_Surface * s, const std::string& filename,
                   PixelFormat format = PixelFormat::RGBA8888 );

    bool _retrieveColours( const uint32_t pixel, Uint8& r, Uint8& g, Uint8& b, Uint8& a ) const noexcept;

    uint32_t _updateGrayscaleColour( const Uint8 alpha, Uint8 v ) const noexcept;
    uint32_t _updateNegativeColour( const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a ) const noexcept;

    uint32_t _convertGrayscalePixel( const uint32_t pixel ) const noexcept;
    uint32_t _convertNegativePixel( const uint32_t pixel ) const noexcept;

public:

    /**
    *   @exception ImageException On failure
    */
    BufferedImage( const std::string& filename,
                   PixelFormat format = PixelFormat::RGBA8888 );

    /**
    *   @exception ImageException On failure
    */
    BufferedImage( const UTF8string& filename,
                   PixelFormat format = PixelFormat::RGBA8888 );

    /**
    *   @fn void convertGrayscale() noexcept
    */
    BufferedImage& convertGrayscale() noexcept;

    /**
    *   @fn void convertNegative()
    */
    BufferedImage& convertNegative() noexcept;

    /**
    *   @fn Sprite * generateSprite(lx::Win::Window& w, const ImgRect& area) const
    *   Create a sprite from the current buffered image
    *
    *   @param [in] w The window to link the sprite to → see *draw()*
    *   @param [in] area (Optional) Area of the sprite to display
    *   @return A new fresh allocated sprite on success, *nullptr* otherwise
    *   @exception ImageException On failure
    */
    Sprite * generateSprite( lx::Win::Window& w,
                             const ImgRect& area = RNULL ) const;
    /**
    *   @fn AnimatedSprite * generateAnimatedSprite(lx::Win::Window& w,
    *                                   const std::vector<ImgRect>& coord,
    *                                   const uint32_t delay) const
    *
    *   Create an animated sprite from the current buffered image
    *
    *   @param [in] w The window to link the sprite to → see *draw()*
    *   @param [in] coord The list of coordinates for each sprite on the sprite sheet
    *   @param [in] delay The delay to display each sprite of the sprite sheet
    *   @param [in] loop Boolean value that specify if the animation must be looped infinitely
    *
    *   @return A new fresh allocated animated sprite on success, *nullptr* otherwise
    *   @exception ImageException On failure
    */
    AnimatedSprite *
    generateAnimatedSprite( lx::Win::Window& w,
                            const std::vector<ImgRect>& coord,
                            const uint32_t delay, bool loop ) const;

    /**
    *   @fn UTF8string getFileName() noexcept
    *   Returns the name of the file associated with this texture
    *   @return The name of the file (UTF-8 format)
    */
    UTF8string getFileName() noexcept;

    ~BufferedImage();
};


/**
*   @class StreamingTexture
*   @brief A special texture for texture streaming.
*
*   This class describes a texture for streaming.
*/
class StreamingTexture final : public Texture
{
    SDL_Surface * _screen;
    bool _update;

    StreamingTexture( const StreamingTexture& ) = delete;
    StreamingTexture& operator =( const StreamingTexture& ) = delete;

public:

    /**
    *   @exception ImageException On failure
    */
    StreamingTexture( lx::Win::Window& w,
                      PixelFormat format = PixelFormat::RGBA8888 );

    /**
    *   @fn bool blit(BufferedImage& s, const ImgRect& rect) noexcept
    *
    *   Put the surface given in argument on the current texture
    *
    *   @param [in] s The surface to put
    *   @param [in] rect The area of the surface to put
    *
    *   @return TRUE on success, FALSE otherwise
    */
    bool blit( BufferedImage& s, const ImgRect& rect ) noexcept;
    /**
    *   @fn void update() noexcept
    *   Update the texture in order to be drawn on the window
    *
    *   @note After each call of update(), you need to call draw()
    *        in order to draw the new texture on the window
    */
    void update() noexcept;

    virtual void draw() noexcept override;

    virtual ~StreamingTexture();
};


/**
*   @class TextTexture
*   @brief The text texture.
*
*   This abstract class describes a texture build from a text.
*/
class TextTexture: public Texture
{

protected:

    UTF8string _text;
    lx::TrueTypeFont::Font& _font;
    unsigned int _size;
    Colour _colour;
    ImgRect _dimension;

    virtual void updateTexture_() noexcept = 0;

    TextTexture( lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                 PixelFormat format = PixelFormat::RGBA8888 );

    TextTexture( const std::string& text, lx::TrueTypeFont::Font& font,
                 lx::Win::Window& w,
                 PixelFormat format = PixelFormat::RGBA8888 );

    TextTexture( const UTF8string& text, lx::TrueTypeFont::Font& font,
                 lx::Win::Window& w,
                 PixelFormat format = PixelFormat::RGBA8888 );

    TextTexture( const std::string& text, unsigned int sz,
                 lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                 PixelFormat format = PixelFormat::RGBA8888 );

    TextTexture( const UTF8string& text, unsigned int sz,
                 lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                 PixelFormat format = PixelFormat::RGBA8888 );

public:

    virtual void draw() noexcept override;
    /**
    *   @fn virtual void draw(const double angle) noexcept
    *
    *   Draw the current text on the window with rotation and mirror effect
    *
    *   @param [in] angle The angle to rotate the sprite (in radian)
    *
    *   @note The window is specified at object construction
    */
    virtual void draw( const double angle ) noexcept;
    /**
    *   @fn virtual void draw(const double angle, const MIRROR mirror) noexcept
    *
    *   Draw the current text on the window with rotation and mirror effect
    *
    *   @param [in] angle The angle to rotate the sprite (in radian)
    *   @param [in] mirror The flag that set the mirror effect:
    *         - DRAW_MIRROR_NONE: No mirror effect
    *         - MIRROR_HORIZONTAL: Horizontal mirror
    *         - MIRROR_VERTICAL: Vertical mirror
    *
    *   @note The window is specified at object construction
    */
    virtual void draw( const double angle, const MIRROR mirror ) noexcept;

    /**
    *   @fn const UTF8string getText() const noexcept
    *   Get the text
    *   @return The text
    */
    const UTF8string getText() const noexcept;
    /**
    *   @fn unsigned int getTextSize() const noexcept
    *   Get the text size
    *   @return The text size
    */
    unsigned int getTextSize() const noexcept;
    /**
    *   @deprecated This signature will be removed in v0.14.0
    *   Please use the other version that returns a pair
    *
    *   @fn void getTextDimension(int& w, int& h) const noexcept
    *
    *   @param [out] w Width value returned by this function
    *   @param [out] h Height value returned by this function
    */
    void getTextDimension( int& w, int& h ) const noexcept;
    /**
    *   @fn std::pair<int, int> getTextDimension() const noexcept
    *   @return The dimension — a pair of integers
    */
    std::pair<int, int> getTextDimension() const noexcept;
    /**
    *   @fn int getTextWidth() const noexcept
    *   Get the width of the text displayed on the screen
    *   @return The width
    */
    int getTextWidth() const noexcept;
    /**
    *   @fn int getTextHeight() const noexcept
    *   Get the height of the text displayed on the screen
    *   @return The height
    */
    int getTextHeight() const noexcept;
    /**
    *   @fn Colour getTextColour() const noexcept
    *   Get the text colour
    *   @return The text size
    */
    Colour getTextColour() const noexcept;
    /**
    *   @fn void setPosition(int x, int y) noexcept
    *
    *   Set the position of the current text
    *
    *   @param [in] x The new X position
    *   @param [in] y The new Y position
    */
    void setPosition( int x, int y ) noexcept;
    /**
    *   @fn void setPosition(const lx::Graphics::ImgCoord& pos) noexcept
    *   @param [in] pos
    */
    void setPosition( const lx::Graphics::ImgCoord& pos ) noexcept;
    /**
    *   @fn virtual void setText(const std::string& text) noexcept
    *
    *   Set the text to display
    *   @param [in] text The text to set
    *   @note This function updates the texture of the text
    */
    virtual void setText( const std::string& text ) noexcept;
    /**
    *   @fn virtual void setText(const UTF8string& text) noexcept
    *
    *   Set the text to display
    *   @param [in] text The text to set
    *   @note This function updates the texture of the text
    */
    virtual void setText( const UTF8string& text ) noexcept;
    /**
    *   @fn virtual void setText(const std::string& text, unsigned int sz) noexcept
    *
    *   Set the text (with its size) to display
    *
    *   @param [in] text The text to set
    *   @param [in] sz The new size of the text
    *   @note This function updates the texture of the text
    */
    virtual void setText( const std::string& text, unsigned int sz ) noexcept;
    /**
    *   @fn virtual void setText(const UTF8string& text, unsigned int sz) noexcept
    *
    *   Set the text (with its size) to display
    *
    *   @param [in] text The utf-8 text to set
    *   @param [in] sz The new size of the text
    *   @note This function updates the texture of the text
    */
    virtual void setText( const UTF8string& text, unsigned int sz ) noexcept;
    /**
    *   @fn virtual void setTextSize(unsigned int sz) noexcept
    *
    *   Set the size of the text that will be displayed
    *
    *   @param [in] sz The new size of the text
    *   @note This function updates the texture of the text
    */
    virtual void setTextSize( unsigned int sz ) noexcept;
    /**
    *   @fn virtual void setTextColour(const Colour& c) noexcept
    *
    *   Set the colour of the text
    *
    *   @param [in] c the colour of the text
    *   @note This function updates the texture of the text
    */
    virtual void setTextColour( const Colour& c ) noexcept;

    virtual ~TextTexture();
};


/**
*   @class SolidTextTexture
*   @brief The solid text texture
*
*   This class describes a solid text texture.
*   A solid text texture is just a text that is quickly
*   and dirty drawn on the screen.
*
*   Using this class for drawing text is fast.
*/
class SolidTextTexture final : public TextTexture
{
protected:

    virtual void updateTexture_() noexcept;

public:

    /**
    *   @exception ImageException On failure
    */
    SolidTextTexture( lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                      PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    SolidTextTexture( const std::string& text, lx::TrueTypeFont::Font& font,
                      lx::Win::Window& w,
                      PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    SolidTextTexture( const UTF8string& text, lx::TrueTypeFont::Font& font,
                      lx::Win::Window& w,
                      PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    SolidTextTexture( const std::string& text, unsigned int sz,
                      lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                      PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    SolidTextTexture( const UTF8string& text, unsigned int sz,
                      lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                      PixelFormat format = PixelFormat::RGBA8888 );

    ~SolidTextTexture() = default;
};


/**
*   @class ShadedTextTexture
*   @brief The shaded text texture
*
*   This class describes a shaded text texture.
*   A shaded text texture is a text that is slowly but nicely drawn on the screen
*   with a background colour that should be defined.
*
*   By default, at instantiation, the background colour is black, but it can be
*   set using *setBgColour()*
*
*   @note If the format of the texture supoports transparency,
*         the alpha value of the entire texture is calculated as the average of
*         the background colour and the text colour
*   @note → ``` alpha = (bgcolour + textcolour) / 2 ```
*/
class ShadedTextTexture final : public TextTexture
{
    Colour _bgcolour;

    uint8_t alpha_();

protected:

    virtual void updateTexture_() noexcept;

public:

    /**
    *   @exception ImageException On failure
    */
    ShadedTextTexture( lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                       PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    ShadedTextTexture( const std::string& text, lx::TrueTypeFont::Font& font,
                       const Colour& bg, lx::Win::Window& w,
                       PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    ShadedTextTexture( const UTF8string& text, lx::TrueTypeFont::Font& font,
                       const Colour& bg, lx::Win::Window& w,
                       PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    ShadedTextTexture( const std::string& text, unsigned int sz,
                       lx::TrueTypeFont::Font& font, const Colour& bg,
                       lx::Win::Window& w,
                       PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    ShadedTextTexture( const UTF8string& text, unsigned int sz,
                       lx::TrueTypeFont::Font& font, const Colour& bg,
                       lx::Win::Window& w,
                       PixelFormat format = PixelFormat::RGBA8888 );

    /**
    *   @fn Colour getBgColour() noexcept
    *
    *   Get the colour of the background behind the text
    *   @return THe background colour
    */
    Colour getBgColour() noexcept;
    /**
    *   @fn void setBgColour(const Colour& bg) noexcept
    *
    *   Set the colour of the background behind the text
    *
    *   @param [in] bg The background colour of the text
    *   @note This function updates the texture of the text
    */
    void setBgColour( const Colour& bg ) noexcept;

    ~ShadedTextTexture() = default;
};


/**
*   @class BlendedTextTexture
*   @brief The blended text texture
*
*   This class describes a blended text texture.
*   A blended text texture is a text that is "very" slowly
*   but very nicely drawn on the screen.
*
*   Using this class for drawing text should be very slow, in particular if
*   you call BlendedImage::setText() and BlendedImage::setTextSize() frequently.
*/
class BlendedTextTexture final : public TextTexture
{
protected:

    virtual void updateTexture_() noexcept;

public:
    /**
    *   @exception ImageException On failure
    */
    BlendedTextTexture( lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                        PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    BlendedTextTexture( const std::string& text, lx::TrueTypeFont::Font& font,
                        lx::Win::Window& w,
                        PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    BlendedTextTexture( const UTF8string& text, lx::TrueTypeFont::Font& font,
                        lx::Win::Window& w,
                        PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    BlendedTextTexture( const std::string& text, unsigned int sz,
                        lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                        PixelFormat format = PixelFormat::RGBA8888 );
    /**
    *   @exception ImageException On failure
    */
    BlendedTextTexture( const UTF8string& text, unsigned int sz,
                        lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                        PixelFormat format = PixelFormat::RGBA8888 );

    ~BlendedTextTexture() = default;
};

}   // Graphics

}  // lx

#endif  // IMAGE_H_INCLUDED
