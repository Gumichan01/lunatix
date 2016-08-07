#ifndef LX_WINDOW_H_INCLUDED
#define LX_WINDOW_H_INCLUDED


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
*	@file LX_Window.hpp
*	@brief The window library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <LunatiX/LX_Hitbox.hpp>
#include <LunatiX/LX_Vector2D.hpp>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Rect;

namespace LX_Graphics
{
class LX_Image;
class LX_Sprite;
class LX_Streaming_Image;
class LX_AnimatedSprite;
class LX_TextImage;
};

namespace LX_TrueTypeFont
{
class LX_Font;
};

// Fullscreen modes
#define LX_GRAPHICS_FULLSCREEN_DESKTOP SDL_WINDOW_FULLSCREEN_DESKTOP    /**< Fullscreen with the current desktop size   */
#define LX_GRAPHICS_FULLSCREEN SDL_WINDOW_FULLSCREEN                    /**< Fullscreen mode with original resolution   */
#define LX_GRAPHICS_NO_FULLSCREEN 0                                     /**< Original resolution in window              */

// Display modes
///< @deprecated
#define LX_WINDOW_SURFACE   0                                           /**< The flag to use the surface    */
#define LX_WINDOW_RENDERING 1                                           /**< The flag to use the rendering  */
#define LX_WINDOW_DEFAULT_MODE LX_WINDOW_RENDERING                      /**< Default mode (Rendering)       */

/**
*   @namespace LX_Win
*   @brief The window module
*/
namespace LX_Win
{

/**
*   @struct LX_WindowInfo
*   @brief Information about the window
*/
struct LX_WindowInfo
{
    std::string title;  /**< Title                      */
    int x;              /**< X position                 */
    int y;              /**< Y position                 */
    int w;              /**< Window Width               */
    int h;              /**< Window Height              */
    int lw;             /**< Independant device width   */
    int lh;             /**< Independant device height  */
    Uint32 flag;        /**< Flags                      */
    bool accel;         /**< Hardware acceleration      */

};


/**
*   @fn void LX_initWindowInfo(LX_WindowInfo &info)
*
*   Get the default configuration of window that will be created.
*
*   @param info The structure to fill information in
*/
void LX_initWindowInfo(LX_WindowInfo &info);

/**
*   @fn void LX_loadWindowConfig(LX_WindowInfo &info)
*
*   Get the configuration of window from the configuration file
*
*   @param info The structure to fill information in
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

    /// Construct the exception
    LX_WindowException(std::string err);
    /// Construct the exception by copy
    LX_WindowException(const LX_WindowException& w);

    /// Get the error message
    const char * what() const noexcept;

    /// Destroy the exception
    ~LX_WindowException() noexcept;
};


/**
*   @class LX_Window
*   @brief The window
*
*   @note By default, the constructor retrieves information from the configuration file
*
*   @warning The LX_Window class must be defined only after
*               the initialization of the engine (calling LX_Init())
*   @warning A LX_WindowException may be occured if the window creation fails
*
*/
class LX_Window
{
    friend class LX_Graphics::LX_Image;
    friend class LX_Graphics::LX_Sprite;
    friend class LX_Graphics::LX_Streaming_Image;
    friend class LX_Graphics::LX_AnimatedSprite;
    friend class LX_Graphics::LX_TextImage;
    friend class LX_TrueTypeFont::LX_Font;

    SDL_Window *_window;        /* The internal window structure     */
    SDL_Renderer *_renderer;    /* The main renderer                 */
    SDL_GLContext _glcontext;   /* The context (only used in OpenGL) */

    int _original_width;        /* The width of the window           */
    int _original_height;       /* The height of the window          */
    bool _render_method;        /* Use Surface or Rendering          */

    LX_Window(LX_Window& w);
    LX_Window& operator =(LX_Window& w);

    void createWindow_(std::string &title, int posX, int posY, int w, int h,
                       Uint32 flag, bool accel = true);

    void createRendering_(bool accel);

    void updateWindow_(void);
    void updateRenderer_(void);
    void clearSurface_(void);
    void clearRenderer_(void);

    bool screenshotUsingRenderer_(std::string& filename);
    bool screenshotUsingSurface_(std::string& filename);


public :

    /**
    *   @fn LX_Window(LX_WindowInfo &info)
    *
    *   Create a window using information from the struture given in argument
    *
    *   @param info The structure tha contains information about the window
    *   @note The structure is updated when the window is created
    */
    LX_Window(LX_WindowInfo &info);

    /**
    *   @fn void drawSegment(const LX_Physics::LX_Point p, const LX_Physics::LX_Point q)
    *
    *   Draw a segment on the window
    *
    *   @param p The first point
    *   @param q The second point
    *
    */
    void drawSegment(const LX_Physics::LX_Point p, const LX_Physics::LX_Point q);
    /**
    *   @fn void drawSegments(const LX_Physics::LX_Point * p, const int count)
    *
    *   Draw several connected segments on the window
    *
    *   @param p A array of points
    *   @param count The number of points, drawing count-1 segments
    *
    */
    void drawSegments(const LX_Physics::LX_Point * p, const int count);
    /**
    *   @fn void drawLine(const LX_Physics::LX_Point p, const LX_Physics::LX_Vector2D v)
    *
    *   Draw a line on the window
    *
    *   @param p The point
    *   @param v The direction vector
    *
    *   @note The length of a line depends on the norm of the direction vector
    *         The length is calculating according to this formula: ||v||*2
    *
    */
    void drawLine(const LX_Physics::LX_Point p, const LX_Physics::LX_Vector2D v);
    /**
    *   @fn void drawRect(const LX_AABB& box)
    *   Draw a rectangle on a window
    *   @param box The rectangle
    */
    void drawRect(const LX_AABB& box);
    /**
    *   @fn void drawRect(const LX_Physics::LX_Point p, const LX_Physics::LX_Vector2D v)
    *
    *   Draw a rectangle using a point and a vector
    *
    *   @param p The point
    *   @param v The vector that defines how to draw the rectangle (width height)
    *
    */
    void drawRect(const LX_Physics::LX_Point p, const LX_Physics::LX_Vector2D v);
    /**
    *   @fn void drawCircle(const LX_Physics::LX_Circle& c)
    *   Draw a circle on a window
    *   @param c The circle to draw
    */
    void drawCircle(const LX_Physics::LX_Circle& c);

