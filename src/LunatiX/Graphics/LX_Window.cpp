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
*	@version 0.8
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


static const char * DEFAULT_TITLE = "LunatiX Engine v0.8";
static const int DEFAULT_WIN_WIDTH = 640;
static const int DEFAULT_WIN_HEIGHT = 480;

namespace LX_Win
{

static Uint32 generateFlags(LX_Configuration &config)
{
    Uint32 flag = 0x00000000;

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
    info.lw = 0;
    info.lh = 0;
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
        info.lw = 0;
        info.lh = 0;
        info.mode = LX_WINDOW_RENDERING;
        info.flag = generateFlags(*config);
        info.accel = true;
    }
}

/* Exception */

LX_WindowException::LX_WindowException(std::string err)
{
    _string_error = err;
}

LX_WindowException::LX_WindowException(const LX_WindowException& w)
{
    _string_error = w._string_error;
}

const char * LX_WindowException::what() const noexcept
{
    return _string_error.c_str();
}

LX_WindowException::~LX_WindowException() noexcept {}


/* LX_Window */

LX_Window::LX_Window(LX_WindowInfo &info)
    : _window(nullptr), _renderer(nullptr),
      _original_width(info.w), _original_height(info.h), _render_method(false)
{
    createWindow_(info.title,info.x,info.y,info.w,info.h,info.mode,
                 info.flag,info.accel);
    getInfo(info);
}


/*
*   Private function that initializes the window according to the configuration
*/
void LX_Window::createWindow_(std::string &title, int posX, int posY, int w, int h,
                             const Uint32 mode, Uint32 flag, bool accel)
{
    _window = SDL_CreateWindow(title.c_str(),posX,posY,w,h,flag);

    if(_window == nullptr)
        throw LX_WindowException(LX_GetError());

    if(mode == LX_WINDOW_RENDERING)
        createRendering_(accel);
    else
        _render_method = false;
}


/*
*   Private function that creates a renderer for the window
*/
void LX_Window::createRendering_(bool accel)
{
    Uint32 render_flag = 0x00000000;
    LX_Configuration *config = LX_Configuration::getInstance();

    // Hardware acceleration or software rendering
    if(accel)
        render_flag = SDL_RENDERER_ACCELERATED;
    else
        render_flag = SDL_RENDERER_SOFTWARE;

    // Video flag and VSync flag actives -> add the option
    if(config->getVideoFlag() && config->getVSyncFlag())
        render_flag |= SDL_RENDERER_PRESENTVSYNC;

    _renderer = SDL_CreateRenderer(_window,-1,render_flag);

    if(_renderer == nullptr)
    {
        std::string err_msg = "Rendering creation: ";
        err_msg = err_msg + LX_GetError();
        throw LX_WindowException(err_msg);
    }

    _render_method = true;     // The render_mode is active
}


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

    err = SDL_BlitSurface(image,area,SDL_GetWindowSurface(_window),&offset);

    if(err < 0)
        return false;

    return true;
}


bool LX_Window::putTexture(SDL_Texture *origin, SDL_Rect *area, SDL_Rect *pos)
{
    return SDL_RenderCopy(_renderer,origin,area,pos) == 0;
}


bool LX_Window::putTextureAndRotate(SDL_Texture *origin, const SDL_Rect *area,
                                    const SDL_Rect *pos, const double angle)
{
    return SDL_RenderCopyEx(_renderer,origin,area,pos,(-angle),
                            nullptr,SDL_FLIP_NONE) == 0;
}


void LX_Window::setTitle(std::string title)
{
    SDL_SetWindowTitle(_window,title.c_str());
}


void LX_Window::setWindowSize(int w, int h)
{
    SDL_SetWindowSize(_window,w,h);
    _original_width = w;
    _original_height = h;
}


