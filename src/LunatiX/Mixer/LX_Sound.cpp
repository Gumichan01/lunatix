
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

/**
*   @file LX_Sound.cpp
*   @brief The abstract sound class definition
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*
*/

#include <LunatiX/LX_Sound.hpp>

namespace LX_Mixer
{

LX_SoundException::LX_SoundException(std::string err) : _string_error(err) {}

LX_SoundException::LX_SoundException(const LX_SoundException& me)
    : _string_error(me._string_error) {}

const char * LX_SoundException::what() const noexcept
{
    return _string_error.c_str();
}


LX_Sound::~LX_Sound() {}
}
