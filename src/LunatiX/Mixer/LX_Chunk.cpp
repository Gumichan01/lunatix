

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is an SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Chunk.cpp
*	@brief The chunk implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <SDL2/SDL_mixer.h>

#include <LunatiX/LX_Chunk.hpp>
#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_FileIO.hpp>
#include <LunatiX/LX_FileBuffer.hpp>

using namespace LX_FileIO;


namespace LX_Mixer
{


/**
*   @fn LX_ChunkException::LX_ChunkException(std::string err)
*
*   Build the LX_ChunkException class
*
*   @param err The error string
*
*/
LX_ChunkException::LX_ChunkException(std::string err)
{
    stringError = err;
}


/**
*   @fn const char * LX_ChunkException::what() const throw()
*
*   Get the error string
*
*   @return The error string
*/
const char * LX_ChunkException::what() const throw()
{
    return stringError.c_str();
}


LX_ChunkException::~LX_ChunkException() throw() {}




/**
*   @fn LX_Chunk::LX_Chunk(void)
*
*   Construct the instance
*
*/
LX_Chunk::LX_Chunk(void) : chunk(NULL)
{
    // Empty
}



/**
*   @fn LX_Chunk::LX_Chunk(Mix_Chunk *sample)
*
*   Construct the instance setting the Mix_Chunk instance
*
*   @param sample The sample file
*
*/
LX_Chunk::LX_Chunk(Mix_Chunk *sample) : chunk(sample)
{
    // Empty
}


/**
*   @fn LX_Chunk::LX_Chunk(string filename)
*
*   Construct the instance creating the Mix_Chunk instance from a file
*
*   @param filename The file to create the chunk from
*
*   @note It is preferable to give a .wav file to the constructor.
*           The chunk was optimized for this format. But it can work with
*           an other file type.
*
*   @exception LX_ChunkException if the chunk cannot be created from the file
*
*/
LX_Chunk::LX_Chunk(string filename) : chunk(NULL)
{
    if(load(filename.c_str()) == false)
    {
        throw LX_ChunkException(LX_GetError());
    }
}


/**
*   @fn LX_Chunk::LX_Chunk(LX_FileBuffer * file)
*
*   Construct the instance creating the Mix_Chunk instance
*   from a file buffer.
*
*   @param file The file buffer to create the chunk from
*
*   @exception LX_ChunkException if the chunk cannot be created from the file buffer
*
*/
LX_Chunk::LX_Chunk(LX_FileBuffer * file) : chunk(NULL)
{
    if(loadFromBuffer(file) == false)
    {
        throw LX_ChunkException(LX_GetError());
    }
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
*   @fn bool LX_Chunk::load(string filename)
*
*   Load the WAV sample from a file
*
*   @param filename The name of the sample file
*
*   @return TRUE on success, FALSE otherwise
*
*   @sa loadFromBuffer
*/
bool LX_Chunk::load(string filename)
{
    Mix_FreeChunk(chunk);
    chunk = Mix_LoadWAV(filename.c_str());
    return chunk != NULL;
}


/**
*   @fn bool LX_Chunk::loadFromBuffer(LX_FileBuffer *file)
*
*   Load the sample from a file buffer
*
*   @param file The file buffer to load the chunk from
*
*   @return TRUE on success, FALSE otherwise
*
*/
bool LX_Chunk::loadFromBuffer(LX_FileBuffer *file)
{
    Mix_FreeChunk(chunk);
    chunk = file->getChunkFromBuffer();
    return chunk != NULL;
}



/**
*   @fn bool LX_Chunk::play()
*
*   Play the current sample
*
*   @note This function plays the sample on the first unserved channel
*         with the no loop option
*
*   @return TRUE on success, FALSE otherwise
*
*/
bool LX_Chunk::play()
{
    return play(-1);
}



/**
*   @fn bool LX_Chunk::play(int channel)
*
*   Play the current sample
*
*   @param channel The channel to play the chunk on
*
*   @note This function plays the sample with no loop
*
*   @return TRUE on success, FALSE otherwise
*
*/
bool LX_Chunk::play(int channel)
{
    return play(channel,0);
}



/**
*   @fn bool LX_Chunk::play(int channel,int ticks)
*
*   Play the current sample during a moment
*
*   @param channel The channel to play the chunk on
*   @param ticks The limit in millisecond to play the current sample
*
*   @note This function plays the sample on with no loop
*
*   @return TRUE on success, FALSE otherwise
*
*/
bool LX_Chunk::play(int channel,int ticks)
{
    return Mix_PlayChannelTimed(channel,chunk,0,ticks) == 0;
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



