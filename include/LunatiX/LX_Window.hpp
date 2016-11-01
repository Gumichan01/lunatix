#ifndef LX_WINDOW_H_INCLUDED
#define LX_WINDOW_H_INCLUDED


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
*    @file LX_Window.hpp
*    @brief The window library
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/LX_AABB.hpp>
#include <LunatiX/utils/utf8_string.hpp>
#include <SDL2/SDL_video.h>

struct SDL_Window;
struct SDL_Renderer;

namespace LX_Graphics
{
class LX_Image;
class LX_Sprite;
class LX_StreamingImage;
class LX_AnimatedSprite;
class LX_TextImage;
};

namespace LX_TrueTypeFont
{
class LX_Font;
};

namespace LX_Physics
{
struct LX_Point;
struct LX_Circle;
struct LX_Vector2D;
};


/**
*   @namespace LX_Win
*   @brief The window module
*
*   It provides functions and classes for manipulating windows
*
*   @warning In order to use this module, the *video* flag
*   in the configuration file must be set to 1, otherwise the behaviour of
*   the library is undefined.
*
*/
namespace LX_Win
{

// Fullscreen modes
const uint32_t LX_GRAPHICS_FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP;  /**< Fullscreen with the current desktop size   */
const uint32_t LX_GRAPHICS_FULLSCREEN = SDL_WINDOW_FULLSCREEN;                  /**< Fullscreen mode with original resolution   */
const uint32_t LX_GRAPHICS_NO_FULLSCREEN = 0;                                   /**< Original resolution in window              */

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
*   @fn void LX_initWindowInfo(LX_WindowInfo &info)
*
*   Get the default configuration of window that will be created.
*
*   @param [out] info The structure to fill information in
*/
void LX_initWindowInfo(LX_WindowInfo &info);

/**
*   @fn void LX_loadWindowConfig(LX_WindowInfo &info)
*
*   Get the configuration of window from the configuration file
*
*   @param [out] info The structure to fill information in
*/
void LX_loadWindowConfig(LX_WindowInfo &info);

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

public :

    /// Constructor
    explicit LX_WindowException(std::string err);
    /// Copy constructor
    LX_WindowException(const LX_WindowException& w);

    /// Get the error message
    const char * what() const noexcept;

    /// Destructor
    ~LX_WindowException() noexcept;
};

/// @todo (#4#) LX_Window - private implementation

/**
*   @class LX_Window
*   @brief The window
*
*   @warning The LX_Window class must be defined only after
*            the initialization of the library (calling LX_Init())
*   @warning A LX_WindowException may be occured if the window creation fails
*
*/
class LX_Window
{
    friend class LX_Graphics::LX_Image;
    friend class LX_Graphics::LX_Sprite;
    friend class LX_Graphics::LX_StreamingImage;
    friend class LX_Graphics::LX_AnimatedSprite;
    friend class LX_Graphics::LX_TextImage;
    friend class LX_TrueTypeFont::LX_Font;

    SDL_Window *_window;        /* The internal window structure        */
    SDL_Renderer *_renderer;    /* The main renderer                    */
    SDL_GLContext _glcontext;   /* The context (only used in OpenGL)    */

    int _original_width;        /* The width of the window              */
    int _original_height;       /* The height of the window             */

    LX_Window(LX_Window& w);
    LX_Window& operator =(LX_Window& w);

    void createWindow_(std::string &title, int posX, int posY, int w, int h,
                       uint32_t flag, bool accel = true);

    void createRenderer_(bool accel);
    void updateRenderer_();
    void clearRenderer_();
    bool screenshot_(const std::string& filename);


public :

    /**
    *   @fn LX_Window(LX_WindowInfo &info)
    *   @brief Constructor
    *
    *   Create a window using information from the struture given in argument
    *
    *   @param [in,out] info The structure that contains information about the window
    *   @note The structure is updated when the window is created
    */
    explicit LX_Window(LX_WindowInfo &info);

