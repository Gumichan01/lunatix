
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

#ifndef LX_CHUNK_H_INCLUDED
#define LX_CHUNK_H_INCLUDED

/**
*   @file LX_Chunk.hpp
*   @brief The sample header
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/LX_Sound.hpp>
#include <memory>

struct Mix_Chunk;

namespace LX_FileIO
{
class LX_FileBuffer_;
}


namespace LX_Mixer
{

class LX_Chunk_;

/**
*   @class LX_Chunk final
*   @brief The sample class
*/
class LX_Chunk final : public virtual LX_Sound
{
    friend class LX_FileIO::LX_FileBuffer_;
    std::unique_ptr<LX_Chunk_> _chkimpl;

    LX_Chunk(Mix_Chunk& chunk);
    LX_Chunk(const LX_Chunk& m) = delete;
    LX_Chunk& operator =(const LX_Chunk& m) = delete;

public:

    /**
    *   @fn LX_Chunk(const std::string& filename)
    *   @brief Load a sample from a file
    *   @param filename
    *   @note It is better to give a .wav file to the constructor.
    *        The sample was optimized for this format. But it can work with
    *        an other file type.
    *
    *   @exception LX_MixerException On failure
    */
    explicit LX_Chunk(const std::string& filename);

    /**
    *   @fn LX_Chunk(const UTF8string& filename)
    *   @brief Load a sample from a file
    *   @param filename
    *   @note It is better to give a .wav file to the constructor.
    *          The sample was optimized for this format. But it can work with
    *          an other file type.
    *
    *   @exception LX_MixerException On failure
    */
    explicit LX_Chunk(const UTF8string& filename);

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
    bool play(int channel) noexcept;
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
    bool play(int channel, int loops) noexcept;
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
    bool play(int channel, int loops, int ticks) noexcept;

    ~LX_Chunk();
};

}

#endif // LX_CHUNK_H_INCLUDED
