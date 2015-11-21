#ifndef LX_CHUNK_H_INCLUDED
#define LX_CHUNK_H_INCLUDED


/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Chunk.hpp
*	@brief The chunk header
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.7
*
*/

#include "LX_Sound.hpp"


struct Mix_Chunk;

namespace LX_FileIO
{

class LX_FileBuffer;

};


namespace LX_Mixer
{

/**
*   @class LX_ChunkException
*   @brief The exception class of LX_Chunk
*/
class LX_ChunkException : public std::exception
{
    std::string stringError;

public :

    LX_ChunkException(std::string err);
    LX_ChunkException(const LX_ChunkException& me);

    const char * what() const noexcept;

    ~LX_ChunkException() noexcept;
};



/**
*   @class LX_Chunk
*   @brief The chunk class
*/
class LX_Chunk : public virtual LX_Sound
{

    Mix_Chunk *chunk;

    LX_Chunk(LX_Chunk& m);
    LX_Chunk& operator =(LX_Chunk& m);

public:

    LX_Chunk(Mix_Chunk *sample);
    LX_Chunk(std::string filename);
    LX_Chunk(LX_FileIO::LX_FileBuffer *file);

    bool load(std::string filename);
    bool loadFromBuffer(LX_FileIO::LX_FileBuffer *file);
    bool play();
    bool play(int channel);
    bool play(int channel,int ticks);

    int volume(int newVolume);

    ~LX_Chunk();
};

};

#endif // LX_CHUNK_H_INCLUDED

