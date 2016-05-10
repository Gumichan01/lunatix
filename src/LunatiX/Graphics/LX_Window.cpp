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
*	@file LX_Window.cpp
*	@brief The implementation of the window
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.7
*
*/

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_endian.h>

#include <LunatiX/LX_Config.hpp>
#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_Error.hpp>

#define LX_ARGB_DEPTH 32                            /* Pixel depth in bits */

/*
*   Define the mask for the surface creation
*   when the screenshot will be done
*/

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define LX_PIXEL_FORMAT SDL_PIXELFORMAT_RGBA8888

static const Uint32 rmask = 0xff000000;
static const Uint32 gmask = 0x00ff0000;
static const Uint32 bmask = 0x0000ff00;
static const Uint32 amask = 0x000000ff;

#else
#define LX_PIXEL_FORMAT SDL_PIXELFORMAT_ABGR8888

static const Uint32 rmask = 0x000000ff;
static const Uint32 gmask = 0x0000ff00;
static const Uint32 bmask = 0x00ff0000;
static const Uint32 amask = 0xff000000;

#endif

/// @todo : refactore createWindow() : string -> reference to string
static const char * DEFAULT_TITLE = "LunatiX Engine v0.7";
static const int DEFAULT_WIN_WIDTH = 640;
static const int DEFAULT_WIN_HEIGHT = 480;

