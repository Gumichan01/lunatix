

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_FileBuffer.cpp
*	@brief The file buffer implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <new>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <LunatiX/LX_FileIO.hpp>
#include <LunatiX/LX_FileBuffer.hpp>
#include <LunatiX/LX_Error.hpp>


namespace LX_FileIO
{

/**
*   @fn LX_FileBuffer::LX_FileBuffer(const char * filename)
*
*   Build the instance of the file buffer
*
*   @param filename The file to generate the buffer
*
*   @exception IOException If the filename is not defined
*
*/
LX_FileBuffer::LX_FileBuffer(const char * filename)
{
    LX_File *reader = NULL;
    std::string str("LX_FileBuffer : ");
    size_t r = 0;

    if(filename == NULL)
        throw IOException("LX_FileBuffer : invalid filename");

    buffer = NULL;
    bufsize = 0;
    name = filename;

    reader = new LX_File(filename,LX_FILEIO_RDONLY);
    reader->seek(0,LX_SEEK_END);

    {
        Sint64 n = reader->tell();

        if(n == -1)
            throw IOException(str + LX_GetError());

        bufsize = n;
    }

    reader->seek(0,LX_SEEK_SET);
    buffer = new (std::nothrow) char[bufsize];

    if(buffer == NULL)
    {
        delete reader;
        throw IOException(str + "not enough memory to store the file content");
    }

    r = reader->read(buffer,sizeof(char),bufsize);

    if(r < bufsize)
    {
        delete reader;
        throw IOException(str + "cannot read the file entirely");
    }

    reader->close();
    delete reader;
}


/**
*   @fn SDL_Surface * LX_FileBuffer::getSurfaceFromBuffer(void)
*
*   Try to load a surface from the memory
*
*   @return A valid surface if the memory refers to an image
*
*/
SDL_Surface * LX_FileBuffer::getSurfaceFromBuffer(void)
{
    SDL_RWops *rw = SDL_RWFromConstMem(buffer,bufsize);
    return (rw == NULL) ? NULL:IMG_Load_RW(rw,1);
}


/**
*   @fn TTF_Font * LX_FileBuffer::getFontFromBuffer(int size)
*
*   Try to load a TTF_Font from the memory
*
*   @return A valid font if the memory refers to a font
*
*/
TTF_Font * LX_FileBuffer::getFontFromBuffer(int size)
{
    SDL_RWops *rw = SDL_RWFromConstMem(buffer,bufsize);
    return (rw == NULL) ? NULL:TTF_OpenFontRW(rw,1,size);
}


/**
*   @fn Mix_Chunk * LX_FileBuffer::getChunkFromBuffer(void)
*
*   Try to load a sample from the memory
*
*   @return A valid sample if the memory refers to a Mix_Chunk
*
*/
Mix_Chunk * LX_FileBuffer::getChunkFromBuffer(void)
{
    SDL_RWops *rw = SDL_RWFromConstMem(buffer,bufsize);
    return (rw == NULL) ? NULL:Mix_LoadWAV_RW(rw,1);
}


/**
*   @fn const char * LX_FileBuffer::getFilename(void)
*
*   Get the name of the file the buffer refers to
*
*   @return The name of the file
*
*/
const char * LX_FileBuffer::getFilename(void)
{
    return name.c_str();
}


/**
*   @fn LX_FileBuffer::~LX_FileBuffer()
*
*   Destroy the file buffer
*
*/
LX_FileBuffer::~LX_FileBuffer()
{
    delete [] buffer;
}

};
