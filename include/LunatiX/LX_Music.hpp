
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_MUSIC_H_INCLUDED
#define LX_MUSIC_H_INCLUDED

/**
*   @file LX_Music.hpp
*   @brief The music library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/LX_Sound.hpp>
#include <memory>


namespace libtagpp
{
class Tag;
}

namespace LX_Graphics
{
class LX_BufferedImage;
}

namespace LX_Mixer
{

/**
*   @struct LX_MusicTag
*   @brief High-level music metadata
*
*   MusicTag is a metadata structure that contains essential information
*   about a music (title, author, album, year, ...)
*
*   In comparison with *libtagpp::Tag*, MusicTag does not contain
*   low-level contents (track-gain, album-gain, bitrate, ...), but have
*   an image loaded from the audio file if it exists.
*/
struct LX_MusicTag
{
    UTF8string title;                   /**< Title  */
    UTF8string artist;                  /**< Artist */
    UTF8string album;                   /**< Album  */
    UTF8string year;                    /**< Year (2016, 2014/02/01)         */
    UTF8string track;                   /**< Track number ("1", "01", "1/4") */
    UTF8string genre;                   /**< Genre  */
    UTF8string format;                  /**< Format (MP3, OGG, FLAC, M4A)    */
    UTF8string duration;                /**< Duration, in HH:MM:SS format    */
    LX_Graphics::LX_BufferedImage *img; /**< Album cover, if it exists       */

    LX_MusicTag() noexcept;
    ~LX_MusicTag();
};

/**
*   @fn const LX_MusicTag getMusicInfoFrom(const UTF8string& u8file) noexcept
*   Get information about the music file
*   @param [in] u8file the music file to get metadata from
*   @return The metadata
*
*   @sa LX_MusicTag
*/
const LX_MusicTag getMusicInfoFrom(const UTF8string& u8file) noexcept;
/**
*   @fn const LX_MusicTag getMusicInfoFrom(const std::string& file) noexcept;
*   Get information about the music file
*   @param [in] file the music file to get metadata from
*   @return The metadata
*
*   @sa LX_MusicTag
*/
const LX_MusicTag getMusicInfoFrom(const std::string& file) noexcept;


class LX_Music_;

/**
*   @class LX_Music
*   @brief The music class
*/
class LX_Music : public virtual LX_Sound
{
    std::unique_ptr<LX_Music_> _mimpl;

    LX_Music(LX_Music& m) = delete;
    LX_Music& operator =(LX_Music& m) = delete;

public:

    /**
    *   @fn LX_Music(const std::string& filename)
    *   @exception LX_MixerException On failure
    */
    LX_Music(const std::string& filename);
    /**
    *   @fn LX_Music(const UTF8string& filename)
    *   @exception LX_MixerException On failure
    */
    LX_Music(const UTF8string& filename);

    /**
    *   @fn void fadeIn(int ms) noexcept
    *
    *   Fade in the current music over some milliseconds of time
    *
    *   @param [in] ms Milliseconds for the fade-in effect to complete
    *
    *   @note fadeIn starts playing the music with the fade-in effect.
    *         It is not necessary to call LX_Music::play() if this function is called
    *
    *   @note Any previous music will be halted, or if it is fading out
    *         it will wait (blocking) for the fade to complete
    */
    void fadeIn(int ms) noexcept;
    /**
    *   @fn void fadeInPos(int ms, int pos) noexcept
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
    *         it will wait (blocking) for the fade to complete
    */
    void fadeInPos(int ms, int pos) noexcept;
    /**
    *   @fn static void fadeOut(int ms) noexcept
    *
    *   Fade out the music over some milliseconds of time
    *
    *   @param [in] ms Milliseconds for the fade-out effect to complete
    *
    *   @note This functions works only when music is playing and
    *         no fading is already set to fade out
    */
    static void fadeOut(int ms) noexcept;

    /**
    *   @fn virtual bool play() noexcept
    *   Play the music specified in the LX_Music class
    *   @return TRUE on success, FALSE otherwise
    *
    *   @note This function internally calls play(int loops) with LX_MIXER_NOLOOP
    */
    virtual bool play() noexcept;
    /**
    *   @fn bool play(int loops) noexcept
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
    bool play(int loops) noexcept;
    /**
    *   @fn static void pause() noexcept
    *   Pause or resume the current music
    */
    static void pause() noexcept;
    /**
    *   @fn static void stop()
    *   Stop the music
    */
    static void stop() noexcept;

    /**
    *   @fn const libtagpp::Tag& getInfo() noexcept
    *   Get information about the current music
    *   @return The metadata
    *
    *   @note It provides low-level information about
    *   the file related to the music (bitrate, album-gain, ...)
    *
    *   @sa metaData()
    */
    const libtagpp::Tag& getInfo() noexcept;
    /**
    *   @fn const LX_MusicTag& metaData() noexcept
    *   Get essential information about the current music
    *   @return The metadata
    *
    *   @sa LX_MusicTag
    *   @sa getInfo()
    */
    const LX_MusicTag& metaData() noexcept;

    ~LX_Music();
};

}

#endif // LX_MUSIC_H_INCLUDED
