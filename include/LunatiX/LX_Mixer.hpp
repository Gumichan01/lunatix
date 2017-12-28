
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_MIXER_H_INCLUDED
#define LX_MIXER_H_INCLUDED

/**
*   @file LX_Mixer.hpp
*   @brief The mixer library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*
*/

#include <LunatiX/utils/utf8_string.hpp>

const int LX_MIXER_AUDIO_FREQUENCY = 44100;     /**< The default audio frequency             */
const int LX_MIXER_STEREO_SOUND = 2;            /**< The stereo variable for the mix namespace  */
const int LX_MIXER_MONO_SOUND = 1;              /**< The mono variable for the mix namespace    */
const int LX_MIXER_DEFAULT_CHUNKSIZE = 1024;    /**< The default chunsize for the mix namespace */

const uint8_t LX_MIXER_EFFECT_LOUD = 255;        /**< Loud (for effect functions)    */
const uint8_t LX_MIXER_EFFECT_SILENCE = 0;       /**< Silence (for effect functions) */
const uint8_t LX_MIXER_EFFECT_NO_DISTANCE = 0;   /**< The distance between the source and the listener */
const uint16_t LX_MIXER_EFFECT_NO_ANGLE = 0;     /**< The angle between the source and the front */


namespace LX_FileIO
{
class LX_FileBuffer;
}


/**
*   @ingroup Audio
*   @namespace LX_Mixer
*   @brief The audio namespace
*
*   It handles sound mixing and effect processing
*
*   @note The effect defined in these following functions:
*
*               - setPanning()
*               - setPosition()
*               - setDistance()
*               - reverseStereo()
*
*   is set as a post-mix processing, i.e. the post-mix processor runs
*   after every specific post-mixers set by the functions listed before.
*
*   If a mix processor has been defined for a specific channel
*   for one of these functions, so this processor is run before every post-mixers.
*
*   Example:
*
*               int chan = 5;                           // channel number
*               LX_Mixer::LX_Chunk chunk("test.wav");
*               LX_Mixer::setDistance(100);             // distance as post-processing effect
*               LX_Mixer::setPanning(55,200);           // panning as post-processing effect
*               LX_Mixer::setPanning(chan,255,0);       // panning on a specific channel
*               chunk.play(chan);
*               //  So the order of post-mix processing is:
*               //    ① panning on channel #5
*               //    ② panning (post-processing)
*               //    ③ distance (post-processing)
*
*
*   @warning In order to use this namespace, the *audio* flag
*   in the configuration file must be set to 1, otherwise the behaviour of
*   the library is undefined.
*
*/
namespace LX_Mixer
{

class LX_Music;
class LX_Chunk;

/**
*   @struct LX_MixerEffectType
*   @brief Type of effect
*/
struct LX_MixerEffectType
{
    bool LX_PANNING;        /**< Panning    */
    bool LX_POSITION;       /**< Position   */
    bool LX_DISTANCE;       /**< Distance   */
    bool LX_STEREO;         /**< Stereo     */
};


/**
*   @struct LX_MixerEffect
*   @brief Mixer effect
*/
struct LX_MixerEffect
{
    LX_MixerEffectType type;    /**< Effect type    */

    // Panning
    uint8_t pan_left;           /**< Left panning   */
    uint8_t pan_right;          /**< Right panning  */

    // Position
    int16_t pos_angle;          /**< Angle (position)       */
    uint8_t pos_distance;       /**< Distance (position)    */

    // Distance
    uint8_t distance;           /**< Distance       */

    // Stereo
    bool rev_stereo;            /**< Reverse stereo */

    // Loop
    int loops;                  /**< Loops          */

