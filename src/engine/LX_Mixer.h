#ifndef LX_MIXER_H_INCLUDED
#define LX_MIXER_H_INCLUDED



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
*	@file LX_Mixer.h
*	@brief The mixer library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 11th, 2014
*
*
*/



#include<iostream>

#include<SDL2/SDL_mixer.h>


#define LX_MIXER_STEREO_SOUND 2             /**< The stereo variable the mix module */
#define LX_MIXER_MONO_SOUND 1               /**< The mono variable for the mix module */
#define LX_MIXER_DEFAULT_CHUNKSIZE 1024     /**< The default chunsize for the mix module */

#define LX_MIXER_LOOP -1                    /**< Activate the loop*/
#define LX_MIXER_NOLOOP 0                   /**< No loop is activated */



/// @todo [LX_Mixer] Support of 2D sound effects (panning, fade in/out, 3D audio, stereo reverse)
/// @todo [LX_Mixer] Create a LX_Chunk class. It will manage the Mix_Chunk structures

class LX_Music;
class LX_Chunk;

/**
*   @class LX_Mixer
*   @brief The LunatiX_engine sound module
*
*   This SDL_Mixer-based sound engine will load and read a various audio files
*
**/
class LX_Mixer{

    LX_Mixer(){}

    public :

    // Music
    LX_Music * loadMusic(std::string filename);
    LX_Music * loadMusic(Mix_Music *mus);

    LX_Chunk * loadSample(std::string filename);
    LX_Chunk * loadSample(Mix_Chunk *ch);

    int channelVolume(int channel,int volume);

    // Effects
    void setDistance(Uint8 distance);
    void setDistance(int channel,Uint8 distance);

    ~LX_Mixer(){}

};




#endif // LX_MIXER_H_INCLUDED
















