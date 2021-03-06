
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

#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

/**
*   @file Chunk.hpp
*   @brief The sample header
*   @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <Lunatix/Sound.hpp>
#include <memory>

struct Mix_Chunk;

namespace lx
{

namespace FileIO
{
class FileBuffer_;
}

}

namespace lx
{

namespace Mixer
{

class Chunk_;

/**
*   @class Chunk
*   @brief The sample
*   @note This can handle WAVE, AIFF, RIFF, OGG, and VOC files
*/
class Chunk final : public virtual Sound
{
    friend class lx::FileIO::FileBuffer_;
    std::unique_ptr<Chunk_> m_chkimpl;

    Chunk( Mix_Chunk& chunk );
    Chunk( const Chunk& m ) = delete;
    Chunk& operator =( const Chunk& m ) = delete;

public:

    /**
    *   @fn Chunk(const std::string& filename)
    *   @brief Load a sample from a file
    *   @param [in] filename
    *
    *   @exception MixerException On failure
    */
    explicit Chunk( const std::string& filename );

    /**
    *   @fn Chunk(const UTF8string& filename)
    *   @brief Load a sample from a file
    *   @param [in] filename
    *
    *   @exception MixerException On failure
    */
    explicit Chunk( const UTF8string& filename );

    /**
    *   @fn virtual bool play() noexcept override
    *
    *   Play the current sample
    *
    *   @return TRUE on success, FALSE otherwise
    *   @note This function plays the sample on the first unserved channel
    *        with the no loop option
    */
    virtual bool play() noexcept override;
    /**
    *   @fn bool play(int channel) noexcept
    *
    *   Play the current sample
    *
    *   @param [in] channel The channel to play the sample on
    *
    *   @return TRUE on success, FALSE otherwise
    *   @note This function plays the sample with no loop
    */
    bool play( int channel ) noexcept;
    /**
    *   @fn bool play(int channel, int loops) noexcept
    *
    *   Play the current sample
    *
    *   @param [in] channel The channel to play the sample on
    *   @param [in] loops number of loops
    *
    *   @return TRUE on success, FALSE otherwise
    *   @note 1 — The sample is played loops + 1 time
    *            For example:
    *              - If loop == 0 → play the sample once
    *              - If loop == 1 → play the sample 2 times, ...
    *              - If loop == n (n ∈ N) → play the sample n+1 times
    *
    *   @note 2 — If loops == -1 → loop forever
    */
    bool play( int channel, int loops ) noexcept;
    /**
    *   @fn bool play(int channel, int loops, int ticks) noexcept
    *
    *   Play the current sample during a moment
    *
    *   @param [in] channel The channel to play the sample on
    *   @param [in] loops number of loops
    *   @param [in] ticks The limit in millisecond to play the current sample
    *
    *   @return TRUE on success, FALSE otherwise
    *   @note This function plays the sample on with no loop
    */
    bool play( int channel, int loops, int ticks ) noexcept;

    ~Chunk();
};

}   // Mixer

}   // lx

#endif // CHUNK_H_INCLUDED
