
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

#ifndef MIX_H_INCLUDED
#define MIX_H_INCLUDED

/**
*   @file Mixer.hpp
*   @brief The mixer library
*   @author Luxon Jean-Pierre(Gumichan01)
*/

#include <Lunatix/utils/utf8_string.hpp>


namespace lx
{

namespace FileIO
{
class FileBuffer;
}

}


namespace lx
{

/**
*   @ingroup Audio
*   @namespace lx::Mixer
*   @brief The audio mixer library
*
*   The mixer handles sound mixing and sound effect processing.
*   It is possible to play several samples and music.
*
*   ## Types of sound ##
*
*   There are two classes that handles each type of sound:
*   - The lx::Mixer::Chunk structure represents a sample.
*   - The lx::Mixer::Music structure represents a piece of music,
*     something that can be played for an extended period of time, usually repeated.
*
*   It's important to remember that you can play multiple samples at once,
*   but you can only play one music at a time.
*
*
*   ## Effects ##
*
*   Different sound effects can be applied on one or sereval channels
*   The effect defined in these following functions:
*   ```
*   - setPanning()
*   - setPosition()
*   - setDistance()
*   - reverseStereo()
*   ```
*   is set as a post-mix processing, i.e. the post-mix processor runs
*   after every specific post-mixers set by the functions listed before.
*   If a mix processor has been defined for a specific channel
*   for one of these functions, so this processor is run before every post-mixers.
*
*   Example:
*   ```
*   int chan = 5;                           // channel number
*   lx::Mixer::Chunk chunk("test.wav");
*   lx::Mixer::setDistance(100);             // distance as post-processing effect
*   lx::Mixer::setPanning(55,200);           // panning as post-processing effect
*   lx::Mixer::setPanning(chan,255,0);       // panning on a specific channel
*   chunk.play(chan);
*   //  So the order of post-mix processing is:
*   //    ① panning on channel #5
*   //    ② panning (post-processing)
*   //    ③ distance (post-processing)
*   ```
*
*   ## Supported formats ##
*
*   It supports playing music and sound samples from the following formats:
*   - WAVE/RIFF (.wav)
*   - AIFF (.aiff)
*   - VOC (.voc)
*   - MOD (.mod .xm .s3m .669 .it .med and more) requiring libmikmod on system
*   - MIDI (.mid) using timidity or native midi hardware
*   - OggVorbis (.ogg) requiring ogg/vorbis libraries on system
*   - MP3 (.mp3) requiring SMPEG or MAD library on system
*   - FLAC (.flac) requiring the FLAC library on system
*
*   @warning In order to use this namespace, the *audio* flag
*   in the configuration file must be set to 1, otherwise the behaviour of
*   the library is undefined.
*
*/
namespace Mixer
{

class Music;
class Chunk;

/**
*   @struct MixerEffectType
*   @brief Type of effect
*/
struct MixerEffectType final
{
    bool panning = false;           /**< Panning        */
    bool position = false;          /**< Position       */
    bool distance = false;          /**< Distance       */
    bool reverse_stereo = false;    /**< Reverse Stereo */

    MixerEffectType() = default;
    MixerEffectType( const MixerEffectType& ) = default;
    MixerEffectType& operator =( const MixerEffectType& ) = default;
};


/**
*   @struct MixerEffect
*   @brief Mixer effect
*/
struct MixerEffect final
{
    MixerEffectType type;           /**< Effect type            */
    uint8_t pan_left = 0;           /**< Left panning           */
    uint8_t pan_right = 0;          /**< Right panning          */
    int16_t pos_angle = 0;          /**< Angle (position)       */
    uint8_t pos_distance = 0;       /**< Distance (position)    */
    uint8_t distance = 0;           /**< Distance               */
    bool rev_stereo = false;        /**< Reverse stereo         */
    int loops = 0;                  /**< Loops                  */

