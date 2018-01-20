
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

#ifndef LX_SOUND_H_INCLUDED
#define LX_SOUND_H_INCLUDED

/**
*   @file LX_Sound.hpp
*   @brief The abstract sound class
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/utils/utf8_string.hpp>

#include <exception>

namespace LX_Mixer
{

const int LX_MIXER_LOOP = -1;   /**< Activate the loop      */
const int LX_MIXER_NOLOOP = 0;  /**< No loop is activated   */


/**
*   @class LX_MixerException
*   @brief Exception class of the Audio module
*/
class LX_MixerException : public std::exception
{
    std::string _string_error;

public:

    explicit LX_MixerException(std::string err);
    LX_MixerException(const LX_MixerException& me);
    virtual const char * what() const noexcept;
    ~LX_MixerException() = default;
};

/**
*   @class LX_Sound
*   @brief The sound interface
*/
class LX_Sound
{

public:
    virtual bool play() noexcept = 0;
    virtual ~LX_Sound();
};

}

#endif // LX_SOUND_H_INCLUDED
