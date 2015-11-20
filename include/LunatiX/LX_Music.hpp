#ifndef LX_MUSIC_H_INCLUDED
#define LX_MUSIC_H_INCLUDED


/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
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

#include <SDL2/SDL_mixer.h>

#include "LX_Sound.hpp"


namespace LX_Mixer
{


/**
*   @class LX_MusicException
*   @brief The exception class of LX_Music
*
*/
class LX_MusicException : public std::exception
{
    std::string stringError;

public :

    LX_MusicException(std::string err);
    LX_MusicException(const LX_MusicException& me);

    const char * what() const noexcept;

    ~LX_MusicException() noexcept;
};



/**
*   @class LX_Music
*   @brief The music class
*
*   This class is a high level description of the Mix_Music type
*
*/
class LX_Music : public virtual LX_Sound
{
    Mix_Music *music;      /* The music to play */

    LX_Music(LX_Music& m);
    LX_Music& operator =(LX_Music& m);

public:

    LX_Music(Mix_Music *mus);
    LX_Music(std::string filename);

    // Music
    bool load(std::string filename);
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

