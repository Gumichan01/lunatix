#ifndef LX_FILEIO_H_INCLUDED
#define LX_FILEIO_H_INCLUDED


/*
*	Copyright (C) 2016 Luxon Jean-Pierre
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
*	@version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>

#include <SDL2/SDL_stdinc.h>

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
struct SDL_RWops;


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
    std::string _string_error;

public :

    /// Construct the Input/Output exception
    IOException(std::string err);
    /// Construct the Input/Output exception by copy
    IOException(const IOException& io);

    /// Get the error message
    const char * what() const noexcept;

    /// Destruction
    ~IOException() noexcept;
};


/**
*   @class LX_File
*   @brief The file handler
*/
class LX_File
{
    UTF8string _name;        /* The name of the file         */
    SDL_RWops *_data;        /* The internal file structure  */

    LX_File(LX_File& f);
    LX_File& operator =(LX_File& f);

    void open_(const Uint32 mode);

public :

    /**
    *   @fn LX_File(const std::string filename, const Uint32 mode)
    *
    *   Open the file given in argument according to the mode requested
    *
    *   @param filename The file to open
    *   @param mode The mode to be used for opening the file.
    *               It is one of these following :
    *               - ::LX_FILEIO_RDONLY
    *               - ::LX_FILEIO_WRONLY
    *               - ::LX_FILEIO_APPEND
    *               - ::LX_FILEIO_RDWR
    *               - ::LX_FILEIO_RDAP
    *               - ::LX_FILEIO_WRTR
    *
    *   @exception IOException If one of these aruguments are invalid
    *               or the file is not openable
    *
    */
    LX_File(const std::string filename, const Uint32 mode);


    /**
    *   @fn LX_File(const UTF8string& filename, const Uint32 mode)
    *
    *   Open the file given in argument according to the mode requested
    *
    *   @param filename The file to open
    *   @param mode The mode to be used for opening the file.
    *               It is one of these following :
    *               - ::LX_FILEIO_RDONLY
    *               - ::LX_FILEIO_WRONLY
    *               - ::LX_FILEIO_APPEND
    *               - ::LX_FILEIO_RDWR
    *               - ::LX_FILEIO_RDAP
    *               - ::LX_FILEIO_WRTR
    *
    *   @exception IOException If one of these aruguments are invalid
    *               or the file is not openable
    *
    */
    LX_File(const UTF8string& filename, const Uint32 mode);

    /**
    *   @fn size_t read(void *ptr,size_t data_size,size_t max_num)
    *
    *   Read the file
    *
    *   @param ptr The pointer to a buffer to read data into
    *   @param data_size The size of each object to read, in bytes
    *   @param max_num The maximum number of objects to read
    *
    *   @return The number of objects read. 0 at error or end of file
    *
    *   @note It can read less bytes than expected.
    */
    size_t read(void *ptr,size_t data_size,size_t max_num);

    /**
    *   @fn size_t readExactly(void *ptr,size_t data_size,size_t num)
    *
    *   Read exactly max_num bytes of the file
    *
    *   @param ptr The pointer to a buffer to read data into
    *   @param data_size The size of each object to read, in bytes
    *   @param num The maximum number of objects to read
    *
    *   @return The number of objects read. 0 at error or end of file
    *
    *   @note   This function assures that exactly num bytes will be read
    *
    */
    size_t readExactly(void *ptr,size_t data_size,size_t num);

    /**
    *   @fn size_t write(void *ptr,size_t data_size,size_t num)
    *
    *   Write on the file
    *
    *   @param ptr The pointer to a buffer containing data to write
    *   @param data_size The size of an object to write, in bytes
    *   @param num The maximum number of objects to write
    *
    *   @return The number of objects written.
    *           This value will be less than num on error
    *
    */
    size_t write(void *ptr,size_t data_size,size_t num);

    /**
    *   @fn size_t write(std::string str)
    *
    *   Write a string on the file
    *
    *   @param str The string to write
    *
    *   @return The number of characters written.
    *           This value will be less than the string length on error
    *
    */
    size_t write(std::string str);

    /**
    *   @fn Sint64 seek(Sint64 offset, int whence)
    *
    *   Seek for a position the file
    *
    *   @param offset An offset in bytes, relative to the whence; can be negative
    *   @param whence Any of LX_SEEK_SET, LX_SEEK_CUR and LX_SEEK_END
    *
    *   @return The final offset in the data stream. -1 on error
    *
    */
    Sint64 seek(Sint64 offset, int whence);

    /**
    *   @fn Sint64 tell(void)
    *
    *   Get the position in a file
    *
    *   @return The current offset of the stream.
    *           -1 if the position cannot be determined
    *
    */
    Sint64 tell(void);

    /**
    *   @fn Sint64 size(void)
    *
    *   Get the size of a file
    *
    *   @return The size of the file.
    *           -1 on failure
    *
    */
    Sint64 size(void);


    /**
    *   @fn SDL_Surface * getSurfaceFromData(void)
    *
    *   Try to load a surface from the file
    *
    *   @return A valid pointer to a surface if the file is an image file.
    *           a null pointer otherwise
    *
    *   @note This function needs to read the entire file to create the surface.
    *           So the cursor is reinitialized to 0 to do that.
    *           However, It saves the old position of the cursor and restores it
    *           at the end of the call;
    *
    */
    const char * getFilename(void);

    /**
    *   @fn const char * getFilename(void)
    *
    *   Get the name of the file the instance refers to
    *
    *   @return The name of the file
    *
    */
    void close(void);

    /**
    *   @fn ~LX_File()
    *
    *   Destroy the instance closing the file
    *
    */
    ~LX_File();

    friend LX_File& operator <<(LX_File& f, UTF8string& u8s);
    friend LX_File& operator <<(LX_File& f, std::string s);
};

};

#endif // LX_FILEIO_H_INCLUDED
