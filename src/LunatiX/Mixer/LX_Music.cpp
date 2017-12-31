
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
*   @file LX_Music.cpp
*   @brief The implementation of the music library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
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
LX_BufferedImage *_loadImage(const std::string& file,
                             const libtagpp::ImgMetaData& imgdata)
{
    if(imgdata._img_offset <= 0 && imgdata._img_size <= 0)
        return nullptr;

    return LX_FileIO::LX_FileBuffer(file, S32(imgdata._img_offset),
                                    S32(imgdata._img_size)).loadBufferedImage();
}

}   // namespace

namespace LX_Mixer
{

/* Music tag */

LX_MusicTag::LX_MusicTag() noexcept: img(nullptr) {}

LX_MusicTag::~LX_MusicTag()
{
    delete img;
}


const LX_MusicTag getMusicInfoFrom(const UTF8string& u8file) noexcept
{
    return getMusicInfoFrom(u8file.utf8_sstring());
}

const LX_MusicTag getMusicInfoFrom(const std::string& file) noexcept
{
    libtagpp::Tag tag;
    LX_MusicTag mtag;

    if(!tag.readTag(file))
        LX_SetError(std::string("Cannot get metadata from ") + file);

    mtag.title    = tag.title();
    mtag.artist   = tag.artist();
    mtag.album    = tag.album();
    mtag.year     = tag.year();
    mtag.track    = tag.track();
    mtag.genre    = tag.genre();
    mtag.format   = tag.properties().format;
    mtag.duration = tag.properties().duration;
    mtag.img      = _loadImage(file, tag.getImageMetaData());

    return mtag;
}


/* LX_music: private implementation */

class LX_Music_
{
    Mix_Music *_music;
    std::string _filename;
    libtagpp::Tag _tag;
    LX_MusicTag _mtag;
    bool mtag_set;

    void load_(const std::string& filename)
    {
        Mix_FreeMusic(_music);
        _music = Mix_LoadMUS(filename.c_str());

        if(_music == nullptr)
            throw LX_MixerException("LX_Music — Cannot load " + filename);
    }

public:

    explicit LX_Music_(const std::string& filename)
        : _music(nullptr), _filename(filename), mtag_set(false)
    {
        load_(filename);
    }

    explicit LX_Music_(const UTF8string& filename)
        : _music(nullptr), _filename(filename.utf8_sstring()), mtag_set(false)
    {
        load_(_filename);
    }

    void fadeIn(int ms) noexcept
    {
        Mix_FadeInMusic(_music, LX_MIXER_NOLOOP, ms);
    }

    void fadeInPos(int ms, int pos) noexcept
    {
        Mix_FadeInMusicPos(_music, LX_MIXER_NOLOOP, ms, pos);
    }

    bool play() noexcept
    {
        return play(LX_MIXER_NOLOOP);
    }

    bool play(int loops) noexcept
    {
        return Mix_PlayMusic(_music, loops) == 0;
    }

    const libtagpp::Tag& getInfo() noexcept
    {
        if(!_tag.readTag(_filename.c_str()))
            LX_SetError("Cannot get metadata");

        return _tag;
    }

    const LX_MusicTag& metaData() noexcept
    {
        if(!mtag_set)
        {
            getInfo();
            _mtag.title    = _tag.title();
            _mtag.artist   = _tag.artist();
            _mtag.album    = _tag.album();
            _mtag.year     = _tag.year();
            _mtag.track    = _tag.track();
            _mtag.genre    = _tag.genre();
            _mtag.format   = _tag.properties().format;
            _mtag.duration = _tag.properties().duration;
            _mtag.img      = _loadImage(_filename, _tag.getImageMetaData());
            mtag_set       = true;
        }

        return _mtag;
    }

    ~LX_Music_()
    {
        Mix_FreeMusic(_music);
    }
};

/* LX_Music: public functions */
LX_Music::LX_Music(const std::string filename)
    : _mimpl(new LX_Music_(filename)) {}

LX_Music::LX_Music(const UTF8string filename)
    : _mimpl(new LX_Music_(filename)) {}


void LX_Music::fadeIn(int ms) noexcept
{
    _mimpl->fadeIn(ms);
}

void LX_Music::fadeInPos(int ms, int pos) noexcept
{
    _mimpl->fadeInPos(ms, pos);
}

void LX_Music::fadeOut(int ms) noexcept
{
    Mix_FadeOutMusic(ms);
}


bool LX_Music::play() noexcept
{
    return _mimpl->play();
}

bool LX_Music::play(int loops) noexcept
{
    return _mimpl->play(loops);
}


void LX_Music::pause() noexcept
{
    if(Mix_PausedMusic())
        Mix_ResumeMusic();
    else
        Mix_PauseMusic();
}

void LX_Music::stop() noexcept
{
    if(Mix_PlayingMusic())
        Mix_HaltMusic();
}


const libtagpp::Tag& LX_Music::getInfo() noexcept
{
    return _mimpl->getInfo();
}

const LX_MusicTag& LX_Music::metaData() noexcept
{
    return _mimpl->metaData();
}

LX_Music::~LX_Music()
{
    _mimpl.reset();
}

}
