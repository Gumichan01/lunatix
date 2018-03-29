
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

#ifndef LX_IMAGE_H_INCLUDED
#define LX_IMAGE_H_INCLUDED

/**
*   @file LX_Texture.hpp
*   @brief The Texture header file
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/LX_Colour.hpp>
#include <LunatiX/LX_Format.hpp>
#include <LunatiX/LX_ImgRect.hpp>
#include <LunatiX/utils/utf8_string.hpp>

#include <utility>
#include <exception>
#include <vector>


struct SDL_Surface;
struct SDL_Texture;

namespace LX_FileIO
{
class LX_FileBuffer;
}

namespace LX_Win
{
class LX_Window;
}

namespace LX_Device
{
class LX_Mouse;
}

namespace LX_TrueTypeFont
{
class LX_Font;
}


namespace LX_Graphics
{

enum class LX_MIRROR : short
{
    /// Flag to define no mirror while drawing a texture
    NONE       = 0,
    /// Flag to define horizontal mirror while drawing a texture
    HORIZONTAL = 1,
    /// Flag to define vertical mirror while drawing a texture
    VERTICAL   = 2,
};

/// Not supposed to be used
static constexpr LX_ImgRect RNULL = {{0,0},0,0};

/**
*   @class LX_ImageException final
*   @brief Exception class related to the image handling
*/
class LX_ImageException final : public std::exception
{
    std::string _string_error;

public:

    explicit LX_ImageException(std::string err);
    LX_ImageException(const LX_ImageException& me);
    /// Get the error message
    virtual const char * what() const noexcept override;
    ~LX_ImageException() = default;
};


/**
*   @class LX_Texture
*   @brief The texture object
*
*   This class describes a texture.
*/
class LX_Texture
{
    friend class LX_BufferedImage;

    LX_Texture(LX_Texture&) = delete;
    LX_Texture(LX_Texture&&) = delete;
    LX_Texture& operator =(const LX_Texture&) = delete;
    LX_Texture&& operator =(const LX_Texture&&) = delete;

protected:

    SDL_Texture * _texture;
    LX_Win::LX_Window& _win;
    LX_PixelFormat _format;

