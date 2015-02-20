

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
*	@file LX_Chunk.cpp
*	@brief The SDL_Chunk wrapper
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 19th, 2015
*
*/

#include "LX_Sound.h"
#include "LX_Chunk.h"
#include "LX_Mixer.h"

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

    if(!load(filename.c_str()))
    {
        std::cerr << "Error occured in LX_Chunk::load_sample / Mix_LoadWAV : " << Mix_GetError() << std::endl;
    }
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
    {
        std::cerr << "Error occured in LX_Chunk::load_sample / Mix_LoadWAV : " << Mix_GetError() << std::endl;
        return false;
    }

    return true;

}



/**
*   @fn void LX_Chunk::play()
*
*   Play the current sample
*
*   @note This function plays the sample on the first unserved channel
*         with the no loop option
*
*/
void LX_Chunk::play()
{
    if(Mix_PlayChannel(-1,chunk,LX_MIXER_NOLOOP) == -1)
    {
        std::cerr << "Error occured in LX_Chunk::load / Mix_PlayChannel : "
                        << Mix_GetError() << std::endl;
    }
}


/**
*   @fn void LX_Chunk::play(int ticks)
*
*   Play the current sample during a moment
*
*   @param ticks Millisecond limit to play the current sample
*
*   @note This function plays the sample on the first unserved channel
*         with the no loop option
*
*/
void LX_Chunk::play(int ticks)
{
    if(Mix_PlayChannelTimed(-1,chunk,LX_MIXER_NOLOOP, ticks))
    {
        std::cerr << "Error occured in LX_Chunk::load / Mix_PlayChannelTimed : "
                        << Mix_GetError() << std::endl;
    }
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
*/
int LX_Chunk::volume(int newVolume)
{
    return Mix_VolumeChunk(chunk,newVolume);
}

























