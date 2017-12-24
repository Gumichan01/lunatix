
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
*   @file LX_Chunk.cpp
*   @brief The chunk implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*
*/

#include <LunatiX/LX_Chunk.hpp>
#include <LunatiX/LX_FileBuffer.hpp>
#include <LunatiX/LX_Error.hpp>

#include <SDL2/SDL_mixer.h>

namespace LX_Mixer
{

/* LX_Chunk (private implementation) */

class LX_Chunk_
{
    Mix_Chunk *_chunk;

    void load_(const std::string& filename)
    {
        Mix_FreeChunk(_chunk);
        _chunk = Mix_LoadWAV(filename.c_str());

        if(_chunk == nullptr)
            throw LX_SoundException("LX_Chunk — Cannot load " + filename);
    }

public:

    explicit LX_Chunk_(Mix_Chunk& chunk): _chunk(&chunk) {}

    explicit LX_Chunk_(const std::string& filename) : _chunk(nullptr)
    {
        load_(filename);
    }

    explicit LX_Chunk_(const UTF8string filename) : _chunk(nullptr)
    {
        load_(filename.utf8_str());
    }

    bool play() noexcept
    {
        return play(-1);
    }

    bool play(int channel) noexcept
    {
        return play(channel, LX_MIXER_NOLOOP);
    }

    bool play(int channel, int loops) noexcept
    {
        return Mix_PlayChannel(channel,_chunk,loops) == 0;
    }

    bool play(int channel, int loops, int ticks) noexcept
    {
        return Mix_PlayChannelTimed(channel, _chunk, loops, ticks) == 0;
    }

    ~LX_Chunk_()
    {
        Mix_FreeChunk(_chunk);
    }
};

/* LX_Chunk */

// Private constructor used for internal uses
LX_Chunk::LX_Chunk(Mix_Chunk& chunk) : _chkimpl(new LX_Chunk_(chunk)) {}

// Public constructors
LX_Chunk::LX_Chunk(const std::string filename) : _chkimpl(new LX_Chunk_(filename)) {}

LX_Chunk::LX_Chunk(const UTF8string filename) : _chkimpl(new LX_Chunk_(filename)) {}


bool LX_Chunk::play() noexcept
{
    return _chkimpl->play();
}

bool LX_Chunk::play(int channel) noexcept
{
    return _chkimpl->play(channel, LX_MIXER_NOLOOP);
}

bool LX_Chunk::play(int channel, int loops) noexcept
{
    return _chkimpl->play(channel, loops);
}

bool LX_Chunk::play(int channel, int loops, int ticks) noexcept
{
    return _chkimpl->play(channel, loops, ticks);
}

LX_Chunk::~LX_Chunk()
{
    _chkimpl.reset();
}

}
