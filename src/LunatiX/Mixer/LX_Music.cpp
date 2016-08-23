
/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/


/**
*    @file LX_Music.cpp
*    @brief The implementation of the music library
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
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


/* LX_Music */

LX_Music::LX_Music(std::string& filename) : _music(nullptr), _filename(filename)
{
    if(load_(filename) == false)
        throw LX_MusicException(LX_GetError());
}


LX_Music::LX_Music(UTF8string& filename) : _music(nullptr), _filename(filename.utf8_str())
{
    if(load_(filename.utf8_str()) == false)
        throw LX_MusicException(LX_GetError());
}


bool LX_Music::load_(std::string filename)
{
    Mix_FreeMusic(_music);
    _music = Mix_LoadMUS(filename.c_str());

    if(_music == nullptr)
        return false;

    _filename = filename;
    return true;
}


void LX_Music::fadeIn(int ms)
{
    Mix_FadeInMusic(_music,LX_MIXER_NOLOOP,ms);
}


void LX_Music::fadeInPos(int ms,int pos)
{
    Mix_FadeInMusicPos(_music,LX_MIXER_NOLOOP,ms,pos);
}


void LX_Music::fadeOut(int ms)
{
    Mix_FadeOutMusic(ms);
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


const libtagpp::Tag& LX_Music::getInfo()
{
    if(!_tag.readTag(_filename))
        LX_SetError("Cannot get metadata");

    return _tag;
}


LX_Music::~LX_Music(void)
{
    Mix_FreeMusic(_music);
}

};
