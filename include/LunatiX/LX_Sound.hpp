#ifndef LX_SOUND_H_INCLUDED
#define LX_SOUND_H_INCLUDED


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
*	@file LX_Sound.hpp
*	@brief The abstract sound class
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>

#define LX_MIXER_LOOP -1                    /**< Activate the loop      */
#define LX_MIXER_NOLOOP 0                   /**< No loop is activated   */


namespace LX_Mixer
{

/**
*   @class LX_Sound
*   @brief The sound interface
*/
class LX_Sound
{
protected:

    virtual bool load_(std::string filename) = 0;

public:

    virtual bool play() = 0;                        /**< @brief Play something      */
    virtual int volume(int newVolume) = 0;          /**< @brief Set the volume      */

    virtual ~LX_Sound();
};

};

#endif // LX_SOUND_H_INCLUDED
