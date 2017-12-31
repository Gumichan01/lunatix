
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_FILEIO_H_INCLUDED
#define LX_FILEIO_H_INCLUDED

/**
*   @file LX_FileIO.hpp
*   @brief The file handling library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <memory>

struct SDL_Surface;
struct SDL_RWops;

/**
*   @ingroup System
*   @defgroup File File abstraction
*   @brief File manipulation (Input/Output, file buffering)
*/

/**
*   @ingroup File
*   @namespace LX_FileIO
*   @brief The file Input/Output namespace
*
*   This provides an interface for manipulating files
*/
namespace LX_FileIO
{

const uint32_t LX_FILEIO_RDONLY = 0x00000001;                           /**< Read only mode (r)     */
const uint32_t LX_FILEIO_WRONLY = 0x00000010;                           /**< Write only mode (w)    */
const uint32_t LX_FILEIO_APPEND = 0x00000100;                           /**< Append mode (a)        */
const uint32_t LX_FILEIO_RDWR   = (LX_FILEIO_RDONLY|LX_FILEIO_WRONLY);  /**< Read/Write mode (r+)   */
const uint32_t LX_FILEIO_RDAP   = (LX_FILEIO_RDONLY|LX_FILEIO_APPEND);  /**< Read/Append mode (a+)  */
const uint32_t LX_FILEIO_WRTR   = (0x00001000|LX_FILEIO_RDWR);          /**< Write but can read mode (w+) */

const uint32_t LX_SEEK_SET = 0;     /**< Beginning of data      */
const uint32_t LX_SEEK_CUR = 1;     /**< The current read point */
const uint32_t LX_SEEK_END = 2;     /**< The end of data        */


/**
*   @class IOException
*   @brief The Input/Output file exception
*
*   This exception class occured when
*   there is a problem on the LX_File constructor
*
*/
class IOException: public std::exception
{
    std::string _string_error;

    IOException& operator =(const IOException& io);

public:

    /// Constructor
    explicit IOException(std::string err);
    /// Copy cnstructor
    IOException(const IOException& io);

    /// Get the error message
    const char * what() const noexcept;

    /// Destructor
    ~IOException() noexcept;
};


/**
*   @class LX_AbstractFile
*   @brief The abstract file interface
*/
class LX_AbstractFile
{
    LX_AbstractFile(const LX_AbstractFile&) = delete;
    LX_AbstractFile& operator =(const LX_AbstractFile&) = delete;

public:

    LX_AbstractFile() = default;

    /**
    *   @fn virtual size_t read(void *buffer, size_t dsize, size_t count) noexcept
    *
    *   Read the file
    *
    *   @param [out] buffer The pointer to a buffer to read data into
    *   @param [in] dsize The size of each object to read, in bytes
    *   @param [in] count The maximum number of objects to read
    *
    *   @return The number of objects that are read. 0 at error or end of file
    *
    *   @note It can read less objects than *count*.
    */
    virtual size_t read(void *buffer, size_t dsize, size_t count) noexcept = 0;
    /**
    *   @fn virtual size_t readExactly(void *buffer, size_t dsize, size_t count) noexcept
    *
    *   Read exactly count bytes of the file
    *
    *   @param [out] buffer The pointer to a buffer to read data into
    *   @param [in] dsize The size of each object to read, in bytes
    *   @param [in] count The maximum number of objects to read
    *
    *   @return The number of objects that are read. -1 at error or end of file
    */
    virtual size_t readExactly(void *buffer, size_t dsize, size_t count) noexcept = 0;

    /**
    *   @fn virtual size_t write(const void *buffer, size_t dsize, size_t count) noexcept
    *
    *   Write on the file
    *
    *   @param [in] buffer The pointer to a buffer containing data to write
    *   @param [in] dsize The size of an object to write, in bytes
    *   @param [in] count The maximum number of objects to write
    *
    *   @return The number of objects written succesfully.
    *           This value may be less than count on error
    */
    virtual size_t write(const void *buffer, size_t dsize, size_t count) noexcept = 0;
    /**
    *   @fn virtual size_t write(const std::string& str) noexcept
    *
    *   Write a string on the file
    *
    *   @param [in] str The string to write
    *
    *   @return The number of characters written.
    *          This value will be less than the string length on error
    *
    *   @sa read
    */
    virtual size_t write(const std::string& str) noexcept = 0;

    /**
    *   @fn virtual bool seek(long offset, int whence) noexcept
    *
    *   Seek for a position the file
    *
    *   @param [in] offset An offset in bytes, relative to the whence; can be negative
    *   @param [in] whence Any of LX_SEEK_SET, LX_SEEK_CUR and LX_SEEK_END
    *
    *   @return TRUE on success, FALSE otherwise
    *
    *   @sa read
    */
    virtual bool seek(long offset, int whence) noexcept = 0;