    LX_Texture(LX_Win::LX_Window& w, LX_PixelFormat format);
    LX_Texture(SDL_Texture *t, LX_Win::LX_Window& w,
               LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    LX_Texture(const std::string& filename, LX_Win::LX_Window& w,
               LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    LX_Texture(const UTF8string& filename, LX_Win::LX_Window& w,
               LX_PixelFormat format = LX_PixelFormat::RGBA8888);
public:

    virtual void draw() noexcept = 0;

    /**
    *   @deprecated bind() will be put in a new sub-class and removed from LX_Texture in 0.14.0
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
    bool bind(float *iw = nullptr, float *ih = nullptr) noexcept;
    /**
    *   @deprecated unbind() will be put in a new sub-class and removed from LX_Texture in 0.14.0
    *
    *   @fn bool unbind() noexcept
    *
    *   Unbind a texture
    *
    *   @return TRUE on success.FALSE if the operation is not supported.
    */
    bool unbind() noexcept;

    /**
    *   @fn LX_Win::LX_Window& getWindow() const noexcept
    *   Get the window where the texture is drawn on
    *   @return The window
    */
    LX_Win::LX_Window& getWindow() const noexcept;
    /**
    *   @fn LX_PixelFormat getFormat() const noexcept
    *   Get the format of the texture
    *   @return The format
    */
    LX_PixelFormat getFormat() const noexcept;


    virtual ~LX_Texture();
};


/**
*   @class LX_Sprite
*   @brief The sprite
*/
class LX_Sprite: public LX_Texture
{
    friend class LX_BufferedImage;
    LX_ImgRect _img_rect;
    UTF8string _filename;

protected:

    LX_Sprite(SDL_Texture *t, LX_Win::LX_Window& w, const UTF8string& filename,
              const LX_ImgRect& img_rect,
              LX_PixelFormat format = LX_PixelFormat::RGBA8888);

public:

    /**
    *   @exception LX_ImageException On failure
    */
    LX_Sprite(const std::string& filename, LX_Win::LX_Window& w,
              LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_Sprite(const std::string& filename, LX_Win::LX_Window& w,
              const LX_ImgRect& img_rect,
              LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_Sprite(const UTF8string& filename, LX_Win::LX_Window& w,
              LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_Sprite(const UTF8string& filename, LX_Win::LX_Window& w,
              const LX_ImgRect& img_rect,
              LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    virtual void draw() noexcept override;
    /**
    *   @fn virtual void draw(const LX_ImgRect& box) noexcept
    *
    *   Draw the current sprite on the window
    *
    *   @param [in] box A pointer to the dimension (coordinates, size)
    *         of the sprite that will be drawn. If the box is *nullptr*,
    *         then the sprite is drawn on the entire screen
    *
    *   @note The window is specified at object construction
    */
    virtual void draw(const LX_ImgRect& box) noexcept;
    /**
    *   @fn virtual void draw(const LX_ImgRect& box, const double angle) noexcept
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
    virtual void draw(const LX_ImgRect& box, const double angle) noexcept;
    /**
    *   @fn virtual void draw(const LX_ImgRect& box, const double angle, const LX_MIRROR mirror) noexcept
    *
    *   Draw the current sprite on the window with rotation
    *
    *   @param [in] box A pointer to the dimension (coordinates, size)
    *         of the sprite that will be drawn. If the box is *nullptr*,
    *         then the sprite is drawn on the entire screen
    *
    *   @param [in] angle The angle to rotate the sprite (in radian)
    *   @param [in] mirror The flag that set the mirror effect:
    *         - LX_MIRROR_NONE: No mirror effect
    *         - LX_MIRROR_HORIZONTAL: Horizontal mirror
    *         - LX_MIRROR_VERTICAL: Vertical mirror
    *
    *   @note The window is specified at object construction
    */
    virtual void draw(const LX_ImgRect& box, const double angle, const LX_MIRROR mirror) noexcept;

    /**
    *   @fn UTF8string getFileName() noexcept
    *   Returns the name of the file associated with this texture
    *   @return The name of the file (UTF-8 format)
    */
    UTF8string getFileName() noexcept;

    virtual ~LX_Sprite() = default;
};


/**
*   @class LX_AnimatedSprite final
*   @brief The animated sprite
*
*   This class describes a sprite sheet used for animation.
*/
class LX_AnimatedSprite final : public LX_Sprite
{
    friend class LX_BufferedImage;
    const std::vector<LX_ImgRect> _coordinates;
    const size_t _SZ;
    uint32_t _delay;    // Delay to display a part of the sprite sheet
    uint32_t _btime;
    size_t _frame;
    bool _started;
    bool _loop;         // TRUE: Infinite loop - FALSE: one loop
    bool _drawable;

    LX_AnimatedSprite(SDL_Texture *t, LX_Win::LX_Window& w,
                      const std::vector<LX_ImgRect>& coord, const uint32_t delay,
                      bool loop, const UTF8string& filename,
                      LX_PixelFormat format = LX_PixelFormat::RGBA8888);

public:

    /**
    *   @fn LX_AnimatedSprite(const std::string& filename, LX_Win::LX_Window& w,
    *                        const std::vector<LX_ImgRect>& coord, const uint32_t delay,
    *                        bool loop, LX_PixelFormat format = LX_PixelFormat::RGBA8888)
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
    *   @exception LX_ImageException On failure
    *
    *   @sa LX_Sprite
    *   @sa LX_Texture
    */
    LX_AnimatedSprite(const std::string& filename, LX_Win::LX_Window& w,
                      const std::vector<LX_ImgRect>& coord, const uint32_t delay,
                      bool loop, LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_AnimatedSprite(const UTF8string& filename, LX_Win::LX_Window& w,
                      const std::vector<LX_ImgRect>& coord, const uint32_t delay,
                      bool loop, LX_PixelFormat format = LX_PixelFormat::RGBA8888);


    virtual void draw(const LX_ImgRect& box) noexcept override;
    virtual void draw(const LX_ImgRect& box, const double angle) noexcept override;
    virtual void draw(const LX_ImgRect& box, const double angle,
                      const LX_MIRROR mirror) noexcept override;

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

    ~LX_AnimatedSprite() = default;
};


/**
*   @class LX_BufferedImage final
*   @brief The Buffered image
*
*   This class describes an image stored in memory.
*   Any texture can be generated from this buffered.
*
*   @note This class throws LX_ImageException if an object cannot be created
*/
class LX_BufferedImage final
{
    friend class LX_StreamingTexture;
    friend class LX_Device::LX_Mouse;
    friend class LX_FileIO::LX_FileBuffer;
    friend class LX_Win::LX_Window;

    SDL_Surface * _surface = nullptr;
    UTF8string _filename{""};

    LX_BufferedImage(const LX_BufferedImage&) = delete;
    LX_BufferedImage& operator =(const LX_BufferedImage&) = delete;

    LX_BufferedImage(SDL_Surface * s,
                     LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    LX_BufferedImage(SDL_Surface * s, const std::string& filename,
                     LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    bool _retrieveColours(Uint32 pixel, Uint8& r, Uint8& g, Uint8& b, Uint8& a) const noexcept;

    Uint32 _updateGrayscaleColour(Uint8 a, Uint8 v) const noexcept;
    Uint32 _updateNegativeColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const noexcept;

    Uint32 _convertGrayscalePixel(Uint32 pixel) const noexcept;
    Uint32 _convertNegativePixel(Uint32 pixel) const noexcept;

public:

    /**
    *   @exception LX_ImageException On failure
    */
    LX_BufferedImage(const std::string& filename,
                     LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    /**
    *   @exception LX_ImageException On failure
    */
    LX_BufferedImage(const UTF8string& filename,
                     LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    /**
    *   @fn void convertGrayscale() noexcept
    */
    LX_BufferedImage& convertGrayscale() noexcept;

    /**
    *   @fn void convertNegative()
    */
    LX_BufferedImage& convertNegative() noexcept;

    /**
    *   @fn LX_Sprite * generateSprite(LX_Win::LX_Window& w, const LX_ImgRect& area) const
    *   Create a sprite from the current buffered image
    *
    *   @param [in] w The window to link the sprite to → see *draw()*
    *   @param [in] area (Optional) Area of the sprite to display
    *   @return A new fresh allocated sprite on success, *nullptr* otherwise
    *   @exception LX_ImageException On failure
    */
    LX_Sprite * generateSprite(LX_Win::LX_Window& w,
                               const LX_ImgRect& area = RNULL) const;
    /**
    *   @fn LX_AnimatedSprite * generateAnimatedSprite(LX_Win::LX_Window& w,
    *                                   const std::vector<LX_ImgRect>& coord,
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
    *   @exception LX_ImageException On failure
    */
    LX_AnimatedSprite *
    generateAnimatedSprite(LX_Win::LX_Window& w,
                           const std::vector<LX_ImgRect>& coord,
                           const uint32_t delay, bool loop) const;

    /**
    *   @fn UTF8string getFileName() noexcept
    *   Returns the name of the file associated with this texture
    *   @return The name of the file (UTF-8 format)
    */
    UTF8string getFileName() noexcept;

    ~LX_BufferedImage();
};


/**
*   @class LX_StreamingTexture final
*   @brief A special texture for texture streaming.
*
*   This class describes a texture for streaming.
*/
class LX_StreamingTexture final : public LX_Texture
{
    SDL_Surface *_screen;
    bool _update;

    LX_StreamingTexture(const LX_StreamingTexture&) = delete;
    LX_StreamingTexture& operator =(const LX_StreamingTexture&) = delete;

public:

    /**
    *   @exception LX_ImageException On failure
    */
    LX_StreamingTexture(LX_Win::LX_Window& w,
                        LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    /**
    *   @fn bool blit(LX_BufferedImage& s, const LX_ImgRect& rect) noexcept
    *
    *   Put the surface given in argument on the current texture
    *
    *   @param [in] s The surface to put
    *   @param [in] rect The area of the surface to put
    *
    *   @return TRUE on success, FALSE otherwise
    */
    bool blit(LX_BufferedImage& s, const LX_ImgRect& rect) noexcept;
    /**
    *   @fn void update() noexcept
    *   Update the texture in order to be drawn on the window
    *
    *   @note After each call of update(), you need to call draw()
    *        in order to draw the new texture on the window
    */
    void update() noexcept;

    virtual void draw() noexcept override;

    virtual ~LX_StreamingTexture();
};


/**
*   @class LX_TextTexture
*   @brief The text texture.
*
*   This abstract class describes a texture build from a text.
*/
class LX_TextTexture: public LX_Texture
{

protected:

    UTF8string _text;
    LX_TrueTypeFont::LX_Font& _font;
    unsigned int _size;
    LX_Colour _colour;
    LX_ImgRect _dimension;

    virtual void updateTexture_() noexcept = 0;

    LX_TextTexture(LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                   LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    LX_TextTexture(const std::string& text, LX_TrueTypeFont::LX_Font& font,
                   LX_Win::LX_Window& w,
                   LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    LX_TextTexture(const UTF8string& text, LX_TrueTypeFont::LX_Font& font,
                   LX_Win::LX_Window& w,
                   LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    LX_TextTexture(const std::string& text, unsigned int sz,
                   LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                   LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    LX_TextTexture(const UTF8string& text, unsigned int sz,
                   LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                   LX_PixelFormat format = LX_PixelFormat::RGBA8888);

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
    virtual void draw(const double angle) noexcept;
    /**
    *   @fn virtual void draw(const double angle, const LX_MIRROR mirror) noexcept
    *
    *   Draw the current text on the window with rotation and mirror effect
    *
    *   @param [in] angle The angle to rotate the sprite (in radian)
    *   @param [in] mirror The flag that set the mirror effect:
    *         - LX_DRAW_MIRROR_NONE: No mirror effect
    *         - LX_MIRROR_HORIZONTAL: Horizontal mirror
    *         - LX_MIRROR_VERTICAL: Vertical mirror
    *
    *   @note The window is specified at object construction
    */
    virtual void draw(const double angle, const LX_MIRROR mirror) noexcept;

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
    void getTextDimension(int& w, int& h) const noexcept;
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
    *   @fn LX_Colour getTextColour() const noexcept
    *   Get the text colour
    *   @return The text size
    */
    LX_Colour getTextColour() const noexcept;
    /**
    *   @fn void setPosition(int x, int y) noexcept
    *
    *   Set the position of the current text
    *
    *   @param [in] x The new X position
    *   @param [in] y The new Y position
    */
    void setPosition(int x, int y) noexcept;
    /**
    *   @fn void setPosition(const LX_Graphics::LX_ImgCoord& pos) noexcept
    *   @param [in] pos
    */
    void setPosition(const LX_Graphics::LX_ImgCoord& pos) noexcept;
    /**
    *   @fn virtual void setText(const std::string& text) noexcept
    *
    *   Set the text to display
    *   @param [in] text The text to set
    *   @note This function updates the texture of the text
    */
    virtual void setText(const std::string& text) noexcept;
    /**
    *   @fn virtual void setText(const UTF8string& text) noexcept
    *
    *   Set the text to display
    *   @param [in] text The text to set
    *   @note This function updates the texture of the text
    */
    virtual void setText(const UTF8string& text) noexcept;
    /**
    *   @fn virtual void setText(const std::string& text, unsigned int sz) noexcept
    *
    *   Set the text (with its size) to display
    *
    *   @param [in] text The text to set
    *   @param [in] sz The new size of the text
    *   @note This function updates the texture of the text
    */
    virtual void setText(const std::string& text, unsigned int sz) noexcept;
    /**
    *   @fn virtual void setText(const UTF8string& text, unsigned int sz) noexcept
    *
    *   Set the text (with its size) to display
    *
    *   @param [in] text The utf-8 text to set
    *   @param [in] sz The new size of the text
    *   @note This function updates the texture of the text
    */
    virtual void setText(const UTF8string& text, unsigned int sz) noexcept;
    /**
    *   @fn virtual void setTextSize(unsigned int sz) noexcept
    *
    *   Set the size of the text that will be displayed
    *
    *   @param [in] sz The new size of the text
    *   @note This function updates the texture of the text
    */
    virtual void setTextSize(unsigned int sz) noexcept;
    /**
    *   @fn virtual void setTextColour(const LX_Colour& c) noexcept
    *
    *   Set the colour of the text
    *
    *   @param [in] c the colour of the text
    *   @note This function updates the texture of the text
    */
    virtual void setTextColour(const LX_Colour& c) noexcept;

    virtual ~LX_TextTexture();
};


/**
*   @class LX_SolidTextTexture final
*   @brief The solid text texture
*
*   This class describes a solid text texture.
*   A solid text texture is just a text that is quickly
*   and dirty drawn on the screen.
*
*   Using this class for drawing text is fast.
*/
class LX_SolidTextTexture final : public LX_TextTexture
{
protected:

    virtual void updateTexture_() noexcept;

public:

    /**
    *   @exception LX_ImageException On failure
    */
    LX_SolidTextTexture(LX_TrueTypeFont::LX_Font& font,LX_Win::LX_Window& w,
                        LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_SolidTextTexture(const std::string& text, LX_TrueTypeFont::LX_Font& font,
                        LX_Win::LX_Window& w,
                        LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_SolidTextTexture(const UTF8string& text, LX_TrueTypeFont::LX_Font& font,
                        LX_Win::LX_Window& w,
                        LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_SolidTextTexture(const std::string& text, unsigned int sz,
                        LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                        LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_SolidTextTexture(const UTF8string& text, unsigned int sz,
                        LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                        LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    ~LX_SolidTextTexture() = default;
};


/**
*   @class LX_ShadedTextTexture final
*   @brief The shaded text texture
*
*   This class describes a shaded text texture.
*   A shaded text texture is a text that is slowly but nicely drawn on the screen
*   with a background colour that should be defined.
*
*   By default, at instantiation, the background colour is black, but it can be
*   set using *setBgColour()*
*/
class LX_ShadedTextTexture final : public LX_TextTexture
{
    LX_Colour _bgcolour;

protected:

    virtual void updateTexture_() noexcept;

public:

    /**
    *   @exception LX_ImageException On failure
    */
    LX_ShadedTextTexture(LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                         LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_ShadedTextTexture(const std::string& text, LX_TrueTypeFont::LX_Font& font,
                         const LX_Colour& bg, LX_Win::LX_Window& w,
                         LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_ShadedTextTexture(const UTF8string& text, LX_TrueTypeFont::LX_Font& font,
                         const LX_Colour& bg, LX_Win::LX_Window& w,
                         LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_ShadedTextTexture(const std::string& text, unsigned int sz,
                         LX_TrueTypeFont::LX_Font& font, const LX_Colour& bg,
                         LX_Win::LX_Window& w,
                         LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_ShadedTextTexture(const UTF8string& text, unsigned int sz,
                         LX_TrueTypeFont::LX_Font& font, const LX_Colour& bg,
                         LX_Win::LX_Window& w,
                         LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    /**
    *   @fn LX_Colour getBgColour() noexcept
    *
    *   Get the colour of the background behind the text
    *   @return THe background colour
    */
    LX_Colour getBgColour() noexcept;
    /**
    *   @fn void setBgColour(const LX_Colour& bg) noexcept
    *
    *   Set the colour of the background behind the text
    *
    *   @param [in] bg The background colour of the text
    *   @note This function updates the texture of the text
    */
    void setBgColour(const LX_Colour& bg) noexcept;

    ~LX_ShadedTextTexture() = default;
};


/**
*   @class LX_BlendedTextTexture final
*   @brief The blended text texture
*
*   This class describes a blended text texture.
*   A blended text texture is a text that is "very" slowly
*   but very nicely drawn on the screen.
*
*   Using this class for drawing text should be very slow, in particular if
*   you call LX_BlendedImage::setText() and LX_BlendedImage::setTextSize() frequently.
*/
class LX_BlendedTextTexture final : public LX_TextTexture
{
protected:

    virtual void updateTexture_() noexcept;

public:
    /**
    *   @exception LX_ImageException On failure
    */
    LX_BlendedTextTexture(LX_TrueTypeFont::LX_Font& font,LX_Win::LX_Window& w,
                          LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_BlendedTextTexture(const std::string& text, LX_TrueTypeFont::LX_Font& font,
                          LX_Win::LX_Window& w,
                          LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_BlendedTextTexture(const UTF8string& text, LX_TrueTypeFont::LX_Font& font,
                          LX_Win::LX_Window& w,
                          LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_BlendedTextTexture(const std::string& text, unsigned int sz,
                          LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                          LX_PixelFormat format = LX_PixelFormat::RGBA8888);
    /**
    *   @exception LX_ImageException On failure
    */
    LX_BlendedTextTexture(const UTF8string& text, unsigned int sz,
                          LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                          LX_PixelFormat format = LX_PixelFormat::RGBA8888);

    ~LX_BlendedTextTexture() = default;
};

}

#endif  // LX_IMAGE_H_INCLUDED
