
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

#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

/**
*   @file Window.hpp
*   @brief The window library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/utils/utf8_string.hpp>
#include <Lunatix/Colour.hpp>

#include <memory>
#include <vector>


struct SDL_Window;
struct SDL_Renderer;


namespace lx
{

namespace Graphics
{
class Texture;
class Sprite;
class StreamingTexture;
class AnimatedSprite;
class TextTexture;
class BufferedImage;
class ImgCoord;
class ImgRect;
}

namespace TrueTypeFont
{
class Font;
}

namespace Physics
{
struct Circle;
/// todo version 0.14.0 remove it
struct Vector2D;
/// end
}


/**
*   @ingroup Graphics
*   @namespace lx::Win
*   @brief The window namespace
*
*   @warning In order to use this namespace, the *video* flag
*   in the configuration file must be set to 1, otherwise the behaviour of
*   the library is undefined.
*/
namespace Win
{

enum class WinMode
{
    FULLSCREEN = 0x00000001,                        /**< Fullscreen mode with original resolution   */
    FULLSCREEN_DESKTOP = ( FULLSCREEN | 0x00001000 ), /**< Fullscreen with the current desktop size   */
    NO_FULLSCREEN = 0x00000000,                     /**< Original resolution in window              */
    OPENGL = 0x00000002,                            /**< Window usable with OpenGL context          */
    SHOWN  = 0x00000004,                            /**< Window is visible                          */
    HIDDEN = 0x00000008,                            /**< Window is not visible                      */
    BORDERLESS = 0x00000010,                        /**< No window decoration                       */
    RESIZABLE  = 0x00000020,                        /**< Window can be resized                      */
    MINIMIZED  = 0x00000040,                        /**< Window is minimized                        */
    MAXIMIZED  = 0x00000080                         /**< Window is maximized                        */
};


/**
*   @enum BlendMode
*   @brief Define the blend mode for drawing operations
*
*/
enum class BlendMode
{
    BLENDMODE_NONE,     /**< no blending dstRGBA = srcRGBA */

    BLENDMODE_BLEND,    /**< alpha blending
                                dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
                                dstA = srcA + (dstA * (1-srcA)) */
    BLENDMODE_ADD,      /**< additive blending
                                dstRGB = (srcRGB * srcA) + dstRGB
                                dstA = dstA */
    BLENDMODE_MOD       /**< colour modulate
                                dstRGB = srcRGB * dstRGB
                                dstA = dstA */
};

/**
*   @struct WindowInfo
*   @brief Information about the window
*/
struct WindowInfo final
{
    uint32_t id = 0;            /**< Id of the window (read-only)   */
    std::string title = {""};   /**< Title                          */
    int x  = 0;                 /**< X position                     */
    int y  = 0;                 /**< Y position                     */
    int w  = 0;                 /**< Window Width                   */
    int h  = 0;                 /**< Window Height                  */
    int lw = 0;                 /**< Independant device width       */
    int lh = 0;                 /**< Independant device height      */
    uint32_t flag = 0;          /**< Flags                          */
    bool accel = false;         /**< Hardware acceleration          */

};


/**
*   @fn void initWindowInfo(WindowInfo &info) noexcept
*   Get the default configuration of window that will be created
*   @param [out] info The structure to fill information in
*/
void initWindowInfo( WindowInfo& info ) noexcept;
/**
*   @fn void loadWindowConfig(WindowInfo &info) noexcept
*   Get the configuration of window from the configuration file
*   @param [out] info The structure to fill information in
*/
void loadWindowConfig( WindowInfo& info ) noexcept;


/**
*   @class WindowException
*   @brief The exception class of Window
*
*   This class describes the exception occured when
*   the SDL_Window instance cannot be loaded.
*
*/
class WindowException final : public std::exception
{
    std::string _string_error;

    WindowException& operator =( const WindowException& w );

public:

    explicit WindowException( std::string err );
    WindowException( const WindowException& w );
    const char * what() const noexcept;

