
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
*   @file Chunk.cpp
*   @brief The chunk implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/Chunk.hpp>
#include <Lunatix/FileBuffer.hpp>
#include <Lunatix/Error.hpp>

#include <SDL2/SDL_mixer.h>


namespace lx
{

namespace Mixer
{

/* Chunk (private implementation) */

class Chunk_ final
{
    Mix_Chunk * m_chunk = nullptr;

    Chunk_( const Chunk_& m ) = delete;
    Chunk_& operator =( const Chunk_& m ) = delete;

    void load_( const std::string& filename )
    {
        Mix_FreeChunk( m_chunk );
        m_chunk = Mix_LoadWAV( filename.c_str() );

        if ( m_chunk == nullptr )
            throw MixerException( "Chunk — Cannot load " + filename );
    }

public:

    explicit Chunk_( Mix_Chunk& chunk ): m_chunk( &chunk ) {}

    explicit Chunk_( const std::string& filename ) : m_chunk( nullptr )
    {
        load_( filename );
    }

    explicit Chunk_( const UTF8string& filename ) : m_chunk( nullptr )
    {
        load_( filename.utf8_sstring() );
    }

    bool play() noexcept
    {
        return play( -1 );
    }

    bool play( int channel ) noexcept
    {
        return play( channel, 0 );
    }

    bool play( int channel, int loops ) noexcept
    {
        return Mix_PlayChannel( channel, m_chunk, loops ) == 0;
    }

    bool play( int channel, int loops, int ticks ) noexcept
    {
        return Mix_PlayChannelTimed( channel, m_chunk, loops, ticks ) == 0;
    }

    ~Chunk_()
    {
        Mix_FreeChunk( m_chunk );
    }
};

/* Chunk */

// Private constructor used for internal uses
Chunk::Chunk( Mix_Chunk& chunk ) : m_chkimpl( new Chunk_( chunk ) ) {}

// Public constructors
Chunk::Chunk( const std::string& filename ) : m_chkimpl( new Chunk_( filename ) ) {}

Chunk::Chunk( const UTF8string& filename ) : m_chkimpl( new Chunk_( filename ) ) {}


bool Chunk::play() noexcept
{
    return m_chkimpl->play();
}

bool Chunk::play( int channel ) noexcept
{
    return m_chkimpl->play( channel );
}

bool Chunk::play( int channel, int loops ) noexcept
{
    return m_chkimpl->play( channel, loops );
}

bool Chunk::play( int channel, int loops, int ticks ) noexcept
{
    return m_chkimpl->play( channel, loops, ticks );
}

Chunk::~Chunk()
{
    m_chkimpl.reset();
}

}   // Mixer

}   // lx
