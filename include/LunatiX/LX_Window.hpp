
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

#ifndef LX_WINDOW_H_INCLUDED
#define LX_WINDOW_H_INCLUDED

/**
*   @file LX_Window.hpp
*   @brief The window library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <LunatiX/LX_Colour.hpp>

#include <memory>
#include <vector>

struct SDL_Window;
struct SDL_Renderer;

namespace LX_Graphics
{
class LX_Texture;
class LX_Sprite;
class LX_StreamingTexture;
class LX_AnimatedSprite;
class LX_TextTexture;
class LX_BufferedImage;
class LX_ImgCoord;
class LX_ImgRect;
}

namespace LX_TrueTypeFont
{
class LX_Font;
}

namespace LX_Physics
{
struct LX_Circle;
/// @todo version 0.14.0 remove it
struct LX_Vector2D;
/// end
}


/**
*   @ingroup Graphics
*   @namespace LX_Win
*   @brief The window namespace
*
*   @warning In order to use this namespace, the *video* flag
*   in the configuration file must be set to 1, otherwise the behaviour of
*   the library is undefined.
*/
namespace LX_Win
{

// Fullscreen modes
const uint32_t LX_WINDOW_FULLSCREEN = 0x00000001;           /**< Fullscreen mode with original resolution   */
const uint32_t LX_WINDOW_FULLSCREEN_DESKTOP = 0x00001001;   /**< Fullscreen with the current desktop size   */
const uint32_t LX_WINDOW_NO_FULLSCREEN = 0x00000000;        /**< Original resolution in window              */
const uint32_t LX_WINDOW_OPENGL = 0x00000002;               /**< Window usable with OpenGL context          */
const uint32_t LX_WINDOW_SHOWN = 0x00000004;                /**< Window is visible                          */
const uint32_t LX_WINDOW_HIDDEN = 0x00000008;               /**< Window is not visible                      */
const uint32_t LX_WINDOW_BORDERLESS = 0x00000010;           /**< No window decoration                       */
const uint32_t LX_WINDOW_RESIZABLE = 0x00000020;            /**< Window can be resized                      */
const uint32_t LX_WINDOW_MINIMIZED = 0x00000040;            /**< Window is minimized                        */
const uint32_t LX_WINDOW_MAXIMIZED = 0x00000080;            /**< Window is maximized                        */

/**
*   @enum LX_BlendMode
*   @brief Define the blend mode for drawing operations
*
*/
enum class LX_BlendMode
{
    LX_BLENDMODE_NONE,     /**< no blending dstRGBA = srcRGBA */

    LX_BLENDMODE_BLEND,    /**< alpha blending
                                dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
                                dstA = srcA + (dstA * (1-srcA)) */
    LX_BLENDMODE_ADD,      /**< additive blending
                                dstRGB = (srcRGB * srcA) + dstRGB
                                dstA = dstA */
    LX_BLENDMODE_MOD       /**< colour modulate
                                dstRGB = srcRGB * dstRGB
                                dstA = dstA */
};

/**
*   @struct LX_WindowInfo
*   @brief Information about the window
*/
struct LX_WindowInfo
{
    uint32_t id;        /**< Identifier of the window (read-only)   */
    std::string title;  /**< Title                      */
    int x;              /**< X position                 */
    int y;              /**< Y position                 */
    int w;              /**< Window Width               */
    int h;              /**< Window Height              */
    int lw;             /**< Independant device width   */
    int lh;             /**< Independant device height  */
    uint32_t flag;      /**< Flags                      */
    bool accel;         /**< Hardware acceleration      */

};


/**
*   @fn void LX_initWindowInfo(LX_WindowInfo &info) noexcept
*   Get the default configuration of window that will be created
*   @param [out] info The structure to fill information in
*/
void LX_initWindowInfo(LX_WindowInfo &info) noexcept;
/**
*   @fn void LX_loadWindowConfig(LX_WindowInfo &info) noexcept
*   Get the configuration of window from the configuration file
*   @param [out] info The structure to fill information in
*/
void LX_loadWindowConfig(LX_WindowInfo &info) noexcept;


/**
*   @class LX_WindowException
*   @brief The exception class of LX_Window
*
*   This class describes the exception occured when
*   the SDL_Window instance cannot be loaded.
*
*/
class LX_WindowException : public std::exception
{
    std::string _string_error;

    LX_WindowException& operator =(const LX_WindowException& w);

public:

    explicit LX_WindowException(std::string err);
    LX_WindowException(const LX_WindowException& w);
    const char * what() const noexcept;

    ~LX_WindowException() noexcept;
};


struct LX_Window_;

/**
*   @class LX_Window
*   @brief The window
*
*   @warning The LX_Window class must be defined only after
*           the initialization of the library (calling LX_Init())
*   @warning A LX_WindowException may be occured if the window creation fails
*
*/
class LX_Window
{
    friend class LX_Graphics::LX_Texture;
    friend class LX_Graphics::LX_Sprite;
    friend class LX_Graphics::LX_BufferedImage;
    friend class LX_Graphics::LX_StreamingTexture;
    friend class LX_Graphics::LX_AnimatedSprite;
    friend class LX_Graphics::LX_TextTexture;
    friend class LX_TrueTypeFont::LX_Font;