    ~WindowException() noexcept = default;
};


struct Window_;

/**
*   @class Window
*   @brief The window
*
*   @warning The Window class must be defined only after
*           the initialization of the library (calling lx::init())
*   @warning A WindowException may be occured if the window creation fails
*
*/
class Window final
{
    friend class lx::Graphics::Texture;
    friend class lx::Graphics::Sprite;
    friend class lx::Graphics::BufferedImage;
    friend class lx::Graphics::StreamingTexture;
    friend class lx::Graphics::AnimatedSprite;
    friend class lx::Graphics::TextTexture;
    friend class lx::TrueTypeFont::Font;

    std::unique_ptr<Window_> _wimpl;

    Window( Window& w ) = delete;
    Window& operator =( Window& w ) = delete;

    void * getRenderingSys() const noexcept;

public:

    /**
    *   @fn Window(WindowInfo &info)
    *   @param [in, out] info The structure that contains information about the window
    *   @note The structure is updated when the window is created
    *   @exception WindowException if the window cannot be created
    */
    explicit Window( WindowInfo& info );

    /**
    *   @fn void setIcon(const std::string& ficon) noexcept
    *   Set a icon to the current window
    *   @param [in] ficon Name of the file to load as an icon
    */
    void setIcon( const std::string& ficon ) noexcept;

    /**
    *   @fn void drawLine(const lx::Graphics::ImgCoord& p, const lx::Graphics::ImgCoord& q) noexcept
    *
    *   @param [in] p The first point
    *   @param [in] q The second point
    */
    void drawLine( const lx::Graphics::ImgCoord& p, const lx::Graphics::ImgCoord& q ) noexcept;
    /**
    *   @deprecated This signature will be removed in v0.14.0
    *   Please use the alternative version that takes an std::vector
    *
    *   @fn void drawLines(const lx::Graphics::ImgCoord * p, const int count) noexcept
    *
    *   Draw several connected segments on the window
    *
    *   @param [in] p An array of points
    *   @param [in] count The number of points, drawing count-1 segments
    */
    void drawLines( const lx::Graphics::ImgCoord * p, const int count ) noexcept;
    /**
    *   @fn void drawLines(const std::vector<lx::Graphics::ImgCoord>& vpoints) noexcept;
    *
    *   Draw several connected segments on the window
    *
    *   @param [in] vpoints An array of points
    *   @note pre-condition: *vpoints.size()* > 0
    */
    void drawLines( const std::vector<lx::Graphics::ImgCoord>& vpoints ) noexcept;
    /**
    *   @deprecated This signature of DrawLine is deprecated and will be removed in v0.14.0
    *   Please use the version that takes two coordinates instead.
    *
    *   @fn void drawLine(const lx::Graphics::ImgCoord& p, const lx::Physics::Vector2D& v) noexcept
    *
    *   @param [in] p The point
    *   @param [in] v The direction vector
    *
    *   @note The length of a line depends on the norm of the direction vector
    *        The length is calculating according to this formula: ||v||*2
    */
    void drawLine( const lx::Graphics::ImgCoord& p, const lx::Physics::Vector2D& v ) noexcept;
    /**
    *   @fn void drawRect(const lx::Graphics::ImgRect& box) noexcept
    *   @param [in] box The rectangle
    */
    void drawRect( const lx::Graphics::ImgRect& box ) noexcept;
    /**
    *   @deprecated This signature of DrawRect is deprecated and will be removed in v0.14.0
    *   Please use the version that takes a box (ImgRect).
    *
    *   @fn void drawRect(const lx::Graphics::ImgCoord& p, const lx::Physics::Vector2D& v) noexcept
    *   @param [in] p The point
    *   @param [in] v The vector that defines how to draw the rectangle (width height)
    *
    */
    void drawRect( const lx::Graphics::ImgCoord& p, const lx::Physics::Vector2D& v ) noexcept;
    /**
    *   @fn void drawCircle(const lx::Physics::Circle& c) noexcept
    *   Draw a circle on a window
    *   @param [in] c The circle to draw
    */
    void drawCircle( const lx::Physics::Circle& c ) noexcept;

