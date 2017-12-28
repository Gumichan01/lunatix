
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
struct Properties
{
    int channels;           /**< Number of audio channels       */
    int samplerate;         /**< Sample rate (in Hz)            */
    int bitrate;            /**< Bitrate (in bits/s)            */
    std::string duration;   /**< Duration                       */
    std::string format;     /**< Format (MP3, OGG, FLAC, M4A)   */

    Properties();
    ~Properties() = default;
};

/**
*   @struct ImgMetaData
*   @brief Information about an image
*/
struct ImgMetaData
{
    int _img_offset;    /**< Beginning of image data in the file */
    int _img_size;      /**< Size of data */
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
    ImgMetaData _imdata;
    Properties _properties;

    friend void ctxtag(Tagctx *ctx, int t, const char *v, int offset, int size, Tagread);

public:

    /// Constructor
    Tag();

    Tag(Tag&) = delete;
    Tag(Tag&&) = delete;
    Tag& operator =(const Tag&) = delete;
    Tag&& operator =(const Tag&&) = delete;

    /**
    *   @fn bool readTag(const std::string& filename)
    *
    *   Read the metadata of the music given in argument
    *
    *   @param [in] filename The name of the music file
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
    /// Get meta data about the location of the image
    const ImgMetaData& getImageMetaData() const;
    /// Get the music properties
    const Properties& properties() const;

    /// Destructor
    ~Tag() = default;
};

}

#endif // TAGS_H_INCLUDED
