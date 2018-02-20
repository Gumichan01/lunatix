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

/**
*   @file LX_Window.cpp
*   @brief The implementation of the window
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*
*/

#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_Texture.hpp>
#include <LunatiX/LX_Config.hpp>
#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_ImgRect.hpp>
#include <LunatiX/LX_Hitbox.hpp>
/// todo v0.14.0 remove it (impl)
#include <LunatiX/LX_Vector2D.hpp>
/// end

#include <SDL2/SDL_image.h>
#include <GL/gl.h>


namespace
{

using LX_Win::LX_WinMode;
using LX_Win::LX_BlendMode;

constexpr uint32_t OPENGL_U = static_cast<uint32_t>(LX_Win::LX_WinMode::OPENGL);

inline constexpr uint32_t openglFlag() noexcept
{
    return static_cast<uint32_t>(LX_WinMode::SHOWN) | OPENGL_U;
}

inline uint32_t renderFlag(const LX_Win::LX_WindowInfo& info) noexcept
{
    return info.accel ? SDL_RENDERER_ACCELERATED : SDL_RENDERER_SOFTWARE;
}

inline bool hasOpenGLsupport(const LX_Win::LX_WindowInfo& info) noexcept
{
    return (info.flag & OPENGL_U) == OPENGL_U;
}

uint32_t genFlags_(const LX_Config::LX_Configuration& config) noexcept
{
    uint32_t flag = 0x00000000;

    if(config.getVideoFlag() && config.getOpenGLFlag())
        flag |= openglFlag();

    return flag;
}

bool fullscreenValidMode_(const LX_WinMode& mode)
{
    return mode == LX_WinMode::FULLSCREEN || mode == LX_WinMode::NO_FULLSCREEN
    || mode == LX_WinMode::FULLSCREEN_DESKTOP;

}

SDL_BlendMode sdlBlend_(const LX_BlendMode& mode) noexcept
{
    SDL_BlendMode m;

    switch(mode)
    {
    case LX_BlendMode::LX_BLENDMODE_BLEND:
        m = SDL_BLENDMODE_BLEND;
        break;

    case LX_BlendMode::LX_BLENDMODE_ADD:
        m = SDL_BLENDMODE_ADD;
        break;

    case LX_BlendMode::LX_BLENDMODE_MOD:
        m = SDL_BLENDMODE_MOD;
        break;
    default:
        m = SDL_BLENDMODE_NONE;
        break;
    }

    return m;
}

}

using namespace LX_Config;

namespace LX_Win
{
// Pixel depth (in bits)
const int LX_ARGB_DEPTH = 32;

const char * DEFAULT_TITLE = "LunatiX Demo";
const int DEFAULT_WIN_WIDTH = 640;
const int DEFAULT_WIN_HEIGHT = 480;

// Mask values
const uint32_t RMASK = 0xff000000;
const uint32_t GMASK = 0x00ff0000;
const uint32_t BMASK = 0x0000ff00;
const uint32_t AMASK = 0x000000ff;


void LX_initWindowInfo(LX_WindowInfo &info) noexcept
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


void LX_loadWindowConfig(LX_WindowInfo &info) noexcept
{
    const LX_Configuration& config = LX_Configuration::getInstance();

    info.id = 0;
    info.title = DEFAULT_TITLE;
    info.x = SDL_WINDOWPOS_CENTERED;
    info.y = SDL_WINDOWPOS_CENTERED;
    info.w = DEFAULT_WIN_WIDTH;
    info.h = DEFAULT_WIN_HEIGHT;
    info.lw = 0;
    info.lh = 0;
    info.flag = genFlags_(config);
    info.accel = true;
}


/* Exception */

LX_WindowException::LX_WindowException(std::string err) : _string_error(err) {}

LX_WindowException::LX_WindowException(const LX_WindowException& w)
    : _string_error(w._string_error) {}

const char * LX_WindowException::what() const noexcept
{
    return _string_error.c_str();
}


/* LX_Window, private implementation */

struct LX_Window_
{
    SDL_Window *_window      = nullptr;             /* The internal window structure        */
    SDL_Renderer *_renderer  = nullptr;             /* The main renderer                    */
    SDL_GLContext _glcontext = nullptr;             /* The context (only used in OpenGL)    */
    int _original_width      = DEFAULT_WIN_WIDTH;   /* The width of the window              */
    int _original_height     = DEFAULT_WIN_WIDTH;   /* The height of the window             */

    LX_Window_(const LX_Window_&) = delete;
    LX_Window_& operator =(const LX_Window_&) = delete;

