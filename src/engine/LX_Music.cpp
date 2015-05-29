

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/



/**
*	@file LX_Music.cpp
*	@brief The implementation of the music library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.4
*
*/


#include "LX_Sound.hpp"
#include "LX_Music.hpp"
#include "LX_Error.hpp"


namespace LX_Mixer{

    /**
    *   @fn LX_Music::LX_Music(void)
    *
    *   Create the instance
    *
    */
    LX_Music::LX_Music(void)
    {
        music = NULL;
    }


    /**
    *   @fn LX_Music::LX_Music(Mix_Music *mus)
    *
    *   Create the instance with a Mix_Music
    *
    *   @param mus The Mix_Music
    *
    */
    LX_Music::LX_Music(Mix_Music *mus)
    {
        music = mus;
    }


    /**
    *   @fn LX_Music::LX_Music(std::string filename)
    *
    *   Create the instance loading a music file
    *
    *   @param filename The music filename you want to load
    *
    */
    LX_Music::LX_Music(std::string filename)
    {
        music = NULL;

        load(filename.c_str());
    }


    /**
    *   @fn LX_Music::~LX_Music(void)
    *
    *   Destroy the instance
    *
    */
    LX_Music::~LX_Music(void)
    {
        Mix_FreeMusic(music);
    }



    /**
    *   @fn bool LX_Music::load(std::string filename)
    *
    *   Load the music specified in the music file
    *
    *   @param filename The file to load the music from
    *
    *   @return TRUE on success, FALSE otherwise
    *
    */
    bool LX_Music::load(std::string filename)
    {
        Mix_FreeMusic(music);

        music = Mix_LoadMUS(filename.c_str());

        if(music == NULL)
            return false;

        return true;
    }


    /**
    *   @fn int LX_Music::play(int loops)
    *
    *   Play the music specified in the LX_Music class
    *
    *   @param loops The loop constant
    *
    *   @return 0 on success, -1 otherwise
    *
    */
    int LX_Music::play(int loops)
    {
        return Mix_PlayMusic(music,loops);
    }


    /**
    *   @fn int LX_Music::play(void)
    *
    *   Play the music specified in the LX_Music class
    *
    *   @return 0 on success, -1 otherwise
    *
    *   @note This function internally calls play(int loops) with no loop
    *
    */
    int LX_Music::play(void)
    {
        return play(LX_MIXER_NOLOOP);
    }


    /**
    *   @fn void LX_Music::pause(void)
    *
    *   Pause or resume the current music
    *
    */
    void LX_Music::pause(void)
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
    *   @fn void LX_Music::stop(void)
    *
    *   Stop the music
    *
    */
    void LX_Music::stop(void)
    {
        if(Mix_PlayingMusic())
        {
            Mix_HaltMusic();
        }
    }



    /**
    *   @fn int LX_Music::volume(int newVolume)
    *
    *   Set the music volume to newVolume, from 0 to 128
    *
    *   @param newVolume The volume to set
    *
    *   @return The previous volume setting
    *
    *   @note If the volume is equals to -1, then the previous volume is the current volume
    *   @note If the new volume is greater than 128, the volume is set to 128
    *   @note The value 128 is the maximum value defined by the MIX_MAX_VOLUME macro
    *
    */
    int LX_Music::volume(int newVolume)
    {
        return Mix_VolumeMusic(newVolume);
    }



    /**
    *   @fn Mix_Music * LX_Music::getMusic(void)
    *
    *   Return the instance to the music structure
    *
    *   @return The Mix_Music
    *
    */
    Mix_Music * LX_Music::getMusic(void)
    {
        return music;
    }


};