    std::unique_ptr<LX_Window_> _wimpl;

    LX_Window(LX_Window& w) = delete;
    LX_Window& operator =(LX_Window& w) = delete;

    void * getRenderingSys() const noexcept;

public:

    /**
    *   @fn LX_Window(LX_WindowInfo &info)
    *   @param [in, out] info The structure that contains information about the window
    *   @note The structure is updated when the window is created
    *   @exception LX_WindowException if the window cannot be created
    */
    explicit LX_Window(LX_WindowInfo &info);

    /**
    *   @fn void setIcon(const std::string& ficon) noexcept
    *   Set a icon to the current window
    *   @param [in] ficon Name of the file to load as an icon
    */
    void setIcon(const std::string& ficon) noexcept;

    /**
    *   @fn void drawLine(const LX_Graphics::LX_ImgCoord& p, const LX_Graphics::LX_ImgCoord& q) noexcept
    *   @param [in] p The first point
    *   @param [in] q The second point
    */
    void drawLine(const LX_Graphics::LX_ImgCoord& p, const LX_Graphics::LX_ImgCoord& q) noexcept;
    /**
    *   @deprecated will be removed in v0.14.0
    *   @fn void drawLines(const LX_Graphics::LX_ImgCoord * p, const int count) noexcept
    *
    *   Draw several connected segments on the window
    *
    *   @param [in] p An array of points
    *   @param [in] count The number of points, drawing count-1 segments
    */
    void drawLines(const LX_Graphics::LX_ImgCoord * p, const int count) noexcept;
    /**
    *   @fn void drawLines(const std::vector<LX_Graphics::LX_ImgCoord>& vpoints) noexcept;
    *
    *   Draw several connected segments on the window
    *
    *   @param [in] vpoints An array of points
    *   @note pre-condition: *vpoints.size()* > 0
    */
    void drawLines(const std::vector<LX_Graphics::LX_ImgCoord>& vpoints) noexcept;
    /**
    *   @deprecated will be removed in v0.14.0
    *   @fn void drawLine(const LX_Graphics::LX_ImgCoord& p, const LX_Physics::LX_Vector2D& v) noexcept
    *
    *   @param [in] p The point
    *   @param [in] v The direction vector
    *
    *   @note The length of a line depends on the norm of the direction vector
    *        The length is calculating according to this formula: ||v||*2
    */
    void drawLine(const LX_Graphics::LX_ImgCoord& p, const LX_Physics::LX_Vector2D& v) noexcept;
    /**
    *   @fn void drawRect(const LX_Graphics::LX_ImgRect& box) noexcept
    *   @param [in] box The rectangle
    */
    void drawRect(const LX_Graphics::LX_ImgRect& box) noexcept;
    /**
    *   @deprecated will be removed in v0.14.0
    *   @fn void drawRect(const LX_Graphics::LX_ImgCoord& p, const LX_Physics::LX_Vector2D& v) noexcept
    *   @param [in] p The point
    *   @param [in] v The vector that defines how to draw the rectangle (width height)
    *
    */
    void drawRect(const LX_Graphics::LX_ImgCoord& p, const LX_Physics::LX_Vector2D& v) noexcept;
    /**
    *   @fn void drawCircle(const LX_Physics::LX_Circle& c) noexcept
    *   Draw a circle on a window
    *   @param [in] c The circle to draw
    */
    void drawCircle(const LX_Physics::LX_Circle& c) noexcept;

    /**
    *   @fn void fillRect(const LX_Graphics::LX_ImgRect& box) noexcept
    *   Fill a rectangle on a window
    *   @param [in] box The rectangle to fill
    */
    void fillRect(const LX_Graphics::LX_ImgRect& box) noexcept;
    /**
    *   @deprecated will be removed in v0.14.0
    *   @fn void fillRect(const LX_Graphics::LX_ImgCoord& p, const LX_Physics::LX_Vector2D& v) noexcept
    *
    *   Fill a rectangle using a point and a 2D vector
    *
    *   @param [in] p The point
    *   @param [in] v The vector
    */
    void fillRect(const LX_Graphics::LX_ImgCoord& p, const LX_Physics::LX_Vector2D& v) noexcept;
    /**
    *   @fn void fillCircle(const LX_Physics::LX_Circle& c) noexcept
    *   Fill a circle on a window
    *   @param [in] c The circle to draw
    */
    void fillCircle(const LX_Physics::LX_Circle& c) noexcept;

