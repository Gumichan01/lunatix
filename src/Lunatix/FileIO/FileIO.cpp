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
*   @file FileIO.cpp
*   @brief The file handling implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/FileIO.hpp>
#include <Lunatix/Error.hpp>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rwops.h>

#include <cstring>
#include <cstdio>
#include <cerrno>

namespace lx
{

namespace FileIO
{

IOException::IOException( const std::string& err ) : _string_error( err ) {}

IOException::IOException( const IOException& io ) : _string_error( io._string_error ) {}

const char * IOException::what() const noexcept
{
    return _string_error.c_str();
}

IOException::~IOException() noexcept {}


/// File

/* Private implementation */

class File_ final
{
    UTF8string _name{""};
    std::FILE * m_file = nullptr;

    File_( const File_& ) = delete;
    File_& operator =( const File_& ) = delete;

    void open_( const FileMode mode )
    {
        switch ( mode )
        {
        case FileMode::RDONLY:
            m_file = std::fopen( _name.utf8_str(), "rb" );
            break;
        case FileMode::WRONLY:
            m_file = std::fopen( _name.utf8_str(), "wb" );
            break;
        case FileMode::APPEND:
            m_file = std::fopen( _name.utf8_str(), "ab" );
            break;
        case FileMode::RDWR:
            m_file = std::fopen( _name.utf8_str(), "rb+" );
            break;
        case FileMode::RDAP:
            m_file = std::fopen( _name.utf8_str(), "ab+" );
            break;
        case FileMode::WRTR:
            m_file = std::fopen( _name.utf8_str(), "wb+" );
            break;
        default:
            throw IOException( "File: Unrecognized mode" );
            break;
        }

        if ( m_file == nullptr )
            throw IOException( lx::getError() );
    }

public:

    File_( const UTF8string& filename, const FileMode mode )
        : _name( filename ), m_file( nullptr )
    {
        open_( mode );
    }

    size_t read( void * buffer, size_t dsize, size_t count ) noexcept
    {
        return std::fread( buffer, dsize, count, m_file );
    }

    size_t readExactly( void * buffer, size_t dsize, size_t count ) noexcept
    {
        size_t total_read = 0;
        char * p = static_cast<char *>( buffer );

        // Read at most count bytes
        while ( total_read < count )
        {
            size_t read_file = read( p, dsize, count );
            p += read_file;
            total_read += read_file;
        }

        return ( total_read != 0 && total_read != count ) ?
               static_cast<size_t>( -1 ) : total_read;
    }

    size_t write( const void * buffer, size_t dsize, size_t count ) noexcept
    {
        return std::fwrite( buffer, dsize, count, m_file );
    }

    size_t write( const std::string& str ) noexcept
    {
        size_t len = str.size();
        return write( reinterpret_cast<const void *>( str.c_str() ), sizeof( char ), len );
    }

    bool seek( long offset, FileWhence whence ) noexcept
    {
        return std::fseek( m_file, offset, static_cast<int>( whence ) ) == 0;
    }

    long tell() const noexcept
    {
        return std::ftell( m_file );
    }

    long size() noexcept
    {
        long fsize = -1L;
        long old_pos = tell();
        bool ok = seek( 0, FileWhence::END );

        if ( ok )
            fsize = tell();

        ok = seek( old_pos, FileWhence::SET );

        if ( !ok )
            return -1L;

        return fsize;
    }

    const char * getFilename() const noexcept
    {
        return  _name.utf8_str();
    }

    void close() noexcept
    {
        if ( m_file != nullptr )
        {
            std::fclose( m_file );
            m_file = nullptr;
        }
    }

