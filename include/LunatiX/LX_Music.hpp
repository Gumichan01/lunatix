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

protected:

    bool load_(std::string filename);

public:

    /**
    *   @fn LX_Music(std::string& filename)
    *
    *   Create the instance loading a music file
    *
    *   @param filename The music filename that will be loaded
    *   @exception LX_MusicException if the music cannot be created from the file
    */
    LX_Music(std::string& filename);

    /**
    *   @fn LX_Music(UTF8string filename)
    *
    *   Create the instance loading a music file
    *
    *   @param filename The music filename that will be loaded
    *   @exception LX_MusicException if the music cannot be created from the file
    */
    LX_Music(UTF8string& filename);

    /**
    *   @fn void fadeIn(int ms)
    *
    *   Fade in the current Music over some milliseconds of time
    *
    *   @param ms Milliseconds for the fade-in effect to complete
    *
    *   @note fadeInMusic starts playing the music with the fade-in effect.
    *         It is not necessary to call LX_Music::play() if this function is called
    *
    *   @note Any previous music will be halted, or if it is fading out
    *           it will wait (blocking) for the fade to complete
    */
    void fadeIn(int ms);
    /**
    *   @fn void fadeOut(int ms)
    *
    *   Fade out the music over some milliseconds of time
    *
    *   @param ms Milliseconds for the fade-out effect to complete
    *
    *   @note This functions works only when music is playing and
    *           no fading is already set to fade out
    */
    void fadeOut(int ms);

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
    *   @fn ~LX_Music(void)
    *   Destroy the instance
    */
    ~LX_Music();
};


};

#endif // LX_MUSIC_H_INCLUDED