    /**
    *   @fn virtual size_t tell() const noexcept
    *
    *   Get the position in a file
    *
    *   @return The current offset of the stream.
    *          -1 if the position cannot be determined
    *
    *   @sa seek
    */
    virtual size_t tell() const noexcept = 0;

    virtual ~LX_AbstractFile();
};


class LX_File_;

/**
*   @class LX_File
*   @brief The file handler
*/
class LX_File: public virtual LX_AbstractFile
{
    std::unique_ptr<LX_File_> _fimpl;

    LX_File(LX_File& f) = delete;
    LX_File& operator =(LX_File& f) = delete;

public:

    /**
    *   @fn LX_File(const std::string& filename, const uint32_t mode)
    *   @brief Constructor
    *
    *   Open the file given in argument according to the mode requested
    *
    *   @param [in] filename The file to open
    *   @param [in] mode The mode to be used for opening the file.
    *              It is one of these following :
    *              - ::LX_FILEIO_RDONLY
    *              - ::LX_FILEIO_WRONLY
    *              - ::LX_FILEIO_APPEND
    *              - ::LX_FILEIO_RDWR
    *              - ::LX_FILEIO_RDAP
    *              - ::LX_FILEIO_WRTR
    *
    *   @exception IOException If one of these aruguments are invalid
    *             or the file is not openable
    */
    LX_File(const std::string& filename, const uint32_t mode);
    /**
    *   @fn LX_File(const UTF8string& filename, const uint32_t mode)
    *   @brief Constructor
    *
    *   Open the file given in argument according to the mode requested
    *
    *   @param [in] filename The file to open
    *   @param [in] mode The mode to be used for opening the file.
    *              It is one of these following :
    *              - ::LX_FILEIO_RDONLY
    *              - ::LX_FILEIO_WRONLY
    *              - ::LX_FILEIO_APPEND
    *              - ::LX_FILEIO_RDWR
    *              - ::LX_FILEIO_RDAP
    *              - ::LX_FILEIO_WRTR
    *
    *   @exception IOException If one of these aruguments are invalid
    *             or the file is not openable
    */
    LX_File(const UTF8string& filename, const uint32_t mode);

    virtual size_t read(void *buffer, size_t dsize, size_t count) noexcept;
    virtual size_t readExactly(void *buffer, size_t dsize, size_t count) noexcept;

    virtual size_t write(const void *buffer, size_t dsize, size_t count) noexcept;
    virtual size_t write(const std::string& str) noexcept;

    virtual bool seek(long offset, int whence) noexcept;
    virtual size_t tell() const noexcept;

    /**
    *   @fn size_t size()
    *   Get the size of a file
    *   @return The size of the file on success. -1 on failure
    */
    size_t size() noexcept;

    /**
    *   @fn const char * getFilename()
    *   Get the name of the file the instance refers to
    *   @return The name of the file
    */
    const char * getFilename() const noexcept;

    /// Destructor
    virtual ~LX_File();
};


class LX_TmpFile_;

/**
*   @class LX_TmpFile
*   @brief The temporary file
*/
class LX_TmpFile: public virtual LX_AbstractFile
{
    std::unique_ptr<LX_TmpFile_> _timpl;

    LX_TmpFile(const LX_TmpFile&) = delete;
    LX_TmpFile& operator =(const LX_TmpFile&) = delete;

public:

    /// Constructor
    LX_TmpFile();

    virtual size_t read(void *buffer, size_t dsize, size_t count) noexcept;
    virtual size_t readExactly(void *buffer, size_t dsize, size_t count) noexcept;

    virtual size_t write(const void *buffer, size_t dsize, size_t count) noexcept;
    virtual size_t write(const std::string& str) noexcept;

    virtual bool seek(long offset, int whence) noexcept;
    virtual size_t tell() const noexcept;

    /// Destructor
    virtual ~LX_TmpFile();
};

/**
*   @fn LX_AbstractFile& operator <<(LX_AbstractFile& f, const std::string s) noexcept
*
*   Write a string into the file
*
*   @param [in,out] f The file to write data into
*   @param [in] s The string
*
*   @return The updated file
*/
LX_AbstractFile& operator <<(LX_AbstractFile& f, const std::string s) noexcept;
/**
*   @fn LX_AbstractFile& operator <<(LX_AbstractFile& f, UTF8string& u8s) noexcept
*
*   Write a utf-8 string into the file
*
*   @param [in, out] f The file to write data into
*   @param [in] u8s The utf-8 string
*
*   @return The updated file
*/
LX_AbstractFile& operator <<(LX_AbstractFile& f, const UTF8string& u8s) noexcept;

/**
*   @fn template <typename T> LX_AbstractFile& operator <<(LX_AbstractFile& f, const T s) noexcept
*
*   Write adata into the file
*
*   @param [in, out] f The file to write data into
*   @param [in] data
*
*   @return The updated file
*/
template <typename T>
LX_AbstractFile& operator <<(LX_AbstractFile& f, const T data) noexcept;

#include "LX_FileIO.tpp"

}

#endif // LX_FILEIO_H_INCLUDED
