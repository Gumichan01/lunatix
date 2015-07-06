#ifndef LX_CHUNK_H_INCLUDED
#define LX_CHUNK_H_INCLUDED



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
*	@file LX_Chunk.hpp
*	@brief The chunk header
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include "LX_Sound.hpp"


struct Mix_Chunk;

namespace LX_FileIO
{

class LX_FileBuffer;

};

using namespace LX_FileIO;


namespace LX_Mixer
{


/**
*   @class LX_Chunk
*   @brief The chunk class
*
*/
class LX_Chunk : LX_Sound
{

    Mix_Chunk *chunk;

public:

    LX_Chunk(void);
    LX_Chunk(Mix_Chunk *sample);
    LX_Chunk(string filename);
    LX_Chunk(LX_FileBuffer *file);

    bool load(std::string filename);
    bool loadFromBuffer(LX_FileBuffer *file);
    bool play();
    bool play(int channel);
    bool play(int channel,int ticks);

    int volume(int newVolume);

    ~LX_Chunk();

};

};

#endif // LX_CHUNK_H_INCLUDED


