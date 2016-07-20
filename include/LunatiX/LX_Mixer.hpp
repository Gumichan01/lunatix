#ifndef LX_MIXER_H_INCLUDED
#define LX_MIXER_H_INCLUDED


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
*	@file LX_Mixer.hpp
*	@brief The mixer library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <SDL2/SDL_mixer.h>

#define LX_MIXER_AUDIO_FREQUENCY 44100      /**< The default audio frequency             */
#define LX_MIXER_STEREO_SOUND 2             /**< The stereo variable for the mix module  */
#define LX_MIXER_MONO_SOUND 1               /**< The mono variable for the mix module    */
#define LX_MIXER_DEFAULT_CHUNKSIZE 1024     /**< The default chunsize for the mix module */

#define LX_MIXER_EFFECT_LOUD 255            /**< Loud (for effect functions)    */
#define LX_MIXER_EFFECT_SILENCE 0           /**< Silence (for effect functions) */
#define LX_MIXER_EFFECT_NO_DISTANCE 0       /**< The distance between the source and the listener */
#define LX_MIXER_EFFECT_NO_ANGLE 0          /**< The angle between the source and the front */


namespace LX_FileIO
{
class LX_FileBuffer;
};


/**
*   @namespace LX_Mixer
*   @brief The mixer module
*/
namespace LX_Mixer
{

class LX_Music;
class LX_Chunk;

/* == Volume == */

/**
*   @fn void setOverallVolume(unsigned short volume)
*
*   Set the overall volume
*
*   @param volume the volume between 0 and 100
*
*   @note if volume > 100, then the overall volume is set to 100
*/
void setOverallVolume(unsigned short volume);

/**
*   @fn void setMusicVolume(unsigned short pvolume)
*
*   Set the music volume in percentage of the overall volume
*
*   @param pvolume the volume of the music in percentage of the overall volume
*
*   @note If the overall volume is 60 and pvolume is 50%, the music volume
*         is 50 * 60 / 100.
*   @note The music volume ca be get using ::getMusicVolume()
*/
void setMusicVolume(unsigned short pvolume);

/**
*   @fn void setFXVolume(unsigned short pvolume)
*
*   Set the FX volume in percentage of the overall volume
*
*   @param pvolume the volume of the music in percentage of the overall volume
*
*   @note Example:
*         If the overall volume is 60 and pvolume is 50%, the FX volume
*         is 50 * 60 / 100.
*   @note The FX volume ca be get using ::getFXVolume()
*/
void setFXVolume(unsigned short pvolume);

/**
*   @fn unsigned short getOverallVolume()
*
*   Get the overall volume
*
*   @return The overall volume
*/
unsigned short getOverallVolume();

/**
*   @fn unsigned short getMusicVolume()
*
*   Get the music volume
*
*   @return The music volume
*/
unsigned short getMusicVolume();

/**
*   @fn unsigned short getFXVolume()
*
*   Get the FX volume
*
*   @return The FX volume
*/
unsigned short getFXVolume();

/* == Music and chunk == */

/**
*   @fn LX_Music * loadMusic(std::string filename)
*
*   Load the music according to the file name
*
*   @param filename The name of the music file
*
*   @return A valid instance of LX_Music
*   @note This function creates a new instance of LX_Music.
*           So do not forget to destroy it.
*/
LX_Music * loadMusic(std::string filename);

/**
*   @fn LX_Music * loadMusic(UTF8string& filename)
*
*   Load the music according to the file name
*
*   @param filename The name of the music file (utf-8)
*
*   @return A valid instance of LX_Music
*   @note This function creates a new instance of LX_Music.
*           So do not forget to destroy it.
*/
LX_Music * loadMusic(UTF8string& filename);

/**
*   @fn LX_Chunk * loadSample(std::string filename)
*
*   Create a new LX_Chunk instance from a WAV file
*
*   @param filename The name of the sample file
*
*   @return A valid instance of LX_Chunk
*   @note This function creates a new instance of LX_Chunk.
*           So do not forget to destroy it.
*/
LX_Chunk * loadSample(std::string filename);

/**
*   @fn LX_Chunk * loadSample(UTF8string& filename)
*
*   Create a new LX_Chunk instance from a WAV file
*
*   @param filename The name of the sample file
*
*   @return A valid instance of LX_Chunk
*   @note This function creates a new instance of LX_Chunk.
*           So do not forget to destroy it.
*/
LX_Chunk * loadSample(UTF8string& filename);

/**
*   @fn LX_Chunk * loadSample(LX_FileIO::LX_FileBuffer *file)
*
*   Create a new LX_Chunk instance from a file buffer
*
*   @param file The file buffer
*
*   @return A valid instance of LX_Chunk if the file buffer is valid
*           a null pointer otherwise
*
*   @note   This function creates a new instance of LX_Chunk.
*           So do not forget to destroy it.
*/
LX_Chunk * loadSample(LX_FileIO::LX_FileBuffer *file);

/**
*   @fn void setMusicPosition(double pos)
*   Set the position of the currently playing song from the beginning
*
*   @param pos The position to play from, in second
*
*   @note This function does not works on every music sources.
*   @note Here are the music sources available:
*         - MOD
*         - OGG
*         - MP3
*/
void setMusicPosition(double pos);

/**
*   @fn int allocateChannels(int num)
*
*   Set the number of channel to use.
*
*   @param num The number of channels to allocate
*   @return The number of channels allocated
*
*   @note   If num is 0, then all channels will be freed.
*   @note   A negative number do nothing,
*           it just returns the number of allocated channels.
*   @note   If num is less than the current number of channels,
*           then the higher channels will be stopped, freed, and not mixed.
*/
int allocateChannels(int num);

/**
*   @fn int reserveChannels(int numchans)
*
*   Set the number of channel to reserve.
*
*   @param numchans The number of channels to reserve
*
*   @return The number of channels reserved
*   @note If num is 0, then all channels will be unreserved
*/
int reserveChannels(int numchans);

/**
*   @fn bool groupChannel(int chan, int tag)
*
*   Add a channel to a specific group
*
*   @param chan The channel to assign the tag
*   @param tag The tag that define the group to put the channel. Positive value
*
*   @return TRUE on success, FALSE otherwise
*   @note Setting -1 in tag put the channel in the default group
*/
bool groupChannel(int chan, int tag);

/**
*   @fn int groupChannels(int chan, int tag)
*
*   Add a channel to a specific group
*
*   @param from First Channel number of channels to assign tag to. Must be less or equal to to
*   @param to Last Channel number of channels to assign tag to. Must be greater or equal to from
*   @param tag The tag that define the group to put the channel. Positive value
*
*   @return The number of tagged channels on success.
*   @note If that number is less than to-from+1 then
*           some channels were no tagged because they didn't exist
*   @note Setting -1 in tag reset the group to the default channel
*/
int groupChannels(int from, int to, int tag);

/**
*   @fn int groupCount(int tag)
*
*   Get the number of channels in the group specifiedby the tag
*
*   @param tag The group id
*
*   @return The number of channels found in the group. This function never fails
*   @note Setting -1 in tag will count all channels
*/
int groupCount(int tag);

/**
*   @fn void pause(int channel)
*
*   Pause the channel
*
*   @param channel The channel to pause
*   @note If channel is -1, then all channels will be paused
*/
void pause(int channel);

/**
*   @fn void resume(int channel)
*
*   Unpause the channel
*
*   @param channel The channel to resume playing
*   @note If channel is -1, then all channels will be unpaused
*/
void resume(int channel);

/**
*   @fn void haltChannel(int channel)
*
*   Halt the channel playback
*
*   @param channel The channel to stop playing
*   @note If channel is -1, then all channels will be stopped
*/
void haltChannel(int channel);

/**
*   @fn void expireChannel(int channel, int ticks)
*
*   Halt the channel playback after some milliseconds
*
*   @param channel The channel to stop playing
*   @param ticks The time in millisecond
*   @note If channel is -1, then all channels will be stopped
*/
void expireChannel(int channel, int ticks);

/**
*   @fn int isPlaying(int channel)
*
*   Check if the channel is playing
*
*   @param channel The channel to test
*   @return 0 If the channel is not playing, 1 otherwise
*
*   @note If channel is -1, then all channels will be tested
*           and the number of channels playing is returned
*/
int isPlaying(int channel);

/**
*   @fn int isPaused(int channel)
*
*   Check if the channel is paused
*
*   @param channel The channel to test
*   @return 0 If the channel is not paused, 1 otherwise
*
*   @note If channel is -1, then all channels will be tested
*           and the number of aused channels is returned
*/
int isPaused(int channel);


/* == Effects == */

/**
*   @fn void fadeInMusic(LX_Music& music,int ms)
*
*   Fade in the loaded Music over some milliseconds of time
*
*   @param music The music to fade in
*   @param ms Milliseconds for the fade-in effect to complete
*
*   @note fadeInMusic starts playing the music with the fade-in effect.
*         It is not necessary to call LX_Music::play() if this function is called
*
*   @note Any previous music will be halted, or if it is fading out
*           it will wait (blocking) for the fade to complete
*/
void fadeInMusic(LX_Music& music,int ms);
/**
*   @fn void fadeOutMusic(int ms)
*
*   Fade out the loaded Music over some milliseconds of time
*
*   @param ms Milliseconds for the fade-out effect to complete
*
*   @note This functions works only when music is playing and
*           no fading is already set to fade out
*/
void fadeOutMusic(int ms);

/**
*   @fn void setPanning(Uint8 left,Uint8 right)
*
*   Set the panning, increasing of decreasing the volume on the left or the right
*
*   @param left The volume of the left audio channel (0 - 255)
*   @param right The volume of the right audio channel (0 - 255)
*
*   @note This function only works on stereo audio. So the call will have no effect
*         or fail if it is done on mono audio.
*   @note The easiest way to do true panning is to call setPanning(left, 254 - left),
*         so that the total volume is correct, if you consider
*         the maximum volume to be 127 per channel for center,
*         or 254 max for left, this works, but about halves the effective volume.
*   @note To unregister this effect, use this function with 255 as left and right value
*           or simply use LX_Mixer::removePanning().
*/
void setPanning(Uint8 left,Uint8 right);
/**
*   @fn void removePanning(int channel)
*   Remove the panning effect
*/
void removePanning();

// 3D Position
/**
*   @fn void setPosition(Sint16 angle)
*
*   Set the virtual position of the audio source.
*
*   @param angle The angle betwwen 0 and 360, larger angles are reduced using angle % 360
*   @note This function call setPosition(angle,LX_MIXER_EFFECT_NO_DISTANCE)
*/
void setPosition(Sint16 angle);
/**
*   @fn void setPosition(Sint16 angle, Uint8 distance)
*
*   Set the virtual position of the audio source.
*
*   @param angle The angle betwwen 0 and 360, larger angles are reduced using angle % 360
*   @param distance The distance between the source and the listener
*/
void setPosition(Sint16 angle, Uint8 distance);
/**
*   @fn void resetPosition()
*
*   Reset the virtual position of the audio source.
*/
void resetPosition();

// Reverse stereo
/**
*   @fn int reverseStereo(bool flip)
*
*   Reverse the left and right audio channels.
*
*   @param flip TRUE to set the effect, FALSE to unregister the effect
*   @note If you want to unregister the effect on a channel, set false as flip
*/
void reverseStereo(bool flip);

// Distance

/**
*   @fn void setDistance(Uint8 distance)
*
*   Set the distance to all channels
*
*   @param distance The virtual distance between the user and the source
*/
void setDistance(Uint8 distance);

};

#endif // LX_MIXER_H_INCLUDED
