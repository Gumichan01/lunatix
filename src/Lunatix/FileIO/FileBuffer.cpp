
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
*   @file FileBuffer.cpp
*   @brief The file buffer implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <Lunatix/FileBuffer.hpp>
#include <Lunatix/FileIO.hpp>
#include <Lunatix/Texture.hpp>
#include <Lunatix/Chunk.hpp>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <new>

namespace lx
{

namespace FileIO
{

/* fileBuffer — private implementation */

class FileBuffer_ final
{
    std::string _name;                      /* The name of the file refered by the buffer */
    std::unique_ptr<int8_t[]> m_buffer;     /* The read-only buffer                       */
    size_t m_bufsize;                       /* The size of the buffer                     */

    Mix_Chunk * getChunkFromBuffer_() const noexcept
    {
        SDL_RWops * rw = SDL_RWFromConstMem( m_buffer.get(), static_cast<int>( m_bufsize ) );
        return ( rw == nullptr ) ? nullptr : Mix_LoadWAV_RW( rw, 1 );
    }

public:

    explicit FileBuffer_( const std::string& filename, size_t offset, size_t sz )
        : _name( filename ), m_buffer( nullptr ), m_bufsize( 0U )
    {
        size_t r = 0;
        long fsize = 0L;
        const long LOFFSET = static_cast<long>( offset );
        std::string str( "FileBuffer: " + _name + " - " );
        File reader( _name, FileMode::RDONLY );

        if ( ( fsize = reader.size() ) == -1L )
            throw IOException( str + "cannot get the size of the file" );

        // If offset > size of the file → failure
        if ( LOFFSET > fsize )
            throw IOException( str + "invalid offset: offset > size of the file" );

        if ( sz == 0 )
            m_bufsize = static_cast<size_t>( fsize - LOFFSET );
        else
            m_bufsize = sz;

        reader.seek( LOFFSET, FileWhence::SET );
        m_buffer.reset( new ( std::nothrow ) int8_t[m_bufsize] );

        if ( m_buffer == nullptr )
            throw IOException( str + "not enough memory to store the file content" );

        r = reader.readExactly( m_buffer.get(), sizeof( int8_t ), m_bufsize );

        if ( r == static_cast<size_t>( -1 ) )
            throw IOException( str + "cannot read the entire file" );
    }


    lx::Mixer::Chunk * loadSample() const
    {
        Mix_Chunk * ch = getChunkFromBuffer_();

        if ( ch == nullptr )
            return nullptr;

        return new lx::Mixer::Chunk( *ch );
    }

    inline SDL_Surface * getSurfaceFromBuffer() const noexcept
    {
        SDL_RWops * rw = SDL_RWFromConstMem( m_buffer.get(), static_cast<int>( m_bufsize ) );
        return ( rw == nullptr ) ? nullptr : IMG_Load_RW( rw, 1 );
    }

    inline TTF_Font * getFontFromBuffer( int size ) const noexcept
    {
        SDL_RWops * rw = SDL_RWFromConstMem( m_buffer.get(), static_cast<int>( m_bufsize ) );
        return ( rw == nullptr ) ? nullptr : TTF_OpenFontRW( rw, 1, size );
    }

    const char * getFilename() const noexcept
    {
        return _name.c_str();
    }

    ~FileBuffer_() = default;
};


// Used by Font
void * FileBuffer::getFontFromBuffer_( int size ) const noexcept
{
    return m_bimpl->getFontFromBuffer( size );
}


/** Filebuffer — public functions */
FileBuffer::FileBuffer( const std::string& filename, size_t offset,
                        size_t sz )
    : m_bimpl( new FileBuffer_( filename, offset, sz ) ) {}

FileBuffer::FileBuffer( const UTF8string& filename, size_t offset,
                        size_t sz )
    : m_bimpl( new FileBuffer_( filename.utf8_sstring(), offset, sz ) ) {}


lx::Graphics::BufferedImage * FileBuffer::loadBufferedImage( lx::Graphics::PixelFormat format ) const
{
    return new lx::Graphics::BufferedImage( m_bimpl->getSurfaceFromBuffer(), getFilename(), format );
}


lx::Mixer::Chunk * FileBuffer::loadSample() const
{
    return m_bimpl->loadSample();
}


const char * FileBuffer::getFilename() const noexcept
{
    return m_bimpl->getFilename();
}

FileBuffer::~FileBuffer()
{
    m_bimpl.reset();
}

}   // FileIO

}   // lx
