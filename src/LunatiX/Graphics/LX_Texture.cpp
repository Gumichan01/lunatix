
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
*   @file LX_Texture.cpp
*   @brief The implementation of the image
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*
*/

#include <LunatiX/LX_Texture.hpp>
#include <LunatiX/LX_TrueTypeFont.hpp>
#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_Log.hpp>

#include <SDL2/SDL_image.h>

#include <functional>

//#define render(x) static_cast<SDL_Renderer*>(x)
#define U32(x) static_cast<uint32_t>(x)

namespace
{

constexpr double DEGREE_180 = 180.0;
const LX_Graphics::LX_ImgRect RNULL{{0, 0}, 0, 0};
const LX_Colour CNULL{0, 0, 0, 0};


inline constexpr SDL_Renderer * render(void * r)
{
    return static_cast<SDL_Renderer*>(r);
}

inline constexpr SDL_RendererFlip shortToFlip_(const LX_Graphics::LX_MIRROR& mirror) noexcept
{
    return static_cast<SDL_RendererFlip>(mirror);
}

inline constexpr double radianToDegree(const double angle) noexcept
{
    return angle * DEGREE_180 / M_PI;
}

// Load a image from a file
SDL_Surface * loadSurface_(const std::string& filename,
                           LX_Graphics::LX_PixelFormat& format) noexcept
{
    SDL_Surface *loaded = IMG_Load(filename.c_str());

    if(loaded == nullptr)
        return nullptr;

    SDL_Surface *optimized = SDL_ConvertSurfaceFormat(loaded, U32(format), 0);
    SDL_FreeSurface(loaded);
    return optimized;
}

// Load a texture from a file
SDL_Texture * loadTexture_(const std::string& filename,
                           LX_Graphics::LX_PixelFormat& format,
                           SDL_Renderer *r) noexcept
{
    SDL_Surface *tmp_s = loadSurface_(filename, format);

    if(tmp_s == nullptr)
        return nullptr;

    SDL_Texture *tmp_t = SDL_CreateTextureFromSurface(r, tmp_s);
    SDL_FreeSurface(tmp_s);
    return tmp_t;
}

inline constexpr SDL_Rect sdl_rect_(const LX_Graphics::LX_ImgRect& imgr)
{
    return SDL_Rect{imgr.p.x, imgr.p.y, imgr.w, imgr.h};
}

inline constexpr bool isNull_(const SDL_Rect& rect)
{
    return rect.x == 0 && rect.y == 0 && rect.w == 0 && rect.h == 0;
}

}

