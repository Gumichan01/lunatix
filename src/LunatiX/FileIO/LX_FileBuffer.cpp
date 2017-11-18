
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file LX_FileBuffer.cpp
*   @brief The file buffer implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*/

#include <LunatiX/LX_FileBuffer.hpp>
#include <LunatiX/LX_FileIO.hpp>
#include <LunatiX/LX_Texture.hpp>
#include <LunatiX/LX_Chunk.hpp>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <new>

#define U64(x) static_cast<uint64_t>(x)
#define S64(x) static_cast<int64_t>(x)


namespace LX_FileIO
{

/* LX_fileBuffer — private implementation */

class LX_FileBuffer_
{
    std::string _name;                      /* The name of the file refered by the buffer */
    std::unique_ptr<int8_t[]> _buffer;      /* The read-only buffer                       */
    uint64_t _bufsize;                      /* The size of the buffer                     */

    Mix_Chunk * getChunkFromBuffer_() const noexcept
    {
        SDL_RWops *rw = SDL_RWFromConstMem(_buffer.get(),static_cast<int>(_bufsize));
        return (rw == nullptr) ? nullptr : Mix_LoadWAV_RW(rw,1);
    }

public:

    explicit LX_FileBuffer_(const UTF8string filename, uint32_t offset, uint32_t sz)
        : LX_FileBuffer_(std::string(filename.utf8_str()), offset, sz) {}

    explicit LX_FileBuffer_(const std::string& filename, uint32_t offset, uint32_t sz)
        : _name(filename), _bufsize(0)
    {
        std::string str("LX_FileBuffer: " + _name + " - ");
        size_t r = 0;
        int64_t s = 0;

        LX_File reader(_name,LX_FILEIO_RDONLY);
        reader.seek(0,LX_SEEK_END);     // Is that useful ?

        if((s = reader.size()) == -1)
            throw IOException(str + "cannot get the size of the file");

        // If offset > size of the file → failure
        if(S64(offset) > s)
        {
            reader.close();
            throw IOException(str + "invalid offset: offset > size of the file");
        }

        if(sz == 0)
            _bufsize = U64(s) - U64(offset);
        else
            _bufsize = U64(sz);

        reader.seek(S64(offset),LX_SEEK_SET);
        _buffer.reset(new (std::nothrow) int8_t[_bufsize]);

        if(_buffer == nullptr)
            throw IOException(str + "not enough memory to store the file content");

        r = reader.readExactly(_buffer.get(),sizeof(int8_t),_bufsize);

        if(r < _bufsize)
            throw IOException(str + "cannot read the entire file");

        reader.close();
    }


    LX_Mixer::LX_Chunk * loadSample() const
    {
        Mix_Chunk * ch = getChunkFromBuffer_();

        if(ch == nullptr)
            return nullptr;

        return new LX_Mixer::LX_Chunk(*ch);
    }

    inline SDL_Surface * getSurfaceFromBuffer() const noexcept
    {
        SDL_RWops *rw = SDL_RWFromConstMem(_buffer.get(), static_cast<int>(_bufsize));
        return (rw == nullptr) ? nullptr : IMG_Load_RW(rw,1);
    }

    inline TTF_Font * getFontFromBuffer(int size) const noexcept
    {
        SDL_RWops *rw = SDL_RWFromConstMem(_buffer.get(),static_cast<int>(_bufsize));
        return (rw == nullptr) ? nullptr : TTF_OpenFontRW(rw,1,size);
    }

    const char * getFilename() const noexcept
    {
        return _name.c_str();
    }

    ~LX_FileBuffer_()
    {
        _buffer.reset();
    }
};


// Used by LX_Font
void * LX_FileBuffer::getFontFromBuffer_(int size) const noexcept
{
    return _bimpl->getFontFromBuffer(size);
}


/** LX_Filebuffer — public functions */
LX_FileBuffer::LX_FileBuffer(const std::string filename, uint32_t offset,
                             uint32_t sz)
    : _bimpl(new LX_FileBuffer_(filename, offset, sz)) {}

LX_FileBuffer::LX_FileBuffer(const UTF8string filename, uint32_t offset,
                             uint32_t sz)
    : _bimpl(new LX_FileBuffer_(filename, offset, sz)) {}


LX_Graphics::LX_BufferedImage * LX_FileBuffer::loadBufferedImage(uint32_t format) const
{
    return new LX_Graphics::LX_BufferedImage(_bimpl->getSurfaceFromBuffer(), getFilename(), format);
}


LX_Mixer::LX_Chunk * LX_FileBuffer::loadSample() const
{
    return _bimpl->loadSample();
}


const char * LX_FileBuffer::getFilename() const noexcept
{
    return _bimpl->getFilename();
}


LX_FileBuffer::~LX_FileBuffer()
{
    _bimpl.reset();
}

}
