
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

/**
*   @file LX_Sound.cpp
*   @brief The abstract sound class definition
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <LunatiX/LX_Sound.hpp>

namespace LX_Mixer
{

LX_MixerException::LX_MixerException( std::string err ) : _string_error( err ) {}

LX_MixerException::LX_MixerException( const LX_MixerException& me )
    : _string_error( me._string_error ) {}

const char * LX_MixerException::what() const noexcept
{
    return _string_error.c_str();
}

}