    explicit LX_Window_(const LX_WindowInfo& info): _window(nullptr),
        _renderer(nullptr), _glcontext(nullptr), _original_width(info.w),
        _original_height(info.h)
    {
        const LX_Configuration& config = LX_Configuration::getInstance();

        // Video flag and VSync flag actives -> add the option
        if(config.getVideoFlag() && config.getVSyncFlag())
            SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

        _window = SDL_CreateWindow(info.title.c_str(), info.x, info.y, info.w,
                                   info.h, info.flag);

        if(_window == nullptr)
            throw LX_WindowException(LX_GetError());

        if(hasOpenGLsupport(info))
            _glcontext = SDL_GL_CreateContext(_window);

        // Hardware acceleration or software rendering
        _renderer = SDL_CreateRenderer(_window, -1, renderFlag(info));

        if(_renderer == nullptr)
        {
            std::string err_msg = "Rendering creation: ";
            err_msg = err_msg + LX_GetError();

            SDL_GL_DeleteContext(_glcontext);
            SDL_DestroyWindow(_window);
            throw LX_WindowException(err_msg);
        }
    }

    void clearRenderer_() noexcept
    {
        uint8_t r, g, b, a;
        SDL_GetRenderDrawColor(_renderer, &r, &g, &b, &a);
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);
        SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    }

    bool screenshot_(const std::string& filename) noexcept
    {
        int err = 0;
        int w, h;
        SDL_Surface *sshot;

        SDL_GetWindowSize(_window, &w, &h);
        sshot = SDL_CreateRGBSurface(0, w, h, LX_ARGB_DEPTH,
                                     RMASK, GMASK, BMASK, AMASK);

        if(sshot == nullptr)
            return false;

        err = SDL_RenderReadPixels(_renderer, nullptr, SDL_PIXELFORMAT_RGBA8888,
                                   sshot->pixels, sshot->pitch);

        if(err == -1)
        {
            // Cannot read the pixels from the renderer
            SDL_FreeSurface(sshot);
            return false;
        }

        err = IMG_SavePNG(sshot, filename.c_str());
        SDL_FreeSurface(sshot);

        return err == 0;
    }


    ~LX_Window_()
    {
        SDL_GL_DeleteContext(_glcontext);
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
    }
};


/* LX_Window */

LX_Window::LX_Window(LX_WindowInfo &info)
    : _wimpl(new LX_Window_(info))
{
    getInfo(info);
}

// private function
void * LX_Window::getRenderingSys() const noexcept
{
    return _wimpl->_renderer;
}

void LX_Window::setIcon(const std::string& ficon) noexcept
{
    SDL_SetWindowIcon(_wimpl->_window, LX_Graphics::LX_BufferedImage(ficon)._surface);
}


void LX_Window::drawLine(const LX_Graphics::LX_ImgCoord& p,
                         const LX_Graphics::LX_ImgCoord& q) noexcept
{
    SDL_RenderDrawLine(_wimpl->_renderer, p.x, p.y, q.x, q.y);
}

void LX_Window::drawLines(const LX_Graphics::LX_ImgCoord * p, const int count) noexcept
{
    SDL_RenderDrawLines(_wimpl->_renderer,(const SDL_Point*) p, count);
}

void LX_Window::drawLines(const std::vector<LX_Graphics::LX_ImgCoord>& vpoints) noexcept
{
    SDL_RenderDrawLines(_wimpl->_renderer,(const SDL_Point*) &vpoints[0],
                        vpoints.size());
}

void LX_Window::drawLine(const LX_Graphics::LX_ImgCoord& p,
                         const LX_Physics::LX_Vector2D& v) noexcept
{
    const int vx = static_cast<int>(v.vx);
    const int vy = static_cast<int>(v.vy);
    drawLine(p, LX_Graphics::LX_ImgCoord{p.x + vx, p.y + vy});
    drawLine(p, LX_Graphics::LX_ImgCoord{p.x - vx, p.y - vy});
}


void LX_Window::drawRect(const LX_Graphics::LX_ImgRect& box) noexcept
{
    const SDL_Rect SDL_BOX{box.p.x, box.p.y, box.w, box.h};
    SDL_RenderDrawRect(_wimpl->_renderer, &SDL_BOX);
}

void LX_Window::drawRect(const LX_Graphics::LX_ImgCoord& p,
                         const LX_Physics::LX_Vector2D& v) noexcept
{
    using LX_Graphics::LX_ImgCoord;
    int w = static_cast<int>(v.vx);
    int h = static_cast<int>(v.vy);
    drawRect(LX_Graphics::LX_ImgRect{LX_ImgCoord{p.x, p.y}, w, h});
}

