

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
*	@file LX_Chunk.cpp
*	@brief The LX_Chunk implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.4
*
*/

#include <SDL2/SDL_mixer.h>

#include "LX_Sound.hpp"
#include "LX_Chunk.hpp"
#include "LX_Error.hpp"


namespace LX_Mixer{

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
    *   Construct the instance setting the Mix_Chunk instance
    *
    *   @param sample The sample file
    *
    */
    LX_Chunk::LX_Chunk(Mix_Chunk *sample)
    {
        chunk = sample;
    }


    /**
    *   @fn LX_Chunk::LX_Chunk(std::string filename)
    *
    *   Construct the instance creating the Mix_Chunk instance from a file
    *
    *   @param filename The file
    *
    *   @note It is preferable to give a .wav file to the constructor.
    *           The chunk was optimized for this format. But it can work with
    *           an other file type.
    *
    */
    LX_Chunk::LX_Chunk(std::string filename)
    {
        chunk = NULL;

        load(filename.c_str());
    }


    /**
    *   @fn LX_Chunk::~LX_Chunk()
    *
    *   Destroy the instance
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
    *   @param filename The name of the sample file
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
    *   @param channel The channel to play the chunk on
    *
    *   @note This function plays the sample with no loop
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
    *   @param channel The channel to play the chunk on
    *   @param ticks The limit in millisecond to play the current sample
    *
    *   @note This function plays the sample on with no loop
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
    *   Set the volume of the chunk, from 0 to 128
    *
    *   @param newVolume The volume to set
    *
    *   @return The previous volume setting
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


};



