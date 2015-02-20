

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Mixer.cpp
*	@brief The mixer library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 11th, 2014
*
*
*/

#include "LX_Sound.h"
#include "LX_Music.h"
#include "LX_Chunk.h"
#include "LX_Mixer.h"


/**
*   @fn LX_Music * LX_Mixer::loadMusic(std::string filename)
*
*   Load the music according to the file name
*
*   @param filename the name of the music file
*
*   @return The new LX_Mixer instance, NULL otherwise
*
*/
LX_Music * LX_Mixer::loadMusic(std::string filename)
{
    return new LX_Music(filename.c_str());
}



/**
*   @fn LX_Music * LX_Mixer::loadMusic(Mix_Music *mus)
*
*   Load the music according to the Mix_Music structure
*
*   @param mus the Mix_Music structure loaded
*
*   @return The new LX_Mixer instance, NULL otherwise
*
*/
LX_Music * LX_Mixer::loadMusic(Mix_Music *mus)
{
    return new LX_Music(mus);
}



/**
*   @fn LX_Chunk * LX_Mixer::loadSample(std::string filename)
*
*   Create a new LX_Chunk instance from a WAV file
*
*   @param filename the name of the sample file
*
*   @return a new instance, NULL otherwise
*
*/
LX_Chunk * LX_Mixer::loadSample(std::string filename)
{
    return new LX_Chunk(filename.c_str());
}


/**
*   @fn LX_Chunk * LX_Mixer::loadSample(Mix_Chunk *ch)
*
*   Create a new LX_Chunk instance from a Mix_Chunk structure
*
*   @param ch the Mix_chunk
*
*   @return a new instance, NULL otherwise
*
*/
LX_Chunk * LX_Mixer::loadSample(Mix_Chunk *ch)
{
    return new LX_Chunk(ch);
}




/**
*   @fn int LX_Mixer::channelVolume(int channel,int volume)
*
*   Set the channel volume to volume, from 0 to 128
*
*   @param channel the channel to set the volume in
*   @param volume
*
*   @return the previous volume setting
*
*   @note if the channel is -1, all channels will be set to the volume
*   @note If the volume is equals to -1, then the average volume is returned
*   @note If the new volume is greater than 128, the volume is set to 128
*   @note Ths value 128 is ht maximum value defined by the MIX_MAX_VOLUME macro
*
*/
int LX_Mixer::channelVolume(int channel,int volume)
{
    return Mix_Volume(channel,volume);
}


/**
*   @fn void LX_Mixer::fadeInMusic(LX_Music *music,int ms)
*
*   Fade in the loaded Music over some milliseconds of time
*
*   @param music The LX
*   @param ms Milliseconds for the fade-in effect to complete
*
*   @note fadeInMusic starts playing the music with the fade-in effec.
*           So if you use this fuction, you do not need
*               to call the LX_Music::play() yourself
*   @note Any previous music will be halted, or if it is fading out
*           it will wait (blocking) for the fade to complete
*
*/
void LX_Mixer::fadeInMusic(LX_Music *music,int ms)
{
    if(Mix_FadeInMusic(music->getMusic(),LX_MIXER_NOLOOP,ms) == -1)
    {
        std::cerr << "Error occured in LX_Mixer::fadeInMusic / Mix_FadeInMusic : "
                        << Mix_GetError() << std::endl;
    }
}


/**
*   @fn void LX_Mixer::fadeOutMusic(int ms)
*
*   Fade out the loaded Music over some milliseconds of time
*
*   @param ms Milliseconds for the fade-out effect to complete
*
*   @note This functions works only when music is playing and
*           no fading is already set to fade out
*
*/
void LX_Mixer::fadeOutMusic(int ms)
{
    if(Mix_FadeOutMusic(ms) == 0)
    {
        std::cerr << "Error occured in LX_Mixer::fadeOutMusic / Mix_FadeOutMusic : "
                        << Mix_GetError() << std::endl;
    }
}


