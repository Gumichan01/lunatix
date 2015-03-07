

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Chunk.cpp
*	@brief The SDL_Chunk wrapper
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 19th, 2015
*
*/

#include<SDL2/SDL_mixer.h>

#include "LX_Sound.h"
#include "LX_Chunk.h"


/**
*   @fn LX_Chunk::LX_Chunk()
*
*   Construct the instance
*
*/
LX_Chunk::LX_Chunk()
{
    chunk = NULL;
}



/**
*   @fn LX_Chunk::LX_Chunk(Mix_Chunk *sample)
*
*   Construct the instance setting the Mix_Chunk instance from the sample
*
*   @param sample the sample file
*
*/
LX_Chunk::LX_Chunk(Mix_Chunk *sample)
{
    chunk = sample;
}


/**
*   @fn LX_Chunk::LX_Chunk(std::string filename)
*
*   Construct the instance creating the Mix_Chunk instance from a WAV file
*
*   @param filename the WAV file
*
*/
LX_Chunk::LX_Chunk(std::string filename)
{
    chunk = NULL;   // Chnuk must be set to NULL before the call of load()

    load(filename.c_str());
}


/**
*   @fn LX_Chunk::~LX_Chunk()
*
*   Destroyt all the instance
*
*/
LX_Chunk::~LX_Chunk()
{
    Mix_FreeChunk(chunk);
}

/**
*   @fn bool LX_Chunk::load(std::string filename)
*
*   Load the WAV sample from a file
*
*   @param filename the name of the sample file
*
*   @return TRUE on success, FALSE otherwise
*
*/
bool LX_Chunk::load(std::string filename)
{
    Mix_FreeChunk(chunk);

    chunk = Mix_LoadWAV(filename.c_str());

    if(chunk == NULL)
        return false;

    return true;
}



/**
*   @fn int LX_Chunk::play()
*
*   Play the current sample
*
*   @note This function plays the sample on the first unserved channel
*         with the no loop option
*
*   @return 0 on success, -1 otherwise
*
*/
int LX_Chunk::play()
{
    return play(-1);
}



/**
*   @fn int LX_Chunk::play(int channel)
*
*   Play the current sample
*
*   @param channel the channel to play the chunk on
*
*   @note This function plays the sample on the first unserved channel
*         with the no loop option
*
*   @return 0 on success, -1 otherwise
*
*/
int LX_Chunk::play(int channel)
{
    return Mix_PlayChannel(channel,chunk,0);
}



/**
*   @fn int LX_Chunk::play(int channel,int ticks)
*
*   Play the current sample during a moment
*
*   @param channel the channel to play the chunk on
*   @param ticks Millisecond limit to play the current sample
*
*   @note This function plays the sample on the first unserved channel
*         with the no loop option
*
*   @return 0 on success, -1 otherwise
*
*/
int LX_Chunk::play(int channel,int ticks)
{
    return Mix_PlayChannelTimed(channel,chunk,0, ticks);
}


/**
*   @fn int LX_Chunk::volume(int newVolume)
*
*   Set the chunk volume to newVolume, from 0 to 128
*
*   @param newVolume
*
*   @return the previous volume setting
*
*   @note If the volume is less than 0, then the previous volume is the current volume
*           and there is no change
*   @note If the new volume is greater than 128, the volume is set to 128
*   @note 128 is the maximum value defined by the MIX_MAX_VOLUME macro
*
*   @return 0 on success, -1 otherwise
*
*/
int LX_Chunk::volume(int newVolume)
{
    return Mix_VolumeChunk(chunk,newVolume);
}

