    /**
    *   @fn void setDrawColour(const LX_Colour& colour) noexcept
    *   Set the colour used for drawing operations (Lines, Rectangles, Circles)
    *   @param [in] colour The colour (RGBA)
    */
    void setDrawColour(const LX_Colour& colour) noexcept;
    /**
    *   @fn void setDrawBlendMode(const LX_BlendMode mode) noexcept
    *
    *   Set the blend mode for drawing operations (Fill, Line)
    *
    *   @param [in] mode The blend mode to use for blending:
    *   |        Value        |                      Meaning                     |
    *   |         ---         |                        ---                       |
    *   |  LX_BLENDMODE_NONE  | no blending                                      |
    *   |                     | destRGBA = srcRGBA                               |
    *   |  LX_BLENDMODE_BLEND | alpha blending                                   |
    *   |                     | destRGB = (srcRGB * srcA) + (destRGB * (1-srcA)) |
    *   |                     | destA = srcA + (destA * (1-srcA))                |
    *   |  LX_BLENDMODE_ADD   | additive blending                                |
    *   |                     | destRGB = (srcRGB * srcA) + destRGB              |
    *   |                     | destA = destA                                    |
    *   |  LX_BLENDMODE_MOD   | colour modulate                                  |
    *   |                     | destRGB = srcRGB * destRGB                       |
    *   |                     | destA = destA                                    |
    */
    void setDrawBlendMode(const LX_BlendMode mode) noexcept;
    /**
    *   @fn void getDrawColour(const LX_Colour& colour) const noexcept
    *   Get the colour used for drawing operations (Lines, Rectangles, Circles)
    *   @param [out] colour The colour (RGBA) to get
    */
    void getDrawColour(LX_Colour& colour) const noexcept;
    /**
    *   @fn void getDrawBlendMode(LX_BlendMode& mode) const noexcept
    *
    *   Get the blend mode for drawing operations (Fill, Line)
    *
    *   @param mode Structure to fill in
    *
    *   @return The blend mode used for blending:
    *   |        Value        |                      Meaning                     |
    *   |         ---         |                        ---                       |
    *   |  LX_BLENDMODE_NONE  | no blending                                      |
    *   |                     | destRGBA = srcRGBA                               |
    *   |  LX_BLENDMODE_BLEND | alpha blending                                   |
    *   |                     | destRGB = (srcRGB * srcA) + (destRGB * (1-srcA)) |
    *   |                     | destA = srcA + (destA * (1-srcA))                |
    *   |  LX_BLENDMODE_ADD   | additive blending                                |
    *   |                     | destRGB = (srcRGB * srcA) + destRGB              |
    *   |                     | destA = destA                                    |
    *   |  LX_BLENDMODE_MOD   | colour modulate                                  |
    *   |                     | destRGB = srcRGB * destRGB                       |
    *   |                     | destA = destA                                    |
    */
    void getDrawBlendMode(LX_BlendMode& mode) const noexcept;

    /**
    *   @fn void setTitle(const std::string& title) noexcept
    *
    *   Set the title of the window
    *
    *   @param [in] title The title
    *   @sa setWindowSize
    */
    void setTitle(const std::string& title) noexcept;
    /**
    *   @fn void setWindowSize(int w, int h) noexcept
    *
    *   Set the size of the window
    *
    *   @param [in] w The width of the window
    *   @param [in] h The height of the window
    *   @sa setTitle
    */
    void setWindowSize(int w, int h) noexcept;
    /**
    *   @fn bool setViewPort(const LX_Graphics::LX_ImgRect& viewport) noexcept
    *
    *   Set a specific drawing area (viewport) for rendering
    *
    *   @param [in] viewport The drawing area to set.
    *   @return TRUE on success, FALSE otherwise
    */
    bool setViewPort(const LX_Graphics::LX_ImgRect& viewport) noexcept;
    /**
    *   @fn void resetViewPort() noexcept
    */
    void resetViewPort() noexcept;
    /**
    *   @fn void getViewPort(LX_Graphics::LX_ImgRect& viewport) const noexcept
    *
    *   Get the drawing area (viewport) for rendering
    *
    *   @param [out] viewport The drawing area to fill
    *
    */
    void getViewPort(LX_Graphics::LX_ImgRect& viewport) const noexcept;

    /**
    *   @fn void toggleFullscreen(uint32_t flag) noexcept
    *
    *   Set the window's fullscreen state
    *
    *   @param [in] flag The flag to use in this function:
    *          - ::LX_WINDOW_FULLSCREEN_DESKTOP
    *          - ::LX_WINDOW_FULLSCREEN
    *          - ::LX_WINDOW_NO_FULLSCREEN
    */
    void toggleFullscreen(uint32_t flag) noexcept;

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
    bool screenshot(const std::string& filename) noexcept;

    /**
    *   @fn uint32_t getID() const noexcept
    *   Get the unique identifier of the window
    *   @return The identifier of the window
    */
    uint32_t getID() const noexcept;
    /**
    *   @fn void getInfo(LX_WindowInfo &info) const
    *   Get information of the current window
    *   @param [out] info The information structure to fill in
    */
    void getInfo(LX_WindowInfo &info) const noexcept;
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
    void glGetDrawableSize(int& w, int& h) const noexcept;
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

    ~LX_Window();
};

}

#endif // LX_WINDOW_H_INCLUDED
