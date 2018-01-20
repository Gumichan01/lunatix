
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

#ifndef LX_FILEBUFFER_HPP_INCLUDED
#define LX_FILEBUFFER_HPP_INCLUDED

/**
*   @file LX_FileBuffer.hpp
*   @brief The file buffer
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <LunatiX/LX_Colour.hpp>
#include <LunatiX/LX_Format.hpp>
#include <memory>


namespace LX_Mixer
{
class LX_Chunk;
}

namespace LX_Graphics
{
class LX_BufferedImage;
}

namespace LX_TrueTypeFont
{
struct LX_Font_;
}

namespace LX_FileIO
{

class LX_FileBuffer_;

/**
*   @class LX_FileBuffer
*   @brief The file buffer class
*
*   This class contains information about a file buffer.
*   It stores a memory copy of a file content into a buffer.
*/
class LX_FileBuffer
{
    friend struct LX_TrueTypeFont::LX_Font_;
    std::unique_ptr<LX_FileBuffer_> _bimpl;

    LX_FileBuffer(LX_FileBuffer& fb);
    LX_FileBuffer& operator =(LX_FileBuffer& fb);

    // private function
    void * getFontFromBuffer_(int size) const noexcept;  // used by LX_TrueTypeFont::LX_Font

public:

    /**
    *   @fn LX_FileBuffer(const std::string filename, uint32_t offset = 0, uint32_t sz = 0)
    *
    *   @param [in] filename The file to read
    *   @param [in] offset The position in the file to start reading (default value: 0)
    *   @param [in] sz The number of bytes to put in the buffer (default value: 0)
    *
    *   @note 1 — By default, the entire file is read from the beginning.
    *   @note 2 — If *sz* if 0, the file is read from *offset* to the end
    *
    *   @warning If the value of *offset* is greater than the size of the file,
    *           then an IOException will be thrown
    *
    *   @exception std::logic_error If the filename is not defined
    *   @exception IOException If the file cannot be read by the instance
    */
    LX_FileBuffer(const std::string filename, uint32_t offset = 0, uint32_t sz = 0);
    /**
    *   @fn explicit LX_FileBuffer(const UTF8string filename, uint32_t offset = 0, uint32_t sz = 0)
    *
    *   @param [in] filename The file to read
    *   @param [in] offset The position in the file to start reading (default value: 0)
    *   @param [in] sz The number of bytes to put in the buffer (default value: 0)
    *
    *   @note 1 — By default, the entire file is read from the beginning.
    *   @note 2 — If *sz* if 0, the file is read from *offset* to the end
    *
    *   @warning If the value of *offset* is greater than the size of the file,
    *           then an IOException will be thrown
    *
    *   @exception std::logic_error If the filename is not defined
    *   @exception IOException If the file cannot be read by the instance
    *
    */
    explicit LX_FileBuffer(const UTF8string filename, uint32_t offset = 0, uint32_t sz = 0);

    /**
    *   @fn LX_Graphics::
    *       LX_BufferedImage * loadBufferedImage(LX_Graphics::LX_PIXELFORMAT format = LX_Graphics::LX_PIXELFORMAT::RGBA8888) const
    *
    *   Load a buffered image from the file buffer.
    *
    *   @param [in] format Optional argument that specified the format of the image
    *
    *   @return A pointer to new an allocated buffered image on success,
    *
    *   @exception LX_Graphics::LX_ImageException if the buffered image cannot be created
    */
    LX_Graphics::LX_BufferedImage * loadBufferedImage(LX_Graphics::LX_PIXELFORMAT format = LX_Graphics::LX_PIXELFORMAT::RGBA8888) const;
    /**
    *   @fn LX_Mixer::LX_Chunk * loadSample() const
    *
    *   Load a sample from the current file buffer
    *
    *   @return A pointer to an allocated LX_Chunk object,
    *          *nullptr* if the file buffer is not a sample to load
    */
    LX_Mixer::LX_Chunk * loadSample() const;

    /**
    *   @fn const char * getFilename() const
    *   Get the name of the file the buffer refers to
    *   @return The name of the file
    */
    const char * getFilename() const noexcept;

    /// Destructor
    ~LX_FileBuffer();
};

}

#endif // LX_FILEBUFFER_HPP_INCLUDED
