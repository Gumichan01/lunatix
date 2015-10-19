#ifndef LX_MUSIC_H_INCLUDED
#define LX_MUSIC_H_INCLUDED



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
*	@file LX_Music.hpp
*	@brief The music library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/


#include<SDL2/SDL_mixer.h>

#include "LX_Sound.hpp"


namespace LX_Mixer
{


class LX_Sound;


/**
*   @class LX_Music
*   @brief The music class
*
*   This class is a high level description of the Mix_Music type
*
*/
class LX_Music : virtual public LX_Sound
{

    Mix_Music *music;      /* The music to play */

    LX_Music(LX_Music& m);
    LX_Music& operator =(LX_Music& m);

public:

    LX_Music(void);
    LX_Music(Mix_Music *mus);
    LX_Music(string filename);

    // Music
    bool load(string filename);
    bool play(void);
    bool play(int loops);
    void pause(void);
    void stop(void);

    // Volume
    int volume(int newVolume);

    Mix_Music *getMusic(void);

    ~LX_Music();

};


};


#endif // LX_MUSIC_H_INCLUDED


