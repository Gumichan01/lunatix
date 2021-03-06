
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
*   @file Texture.cpp
*   @brief The implementation of the image
*   @author Luxon Jean-Pierre(Gumichan01)
*/

#include <Lunatix/Texture.hpp>
#include <Lunatix/TrueTypeFont.hpp>
#include <Lunatix/Window.hpp>
#include <Lunatix/Error.hpp>
#include <Lunatix/Log.hpp>

#include <SDL2/SDL_image.h>

#include <functional>


namespace
{

constexpr double DEGREE_180 = 180.0;
const lx::Graphics::ImgRect RNULL = { { 0, 0 }, 0, 0 };
const lx::Graphics::Colour CNULL = { 0, 0, 0, 0 };


inline constexpr SDL_Renderer * render( void * r )
{
    return static_cast<SDL_Renderer *>( r );
}

inline constexpr uint32_t u32( lx::Graphics::PixelFormat& x )
{
    return static_cast<uint32_t>( x );
}

inline constexpr SDL_RendererFlip cast_( const lx::Graphics::MirrorEffect& mirror ) noexcept
{
    return static_cast<SDL_RendererFlip>( mirror );
}

inline constexpr double radianToDegree( const double angle ) noexcept
{
    return angle * DEGREE_180 / M_PI;
}

// Load a image from a file
SDL_Surface * loadSurface_( const std::string& filename,
                            lx::Graphics::PixelFormat& format ) noexcept
{
    SDL_Surface * loaded = IMG_Load( filename.c_str() );

    if ( loaded == nullptr )
        return nullptr;

    SDL_Surface * optimized = SDL_ConvertSurfaceFormat( loaded, u32( format ), 0 );
    SDL_FreeSurface( loaded );
    return optimized;
}

// Load a texture from a file
SDL_Texture * loadTexture_( const std::string& filename,
                            lx::Graphics::PixelFormat& format,
                            SDL_Renderer * r ) noexcept
{
    SDL_Surface * tmp_s = loadSurface_( filename, format );

    if ( tmp_s == nullptr )
        return nullptr;

    SDL_Texture * tmp_t = SDL_CreateTextureFromSurface( r, tmp_s );
    SDL_FreeSurface( tmp_s );
    return tmp_t;
}

inline constexpr SDL_Rect sdl_rect_( const lx::Graphics::ImgRect& imgr )
{
    return SDL_Rect{ imgr.p.x, imgr.p.y, imgr.w, imgr.h };
}

inline constexpr bool isNull_( const SDL_Rect& rect )
{
    return rect.x == 0 && rect.y == 0 && rect.w == 0 && rect.h == 0;
}

}


