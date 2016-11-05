
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
#include <LunatiX/utils/libtagspp/libtagspp.hpp>
#include <LunatiX/LX_Error.hpp>
#include <SDL2/SDL_mixer.h>


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


/* Music tag */

MusicTag::MusicTag(): img(nullptr) {}

MusicTag::~MusicTag()
{
    delete img;
}


/* LX_music: private implementation */

class LX_Music_
{
    Mix_Music *_music;
    libtagpp::Tag _tag;
    std::string _filename;

protected:

    bool load_(const UTF8string& filename)
    {
        Mix_FreeMusic(_music);
        _music = Mix_LoadMUS(filename.utf8_str());

        if(_music == nullptr)
            return false;

        return true;
    }

public:

    explicit LX_Music_(const std::string& filename)
        : _music(nullptr), _filename(filename)
    {
        if(load_(filename) == false)
            throw LX_MusicException(LX_GetError());
    }

    explicit LX_Music_(const UTF8string& filename)
        : _music(nullptr), _filename(filename.utf8_str())
    {
        if(load_(filename) == false)
            throw LX_MusicException(LX_GetError());
    }

    void fadeIn(int ms)
    {
        Mix_FadeInMusic(_music,LX_MIXER_NOLOOP,ms);
    }

    void fadeInPos(int ms,int pos)
    {
        Mix_FadeInMusicPos(_music,LX_MIXER_NOLOOP,ms,pos);
    }

    bool play()
    {
        return play(LX_MIXER_NOLOOP);
    }

    bool play(int loops)
    {
        return Mix_PlayMusic(_music,loops) == 0;
    }

    const libtagpp::Tag& getInfo()
    {
        if(!_tag.readTag(_filename))
            LX_SetError("Cannot get metadata");

        return _tag;
    }

    ~LX_Music_()
    {
        Mix_FreeMusic(_music);
    }
};

/* LX_Music: public functions */

LX_Music::LX_Music(const std::string& filename) : _mimpl(new LX_Music_(filename)) {}

LX_Music::LX_Music(const UTF8string& filename) : _mimpl(new LX_Music_(filename)) {}


void LX_Music::fadeIn(int ms)
{
    _mimpl->fadeIn(ms);
}


void LX_Music::fadeInPos(int ms,int pos)
{
    _mimpl->fadeInPos(ms,pos);
}


void LX_Music::fadeOut(int ms)
{
    Mix_FadeOutMusic(ms);
}


bool LX_Music::play()
{
    return _mimpl->play();
}


bool LX_Music::play(int loops)
{
    return _mimpl->play(loops);
}


void LX_Music::pause()
{
    if(Mix_PausedMusic())
        Mix_ResumeMusic();
    else
        Mix_PauseMusic();
}


void LX_Music::stop()
{
    if(Mix_PlayingMusic())
        Mix_HaltMusic();
}


const libtagpp::Tag& LX_Music::getInfo()
{
    return _mimpl->getInfo();
}


LX_Music::~LX_Music()
{
    _mimpl.reset();
}

};