namespace LX_Graphics
{

static Uint32 generateFlags(LX_Configuration &config)
{
    Uint32 flag = 0x00000000;

    if(config.getVideoFlag() && config.getFullscreenFlag())
        flag |= LX_GRAPHICS_FULLSCREEN;

    if(config.getVideoFlag() && config.getOpenGLFlag())
        flag |= SDL_WINDOW_OPENGL;

    return flag;
}

void LX_initWindowInfo(LX_WindowInfo &info)
{
    info.title = DEFAULT_TITLE;
    info.x = SDL_WINDOWPOS_CENTERED;
    info.y = SDL_WINDOWPOS_CENTERED;
    info.w = DEFAULT_WIN_WIDTH;
    info.h = DEFAULT_WIN_HEIGHT;
    info.mode = LX_WINDOW_RENDERING;
    info.flag = 0;
    info.accel = true;
}


void LX_loadWindowConfig(LX_WindowInfo &info)
{
    LX_Configuration *config = LX_Configuration::getInstance();

    if(config == nullptr)
        LX_initWindowInfo(info);
    else
    {
        info.title = DEFAULT_TITLE;
        info.x = SDL_WINDOWPOS_CENTERED;
        info.y = SDL_WINDOWPOS_CENTERED;
        info.w = config->getWinWidth();
        info.h = config->getWinHeight();
        info.mode = LX_WINDOW_RENDERING;
        info.flag = generateFlags(*config);
        info.accel = true;
    }
}


/**
*   @fn LX_WindowException::LX_WindowException(std::string err)
*
*   Constructor
*
*   @param err The error string
*
*/
LX_WindowException::LX_WindowException(std::string err)
{
    stringError = err;
}


LX_WindowException::LX_WindowException(const LX_WindowException& w)
{
    stringError = w.stringError;
}


/**
*   @fn const char * LX_WindowException::what() const noexcept
*
*   Get the error string associated with the exception
*
*   @return The error string
*/
const char * LX_WindowException::what() const noexcept
{
    return stringError.c_str();
}

LX_WindowException::~LX_WindowException() noexcept {}


/**
*   @fn LX_Window::LX_Window(const Uint32 mode, bool accel)
*   @deprecated
*
*   Create the window with the default configuration
*
*   @param mode The display mode
*           - ::LX_WINDOW_SURFACE : to use surfaces
*           - ::LX_WINDOW_RENDERING : to use the renderer
*
*   @param accel Tag that selects the rendering mode
*           - True : Use hardware acceleration
*           - False : Use software fallback
*
*   @note The default configuration is used in this constructor
*   @exception LX_WindowException
*
*/
LX_Window::LX_Window(const Uint32 mode, bool accel)
    : LX_Window(DEFAULT_TITLE,mode,accel)
{
    // Empty
}


/**
*   @fn LX_Window::LX_Window(std::string title, const Uint32 mode, bool accel)
*
*   Create the window setting the title and using the configuration file
*
*   @param title The title of the window
*   @param mode The display mode :
*           - ::LX_WINDOW_SURFACE : to use surfaces
*           - ::LX_WINDOW_RENDERING : to use the renderer
*
*   @param accel Tag that selects the rendering mode
*           - True : Use hardware acceleration
*           - False : Use software fallback
*
*   @note The default configuration is used in this constructor
*
*/
LX_Window::LX_Window(std::string title, const Uint32 mode, bool accel)
    : window(nullptr), renderer(nullptr), original_width(0), original_height(0),
    render_method(false)
{
    int xpos,ypos,w,h;
    Uint32 flag = 0x00000000;
    LX_Configuration *config = LX_Configuration::getInstance();

    w = config->getWinWidth();
    h = config->getWinHeight();
    original_width = w;
    original_height = h;

    if(config->getFullscreenFlag())
    {
        flag |= LX_GRAPHICS_FULLSCREEN;
        xpos = SDL_WINDOWPOS_UNDEFINED;
        ypos = SDL_WINDOWPOS_UNDEFINED;
    }
    else
    {
        xpos = SDL_WINDOWPOS_CENTERED;
        ypos = SDL_WINDOWPOS_CENTERED;
    }

    if(config->getOpenGLFlag())
        flag |= SDL_WINDOW_OPENGL;

    createWindow(title.c_str(),xpos,ypos,w,h,mode,flag,accel);
}



LX_Window::LX_Window(LX_WindowInfo &info)
    : window(nullptr), renderer(nullptr),
    original_width(info.w), original_height(info.h), render_method(false)
{
    createWindow(info.title.c_str(),info.x,info.y,info.w,info.h,info.mode,
                 info.flag,info.accel);
}


/**
*   @fn LX_Window::LX_Window(std::string title, int posX, int posY, int w, int h,
*                               const Uint32 mode, Uint32 flag, bool accel)
*
*   Create the window with a custom configuration
*
*   @param title The title of the window
*   @param posX The X position of the window on the desktop
*   @param posY The Y position of the window on the desktop
*   @param w The width of the window
*   @param h The height of the window
*   @param mode The display mode
*           - ::LX_WINDOW_SURFACE : to use surfaces
*           - ::LX_WINDOW_RENDERING : to use the renderer
*
*   @param flag One of these following flags
*           - ::LX_GRAPHICS_FULLSCREEN_DESKTOP
*           - ::LX_GRAPHICS_FULLSCREEN
*           - ::LX_GRAPHICS_NO_FULLSCREEN
*           - And any SDL flags
*
*   @param accel Tag that selects the rendering mode
*           - True : Use hardware acceleration
*           - False : Use software fallback
*
*   @note This constructor does not use the configuration file
*   @exception LX_WindowException
*
*/
LX_Window::LX_Window(std::string title, int posX, int posY, int w, int h,
                     const Uint32 mode, Uint32 flag, bool accel)
    : window(nullptr), renderer(nullptr), original_width(w),
    original_height(h), render_method(false)
{
    createWindow(title.c_str(),posX,posY,w,h,mode,flag,accel);
}


/*
*   Initialize the window according to the configuration
*/
void LX_Window::createWindow(std::string title, int posX, int posY, int w, int h,
                        const Uint32 mode, Uint32 flag, bool accel)
{
    window = SDL_CreateWindow(title.c_str(),posX,posY,w,h,flag);

    if(window == nullptr)
        throw LX_WindowException(LX_GetError());

    if(mode == LX_WINDOW_RENDERING)
        createRendering(accel);
    else
        render_method = false;
}


/*
*   Create a renderer for the window
*/
void LX_Window::createRendering(bool accel)
{
    Uint32 renderFlag = 0x00000000;
    LX_Configuration *config = LX_Configuration::getInstance();

    // Hardware acceleration or software rendering
    if(accel)
        renderFlag = SDL_RENDERER_ACCELERATED;
    else
        renderFlag = SDL_RENDERER_SOFTWARE;

    // Video flag and VSync flag actives -> add the option
    if(config->getVideoFlag() && config->getVSyncFlag())
        renderFlag |= SDL_RENDERER_PRESENTVSYNC;

    renderer = SDL_CreateRenderer(window,-1,renderFlag);

    if(renderer == nullptr)
    {
        std::string err_msg = "Rendering creation: ";
        err_msg = err_msg + LX_GetError();
        throw LX_WindowException(err_msg.c_str());
    }

    render_method = true;     // The render_mode is active
}


/**
*   @fn LX_Window::~LX_Window()
*
*   Destroy the window instance
*
*/
LX_Window::~LX_Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


/**
*   @fn bool LX_Window::putSurface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos)
*
*   This function puts a area of the surface on the window surface at a specified position
*
*   @param image The surface to put
*   @param area The area of the surface to put on the screen
*   @param pos The position of the surface
*
*   @return True If the image was put with success, False otherwise
*
*   @note   If you do not need to determine the area parameter of the surface,
*           put a null pointer
*
*   @note   You can give a LX_AABB object to the function instead of a SDL_Rect object.
*           Actually, LX_AABB is just an alias of SDL_Rect
*
*   @sa putTexture
*/
bool LX_Window::putSurface(SDL_Surface *image, SDL_Rect *area, SDL_Rect *pos)
{
    int err = 0;
    SDL_Rect offset;

    if(image == nullptr)
        return false;

    if(pos == nullptr)
        offset = {0,0,0,0};
    else
        offset = {pos->x,pos->y,pos->w,pos->h};

    err = SDL_BlitSurface(image,area,SDL_GetWindowSurface(window),&offset);

    if(err < 0)
        return false;

    return true;
}


/**
*   @fn bool LX_Window::putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos)
*
*   This function puts an area of the texture on the window
*
*   @param origin The texture to put
*   @param area The area of the surface to put on the renderer
*   @param pos The position of the texture
*
*   @return True If the texture was put with success, False otherwise
*
*   @note   If you do not need to determine the area parameter of the surface,
*           put a null pointer
*
*   @note You can give a LX_AABB object to the function instead of a SDL_Rect object.
*           Actually, LX_AABB is just an alias of SDL_Rect
*
*   @warning The width and the height defined in the SDL_Rect are important, the function uses it
*               to display the texture according to its dimension
*
*   @sa putSurface
*   @sa putTextureAndRotate
*/
bool LX_Window::putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos)
{
    return(SDL_RenderCopy(renderer,origin,area,pos) == 0);
}