namespace lx
{

namespace Graphics
{

ImageException::ImageException( std::string err ) : m_msg( err ) {}

ImageException::ImageException( const ImageException& me )
    : m_msg( me.m_msg ) {}

const char * ImageException::what() const noexcept
{
    return m_msg.c_str();
}


/** Texture */

//  protected zero-argument constructor
Texture::Texture( lx::Win::Window& w, PixelFormat format )
    : _texture( nullptr ), _win( w ), _format( format ) {}


Texture::Texture( SDL_Texture * t, lx::Win::Window& w, PixelFormat format )
    : _texture( t ), _win( w ), _format( format ) {}


Texture::Texture( const std::string& filename, lx::Win::Window& w,
                  PixelFormat format )
    : _texture( nullptr ), _win( w ), _format( format )
{
    _texture = loadTexture_( filename, format, render( w.getRenderingSys_() ) );

    if ( _texture == nullptr )
        throw ImageException( "Texture — Cannot load " + filename );
}


Texture::Texture( const UTF8string& filename, lx::Win::Window& w,
                  PixelFormat format )
    : Texture( filename.utf8_sstring(), w, format ) {}


lx::Win::Window& Texture::getWindow() const noexcept
{
    return _win;
}

PixelFormat Texture::getFormat() const noexcept
{
    return _format;
}


Texture::~Texture()
{
    if ( _texture != nullptr )
        SDL_DestroyTexture( _texture );
}


/** Sprite */

// protected constructor
Sprite::Sprite( SDL_Texture * t, lx::Win::Window& w,
                const UTF8string& filename,
                const ImgRect& area, PixelFormat format )
    : Texture( t, w, format ), m_area( area ), m_filename( filename ) {}

Sprite::Sprite( const std::string& filename, lx::Win::Window& w,
                PixelFormat format )
    : Texture( filename, w, format ), m_area(), m_filename( filename ) {}

Sprite::Sprite( const std::string& filename, lx::Win::Window& w,
                const ImgRect& area, PixelFormat format )
    : Texture( filename, w, format ), m_area( area ),
      m_filename( filename ) {}

Sprite::Sprite( const UTF8string& filename, lx::Win::Window& w,
                PixelFormat format )
    : Texture( filename, w, format ), m_area(), m_filename( filename ) {}

Sprite::Sprite( const UTF8string& filename, lx::Win::Window& w,
                const ImgRect& area, PixelFormat format )
    : Texture( filename, w, format ), m_area( area ),
      m_filename( filename ) {}


void Sprite::draw() noexcept
{
    const SDL_Rect SRC_RECT = sdl_rect_( m_area );
    const SDL_Rect * SRC_AREA = isNull_( SRC_RECT ) ? nullptr : &SRC_RECT;
    SDL_RenderCopy( render( _win.getRenderingSys_() ), _texture, SRC_AREA, nullptr );
}

void Sprite::draw( const ImgRect& box ) noexcept
{
    draw( box, 0.0 );
}


void Sprite::draw( const ImgRect& box, const double angle ) noexcept
{
    draw( box, angle, MirrorEffect::NONE );
}

void Sprite::draw( const ImgRect& box, const double angle, const MirrorEffect mirror ) noexcept
{
    const SDL_Rect SDL_RECT = sdl_rect_( box );
    const SDL_Rect SRC_RECT = sdl_rect_( m_area );
    const SDL_Rect * SRC_AREA = isNull_( SRC_RECT ) ? nullptr : &SRC_RECT;

    SDL_RenderCopyEx( render( _win.getRenderingSys_() ), _texture, SRC_AREA, &SDL_RECT,
                      ( -radianToDegree( angle ) ), nullptr, cast_( mirror ) );
}


UTF8string Sprite::getFileName() noexcept
{
    return m_filename;
}


/** AnimatedSprite */

// protected constructor
AnimatedSprite::AnimatedSprite( SDL_Texture * t, lx::Win::Window& w,
                                const std::vector<ImgRect>& coord,
                                const uint32_t delay, bool loop,
                                const UTF8string& filename, PixelFormat format )
    : Sprite( t, w, filename, RNULL, format ), M_COORDINATES( coord ),
      M_NBCOORDINATES( coord.size() ), m_timer(), m_delay( delay ),
      m_frame( 0 ), m_loop( loop ), m_drawable( true ) {}

// public constructor
AnimatedSprite::AnimatedSprite( const std::string& filename,
                                lx::Win::Window& w,
                                const std::vector<ImgRect>& coord,
                                const uint32_t delay, bool loop,
                                PixelFormat format )
    : AnimatedSprite( UTF8string( filename ), w, coord, delay, loop, format ) {}


AnimatedSprite::AnimatedSprite( const UTF8string& filename, lx::Win::Window& w,
                                const std::vector<ImgRect>& coord,
                                const uint32_t delay, bool loop,
                                PixelFormat format )
    : Sprite( filename, w, format ), M_COORDINATES( coord ),
      M_NBCOORDINATES( coord.size() ), m_timer(), m_delay( delay ),
      m_frame( 0 ), m_loop( loop ), m_drawable( true ) {}


void AnimatedSprite::draw( const ImgRect& box ) noexcept
{
    draw( box, 0.0 );
}

void AnimatedSprite::draw( const ImgRect& box, const double angle ) noexcept
{
    draw( box, angle, MirrorEffect::NONE );
}


void AnimatedSprite::draw( const ImgRect& box, const double angle, const MirrorEffect mirror ) noexcept
{
    if ( m_timer.isStopped() )
    {
        m_timer.start();
    }
    else if ( m_timer.getTicks() > m_delay )
    {
        if ( m_frame == M_NBCOORDINATES - 1 )
        {
            if ( m_loop )
                m_frame = 0;
            else
            {
                m_timer.pause();
                m_drawable = false;
            }
        }
        else
            m_frame += 1;

        // I need to restart the timer, so I can calculate the new delay
        // of the new frame.
        m_timer.lap();
    }

    if ( m_drawable )
    {
        const SDL_Rect SDL_RECT = sdl_rect_( box );
        const SDL_Rect COORD = sdl_rect_( M_COORDINATES[m_frame] );

        SDL_RenderCopyEx( render( _win.getRenderingSys_() ), _texture,
                          &COORD, &SDL_RECT, ( -radianToDegree( angle ) ),
                          nullptr, cast_( mirror ) );
    }
}


void AnimatedSprite::resetAnimation() noexcept
{
    m_timer.stop();
    m_timer.reset();
    m_drawable = true;
    m_frame = 0;
}


uint32_t AnimatedSprite::getFrameDelay() const noexcept
{
    return m_delay;
}

bool AnimatedSprite::isInfinitelyLooped() const noexcept
{
    return m_loop;
}


/** BufferedImage */

BufferedImage::BufferedImage( SDL_Surface * s, PixelFormat format )
    : BufferedImage( s, "", format ) {}


BufferedImage::BufferedImage( SDL_Surface * s, const std::string& filename,
                              PixelFormat format )
    : m_surface( s ), m_filename( filename )
{
    uint32_t tmpf = u32( format );

    if ( s->format->format != tmpf )
    {
        m_surface = SDL_ConvertSurfaceFormat( s, tmpf, 0 );
        SDL_FreeSurface( s );
    }
}


BufferedImage::BufferedImage( const std::string& filename, PixelFormat format )
    : m_surface( nullptr ), m_filename( filename )
{
    m_surface = loadSurface_( filename, format );

    if ( m_surface == nullptr )
        throw ImageException( "BufferedImage — Cannot load " + filename );
}


BufferedImage::BufferedImage( const UTF8string& filename, PixelFormat format )
    : BufferedImage( filename.utf8_sstring(), format ) {}


bool BufferedImage::retrieveColours_( const uint32_t pixel, Uint8& r, Uint8& g,
                                      Uint8& b, Uint8& a ) const noexcept
{
    const PixelFormat fmt = static_cast<PixelFormat>( m_surface->format->format );
    uint32_t tmp_r, tmp_g, tmp_b, tmp_a;

    switch ( fmt )
    {
    case PixelFormat::RGBA8888:
        tmp_r = ( pixel >> 24 ) & 0xFF;
        tmp_g = ( pixel >> 16 ) & 0xFF;
        tmp_b = ( pixel >> 8 ) & 0xFF;
        tmp_a = pixel & 0xFF;
        break;

    case PixelFormat::ARGB8888:
        tmp_a = ( pixel >> 24 ) & 0xFF;
        tmp_r = ( pixel >> 16 ) & 0xFF;
        tmp_g = ( pixel >> 8 ) & 0xFF;
        tmp_b = pixel & 0xFF;
        break;

    case PixelFormat::BGRA8888:
        tmp_b = ( pixel >> 24 ) & 0xFF;
        tmp_g = ( pixel >> 16 ) & 0xFF;
        tmp_r = ( pixel >> 8 ) & 0xFF;
        tmp_a = pixel & 0xFF;
        break;

    case PixelFormat::ABGR8888:
        tmp_a = ( pixel >> 24 ) & 0xFF;
        tmp_b = ( pixel >> 16 ) & 0xFF;
        tmp_g = ( pixel >> 8 ) & 0xFF;
        tmp_r = pixel & 0xFF;
        break;

    case PixelFormat::RGBA4444:
        tmp_r = ( pixel >> 12 ) & 0xFF;
        tmp_g = ( pixel >> 8 ) & 0xFF;
        tmp_b = ( pixel >> 4 ) & 0xFF;
        tmp_a = pixel & 0xFF;
        break;

    case PixelFormat::ARGB4444:
        tmp_a = ( pixel >> 12 ) & 0xFF;
        tmp_r = ( pixel >> 8 ) & 0xFF;
        tmp_g = ( pixel >> 4 ) & 0xFF;
        tmp_b = pixel & 0xFF;
        break;

    case PixelFormat::BGRA4444:
        tmp_b = ( pixel >> 12 ) & 0xFF;
        tmp_g = ( pixel >> 8 ) & 0xFF;
        tmp_r = ( pixel >> 4 ) & 0xFF;
        tmp_a = pixel & 0xFF;
        break;

    case PixelFormat::ABGR4444:
        tmp_a = ( pixel >> 12 ) & 0xFF;
        tmp_b = ( pixel >> 8 ) & 0xFF;
        tmp_g = ( pixel >> 4 ) & 0xFF;
        tmp_r = pixel & 0xFF;
        break;

    case PixelFormat::RGB24:
    case PixelFormat::RGB888:
        tmp_r = ( pixel >> 16 ) & 0xFF;
        tmp_g = ( pixel >> 8 ) & 0xFF;
        tmp_b = pixel & 0xFF;
        break;

    case PixelFormat::BGR24:
    case PixelFormat::BGR888:
        tmp_b = ( pixel >> 12 ) & 0xFF;
        tmp_g = ( pixel >> 8 ) & 0xFF;
        tmp_r = ( pixel >> 4 ) & 0xFF;
        break;

    default:
        return false;
        break;
    }

    r = static_cast<uint8_t>( tmp_r );
    g = static_cast<uint8_t>( tmp_g );
    b = static_cast<uint8_t>( tmp_b );
    a = static_cast<uint8_t>( tmp_a );
    return true;
}


uint32_t BufferedImage::updateGrayscaleColour_( const Uint8 alpha, const Uint8 v ) const noexcept
{
    uint32_t npixel = 0;
    PixelFormat fmt = static_cast<PixelFormat>( m_surface->format->format );

    switch ( fmt )
    {
    case PixelFormat::RGBA8888:
        npixel = static_cast<uint32_t>( ( v << 24 ) | ( v << 16 ) | ( v << 8 ) | alpha );
        break;

    case PixelFormat::ARGB8888:
        npixel = static_cast<uint32_t>( ( alpha << 24 ) | ( v << 16 ) | ( v << 8 ) | v );
        break;

    case PixelFormat::BGRA8888:
        npixel = static_cast<uint32_t>( ( v << 24 ) | ( v << 16 ) | ( v << 8 ) | alpha );
        break;

    case PixelFormat::ABGR8888:
        npixel = static_cast<uint32_t>( ( alpha << 24 ) | ( v << 16 ) | ( v << 8 ) | v );
        break;

    case PixelFormat::RGBA4444:
        npixel = static_cast<uint32_t>( ( v << 12 ) | ( v << 8 ) | ( v << 4 ) | alpha );
        break;

    case PixelFormat::ARGB4444:
        npixel = static_cast<uint32_t>( ( alpha << 12 ) | ( v << 8 ) | ( v << 4 ) | v );
        break;

    case PixelFormat::BGRA4444:
        npixel = static_cast<uint32_t>( ( v << 12 ) | ( v << 8 ) | ( v << 4 ) | alpha );
        break;

    case PixelFormat::ABGR4444:
        npixel = static_cast<uint32_t>( ( alpha << 12 ) | ( v << 8 ) | ( v << 4 ) | v );
        break;

    case PixelFormat::BGR24:
    case PixelFormat::RGB24:
    case PixelFormat::BGR888:
    case PixelFormat::RGB888:
        npixel = static_cast<uint32_t>( ( v << 16 ) | ( v << 8 ) | v );
        break;

    default:
        break;
    }

    return npixel;
}


uint32_t BufferedImage::convertGrayscalePixel_( const uint32_t pixel ) const noexcept
{
    const float RED_RATIO   = 0.212671f;
    const float GREEN_RATIO = 0.715160f;
    const float BLUE_RATIO  = 0.072169f;

    Uint8 red = 0, green = 0, blue = 0, alpha = 0;

    if ( !retrieveColours_( pixel, red, green, blue, alpha ) )
    {
        lx::Log::logCritical( lx::Log::VIDEO, "convert image: Unrecognized format" );
        return pixel;
    }

    const float R = static_cast<float>( red );
    const float G = static_cast<float>( green );
    const float B = static_cast<float>( blue );

    const Uint8 V = static_cast<Uint8>( RED_RATIO * R + GREEN_RATIO * G + BLUE_RATIO * B );
    return updateGrayscaleColour_( alpha, V );
}


uint32_t
BufferedImage::updateNegativeColour_( const Uint8 r, const Uint8 g,
                                      const Uint8 b, const Uint8 a ) const noexcept
{
    uint32_t npixel = 0;
    PixelFormat fmt = static_cast<PixelFormat>( m_surface->format->format );

    switch ( fmt )
    {
    case PixelFormat::RGBA8888:
        npixel = static_cast<uint32_t>( ( r << 24 ) | ( g << 16 ) | ( b << 8 ) | a );
        break;

    case PixelFormat::ARGB8888:
        npixel = static_cast<uint32_t>( ( a << 24 ) | ( r << 16 ) | ( g << 8 ) | b );
        break;

    case PixelFormat::BGRA8888:
        npixel = static_cast<uint32_t>( ( r << 24 ) | ( g << 16 ) | ( b << 8 ) | a );
        break;

    case PixelFormat::ABGR8888:
        npixel = static_cast<uint32_t>( ( a << 24 ) | ( r << 16 ) | ( g << 8 ) | b );
        break;

    case PixelFormat::RGBA4444:
        npixel = static_cast<uint32_t>( ( r << 12 ) | ( g << 8 ) | ( b << 4 ) | a );
        break;

    case PixelFormat::ARGB4444:
        npixel = static_cast<uint32_t>( ( a << 12 ) | ( r << 8 ) | ( g << 4 ) | b );
        break;

    case PixelFormat::BGRA4444:
        npixel = static_cast<uint32_t>( ( b << 12 ) | ( g << 8 ) | ( r << 4 ) | a );
        break;

    case PixelFormat::ABGR4444:
        npixel = static_cast<uint32_t>( ( a << 12 ) | ( r << 8 ) | ( g << 4 ) | b );
        break;

    case PixelFormat::BGR24:
    case PixelFormat::BGR888:
        npixel = static_cast<uint32_t>( ( b << 16 ) | ( g << 8 ) | r );
        break;

    case PixelFormat::RGB24:
    case PixelFormat::RGB888:
        npixel = static_cast<uint32_t>( ( r << 16 ) | ( g << 8 ) | b );
        break;

    default:
        break;
    }

    return npixel;
}


uint32_t BufferedImage::convertNegativePixel_( const uint32_t pixel ) const noexcept
{
    Uint8 red = 0, green = 0, blue = 0, alpha = 0;

    if ( !retrieveColours_( pixel, red, green, blue, alpha ) )
    {
        lx::Log::logCritical( lx::Log::VIDEO, "convert image: Unrecognized format" );
        return pixel;
    }

    const Uint8 MAX_UINT = 255;
    const std::minus<Uint8> MINUS;
    const Uint8 R = MINUS( MAX_UINT, red );
    const Uint8 G = MINUS( MAX_UINT, green );
    const Uint8 B = MINUS( MAX_UINT, blue );

    return updateNegativeColour_( R, G, B, alpha );
}


BufferedImage& BufferedImage::convertGrayscale() noexcept
{
    const long NBPIXELS = m_surface->w * m_surface->h;
    uint32_t * pixels = static_cast<uint32_t *>( m_surface->pixels );

    for ( long i = 0; i < NBPIXELS; ++i )
    {
        const uint32_t pixel = pixels[i];
        pixels[i] = convertGrayscalePixel_( pixel );
    }

    return *this;
}

BufferedImage& BufferedImage::convertNegative() noexcept
{
    const long NBPIXELS = m_surface->w * m_surface->h;
    uint32_t * pixels = static_cast<uint32_t *>( m_surface->pixels );

    for ( long i = 0; i < NBPIXELS; ++i )
    {
        const uint32_t pixel = pixels[i];
        pixels[i] = convertNegativePixel_( pixel );
    }

    return *this;
}

Sprite * BufferedImage::generateSprite( lx::Win::Window& w, const ImgRect& area ) const
{
    return new Sprite( SDL_CreateTextureFromSurface( render( w.getRenderingSys_() ),
                       m_surface ), w, m_filename, area );
}

AnimatedSprite * BufferedImage::
generateAnimatedSprite( lx::Win::Window& w, const std::vector<ImgRect>& coord,
                        const uint32_t delay, bool loop ) const
{
    return new AnimatedSprite( SDL_CreateTextureFromSurface( render( w.getRenderingSys_() ), m_surface ),
                               w, coord, delay, loop, m_filename );
}


UTF8string BufferedImage::getFileName() noexcept
{
    return m_filename;
}


BufferedImage::~BufferedImage()
{
    SDL_FreeSurface( m_surface );
}



/** StreamingTexture */

StreamingTexture::StreamingTexture( lx::Win::Window& w, PixelFormat format )
    : Texture( w, format ), m_screen( nullptr ), m_update( false )
{
    int bpp, width, height;
    uint32_t r, g, b, a;

    if ( SDL_PixelFormatEnumToMasks( u32( _format ), &bpp, &r, &g, &b, &a ) != SDL_TRUE )
    {
        SDL_PixelFormatEnumToMasks( SDL_PIXELFORMAT_RGBA8888, &bpp, &r, &g, &b, &a );
        _format = PixelFormat::RGBA8888;
    }

    lx::Win::WindowInfo info;
    _win.getInfo( info );

    if ( info.lw == 0 && info.lh == 0 )
    {
        width  = _win.getWidth();
        height = _win.getHeight();
    }
    else
    {
        width  = info.lw;
        height = info.lh;
    }

    if ( width <= 0 || height <= 0 )
        throw ImageException( "StreamingTexture - bad dimensions" );
    else
    {
        m_screen  = SDL_CreateRGBSurface( 0, width, height, bpp, r, g, b, a );
        _texture = SDL_CreateTexture( render( w.getRenderingSys_() ), u32( _format ),
                                      SDL_TEXTUREACCESS_STREAMING, width, height );
    }
}


bool StreamingTexture::blit( BufferedImage& s, const ImgRect& rect ) noexcept
{
    SDL_Rect SDL_RECT = sdl_rect_( rect );
    bool b = ( SDL_BlitScaled( s.m_surface, nullptr, m_screen, &SDL_RECT ) == 0 );

    if ( !m_update )
        m_update = b;

    return b;
}

void StreamingTexture::update() noexcept
{
    if ( m_update )
    {
        SDL_UpdateTexture( _texture, nullptr, m_screen->pixels, m_screen->pitch );
        SDL_FillRect( m_screen, nullptr, SDL_MapRGBA( m_screen->format, 0, 0, 0, 0 ) );
        m_update = false;
    }
}

void StreamingTexture::draw() noexcept
{
    SDL_RenderCopy( render( _win.getRenderingSys_() ), _texture, nullptr, nullptr );
}

StreamingTexture::~StreamingTexture()
{
    SDL_DestroyTexture( _texture );
    SDL_FreeSurface( m_screen );
}


/** TextTexture */

TextTexture::TextTexture( lx::TrueTypeFont::Font& font,
                          lx::Win::Window& w, PixelFormat format )
    : Texture( w, format ), _text( "" ), _font( font ), _size( 0 ), _colour( CNULL ),
      _dimension( RNULL )
{
    _colour = _font.getColour_();
    _size = _font.getSize_();
}


TextTexture::TextTexture( const std::string& text, lx::TrueTypeFont::Font& font,
                          lx::Win::Window& w, PixelFormat format )
    : TextTexture( UTF8string( text ), font.getSize_(), font, w, format ) {}


TextTexture::TextTexture( const UTF8string& text, lx::TrueTypeFont::Font& font,
                          lx::Win::Window& w, PixelFormat format )
    : TextTexture( text, font.getSize_(), font, w, format ) {}


TextTexture::TextTexture( const std::string& text, unsigned int sz,
                          lx::TrueTypeFont::Font& font,
                          lx::Win::Window& w, PixelFormat format )
    : TextTexture( UTF8string( text ), sz, font, w, format ) {}


TextTexture::TextTexture( const UTF8string& text, unsigned int sz,
                          lx::TrueTypeFont::Font& font,
                          lx::Win::Window& w, PixelFormat format )
    : Texture( w, format ), _text( text ), _font( font ), _size( sz ),
      _colour( _font.getColour_() ), _dimension( RNULL )
{
    _font.sizeOfText_( _text, _size, _dimension.w, _dimension.h );
}


void TextTexture::draw() noexcept
{
    draw( 0.0 );
}


void TextTexture::draw( const double angle ) noexcept
{
    draw( angle, MirrorEffect::NONE );
}


void TextTexture::draw( const double angle, const MirrorEffect mirror ) noexcept
{
    const SDL_Rect DIM = sdl_rect_( _dimension );
    SDL_RenderCopyEx( render( _win.getRenderingSys_() ), _texture, nullptr,
                      &DIM, ( -radianToDegree( angle ) ), nullptr,
                      cast_( mirror ) );
}

const UTF8string TextTexture::getText() const noexcept
{
    return _text;
}

unsigned int TextTexture::getTextSize() const noexcept
{
    return _size;
}

std::pair<int, int> TextTexture::getTextDimension() const noexcept
{
    return std::make_pair( _dimension.w, _dimension.h );
}

int TextTexture::getTextWidth() const noexcept
{
    return _dimension.w;
}

int TextTexture::getTextHeight() const noexcept
{
    return _dimension.h;
}

Colour TextTexture::getTextColour() const noexcept
{
    return _colour;
}

void TextTexture::setText( const std::string& text ) noexcept
{
    setText( text, _size );
}

void TextTexture::setText( const UTF8string& text ) noexcept
{
    setText( text, _size );
}


void TextTexture::setText( const std::string& text, unsigned int sz ) noexcept
{
    setText( UTF8string( text ), sz );
}


void TextTexture::setText( const UTF8string& text, unsigned int sz ) noexcept
{
    if ( text != _text || _size != sz )
    {
        _text = text;
        _size = sz;
        updateTexture_();
    }
}


void TextTexture::setPosition( int x, int y ) noexcept
{
    _dimension.p.x = x;
    _dimension.p.y = y;
}

void TextTexture::setPosition( const lx::Graphics::ImgCoord& pos ) noexcept
{
    _dimension.p = pos;
}

void TextTexture::setTextSize( unsigned int sz ) noexcept
{
    if ( _size != sz )
    {
        _size = sz;

        if ( !_text.utf8_empty() )
            updateTexture_();
    }
}


void TextTexture::setTextColour( const Colour& c ) noexcept
{
    if ( _colour != c )
    {
        _colour = c;

        if ( !_text.utf8_empty() )
            updateTexture_();
    }
}


TextTexture::~TextTexture() {}


/** SolidTextTexture */

SolidTextTexture::
SolidTextTexture( lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                  PixelFormat format )
    : TextTexture( font, w, format ) {}


SolidTextTexture::
SolidTextTexture( const std::string& text, lx::TrueTypeFont::Font& font,
                  lx::Win::Window& w, PixelFormat format )
    : SolidTextTexture( UTF8string( text ), font, w, format ) {}


SolidTextTexture::
SolidTextTexture( const UTF8string& text, lx::TrueTypeFont::Font& font,
                  lx::Win::Window& w, PixelFormat format )
    : SolidTextTexture( text, font.getSize_(), font, w, format ) {}


SolidTextTexture::
SolidTextTexture( const std::string& text, unsigned int sz,
                  lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                  PixelFormat format )
    : SolidTextTexture( UTF8string( text ), sz, font, w, format ) {}


SolidTextTexture::
SolidTextTexture( const UTF8string& text, unsigned int sz,
                  lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                  PixelFormat format )
    : TextTexture( text, sz, font, w, format )
{
    _texture = _font.drawSolidText_( _text, _size, _win );
    SDL_SetTextureAlphaMod( _texture, _colour.a );

    if ( _texture == nullptr )
        throw ImageException( "SolidTextTexture — Cannot create the texture " +
                              text.utf8_sstring() );
}


void SolidTextTexture::updateTexture_() noexcept
{
    const Colour tmp = _font.getColour_();

    if ( _texture != nullptr )
        SDL_DestroyTexture( _texture );

    _font.setColour_( _colour );
    _texture = _font.drawSolidText_( _text, _size, _win );

    /* Transparent colour */
    SDL_SetTextureAlphaMod( _texture, _colour.a );

    _font.sizeOfText_( _text, _size, _dimension.w, _dimension.h );
    _font.setColour_( tmp );
}


/** ShadedTextTexture */

ShadedTextTexture::
ShadedTextTexture( lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                   PixelFormat format )
    : TextTexture( font, w, format ), m_bgcolour( CNULL ) {}


ShadedTextTexture::
ShadedTextTexture( const std::string& text, lx::TrueTypeFont::Font& font,
                   const Colour& bg, lx::Win::Window& w, PixelFormat format )
    : ShadedTextTexture( UTF8string( text ), font, bg, w, format ) {}


ShadedTextTexture::
ShadedTextTexture( const UTF8string& text, lx::TrueTypeFont::Font& font,
                   const Colour& bg, lx::Win::Window& w, PixelFormat format )
    : ShadedTextTexture( text, font.getSize_(), font, bg, w, format ) {}


ShadedTextTexture::
ShadedTextTexture( const std::string& text, unsigned int sz,
                   lx::TrueTypeFont::Font& font, const Colour& bg,
                   lx::Win::Window& w, PixelFormat format )
    : ShadedTextTexture( UTF8string( text ), sz, font, bg, w, format ) {}


ShadedTextTexture::
ShadedTextTexture( const UTF8string& text, unsigned int sz,
                   lx::TrueTypeFont::Font& font, const Colour& bg,
                   lx::Win::Window& w, PixelFormat format )
    : TextTexture( text, sz, font, w, format ), m_bgcolour( bg )
{
    _texture = _font.drawShadedText_( _text, _size, m_bgcolour, _win );

    SDL_SetTextureAlphaMod( _texture, alpha_() );

    if ( _texture == nullptr )
        throw ImageException( "ShadedTextTexture — Cannot create the texture: " +
                              text.utf8_sstring() );
}

/*
    Set the alpha value as te measn of colour.a and bgcolour.a
*/
uint8_t ShadedTextTexture::alpha_()
{
    const std::divides<Uint8> DIV;
    return std::plus<Uint8>()( DIV( _colour.a, 2 ), DIV( m_bgcolour.a, 2 ) );
}


void ShadedTextTexture::updateTexture_() noexcept
{
    const Colour tmp = _font.getColour_();

    if ( _texture != nullptr )
        SDL_DestroyTexture( _texture );

    _font.setColour_( _colour );
    _texture = _font.drawShadedText_( _text, _size, m_bgcolour, _win );

    SDL_SetTextureAlphaMod( _texture, alpha_() );
    _font.sizeOfText_( _text, _size, _dimension.w, _dimension.h );
    _font.setColour_( tmp );
}


void ShadedTextTexture::setBgColour( const Colour& bg ) noexcept
{
    if ( m_bgcolour != bg )
    {
        m_bgcolour = bg;

        if ( !_text.utf8_empty() )
            updateTexture_();
    }
}


/** BlendedTextTexture */

BlendedTextTexture::
BlendedTextTexture( lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                    PixelFormat format )
    : TextTexture( font, w, format ) {}


BlendedTextTexture::
BlendedTextTexture( const std::string& text, lx::TrueTypeFont::Font& font,
                    lx::Win::Window& w, PixelFormat format )
    : BlendedTextTexture( UTF8string( text ), font, w, format ) {}


BlendedTextTexture::
BlendedTextTexture( const UTF8string& text, lx::TrueTypeFont::Font& font,
                    lx::Win::Window& w, PixelFormat format )
    : BlendedTextTexture( text, font.getSize_(), font, w, format ) {}


BlendedTextTexture::
BlendedTextTexture( const std::string& text, unsigned int sz,
                    lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                    PixelFormat format )
    : BlendedTextTexture( UTF8string( text ), sz, font, w, format ) {}


BlendedTextTexture::
BlendedTextTexture( const UTF8string& text, unsigned int sz,
                    lx::TrueTypeFont::Font& font, lx::Win::Window& w,
                    PixelFormat format )
    : TextTexture( text, sz, font, w, format )
{
    _texture = _font.drawBlendedText_( _text, _size, _win );
    SDL_SetTextureAlphaMod( _texture, _colour.a );

    if ( _texture == nullptr )
        throw ImageException( "BlendedTextTexture — Cannot create the texture: " +
                              text.utf8_sstring() );
}


void BlendedTextTexture::updateTexture_() noexcept
{
    const Colour tmp = _font.getColour_();

    if ( _texture != nullptr )
        SDL_DestroyTexture( _texture );

    _font.setColour_( _colour );
    _texture = _font.drawBlendedText_( _text, _size, _win );
    SDL_SetTextureAlphaMod( _texture, _colour.a );
    _font.sizeOfText_( _text, _size, _dimension.w, _dimension.h );
    _font.setColour_( tmp );
}

}   // Graphics

}   // lx