    /**
    *   @fn void drawSegment(const LX_Physics::LX_Point& p, const LX_Physics::LX_Point& q)
    *
    *   Draw a segment on the window
    *
    *   @param [in] p The first point
    *   @param [in] q The second point
    *
    */
    void drawSegment(const LX_Physics::LX_Point& p, const LX_Physics::LX_Point& q);
    /**
    *   @fn void drawSegments(const LX_Physics::LX_Point * p, const int count)
    *
    *   Draw several connected segments on the window
    *
    *   @param [in] p A array of points
    *   @param [in] count The number of points, drawing count-1 segments
    *
    */
    void drawSegments(const LX_Physics::LX_Point * p, const int count);
    /**
    *   @fn void drawLine(const LX_Physics::LX_Point& p, const LX_Physics::LX_Vector2D& v)
    *
    *   Draw a line on the window
    *
    *   @param [in] p The point
    *   @param [in] v The direction vector
    *
    *   @note The length of a line depends on the norm of the direction vector
    *         The length is calculating according to this formula: ||v||*2
    *
    */
    void drawLine(const LX_Physics::LX_Point& p, const LX_Physics::LX_Vector2D& v);
    /**
    *   @fn void drawRect(const LX_AABB& box)
    *   Draw a rectangle on a window
    *   @param [in] box The rectangle
    */
    void drawRect(const LX_AABB& box);
    /**
    *   @fn void drawRect(const LX_Physics::LX_Point& p, const LX_Physics::LX_Vector2D& v)
    *
    *   Draw a rectangle using a point and a vector
    *
    *   @param [in] p The point
    *   @param [in] v The vector that defines how to draw the rectangle (width height)
    *
    */
    void drawRect(const LX_Physics::LX_Point& p, const LX_Physics::LX_Vector2D& v);
    /**
    *   @fn void drawCircle(const LX_Physics::LX_Circle& c)
    *   Draw a circle on a window
    *   @param [in] c The circle to draw
    */
    void drawCircle(const LX_Physics::LX_Circle& c);

    /**
    *   @fn void fillRect(const LX_AABB& box)
    *   Fill a rectangle on a window
    *   @param [in] box The rectangle to fill
    */
    void fillRect(const LX_AABB& box);
    /**
    *   @fn void fillRect(const LX_Physics::LX_Point& p, const LX_Physics::LX_Vector2D& v)
    *
    *   Fill a rectangle using a point and a 2D vector
    *
    *   @param [in] p The point
    *   @param [in] v The vector
    */
    void fillRect(const LX_Physics::LX_Point& p, const LX_Physics::LX_Vector2D& v);
    /**
    *   @fn void fillCircle(const LX_Physics::LX_Circle& c)
    *   Fill a circle on a window
    *   @param [in] c The circle to draw
    */
    void fillCircle(const LX_Physics::LX_Circle& c);

    /**
    *   @fn void setDrawColor(const SDL_Color& color)
    *   Set the color used for drawing operations (Lines, Rectangles, Circles)
    *   @param [in] color The color (RGBA)
    */
    void setDrawColor(const SDL_Color& color);
    /**
    *   @fn void setDrawBlendMode(SDL_BlendMode mode)
    *
    *   Set the blend mode for drawing operations (Fill, Line)
    *
    *   @param [in] mode The blend mode to use for blending:
    *    |        Value        |                      Meaning                     |
    *    |         ---         |                        ---                       |
    *    | SDL_BLENDMODE_NONE  | no blending                                      |
    *    |                     | destRGBA = srcRGBA                               |
    *    | SDL_BLENDMODE_BLEND | alpha blending                                   |
    *    |                     | destRGB = (srcRGB * srcA) + (destRGB * (1-srcA)) |
    *    |                     | destA = srcA + (destA * (1-srcA))                |
    *    |  SDL_BLENDMODE_ADD  | additive blending                                |
    *    |                     | destRGB = (srcRGB * srcA) + destRGB              |
    *    |                     | destA = destA                                    |
    *    |  SDL_BLENDMODE_MOD  | color modulate                                   |
    *    |                     | destRGB = srcRGB * destRGB                       |
    *    |                     | destA = destA                                    |
    */
    void setDrawBlendMode(SDL_BlendMode mode);
    /**
    *   @fn void getDrawColor(const SDL_Color& color) const
    *   Get the color used for drawing operations (Lines, Rectangles, Circles)
    *   @param [out] color The color (RGBA) to get
    */
    void getDrawColor(SDL_Color& color) const;
    /**
    *   @fn void getDrawBlendMode(SDL_BlendMode& mode) const
    *
    *   Get the blend mode for drawing operations (Fill, Line)
    *
    *   @param mode Structure to fill in
    *
    *   @return The blend mode used for blending:
    *    |        Value        |                      Meaning                     |
    *    |         ---         |                        ---                       |
    *    | SDL_BLENDMODE_NONE  | no blending                                      |
    *    |                     | destRGBA = srcRGBA                               |
    *    | SDL_BLENDMODE_BLEND | alpha blending                                   |
    *    |                     | destRGB = (srcRGB * srcA) + (destRGB * (1-srcA)) |
    *    |                     | destA = srcA + (destA * (1-srcA))                |
    *    |  SDL_BLENDMODE_ADD  | additive blending                                |
    *    |                     | destRGB = (srcRGB * srcA) + destRGB              |
    *    |                     | destA = destA                                    |
    *    |  SDL_BLENDMODE_MOD  | color modulate                                   |
    *    |                     | destRGB = srcRGB * destRGB                       |
    *    |                     | destA = destA                                    |
    */
    void getDrawBlendMode(SDL_BlendMode& mode) const;

