
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
*   @file LX_FileBuffer.cpp
*   @brief The file buffer implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <LunatiX/FileBuffer.hpp>
#include <LunatiX/FileIO.hpp>
#include <LunatiX/Texture.hpp>
#include <LunatiX/Chunk.hpp>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <new>



namespace LX_FileIO
{

/* LX_fileBuffer — private implementation */

class LX_FileBuffer_ final
{
    std::string _name;                      /* The name of the file refered by the buffer */
    std::unique_ptr<int8_t[]> _buffer;      /* The read-only buffer                       */
    size_t _bufsize;                        /* The size of the buffer                     */

    Mix_Chunk * getChunkFromBuffer_() const noexcept
    {
        SDL_RWops * rw = SDL_RWFromConstMem( _buffer.get(), static_cast<int>( _bufsize ) );
        return ( rw == nullptr ) ? nullptr : Mix_LoadWAV_RW( rw, 1 );
    }

public:

    explicit LX_FileBuffer_( const std::string& filename, size_t offset, size_t sz )
        : _name( filename ), _buffer( nullptr ), _bufsize( 0 )
    {
        std::string str( "LX_FileBuffer: " + _name + " - " );
        size_t r = 0, fsize = 0;

        LX_File reader( _name, LX_FileMode::RDONLY );

        if ( ( fsize = reader.size() ) == static_cast<size_t>( -1 ) )
            throw IOException( str + "cannot get the size of the file" );

        // If offset > size of the file → failure
        if ( offset > fsize )
            throw IOException( str + "invalid offset: offset > size of the file" );

        if ( sz == 0 )
            _bufsize = fsize - offset;
        else
            _bufsize = sz;

        reader.seek( static_cast<long>( offset ), LX_FileWhence::SET );
        _buffer.reset( new ( std::nothrow ) int8_t[_bufsize] );

        if ( _buffer == nullptr )
            throw IOException( str + "not enough memory to store the file content" );

        r = reader.readExactly( _buffer.get(), sizeof( int8_t ), _bufsize );

        if ( r == static_cast<size_t>( -1 ) )
            throw IOException( str + "cannot read the entire file" );
    }


    LX_Mixer::LX_Chunk * loadSample() const
    {
        Mix_Chunk * ch = getChunkFromBuffer_();

        if ( ch == nullptr )
            return nullptr;

        return new LX_Mixer::LX_Chunk( *ch );
    }

    inline SDL_Surface * getSurfaceFromBuffer() const noexcept
    {
        SDL_RWops * rw = SDL_RWFromConstMem( _buffer.get(), static_cast<int>( _bufsize ) );
        return ( rw == nullptr ) ? nullptr : IMG_Load_RW( rw, 1 );
    }

    inline TTF_Font * getFontFromBuffer( int size ) const noexcept
    {
        SDL_RWops * rw = SDL_RWFromConstMem( _buffer.get(), static_cast<int>( _bufsize ) );
        return ( rw == nullptr ) ? nullptr : TTF_OpenFontRW( rw, 1, size );
    }

    const char * getFilename() const noexcept
    {
        return _name.c_str();
    }

    ~LX_FileBuffer_() = default;
};


// Used by LX_Font
void * LX_FileBuffer::getFontFromBuffer_( int size ) const noexcept
{
    return _bimpl->getFontFromBuffer( size );
}


/** LX_Filebuffer — public functions */
LX_FileBuffer::LX_FileBuffer( const std::string& filename, size_t offset,
                              size_t sz )
    : _bimpl( new LX_FileBuffer_( filename, offset, sz ) ) {}

LX_FileBuffer::LX_FileBuffer( const UTF8string& filename, size_t offset,
                              size_t sz )
    : _bimpl( new LX_FileBuffer_( filename.utf8_sstring(), offset, sz ) ) {}


LX_Graphics::LX_BufferedImage * LX_FileBuffer::loadBufferedImage( LX_Graphics::LX_PixelFormat format ) const
{
    return new LX_Graphics::LX_BufferedImage( _bimpl->getSurfaceFromBuffer(), getFilename(), format );
}


LX_Mixer::LX_Chunk * LX_FileBuffer::loadSample() const
{
    return _bimpl->loadSample();
}


const char * LX_FileBuffer::getFilename() const noexcept
{
    return _bimpl->getFilename();
}

LX_FileBuffer::~LX_FileBuffer()
{
    _bimpl.reset();
}

}