    /**
    *   @fn void fillRect(const lx::Graphics::ImgRect& box) noexcept
    *   Fill a rectangle on a window
    *   @param [in] box The rectangle to fill
    */
    void fillRect( const lx::Graphics::ImgRect& box ) noexcept;
    /**
    *   @deprecated This signature will be removed in v0.14.0
    *   Please use the version that takes the rect instead..
    *
    *   @fn void fillRect(const lx::Graphics::ImgCoord& p, const lx::Physics::Vector2D& v) noexcept
    *
    *   Fill a rectangle using a point and a 2D vector
    *
    *   @param [in] p The point
    *   @param [in] v The vector
    */
    void fillRect( const lx::Graphics::ImgCoord& p, const lx::Physics::Vector2D& v ) noexcept;
    /**
    *   @fn void fillCircle(const lx::Physics::Circle& c) noexcept
    *   Fill a circle on a window
    *   @param [in] c The circle to draw
    */
    void fillCircle( const lx::Physics::Circle& c ) noexcept;

    /**
    *   @fn void setDrawColour(const Graphics::Colour& colour) noexcept
    *   Set the colour used for drawing operations (Lines, Rectangles, Circles)
    *   @param [in] colour The colour (RGBA)
    */
    void setDrawColour( const Graphics::Colour& colour ) noexcept;
    /**
    *   @fn void setDrawBlendMode(const BlendMode mode) noexcept
    *
    *   Set the blend mode for drawing operations (Fill, Line)
    *
    *   @param [in] mode The blend mode to use for blending:
    *   |        Value        |                      Meaning                     |
    *   |         ---         |                        ---                       |
    *   |  BLENDMODE_NONE  | no blending                                      |
    *   |                     | destRGBA = srcRGBA                               |
    *   |  BLENDMODE_BLEND | alpha blending                                   |
    *   |                     | destRGB = (srcRGB * srcA) + (destRGB * (1-srcA)) |
    *   |                     | destA = srcA + (destA * (1-srcA))                |
    *   |  BLENDMODE_ADD   | additive blending                                |
    *   |                     | destRGB = (srcRGB * srcA) + destRGB              |
    *   |                     | destA = destA                                    |
    *   |  BLENDMODE_MOD   | colour modulate                                  |
    *   |                     | destRGB = srcRGB * destRGB                       |
    *   |                     | destA = destA                                    |
    */
    void setDrawBlendMode( const BlendMode mode ) noexcept;
    /**
    *   @fn void getDrawColour(const Graphics::Colour& colour) const noexcept
    *   Get the colour used for drawing operations (Lines, Rectangles, Circles)
    *   @param [out] colour The colour (RGBA) to get
    */
    void getDrawColour( Graphics::Colour& colour ) const noexcept;
    /**
    *   @fn void getDrawBlendMode(BlendMode& mode) const noexcept
    *
    *   Get the blend mode for drawing operations (Fill, Line)
    *
    *   @param mode Structure to fill in
    *
    *   @return The blend mode used for blending:
    *   |        Value        |                      Meaning                     |
    *   |         ---         |                        ---                       |
    *   |  BLENDMODE_NONE  | no blending                                      |
    *   |                     | destRGBA = srcRGBA                               |
    *   |  BLENDMODE_BLEND | alpha blending                                   |
    *   |                     | destRGB = (srcRGB * srcA) + (destRGB * (1-srcA)) |
    *   |                     | destA = srcA + (destA * (1-srcA))                |
    *   |  BLENDMODE_ADD   | additive blending                                |
    *   |                     | destRGB = (srcRGB * srcA) + destRGB              |
    *   |                     | destA = destA                                    |
    *   |  BLENDMODE_MOD   | colour modulate                                  |
    *   |                     | destRGB = srcRGB * destRGB                       |
    *   |                     | destA = destA                                    |
    */
    void getDrawBlendMode( BlendMode& mode ) const noexcept;

