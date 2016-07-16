#ifndef LX_FILEBUFFER_HPP_INCLUDED
#define LX_FILEBUFFER_HPP_INCLUDED


/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_FileBuffer.hpp
*	@brief The file buffer
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>

struct SDL_Surface;
struct Mix_Chunk;


namespace LX_FileIO
{

class LX_File;
class IOException;

/**
*   @class LX_FileBuffer
*   @brief The file buffer class
*
*   This structure contains information about a file buffer.
*   It stores a memory copy of a file content into a buffer.
*/
class LX_FileBuffer
{
    UTF8string _name;        /* The name of the file the instance refers to  */
    char *_buffer;           /* The read-only buffer                         */
    Uint64 _bufsize;         /* The size of the buffer                       */

    LX_FileBuffer(LX_FileBuffer& fb);
    LX_FileBuffer& operator =(LX_FileBuffer& fb);

public :

    /**
    *   @fn LX_FileBuffer(const std::string filename)
    *
    *   Build the instance of the file buffer
    *
    *   @param filename The file to generate the buffer
    *
    *   @exception std::logic_error If the filename is not defined
    *   @exception IOException If the file cannot be read by the instance
    *
    */
    LX_FileBuffer(const std::string filename);

    /**
    *   @fn LX_FileBuffer(const UTF8string& filename)
    *
    *   Build the instance of the file buffer
    *
    *   @param filename The file to generate the buffer
    *
    *   @exception std::logic_error If the filename is not defined
    *   @exception IOException If the file cannot be read by the instance
    *
    */
    LX_FileBuffer(const UTF8string& filename);

    /**
    *   @fn SDL_Surface * getSurfaceFromBuffer(void)
    *
    *   Try to load a surface from the memory
    *
    *   @return A valid surface if the memory refers to an image
    *
    */
    SDL_Surface * getSurfaceFromBuffer(void);

    /**
    *   @fn TTF_Font * getFontFromBuffer(int size)
    *
    *   Try to load a TTF_Font from the memory
    *
    *   @param size The font size
    *
    *   @return A valid font if the memory refers to a font
    *
    */
    TTF_Font * getFontFromBuffer(int size);

    /**
    *   @fn Mix_Chunk * getChunkFromBuffer(void)
    *
    *   Try to load a sample from the memory
    *
    *   @return A valid sample if the memory refers to a Mix_Chunk
    *
    */
    Mix_Chunk * getChunkFromBuffer(void);

    /**
    *   @fn const char * getFilename(void)
    *
    *   Get the name of the file the buffer refers to
    *
    *   @return The name of the file
    *
    */
    const char * getFilename(void);

    /**
    *   @fn ~LX_FileBuffer()
    *
    *   Destroy the file buffer
    *
    */
    ~LX_FileBuffer();
};

};

#endif // LX_FILEBUFFER_HPP_INCLUDED
