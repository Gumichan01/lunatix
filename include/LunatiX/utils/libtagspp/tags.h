
#ifndef TAGS_H_INCLUDED
#define TAGS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Tagctx Tagctx;
typedef int (*Tagread)(void *buf, int *cnt);

/* Tag type. */
enum
{
	Tartist,
	Talbum,
	Ttitle,
	Tdate, /* "2014", "2015/02/01", but the year goes first */
	Ttrack, /* "1", "01", "1/4", but the track number goes first */
	Talbumgain,
	Talbumpeak,
	Ttrackgain,
	Ttrackpeak,
	Tgenre,
	Timage,
};

/* Format of the audio file. */
enum
{
	Fmp3,
	Fogg,
	Fflac,
	Fm4a,
};

/* Tag parser context. You need to set it properly before parsing an audio file using libtags. */
struct Tagctx
{
	/* Set it to the filename. Doesn't have to be a full path, but extension must be there. */
	const char *filename;

	/* Read function. This is what libtags uses to read the file. */
	int (*read)(Tagctx *ctx, void *buf, int cnt);

	/* Seek function. This is what libtags uses to seek through the file. */
	int (*seek)(Tagctx *ctx, int offset, int whence);

	/* Callback that is used by libtags to inform about the tags of a file.
	 * "type" is the tag's type (Tartist, ...). "s" is the null-terminated string unless "type" is
	 * Timage. "offset" and "size" define the placement and size of the image cover ("type" = Timage)
	 * inside the file, and "f" is not NULL in case reading the image cover requires additional
	 * operations on the data, in which case you need to read the image cover as a stream and call this
	 * function to apply these operations on the contents read.
	 */
	void (*tag)(Tagctx *ctx, int type, const char *s, int offset, int size, Tagread f);

	/* Auxiliary data. Not used by libtags. */
	void *aux;

	/* Memory buffer to work in. */
	char *buf;

	/* Size of the buffer. Must be at least 256 bytes. */
	int bufsz;

	/* Here goes the stuff libtags sets. It should be accessed after tagsget() returns.
	 * A value of 0 means it's undefined.
	 */
	int channels; /* Number of channels. */
	int samplerate; /* Hz */
	int bitrate; /* Bitrate, bits/s. */
	int duration; /* ms */
	int format; /* Fmp3, Fogg, Fflac, Fm4a */

	/* Private, don't touch. */
	int found;
	int num;
};

/* Parse the file using this function. Returns 0 on success. */
extern int tagsget(Tagctx *ctx);

#ifdef __cplusplus
}
#endif

#endif // TAGS_H_INCLUDED
