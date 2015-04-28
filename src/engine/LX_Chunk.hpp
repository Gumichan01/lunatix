#ifndef LX_CHUNK_H_INCLUDED
#define LX_CHUNK_H_INCLUDED



/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
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
*	@brief The LX_Chunk file
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.3
*
*/


struct Mix_Chunk;
class LX_Sound;


/**
*   @class LX_Chunk
*   @brief The chunk class
*
*/
class LX_Chunk : LX_Sound{

    Mix_Chunk *chunk;

    public:

    LX_Chunk();
    LX_Chunk(Mix_Chunk *sample);
    LX_Chunk(std::string filename);

    bool load(std::string filename);
    int play();
    int play(int channel);
    int play(int channel,int ticks);

    int volume(int newVolume);

    ~LX_Chunk();

};


#endif // LX_CHUNK_H_INCLUDED

