    /**
    *   @fn void setTitle(const std::string& title) noexcept
    *
    *   Set the title of the window
    *
    *   @param [in] title The title
    *   @sa setWindowSize
    */
    void setTitle( const std::string& title ) noexcept;
    /**
    *   @fn void setWindowSize(int w, int h) noexcept
    *
    *   Set the size of the window
    *
    *   @param [in] w The width of the window
    *   @param [in] h The height of the window
    *   @sa setTitle
    */
    void setWindowSize( int w, int h ) noexcept;
    /**
    *   @fn bool setViewPort(const lx::Graphics::ImgRect& viewport) noexcept
    *
    *   Set a specific drawing area (viewport) for rendering
    *
    *   @param [in] viewport The drawing area to set.
    */
    void setViewPort( const lx::Graphics::ImgRect& viewport ) noexcept;
    /**
    *   @fn void resetViewPort() noexcept
    */
    void resetViewPort() noexcept;
    /**
    *   @fn void getViewPort(lx::Graphics::ImgRect& viewport) const noexcept
    *
    *   Get the drawing area (viewport) for rendering
    *
    *   @param [out] viewport The drawing area to fill
    *
    */
    void getViewPort( lx::Graphics::ImgRect& viewport ) const noexcept;

    /**
    *   @fn void toggleFullscreen(const WinMode flag) noexcept
    *
    *   Set the window's fullscreen state
    *
    *   @param [in] flag
    *
    *   @pre The flag to use in this function is on of the following:
    *          - WinMode::FULLSCREEN_DESKTOP
    *          - WinMode::FULLSCREEN
    *          - WinMode::NO_FULLSCREEN
    *
    *   @note Using another flag has no effect
    */
    void toggleFullscreen( const WinMode flag ) noexcept;

    /**
    *   @fn void show() noexcept
    *   Show the window
    */
    void show() noexcept;
    /**
    *   @fn void hide() noexcept
    *   Hide the window
    */
    void hide() noexcept;
    /**
    *   @fn void update() noexcept
    *   Updates the window's display
    *   @note This function can be used with OpenGL
    */
    void update() noexcept;
    /**
    *   @fn void clearWindow() noexcept
    *   Clear the display of the current window
    *   @note This function can be used with OpenGL
    */
    void clearWindow() noexcept;

    /**
    *   @fn bool screenshot(const std::string& filename) noexcept
    *
    *   Take a screenshot and save it in a file
    *
    *   @param [in] filename The name of the file to save the image in
    *   @return True on success, False otherwise
    */
    bool screenshot( const std::string& filename ) noexcept;

    /**
    *   @fn uint32_t getID() const noexcept
    *   Get the unique identifier of the window
    *   @return The identifier of the window
    */
    uint32_t getID() const noexcept;
    /**
    *   @fn void getInfo(WindowInfo &info) const
    *   Get information of the current window
    *   @param [out] info The information structure to fill in
    */
    void getInfo( WindowInfo& info ) const noexcept;
    /**
    *   @fn int getWidth() const noexcept
    *   Get the width of the window
    *   @return The width
    */
    int getWidth() const noexcept;
    /**
    *   @fn int getHeight() const noexcept
    *   Get the height of the window
    *   @return The height
    */
    int getHeight() const noexcept;
    /**
    *   @fn int getLogicalWidth() const noexcept
    *   Get the logical width of the window
    *   @return The logical width
    */
    int getLogicalWidth() const noexcept;
    /**
    *   @fn int getLogicalHeight() const noexcept
    *   Get the logical height of the window
    *   @return The logical height
    */
    int getLogicalHeight() const noexcept;
    /**
    *   @fn void glGetDrawableSize(int& w, int& h) const noexcept
    *
    *   Get the size of a window underlying's drawable (for use with glViewport)
    *
    *   @param [out] w The reference to the variable for storing the width
    *   @param [out] h The reference to the variable for storing the height
    */
    void glGetDrawableSize( int& w, int& h ) const noexcept;
    /**
    *   @fn void glMakeCurrent() noexcept
    *
    *   Set the focus on the current OpenGL window for rendering
    *
    *   @return TRUE on success.
    *          FALSE if the window is not an OpenGL window
    *
    *   @note This function must only be used if the window was
    *        created with the OpenGL flag. Otherwise, it returns FALSE.
    */
    bool glMakeCurrent() noexcept;

    ~Window();
};

}   // Window

}   // lx

#endif // WINDOW_H_INCLUDED
