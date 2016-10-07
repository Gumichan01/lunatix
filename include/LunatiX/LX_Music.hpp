#ifndef LX_MUSIC_H_INCLUDED
#define LX_MUSIC_H_INCLUDED


/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_Music.hpp
*    @brief The music library
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include "LX_Sound.hpp"

#include <LunatiX/utils/libtagspp/libtagspp.hpp>
#include <SDL2/SDL_mixer.h>


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

    /// Constructor
    explicit LX_MusicException(std::string err);
    /// Copy constructor
    LX_MusicException(const LX_MusicException& me);

    /// Get the error message
    const char * what() const noexcept;

    /// Destructor
    ~LX_MusicException() noexcept;
};


/**
*   @class LX_Music
*   @brief The music class
*/
class LX_Music : public virtual LX_Sound
{
    Mix_Music *_music;
    libtagpp::Tag _tag;
    std::string _filename;

    LX_Music(LX_Music& m);
    LX_Music& operator =(LX_Music& m);

protected:

    bool load_(const std::string& filename);
    bool load_(const UTF8string& filename);

public:

    /**
    *   @fn LX_Music(const std::string& filename)
    *   @brief Constructor
    *
    *   @param [in] filename The music filename that will be loaded
    *   @exception LX_MusicException if the music cannot be created from the file
    */
    LX_Music(const std::string& filename);
    /**
    *   @fn LX_Music(const UTF8string& filename)
    *   @brief Constructor
    *
    *   @param [in] filename The music filename that will be loaded
    *   @exception LX_MusicException if the music cannot be created from the file
    */
    explicit LX_Music(const UTF8string& filename);

    /**
    *   @fn void fadeIn(int ms)
    *
    *   Fade in the current music over some milliseconds of time
    *
    *   @param [in] ms Milliseconds for the fade-in effect to complete
    *
    *   @note fadeIn starts playing the music with the fade-in effect.
    *         It is not necessary to call LX_Music::play() if this function is called
    *
    *   @note Any previous music will be halted, or if it is fading out
    *           it will wait (blocking) for the fade to complete
    */
    void fadeIn(int ms);
    /**
    *   @fn void fadeInPos(int ms,int pos)
    *
    *   Fade in the current music over some milliseconds of time
    *
    *   @param [in] ms Milliseconds for the fade-in effect to complete
    *   @param [in] pos The position to start the music
    *
    *   @note fadeInPos starts playing the music with the fade-in effect.
    *         It is not necessary to call LX_Music::play() if this function is called
    *
    *   @note Any previous music will be halted, or if it is fading out
    *           it will wait (blocking) for the fade to complete
    */
    void fadeInPos(int ms,int pos);
    /**
    *   @fn void fadeOut(int ms)
    *
    *   Fade out the music over some milliseconds of time
    *
    *   @param [in] ms Milliseconds for the fade-out effect to complete
    *
    *   @note This functions works only when music is playing and
    *           no fading is already set to fade out
    */
    void fadeOut(int ms);

    /**
    *   @fn bool play()
    *
    *   Play the music specified in the LX_Music class
    *
    *   @return TRUE on success, FALSE otherwise
    *
    *   @note This function internally calls play(int loops) with LX_MIXER_NOLOOP
    */
    bool play();
    /**
    *   @fn bool play(int loops)
    *
    *   Play the music specified in the LX_Music class
    *
    *   @param [in] loops The loop constant
    *
    *   @return TRUE on success,FALSE otherwise
    *
    *   @note If loops is set to LX_MIXER_NOLOOP, the music is played only once.
    *   @note If loops is set to LX_MIXER_LOOP, the music is played forever.
    */
    bool play(int loops);

    /**
    *   @fn void pause()
    *   Pause or resume the current music
    */
    void pause();

    /**
    *   @fn void stop()
    *   Stop the music
    */
    void stop();

    /**
    *   @fn const libtagpp::Tag& getInfo()
    *   Get information about the current file
    *   @return The metadata
    */
    const libtagpp::Tag& getInfo();

    /// Destructor
    ~LX_Music();
};

};

#endif // LX_MUSIC_H_INCLUDED
