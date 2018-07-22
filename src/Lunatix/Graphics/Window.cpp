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
*   @file Window.cpp
*   @brief The implementation of the window
*   @author Luxon Jean-Pierre(Gumichan01)
*/

#include <Lunatix/Window.hpp>
#include <Lunatix/Texture.hpp>
#include <Lunatix/Config.hpp>
#include <Lunatix/Error.hpp>
#include <Lunatix/ImgRect.hpp>
#include <Lunatix/Hitbox.hpp>

#include <SDL2/SDL_image.h>
#include <GL/gl.h>


namespace
{


uint32_t toSDL2VideoFlags_( const lx::Win::WinFlags& wflags ) noexcept
{
    uint32_t flag = 0x0000000;

    if ( wflags.fullscreen )
    {
        flag |= SDL_WINDOW_FULLSCREEN;
    }
    else if ( wflags.fullscreen_desktop )
    {
        flag |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    if ( wflags.opengl )
    {
        flag |= SDL_WINDOW_OPENGL;
    }

    if ( wflags.shown )
    {
        flag |= SDL_WINDOW_SHOWN;
    }
    else if ( wflags.hidden )
    {
        flag |= SDL_WINDOW_HIDDEN;
    }

    return flag;
}

uint32_t toSDL2WinFlags_( const lx::Win::WinFlags& wflags ) noexcept
{
    uint32_t flag = 0x0000000;

    if ( wflags.borderless )
    {
        flag |= SDL_WINDOW_BORDERLESS;
    }

    if ( wflags.resizable )
    {
        flag |= SDL_WINDOW_RESIZABLE;
    }

    if ( wflags.minimized )
    {
        flag |= SDL_WINDOW_MINIMIZED;
    }

    if ( wflags.maximized )
    {
        flag |= SDL_WINDOW_MAXIMIZED;
    }

    return flag;
}

uint32_t toSDL2InputFlags_( const lx::Win::WinFlags& wflags ) noexcept
{
    uint32_t flag = 0x0000000;

    if ( wflags.input_grabbed )
    {
        flag |= SDL_WINDOW_INPUT_GRABBED;
    }

    if ( wflags.input_focus )
    {
        flag |= SDL_WINDOW_INPUT_FOCUS;
    }

    if ( wflags.mouse_focus )
    {
        flag |= SDL_WINDOW_MOUSE_FOCUS;
    }

    if ( wflags.high_dpi )
    {
        flag |= SDL_WINDOW_ALLOW_HIGHDPI;
    }

    if ( wflags.mouse_capture )
    {
        flag |= SDL_WINDOW_MOUSE_CAPTURE;
    }

    return flag;
}

uint32_t toSDL2X11Flags_( const lx::Win::WinFlags& wflags ) noexcept
{
    uint32_t flag = 0x0000000;

    if ( wflags.x11_top )
    {
        flag |= SDL_WINDOW_ALWAYS_ON_TOP;
    }

    if ( wflags.x11_skip_taskbar )
    {
        flag |= SDL_WINDOW_SKIP_TASKBAR;
    }

    if ( wflags.x11_utility )
    {
        flag |= SDL_WINDOW_UTILITY;
    }

    if ( wflags.x11_tooltip )
    {
        flag |= SDL_WINDOW_TOOLTIP;
    }

    if ( wflags.x11_popup )
    {
        flag |= SDL_WINDOW_POPUP_MENU;
    }

    return flag;
}

uint32_t toSDL2Flags_( const lx::Win::WinFlags& wflags ) noexcept
{
    uint32_t flag = 0x0000000;
    flag |= toSDL2VideoFlags_( wflags );
    flag |= toSDL2WinFlags_( wflags );
    flag |= toSDL2InputFlags_( wflags );
    flag |= toSDL2X11Flags_( wflags );
    return flag;
}

inline constexpr uint32_t toSDL2Flags_( const lx::Win::ScreenMode smode ) noexcept
{
    return static_cast<uint32_t>( smode );
}

lx::Win::WinFlags fromSDL2Flags_( const uint32_t flags ) noexcept
{
    lx::Win::WinFlags wflags;

    wflags.fullscreen = ( ( flags & SDL_WINDOW_FULLSCREEN ) == SDL_WINDOW_FULLSCREEN );
    wflags.fullscreen_desktop = ( ( flags & SDL_WINDOW_FULLSCREEN ) == SDL_WINDOW_FULLSCREEN_DESKTOP );
    wflags.opengl = ( ( flags & SDL_WINDOW_OPENGL ) == SDL_WINDOW_OPENGL );
    wflags.shown = ( ( flags & SDL_WINDOW_SHOWN ) == SDL_WINDOW_SHOWN );
    wflags.hidden = ( ( flags & SDL_WINDOW_HIDDEN ) == SDL_WINDOW_HIDDEN );
    wflags.borderless = ( ( flags & SDL_WINDOW_BORDERLESS ) == SDL_WINDOW_BORDERLESS );
    wflags.resizable = ( ( flags & SDL_WINDOW_RESIZABLE ) == SDL_WINDOW_RESIZABLE );
    wflags.minimized = ( ( flags & SDL_WINDOW_MINIMIZED ) == SDL_WINDOW_MINIMIZED );
    wflags.maximized = ( ( flags & SDL_WINDOW_MAXIMIZED ) == SDL_WINDOW_MAXIMIZED );
    wflags.input_grabbed = ( ( flags & SDL_WINDOW_INPUT_GRABBED ) == SDL_WINDOW_INPUT_GRABBED );
    wflags.input_focus = ( ( flags & SDL_WINDOW_INPUT_FOCUS ) == SDL_WINDOW_INPUT_FOCUS );
    wflags.mouse_focus = ( ( flags & SDL_WINDOW_MOUSE_FOCUS ) == SDL_WINDOW_MOUSE_FOCUS );
    wflags.high_dpi = ( ( flags & SDL_WINDOW_ALLOW_HIGHDPI ) == SDL_WINDOW_ALLOW_HIGHDPI );
    wflags.mouse_capture = ( ( flags & SDL_WINDOW_MOUSE_CAPTURE ) == SDL_WINDOW_MOUSE_CAPTURE );
    wflags.x11_top = ( ( flags & SDL_WINDOW_ALWAYS_ON_TOP ) == SDL_WINDOW_ALWAYS_ON_TOP );
    wflags.x11_skip_taskbar = ( ( flags & SDL_WINDOW_SKIP_TASKBAR ) == SDL_WINDOW_SKIP_TASKBAR );
    wflags.x11_utility = ( ( flags & SDL_WINDOW_UTILITY ) == SDL_WINDOW_UTILITY );
    wflags.x11_tooltip = ( ( flags & SDL_WINDOW_TOOLTIP ) == SDL_WINDOW_TOOLTIP );
    wflags.x11_popup = ( ( flags & SDL_WINDOW_POPUP_MENU ) == SDL_WINDOW_POPUP_MENU );

    return wflags;
}

inline constexpr uint32_t setRendering_( const lx::Win::WindowInfo& info ) noexcept
{
    return info.accel ? SDL_RENDERER_ACCELERATED : SDL_RENDERER_SOFTWARE;
}

inline bool hasOpenGLsupport_( const lx::Win::WindowInfo& info ) noexcept
{
    return info.wflags.opengl;
}

uint32_t genFlags_( const lx::Config::Configuration& config ) noexcept
{
    uint32_t flag = 0x00000000;

    if ( config.getVideoFlag() && config.getOpenGLFlag() )
        flag |= SDL_WINDOW_OPENGL;

    return flag;
}


SDL_BlendMode sdlBlend_( const lx::Win::BlendMode& mode ) noexcept
{
    SDL_BlendMode m;

    switch ( mode )
    {
    case lx::Win::BlendMode::BLEND:
        m = SDL_BLENDMODE_BLEND;
        break;

    case lx::Win::BlendMode::ADD:
        m = SDL_BLENDMODE_ADD;
        break;

    case lx::Win::BlendMode::MOD:
        m = SDL_BLENDMODE_MOD;
        break;
    default:
        m = SDL_BLENDMODE_NONE;
        break;
    }

    return m;
}

}

//using namespace lx::Config;


namespace lx
{

namespace Win
{
// Pixel depth (in bits)
const int ARGB_DEPTH = 32;

const std::string DEFAULT_TITLE( "LunatiX Demo" );
const int DEFAULT_WIN_WIDTH = 640;
const int DEFAULT_WIN_HEIGHT = 480;

// Mask values
const uint32_t RMASK = 0xff000000;
const uint32_t GMASK = 0x00ff0000;
const uint32_t BMASK = 0x0000ff00;
const uint32_t AMASK = 0x000000ff;


void initWindowInfo( WindowInfo& info ) noexcept
{
    info.id = 0;
    info.title = DEFAULT_TITLE;
    info.x = SDL_WINDOWPOS_CENTERED;
    info.y = SDL_WINDOWPOS_CENTERED;
    info.w = DEFAULT_WIN_WIDTH;
    info.h = DEFAULT_WIN_HEIGHT;
    info.lw = 0;
    info.lh = 0;
    info.accel = true;
}


void loadWindowConfig( WindowInfo& info ) noexcept
{
    const lx::Config::Configuration& config = lx::Config::Configuration::getInstance();

    info.id = 0;
    info.title = DEFAULT_TITLE;
    info.x = SDL_WINDOWPOS_CENTERED;
    info.y = SDL_WINDOWPOS_CENTERED;
    info.w = DEFAULT_WIN_WIDTH;
    info.h = DEFAULT_WIN_HEIGHT;
    info.lw = 0;
    info.lh = 0;
    info.wflags = fromSDL2Flags_( genFlags_( config ) );
    info.accel = true;
}


/* Exception */

WindowException::WindowException( std::string err ) : m_msg( err ) {}

WindowException::WindowException( const WindowException& w )
    : m_msg( w.m_msg ) {}

const char * WindowException::what() const noexcept
{
    return m_msg.c_str();
}


/* Window, private implementation */

struct Window_ final
{
    SDL_Window * window      = nullptr;             /* Innternal window structure           */
    SDL_Renderer * renderer  = nullptr;
    SDL_GLContext glcontext  = nullptr;             /* The context (only used in OpenGL)    */
    int original_width       = DEFAULT_WIN_WIDTH;
    int original_height      = DEFAULT_WIN_WIDTH;
    lx::Graphics::ImgRect viewport = { { 0, 0 }, 0, 0 };