void LX_Window::drawCircle(const LX_Physics::LX_Circle& c) noexcept
{
    const LX_Graphics::LX_ImgCoord& P = LX_Graphics::toPixelPosition(c.center);
    const int R = static_cast<int>(c.radius);
    int x = 0;
    int y = R;
    int d = R - 1;

    while(y >= x)
    {
        SDL_RenderDrawPoint(_wimpl->_renderer, P.x + x, P.y + y);
        SDL_RenderDrawPoint(_wimpl->_renderer, P.x + y, P.y + x);
        SDL_RenderDrawPoint(_wimpl->_renderer, P.x - x, P.y + y);
        SDL_RenderDrawPoint(_wimpl->_renderer, P.x - y, P.y + x);
        SDL_RenderDrawPoint(_wimpl->_renderer, P.x + x, P.y - y);
        SDL_RenderDrawPoint(_wimpl->_renderer, P.x + y, P.y - x);
        SDL_RenderDrawPoint(_wimpl->_renderer, P.x - x, P.y - y);
        SDL_RenderDrawPoint(_wimpl->_renderer, P.x - y, P.y - x);

        if(d >= 2 * x)
        {
            d -= 2 * x + 1;
            x +=1;
        }
        else if(d < 2 * (R - y))
        {
            d += 2 * y - 1;
            y -= 1;
        }
        else
        {
            d += 2 * (y - x - 1);
            y -= 1;
            x += 1;
        }
    }
}


void LX_Window::fillRect(const LX_Graphics::LX_ImgRect& box) noexcept
{
    const SDL_Rect SDL_BOX{box.p.x, box.p.y, box.w, box.h};
    SDL_RenderFillRect(_wimpl->_renderer, &SDL_BOX);
}

void LX_Window::fillRect(const LX_Graphics::LX_ImgCoord& p,
                         const LX_Physics::LX_Vector2D& v) noexcept
{
    int w = static_cast<int>(v.vx);
    int h = static_cast<int>(v.vy);
    fillRect(LX_Graphics::LX_ImgRect{p.x, p.y, w, h});
}

void LX_Window::fillCircle(const LX_Physics::LX_Circle& c) noexcept
{
    const LX_Graphics::LX_ImgCoord& P = LX_Graphics::toPixelPosition(c.center);
    const int R = static_cast<int>(c.radius);
    int x = 0;
    int y = R;
    int d = R - 1;

    while(y >= x)
    {
        drawLine(LX_Graphics::LX_ImgCoord{P.x - y, P.y + x},
                 LX_Graphics::LX_ImgCoord{P.x + y, P.y + x});
        drawLine(LX_Graphics::LX_ImgCoord{P.x - x,P.y + y},
                 LX_Graphics::LX_ImgCoord{P.x + x, P.y + y});
        drawLine(LX_Graphics::LX_ImgCoord{P.x - x, P.y - y},
                 LX_Graphics::LX_ImgCoord{P.x + x, P.y - y});
        drawLine(LX_Graphics::LX_ImgCoord{P.x - y, P.y - x},
                 LX_Graphics::LX_ImgCoord{P.x + y, P.y - x});

        if(d >= 2 * x)
        {
            d -= 2 * x + 1;
            x +=1;
        }
        else if(d < 2 * (R - y))
        {
            d += 2 * y - 1;
            y -= 1;
        }
        else
        {
            d += 2 * (y - x - 1);
            y -= 1;
            x += 1;
        }
    }
}


void LX_Window::setDrawColour(const LX_Colour& colour) noexcept
{
    SDL_SetRenderDrawColor(_wimpl->_renderer, colour.r, colour.g, colour.b, colour.a);
}

void LX_Window::getDrawColour(LX_Colour& colour) const noexcept
{
    SDL_GetRenderDrawColor(_wimpl->_renderer, &colour.r, &colour.g, &colour.b, &colour.a);
}


void LX_Window::setDrawBlendMode(const LX_BlendMode mode) noexcept
{
    SDL_SetRenderDrawBlendMode(_wimpl->_renderer, sdlBlend_(mode));
}

void LX_Window::getDrawBlendMode(LX_BlendMode& mode) const noexcept
{
    SDL_BlendMode sdlm = sdlBlend_(mode);
    SDL_GetRenderDrawBlendMode(_wimpl->_renderer, &sdlm);
}


void LX_Window::setTitle(const std::string& title) noexcept
{
    SDL_SetWindowTitle(_wimpl->_window, title.c_str());
}

