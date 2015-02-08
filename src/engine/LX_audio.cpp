

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
*	@file LX_Audio.cpp
*	@brief The LunatiX_engine sound module
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 23th, 2014
*
*/

#include "LX_Audio.h"



/**
*   @fn LX_Audio::LX_Audio()
*
*   Load the LX_Audio manager
*
*/
LX_Audio::LX_Audio()
{
    music = NULL;
}


/**
*   @fn LX_Audio::LX_Audio(Mix_Music *mus)
*
*   Load the LX_Audio manager with a Mix_Music
*
*   @param mus the Mix_Music
*
*/
LX_Audio::LX_Audio(Mix_Music *mus)
{
    music = mus;
}


/**
*   @fn LX_Audio::LX_Audio(std::string filename)
*
*   Load the LX_Audio manager with a Mix_Music
*
*   @param filename the music filename you want to load
*
*/
LX_Audio::LX_Audio(std::string filename)
{
    music = NULL;   // If you remove this code line, you will have a segmentation fault

    if(load_music(filename.c_str()))
    {
        music = NULL;
    }
}



/**
*   @fn bool LX_Audio::load_music(std::string filename)
*
*   Load the music specified in the music file
*
*   @param filename the file you want to open
*
*   @return TRUE if all is OK, FALSE otherwise
*
*/
bool LX_Audio::load_music(std::string filename)
{
    Mix_FreeMusic(music);

    music = Mix_LoadMUS(filename.c_str());

    if(music == NULL)
    {
        std::cerr << "Error occured in LX_Audio::load_music / Mix_LoadMUS : " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}


/**
*   @fn bool LX_Audio::play_music(int loops)
*
*   Play the music specified in the LX_Audio class
*
*   @param loops the loops constant
*
*   @return TRUE if it is OK, FALSE otherwise
*
*/
void LX_Audio::play_music(int loops)
{
    if(Mix_PlayMusic(music,LX_AUDIO_LOOP) == -1)
    {
        std::cerr << "Error occured in LX_Audio::play_music : " << Mix_GetError() << std::endl;
    }
}


/**
*   @fn bool LX_Audio::play_music()
*
*   Play the music specified in the LX_Audio class
*
*   @return TRUE if it is OK, FALSE otherwise
*
*   @note This function internally calls play_music(int loops)
*
*/
void LX_Audio::play_music()
{
    return play_music(LX_AUDIO_LOOP);
}


/**
*   @fn void LX_Audio::pause_music()
*
*   Pause or resume the current music
*
*/
void LX_Audio::pause_music()
{
    if(Mix_PausedMusic())
    {
        Mix_ResumeMusic();
    }
    else
    {
        Mix_PauseMusic();
    }
}


/**
*   @fn void LX_Audio::stop_music()
*
*   Stop the music
*
*/
void LX_Audio::stop_music()
{
    if(!Mix_PlayingMusic())
    {
        Mix_PlayMusic(music,-1);
    }
    else
    {
        Mix_HaltMusic();
    }
}


/**
*   @fn Mix_Chunk * LX_Audio::load_sample(std::string filename)
*
*   Load the sample
*
*   @param filename the name of the sample file
*
*   @return The sample if it is OK, NULL otherwise
*
*/
Mix_Chunk * LX_Audio::load_sample(std::string filename)
{
    Mix_Chunk *sample = NULL;

    sample = Mix_LoadWAV(filename.c_str());

    if(sample == NULL)
    {
        std::cerr << "Error occured in LX_Audio::load_sample / Mix_LoadWAV : " << Mix_GetError() << std::endl;
    }

    return sample;
}




/**
*   @fn void LX_Audio::play_sample(Mix_Chunk *sample)
*
*   Load the sample
*
*   @param sample the sample
*
*   @note This function plays the sample on the first unserved channel with no loop option
*           If you want to select a channel and/or play the sample with the loop option
*           you may use the other function
*
*/
void LX_Audio::play_sample(int channel,Mix_Chunk *sample,int loops)
{
    if(Mix_PlayChannel(channel,sample,loops) == -1)
    {
        std::cerr << "Error occured in LX_Audio::play_sample : " << Mix_GetError() << std::endl;
    }
}



/**
*   @fn void LX_Audio::play_sample(Mix_Chunk *sample)
*
*   Load the sample
*
*   @param sample the sample
*
*   @note This function plays the sample on the first unserved channel with no loop option
*           If you want to select a channel and/or play the sample with the loop option
*           you may use the other function
*
*/
void LX_Audio::play_sample(Mix_Chunk *sample)
{
    play_sample(-1,sample,LX_AUDIO_LOOP);
}


/**
*   @fn int LX_Audio::musicVolume()
*
*   Set the music volume to volume, from 0 to 128
*
*   @param volume
*
*   @return the previous volume setting
*
*   @note If the volume is equals to -1, then the previous volume is the current volume
*   @note If the new volume is greater than 128, the volume is set to 128
*   @note Ths value 128 is ht maximum value defined by the MIX_MAX_VOLUME macro
*
*/
int LX_Audio::musicVolume(int volume)
{
    return Mix_VolumeMusic(volume);
}




/**
*   @fn int LX_Audio::chunkVolume(Mix_Chunk *chunk,int volume)
*
*   Set the chunk volume to volume, from 0 to 128
*
*   @param chunk the chunk to set the volume in
*   @param volume
*
*   @return the previous volume setting
*
*   @note If the volume is less than 0, then the previous volume is the current volume
*           and there is no change
*   @note If the new volume is greater than 128, the volume is set to 128
*   @note Ths value 128 is ht maximum value defined by the MIX_MAX_VOLUME macro
*
*/
int LX_Audio::chunkVolume(Mix_Chunk *chunk,int volume)
{
    return Mix_VolumeChunk(chunk,volume);
}



/**
*   @fn int LX_Audio::channelVolume(int channel,int volume)
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
int LX_Audio::channelVolume(int channel,int volume)
{
    return Mix_Volume(channel,volume);
}


void LX_Audio::setDistance(Uint8 distance)
{
    setDistance(MIX_CHANNEL_POST,distance);
}

void LX_Audio::setDistance(int channel,Uint8 distance)
{
    if(Mix_SetDistance(channel,distance))
    {
        std::cerr << "distance setting failed : " << Mix_GetError() << std::endl;
    }
}




















