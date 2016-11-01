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
*    @file LX_Window.cpp
*    @brief The implementation of the window
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_Config.hpp>
#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_Hitbox.hpp>
#include <LunatiX/LX_Vector2D.hpp>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

#include <GL/glu.h>


namespace
{

const int LX_ARGB_DEPTH = 32;                               /* Pixel depth (in bits) */
const uint32_t LX_PIXEL_FORMAT = SDL_PIXELFORMAT_RGBA8888;  /* Pixel format          */

const char * DEFAULT_TITLE = "LunatiX v0.8";
const int DEFAULT_WIN_WIDTH = 640;
const int DEFAULT_WIN_HEIGHT = 480;

// Mask values
const uint32_t RMASK = 0xff000000;
const uint32_t GMASK = 0x00ff0000;
const uint32_t BMASK = 0x0000ff00;
const uint32_t AMASK = 0x000000ff;

uint32_t generateFlags(LX_Config::LX_Configuration &config)
{
    uint32_t flag = 0x00000000;

    if(config.getVideoFlag() && config.getOpenGLFlag())
        flag |= SDL_WINDOW_OPENGL;

    return flag;
}

};


namespace LX_Win
{


void LX_initWindowInfo(LX_WindowInfo &info)
{
    info.id = 0;
    info.title = DEFAULT_TITLE;
    info.x = SDL_WINDOWPOS_CENTERED;
    info.y = SDL_WINDOWPOS_CENTERED;
    info.w = DEFAULT_WIN_WIDTH;
    info.h = DEFAULT_WIN_HEIGHT;
    info.lw = 0;
    info.lh = 0;
    info.flag = 0;
    info.accel = true;
}


void LX_loadWindowConfig(LX_WindowInfo &info)
{
    LX_Config::LX_Configuration *config = LX_Config::LX_Configuration::getInstance();

    if(config == nullptr)
        LX_initWindowInfo(info);
    else
    {
        info.id = 0;
        info.title = DEFAULT_TITLE;
        info.x = SDL_WINDOWPOS_CENTERED;
        info.y = SDL_WINDOWPOS_CENTERED;
        info.w = config->getWinWidth();
        info.h = config->getWinHeight();
        info.lw = 0;
        info.lh = 0;
        info.flag = generateFlags(*config);
        info.accel = true;
    }
}

/* Exception */

LX_WindowException::LX_WindowException(std::string err) : _string_error(err) {}

LX_WindowException::LX_WindowException(const LX_WindowException& w)
    : _string_error(w._string_error) {}

const char * LX_WindowException::what() const noexcept
{
    return _string_error.c_str();
}

LX_WindowException::~LX_WindowException() noexcept {}


/* LX_Window */

LX_Window::LX_Window(LX_WindowInfo &info)
    : _window(nullptr), _renderer(nullptr), _glcontext(nullptr),
      _original_width(info.w), _original_height(info.h)
{
    createWindow_(info.title,info.x,info.y,info.w,info.h,info.flag,info.accel);
    getInfo(info);
}


/*
*   Private function that initializes the window according to the configuration
*/
void LX_Window::createWindow_(std::string &title, int posX, int posY, int w, int h,
                              uint32_t flag, bool accel)
{
    _window = SDL_CreateWindow(title.c_str(),posX,posY,w,h,flag);

    if(_window == nullptr)
        throw LX_WindowException(LX_GetError());

    if((flag&SDL_WINDOW_OPENGL) == SDL_WINDOW_OPENGL)
        _glcontext = SDL_GL_CreateContext(_window);

    createRenderer_(accel);
}


/*
*   Private function that creates a renderer for the window
*/
void LX_Window::createRenderer_(bool accel)
{
    uint32_t render_flag = 0x00000000;
    LX_Config::LX_Configuration *config = LX_Config::LX_Configuration::getInstance();

    // Hardware acceleration or software rendering
    if(accel)
        render_flag = SDL_RENDERER_ACCELERATED;
    else
        render_flag = SDL_RENDERER_SOFTWARE;

    // Video flag and VSync flag actives -> add the option
    if(config->getVideoFlag() && config->getVSyncFlag())
        SDL_SetHint(SDL_HINT_RENDER_VSYNC,"1");

    _renderer = SDL_CreateRenderer(_window,-1,render_flag);

    if(_renderer == nullptr)
    {
        std::string err_msg = "Rendering creation: ";
        err_msg = err_msg + LX_GetError();
        SDL_GL_DeleteContext(_glcontext);
        SDL_DestroyWindow(_window);
        throw LX_WindowException(err_msg);
    }
}


void LX_Window::drawSegment(const LX_Physics::LX_Point& p, const LX_Physics::LX_Point& q)
{
    SDL_RenderDrawLine(_renderer,p.x,p.y,q.x,q.y);
}


void LX_Window::drawSegments(const LX_Physics::LX_Point * p, const int count)
{
    SDL_RenderDrawLines(_renderer,(const SDL_Point*) p,count);
}


void LX_Window::drawLine(const LX_Physics::LX_Point& p, const LX_Physics::LX_Vector2D& v)
{
    const int vx = static_cast<int>(v.vx);
    const int vy = static_cast<int>(v.vy);
    drawSegment(p,LX_Physics::LX_Point(p.x + vx, p.y + vy));
    drawSegment(p,LX_Physics::LX_Point(p.x - vx, p.y - vy));
}


void LX_Window::drawRect(const LX_AABB& box)
{
    SDL_RenderDrawRect(_renderer,&box);
}


void LX_Window::drawRect(const LX_Physics::LX_Point& p, const LX_Physics::LX_Vector2D& v)
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


void LX_Window::fillRect(const LX_Physics::LX_Point& p, const LX_Physics::LX_Vector2D& v)
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


void LX_Window::getDrawColor(SDL_Color& color) const
{
    SDL_GetRenderDrawColor(_renderer,&color.r,&color.g,&color.b,&color.a);
}


void LX_Window::setDrawBlendMode(SDL_BlendMode mode)
{
    SDL_SetRenderDrawBlendMode(_renderer,mode);
}


void LX_Window::getDrawBlendMode(SDL_BlendMode& mode) const
{
    SDL_GetRenderDrawBlendMode(_renderer,&mode);
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
    return SDL_RenderSetViewport(_renderer,viewport) == 0;
}


void LX_Window::getViewPort(LX_AABB& viewport) const
{
    SDL_RenderGetViewport(_renderer,&viewport);
}


void LX_Window::toggleFullscreen(uint32_t flag)
{
    SDL_SetWindowFullscreen(_window,flag);

    if(flag == LX_GRAPHICS_NO_FULLSCREEN)   // set the window at the original size
    {
        setWindowSize(_original_width,_original_height);
    }
    else if(flag == LX_GRAPHICS_FULLSCREEN)
    {
        SDL_RenderSetLogicalSize(_renderer,_original_width,_original_height);
    }
}


/*
*   This private function updates the renderer of the window
*/
void LX_Window::updateRenderer_()
{
    SDL_RenderPresent(_renderer);
}


void LX_Window::update()
{
    if(_glcontext != nullptr)
        SDL_GL_SwapWindow(_window);
    else
        updateRenderer_();
}


/*
*   Private function that clears the main window renderer
*/
void LX_Window::clearRenderer_()
{
    uint8_t r,g,b,a;
    SDL_GetRenderDrawColor(_renderer,&r,&g,&b,&a);
    SDL_SetRenderDrawColor(_renderer,0,0,0,255);
    SDL_RenderClear(_renderer);
    SDL_SetRenderDrawColor(_renderer,r,g,b,a);
}


void LX_Window::clearWindow()
{
    if(_glcontext)
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    else
        clearRenderer_();
}


/*
*   Private function that makes a screenshot using the renderer
*/
bool LX_Window::screenshot_(std::string& filename)
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


bool LX_Window::screenshot(std::string filename)
{
    return screenshot_(filename);
}


uint32_t LX_Window::getID()
{
    return SDL_GetWindowID(_window);
}


void LX_Window::getInfo(LX_WindowInfo &info)
{
    info.id = getID();
    info.title = SDL_GetWindowTitle(_window);
    info.flag = SDL_GetWindowFlags(_window);

    SDL_GetWindowPosition(_window,&info.x,&info.y);
    SDL_GetWindowSize(_window, &info.w,&info.h);
    SDL_RenderGetLogicalSize(_renderer,&info.lw,&info.lh);

    SDL_RendererInfo rinfo;
    SDL_GetRendererInfo(_renderer, &rinfo);
    info.accel = ( (rinfo.flags&SDL_RENDERER_ACCELERATED) != 0 );
}


int LX_Window::getWidth() const
{
    int w;
    SDL_GetWindowSize(_window,&w,nullptr);
    return w;
}


int LX_Window::getHeight() const
{
    int h;
    SDL_GetWindowSize(_window,nullptr,&h);
    return h;
}


int LX_Window::getLogicalWidth() const
{
    int w;
    SDL_RenderGetLogicalSize(_renderer,&w,nullptr);
    return w == 0 ? getWidth() : w;
}


int LX_Window::getLogicalHeight() const
{
    int h;
    SDL_RenderGetLogicalSize(_renderer,nullptr,&h);
    return h == 0 ? getHeight() : h;
}


void LX_Window::glGetDrawableSize(int& w, int& h) const
{
    SDL_GL_GetDrawableSize(_window,&w,&h);
}


bool LX_Window::glMakeCurrent()
{
    if(_glcontext == nullptr)
    {
        LX_SetError("The current window is not an OpenGL window");
        return false;
    }

    return SDL_GL_MakeCurrent(_window,_glcontext) == 0;
}


LX_Window::~LX_Window()
{
    SDL_GL_DeleteContext(_glcontext);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

};
