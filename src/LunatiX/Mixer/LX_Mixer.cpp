

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
*	@file LX_Mixer.cpp
*	@brief The implementation of the mixer library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.7
*
*/

#include <LunatiX/LX_Music.hpp>
#include <LunatiX/LX_Chunk.hpp>
#include <LunatiX/LX_Mixer.hpp>
#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_FileIO.hpp>
#include <LunatiX/LX_FileBuffer.hpp>

using namespace LX_FileIO;


namespace LX_Mixer
{


/**
*   @fn LX_Music * loadMusic(std::string filename)
*
*   Load the music according to the file name
*
*   @param filename The name of the music file
*
*   @return A valid instance of LX_Music
*
*   @note This function creates a new instance of LX_Music.
*           So do not forget to destroy it.
*
*/
LX_Music * loadMusic(std::string filename)
{
    return new LX_Music(filename.c_str());
}



/**
*   @fn LX_Music * loadMusic(Mix_Music *mus)
*
*   Load the music according to the Mix_Music structure
*
*   @param mus The Mix_Music structure loaded
*
*   @return A valid instance of LX_Music
*
*   @note This function creates a new instance of LX_Music.
*           So do not forget to destroy it.
*
*/
LX_Music * loadMusic(Mix_Music *mus)
{
    return new LX_Music(mus);
}



/**
*   @fn LX_Chunk * loadSample(std::string filename)
*
*   Create a new LX_Chunk instance from a WAV file
*
*   @param filename The name of the sample file
*
*   @return A valid instance of LX_Chunk
*
*   @note This function creates a new instance of LX_Chunk.
*           So do not forget to destroy it.
*
*/
LX_Chunk * loadSample(std::string filename)
{
    return new LX_Chunk(filename.c_str());
}


/**
*   @fn LX_Chunk * loadSample(Mix_Chunk *ch)
*
*   Create a new LX_Chunk instance from a Mix_Chunk structure
*
*   @param ch The Mix_chunk
*
*   @return A valid instance of LX_Chunk
*
*   @note This function creates a new instance of LX_Chunk.
*           So do not forget to destroy it.
*
*/
LX_Chunk * loadSample(Mix_Chunk *ch)
{
    return new LX_Chunk(ch);
}


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
*
*/
LX_Chunk * loadSample(LX_FileIO::LX_FileBuffer *file)
{
    return (file == nullptr) ? nullptr:(new LX_Chunk(file));
}



/**
*   @fn int allocateChannels(int num)
*
*   Set the number of channel to use.
*
*   @param num The number of channels to allocate
*
*   @return The number of channels allocated
*
*   @note   If num is 0, then all channels will be freed.
*
*   @note   A negative number do nothing,
*           it just displays the number of allocated channels.
*
*   @note   If num is less than the current number of channels,
*           then the higher channels will be stopped, freed, and not mixed.
*
*/
int allocateChannels(int num)
{
    return Mix_AllocateChannels(num);
}



/**
*   @fn int reserveChannels(int numchans)
*
*   Set the number of channel to reserve.
*
*   @param numchans The number of channels to reserve
*
*   @return The number of channels reserved
*
*   @note If num is 0, then all channels will be unreserved
*
*/
int reserveChannels(int numchans)
{
    return Mix_ReserveChannels(numchans);
}



/**
*   @fn int channelVolume(int channel,int volume)
*
*   Set the channel volume to volume, from 0 to 128
*
*   @param channel the channel to set the volume in
*   @param volume
*
*   @return The previous volume setting
*
*   @note If the channel is -1, all channels will be set to the volume
*   @note If the volume is equals to -1, then the average volume is returned
*   @note If the new volume is greater than 128, the volume is set to 128
*   @note This value 128 is ht maximum value defined by the MIX_MAX_VOLUME macro
*
*/
int channelVolume(int channel,int volume)
{
    return Mix_Volume(channel,volume);
}



/**
*   @fn void pause(int channel)
*
*   Pause the channel
*
*   @param channel The channel to pause
*
*   @note If channel is -1, then all channels will be paused
*
*/
void pause(int channel)
{
    Mix_Pause(channel);
}



/**
*   @fn void resume(int channel)
*
*   Unpause the channel
*
*   @param channel The channel to resume playing
*
*   @note If channel is -1, then all channels will be unpaused
*
*/
void resume(int channel)
{
    Mix_Resume(channel);
}


/**
*   @fn void haltChannel(int channel)
*
*   Halt the channel playback
*
*   @param channel The channel to stop playing
*
*   @note If channel is -1, then all channels will be stopped
*
*/
void haltChannel(int channel)
{
    Mix_HaltChannel(channel);
}


/**
*   @fn void expireChannel(int channel, int ticks)
*
*   Halt the channel playback after some milliseconds
*
*   @param channel The channel to stop playing
*   @param ticks The time in millisecond
*
*   @note If channel is -1, then all channels will be stopped
*
*/
void expireChannel(int channel, int ticks)
{
    Mix_ExpireChannel(channel,ticks);
}


/**
*   @fn int isPlaying(int channel)
*
*   Check if the channel is playing
*
*   @param channel The channel to test
*
*   @return 0 If the channel is not playing, 1 otherwise
*
*   @note If channel is -1, then all channels will be tested
*           and the number of channels playing is returned
*
*/
int isPlaying(int channel)
{
    return Mix_Playing(channel);
}


/**
*   @fn int isPaused(int channel)
*
*   Check if the channel is paused
*
*   @param channel The channel to test
*
*   @return 0 If the channel is not paused, 1 otherwise
*
*   @note If channel is -1, then all channels will be tested
*           and the number of aused channels is returned
*
*/
int isPaused(int channel)
{
    return Mix_Paused(channel);
}



/**
*   @fn void fadeInMusic(LX_Music *music,int ms)
*
*   Fade in the loaded Music over some milliseconds of time
*
*   @param music The music to fade in
*   @param ms Milliseconds for the fade-in effect to complete
*
*   @note   fadeInMusic starts playing the music with the fade-in effecT.
*           It is not necessary to call LX_Music::play() if this function is called
*
*   @note Any previous music will be halted, or if it is fading out
*           it will wait (blocking) for the fade to complete
*
*/
void fadeInMusic(LX_Music *music,int ms)
{
    Mix_FadeInMusic(music->getMusic(),LX_MIXER_NOLOOP,ms);
}


/**
*   @fn void fadeOutMusic(int ms)
*
*   Fade out the loaded Music over some milliseconds of time
*
*   @param ms Milliseconds for the fade-out effect to complete
*
*   @note This functions works only when music is playing and
*           no fading is already set to fade out
*
*/
void fadeOutMusic(int ms)
{
    Mix_FadeOutMusic(ms);
}


/**
*   @fn void setPanning(int channel,Uint8 left,Uint8 right)
*
*   Set the panning on a channel, increasing of decreasing
*   the volume on this channel
*
*   @param channel The channel
*   @param left The volume of the left channel (0 - 255)
*   @param right The volume of the right channel (0 - 255)
*
*   @note This function only works on stereo audio.
*   @note It is possible the call fail if it is done on a mono audio.
*   @note To unregister type effect, use this function with 255 as left and right value
*           or use LX_Mixer::removePanning().
*
*/
void setPanning(int channel,Uint8 left,Uint8 right)
{
    Mix_SetPanning(channel,left,right);
}


/**
*   @fn void removePanning(int channel)
*
*   Remove the panning on a channel
*
*   @param channel The channel to remove the panning on
*
*/
void removePanning(int channel)
{
    setPanning(channel,LX_MIXER_EFFECT_LOUD,LX_MIXER_EFFECT_LOUD);
}



/**
*   @fn void setDistance(Uint8 distance)
*
*   Set the distance to all channels
*
*   @param distance The virtual distance betwenn the user and the source
*
*/
void setDistance(Uint8 distance)
{
    setDistance(MIX_CHANNEL_POST,distance);
}


/**
*   @fn void setPosition(Sint16 angle)
*
*   Set the virtual position of the audio source according to the channel.
*
*   @param angle The angle betwwen 0 and 360, larger angles are reduced using angle % 360
*
*/
void setPosition(Sint16 angle)
{
    setPosition(angle,LX_MIXER_EFFECT_NO_DISTANCE);
}


/**
*   @fn void setPosition(Sint16 angle, Uint8 distance)
*
*   Set the virtual position of the audio source according to the channel.
*
*   @param angle The angle betwwen 0 and 360, larger angles are reduced using angle % 360
*   @param distance The distance between the source and the listener
*
*/
void setPosition(Sint16 angle, Uint8 distance)
{
    setPosition(MIX_CHANNEL_POST,angle,distance);
}



/**
*   @fn void setPosition(int channel, Sint16, Uint8 distance)
*
*   Set the virtual position of the audio source according to the channel.
*   This function emulates a 3D audio effect.
*
*   @param channel The channel to register the effect on
*   @param angle The angle betwwen 0 and 360, larger angles are reduced using angle % 360
*   @param distance The distance between the source and the listener
*
*/
void setPosition(int channel, Sint16 angle, Uint8 distance)
{
    Mix_SetPosition(channel,angle,distance);
}



/**
*   @fn void resetPosition(int channel)
*
*   Reset the virtual position of the audio source according to the channel.
*
*   @param channel The channel to unregister the effect on
*
*/
void resetPosition(int channel)
{
    setPosition(channel,LX_MIXER_EFFECT_NO_ANGLE,LX_MIXER_EFFECT_NO_DISTANCE);
}


/**
*   @fn int reverseStereo(int channel, int flip)
*
*   Reverse the left and right channel sound
*
*   @param channel The channel to register the effect
*   @param flip Must be a non-zero value to register the reverse effect
*
*   @note If you want to unregister the effect on a channel, set 0 as flip
*
*/
void reverseStereo(int channel, int flip)
{
    Mix_SetReverseStereo(channel,flip);
}



/**
*   @fn void setDistance(int channel,Uint8 distance)
*
*   Set the distance of a channel
*
*   @param channel The channel to use
*   @param distance The virtual distance betwenn the user and the source
*
*   @note If MIX_CHANNEL_POST is set, all channels will be dealt
*
*/
void setDistance(int channel,Uint8 distance)
{
    Mix_SetDistance(channel,distance);
}


};

