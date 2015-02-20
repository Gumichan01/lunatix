#ifndef LX_CHUNK_H_INCLUDED
#define LX_CHUNK_H_INCLUDED



/*
*	Copyright (C) 2014 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Chunk.h
*	@brief The wrapper of the SDL_Chunk structure
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 19th, 2015
*
*/

#include<iostream>


struct Mix_Chunk;
class LX_Sound;

class LX_Chunk : LX_Sound{

    Mix_Chunk *chunk;

    public:

    LX_Chunk();
    LX_Chunk(Mix_Chunk *sample);
    LX_Chunk(std::string filename);

    bool load(std::string filename);
    void play();
    void play(int ticks);

    int volume(int newVolume);

    ~LX_Chunk();

};


#endif // LX_CHUNK_H_INCLUDED

















