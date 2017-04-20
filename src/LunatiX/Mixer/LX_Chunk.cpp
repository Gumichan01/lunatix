
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
    bool _loaded;

public:

    explicit LX_Chunk_(Mix_Chunk& chunk): _chunk(&chunk), _loaded(true) {}

    explicit LX_Chunk_(const std::string& filename)
        : _chunk(nullptr), _loaded(false)
    {
        _loaded = load_(UTF8string(filename));
    }

    explicit LX_Chunk_(const UTF8string& filename)
        : _chunk(nullptr), _loaded(false)
    {
        _loaded = load_(filename);
    }


    bool load_(const UTF8string& filename)
    {
        Mix_FreeChunk(_chunk);
        _chunk = Mix_LoadWAV(filename.utf8_str());
        return _chunk != nullptr;
    }

    bool isLoaded_() const
    {
        return _loaded;
    }

    bool play()
    {
        return play(-1);
    }

    bool play(int channel)
    {
        return play(channel,LX_MIXER_NOLOOP);
    }

    bool play(int channel,int loops)
    {
        return Mix_PlayChannel(channel,_chunk,loops) == 0;
    }

    bool play(int channel,int loops,int ticks)
    {
        return Mix_PlayChannelTimed(channel,_chunk,loops,ticks) == 0;
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
LX_Chunk::LX_Chunk() : _chkimpl(nullptr) {}

LX_Chunk::LX_Chunk(const std::string& filename) : _chkimpl(new LX_Chunk_(filename)) {}

LX_Chunk::LX_Chunk(const UTF8string& filename) : _chkimpl(new LX_Chunk_(filename)) {}


bool LX_Chunk::load(const std::string& filename)
{
    _chkimpl.reset(new LX_Chunk_(filename));
    return _chkimpl->isLoaded_();
}

bool LX_Chunk::load(const UTF8string& filename)
{
    _chkimpl.reset(new LX_Chunk_(filename));
    return _chkimpl->isLoaded_();
}

bool LX_Chunk::isLoaded() const
{
    return _chkimpl != nullptr && _chkimpl->isLoaded_();
}

bool LX_Chunk::play()
{
    return isLoaded() && _chkimpl->play();
}

bool LX_Chunk::play(int channel)
{
    return isLoaded() && _chkimpl->play(channel,LX_MIXER_NOLOOP);
}

bool LX_Chunk::play(int channel,int loops)
{
    return isLoaded() && _chkimpl->play(channel,loops);
}

bool LX_Chunk::play(int channel,int loops,int ticks)
{
    return _chkimpl->play(channel,loops,ticks);
}

void LX_Chunk::close()
{
    _chkimpl.reset();
}

LX_Chunk::~LX_Chunk()
{
    _chkimpl.reset();
}

};
