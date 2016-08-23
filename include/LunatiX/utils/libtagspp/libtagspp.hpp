
#ifndef TAGS_HPP_INCLUDED
#define TAGS_HPP_INCLUDED

#include <string>

struct Tagctx;
typedef int (*Tagread)(void *buf, int *cnt);

namespace libtagpp
{

class Tag;

class Properties
{
    friend class Tag;
    int _channels;
    int _samplerate;
    int _bitrate;
    int _duration;
    int _format;

public:

    Properties();
    int channels() const;
    int samplerate() const;
    int bitrate() const;
    const char * duration() const;
    int format() const;
    ~Properties();
};


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

    Tag();

    bool readTag(const std::string& filename);
    const char * title() const;
    const char * artist() const;
    const char * album() const;
    const char * year() const;
    const char * track() const;
    const char * genre() const;
    const char * albumgain() const;
    const char * albumpeak() const;
    const char * trackgain() const;
    const char * trackpeak() const;
    const Properties& properties() const;

    ~Tag();
};

};

#endif // TAGS_H_INCLUDED
