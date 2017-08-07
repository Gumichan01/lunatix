
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

#ifndef LX_SOUND_H_INCLUDED
#define LX_SOUND_H_INCLUDED

/**
*   @file LX_Sound.hpp
*   @brief The abstract sound class
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*/

#include <LunatiX/utils/utf8_string.hpp>

#include <exception>

namespace LX_Mixer
{

const int LX_MIXER_LOOP = -1;   /**< Activate the loop      */
const int LX_MIXER_NOLOOP = 0;  /**< No loop is activated   */


/**
*   @class LX_SoundException
*   @brief The sound interface
*/
class LX_SoundException : public std::exception
{
    std::string _string_error;

public:

    /// Constructor
    explicit LX_SoundException(std::string err);
    /// Copy constructor
    LX_SoundException(const LX_SoundException& me);

    /// Get the error message
    virtual const char * what() const noexcept;

    /// Destructor
    ~LX_SoundException() = default;
};

/**
*   @class LX_Sound
*   @brief The sound interface
*/
class LX_Sound
{

public:

    /// Load a sound file
    virtual bool load(const std::string filename) = 0;
    /// Load a sound file (UTF-8)
    virtual bool load(const UTF8string filename) = 0;
    /// Check if the sound is loaded
    virtual bool isLoaded() const = 0;
    /// Play something
    virtual bool play() = 0;
    /// Close the music
    virtual void close() = 0;
    /// Destructor
    virtual ~LX_Sound();
};

}

#endif // LX_SOUND_H_INCLUDED
