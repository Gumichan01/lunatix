
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

LX_MusicException::LX_MusicException(std::string err) : string_error(err) {}

LX_MusicException::LX_MusicException(const LX_MusicException& me)
    : string_error(me.string_error) {}

const char * LX_MusicException::what() const noexcept
{
    return string_error.c_str();
}

LX_MusicException::~LX_MusicException() noexcept {}


LX_Music::LX_Music(Mix_Music *mus) : music(mus)
{
    if(mus == nullptr)
        throw LX_MusicException("LX_Music constructor: invalid Mix_Music");
}


LX_Music::LX_Music(std::string filename) : music(nullptr)
{
    if(load(filename.c_str()) == false)
        throw LX_MusicException(LX_GetError());
}


bool LX_Music::load(std::string filename)
{
    Mix_FreeMusic(music);
    music = Mix_LoadMUS(filename.c_str());

    if(music == nullptr)
        return false;

    return true;
}


bool LX_Music::play(void)
{
    return play(LX_MIXER_NOLOOP);
}


bool LX_Music::play(int loops)
{
    return Mix_PlayMusic(music,loops) == 0;
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
    return music;
}


LX_Music::~LX_Music(void)
{
    Mix_FreeMusic(music);
}

};

