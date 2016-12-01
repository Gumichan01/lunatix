
/*
*   Copyright (C) 2016 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file LX_Music.cpp
*   @brief The implementation of the music library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.9
*/

#include <LunatiX/LX_Music.hpp>
#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_Texture.hpp>
#include <LunatiX/LX_FileBuffer.hpp>
#include <LunatiX/utils/libtagspp/libtagspp.hpp>
#include <SDL2/SDL_mixer.h>

#define S32(x) static_cast<uint32_t>(x)

namespace
{
LX_Graphics::
LX_BufferedImage *_loadImage(std::string file,
                             const libtagpp::ImgMetaData& imgdata)
{
    if(imgdata._img_offset <= 0 && imgdata._img_size <= 0)
        return nullptr;

    return LX_FileIO::LX_FileBuffer(file, S32(imgdata._img_offset),
                                    S32(imgdata._img_size)).loadBufferedImage();
}
};

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

LX_MusicTag::LX_MusicTag(): img(nullptr) {}

LX_MusicTag::~LX_MusicTag()
{
    delete img;
}


/* LX_music: private implementation */

class LX_Music_
{
    Mix_Music *_music;
    std::string _filename;
    bool _loaded;
    libtagpp::Tag _tag;
    LX_MusicTag _mtag;
    bool mtag_set;

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
        : _music(nullptr), _filename(filename), _loaded(false), mtag_set(false)
    {
         _loaded = load_(filename);
    }

    explicit LX_Music_(const UTF8string& filename)
        : LX_Music_(filename.utf8_str()) {}

    bool isLoaded()
    {
        return _loaded;
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

    const LX_MusicTag& metaData()
    {
        if(!mtag_set)
        {
            getInfo();
            _mtag.title = _tag.title();
            _mtag.artist = _tag.artist();
            _mtag.album = _tag.album();
            _mtag.year = _tag.year();
            _mtag.track = _tag.track();
            _mtag.genre = _tag.genre();
            _mtag.format = _tag.properties().format;
            _mtag.duration = _tag.properties().duration;
            _mtag.img = _loadImage(_filename,_tag.getImageMetaData());

            mtag_set = true;
        }

        return _mtag;
    }

    ~LX_Music_()
    {
        Mix_FreeMusic(_music);
    }
};

/* LX_Music: public functions */

LX_Music::LX_Music() : _mimpl(nullptr) {}

LX_Music::LX_Music(const std::string& filename) : _mimpl(new LX_Music_(filename))
{
    if(!_mimpl->isLoaded())
        throw LX_Mixer::LX_MusicException(LX_GetError());
}

LX_Music::LX_Music(const UTF8string& filename) : _mimpl(new LX_Music_(filename))
{
    if(!_mimpl->isLoaded())
        throw LX_Mixer::LX_MusicException(LX_GetError());
}


bool LX_Music::load(const std::string& filename)
{
    _mimpl.reset(new LX_Music_(filename));
    return _mimpl->isLoaded();
}

bool LX_Music::load(const UTF8string& filename)
{
    _mimpl.reset(new LX_Music_(filename));
    return _mimpl->isLoaded();
}

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

void LX_Music::close()
{
    _mimpl.reset();
}


const libtagpp::Tag& LX_Music::getInfo()
{
    return _mimpl->getInfo();
}

const LX_MusicTag& LX_Music::metaData()
{
    return _mimpl->metaData();
}


LX_Music::~LX_Music()
{
    _mimpl.reset();
}

};
