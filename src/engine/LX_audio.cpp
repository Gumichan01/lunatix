

/*
*
*	Copyright (C)  Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*
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
        fprintf(stderr,"\nException occured in LX_Audio::load_music / Mix_LoadMUS :  %s \n", Mix_GetError());
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
        fprintf(stderr,"\nException occured in LX_Audio::load_music / Mix_PlayMusic :  %s \n", Mix_GetError());
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





