    /**
    *   @fn void setTitle(std::string title)
    *
    *   Set the title of the window
    *
    *   @param [in] title The title
    *   @sa setWindowSize
    */
    void setTitle(std::string title);

    /**
    *   @fn void setWindowSize(int w, int h)
    *
    *   Set the size of the window
    *
    *   @param [in] w The width of the window
    *   @param [in] h The height of the window
    *   @sa setTitle
    */
    void setWindowSize(int w, int h);

    /**
    *   @fn bool setViewPort(LX_AABB * viewport)
    *
    *   et a specific drawing area (viewport) for rendering
    *
    *   @param [in] viewport The drawing area to set. nullptr defines the entire target
    *   @return TRUE on success, FALSE otherwise
    */
    bool setViewPort(LX_AABB * viewport);

    /**
    *   @fn void getViewPort(LX_AABB& viewport) const
    *
    *   Get the drawing area (viewport) for rendering
    *
    *   @param [out] viewport The drawing area to fill
    *
    */
    void getViewPort(LX_AABB& viewport) const;

    /**
    *   @fn void toggleFullscreen(uint32_t flag)
    *
    *   Set the window's fullscreen state
    *
    *   @param [in] flag The flag to use in this function:
    *           - ::LX_GRAPHICS_FULLSCREEN_DESKTOP
    *           - ::LX_GRAPHICS_FULLSCREEN
    *           - ::LX_GRAPHICS_NO_FULLSCREEN
    *
    */
    void toggleFullscreen(uint32_t flag);

    /**
    *   @fn void update()
    *   Updates the window's display
    *   @note This function can be used with OpenGL
    */
    void update();

    /**
    *   @fn void clearWindow()
    *   Clear the display of the current window
    *   @note This function can be used with OpenGL
    */
    void clearWindow();

    /**
    *   @fn bool screenshot(const std::string& filename)
    *
    *   Take a screenshot and save it in a file
    *
    *   @param [in] filename The name of the file to save the image in
    *   @return True on success, False otherwise
    */
    bool screenshot(const std::string& filename);

    /**
    *   @fn uint32_t getID() const
    *   Get the unique identifier of the window
    *   @return The identifier of the window
    */
    uint32_t getID() const;
    /**
    *   @fn void getInfo(LX_WindowInfo &info)
    *
    *   Get information of the current window
    *
    *   @param [in] info The information structure to fill in
    */
    void getInfo(LX_WindowInfo &info);

    /**
    *   @fn int getWidth() const
    *
    *   Get the width of the window
    *
    *   @return The width
    */
    int getWidth() const;
    /**
    *   @fn int getHeight() const
    *
    *   Get the height of the window
    *
    *   @return The height
    */
    int getHeight() const;

    /**
    *   @fn int getLogicalWidth() const
    *
    *   Get the logical width of the window
    *
    *   @return The logical width
    */
    int getLogicalWidth() const;
    /**
    *   @fn int getLogicalHeight() const
    *
    *   Get the logical height of the window
    *
    *   @return The logical height
    */
    int getLogicalHeight() const;

    /**
    *   @fn void glGetDrawableSize(int& w, int& h) const
    *
    *   Get the size of a window underlying's drawable (for use with glViewport)
    *
    *   @param [out] w The reference to the variable for storing the width
    *   @param [out] h The reference to the variable for storing the height
    *
    *   @note This may differ from getWidth/getHeight if we are rendering
    *         to a high-DPI drawable, i.e. the window was created with
    *         SDL_WINDOW_ALLOW_HIGHDPI on a platform with high-DPI support.
    */
    void glGetDrawableSize(int& w, int& h) const;
    /**
    *   @fn void glMakeCurrent()
    *
    *   Set focus on the current OpenGL window for rendering
    *
    *   @return TRUE on success.
    *           FALSE if the window is not an OpenGL window
    *
    *   @note This function must only be used if the window was
    *         created with the SDL_WINDOW_OPENGL.
    *         Otherwise, it returns FALSE.
    */
    bool glMakeCurrent();

    /// Destructor
    ~LX_Window();
};

};

#endif // LX_WINDOW_H_INCLUDED