    Window_( const Window_& ) = delete;
    Window_& operator =( const Window_& ) = delete;

    explicit Window_( const WindowInfo& info ): window( nullptr ),
        renderer( nullptr ), glcontext( nullptr ), original_width( info.w ),
        original_height( info.h )
    {
        const lx::Config::Configuration& config = lx::Config::Configuration::getInstance();

        // The VSync flag is used in order to prevent screen tearing
        if ( config.getVideoFlag() && config.getVSyncFlag() )
            SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" );

        window = SDL_CreateWindow( info.title.c_str(), info.x, info.y, info.w,
                                   info.h, toSDL2Flags_( info.wflags ) );

        if ( window == nullptr )
            throw WindowException( lx::getError() );

        if ( hasOpenGLsupport_( info ) )
            glcontext = SDL_GL_CreateContext( window );

        // Hardware acceleration or software rendering
        renderer = SDL_CreateRenderer( window, -1, setRendering_( info ) );

        if ( renderer == nullptr )
        {
            std::string err_msg = "Rendering creation: ";
            err_msg = err_msg + lx::getError();

            SDL_GL_DeleteContext( glcontext );
            SDL_DestroyWindow( window );
            throw WindowException( err_msg );
        }


    }

    void clearRenderer_() noexcept
    {
        uint8_t r, g, b, a;
        const lx::Graphics::Colour C = { 0, 0, 0, 255 };
        SDL_GetRenderDrawColor( renderer, &r, &g, &b, &a );
        SDL_SetRenderDrawColor( renderer, C.r, C.g, C.b, C.a );
        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, r, g, b, a );
    }

