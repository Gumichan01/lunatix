
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
*	@file LX_Music.cpp
*	@brief The implementation of the music library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/LX_Music.hpp>
#include <LunatiX/LX_Error.hpp>


namespace LX_Mixer
{

LX_MusicException::LX_MusicException(std::string err) : _string_error(err) {}

LX_MusicException::LX_MusicException(const LX_MusicException& me)
    : _string_error(me._string_error) {}

const char * LX_MusicException::what() const noexcept
{
    return _string_error.c_str();
}

LX_MusicException::~LX_MusicException() noexcept {}


LX_Music::LX_Music(Mix_Music *mus) : _music(mus)
{
    if(mus == nullptr)
        throw LX_MusicException("LX_Music constructor: invalid Mix_Music");
}


LX_Music::LX_Music(std::string filename) : _music(nullptr)
{
    if(load(filename.c_str()) == false)
        throw LX_MusicException(LX_GetError());
}


bool LX_Music::load(std::string filename)
{
    Mix_FreeMusic(_music);
    _music = Mix_LoadMUS(filename.c_str());

    if(_music == nullptr)
        return false;

    return true;
}


bool LX_Music::play(void)
{
    return play(LX_MIXER_NOLOOP);
}


bool LX_Music::play(int loops)
{
    return Mix_PlayMusic(_music,loops) == 0;
}


void LX_Music::pause(void)
{
    if(Mix_PausedMusic())
        Mix_ResumeMusic();
    else
        Mix_PauseMusic();
}


void LX_Music::stop(void)
{
    if(Mix_PlayingMusic())
        Mix_HaltMusic();
}


int LX_Music::volume(int newVolume)
{
    return Mix_VolumeMusic(newVolume);
}


Mix_Music * LX_Music::getMusic(void)
{
    return _music;
}


LX_Music::~LX_Music(void)
{
    Mix_FreeMusic(_music);
}

};