    MixerEffect();
};

/* == Volume == */

/**
*   @fn void setOverallVolume(unsigned short volume) noexcept
*
*   Set the overall volume
*
*   @param [in] volume the volume between 0 and 100
*
*   @note if volume > 100, then the overall volume is set to 100
*/
void setOverallVolume( unsigned short volume ) noexcept;
/**
*   @fn void setMusicVolume(unsigned short pvolume) noexcept
*
*   Set the music volume in percentage of the overall volume
*
*   @param [in] pvolume the volume of the music in percentage of the overall volume
*
*   @note If the overall volume is 60 and pvolume is 50%, the music volume
*        is 50 * 60 / 100.
*   @note The music volume ca be get using ::getMusicVolume()
*/
void setMusicVolume( unsigned short pvolume ) noexcept;
/**
*   @fn void setFXVolume(unsigned short pvolume) noexcept
*
*   Set the FX volume in percentage of the overall volume
*
*   @param [in] pvolume the volume of the music in percentage of the overall volume
*
*   @note Example:
*        If the overall volume is 60 and pvolume is 50%, the FX volume
*        is 50 * 60 / 100.
*   @note The FX volume ca be get using ::getFXVolume()
*/
void setFXVolume( unsigned short pvolume ) noexcept;

/**
*   @fn unsigned short getOverallVolume() noexcept
*   Get the overall volume
*   @return The overall volume
*/
unsigned short getOverallVolume() noexcept;
/**
*   @fn unsigned short getMusicVolume() noexcept
*   Get the music volume
*   @return The music volume
*/
unsigned short getMusicVolume() noexcept;
/**
*   @fn unsigned short getFXVolume() noexcept
*   Get the FX volume
*   @return The FX volume
*/
unsigned short getFXVolume() noexcept;


/* == Music and chunk == */

/**
*   @fn Chunk * loadSample(lx::FileIO::FileBuffer& file)
*
*   Create a new Chunk instance from a file buffer
*
*   @param [in] file The file buffer
*
*   @return A valid instance of Chunk if the file buffer is valid
*          a null pointer otherwise
*
*   @note   This function creates a new instance of Chunk.
*          So do not forget to destroy it.
*
*   @exception MixerException On failure
*/
Chunk * loadSample( lx::FileIO::FileBuffer& file );

/**
*   @fn void setMusicPosition(double pos) noexcept
*   Set the position of the currently playing song from the beginning
*
*   @param [in] pos The position to play from, in second
*
*   @note This function does not works on every music sources.
*   @note Here are the music sources available:
*        - MOD
*        - OGG
*        - MP3
*/
void setMusicPosition( double pos ) noexcept;

/**
*   @fn int allocateChannels(int num) noexcept
*
*   Set the number of channel to use.
*
*   @param [in] num The number of channels to allocate
*   @return The number of channels allocated
*
*   @note   If *num* is 0, then all channels will be freed.
*   @note   A negative number do nothing,
*          it just returns the number of allocated channels.
*   @note   If *num* is less than the current number of channels,
*          then the higher channels will be stopped, freed, and not mixed.
*/
int allocateChannels( int num ) noexcept;
/**
*   @fn int reserveChannels(int numchans) noexcept
*
*   Set the number of channel to reserve.
*
*   @param [in] numchans The number of channels to reserve
*
*   @return The number of channels reserved
*   @note If *num* is 0, then all channels will be unreserved
*/
int reserveChannels( int numchans ) noexcept;

/**
*   @fn bool groupChannel(int chan, int tag) noexcept
*
*   Add a channel to a specific group
*
*   @param [in] chan The channel to assign the tag
*   @param [in] tag The tag that define the group to put the channel. Positive value
*
*   @return TRUE on success, FALSE otherwise
*   @note Setting -1 in *tag* put the channel in the default group
*/
bool groupChannel( int chan, int tag ) noexcept;
/**
*   @fn int groupChannels(int from, int to, int tag) noexcept
*
*   Add a channel to a specific group
*
*   @param [in] from First Channel number of channels to assign tag to. Must be less or equal to to
*   @param [in] to Last Channel number of channels to assign tag to. Must be greater or equal to from
*   @param [in] tag The tag that define the group to put the channel. Positive value
*
*   @return The number of tagged channels on success.
*   @note If that number is less than to-from+1 then
*          some channels were no tagged because they didn't exist
*   @note Setting -1 in *tag* reset the group to the default channel
*/
int groupChannels( int from, int to, int tag ) noexcept;

/**
*   @fn int groupCount(int tag) noexcept
*
*   Get the number of channels in the group specified by the tag
*
*   @param [in] tag The group id
*
*   @return The number of channels found in the group. This function never fails
*   @note Setting -1 in *tag* will count all channels
*/
int groupCount( int tag ) noexcept;
/**
*   @fn int channelAvailable(int tag) noexcept
*
*   Get the first available (not playing) channel in the group specified by the tag
*
*   @param [in] tag The group id to look for the available channel
*
*   @return The channel id on success. -1 if no channel is available.
*   @note Setting -1 in *tag* will search all channels
*/
int channelAvailable( int tag ) noexcept;

/**
*   @fn bool groupPlayChunk( Chunk& chunk, int tag ) noexcept
*
*   Play the chunk on a channel of the group specified by the tag
*
*   @param [in] chunk The chunk to play
*   @param [in] tag The group id to look for the channel for playing the chunk on
*
*   @return TRUE if the chunk can be played, FALSE if no channel is available
*
*   @note If the group is empty, any unreserved channels in the default
*        group is selected and the chunk is played on it
*   @note If no channel of the group is available for playing, the oldest
*        playing channel is chosen. So, it is halted, and is used to play the chunk on
*/
bool groupPlayChunk( Chunk& chunk, int tag ) noexcept;
/**
*   @fn bool groupPlayChunk(Chunk& chunk, int tag, const MixerEffect& effect) noexcept
*
*   Play the chunk on a channel of the group specified by the tag, with an effect to apply
*
*   @param [in] chunk The chunk to play
*   @param [in] tag The group id to look for the channel for playing the chunk on
*   @param [in] effect The structure that provides information about the effects to use
*
*   @return TRUE if the chunk can be played, FALSE if no channel is available
*
*   @note If the group is empty, any unreserved channels in the default
*        group is selected and the chunk is played on it
*   @note If no channel of the group is available for playing, the oldest
*        playing channel is chosen. So, it is halted, and is used to play the chunk on
*/
bool groupPlayChunk( Chunk& chunk, int tag, const MixerEffect& effect ) noexcept;

/**
*   @fn void pause(int channel) noexcept
*
*   Pause the channel
*
*   @param [in] channel The channel to pause
*   @note If channel is -1, then all channels will be paused
*/
void pause( int channel ) noexcept;
/**
*   @fn void resume(int channel) noexcept
*
*   Unpause the channel
*
*   @param [in] channel The channel to resume playing
*   @note If channel is -1, then all channels will be unpaused
*/
void resume( int channel ) noexcept;

/**
*   @fn void haltChannel(int channel) noexcept
*
*   Halt the channel playback
*
*   @param [in] channel The channel to stop playing
*   @note If channel is -1, then all channels will be stopped
*/
void haltChannel( int channel ) noexcept;
/**
*   @fn void expireChannel(int channel, int ticks) noexcept
*
*   Halt the channel playback after some milliseconds
*
*   @param [in] channel The channel to stop playing
*   @param [in] ticks The time in millisecond
*   @note If channel is -1, then all channels will be stopped
*/
void expireChannel( int channel, int ticks ) noexcept;

/**
*   @fn bool isPlaying(int channel) noexcept
*
*   Check if the channel is playing
*
*   @param [in] channel The channel to test
*   @return True If the channel is playing, False otherwise
*
*   @pre channel != -1
*   @note If channel is -1, then the behaviour is undefined
*   @sa playingChannels
*/
bool isPlaying( int channel ) noexcept;
/**
*   @fn bool isPaused(int channel) noexcept
*
*   Check if the channel is paused
*
*   @param [in] channel The channel to test
*   @return True If the channel is paused, False otherwise
*
*   @pre channel != -1
*   @note If channel is -1, then the behaviour is undefined
*   @sa pausedChannels
*/
bool isPaused( int channel ) noexcept;
/**
*   @fn int playingChannels() noexcept
*
*   Get the number of channel used to play a sample
*
*   @return The number of channels playing
*/
int playingChannels() noexcept;
/**
*   @fn int pausedChannels() noexcept
*
*   Get the number of paused channel
*
*   @return The number of paused channels
*/
int pausedChannels() noexcept;

/* == Effects == */

/**
*   @fn void fadeInMusic(Music& music, int ms) noexcept
*
*   Fade in the loaded Music over some milliseconds of time
*
*   @param [in] music The music to fade in
*   @param [in] ms Milliseconds for the fade-in effect to complete
*
*   @note fadeInMusic starts playing the music with the fade-in effect.
*        It is not necessary to call Music::play() if this function is called
*
*   @note Any previous music will be halted, or if it is fading out
*          it will wait (blocking) for the fade to complete
*/
void fadeInMusic( Music& music, int ms ) noexcept;
/**
*   @fn void void fadeInMusicPos(Music& music,int ms, int pos) noexcept
*
*   Fade in the loaded Music over some milliseconds of time from the position
*
*   @param [in] music The music to fade in
*   @param [in] ms Milliseconds for the fade-in effect to complete
*   @param [in] pos The position to start the music
*
*   @note fadeInMusicPos starts playing the music with the fade-in effect.
*        It is not necessary to call Music::play() if this function is called
*
*   @note Any previous music will be halted, or if it is fading out
*          it will wait (blocking) for the fade to complete
*/
void fadeInMusicPos( Music& music, int ms, int pos ) noexcept;
/**
*   @fn void fadeOutMusic(int ms) noexcept
*
*   Fade out the loaded Music over some milliseconds of time
*
*   @param [in] ms Milliseconds for the fade-out effect to complete
*
*   @note This functions works only when music is playing and
*          no fading is already set to fade out
*/
void fadeOutMusic( int ms ) noexcept;

/**
*   @fn void setPanning(uint8_t left, uint8_t right) noexcept
*
*   Set the panning, increasing of decreasing the volume on the left or the right,
*   as a post-processing effect
*
*   @param [in] left The volume of the left audio channel (0 - 255)
*   @param [in] right The volume of the right audio channel (0 - 255)
*
*   @note 1 — This function set the effect on every mixing channels.
*        The other signature can be used to set the effect on a specific channel.
*   @note 2 — The easiest way to do true panning is to call setPanning(left, 254 - left),
*        so that the total volume is correct, if you consider
*        the maximum volume to be 127 per channel for center,
*        or 254 max for left, this works, but about halves the effective volume.
*   @note 3 — To unregister this effect, use this function with 255 as left and right value
*        or simply use lx::Mixer::removePanning().
*/
void setPanning( uint8_t left, uint8_t right ) noexcept;
/**
*   @fn void setPanning(int chan, uint8_t left, uint8_t right) noexcept
*
*   Set the panning, increasing of decreasing the volume on the left or the right,
*   on a specific mixing channel
*
*   @param [in] chan The channel
*   @param [in] left The volume of the left audio channel (0 - 255)
*   @param [in] right The volume of the right audio channel (0 - 255)
*
*   @note 1 — The easiest way to do true panning is to call setPanning(left, 254 - left),
*        so that the total volume is correct, if you consider
*        the maximum volume to be 127 per channel for center,
*        or 254 max for left, this works, but about halves the effective volume.
*   @note 2 — To unregister this effect, use this function with 255 as left and right value
*        or simply use lx::Mixer::removePanning(int chan).
*/
void setPanning( int chan, uint8_t left, uint8_t right ) noexcept;
/**
*   @fn void removePanning() noexcept
*   Remove the panning effect applied on every channels
*/
void removePanning() noexcept;
/**
*   @fn void removePanning(int chan) noexcept
*   Remove the panning effect on a specific channel
*   @param [in] chan The channel to remove the effect from
*   @note This function also remove the post-processing effects
*/
void removePanning( int chan ) noexcept;

// 3D Position

/**
*   @fn void setPosition(int16_t angle) noexcept
*
*   Set the virtual position of the audio source.
*
*   @param [in] angle The angle between 0 and 360, larger angles are reduced using angle % 360
*   @note This function call setPosition(angle, MIX_FX_NO_distance)
*/
void setPosition( int16_t angle ) noexcept;
/**
*   @fn void setPosition(int16_t angle, uint8_t distance) noexcept
*
*   Set the virtual position of the audio source (post-processing).
*
*   @param [in] angle The angle between 0 and 360, larger angles are reduced using angle % 360
*   @param [in] distance The distance between the source and the listener
*/
void setPosition( int16_t angle, uint8_t distance ) noexcept;
/**
*   @fn void setPosition(int chan, int16_t angle, uint8_t distance) noexcept
*
*   Set the virtual position of the audio source in a specific channel.
*
*   @param [in] chan The channel
*   @param [in] angle The angle between 0 and 360, larger angles are reduced using angle % 360
*   @param [in] distance The distance between the source and the listener
*/
void setPosition( int chan, int16_t angle, uint8_t distance ) noexcept;
/**
*   @fn void resetPosition() noexcept
*   Reset the virtual position of the audio source.
*/
void resetPosition() noexcept;
/**
*   @fn void resetPosition(int chan) noexcept
*   Reset the virtual position of the audio source.
*   @param [in] chan The channel
*/
void resetPosition( int chan ) noexcept;

// Reverse stereo

/**
*   @fn void reverseStereo(bool flip) noexcept
*
*   Reverse the left and right audio channels.
*
*   @param [in] flip TRUE to set the effect, FALSE to unregister the effect
*   @note If you want to unregister the effect on a channel, set flip as false
*/
void reverseStereo( bool flip ) noexcept;
/**
*   @fn void reverseStereo(int chan, bool flip) noexcept
*
*   Reverse the left and right audio channels on a specific mix channel
*
*   @param [in] chan The channel to reverse the stereo sound from
*   @param [in] flip TRUE to set the effect, FALSE to unregister the effect
*   @note If you want to unregister the effect on a channel, set flip as false
*/
void reverseStereo( int chan, bool flip ) noexcept;

// Distance

/**
*   @fn void setDistance(uint8_t distance) noexcept
*   Set the distance to all channels
*   @param [in] distance The virtual distance between the user and the source
*/
void setDistance( uint8_t distance ) noexcept;
/**
*   @fn void setDistance(int chan, uint8_t distance) noexcept
*   Set the distance to a specific channel
*   @param [in] chan The channel
*   @param [in] distance The virtual distance between the user and the source
*/
void setDistance( int chan, uint8_t distance ) noexcept;

}   // Mixer

}   // lx

#endif // MIX_H_INCLUDED