    bool screenshot_( const std::string& filename ) noexcept
    {
        int err = 0;
        int w, h;
        SDL_Surface * sshot_surface;

        SDL_GetWindowSize( window, &w, &h );
        sshot_surface = SDL_CreateRGBSurface( 0, w, h, ARGB_DEPTH,
                                              RMASK, GMASK,
                                              BMASK, AMASK );

        if ( sshot_surface == nullptr )
            return false;

        err = SDL_RenderReadPixels( renderer, nullptr, SDL_PIXELFORMAT_RGBA8888,
                                    sshot_surface->pixels, sshot_surface->pitch );

        if ( err == -1 )
        {
            // Cannot read the pixels from the renderer
            SDL_FreeSurface( sshot_surface );
            return false;
        }

        err = IMG_SavePNG( sshot_surface, filename.c_str() );
        SDL_FreeSurface( sshot_surface );

        return err == 0;
    }


    ~Window_()
    {
        SDL_GL_DeleteContext( glcontext );
        SDL_DestroyRenderer( renderer );
        SDL_DestroyWindow( window );
    }
};


/* Window */

Window::Window( WindowInfo& info )
    : m_wimpl( new Window_( info ) )
{
    getInfo( info );
    getViewPort( m_wimpl->viewport );
}

// private function
void * Window::getRenderingSys_() const noexcept
{
    return m_wimpl->renderer;
}

void Window::setIcon( const std::string& ficon ) noexcept
{
    SDL_SetWindowIcon( m_wimpl->window, lx::Graphics::BufferedImage( ficon ).m_surface );
}


void Window::drawLine( const lx::Graphics::ImgCoord& p,
                       const lx::Graphics::ImgCoord& q ) noexcept
{
    SDL_RenderDrawLine( m_wimpl->renderer, p.x, p.y, q.x, q.y );
}

void Window::drawLines( const std::vector<lx::Graphics::ImgCoord>& vpoints ) noexcept
{
    SDL_RenderDrawLines( m_wimpl->renderer,
                         reinterpret_cast<const SDL_Point *>( &vpoints[0] ),
                         static_cast<int>( vpoints.size() ) );
}


void Window::drawRect( const lx::Graphics::ImgRect& box ) noexcept
{
    const SDL_Rect SDL_BOX = { box.p.x, box.p.y, box.w, box.h };
    SDL_RenderDrawRect( m_wimpl->renderer, &SDL_BOX );
}


void Window::drawCircle( const lx::Physics::Circle& c ) noexcept
{
    const lx::Graphics::ImgCoord& P = lx::Graphics::toPixelPosition( c.center );
    const int R = static_cast<int>( c.radius );
    int x = 0;
    int y = R;
    int d = R - 1;

    while ( y >= x )
    {
        SDL_RenderDrawPoint( m_wimpl->renderer, P.x + x, P.y + y );
        SDL_RenderDrawPoint( m_wimpl->renderer, P.x + y, P.y + x );
        SDL_RenderDrawPoint( m_wimpl->renderer, P.x - x, P.y + y );
        SDL_RenderDrawPoint( m_wimpl->renderer, P.x - y, P.y + x );
        SDL_RenderDrawPoint( m_wimpl->renderer, P.x + x, P.y - y );
        SDL_RenderDrawPoint( m_wimpl->renderer, P.x + y, P.y - x );
        SDL_RenderDrawPoint( m_wimpl->renderer, P.x - x, P.y - y );
        SDL_RenderDrawPoint( m_wimpl->renderer, P.x - y, P.y - x );

        if ( d >= 2 * x )
        {
            d -= 2 * x + 1;
            x += 1;
        }
        else if ( d < 2 * ( R - y ) )
        {
            d += 2 * y - 1;
            y -= 1;
        }
        else
        {
            d += 2 * ( y - x - 1 );
            y -= 1;
            x += 1;
        }
    }
}


void Window::fillRect( const lx::Graphics::ImgRect& box ) noexcept
{
    const SDL_Rect SDL_BOX{box.p.x, box.p.y, box.w, box.h};
    SDL_RenderFillRect( m_wimpl->renderer, &SDL_BOX );
}


void Window::fillCircle( const lx::Physics::Circle& c ) noexcept
{
    const lx::Graphics::ImgCoord& P = lx::Graphics::toPixelPosition( c.center );
    const int R = static_cast<int>( c.radius );
    int x = 0;
    int y = R;
    int d = R - 1;

    while ( y >= x )
    {
        drawLine( lx::Graphics::ImgCoord{ P.x - y, P.y + x },
                  lx::Graphics::ImgCoord{ P.x + y, P.y + x } );
        drawLine( lx::Graphics::ImgCoord{ P.x - x, P.y + y },
                  lx::Graphics::ImgCoord{ P.x + x, P.y + y } );
        drawLine( lx::Graphics::ImgCoord{ P.x - x, P.y - y },
                  lx::Graphics::ImgCoord{ P.x + x, P.y - y } );
        drawLine( lx::Graphics::ImgCoord{ P.x - y, P.y - x },
                  lx::Graphics::ImgCoord{ P.x + y, P.y - x } );

        if ( d >= 2 * x )
        {
            d -= 2 * x + 1;
            x += 1;
        }
        else if ( d < 2 * ( R - y ) )
        {
            d += 2 * y - 1;
            y -= 1;
        }
        else
        {
            d += 2 * ( y - x - 1 );
            y -= 1;
            x += 1;
        }
    }
}


void Window::setDrawColour( const Graphics::Colour& colour ) noexcept
{
    SDL_SetRenderDrawColor( m_wimpl->renderer, colour.r, colour.g, colour.b, colour.a );
}

void Window::getDrawColour( Graphics::Colour& colour ) const noexcept
{
    SDL_GetRenderDrawColor( m_wimpl->renderer, &colour.r, &colour.g, &colour.b, &colour.a );
}


void Window::setDrawBlendMode( const BlendMode mode ) noexcept
{
    SDL_SetRenderDrawBlendMode( m_wimpl->renderer, sdlBlend_( mode ) );
}

void Window::getDrawBlendMode( BlendMode& mode ) const noexcept
{
    SDL_BlendMode sdlm = sdlBlend_( mode );
    SDL_GetRenderDrawBlendMode( m_wimpl->renderer, &sdlm );
}


void Window::setTitle( const std::string& title ) noexcept
{
    SDL_SetWindowTitle( m_wimpl->window, title.c_str() );
}


std::string Window::getTitle() noexcept
{
    const char * TITLE = SDL_GetWindowTitle( m_wimpl->window );
    return std::string( ( TITLE == nullptr ) ? "" : TITLE );
}

void Window::setWindowSize( int w, int h ) noexcept
{
    SDL_SetWindowSize( m_wimpl->window, w, h );
    m_wimpl->original_width = w;
    m_wimpl->original_height = h;
    getViewPort( m_wimpl->viewport );
}

void Window::setPosition( int x, int y ) noexcept
{
    WindowInfo winfo;
    getInfo( winfo );

    if ( !winfo.wflags.fullscreen )
        SDL_SetWindowPosition( m_wimpl->window, x, y );

}

int Window::getXPosition() noexcept
{
    int x;
    SDL_GetWindowPosition( m_wimpl->window, &x, nullptr );
    return x;
}

int Window::getYPosition() noexcept
{
    int y;
    SDL_GetWindowPosition( m_wimpl->window, nullptr, &y );
    return y;
}

void Window::setOpacity( const float percent ) noexcept
{
    const float MAX_PERCENT = 100.0f;
    const float MIN_PERCENT = 0.0f;
    float real_percent = 0.0f;

    if ( percent > MAX_PERCENT )
        real_percent = MAX_PERCENT;

    else if ( percent < MIN_PERCENT )
        real_percent = MIN_PERCENT;

    else
        real_percent = percent;

    float opacity = real_percent / MAX_PERCENT;
    SDL_SetWindowOpacity( m_wimpl->window, opacity );
}

float Window::getOpacity() noexcept
{
    float opacity;
    SDL_GetWindowOpacity( m_wimpl->window, &opacity );
    return opacity;
}

void Window::setViewPort( const lx::Graphics::ImgRect& viewport ) noexcept
{
    const SDL_Rect VPORT = { viewport.p.x, viewport.p.y, viewport.w, viewport.h };
    SDL_RenderSetViewport( m_wimpl->renderer, &VPORT );
}

void Window::resetViewPort() noexcept
{
    setViewPort( m_wimpl->viewport );
}

void Window::getViewPort( lx::Graphics::ImgRect& viewport ) const noexcept
{
    SDL_Rect rect;
    SDL_RenderGetViewport( m_wimpl->renderer, &rect );
    viewport = { { rect.x, rect.y }, rect.w, rect.h };
}


void Window::toggleFullscreen( const ScreenMode flag ) noexcept
{
    SDL_SetWindowFullscreen( m_wimpl->window, toSDL2Flags_( flag ) );

    if ( flag == ScreenMode::NO_FULLSCREEN )
    {
        setWindowSize( m_wimpl->original_width, m_wimpl->original_height );
    }
    else if ( flag == ScreenMode::FULLSCREEN )
    {
        SDL_RenderSetLogicalSize( m_wimpl->renderer, m_wimpl->original_width,
                                  m_wimpl->original_height );
    }

    getViewPort( m_wimpl->viewport );
}

void Window::show() noexcept
{
    SDL_ShowWindow( m_wimpl->window );
}

void Window::hide() noexcept
{
    SDL_HideWindow( m_wimpl->window );
}

void Window::update() noexcept
{
    if ( m_wimpl->glcontext != nullptr )
        SDL_GL_SwapWindow( m_wimpl->window );
    else
        SDL_RenderPresent( m_wimpl->renderer );
}

void Window::clearWindow() noexcept
{
    if ( m_wimpl->glcontext != nullptr )
    {
        const lx::Graphics::glColour GLC = { 0.0f, 0.0f, 0.0f, 1.0f };
        glClearColor( GLC.r, GLC.g, GLC.b, GLC.a );
        glClear( GL_COLOR_BUFFER_BIT );
    }
    else
        m_wimpl->clearRenderer_();
}


bool Window::screenshot( const std::string& filename ) noexcept
{
    return m_wimpl->screenshot_( filename );
}

uint32_t Window::getID() const noexcept
{
    return SDL_GetWindowID( m_wimpl->window );
}

void Window::getInfo( WindowInfo& info ) const noexcept
{
    info.id = getID();
    info.title = SDL_GetWindowTitle( m_wimpl->window );
    info.wflags = fromSDL2Flags_( SDL_GetWindowFlags( m_wimpl->window ) );

    SDL_GetWindowPosition( m_wimpl->window, &info.x, &info.y );
    SDL_GetWindowSize( m_wimpl->window, &info.w, &info.h );
    info.lw = getLogicalWidth();
    info.lh = getLogicalHeight();

    SDL_RendererInfo rinfo;
    SDL_GetRendererInfo( m_wimpl->renderer, &rinfo );
    info.accel = ( ( rinfo.flags & SDL_RENDERER_ACCELERATED ) != 0 );
}

int Window::getWidth() const noexcept
{
    int w;
    SDL_GetWindowSize( m_wimpl->window, &w, nullptr );
    return w;
}

int Window::getHeight() const noexcept
{
    int h;
    SDL_GetWindowSize( m_wimpl->window, nullptr, &h );
    return h;
}

int Window::getLogicalWidth() const noexcept
{
    int w;
    SDL_RenderGetLogicalSize( m_wimpl->renderer, &w, nullptr );
    return w == 0 ? getWidth() : w;
}

int Window::getLogicalHeight() const noexcept
{
    int h;
    SDL_RenderGetLogicalSize( m_wimpl->renderer, nullptr, &h );
    return h == 0 ? getHeight() : h;
}

void Window::glGetDrawableSize( int& w, int& h ) const noexcept
{
    SDL_GL_GetDrawableSize( m_wimpl->window, &w, &h );
}

bool Window::glMakeCurrent() noexcept
{
    if ( m_wimpl->glcontext == nullptr )
    {
        lx::setError( "The current window is not an OpenGL window" );
        return false;
    }

    return SDL_GL_MakeCurrent( m_wimpl->window, m_wimpl->glcontext ) == 0;
}

Window::~Window()
{
    m_wimpl.reset();
}

}   // Win

}   // lx
