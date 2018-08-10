
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
*   @file Music.cpp
*   @brief The implementation of the music library
*   @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <Lunatix/Music.hpp>
#include <Lunatix/Error.hpp>
#include <Lunatix/Texture.hpp>
#include <Lunatix/FileBuffer.hpp>
#include <Lunatix/utils/libtagspp/libtagspp.hpp>
#include <SDL2/SDL_mixer.h>


namespace
{

const int NOLOOP  = 0;
const int INFLOOP = -1;


lx::Graphics::
BufferedImage * _loadImage( const std::string& file,
                            const libtagpp::ImgMetaData& imgdata )
{
    if ( imgdata._img_offset <= 0 && imgdata._img_size <= 0 )
        return nullptr;

    const size_t IMG_OFFSET = static_cast<size_t>( imgdata._img_offset );
    const size_t IMG_SZ     = static_cast<size_t>( imgdata._img_size );

    return lx::FileIO::FileBuffer( file, IMG_OFFSET, IMG_SZ ).loadBufferedImage();
}

}   // namespace


namespace lx
{

namespace Mixer
{

/* Music tag */

MusicTag::~MusicTag()
{
    delete img;
}


const MusicTag getMusicInfoFrom( const UTF8string& u8file ) noexcept
{
    return getMusicInfoFrom( u8file.utf8_sstring() );
}

const MusicTag getMusicInfoFrom( const std::string& file ) noexcept
{
    libtagpp::Tag tag;
    MusicTag mtag;

    if ( !tag.readTag( file ) )
        lx::setError( std::string( "Cannot get metadata from " ) + file );

    mtag.title    = tag.title();
    mtag.artist   = tag.artist();
    mtag.album    = tag.album();
    mtag.year     = tag.year();
    mtag.track    = tag.track();
    mtag.genre    = tag.genre();
    mtag.format   = tag.properties().format;
    mtag.duration = tag.properties().duration;
    mtag.img      = _loadImage( file, tag.getImageMetaData() );

    return mtag;
}


/* music: private implementation */

class Music_
{
    Mix_Music * m_music = nullptr;
    std::string m_filename;
    libtagpp::Tag m_tag;
    MusicTag m_musictag;
    bool m_mtag_set = false;

    Music_( const Music_& m ) = delete;
    Music_& operator =( const Music_& m ) = delete;

    void load_( const std::string& filename )
    {
        Mix_FreeMusic( m_music );
        m_music = Mix_LoadMUS( filename.c_str() );

        if ( m_music == nullptr )
            throw MixerException( "Music — Cannot load " + filename );
    }

public:

    explicit Music_( const std::string& filename )
        : m_music( nullptr ), m_filename( filename ), m_tag(), m_musictag(), m_mtag_set( false )
    {
        load_( filename );
    }

    explicit Music_( const UTF8string& filename )
        : Music_( filename.utf8_sstring() ) {}

    void fadeIn( int ms ) noexcept
    {
        Mix_FadeInMusic( m_music, NOLOOP, ms );
    }

    void fadeInPos( int ms, int pos ) noexcept
    {
        Mix_FadeInMusicPos( m_music, NOLOOP, ms, pos );
    }

    bool play() noexcept
    {
        return play( false );
    }

    bool play( bool infinite ) noexcept
    {
        return Mix_PlayMusic( m_music, infinite ? INFLOOP : NOLOOP ) == 0;
    }

    bool play( unsigned int loops ) noexcept
    {
        return Mix_PlayMusic( m_music, static_cast<int>( loops ) ) == 0;
    }

    const libtagpp::Tag& getInfo() noexcept
    {
        if ( !m_tag.readTag( m_filename.c_str() ) )
            lx::setError( "Cannot get metadata" );

        return m_tag;
    }

    const MusicTag& metaData() noexcept
    {
        if ( !m_mtag_set )
        {
            getInfo();
            m_musictag.title    = m_tag.title();
            m_musictag.artist   = m_tag.artist();
            m_musictag.album    = m_tag.album();
            m_musictag.year     = m_tag.year();
            m_musictag.track    = m_tag.track();
            m_musictag.genre    = m_tag.genre();
            m_musictag.format   = m_tag.properties().format;
            m_musictag.duration = m_tag.properties().duration;
            m_musictag.img      = _loadImage( m_filename, m_tag.getImageMetaData() );
            m_mtag_set       = true;
        }

        return m_musictag;
    }

    ~Music_()
    {
        Mix_FreeMusic( m_music );
    }
};

/* Music: public functions */
Music::Music( const std::string& filename )
    : m_mimpl( new Music_( filename ) ) {}

Music::Music( const UTF8string& filename )
    : m_mimpl( new Music_( filename ) ) {}


void Music::fadeIn( int ms ) noexcept
{
    m_mimpl->fadeIn( ms );
}

void Music::fadeInPos( int ms, int pos ) noexcept
{
    m_mimpl->fadeInPos( ms, pos );
}

void Music::fadeOut( int ms ) noexcept
{
    Mix_FadeOutMusic( ms );
}


bool Music::play() noexcept
{
    return m_mimpl->play();
}

bool Music::play( bool infinite_loop ) noexcept
{
    return m_mimpl->play( infinite_loop );
}

bool Music::play( unsigned int loops ) noexcept
{
    return m_mimpl->play( loops );
}


void Music::pause() noexcept
{
    if ( Mix_PausedMusic() )
        Mix_ResumeMusic();
    else
        Mix_PauseMusic();
}

void Music::stop() noexcept
{
    if ( Mix_PlayingMusic() )
        Mix_HaltMusic();
}


const libtagpp::Tag& Music::getInfo() noexcept
{
    return m_mimpl->getInfo();
}

const MusicTag& Music::metaData() noexcept
{
    return m_mimpl->metaData();
}

Music::~Music()
{
    m_mimpl.reset();
}

}   // Mixer

}   // lx
