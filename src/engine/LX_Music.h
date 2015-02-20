#ifndef LX_MUSIC_H_INCLUDED
#define LX_MUSIC_H_INCLUDED



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
*	@file LX_Music.h
*	@brief The LX_Music library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date February 11th, 2014
*
*/


#include<iostream>

#include<SDL2/SDL_mixer.h>



/**
*   @class LX_Music
*   @brief The audio class
*
*   This clas is a wrapper of the Mix_Music type
*
**/
class LX_Music{

    Mix_Music *music;      /**<The music you want to play (note : LX_Music only plays one music)*/

    public:

    LX_Music();
    LX_Music(Mix_Music *mus);
    LX_Music(std::string filename);

    // Music
    bool load(std::string filename);
    void play();
    void play(int loops);
    void pause();
    void stop();


    // Volume
    int volume(int newVolume);


    ~LX_Music();

};

#endif // LX_MUSIC_H_INCLUDED



















