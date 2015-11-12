

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is an SDL2-based game engine.
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
*   @exception std::logic_error If the filename is not defined
*   @exception IOException If the file cannot be read by the instance
*
*/
LX_FileBuffer::LX_FileBuffer(const char * filename)
    : name(filename), buffer(nullptr), bufsize(0)
{
    LX_File *reader = nullptr;
    std::string str("LX_FileBuffer : ");
    size_t r = 0;
    Sint64 s = 0;

    reader = new LX_File(name.c_str(),LX_FILEIO_RDONLY);
    reader->seek(0,LX_SEEK_END);

    if((s = reader->size()) == -1 )
        throw IOException(str + "cannot get the size of the file");

    bufsize = static_cast<Uint64>(s);

    reader->seek(0,LX_SEEK_SET);
    buffer = new (std::nothrow) char[bufsize];

    if(buffer == nullptr)
    {
        delete reader;
        throw IOException(str + "not enough memory to store the file content");
    }

    r = reader->readExactly(buffer,sizeof(char),bufsize);

    if(r < bufsize)
    {
        delete reader;
        throw IOException(str + "cannot read the entire file");
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
    SDL_RWops *rw = SDL_RWFromConstMem(buffer, static_cast<int>(bufsize));
    return (rw == nullptr) ? nullptr:IMG_Load_RW(rw,1);
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
    SDL_RWops *rw = SDL_RWFromConstMem(buffer,static_cast<int>(bufsize));
    return (rw == nullptr) ? nullptr:TTF_OpenFontRW(rw,1,size);
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
    SDL_RWops *rw = SDL_RWFromConstMem(buffer,static_cast<int>(bufsize));
    return (rw == nullptr) ? nullptr:Mix_LoadWAV_RW(rw,1);
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
