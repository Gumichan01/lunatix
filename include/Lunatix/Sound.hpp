
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

#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

/**
*   @file Sound.hpp
*   @brief The abstract sound class
*   @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <Lunatix/utils/utf8_string.hpp>

#include <exception>

namespace lx
{

namespace Mixer
{

/**
*   @class MixerException
*   @brief Exception class of the Audio module
*/
class MixerException final : public std::exception
{
    std::string m_msg;

public:

    explicit MixerException( std::string err );
    MixerException( const MixerException& me );
    virtual const char * what() const noexcept override;
    ~MixerException() = default;
};

/**
*   @class Sound
*   @brief The sound interface
*/
class Sound
{

public:
    /**
    *   @fn virtual bool play() noexcept = 0
    */
    virtual bool play() noexcept = 0;
    virtual ~Sound() = default;
};

}   // Mixer

}   // lx

#endif // SOUND_H_INCLUDED