    LX_MixerEffect() noexcept;
    LX_MixerEffect(const LX_MixerEffect& st) noexcept;
    LX_MixerEffect& operator = (const LX_MixerEffect& st) noexcept;
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
void setOverallVolume(unsigned short volume) noexcept;
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
void setMusicVolume(unsigned short pvolume) noexcept;
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
void setFXVolume(unsigned short pvolume) noexcept;

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
*   @fn LX_Chunk * loadSample(LX_FileIO::LX_FileBuffer& file)
*
*   Create a new LX_Chunk instance from a file buffer
*
*   @param [in] file The file buffer
*
*   @return A valid instance of LX_Chunk if the file buffer is valid
*          a null pointer otherwise
*
*   @note   This function creates a new instance of LX_Chunk.
*          So do not forget to destroy it.
*
*   @exception LX_MixerException On failure
*/
LX_Chunk * loadSample(LX_FileIO::LX_FileBuffer& file);

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
void setMusicPosition(double pos) noexcept;

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
int allocateChannels(int num) noexcept;
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
int reserveChannels(int numchans) noexcept;

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
bool groupChannel(int chan, int tag) noexcept;
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
int groupChannels(int from, int to, int tag) noexcept;

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
int groupCount(int tag) noexcept;
/**
*   @fn int channelAvailable(int tag) noexcept
*
*   Get the first available (not playing) channel in the group specified by the tag
*
*   @param [in] tag The group id to look for the available channel
*
*   @return The channel id on success. -1 if no channel is available.
*/
int channelAvailable(int tag) noexcept;

/**
*   @fn bool groupPlayChunk(LX_Chunk& chunk, int tag, int loops = 0) noexcept
*
*   Play the chunk on a channel of the group specified by the tag
*
*   @param [in] chunk The chunk to play
*   @param [in] tag The group id to look for the channel for playing the chunk on
*   @param [in] loops Optional argument that specified the number of loop (default value = 0)
*
*   @return TRUE if the chunk can be played, FALSE if no channel is available
*
*   @note If the group is empty, any unreserved channels in the default
*        group is selected and the chunk is played on it
*   @note If no channel of the group is available for playing, the oldest
*        playing channel is chosen. So, it is halted, and is used to play the chunk on
*/
bool groupPlayChunk(LX_Chunk& chunk, int tag, int loops = 0) noexcept;

/**
*   @fn bool groupPlayChunk(LX_Chunk& chunk, int tag, const LX_MixerEffect effect) noexcept
*
*   Play the chunk on a channel of the group specified by the tag
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
bool groupPlayChunk(LX_Chunk& chunk, int tag, const LX_MixerEffect effect) noexcept;

/**
*   @fn void pause(int channel) noexcept
*
*   Pause the channel
*
*   @param [in] channel The channel to pause
*   @note If channel is -1, then all channels will be paused
*/
void pause(int channel) noexcept;
/**
*   @fn void resume(int channel) noexcept
*
*   Unpause the channel
*
*   @param [in] channel The channel to resume playing
*   @note If channel is -1, then all channels will be unpaused
*/
void resume(int channel) noexcept;

/**
*   @fn void haltChannel(int channel) noexcept
*
*   Halt the channel playback
*
*   @param [in] channel The channel to stop playing
*   @note If channel is -1, then all channels will be stopped
*/
void haltChannel(int channel) noexcept;
/**
*   @fn void expireChannel(int channel, int ticks) noexcept
*
*   Halt the channel playback after some milliseconds
*
*   @param [in] channel The channel to stop playing
*   @param [in] ticks The time in millisecond
*   @note If channel is -1, then all channels will be stopped
*/
void expireChannel(int channel, int ticks) noexcept;

/**
*   @fn int isPlaying(int channel) noexcept
*
*   Check if the channel is playing
*
*   @param [in] channel The channel to test
*   @return 0 If the channel is not playing, 1 otherwise
*
*   @note If channel is -1, then all channels will be tested
*          and the number of channels playing is returned
*/
int isPlaying(int channel) noexcept;
/**
*   @fn int isPaused(int channel) noexcept
*
*   Check if the channel is paused
*
*   @param [in] channel The channel to test
*   @return 0 If the channel is not paused, 1 otherwise
*
*   @note If channel is -1, then all channels will be tested
*          and the number of aused channels is returned
*/
int isPaused(int channel) noexcept;


/* == Effects == */

/**
*   @fn void fadeInMusic(LX_Music& music, int ms) noexcept
*
*   Fade in the loaded Music over some milliseconds of time
*
*   @param [in] music The music to fade in
*   @param [in] ms Milliseconds for the fade-in effect to complete
*
*   @note fadeInMusic starts playing the music with the fade-in effect.
*        It is not necessary to call LX_Music::play() if this function is called
*
*   @note Any previous music will be halted, or if it is fading out
*          it will wait (blocking) for the fade to complete
*/
void fadeInMusic(LX_Music& music, int ms) noexcept;
/**
*   @fn void void fadeInMusicPos(LX_Music& music,int ms, int pos) noexcept
*
*   Fade in the loaded Music over some milliseconds of time from the position
*
*   @param [in] music The music to fade in
*   @param [in] ms Milliseconds for the fade-in effect to complete
*   @param [in] pos The position to start the music
*
*   @note fadeInMusicPos starts playing the music with the fade-in effect.
*        It is not necessary to call LX_Music::play() if this function is called
*
*   @note Any previous music will be halted, or if it is fading out
*          it will wait (blocking) for the fade to complete
*/
void fadeInMusicPos(LX_Music& music, int ms, int pos) noexcept;
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
void fadeOutMusic(int ms) noexcept;

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
*        or simply use LX_Mixer::removePanning().
*/
void setPanning(uint8_t left, uint8_t right) noexcept;
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
*        or simply use LX_Mixer::removePanning(int chan).
*/
void setPanning(int chan, uint8_t left, uint8_t right) noexcept;
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
void removePanning(int chan) noexcept;

// 3D Position

/**
*   @fn void setPosition(int16_t angle) noexcept
*
*   Set the virtual position of the audio source.
*
*   @param [in] angle The angle between 0 and 360, larger angles are reduced using angle % 360
*   @note This function call setPosition(angle, LX_MIXER_EFFECT_NO_DISTANCE)
*/
void setPosition(int16_t angle) noexcept;
/**
*   @fn void setPosition(int16_t angle, uint8_t distance) noexcept
*
*   Set the virtual position of the audio source (post-processing).
*
*   @param [in] angle The angle between 0 and 360, larger angles are reduced using angle % 360
*   @param [in] distance The distance between the source and the listener
*/
void setPosition(int16_t angle, uint8_t distance) noexcept;
/**
*   @fn void setPosition(int chan, int16_t angle, uint8_t distance) noexcept
*
*   Set the virtual position of the audio source in a specific channel.
*
*   @param [in] chan The channel
*   @param [in] angle The angle between 0 and 360, larger angles are reduced using angle % 360
*   @param [in] distance The distance between the source and the listener
*/
void setPosition(int chan, int16_t angle, uint8_t distance) noexcept;
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
void resetPosition(int chan) noexcept;

// Reverse stereo

/**
*   @fn void reverseStereo(bool flip) noexcept
*
*   Reverse the left and right audio channels.
*
*   @param [in] flip TRUE to set the effect, FALSE to unregister the effect
*   @note If you want to unregister the effect on a channel, set flip as false
*/
void reverseStereo(bool flip) noexcept;
/**
*   @fn void reverseStereo(int chan, bool flip) noexcept
*
*   Reverse the left and right audio channels on a specific mix channel
*
*   @param [in] chan The channel to reverse the stereo sound from
*   @param [in] flip TRUE to set the effect, FALSE to unregister the effect
*   @note If you want to unregister the effect on a channel, set flip as false
*/
void reverseStereo(int chan, bool flip) noexcept;

// Distance

/**
*   @fn void setDistance(uint8_t distance) noexcept
*   Set the distance to all channels
*   @param [in] distance The virtual distance between the user and the source
*/
void setDistance(uint8_t distance) noexcept;
/**
*   @fn void setDistance(int chan, uint8_t distance) noexcept
*   Set the distance to a specific channel
*   @param [in] chan The channel
*   @param [in] distance The virtual distance between the user and the source
*/
void setDistance(int chan, uint8_t distance) noexcept;

}

#endif // LX_MIXER_H_INCLUDED
