
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#define snprint std::snprintf
#define nil nullptr

inline int cistrcmp(const char* s1, const char* s2)
{
    while (*s1 != '\0' && (std::toupper(*s1++) == std::toupper(*s2++)));
    const char su1 = std::toupper(*((unsigned char *)--s1));
    const char su2 = std::toupper(*((unsigned char *)--s2));
    return (su1 < su2) ? -1 : (su1 != su2);
}

template <typename T>
inline constexpr int leuint(T * d) noexcept
{
    return static_cast<int>(d[3] << 24 | d[2] << 16 | d[1] <<  8 | d[0] <<  0);
}


typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long long uvlong;

#include "tags.h"

enum
{
    Numgenre = 192,
};

extern const char *id3genres[Numgenre];

/*
 * Converts (to UTF-8) at most sz bytes of src and writes it to out buffer.
 * Returns the number of bytes converted.
 * You need sz*2+1 bytes for out buffer to be completely safe.
 */
int iso88591toutf8(uchar *out, int osz, const uchar *src, int sz);

/*
 * Converts (to UTF-8) at most sz bytes of src and writes it to out buffer.
 * Returns the number of bytes converted or < 0 in case of error.
 * You need sz*4+1 bytes for out buffer to be completely safe.
 * UTF-16 defaults to big endian if there is no BOM.
 */
int utf16to8(uchar *out, int osz, const uchar *src, int sz);

/*
 * This one is common for both vorbis.c and flac.c
 * It maps a string k to tag type and executes the callback from ctx.
 * Returns 1 if callback was called, 0 otherwise.
 */
void cbvorbiscomment(Tagctx *ctx, char *k, char *v);

void tagscallcb(Tagctx *ctx, int type, const char *s, int offset, int size, Tagread f);

#define txtcb(ctx, type, s) tagscallcb(ctx, type, (const char*)s, 0, 0, nil)
