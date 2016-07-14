

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
*	@file LX_FileBuffer.cpp
*	@brief The file buffer implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
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

LX_FileBuffer::LX_FileBuffer(const std::string filename)
    : name(filename), buffer(nullptr), bufsize(0)
{
    LX_File *reader = nullptr;
    std::string str("LX_FileBuffer: " + std::string(name.utf8_str()) + " - ");
    size_t r = 0;
    Sint64 s = 0;

    reader = new LX_File(name,LX_FILEIO_RDONLY);
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


SDL_Surface * LX_FileBuffer::getSurfaceFromBuffer(void)
{
    SDL_RWops *rw = SDL_RWFromConstMem(buffer, static_cast<int>(bufsize));
    return (rw == nullptr) ? nullptr:IMG_Load_RW(rw,1);
}


TTF_Font * LX_FileBuffer::getFontFromBuffer(int size)
{
    SDL_RWops *rw = SDL_RWFromConstMem(buffer,static_cast<int>(bufsize));
    return (rw == nullptr) ? nullptr:TTF_OpenFontRW(rw,1,size);
}


Mix_Chunk * LX_FileBuffer::getChunkFromBuffer(void)
{
    SDL_RWops *rw = SDL_RWFromConstMem(buffer,static_cast<int>(bufsize));
    return (rw == nullptr) ? nullptr:Mix_LoadWAV_RW(rw,1);
}


const char * LX_FileBuffer::getFilename(void)
{
    return name.utf8_str();
}


LX_FileBuffer::~LX_FileBuffer()
{
    delete [] buffer;
}

};