    ~File_()
    {
        close();
    }
};


/* Public functions */

File::File( const std::string& filename, const FileMode mode )
    : File( UTF8string( filename ), mode ) {}

File::File( const UTF8string& filename, const FileMode mode )
    : m_fimpl( new File_( filename, mode ) ) {}


size_t File::read( void * buffer, size_t dsize, size_t count ) noexcept
{
    return m_fimpl->read( buffer, dsize, count );
}

size_t File::readExactly( void * buffer, size_t dsize, size_t count ) noexcept
{
    return m_fimpl->readExactly( buffer, dsize, count );
}


size_t File::write( const void * buffer, size_t dsize, size_t count ) noexcept
{
    return m_fimpl->write( buffer, dsize, count );
}

size_t File::write( const std::string& str ) noexcept
{
    return m_fimpl->write( str );
}

bool File::seek( long offset, FileWhence whence ) noexcept
{
    return m_fimpl->seek( offset, whence );
}

long File::tell() const noexcept
{
    return m_fimpl->tell();
}

long File::size() noexcept
{
    return m_fimpl->size();
}

const char * File::getFilename() const noexcept
{
    return m_fimpl->getFilename();
}

void File::close() noexcept
{
    m_fimpl->close();
}

File::~File()
{
    m_fimpl->close();
}


/// TmpFile

/* Private implementation */

class TmpFile_ final
{
    FILE * m_file = nullptr;

    TmpFile_( const TmpFile_& ) = delete;
    TmpFile_& operator =( const TmpFile_& ) = delete;

public:

    TmpFile_() : m_file( tmpfile() )
    {
        if ( m_file == nullptr )
            throw IOException( strerror( errno ) );
    }

    size_t read( void * buffer, size_t dsize, size_t count ) noexcept
    {
        size_t sz = std::fread( buffer, dsize, count, m_file );
        char * err = std::strerror( errno );

        if ( std::ferror( m_file ) )
            lx::setError( err );

        return sz;
    }

    size_t readExactly( void * buffer, size_t dsize, size_t count ) noexcept
    {
        const size_t FERR = static_cast<size_t>( -1 );
        size_t total_read = 0;
        uint8_t * p = static_cast<uint8_t *>( buffer );

        // Read at most count bytes
        while ( total_read < count )
        {
            size_t read_file = read( p, dsize, count - total_read );

            if ( read_file == FERR )
                return FERR;

            p += read_file;
            total_read += read_file;
        }

        return total_read != count ? FERR : total_read;
    }

    size_t write( const void * buffer, size_t dsize, size_t count ) noexcept
    {
        size_t sz = fwrite( buffer, dsize, count, m_file );
        char * err = strerror( errno );

        if ( ferror( m_file ) )
            lx::setError( err );

        return sz;
    }

    size_t write( const std::string& str ) noexcept
    {
        size_t len = str.size();
        return write( reinterpret_cast<const void *>( str.c_str() ), sizeof( char ), len );
    }

    bool seek( long offset, FileWhence whence ) noexcept
    {
        return std::fseek( m_file, offset, static_cast<int>( whence ) ) == 0;
    }

    long tell() const noexcept
    {
        return std::ftell( m_file );
    }

    ~TmpFile_()
    {
        fclose( m_file );
        m_file = nullptr;
    }
};


/* Public functions */

TmpFile::TmpFile(): m_timpl( new TmpFile_() ) {}


size_t TmpFile::read( void * buffer, size_t dsize, size_t count ) noexcept
{
    return m_timpl->read( buffer, dsize, count );
}

size_t TmpFile::readExactly( void * buffer, size_t dsize, size_t count ) noexcept
{
    return m_timpl->readExactly( buffer, dsize, count );
}


size_t TmpFile::write( const void * buffer, size_t dsize, size_t count ) noexcept
{
    return m_timpl->write( buffer, dsize, count );
}

size_t TmpFile::write( const std::string& str ) noexcept
{
    return m_timpl->write( str );
}


bool TmpFile::seek( long offset, FileWhence whence ) noexcept
{
    return m_timpl->seek( offset, whence );
}

long TmpFile::tell() const noexcept
{
    return m_timpl->tell();
}

TmpFile::~TmpFile()
{
    m_timpl.reset();
}

/// Stream
AbstractFile& operator <<( AbstractFile& f, const char s[] ) noexcept
{
    f.write( s, sizeof( char ), strlen( s ) );
    return f;
}

AbstractFile& operator <<( AbstractFile& f, const std::string& s ) noexcept
{
    f.write( s );
    return f;
}

AbstractFile& operator <<( AbstractFile& f, const UTF8string& u8s ) noexcept
{
    f.write( u8s.utf8_sstring() );
    return f;
}

}   // FileIO

}   // lx
