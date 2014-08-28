

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
*   @fn bool LX_Audio::play_music()
*
*   Play the music specified in the LX_Audio class
*
*   @return TRUE if all is OK, FALSE otherwise
*
*/
bool LX_Audio::play_music()
{
    int err;

    err = Mix_PlayMusic(music,LX_AUDIO_LOOP);

    if(err == -1)
    {
        std::cerr << "Error occured in LX_Audio::load_music / Mix_PlayMusic : " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
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
*/
void LX_Audio::play_sample(Mix_Chunk *sample)
{
    Mix_PlayChannel(-1,sample,LX_AUDIO_NOLOOP);
}


