    /**
    *   @fn void fillRect(const LX_AABB& box)
    *   Fill a rectangle on a window
    *   @param box The rectangle to fill
    */
    void fillRect(const LX_AABB& box);
    /**
    *   @fn void fillRect(const LX_Physics::LX_Point p, const LX_Physics::LX_Vector2D v)
    *
    *   Fill a rectangle using a point and a 2D vector
    *
    *   @param p The point
    *   @param v The vector
    */
    void fillRect(const LX_Physics::LX_Point p, const LX_Physics::LX_Vector2D v);
    /**
    *   @fn void fillCircle(const LX_Physics::LX_Circle& c)
    *   Fill a circle on a window
    *   @param c The circle to draw
    */
    void fillCircle(const LX_Physics::LX_Circle& c);

    /**
    *   @fn void setDrawColor(const SDL_Color& color)
    *   Set the color used for drawing operations (Lines, Rectangles, Circles)
    *   @param color The color (ARGB)
    */
    void setDrawColor(const SDL_Color& color);
    /**
    *   @fn void setDrawBlendMode(SDL_BlendMode mode)
    *
    *   Set the blend mode for drawing operations (Fill, Line)
    *
    *   @param mode The blend mode to use for blending:
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
    *   @fn void setTitle(std::string title)
    *
    *   Set the title of the window
    *
    *   @param title The title
    *
    *   @sa setWindowSize
    */
    void setTitle(std::string title);

    /**
    *   @fn void setWindowSize(int w, int h)
    *
    *   Set the size of the window
    *
    *   @param w The width of the window
    *   @param h The height of the window
    *
    *   @sa setTitle
    */
    void setWindowSize(int w, int h);

    /**
    *   @fn bool setViewPort(LX_AABB * viewport)
    *
    *   et a specific drawing area (viewport) for rendering
    *
    *   @param viewport The drawing area to set. nullptr defines the entire target
    *   @return TRUE on success, FALSE otherwise
    */
    bool setViewPort(LX_AABB * viewport);

    /**
    *   @fn void getViewPort(LX_AABB& viewport)
    *
    *   Get the drawing area (viewport) for rendering
    *
    *   @param viewport The drawing area to fill
    *
    */
    void getViewPort(LX_AABB& viewport);

    /**
    *   @fn void toggleFullscreen(Uint32 flag)
    *
    *   Set the window's fullscreen state
    *
    *   @param flag The flag to use in this function:
    *           - ::LX_GRAPHICS_FULLSCREEN_DESKTOP
    *           - ::LX_GRAPHICS_FULLSCREEN
    *           - ::LX_GRAPHICS_NO_FULLSCREEN
    *
    */
    void toggleFullscreen(Uint32 flag);

    /**
    *   @fn void update(void)
    *   Updates the window's display
    *   @note This function can be used with OpenGL
    */
    void update(void);

    /**
    *   @fn void clearWindow(void)
    *   Clear the display of the current window
    *   @note This function can be used with OpenGL
    */
    void clearWindow(void);

    /**
    *   @fn bool screenshot(std::string filename)
    *
    *   Take a screenshot and save it in a file
    *
    *   @param filename The name of the file to save the image in
    *   @return True on success, False otherwise
    */
    bool screenshot(std::string filename);

    /**
    *   @fn void getInfo(LX_WindowInfo &info)
    *
    *   Get information of the current window
    *
    *   @param info the info the structure to fill in information
    */
    void getInfo(LX_WindowInfo &info);

    /**
    *   @fn int getWidth(void)
    *
    *   Get the width of the window
    *
    *   @return the width
    */
    int getWidth(void);

    /**
    *   @fn int getHeight(void)
    *
    *   Get the height of the window
    *
    *   @return the height
    */
    int getHeight(void);

    /**
    *   @fn void glGetDrawableSize(int& w, int& h)
    *
    *   Get the size of a window underlying's drawable (for use with glViewport)
    *
    *   @param [out] w  The reference to the variable for storing the width
    *   @param [out] h  The reference to the variable for storing the height
    *
    *   @note This may differ from getWidth/getHeight if we are rendering
    *         to a high-DPI drawable, i.e. the window was created with
    *         SDL_WINDOW_ALLOW_HIGHDPI on a platform with high-DPI support.
    */
    void glGetDrawableSize(int& w, int& h);

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

    /**
    *   @fn ~LX_Window()
    *
    *   Destroy the window instance
    */
    ~LX_Window();
};

};

#endif // LX_WINDOW_H_INCLUDED