/**
*   @fn void LX_Mixer::setPanning(int channel,Uint8 left,Uint8 right)
*
*   Set the panning on a channel, increasing of decreasing
*   the volume on this channel
*
*   @param channel the channel
*   @param left the volume of the left channel (0 - 255)
*   @param right the volume of the right channel (0 - 255)
*
*   @note This function only works on stereo audio.
*   @note It is possible the call fail if you do it on a mono audio.
*   @note To unregister tyhe effect, use this function with 255 as left and right value
*           or use LX_MixerremovePanning().
*
*/
void LX_Mixer::setPanning(int channel,Uint8 left,Uint8 right)
{
    if(Mix_SetPanning(channel,left,right) == 0)
    {
        std::cerr << "Error occured in LX_Mixer::setPanning / Mix_setPanning : "
                        << Mix_GetError() << std::endl;
    }
}


/**
*   @fn void LX_Mixer::removePanning(int channel)
*
*   Remove the panning on a channel
*
*   @param channel the channel you want to remove the panning on
*
*/
void LX_Mixer::removePanning(int channel)
{
    setPanning(channel,LX_MIXER_EFFECT_LOUD,LX_MIXER_EFFECT_LOUD);
}



/**
*   @fn void LX_Mixer::setDistance(Uint8 distance)
*
*   Set the distance
*
*   @param distance the virtuel distance betwenn the user and the source
*
*/
void LX_Mixer::setDistance(Uint8 distance)
{
    setDistance(MIX_CHANNEL_POST,distance);
}


/**
*   @fn void LX_Mixer::setPosition(Sint16 angle, int distance)
*
*   Set the virtuel position of the audio source according to the channel.
*
*   @param angle The angle betwwen 0 and 360, larger angles are reduced using angle % 360
*
*/
void LX_Mixer::setPosition(Sint16 angle)
{
    setPosition(angle,LX_MIXER_EFFECT_NO_DISTANCE);
}


/**
*   @fn void LX_Mixer::setPosition(Sint16 angle, int distance)
*
*   Set the virtuel position of the audio source according to the channel.
*
*   @param angle The angle betwwen 0 and 360, larger angles are reduced using angle % 360
*   @param distance the distance between the source and the listener
*
*/
void LX_Mixer::setPosition(Sint16 angle, int distance)
{
    setPosition(MIX_CHANNEL_POST,angle,distance);
}



/**
*   @fn void LX_Mixer::setPosition(int channel, Sint16, int distance)
*
*   Set the virtuel position of the audio source according to the channel.
*   This function emulates a 3D audio effect.
*
*   @param channel the channel you want to register the effect on
*   @param angle The angle betwwen 0 and 360, larger angles are reduced using angle % 360
*   @param distance the distance between the source and the listener
*
*   @note the distance is the same as the distance you can specified with LX_Mixer::setDistance()
*
*/
void LX_Mixer::setPosition(int channel, Sint16 angle, int distance)
{
    if(Mix_SetPosition(channel,angle,distance) == 0)
    {
        std::cerr << "Error occured in LX_Mixer::setPosition / Mix_setPosition : "
                        << Mix_GetError() << std::endl;
    }
}



/**
*   @fn void LX_Mixer::resetPosition(int channel)
*
*   Reset the virtuel position of the audio source according to the channel.
*
*   @param channel the channel you want to unregister the effect on
*
*/
void LX_Mixer::resetPosition(int channel)
{
    setPosition(channel,LX_MIXER_EFFECT_NO_ANGLE,LX_MIXER_EFFECT_NO_DISTANCE);
}




/**
*   @fn void LX_Mixer::setDistance(int channel,Uint8 distance)
*
*   Set the distance
*
*   @param channel the channel you need to use
*   @param distance the virtuel distance betwenn the user and the source
*
*   @note If you set MIX_CHANNEL_POST, all channel will be dealt
*
*/
void LX_Mixer::setDistance(int channel,Uint8 distance)
{
    if(Mix_SetDistance(channel,distance) == 0)
    {
        std::cerr << "distance setting failed : " << Mix_GetError() << std::endl;
    }
}














