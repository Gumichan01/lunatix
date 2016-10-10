#ifndef LX_FILEBUFFER_HPP_INCLUDED
#define LX_FILEBUFFER_HPP_INCLUDED


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
*    @file LX_FileBuffer.hpp
*    @brief The file buffer
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <SDL2/SDL_ttf.h>
#include <memory>

struct SDL_Surface;
struct Mix_Chunk;

namespace LX_Mixer
{
class LX_Chunk;
}

namespace LX_Graphics
{
class LX_Image;
}

namespace LX_TrueTypeFont
{
class LX_Font;
}

namespace LX_FileIO
{

class LX_File;
class IOException;

/// @todo (#1#) LX_FileBuffer - private implementation

/**
*   @class LX_FileBuffer
*   @brief The file buffer class
*
*   This structure contains information about a file buffer.
*   It stores a memory copy of a file content into a buffer.
*/
class LX_FileBuffer
{
    friend class LX_Graphics::LX_Image;
    friend class LX_TrueTypeFont::LX_Font;
    UTF8string _name;                   /* The name of the file refered by the buffer */
    std::unique_ptr<char[]> _buffer;    /* The read-only buffer                       */
    uint64_t _bufsize;                  /* The size of the buffer                     */

    LX_FileBuffer(LX_FileBuffer& fb);
    LX_FileBuffer& operator =(LX_FileBuffer& fb);

    Mix_Chunk * getChunkFromBuffer_() const;
    SDL_Surface * getSurfaceFromBuffer_() const;
    TTF_Font * getFontFromBuffer_(int size) const;

public :

    /**
    *   @fn LX_FileBuffer(const std::string& filename)
    *   @brief Constructor
    *
    *   Build the instance of the file buffer
    *
    *   @param [in] filename The file to generate the buffer
    *
    *   @exception std::logic_error If the filename is not defined
    *   @exception IOException If the file cannot be read by the instance
    *
    */
    LX_FileBuffer(const std::string& filename);
    /**
    *   @fn LX_FileBuffer(const UTF8string& filename)
    *   @brief Constructor
    *
    *   Build the instance of the file buffer
    *
    *   @param [in] filename The file to generate the buffer
    *
    *   @exception std::logic_error If the filename is not defined
    *   @exception IOException If the file cannot be read by the instance
    *
    */
    explicit LX_FileBuffer(const UTF8string& filename);

    /**
    *   @fn LX_Mixer::LX_Chunk * loadSample() const
    *
    *   Load a sample from the current file buffer
    *
    *   @return A pointer to an LX_Chunk object, nullptr if thhe fil buffer
    *           is not a sample to load
    */
    LX_Mixer::LX_Chunk * loadSample() const;

    /**
    *   @fn const char * getFilename() const
    *
    *   Get the name of the file the buffer refers to
    *
    *   @return The name of the file
    */
    const char * getFilename() const;

    /// Destructor
    ~LX_FileBuffer();
};

};

#endif // LX_FILEBUFFER_HPP_INCLUDED