namespace LX_Graphics
{

LX_ImageException::LX_ImageException(std::string err) : _string_error(err) {}

LX_ImageException::LX_ImageException(const LX_ImageException& me)
    : _string_error(me._string_error) {}

const char * LX_ImageException::what() const noexcept
{
    return _string_error.c_str();
}


/** LX_Texture */

//  protected zero-argument constructor
LX_Texture::LX_Texture(LX_Win::LX_Window& w, LX_PixelFormat format)
    : _texture(nullptr), _win(w), _format(format) {}


LX_Texture::LX_Texture(SDL_Texture *t, LX_Win::LX_Window& w, LX_PixelFormat format)
    : _texture(t), _win(w), _format(format) {}


LX_Texture::LX_Texture(const std::string& filename, LX_Win::LX_Window& w,
                       LX_PixelFormat format)
    : _texture(nullptr), _win(w), _format(format)
{
    _texture = loadTexture_(filename, format, render(w.getRenderingSys()));

    if(_texture == nullptr)
        throw LX_ImageException("LX_Texture — Cannot load " + filename);
}


LX_Texture::LX_Texture(const UTF8string& filename, LX_Win::LX_Window& w,
                       LX_PixelFormat format)
    : LX_Texture(filename.utf8_sstring(), w, format) {}

bool LX_Texture::bind(float *iw, float *ih) noexcept
{
    return _win.glMakeCurrent() && SDL_GL_BindTexture(_texture, iw, ih) == 0;
}

bool LX_Texture::unbind() noexcept
{
    return SDL_GL_UnbindTexture(_texture) == 0;
}


LX_Win::LX_Window& LX_Texture::getWindow() const noexcept
{
    return _win;
}

LX_PixelFormat LX_Texture::getFormat() const noexcept
{
    return _format;
}


LX_Texture::~LX_Texture()
{
    if(_texture != nullptr)
        SDL_DestroyTexture(_texture);
}


/** LX_Sprite */

// protected constructor
LX_Sprite::LX_Sprite(SDL_Texture *t, LX_Win::LX_Window& w,
                     const UTF8string& filename,
                     const LX_ImgRect& img_rect, LX_PixelFormat format)
    : LX_Texture(t, w, format), _img_rect(img_rect), _filename(filename) {}

LX_Sprite::LX_Sprite(const std::string& filename, LX_Win::LX_Window& w,
                     LX_PixelFormat format)
    : LX_Texture(filename, w, format), _img_rect(), _filename(filename) {}

LX_Sprite::LX_Sprite(const std::string& filename, LX_Win::LX_Window& w,
                     const LX_ImgRect& img_rect, LX_PixelFormat format)
    : LX_Texture(filename, w, format), _img_rect(img_rect),
      _filename(filename) {}

LX_Sprite::LX_Sprite(const UTF8string& filename, LX_Win::LX_Window& w,
                     LX_PixelFormat format)
    : LX_Texture(filename, w, format), _img_rect(), _filename(filename) {}

LX_Sprite::LX_Sprite(const UTF8string& filename, LX_Win::LX_Window& w,
                     const LX_ImgRect& img_rect, LX_PixelFormat format)
    : LX_Texture(filename, w, format), _img_rect(img_rect),
      _filename(filename) {}


void LX_Sprite::draw() noexcept
{
    const SDL_Rect SDL_SRC = sdl_rect_(_img_rect);
    const SDL_Rect * SDL_SRCP = isNull_(SDL_SRC) ? nullptr : &SDL_SRC;
    SDL_RenderCopy(render(_win.getRenderingSys()), _texture, SDL_SRCP, nullptr);
}

void LX_Sprite::draw(const LX_ImgRect& box) noexcept
{
    draw(box, 0.0);
}


void LX_Sprite::draw(const LX_ImgRect& box, const double angle) noexcept
{
    draw(box, angle, LX_MIRROR::NONE);
}

void LX_Sprite::draw(const LX_ImgRect& box, const double angle, const LX_MIRROR mirror) noexcept
{
    const SDL_Rect SDL_RECT = sdl_rect_(box);
    const SDL_Rect SDL_SRC = sdl_rect_(_img_rect);
    const SDL_Rect * SDL_SRCP = isNull_(SDL_SRC) ? nullptr : &SDL_SRC;
    SDL_RenderCopyEx(render(_win.getRenderingSys()), _texture, SDL_SRCP, &SDL_RECT,
                     (-radianToDegree(angle)), nullptr, shortToFlip_(mirror));
}


UTF8string LX_Sprite::getFileName() noexcept
{
    return _filename;
}


/** LX_AnimatedSprite */

// protected constructor
LX_AnimatedSprite::LX_AnimatedSprite(SDL_Texture *t, LX_Win::LX_Window& w,
                                     const std::vector<LX_ImgRect>& coord,
                                     const uint32_t delay, bool loop,
                                     const UTF8string& filename, LX_PixelFormat format)
    : LX_Sprite(t, w, filename, LX_ImgRect{0,0,0,0}, format),
      _coordinates(coord), _SZ(coord.size()), _delay(delay), _btime(0),
      _frame(0), _started(false), _loop(loop), _drawable(true) {}

// public constructor
LX_AnimatedSprite::LX_AnimatedSprite(const std::string& filename,
                                     LX_Win::LX_Window& w,
                                     const std::vector<LX_ImgRect>& coord,
                                     const uint32_t delay, bool loop,
                                     LX_PixelFormat format)
    : LX_AnimatedSprite(UTF8string(filename), w, coord, delay, loop, format) {}


LX_AnimatedSprite::LX_AnimatedSprite(const UTF8string& filename, LX_Win::LX_Window& w,
                                     const std::vector<LX_ImgRect>& coord,
                                     const uint32_t delay, bool loop,
                                     LX_PixelFormat format)
    : LX_Sprite(filename, w, format), _coordinates(coord),
      _SZ(coord.size()), _delay(delay), _btime(0), _frame(0),
      _started(false), _loop(loop), _drawable(true) {}


void LX_AnimatedSprite::draw(const LX_ImgRect& box) noexcept
{
    draw(box, 0.0);
}

void LX_AnimatedSprite::draw(const LX_ImgRect& box, const double angle) noexcept
{
    draw(box, angle, LX_MIRROR::NONE);
}


void LX_AnimatedSprite::draw(const LX_ImgRect& box, const double angle, const LX_MIRROR mirror) noexcept
{
    if(!_started)
    {
        _started = true;
        _btime = SDL_GetTicks();
    }
    else if(SDL_GetTicks() - _btime > _delay)
    {
        _btime = SDL_GetTicks();

        if(_frame == _SZ - 1)
        {
            if(_loop)
                _frame = 0;
            else
                _drawable = false;
        }
        else
            _frame += 1;
    }

    if(_drawable)
    {
        const SDL_Rect SDL_RECT = sdl_rect_(box);
        const SDL_Rect COORD = sdl_rect_(_coordinates[_frame]);
        SDL_RenderCopyEx(render(_win.getRenderingSys()), _texture,
                         &COORD, &SDL_RECT, (-radianToDegree(angle)),
                         nullptr, shortToFlip_(mirror));
    }
}


void LX_AnimatedSprite::resetAnimation() noexcept
{
    _started = false;
    _drawable = true;
    _frame = 0;
}


uint32_t LX_AnimatedSprite::getFrameDelay() const noexcept
{
    return _delay;
}

bool LX_AnimatedSprite::isInfinitelyLooped() const noexcept
{
    return _loop;
}


/** LX_BufferedImage */

LX_BufferedImage::LX_BufferedImage(SDL_Surface * s, LX_PixelFormat format)
    : LX_BufferedImage(s, "", format) {}


LX_BufferedImage::LX_BufferedImage(SDL_Surface * s, const std::string& filename,
                                   LX_PixelFormat format)
    : _surface(s), _filename(filename)
{
    uint32_t tmpf = U32(format);

    if(s->format->format != tmpf)
    {
        _surface = SDL_ConvertSurfaceFormat(s, tmpf, 0);
        SDL_FreeSurface(s);
    }
}


LX_BufferedImage::LX_BufferedImage(const std::string& filename, LX_PixelFormat format)
    : _surface(nullptr), _filename(filename)
{
    _surface = loadSurface_(filename, format);

    if(_surface == nullptr)
        throw LX_ImageException("LX_BufferedImage — Cannot load " + filename);
}


LX_BufferedImage::LX_BufferedImage(const UTF8string& filename, LX_PixelFormat format)
    : LX_BufferedImage(filename.utf8_sstring(), format) {}


bool LX_BufferedImage::_retrieveColours(Uint32 pixel, Uint8& r, Uint8& g,
                                        Uint8& b, Uint8& a) const noexcept
{
    const LX_PixelFormat fmt = static_cast<LX_PixelFormat>(_surface->format->format);
    Uint32 tmp_r, tmp_g, tmp_b, tmp_a;

    switch(fmt)
    {
    case LX_PixelFormat::RGBA8888:
        tmp_r = (pixel >> 24) & 0xFF;
        tmp_g = (pixel >> 16) & 0xFF;
        tmp_b = (pixel >> 8) & 0xFF;
        tmp_a = pixel & 0xFF;
        break;

    case LX_PixelFormat::ARGB8888:
        tmp_a = (pixel >> 24) & 0xFF;
        tmp_r = (pixel >> 16) & 0xFF;
        tmp_g = (pixel >> 8) & 0xFF;
        tmp_b = pixel & 0xFF;
        break;

    case LX_PixelFormat::BGRA8888:
        tmp_b = (pixel >> 24) & 0xFF;
        tmp_g = (pixel >> 16) & 0xFF;
        tmp_r = (pixel >> 8) & 0xFF;
        tmp_a = pixel & 0xFF;
        break;

    case LX_PixelFormat::ABGR8888:
        tmp_a = (pixel >> 24) & 0xFF;
        tmp_b = (pixel >> 16) & 0xFF;
        tmp_g = (pixel >> 8) & 0xFF;
        tmp_r = pixel & 0xFF;
        break;

    case LX_PixelFormat::RGBA4444:
        tmp_r = (pixel >> 12) & 0xFF;
        tmp_g = (pixel >> 8) & 0xFF;
        tmp_b = (pixel >> 4) & 0xFF;
        tmp_a = pixel & 0xFF;
        break;

    case LX_PixelFormat::ARGB4444:
        tmp_a = (pixel >> 12) & 0xFF;
        tmp_r = (pixel >> 8) & 0xFF;
        tmp_g = (pixel >> 4) & 0xFF;
        tmp_b = pixel & 0xFF;
        break;

    case LX_PixelFormat::BGRA4444:
        tmp_b = (pixel >> 12) & 0xFF;
        tmp_g = (pixel >> 8) & 0xFF;
        tmp_r = (pixel >> 4) & 0xFF;
        tmp_a = pixel & 0xFF;
        break;

    case LX_PixelFormat::ABGR4444:
        tmp_a = (pixel >> 12) & 0xFF;
        tmp_b = (pixel >> 8) & 0xFF;
        tmp_g = (pixel >> 4) & 0xFF;
        tmp_r = pixel & 0xFF;
        break;

    case LX_PixelFormat::RGB24:
    case LX_PixelFormat::RGB888:
        tmp_r = (pixel >> 16) & 0xFF;
        tmp_g = (pixel >> 8) & 0xFF;
        tmp_b = pixel & 0xFF;
        break;

    case LX_PixelFormat::BGR24:
    case LX_PixelFormat::BGR888:
        tmp_b = (pixel >> 12) & 0xFF;
        tmp_g = (pixel >> 8) & 0xFF;
        tmp_r = (pixel >> 4) & 0xFF;
        break;

    default:
        return false;
        break;
    }

    r = static_cast<uint8_t>(tmp_r);
    g = static_cast<uint8_t>(tmp_g);
    b = static_cast<uint8_t>(tmp_b);
    a = static_cast<uint8_t>(tmp_a);
    return true;
}


Uint32 LX_BufferedImage::_updateGrayscaleColour(Uint8 a, Uint8 v) const noexcept
{
    Uint32 npixel = 0;
    LX_PixelFormat fmt = static_cast<LX_PixelFormat>(_surface->format->format);

    switch(fmt)
    {
    case LX_PixelFormat::RGBA8888:
        npixel = static_cast<Uint32>((v << 24) | (v << 16) | (v << 8) | a);
        break;

    case LX_PixelFormat::ARGB8888:
        npixel = static_cast<Uint32>((a << 24) | (v << 16) | (v << 8) | v);
        break;

    case LX_PixelFormat::BGRA8888:
        npixel = static_cast<Uint32>((v << 24) | (v << 16) | (v << 8) | a);
        break;

    case LX_PixelFormat::ABGR8888:
        npixel = static_cast<Uint32>((a << 24) | (v << 16) | (v << 8) | v);
        break;

    case LX_PixelFormat::RGBA4444:
        npixel = static_cast<Uint32>((v << 12) | (v << 8) | (v << 4) | a);
        break;

    case LX_PixelFormat::ARGB4444:
        npixel = static_cast<Uint32>((a << 12) | (v << 8) | (v << 4) | v);
        break;

    case LX_PixelFormat::BGRA4444:
        npixel = static_cast<Uint32>((v << 12) | (v << 8) | (v << 4) | a);
        break;

    case LX_PixelFormat::ABGR4444:
        npixel = static_cast<Uint32>((a << 12) | (v << 8) | (v << 4) | v);
        break;

    case LX_PixelFormat::BGR24:
    case LX_PixelFormat::RGB24:
    case LX_PixelFormat::BGR888:
    case LX_PixelFormat::RGB888:
        npixel = static_cast<Uint32>((v << 16) | (v << 8) | v);
        break;

    default:
        break;
    }

    return npixel;
}


Uint32 LX_BufferedImage::_convertGrayscalePixel(Uint32 pixel) const noexcept
{

#define FL(x) static_cast<float>(x)

    const float RED_RATIO   = 0.212671f;
    const float GREEN_RATIO = 0.715160f;
    const float BLUE_RATIO  = 0.072169f;

    Uint8 r = 0, g = 0, b = 0, a = 0;

    if(!_retrieveColours(pixel, r, g, b, a))
    {
        LX_Log::logCritical(LX_Log::VIDEO, "convert image: Unrecognized format");
        return pixel;
    }

    Uint8 v = static_cast<Uint8>(RED_RATIO * FL(r) + GREEN_RATIO * FL(g) + BLUE_RATIO * FL(b));
    return _updateGrayscaleColour(a, v);
}


Uint32 LX_BufferedImage::_updateNegativeColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const noexcept
{
    Uint32 npixel = 0;
    LX_PixelFormat fmt = static_cast<LX_PixelFormat>(_surface->format->format);

    switch(fmt)
    {
    case LX_PixelFormat::RGBA8888:
        npixel = static_cast<Uint32>((r << 24) | (g << 16) | (b << 8) | a);
        break;

    case LX_PixelFormat::ARGB8888:
        npixel = static_cast<Uint32>((a << 24) | (r << 16) | (g << 8) | b);
        break;

    case LX_PixelFormat::BGRA8888:
        npixel = static_cast<Uint32>((r << 24) | (g << 16) | (b << 8) | a);
        break;

    case LX_PixelFormat::ABGR8888:
        npixel = static_cast<Uint32>((a << 24) | (r << 16) | (g << 8) | b);
        break;

    case LX_PixelFormat::RGBA4444:
        npixel = static_cast<Uint32>((r << 12) | (g << 8) | (b << 4) | a);
        break;

    case LX_PixelFormat::ARGB4444:
        npixel = static_cast<Uint32>((a << 12) | (r << 8) | (g << 4) | b);
        break;

    case LX_PixelFormat::BGRA4444:
        npixel = static_cast<Uint32>((b << 12) | (g << 8) | (r << 4) | a);
        break;

    case LX_PixelFormat::ABGR4444:
        npixel = static_cast<Uint32>((a << 12) | (r << 8) | (g << 4) | b);
        break;

    case LX_PixelFormat::BGR24:
    case LX_PixelFormat::BGR888:
        npixel = static_cast<Uint32>((b << 16) | (g << 8) | r);
        break;

    case LX_PixelFormat::RGB24:
    case LX_PixelFormat::RGB888:
        npixel = static_cast<Uint32>((r << 16) | (g << 8) | b);
        break;

    default:
        break;
    }

    return npixel;
}


Uint32 LX_BufferedImage::_convertNegativePixel(Uint32 pixel) const noexcept
{
    const Uint8 MAX_UINT = 255;
    Uint8 r = 0, g = 0, b = 0, a = 0;

    if(!_retrieveColours(pixel, r, g, b, a))
    {
        LX_Log::logCritical(LX_Log::VIDEO, "convert image: Unrecognized format");
        return pixel;
    }

    const std::minus<Uint8> MINUS;
    r = MINUS(MAX_UINT, r);
    g = MINUS(MAX_UINT, g);
    b = MINUS(MAX_UINT, b);

    return _updateNegativeColour(r, g, b, a);
}


LX_BufferedImage& LX_BufferedImage::convertGrayscale() noexcept
{
    const long NBPIXELS = _surface->w * _surface->h;
    Uint32 * pixels = static_cast<Uint32*>(_surface->pixels);

    for (long i = 0; i < NBPIXELS; ++i)
    {
        Uint32 pixel = pixels[i];
        pixels[i] = _convertGrayscalePixel(pixel);
    }

    return *this;
}

LX_BufferedImage& LX_BufferedImage::convertNegative() noexcept
{
    const long NBPIXELS = _surface->w * _surface->h;
    Uint32 * pixels = static_cast<Uint32*>(_surface->pixels);

    for (long i = 0; i < NBPIXELS; ++i)
    {
        Uint32 pixel = pixels[i];
        pixels[i] = _convertNegativePixel(pixel);
    }

    return *this;
}

LX_Sprite * LX_BufferedImage::generateSprite(LX_Win::LX_Window& w, const LX_ImgRect& area) const
{
    return new LX_Sprite(SDL_CreateTextureFromSurface(render(w.getRenderingSys()),
                         _surface), w, _filename, area);
}

LX_AnimatedSprite * LX_BufferedImage::
generateAnimatedSprite(LX_Win::LX_Window& w, const std::vector<LX_ImgRect>& coord,
                       const uint32_t delay, bool loop) const
{
    return new LX_AnimatedSprite(SDL_CreateTextureFromSurface(render(w.getRenderingSys()), _surface),
                                 w, coord, delay, loop, _filename);
}


UTF8string LX_BufferedImage::getFileName() noexcept
{
    return _filename;
}


LX_BufferedImage::~LX_BufferedImage()
{
    SDL_FreeSurface(_surface);
}



/** LX_StreamingTexture */

LX_StreamingTexture::LX_StreamingTexture(LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_Texture(w,format), _screen(nullptr), _update(false)
{
    int bpp, width, height;
    uint32_t r, g, b, a;

    if(SDL_PixelFormatEnumToMasks(U32(_format), &bpp, &r, &g, &b, &a) != SDL_TRUE)
    {
        SDL_PixelFormatEnumToMasks(SDL_PIXELFORMAT_RGBA8888, &bpp, &r, &g, &b, &a);
        _format = LX_PixelFormat::RGBA8888;
    }

    LX_Win::LX_WindowInfo info;
    _win.getInfo(info);

    if(info.lw == 0 && info.lh == 0)
    {
        width  = _win.getWidth();
        height = _win.getHeight();
    }
    else
    {
        width  = info.lw;
        height = info.lh;
    }

    if(width <= 0 || height <= 0)
        throw LX_ImageException("LX_StreamingTexture - bad dimensions");
    else
    {
        _screen  = SDL_CreateRGBSurface(0, width, height, bpp, r, g, b, a);
        _texture = SDL_CreateTexture(render(w.getRenderingSys()), U32(_format),
                                     SDL_TEXTUREACCESS_STREAMING, width, height);
    }
}


bool LX_StreamingTexture::blit(LX_BufferedImage& s, const LX_ImgRect& rect) noexcept
{
    SDL_Rect SDL_RECT = sdl_rect_(rect);
    bool b = (SDL_BlitScaled(s._surface, nullptr, _screen, &SDL_RECT) == 0);

    if(!_update)
        _update = b;

    return b;
}

void LX_StreamingTexture::update() noexcept
{
    if(_update)
    {
        SDL_UpdateTexture(_texture, nullptr, _screen->pixels, _screen->pitch);
        SDL_FillRect(_screen, nullptr, SDL_MapRGBA(_screen->format, 0, 0, 0, 0));
        _update = false;
    }
}

void LX_StreamingTexture::draw() noexcept
{
    SDL_RenderCopy(render(_win.getRenderingSys()), _texture, nullptr, nullptr);
}

LX_StreamingTexture::~LX_StreamingTexture()
{
    SDL_DestroyTexture(_texture);
    SDL_FreeSurface(_screen);
}


/** LX_TextTexture */

LX_TextTexture::LX_TextTexture(LX_TrueTypeFont::LX_Font& font,
                               LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_Texture(w, format), _text(""), _font(font), _size(0), _colour(CNULL),
      _dimension(RNULL)
{
    _colour = _font.getColour_();
    _size = _font.getSize_();
}


LX_TextTexture::LX_TextTexture(const std::string& text, LX_TrueTypeFont::LX_Font& font,
                               LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_TextTexture(UTF8string(text), font.getSize_(), font, w, format) {}


LX_TextTexture::LX_TextTexture(const UTF8string& text, LX_TrueTypeFont::LX_Font& font,
                               LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_TextTexture(text, font.getSize_(), font, w, format) {}


LX_TextTexture::LX_TextTexture(const std::string& text, unsigned int sz,
                               LX_TrueTypeFont::LX_Font& font,
                               LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_TextTexture(UTF8string(text), sz, font, w, format) {}


LX_TextTexture::LX_TextTexture(const UTF8string& text, unsigned int sz,
                               LX_TrueTypeFont::LX_Font& font,
                               LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_Texture(w, format), _text(text), _font(font), _size(sz),
      _colour(_font.getColour_()), _dimension(RNULL)
{
    _font.sizeOfText_(_text, _size, _dimension.w, _dimension.h);
}


void LX_TextTexture::draw() noexcept
{
    draw(0.0);
}


void LX_TextTexture::draw(const double angle) noexcept
{
    draw(angle, LX_MIRROR::NONE);
}


void LX_TextTexture::draw(const double angle, const LX_MIRROR mirror) noexcept
{
    const SDL_Rect DIM = sdl_rect_(_dimension);
    SDL_RenderCopyEx(render(_win.getRenderingSys()), _texture, nullptr,
                     &DIM, (-radianToDegree(angle)), nullptr,
                     shortToFlip_(mirror));
}

const UTF8string LX_TextTexture::getText() const noexcept
{
    return _text;
}

unsigned int LX_TextTexture::getTextSize() const noexcept
{
    return _size;
}

void LX_TextTexture::getTextDimension(int& w, int& h) const noexcept
{
    w = _dimension.w;
    h = _dimension.h;
}

std::pair<int, int> LX_TextTexture::getTextDimension() const noexcept
{
    return std::make_pair(_dimension.w, _dimension.h);
}

int LX_TextTexture::getTextWidth() const noexcept
{
    return _dimension.w;
}

int LX_TextTexture::getTextHeight() const noexcept
{
    return _dimension.h;
}

LX_Colour LX_TextTexture::getTextColour() const noexcept
{
    return _colour;
}

void LX_TextTexture::setText(const std::string& text) noexcept
{
    setText(text, _size);
}

void LX_TextTexture::setText(const UTF8string& text) noexcept
{
    setText(text, _size);
}


void LX_TextTexture::setText(const std::string& text, unsigned int sz) noexcept
{
    setText(UTF8string(text), sz);
}


void LX_TextTexture::setText(const UTF8string& text, unsigned int sz) noexcept
{
    if(text != _text || _size != sz)
    {
        _text = text;
        _size = sz;
        updateTexture_();
    }
}


void LX_TextTexture::setPosition(int x, int y) noexcept
{
    _dimension.p.x = x;
    _dimension.p.y = y;
}

void LX_TextTexture::setPosition(const LX_Graphics::LX_ImgCoord& pos) noexcept
{
    _dimension.p = pos;
}

void LX_TextTexture::setTextSize(unsigned int sz) noexcept
{
    if(_size != sz)
    {
        _size = sz;

        if(!_text.utf8_empty())
            updateTexture_();
    }
}


void LX_TextTexture::setTextColour(const LX_Colour& c) noexcept
{
    if(_colour != c)
    {
        _colour = c;

        if(!_text.utf8_empty())
            updateTexture_();
    }
}


LX_TextTexture::~LX_TextTexture() {}


/** LX_SolidTextTexture */

LX_SolidTextTexture::
LX_SolidTextTexture(LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                    LX_PixelFormat format)
    : LX_TextTexture(font, w, format) {}


LX_SolidTextTexture::
LX_SolidTextTexture(const std::string& text, LX_TrueTypeFont::LX_Font& font,
                    LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_SolidTextTexture(UTF8string(text), font, w, format) {}


LX_SolidTextTexture::
LX_SolidTextTexture(const UTF8string& text, LX_TrueTypeFont::LX_Font& font,
                    LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_SolidTextTexture(text, font.getSize_(), font, w, format) {}


LX_SolidTextTexture::
LX_SolidTextTexture(const std::string& text, unsigned int sz,
                    LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                    LX_PixelFormat format)
    : LX_SolidTextTexture(UTF8string(text), sz, font, w, format) {}


LX_SolidTextTexture::
LX_SolidTextTexture(const UTF8string& text, unsigned int sz,
                    LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                    LX_PixelFormat format)
    : LX_TextTexture(text, sz, font, w, format)
{
    _texture = _font.drawSolidText_(_text, _size, _win);
    SDL_SetTextureAlphaMod(_texture, _colour.a);

    if(_texture == nullptr)
        throw LX_ImageException("LX_SolidTextTexture — Cannot create the texture " +
                                text.utf8_sstring());
}


void LX_SolidTextTexture::updateTexture_() noexcept
{
    const LX_Colour tmp = _font.getColour_();

    if(_texture != nullptr)
        SDL_DestroyTexture(_texture);

    _font.setColour_(_colour);
    _texture = _font.drawSolidText_(_text, _size, _win);

    /* Transparent colour */
    SDL_SetTextureAlphaMod(_texture, _colour.a);

    _font.sizeOfText_(_text, _size, _dimension.w, _dimension.h);
    _font.setColour_(tmp);
}


/** LX_ShadedTextTexture */

LX_ShadedTextTexture::
LX_ShadedTextTexture(LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                     LX_PixelFormat format)
    : LX_TextTexture(font, w, format), _bgcolour(CNULL) {}


LX_ShadedTextTexture::
LX_ShadedTextTexture(const std::string& text, LX_TrueTypeFont::LX_Font& font,
                     const LX_Colour& bg, LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_ShadedTextTexture(UTF8string(text), font, bg, w, format) {}


LX_ShadedTextTexture::
LX_ShadedTextTexture(const UTF8string& text, LX_TrueTypeFont::LX_Font& font,
                     const LX_Colour& bg, LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_ShadedTextTexture(text, font.getSize_(), font, bg, w,format) {}


LX_ShadedTextTexture::
LX_ShadedTextTexture(const std::string& text, unsigned int sz,
                     LX_TrueTypeFont::LX_Font& font, const LX_Colour& bg,
                     LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_ShadedTextTexture(UTF8string(text), sz, font, bg, w, format) {}


LX_ShadedTextTexture::
LX_ShadedTextTexture(const UTF8string& text, unsigned int sz,
                     LX_TrueTypeFont::LX_Font& font, const LX_Colour& bg,
                     LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_TextTexture(text, sz, font, w, format), _bgcolour(bg)
{
    _texture = _font.drawShadedText_(_text, _size, _bgcolour, _win);
    SDL_SetTextureAlphaMod(_texture, (_colour.a / 2) + (_bgcolour.a / 2));

    if(_texture == nullptr)
        throw LX_ImageException("LX_ShadedTextTexture — Cannot create the texture: " +
                                text.utf8_sstring());
}


void LX_ShadedTextTexture::updateTexture_() noexcept
{
    const LX_Colour tmp = _font.getColour_();

    if(_texture != nullptr)
        SDL_DestroyTexture(_texture);

    _font.setColour_(_colour);
    _texture = _font.drawShadedText_(_text, _size, _bgcolour, _win);

    SDL_SetTextureAlphaMod(_texture, (_colour.a / 2) + (_bgcolour.a / 2));
    _font.sizeOfText_(_text, _size, _dimension.w, _dimension.h);
    _font.setColour_(tmp);
}


void LX_ShadedTextTexture::setBgColour(const LX_Colour& bg) noexcept
{
    if(_bgcolour != bg)
    {
        _bgcolour = bg;

        if(!_text.utf8_empty())
            updateTexture_();
    }
}


/** LX_BlendedTextTexture */

LX_BlendedTextTexture::
LX_BlendedTextTexture(LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                      LX_PixelFormat format)
    : LX_TextTexture(font, w, format) {}


LX_BlendedTextTexture::
LX_BlendedTextTexture(const std::string& text, LX_TrueTypeFont::LX_Font& font,
                      LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_BlendedTextTexture(UTF8string(text), font, w, format) {}


LX_BlendedTextTexture::
LX_BlendedTextTexture(const UTF8string& text, LX_TrueTypeFont::LX_Font& font,
                      LX_Win::LX_Window& w, LX_PixelFormat format)
    : LX_BlendedTextTexture(text, font.getSize_(), font, w, format) {}


LX_BlendedTextTexture::
LX_BlendedTextTexture(const std::string& text, unsigned int sz,
                      LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                      LX_PixelFormat format)
    : LX_BlendedTextTexture(UTF8string(text), sz, font, w, format) {}


LX_BlendedTextTexture::
LX_BlendedTextTexture(const UTF8string& text, unsigned int sz,
                      LX_TrueTypeFont::LX_Font& font, LX_Win::LX_Window& w,
                      LX_PixelFormat format)
    : LX_TextTexture(text, sz, font, w, format)
{
    _texture = _font.drawBlendedText_(_text, _size, _win);
    SDL_SetTextureAlphaMod(_texture, _colour.a);

    if(_texture == nullptr)
        throw LX_ImageException("LX_BlendedTextTexture — Cannot create the texture: " +
                                text.utf8_sstring());
}


void LX_BlendedTextTexture::updateTexture_() noexcept
{
    const LX_Colour tmp = _font.getColour_();

    if(_texture != nullptr)
        SDL_DestroyTexture(_texture);

    _font.setColour_(_colour);
    _texture = _font.drawBlendedText_(_text, _size, _win);
    SDL_SetTextureAlphaMod(_texture, _colour.a);
    _font.sizeOfText_(_text, _size, _dimension.w, _dimension.h);
    _font.setColour_(tmp);
}

}
