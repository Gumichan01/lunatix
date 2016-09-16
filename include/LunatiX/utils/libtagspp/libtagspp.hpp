
#ifndef TAGS_HPP_INCLUDED
#define TAGS_HPP_INCLUDED

/**
*    @file libtagspp.hpp
*    @brief The metadata reader API
*    @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <string>

struct Tagctx;
typedef int (*Tagread)(void *buf, int *cnt);


/**
*   @namespace libtagpp
*   @brief The metadata reader namespace
*/
namespace libtagpp
{

class Tag;

/**
*   @class Properties
*   @brief Set of music properties (duration, format, ...)
*/
class Properties
{
    friend class Tag;
    int _channels;
    int _samplerate;
    int _bitrate;
    int _duration;
    int _format;

public:

    /// Constructor
    Properties();
    /**
    *   @fn int channels() const
    *   Get the number of channels
    *   @return The number of channels, 0 if it is not defined
    */
    int channels() const;
    /**
    *   @fn int samplerate() const
    *   Get the sample rate
    *   @return The sample rate in Hz, 0 if it is not defined
    */
    int samplerate() const;
    /**
    *   @fn int bitrate() const
    *   Get the bit rate
    *   @return The bit rate in bit.s⁻¹ (bit/s), 0 if it is not defined
    */
    int bitrate() const;
    /**
    *   @fn std::string duration() const
    *   Get the duration of the music
    *   @return A string representing the duration, "0" if it is not defined
    */
    std::string duration() const;
    /**
    *   @fn int format() const
    *   Get the format of the music
    *   @return The format. It has on of the following values:
    *           - Fmp3: MP3 format
    *           - Fogg: OGG Vorbis format
    *           - Fflac: FLAC format
    *           - Fm4a: M4A format. See: http://www.wikiwand.com/en/Advanced_Audio_Coding
    */
    int format() const;
    /// Destructor
    ~Properties();
};


/**
*   @class Tag
*   @brief Metadata of the music
*/
class Tag
{
    std::string _title;
    std::string _artist;
    std::string _album;
    std::string _year;
    std::string _track;
    std::string _genre;
    std::string _albumgain;
    std::string _albumpeak;
    std::string _trackgain;
    std::string _trackpeak;
    Properties _properties;

    Tag(Tag&);
    friend void ctxtag(Tagctx *ctx, int t, const char *v, int offset, int size, Tagread f);

public:

    /// Constructor
    Tag();

    /**
    *   @fn bool readTag(const std::string& filename)
    *
    *   Read the metadata of the music given in argument
    *
    *   @param [in] filename The name of the music file
    *
    *   @return TRUE on success, and metadat are set, FALSE otherwise
    */
    bool readTag(const std::string& filename);
    /// Get the title
    const char * title() const;
    /// Get the artist
    const char * artist() const;
    /// Get the album
    const char * album() const;
    /// Get the year of publication
    const char * year() const;
    /// Get the track number
    const char * track() const;
    /// Get the music genre
    const char * genre() const;
    /// Get the album-gain
    const char * albumgain() const;
    /// Get the album peak
    const char * albumpeak() const;
    /// Get the track-gain
    const char * trackgain() const;
    /// Get the track peak
    const char * trackpeak() const;
    /// Get the music properties
    const Properties& properties() const;

    /// Destructor
    ~Tag();
};

};

#endif // TAGS_H_INCLUDED
