

/*
*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*
*/

/**
*	@file LX_Mixer.cpp
*	@brief The mixer library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 11th, 2014
*
*
*/

#include "LX_Sound.h"
#include "LX_Music.h"
#include "LX_Chunk.h"
#include "LX_Mixer.h"


/**
*   @fn LX_Music * LX_Mixer::loadMusic(std::string filename)
*
*   Load the music according to the file name
*
*   @param filename the name of the music file
*
*   @return The new LX_Mixer instance, NULL otherwise
*
*/
LX_Music * LX_Mixer::loadMusic(std::string filename)
{
    return new LX_Music(filename.c_str());
}



/**
*   @fn LX_Music * LX_Mixer::loadMusic(Mix_Music *mus)
*
*   Load the music according to the Mix_Music structure
*
*   @param mus the Mix_Music structure loaded
*
*   @return The new LX_Mixer instance, NULL otherwise
*
*/
LX_Music * LX_Mixer::loadMusic(Mix_Music *mus)
{
    return new LX_Music(mus);
}



/**
*   @fn LX_Chunk * LX_Mixer::loadSample(std::string filename)
*
*   Create a new LX_Chunk instance from a WAV file
*
*   @param filename the name of the sample file
*
*   @return a new instance, NULL otherwise
*
*/
LX_Chunk * LX_Mixer::loadSample(std::string filename)
{
    return new LX_Chunk(filename.c_str());
}


/**
*   @fn LX_Chunk * LX_Mixer::loadSample(Mix_Chunk *ch)
*
*   Create a new LX_Chunk instance from a Mix_Chunk structure
*
*   @param ch the Mix_chunk
*
*   @return a new instance, NULL otherwise
*
*/
LX_Chunk * LX_Mixer::loadSample(Mix_Chunk *ch)
{
    return new LX_Chunk(ch);
}




/**
*   @fn int LX_Mixer::channelVolume(int channel,int volume)
*
*   Set the channel volume to volume, from 0 to 128
*
*   @param channel the channel to set the volume in
*   @param volume
*
*   @return the previous volume setting
*
*   @note if the channel is -1, all channels will be set to the volume
*   @note If the volume is equals to -1, then the average volume is returned
*   @note If the new volume is greater than 128, the volume is set to 128
*   @note Ths value 128 is ht maximum value defined by the MIX_MAX_VOLUME macro
*
*/
int LX_Mixer::channelVolume(int channel,int volume)
{
    return Mix_Volume(channel,volume);
}



/**
*   @fn void LX_Mixer::setDistance(Uint8 distance)
*
*   Set the distance
*
*   @param distance the virtuel distance betwenn the user and the source
*
*/
void LX_Mixer::setDistance(Uint8 distance)
{
    setDistance(MIX_CHANNEL_POST,distance);
}


/**
*   @fn void LX_Mixer::setDistance(int channel,Uint8 distance)
*
*   Set the distance
*
*   @param channel the channel you need to use
*   @param distance the virtuel distance betwenn the user and the source
*
*   @note If you set MIX_CHANNEL_POST, all channel will be dealt
*
*/
void LX_Mixer::setDistance(int channel,Uint8 distance)
{
    if(Mix_SetDistance(channel,distance))
    {
        std::cerr << "distance setting failed : " << Mix_GetError() << std::endl;
    }
}