/**
*   @fn bool LX_Window::putTextureAndRotate(SDL_Texture *origin, const SDL_Rect *area,
*                                           const SDL_Rect *pos,const double angle)
*
*   This function puts an area of the texture on the window and optionnaly rotate it
*
*   @param origin The texture to put
*   @param area The area of the surface to put on the renderer
*   @param pos The position of the texture
*   @param angle an angle in degrees that indicate the rotation
*
*   @return True If the texture was put with success, False otherwise
*
*   @note   If you do not need to determine the area parameter of the surface,
*           put a null pointer
*   @note   You can give a LX_AABB object to the function instead of a SDL_Rect object.
*           Actually, LX_AABB is just an alias of SDL_Rect
*
*   @warning    The width and the height defined in the SDL_Rect are important,
*               the function uses it to display the texture according
*               to its dimension
*
*   @sa putSurface
*   @sa putTexture
*/
bool LX_Window::putTextureAndRotate(SDL_Texture *origin, const SDL_Rect *area,
                                    const SDL_Rect *pos, const double angle)
{
    return(SDL_RenderCopyEx(renderer,origin,area,pos, (-angle), nullptr,SDL_FLIP_NONE) == 0);
}


/**
*   @fn void LX_Window::setTitle(std::string title)
*
*   Set the title of the window
*
*   @param title The title
*
*   @sa setWindowSize
*/
void LX_Window::setTitle(std::string title)
{
    SDL_SetWindowTitle(window,title.c_str());
}


/**
*   @fn void LX_Window::setWindowSize(int w, int h)
*
*   Set the size of the window
*
*   @param w The width of the window
*   @param h The height of the window
*
*   @sa setTitle
*/
void LX_Window::setWindowSize(int w, int h)
{
    SDL_SetWindowSize(window,w,h);
}


/**
*   @fn void LX_Window::setFullscreen(Uint32 flag)
*
*   Set the window's fullscreen state
*
*   @param flag The flag to use in this function:
*           - ::LX_GRAPHICS_FULLSCREEN_DESKTOP
*           - ::LX_GRAPHICS_FULLSCREEN
*           - ::LX_GRAPHICS_NO_FULLSCREEN
*
*/
void LX_Window::setFullscreen(Uint32 flag)
{
    SDL_SetWindowFullscreen(window,flag);

    if(flag == LX_GRAPHICS_NO_FULLSCREEN)   // set the window at the original size
    {
        setWindowSize(original_width,original_height);
    }
}


