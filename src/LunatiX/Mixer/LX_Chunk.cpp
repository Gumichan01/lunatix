

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
*	@file LX_Chunk.cpp
*	@brief The chunk implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/LX_Chunk.hpp>
#include <SDL2/SDL_mixer.h>

#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_FileIO.hpp>
#include <LunatiX/LX_FileBuffer.hpp>


namespace LX_Mixer
{

LX_ChunkException::LX_ChunkException(std::string err) : _string_error(err) {}

LX_ChunkException::LX_ChunkException(const LX_ChunkException& me)
    : _string_error(me._string_error) {}

const char * LX_ChunkException::what() const noexcept
{
    return _string_error.c_str();
}

LX_ChunkException::~LX_ChunkException() noexcept {}


/* LX_Chunk */

LX_Chunk::LX_Chunk(std::string& filename) : _chunk(nullptr)
{
    if(load_(filename) == false)
        throw LX_ChunkException(LX_GetError());
}


LX_Chunk::LX_Chunk(UTF8string& filename) : _chunk(nullptr)
{
    if(load_(filename.utf8_str()) == false)
        throw LX_ChunkException(LX_GetError());
}


LX_Chunk::LX_Chunk(LX_FileIO::LX_FileBuffer * file) : _chunk(nullptr)
{
    if(loadFromBuffer(file) == false)
        throw LX_ChunkException(LX_GetError());
}


bool LX_Chunk::load_(std::string filename)
{
    Mix_FreeChunk(_chunk);
    _chunk = Mix_LoadWAV(filename.c_str());
    return _chunk != nullptr;
}


bool LX_Chunk::loadFromBuffer(LX_FileIO::LX_FileBuffer *file)
{
    Mix_FreeChunk(_chunk);
    _chunk = file->getChunkFromBuffer();
    return _chunk != nullptr;
}


bool LX_Chunk::play()
{
    return play(-1);
}


bool LX_Chunk::play(int channel)
{
    return play(channel,LX_MIXER_NOLOOP);
}


bool LX_Chunk::play(int channel,int loops)
{
    return Mix_PlayChannel(channel,_chunk,loops) == 0;
}


bool LX_Chunk::play(int channel,int loops,int ticks)
{
    return Mix_PlayChannelTimed(channel,_chunk,loops,ticks) == 0;
}


LX_Chunk::~LX_Chunk()
{
    Mix_FreeChunk(_chunk);
}

};