void LX_Window::toggleFullscreen(Uint32 flag)
{
    SDL_SetWindowFullscreen(_window,flag);

    if(flag == LX_GRAPHICS_NO_FULLSCREEN)   // set the window at the original size
    {
        setWindowSize(_original_width,_original_height);
    }
    else if(flag == LX_GRAPHICS_FULLSCREEN_DESKTOP)
    {
        if(_render_method)
        {
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear");
            SDL_RenderSetLogicalSize(_renderer,_original_width,_original_height);
        }
    }
}


/*
*   This private function updates the renderer of the window
*
*   This fonction must be only used when textures are manipulated
*   on the current window. So LX_Window::updateWindow() and this function
*   cannot be used together on a same window.
*/
void LX_Window::updateRenderer_(void)
{
    SDL_RenderPresent(_renderer);
}


/*
*   This private function updates the surface of the window
*
*   This fonction must be only used whane textures are manipulated
*   on the current window. So LX_Window::updateRenderer() and this function
*   cannot be used together on a same window.
*/
void LX_Window::updateWindow_(void)
{
    SDL_UpdateWindowSurface(_window);
}


void LX_Window::update(void)
{
    if(_render_method)
        updateRenderer_();
    else
        updateWindow_();
}


/*
*   Private function that clears the main window surface
*/
void LX_Window::clearSurface_(void)
{
    SDL_Surface *tmp = SDL_GetWindowSurface(_window);
    SDL_FillRect(tmp,nullptr, SDL_MapRGB(tmp->format,0,0,0));
}


/*
*   Private function that clears the main window renderer
*/
void LX_Window::clearRenderer_(void)
{
    SDL_RenderClear(_renderer);
}


void LX_Window::clearWindow(void)
{
    if(_render_method)
        clearRenderer_();
    else
        clearSurface_();
}


/*
*   Private function that makes a screenshot using the renderer
*/
bool LX_Window::screenshotUsingRenderer_(std::string& filename)
{
    int err = 0;
    SDL_Surface *sshot = nullptr;

    sshot = SDL_CreateRGBSurface(0,getWidth(),getHeight(),
                                 LX_ARGB_DEPTH,rmask,gmask,bmask,amask);

    if(sshot == nullptr)
        return false;

    err = SDL_RenderReadPixels(_renderer,nullptr,LX_PIXEL_FORMAT,
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
*   Private function that makes a screenshot using the surface
*/
bool LX_Window::screenshotUsingSurface_(std::string& filename)
{
    SDL_Surface *sshot = nullptr;
    sshot = SDL_GetWindowSurface(_window);

    if(sshot == nullptr)
        return false;

    return(IMG_SavePNG(sshot,filename.c_str()) == 0);
}


bool LX_Window::screenshot(std::string filename)
{
    if(_render_method)
        return screenshotUsingRenderer_(filename);

    return screenshotUsingSurface_(filename);
}


void LX_Window::getInfo(LX_WindowInfo &info)
{
    info.title = SDL_GetWindowTitle(_window);
    SDL_GetWindowPosition(_window,&info.x,&info.y);
    SDL_GetWindowSize(_window, &info.w,&info.h);

    if(_render_method)
        SDL_RenderGetLogicalSize(_renderer,&info.lw,&info.lh);
    else
    {
        info.lw = 0;
        info.lh = 0;
    }

    info.flag = SDL_GetWindowFlags(_window);
    info.mode = _render_method ? LX_WINDOW_RENDERING : LX_WINDOW_SURFACE;

    if(_render_method)
    {
        SDL_RendererInfo rinfo;
        SDL_GetRendererInfo(_renderer, &rinfo);

        info.accel = _renderer != nullptr &&
                     (rinfo.flags&SDL_RENDERER_ACCELERATED) == SDL_RENDERER_ACCELERATED;
    }
    else
    {
        info.accel = false;
    }
}


SDL_Renderer * LX_Window::getRenderer(void)
{
    return _renderer;
}


int LX_Window::getWidth(void)
{
    int w;
    SDL_GetWindowSize(_window,&w,nullptr);
    return w;
}


int LX_Window::getHeight(void)
{
    int h;
    SDL_GetWindowSize(_window,nullptr,&h);
    return h;
}


LX_Window::~LX_Window()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

};