/**
*   @fn void LX_Window::update(void)
*
*   Updates the window's display
*
*/
void LX_Window::update(void)
{
    if(render_method)
        updateRenderer();
    else
        updateWindow();
}



/*
*   This function updates the renderer of the window
*
*   This fonction must be only used when textures are manipulated
*   on the current window. So LX_Window::updateWindow() and this function
*   cannot be used together on a same window.
*
*/
void LX_Window::updateRenderer(void)
{
    SDL_RenderPresent(renderer);
}


/*
*   This function updates the surface of the window
*
*   This fonction must be only used whane textures are manipulated
*   on the current window. So LX_Window::updateRenderer() and this function
*   cannot be used together on a same window.
*/
void LX_Window::updateWindow(void)
{
    SDL_UpdateWindowSurface(window);
}


/**
*   @fn void LX_Window::clearWindow(void)
*
*   Clear the display of the current window
*
*/
void LX_Window::clearWindow(void)
{
    if(render_method)
        clearRenderer();
    else
        clearSurface();
}


/*
*   Clear the main window surface
*/
void LX_Window::clearSurface(void)
{
    SDL_Surface *tmp = SDL_GetWindowSurface(window);
    SDL_FillRect(tmp,nullptr, SDL_MapRGB(tmp->format,0,0,0));
}


/*
*   Clear the main window renderer
*/
void LX_Window::clearRenderer(void)
{
    SDL_RenderClear(renderer);
}


/**
    @fn bool LX_Window::screenshot(std::string filename)

    Take a screenshot and save it in a file

    @return True on success, False otherwise

*/
bool LX_Window::screenshot(std::string filename)
{
    if(render_method)
        return screenshotUsingRenderer(filename);

    return screenshotUsingSurface(filename);
}


/*
*   Make a screenshot using the renderer
*/
bool LX_Window::screenshotUsingRenderer(std::string& filename)
{
    int err = 0;
    SDL_Surface *sshot = nullptr;

    sshot = SDL_CreateRGBSurface(0,getWidth(),getHeight(),
                                 LX_ARGB_DEPTH,rmask,gmask,bmask,amask);

    if(sshot == nullptr)
        return false;

    err = SDL_RenderReadPixels(renderer,nullptr,LX_PIXEL_FORMAT,
                               sshot->pixels,sshot->pitch);

    if(err == -1)
    {
        // Cannot read the pixels from the renderer
        SDL_FreeSurface(sshot);
        return false;
    }

    err = IMG_SavePNG(sshot,filename.c_str());
    SDL_FreeSurface(sshot);

    return err == 0;
}


/*
*   Make a screenshot using the renderer
*/
bool LX_Window::screenshotUsingSurface(std::string& filename)
{
    SDL_Surface *sshot = nullptr;
    sshot = getSurface();

    if(sshot == nullptr)
        return false;

    return(IMG_SavePNG(sshot,filename.c_str()) == 0);
}



/**
*   @fn SDL_Renderer * LX_Window::getRenderer(void)
*
*   Get the window renderer
*
*   @return A valid pointer to the renderer if the window internally use it
*
*/
SDL_Renderer * LX_Window::getRenderer(void)
{
    return SDL_GetRenderer(window);
}


/**
*   @fn SDL_Surface * LX_Window::getSurface(void)
*
*   Get the window surface
*
*   @return A valid pointer to the SDL_Surface if the window internally use it
*
*/
SDL_Surface * LX_Window::getSurface(void)
{
    return SDL_GetWindowSurface(window);
}


/**
*
*   @fn SDL_Window * LX_Window::getWindow(void)
*
*   Get the window
*
*   @return A pointer to the SDL_Window instance
*
*   @note Normally, the function never returns an invalid pointer,
*           but it is better to check the pointer value
*
*/
SDL_Window * LX_Window::getWindow(void)
{
    return window;
}


/**
*   @fn int LX_Window::getWidth(void)
*
*   Get the width of the window
*
*   @return the width
*
*/
int LX_Window::getWidth(void)
{
    int w;
    SDL_GetWindowSize(window,&w,nullptr);

    return w;
}


/**
*   @fn int LX_Window::getHeight(void)
*
*   Get the height of the window
*
*   @return the height
*
*/
int LX_Window::getHeight(void)
{
    int h;
    SDL_GetWindowSize(window,nullptr,&h);

    return h;
}


};

