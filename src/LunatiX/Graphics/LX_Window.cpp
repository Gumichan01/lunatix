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

#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_Config.hpp>
#include <LunatiX/LX_Image.hpp>
#include <LunatiX/LX_TrueTypeFont.hpp>
#include <LunatiX/LX_Error.hpp>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_endian.h>

#include <GL/glu.h>

#define LX_ARGB_DEPTH 32                            /* Pixel depth (in bits) */
#define LX_PIXEL_FORMAT SDL_PIXELFORMAT_RGBA8888    /* Pixel format          */

namespace
{
const char * DEFAULT_TITLE = "LunatiX Engine v0.8";
const int DEFAULT_WIN_WIDTH = 640;
const int DEFAULT_WIN_HEIGHT = 480;

// Mask values
const Uint32 RMASK = 0xff000000;
const Uint32 GMASK = 0x00ff0000;
const Uint32 BMASK = 0x0000ff00;
const Uint32 AMASK = 0x000000ff;

Uint32 generateFlags(LX_Configuration &config)
{
    Uint32 flag = 0x00000000;

    if(config.getVideoFlag() && config.getOpenGLFlag())
        flag |= SDL_WINDOW_OPENGL;

    return flag;
}

};


namespace LX_Win
{


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
    : _window(nullptr), _renderer(nullptr), _glcontext(nullptr),
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

    if((flag&SDL_WINDOW_OPENGL) == SDL_WINDOW_OPENGL)
        _glcontext = SDL_GL_CreateContext(_window);

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


void LX_Window::drawSegment(const LX_Physics::LX_Point p, const LX_Physics::LX_Point q)
{
    SDL_RenderDrawLine(_renderer,p.x,p.y,q.x,q.y);
}


void LX_Window::drawSegments(const LX_Physics::LX_Point * p, const int count)
{
    SDL_RenderDrawLines(_renderer,(const SDL_Point*) p,count);
}


void LX_Window::drawLine(const LX_Physics::LX_Point p, const LX_Physics::LX_Vector2D v)
{
    int vx = static_cast<int>(v.vx);
    int vy = static_cast<int>(v.vy);
    drawSegment(p,LX_Physics::LX_Point(p.x + vx, p.y + vy));
    drawSegment(p,LX_Physics::LX_Point(p.x - vx, p.y - vy));
}


void LX_Window::drawRect(const LX_AABB& box)
{
    SDL_RenderDrawRect(_renderer,&box);
}


void LX_Window::drawRect(const LX_Physics::LX_Point p, const LX_Physics::LX_Vector2D v)
{
    int w = static_cast<int>(v.vx);
    int h = static_cast<int>(v.vy);
    const LX_AABB box = {p.x,p.y,w,h};
    drawRect(box);
}


void LX_Window::drawCircle(const LX_Physics::LX_Circle& c)
{
    const int x_center = c.center.x;
    const int y_center = c.center.y;
    const int r = static_cast<int>(c.radius);
    int x = 0;
    int y = r;
    int d = r - 1;

    while(y >= x)
    {
        SDL_RenderDrawPoint(_renderer, x_center + x, y_center + y);
        SDL_RenderDrawPoint(_renderer, x_center + y, y_center + x);
        SDL_RenderDrawPoint(_renderer, x_center - x, y_center + y);
        SDL_RenderDrawPoint(_renderer, x_center - y, y_center + x);
        SDL_RenderDrawPoint(_renderer, x_center + x, y_center - y);
        SDL_RenderDrawPoint(_renderer, x_center + y, y_center - x);
        SDL_RenderDrawPoint(_renderer, x_center - x, y_center - y);
        SDL_RenderDrawPoint(_renderer, x_center - y, y_center - x);

        if(d >= 2*x)
        {
            d -= 2*x + 1;
            x +=1;
        }
        else if(d < 2*(r-y))
        {
            d += 2*y - 1;
            y -= 1;
        }
        else
        {
            d += 2*(y - x - 1);
            y -= 1;
            x += 1;
        }
    }
}


void LX_Window::fillRect(const LX_AABB& box)
{
    SDL_RenderFillRect(_renderer,&box);
}


void LX_Window::fillRect(const LX_Physics::LX_Point p, const LX_Physics::LX_Vector2D v)
{
    int w = static_cast<int>(v.vx);
    int h = static_cast<int>(v.vy);
    const LX_AABB box = {p.x,p.y,w,h};
    fillRect(box);
}


void LX_Window::fillCircle(const LX_Physics::LX_Circle& c)
{
    const int x_center = c.center.x;
    const int y_center = c.center.y;
    const int r = static_cast<int>(c.radius);
    int x = 0;
    int y = r;
    int d = r - 1;

    while(y >= x)
    {
        drawSegment(LX_Physics::LX_Point(x_center - y, y_center + x),
                    LX_Physics::LX_Point(x_center + y, y_center + x));
        drawSegment(LX_Physics::LX_Point(x_center - x,y_center + y),
                    LX_Physics::LX_Point(x_center + x, y_center + y));
        drawSegment(LX_Physics::LX_Point(x_center - x, y_center - y),
                    LX_Physics::LX_Point(x_center + x, y_center - y));
        drawSegment(LX_Physics::LX_Point(x_center - y, y_center - x),
                    LX_Physics::LX_Point(x_center + y, y_center - x));

        if(d >= 2*x)
        {
            d -= 2*x + 1;
            x +=1;
        }
        else if(d < 2*(r-y))
        {
            d += 2*y - 1;
            y -= 1;
        }
        else
        {
            d += 2*(y - x - 1);
            y -= 1;
            x += 1;
        }
    }
}


void LX_Window::setDrawColor(const SDL_Color& color)
{
    SDL_SetRenderDrawColor(_renderer,color.r,color.g,color.b,color.a);
}


void LX_Window::setDrawBlendMode(SDL_BlendMode mode)
{
    SDL_SetRenderDrawBlendMode(_renderer,mode);
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


bool LX_Window::setViewPort(LX_AABB * viewport)
{
    return SDL_RenderSetViewport(_renderer, viewport) == 0;
}


void LX_Window::getViewPort(LX_AABB& viewport)
{
    SDL_RenderGetViewport(_renderer, &viewport);
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
    if(_glcontext != nullptr)
        SDL_GL_SwapWindow(_window);
    else if(_render_method)
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
    Uint8 r,g,b,a;
    SDL_GetRenderDrawColor(_renderer,&r,&g,&b,&a);
    SDL_SetRenderDrawColor(_renderer,0,0,0,255);
    SDL_RenderClear(_renderer);
    SDL_SetRenderDrawColor(_renderer,r,g,b,a);
}


void LX_Window::clearWindow(void)
{
    if(_glcontext)
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    else if(_render_method)
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
                                 LX_ARGB_DEPTH,RMASK,GMASK,BMASK,AMASK);

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


void LX_Window::glGetDrawableSize(int& w, int& h)
{
    SDL_GL_GetDrawableSize(_window,&w,&h);
}


LX_Window::~LX_Window()
{
    SDL_GL_DeleteContext(_glcontext);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

};
