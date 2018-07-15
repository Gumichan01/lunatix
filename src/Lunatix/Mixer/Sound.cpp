
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
*   @file Sound.cpp
*   @brief The abstract sound class definition
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/Sound.hpp>

namespace lx
{

namespace Mixer
{

MixerException::MixerException( std::string err ) : m_msg( err ) {}

MixerException::MixerException( const MixerException& me )
    : m_msg( me.m_msg ) {}

const char * MixerException::what() const noexcept
{
    return m_msg.c_str();
}

}   // Mixer

}   // lx
