
/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    https://gumichan01.github.io/
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

#ifndef LX_SOUND_H_INCLUDED
#define LX_SOUND_H_INCLUDED

/**
*    @file LX_Sound.hpp
*    @brief The abstract sound class
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*/

const int LX_MIXER_LOOP = -1;   /**< Activate the loop      */
const int LX_MIXER_NOLOOP = 0;  /**< No loop is activated   */


namespace LX_Mixer
{

/**
*   @class LX_Sound
*   @brief The sound interface
*/
class LX_Sound
{

public:

    /// Play something
    virtual bool play() = 0;
    /// Destructor
    virtual ~LX_Sound();
};

};

#endif // LX_SOUND_H_INCLUDED
