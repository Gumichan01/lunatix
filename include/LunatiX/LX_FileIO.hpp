#ifndef LX_FILEIO_H_INCLUDED
#define LX_FILEIO_H_INCLUDED


/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_FileIO.hpp
*	@brief The file handling library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.7
*
*/

#include <string>

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_rwops.h>

#define LX_FILEIO_RDONLY 0x00000001                             /**< Read only mode (r) */
#define LX_FILEIO_WRONLY 0x00000010                             /**< Write only mode (w) */
#define LX_FILEIO_APPEND 0x00000100                             /**< Append mode (a) */
#define LX_FILEIO_RDWR   (LX_FILEIO_RDONLY|LX_FILEIO_WRONLY)    /**< Read/Write mode (r+) */
#define LX_FILEIO_RDAP   (LX_FILEIO_RDONLY|LX_FILEIO_APPEND)    /**< Read/Append mode (a+) */
#define LX_FILEIO_WRTR   (0x00001000|LX_FILEIO_RDWR)            /**< Write but can read mode (w+) */

#define LX_SEEK_SET      RW_SEEK_SET                            /**< Beginning of data */
#define LX_SEEK_CUR      RW_SEEK_CUR                            /**< The current read point */
#define LX_SEEK_END      RW_SEEK_END                            /**< The end of data */


struct SDL_Surface;


/**
*   @namespace LX_FileIO
*   @brief The Input/Output file module
*/
namespace LX_FileIO
{

/**
*   @class IOException
*   @brief The Input/Output exception
*
*   This exception class occured when
*   there is a problem on the LX_File constructor
*
*/
class IOException: public std::exception
{
    std::string stringError;

public :

    IOException(std::string err);
    IOException(const IOException& io);

    const char * what() const noexcept;

    ~IOException() noexcept;
};


/**
*   @class LX_File
*   @brief The file handler
*/
class LX_File
{
    std::string name;       /* The name of the file         */
    SDL_RWops *data;        /* The internal file structure  */

    LX_File(LX_File& f);
    LX_File& operator =(LX_File& f);

    void open(const Uint32 mode);

public :

    LX_File(std::string filename, const Uint32 mode);

    size_t read(void *ptr,size_t data_size,size_t max_num);
    size_t readExactly(void *ptr,size_t data_size,size_t num);
    size_t write(void *ptr,size_t data_size,size_t num);
    size_t write(std::string str);

    Sint64 seek(Sint64 offset, int whence);
    Sint64 tell(void);
    Sint64 size(void);

    SDL_Surface * getSurfaceFromData(void);
    const char * getFilename(void);

    void close(void);

    ~LX_File();
};

};

#endif // LX_FILEIO_H_INCLUDED

