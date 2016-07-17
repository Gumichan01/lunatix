#ifndef LX_MUSIC_H_INCLUDED
#define LX_MUSIC_H_INCLUDED


/*
*	Copyright (C) 2016 Luxon Jean-Pierre
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
*	@version 0.8
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
    std::string _string_error;

public :

    /// Construct the exception
    LX_MusicException(std::string err);
    /// Construct the exception by copy
    LX_MusicException(const LX_MusicException& me);

    /// Get the error message
    const char * what() const noexcept;

    /// Destroy the exception
    ~LX_MusicException() noexcept;
};

/// TODO load music from utf-8 string files

/**
*   @class LX_Music
*   @brief The music class
*
*   This class is a high level description of the Mix_Music type
*
*/
class LX_Music : public virtual LX_Sound
{
    Mix_Music *_music;

    LX_Music(LX_Music& m);
    LX_Music& operator =(LX_Music& m);

public:

    /**
    *   @fn LX_Music(Mix_Music *mus)
    *
    *   Create the instance with a Mix_Music
    *
    *   @param mus The Mix_Music
    */
    LX_Music(Mix_Music *mus);   /// TODO remove this constructor (Mix_Music)

    /**
    *   @fn LX_Music(std::string filename)
    *
    *   Create the instance loading a music file
    *
    *   @param filename The music filename that will be loaded
    */
    LX_Music(std::string filename);

    /**
    *   @fn bool load(std::string filename)
    *
    *   Load the music specified in the music file
    *
    *   @param filename The file to load the music from
    *
    *   @return TRUE on success, FALSE otherwise
    */
    bool load(std::string filename);    /// TODO remove this function (useless)

    /**
    *   @fn bool play(void)
    *
    *   Play the music specified in the LX_Music class
    *
    *   @return TRUE on success, FALSE otherwise
    *
    *   @note This function internally calls play(int loops) with LX_MIXER_NOLOOP
    *
    */
    bool play(void);

    /**
    *   @fn bool play(int loops)
    *
    *   Play the music specified in the LX_Music class
    *
    *   @param loops The loop constant
    *
    *   @return TRUE on success,FALSE otherwise
    *
    *   @note If loops is set to LX_MIXER_NOLOOP, the music is played only once.
    *   @note If loops is set to LX_MIXER_LOOP, the music is played forever.
    */
    bool play(int loops);

    /**
    *   @fn void pause(void)
    *   Pause or resume the current music
    */
    void pause(void);

    /**
    *   @fn void stop(void)
    *   Stop the music
    */
    void stop(void);

    /**
    *   @fn int volume(int newVolume)
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
    */
    int volume(int newVolume);

    /**
    *   @fn Mix_Music * getMusic(void)
    *
    *   Return the instance to the music structure
    *
    *   @return The Mix_Music
    */
    Mix_Music *getMusic(void);  /// TODO remove this function (encapsulation violation)

    /**
    *   @fn ~LX_Music(void)
    *
    *   Destroy the instance
    *
    */
    ~LX_Music();
};


};

#endif // LX_MUSIC_H_INCLUDED