void LX_Window::setWindowSize(int w, int h) noexcept
{
    SDL_SetWindowSize(_wimpl->_window, w, h);
    _wimpl->_original_width = w;
    _wimpl->_original_height = h;
}


void LX_Window::setViewPort(const LX_Graphics::LX_ImgRect& viewport) noexcept
{
    const SDL_Rect VPORT{viewport.p.x, viewport.p.y, viewport.w, viewport.h};
    SDL_RenderSetViewport(_wimpl->_renderer, &VPORT);
}

void LX_Window::resetViewPort() noexcept
{
    SDL_RenderSetViewport(_wimpl->_renderer, nullptr);
}

void LX_Window::getViewPort(LX_Graphics::LX_ImgRect& viewport) const noexcept
{
    SDL_Rect rect;
    SDL_RenderGetViewport(_wimpl->_renderer, &rect);
    viewport = {LX_Graphics::LX_ImgCoord{rect.x, rect.y}, rect.w, rect.h};
}


void LX_Window::toggleFullscreen(const LX_WinMode flag) noexcept
{
    if(fullscreenValidMode_(flag))
    {
        SDL_SetWindowFullscreen(_wimpl->_window, static_cast<uint32_t>(flag));

        if(flag == LX_WinMode::NO_FULLSCREEN)
        {
            setWindowSize(_wimpl->_original_width, _wimpl->_original_height);
        }
        else if(flag == LX_WinMode::FULLSCREEN)
        {
            SDL_RenderSetLogicalSize(_wimpl->_renderer, _wimpl->_original_width,
                                     _wimpl->_original_height);
        }
    }
}

void LX_Window::show() noexcept
{
    SDL_ShowWindow(_wimpl->_window);
}

void LX_Window::hide() noexcept
{
    SDL_HideWindow(_wimpl->_window);
}

void LX_Window::update() noexcept
{
    if(_wimpl->_glcontext != nullptr)
        SDL_GL_SwapWindow(_wimpl->_window);
    else
        SDL_RenderPresent(_wimpl->_renderer);
}

void LX_Window::clearWindow() noexcept
{
    if(_wimpl->_glcontext != nullptr)
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    else
        _wimpl->clearRenderer_();
}


bool LX_Window::screenshot(const std::string& filename) noexcept
{
    return _wimpl->screenshot_(filename);
}

uint32_t LX_Window::getID() const noexcept
{
    return SDL_GetWindowID(_wimpl->_window);
}

void LX_Window::getInfo(LX_WindowInfo &info) const noexcept
{
    info.id = getID();
    info.title = SDL_GetWindowTitle(_wimpl->_window);
    info.flag = SDL_GetWindowFlags(_wimpl->_window);

    SDL_GetWindowPosition(_wimpl->_window, &info.x, &info.y);
    SDL_GetWindowSize(_wimpl->_window, &info.w, &info.h);
    info.lw = getLogicalWidth();
    info.lh = getLogicalHeight();

    SDL_RendererInfo rinfo;
    SDL_GetRendererInfo(_wimpl->_renderer, &rinfo);
    info.accel = ((rinfo.flags&SDL_RENDERER_ACCELERATED) != 0);
}

int LX_Window::getWidth() const noexcept
{
    int w;
    SDL_GetWindowSize(_wimpl->_window, &w, nullptr);
    return w;
}

int LX_Window::getHeight() const noexcept
{
    int h;
    SDL_GetWindowSize(_wimpl->_window, nullptr, &h);
    return h;
}

int LX_Window::getLogicalWidth() const noexcept
{
    int w;
    SDL_RenderGetLogicalSize(_wimpl->_renderer, &w, nullptr);
    return w == 0 ? getWidth() : w;
}

int LX_Window::getLogicalHeight() const noexcept
{
    int h;
    SDL_RenderGetLogicalSize(_wimpl->_renderer, nullptr, &h);
    return h == 0 ? getHeight() : h;
}

void LX_Window::glGetDrawableSize(int& w, int& h) const noexcept
{
    SDL_GL_GetDrawableSize(_wimpl->_window, &w, &h);
}

bool LX_Window::glMakeCurrent() noexcept
{
    if(_wimpl->_glcontext == nullptr)
    {
        LX_SetError("The current window is not an OpenGL window");
        return false;
    }

    return SDL_GL_MakeCurrent(_wimpl->_window, _wimpl->_glcontext) == 0;
}

LX_Window::~LX_Window()
{
    _wimpl.reset();
}

}
