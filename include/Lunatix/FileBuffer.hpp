
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

#ifndef FILEBUFFER_HPP_INCLUDED
#define FILEBUFFER_HPP_INCLUDED

/**
*   @file FileBuffer.hpp
*   @brief The file buffer
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/Colour.hpp>
#include <Lunatix/Format.hpp>
#include <Lunatix/utils/utf8_string.hpp>
#include <memory>


namespace lx
{

namespace Graphics
{
class BufferedImage;
}

namespace Mixer
{
class Chunk;
}

namespace TrueTypeFont
{
struct Font_;
}


namespace FileIO
{

class FileBuffer_;

/**
*   @class FileBuffer
*   @brief The file buffer class
*
*   This class contains information about a file buffer.
*   It stores a memory copy of a file content into a buffer.
*/
class FileBuffer final
{
    friend struct lx::TrueTypeFont::Font_;
    std::unique_ptr<FileBuffer_> m_bimpl;

    FileBuffer( FileBuffer& fb );
    FileBuffer& operator =( FileBuffer& fb );

    // private function
    void * getFontFromBuffer_( int size ) const noexcept; // used by lx::TrueTypeFont::Font

public:

    /**
    *   @fn FileBuffer(const std::string& filename, size_t offset = 0, size_t sz = 0)
    *
    *   @param [in] filename The file to read
    *   @param [in] offset The position in the file to start reading (default value: 0)
    *   @param [in] sz The number of bytes to put in the buffer (default value: 0)
    *
    *   @note 1 — By default, the entire file is read from the beginning.
    *   @note 2 — If *sz* if 0, the file is read from *offset* to the end
    *
    *   @pre offset ≤ sz
    *
    *   @warning If the value of *offset* is greater than the size of the file,
    *           then an IOException will be thrown
    *
    *   @exception std::logic_error If the filename is not defined
    *   @exception IOException If the file cannot be read
    */
    FileBuffer( const std::string& filename, size_t offset = 0, size_t sz = 0 );
    /**
    *   @fn explicit FileBuffer(const UTF8string& filename, size_t offset = 0, size_t sz = 0)
    *
    *   @param [in] filename The file to read
    *   @param [in] offset The position in the file to start reading (default value: 0)
    *   @param [in] sz The number of bytes to put in the buffer (default value: 0)
    *
    *   @note 1 — By default, the entire file is read from the beginning.
    *   @note 2 — If *sz* if 0, the file is read from *offset* to the end
    *
    *   @pre offset ≤ sz
    *
    *   @warning If the value of *offset* is greater than the size of the file,
    *           then an IOException will be thrown
    *
    *   @exception std::logic_error If the filename is not defined
    *   @exception IOException If the file cannot be read by the instance
    *
    */
    explicit FileBuffer( const UTF8string& filename, size_t offset = 0, size_t sz = 0 );

    /**
    *   @fn lx::Graphics::BufferedImage * loadBufferedImage(lx::Graphics::PixelFormat format = lx::Graphics::PixelFormat::RGBA8888) const
    *
    *   @param [in] format Optional argument that specified the format of the image
    *
    *   @return A pointer to an allocated buffered image on success,
    *
    *   @exception lx::Graphics::ImageException if the buffered image cannot be created
    */
    lx::Graphics::BufferedImage * loadBufferedImage( lx::Graphics::PixelFormat format = lx::Graphics::PixelFormat::RGBA8888 ) const;
    /**
    *   @fn lx::Mixer::Chunk * loadSample() const
    *
    *   @return A pointer to an allocated Chunk object,
    *          *nullptr* if the file buffer is not a sample to load
    */
    lx::Mixer::Chunk * loadSample() const;

    /**
    *   @fn const char * getFilename() const
    *   @return The name of the file
    */
    const char * getFilename() const noexcept;

    ~FileBuffer();
};

}   // FileIO

}   // lx

#endif // FILEBUFFER_HPP_INCLUDED
