

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
*    @file LX_FileBuffer.cpp
*    @brief The file buffer implementation
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/LX_FileIO.hpp>
#include <LunatiX/LX_FileBuffer.hpp>

#include <LunatiX/LX_Chunk.hpp>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <new>

namespace LX_FileIO
{

LX_FileBuffer::LX_FileBuffer(const std::string& filename)
    : LX_FileBuffer(UTF8string(filename)) {}


LX_FileBuffer::LX_FileBuffer(const UTF8string& filename)
    : _name(filename), _buffer(nullptr), _bufsize(0)
{
    LX_File *reader = nullptr;
    std::string str("LX_FileBuffer: " + std::string(_name.utf8_str()) + " - ");
    size_t r = 0;
    int64_t s = 0;

    reader = new LX_File(_name,LX_FILEIO_RDONLY);
    reader->seek(0,LX_SEEK_END);

    if((s = reader->size()) == -1 )
        throw IOException(str + "cannot get the size of the file");

    _bufsize = static_cast<uint64_t>(s);

    reader->seek(0,LX_SEEK_SET);
    _buffer = new (std::nothrow) char[_bufsize];

    if(_buffer == nullptr)
    {
        delete reader;
        throw IOException(str + "not enough memory to store the file content");
    }

    r = reader->readExactly(_buffer,sizeof(char),_bufsize);

    if(r < _bufsize)
    {
        delete reader;
        throw IOException(str + "cannot read the entire file");
    }

    reader->close();
    delete reader;
}

// Private function
SDL_Surface * LX_FileBuffer::getSurfaceFromBuffer_(void)
{
    SDL_RWops *rw = SDL_RWFromConstMem( _buffer, static_cast<int>(_bufsize));
    return (rw == nullptr) ? nullptr:IMG_Load_RW(rw,1);
}

// Private function
TTF_Font * LX_FileBuffer::getFontFromBuffer_(int size)
{
    SDL_RWops *rw = SDL_RWFromConstMem( _buffer,static_cast<int>(_bufsize));
    return (rw == nullptr) ? nullptr:TTF_OpenFontRW(rw,1,size);
}

// Private function
Mix_Chunk * LX_FileBuffer::getChunkFromBuffer_(void)
{
    SDL_RWops *rw = SDL_RWFromConstMem( _buffer,static_cast<int>(_bufsize));
    return (rw == nullptr) ? nullptr:Mix_LoadWAV_RW(rw,1);
}


LX_Mixer::LX_Chunk * LX_FileBuffer::loadSample()
{
    Mix_Chunk * ch = getChunkFromBuffer_();

    if(ch == nullptr)
        return nullptr;

    LX_Mixer::LX_Chunk *lxchunk = new LX_Mixer::LX_Chunk(*ch);
    return lxchunk;
}


const char * LX_FileBuffer::getFilename(void)
{
    return _name.utf8_str();
}


LX_FileBuffer::~LX_FileBuffer()
{
    delete [] _buffer;
}

};
