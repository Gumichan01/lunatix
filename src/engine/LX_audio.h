#ifndef LX_AUDIO_H_INCLUDED
#define LX_AUDIO_H_INCLUDED



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
*	@file LX_Audio.h
*	@brief The LX_Audio library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 18th, 2014
*
*/


#include<iostream>

#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>

/// @todo Support of 2D sound effects

#define LX_AUDIO_STEREO_SOUND 2             /**< The stereo variable the mix module */
#define LX_AUDIO_MONO_SOUND 1               /**< The mono variable for the mix module */
#define LX_AUDIO_DEFAULT_CHUNKSIZE 1024     /**< The default chunsize for the mix module */

#define LX_AUDIO_LOOP -1                    /**< Activate the loop*/
#define LX_AUDIO_NOLOOP 0                   /**< No loop is activated */


/**
*   @class LX_Audio
*   @brief The LunatiX_engine sound module
*
*   This SDL_Mixer-based sound engine will load and read a various audio files
*
*
**/
class LX_Audio{

    Mix_Music *music;      /**<The music you want to play (note : LX_Audio only plays one music)*/


    public:

/**
*   @fn LX_Audio()
*
*   Load the LX_Audio library
*
**/
    LX_Audio()
    {
        music = NULL;
    }

    bool load_music(std::string filename);
    void play_music();
    void play_music(int loops);
    void pause_music();
    void stop_music();

    Mix_Chunk * load_sample(std::string filename);
    void play_sample(Mix_Chunk *sample);
    void play_sample(int channel,Mix_Chunk *sample,int loops);

    int musicVolume(int volume);
    int chunkVolume(Mix_Chunk *chunk,int volume);
    int channelVolume(int channel,int volume);

    ~LX_Audio()
    {
        Mix_FreeMusic(music);
    }

};

#endif // LX_AUDIO_H_INCLUDED



















