#ifndef LX_CHUNK_H_INCLUDED
#define LX_CHUNK_H_INCLUDED

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
*    @file LX_Chunk.hpp
*    @brief The chunk header
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include "LX_Sound.hpp"


struct Mix_Chunk;

namespace LX_FileIO
{
class LX_FileBuffer;
};


namespace LX_Mixer
{

/**
*   @class LX_ChunkException
*   @brief The exception class of LX_Chunk
*/
class LX_ChunkException : public std::exception
{
    std::string _string_error;

public :

    /// Constructor
    explicit LX_ChunkException(std::string err);
    /// Copy constructor
    LX_ChunkException(const LX_ChunkException& me);

    /// Get the error message
    const char * what() const noexcept;

    /// Destructor
    ~LX_ChunkException() noexcept;
};


/**
*   @class LX_Chunk
*   @brief The chunk class
*/
class LX_Chunk : public virtual LX_Sound
{
    friend class LX_FileIO::LX_FileBuffer;
    Mix_Chunk *_chunk;

    explicit LX_Chunk(Mix_Chunk& chunk);
    LX_Chunk(LX_Chunk& m);
    LX_Chunk& operator =(LX_Chunk& m);

protected:

    bool load_(const std::string& filename);

public:

    /**
    *   @fn LX_Chunk(const std::string& filename)
    *   @brief Constructor
    *
    *   Construct the instance creating the Mix_Chunk instance from a file
    *
    *   @param [in] filename The file to create the chunk from
    *
    *   @note It is preferable to give a .wav file to the constructor.
    *           The chunk was optimized for this format. But it can work with
    *           an other file type.
    *
    *   @exception LX_ChunkException if the chunk cannot be created from the file
    */
    explicit LX_Chunk(const std::string& filename);

    /**
    *   @fn LX_Chunk(UTF8string& filename)
    *   @brief Constructor
    *
    *   Create the instance loading a chunk file
    *
    *   @param [in] filename The chunk filename that will be loaded
    *
    *   @note It is preferable to give a .wav file to the constructor.
    *           The chunk was optimized for this format. But it can work with
    *           an other file type.
    *   @exception LX_ChunkException if the chunk cannot be created from the file
    */
    explicit LX_Chunk(UTF8string& filename);

    /**
    *   @fn bool loadFromBuffer(LX_FileBuffer *file)
    *
    *   Load the sample from a file buffer
    *
    *   @param [in] file The file buffer to load the chunk from
    *   @return TRUE on success, FALSE otherwise
    */
    bool loadFromBuffer(LX_FileIO::LX_FileBuffer *file);

    /**
    *   @fn bool play()
    *
    *   Play the current sample
    *
    *   @return TRUE on success, FALSE otherwise
    *   @note This function plays the sample on the first unserved channel
    *         with the no loop option
    */
    bool play();

    /**
    *   @fn bool play(int channel)
    *
    *   Play the current sample
    *
    *   @param [in] channel The channel to play the chunk on
    *
    *   @return TRUE on success, FALSE otherwise
    *   @note This function plays the sample with no loop
    */
    bool play(int channel);

    /**
    *   @fn bool play(int channel,int loops);
    *
    *   Play the current sample
    *
    *   @param [in] channel The channel to play the chunk on
    *   @param [in] loops number of loops
    *
    *   @return TRUE on success, FALSE otherwise
    *   @note The chunk is played loops +1 time
    *         For example:
    *         - If loop == 0 -> play the chunk once
    *         - If loop == 1 -> play the chunk 2 times, ...
    *
    *   @note If loops == -1 -> loop forever
    */
    bool play(int channel,int loops);

    /**
    *   @fn bool play(int channel,int loops,int ticks)
    *
    *   Play the current sample during a moment
    *
    *   @param [in] channel The channel to play the chunk on
    *   @param [in] loops number of loops
    *   @param [in] ticks The limit in millisecond to play the current sample
    *
    *   @return TRUE on success, FALSE otherwise
    *   @note This function plays the sample on with no loop
    */
    bool play(int channel,int loops,int ticks);

    /// Destructor
    ~LX_Chunk();
};

};

#endif // LX_CHUNK_H_INCLUDED
