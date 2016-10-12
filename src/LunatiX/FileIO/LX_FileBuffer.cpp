

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
#include <SDL2/SDL_ttf.h>
#include <new>

namespace LX_FileIO
{

/* LX_fileBuffer — private implementation */

class LX_FileBuffer_
{
    friend class LX_Graphics::LX_Image;
    friend class LX_TrueTypeFont::LX_Font;
    UTF8string _name;                       /* The name of the file refered by the buffer */
    std::unique_ptr<int8_t[]> _buffer;      /* The read-only buffer                       */
    uint64_t _bufsize;                      /* The size of the buffer                     */

    Mix_Chunk * getChunkFromBuffer_() const
    {
        SDL_RWops *rw = SDL_RWFromConstMem(_buffer.get(),static_cast<int>(_bufsize));
        return (rw == nullptr) ? nullptr : Mix_LoadWAV_RW(rw,1);
    }

public:

    explicit LX_FileBuffer_(const UTF8string& filename) : _name(filename)
    {
        LX_File *reader = nullptr;
        std::string str("LX_FileBuffer: " + std::string(_name.utf8_str()) + " - ");
        size_t r = 0;
        int64_t s = 0;

        reader = new LX_File(_name,LX_FILEIO_RDONLY);
        reader->seek(0,LX_SEEK_END);

        if((s = reader->size()) == -1)
            throw IOException(str + "cannot get the size of the file");

        _bufsize = static_cast<uint64_t>(s);

        reader->seek(0,LX_SEEK_SET);
        _buffer.reset(new (std::nothrow) int8_t[_bufsize]);

        if(_buffer == nullptr)
        {
            delete reader;
            throw IOException(str + "not enough memory to store the file content");
        }

        r = reader->readExactly(_buffer.get(),sizeof(int8_t),_bufsize);

        if(r < _bufsize)
        {
            delete reader;
            throw IOException(str + "cannot read the entire file");
        }

        reader->close();
        delete reader;
    }

    LX_Mixer::LX_Chunk * loadSample() const
    {
        Mix_Chunk * ch = getChunkFromBuffer_();

        if(ch == nullptr)
            return nullptr;

        return new LX_Mixer::LX_Chunk(*ch);
    }

    inline SDL_Surface * getSurfaceFromBuffer() const
    {
        SDL_RWops *rw = SDL_RWFromConstMem(_buffer.get(), static_cast<int>(_bufsize));
        return (rw == nullptr) ? nullptr : IMG_Load_RW(rw,1);
    }

    inline TTF_Font * getFontFromBuffer(int size) const
    {
        SDL_RWops *rw = SDL_RWFromConstMem(_buffer.get(),static_cast<int>(_bufsize));
        return (rw == nullptr) ? nullptr : TTF_OpenFontRW(rw,1,size);
    }

    const char * getFilename() const
    {
        return _name.utf8_str();
    }

    ~LX_FileBuffer_()
    {
        _buffer.reset();
    }
};

/* LX_Filebuffer — public functions */

LX_FileBuffer::LX_FileBuffer(const std::string& filename)
    : LX_FileBuffer(UTF8string(filename)) {}


LX_FileBuffer::LX_FileBuffer(const UTF8string& filename)
    : _bimpl(new LX_FileBuffer_(filename)) {}


/* Private functions */
// Used by LX_Font
void * LX_FileBuffer::getSurfaceFromBuffer_() const
{
    return _bimpl->getSurfaceFromBuffer();
}

// Used by LX_Image and sub-classes
void * LX_FileBuffer::getFontFromBuffer_(int size) const
{
    return _bimpl->getFontFromBuffer(size);
}

/* Public functions */

LX_Mixer::LX_Chunk * LX_FileBuffer::loadSample() const
{
    return _bimpl->loadSample();
}


const char * LX_FileBuffer::getFilename() const
{
    return _bimpl->getFilename();
}


LX_FileBuffer::~LX_FileBuffer()
{
    _bimpl.reset();
}

};
