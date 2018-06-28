
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

#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED

/**
*   @file FileIO.hpp
*   @brief The file handling library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/utils/utf8_string.hpp>
#include <cstdio>
#include <memory>

struct SDL_Surface;
struct SDL_RWops;

/**
*   @ingroup System
*   @defgroup File File abstraction
*   @brief File manipulation (Input/Output, file buffering)
*/

namespace lx
{

/**
*   @ingroup File
*   @namespace lx::FileIO
*   @brief The file Input/Output namespace
*
*   This provides an interface for manipulating files
*/
namespace FileIO
{

/**
*   @enum FileMode
*   @brief The file access mode
*/
enum class FileMode
{
    RDONLY = 0x00000001,            /**< Read only mode (r)             */
    WRONLY = 0x00000010,            /**< Write only mode (w)            */
    APPEND = 0x00000100,            /**< Append mode (a)                */
    RDWR   = ( RDONLY | WRONLY ),   /**< Read/Write mode (r+)           */
    RDAP   = ( RDONLY | APPEND ),   /**< Read/Append mode (a+)          */
    WRTR   = ( 0x00001000 | RDWR )  /**< Write but can read mode (w+)   */
};

/**
*   @enum FileWhence
*   @brief The position used as reference in the file
*/
enum class FileWhence
{
    SET = SEEK_SET,     /**< Beginning of data      */
    CUR = SEEK_CUR,     /**< The current read point */
    END = SEEK_END      /**< The end of data        */
};


/**
*   @class IOException
*   @brief The Input/Output file exception
*
*   This exception class occured when
*   there is a problem on the File constructor
*
*/
class IOException final : public std::exception
{
    std::string _string_error;

    IOException& operator =( const IOException& io );

public:

    explicit IOException( const std::string& err );
    IOException( const IOException& io );
    const char * what() const noexcept override;
    ~IOException() noexcept;
};


/**
*   @class AbstractFile
*   @brief The abstract file interface
*/
class AbstractFile
{
    AbstractFile( const AbstractFile& ) = delete;
    AbstractFile& operator =( const AbstractFile& ) = delete;

public:

    AbstractFile() = default;

    /**
    *   @fn virtual size_t read(void *buffer, size_t dsize, size_t count = 1) noexcept
    *
    *   @param [out] buffer The pointer to a buffer to read data into
    *   @param [in] dsize The size of each object to read, in bytes
    *   @param [in] count The maximum number of objects to read
    *
    *   @return The number of objects that are read. 0 at error or end of file
    *
    *   @note It can read less objects than *count*.
    */
    virtual size_t read( void * buffer, size_t dsize, size_t count = 1 ) noexcept = 0;
    /**
    *   @fn virtual size_t readExactly(void *buffer, size_t dsize, size_t count = 1) noexcept
    *
    *   @param [out] buffer The pointer to a buffer to read data into
    *   @param [in] dsize The size of each object to read, in bytes
    *   @param [in] count The maximum number of objects to read
    *
    *   @return The number of objects that are read. -1 at error or end of file
    */
    virtual size_t readExactly( void * buffer, size_t dsize, size_t count = 1 ) noexcept = 0;

    /**
    *   @fn virtual size_t write(const void *buffer, size_t dsize, size_t count) noexcept
    *
    *   @param [in] buffer The pointer to a buffer containing data to write
    *   @param [in] dsize The size of an object to write, in bytes
    *   @param [in] count The maximum number of objects to write
    *
    *   @return The number of objects written succesfully.
    *           This value may be less than count on error
    */
    virtual size_t write( const void * buffer, size_t dsize, size_t count = 1 ) noexcept = 0;
    /**
    *   @fn virtual size_t write(const std::string& str) noexcept
    *
    *   @param [in] str The string to write
    *
    *   @return The number of characters written.
    *          This value will be less than the string length on error
    *
    *   @sa read
    */
    virtual size_t write( const std::string& str ) noexcept = 0;

    // TODO refactor seek() -> long instead of size_t
    /**
    *   @fn virtual bool seek(long offset, FileWhence whence) noexcept
    *
    *   Seek for a position the file
    *
    *   @param [in] offset An offset in bytes, relative to the whence; can be negative
    *   @param [in] whence Any of ::SET, ::CUR and ::END
    *
    *   @return TRUE on success, FALSE otherwise
    *
    *   @sa read
    */
    virtual bool seek( long offset, FileWhence whence ) noexcept = 0;

    // TODO refactor tell() -> long instead of size_t
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

    virtual ~AbstractFile() = default;
};


class File_;

/**
*   @class File
*   @brief The file handler
*/
class File final : public virtual AbstractFile
{
    std::unique_ptr<File_> _fimpl;

    File( File& f ) = delete;
    File& operator =( File& f ) = delete;

public:

    /**
    *   @fn File(const std::string& filename, const FileMode mode)
    *
    *   Open the file given in argument according to the mode requested
    *
    *   @param [in] filename The file to open
    *   @param [in] mode The mode to be used for opening the file.
    *              It is one of these following :
    *              - ::RDONLY
    *              - ::WRONLY
    *              - ::APPEND
    *              - ::RDWR
    *              - ::RDAP
    *              - ::WRTR
    *
    *   @exception IOException If one of these aruguments are invalid
    *             or the file is not openable
    */
    File( const std::string& filename, const FileMode mode );
    /**
    *   @fn File(const UTF8string& filename, const FileMode mode)
    *
    *   Open the file given in argument according to the mode requested
    *
    *   @param [in] filename The file to open
    *   @param [in] mode The mode to be used for opening the file.
    *              It is one of these following :
    *              - ::RDONLY
    *              - ::WRONLY
    *              - ::APPEND
    *              - ::RDWR
    *              - ::RDAP
    *              - ::WRTR
    *
    *   @exception IOException If one of these aruguments are invalid
    *             or the file is not openable
    */
    File( const UTF8string& filename, const FileMode mode );

    virtual size_t read( void * buffer, size_t dsize, size_t count = 1 ) noexcept override;
    virtual size_t readExactly( void * buffer, size_t dsize, size_t count = 1 ) noexcept override;

    virtual size_t write( const void * buffer, size_t dsize, size_t count = 1 ) noexcept override;
    virtual size_t write( const std::string& str ) noexcept override;

    virtual bool seek( long offset, FileWhence whence ) noexcept;
    virtual size_t tell() const noexcept;
    /**
    *   @fn size_t size()
    *   Get the size of a file
    *   @return The size of the file on success. -1 on failure
    */
    size_t size() noexcept;
    /**
    *   @fn const char * getFilename()
    *   Get the name of the file
    *   @return The name of the file
    */
    const char * getFilename() const noexcept;
    /**
    *   @fn void close() noexcept
    *   Close
    */
    void close() noexcept;

    virtual ~File();
};


class TmpFile_;

/**
*   @class TmpFile
*   @brief The temporary file
*/
class TmpFile final : public virtual AbstractFile
{
    std::unique_ptr<TmpFile_> _timpl;

    TmpFile( const TmpFile& ) = delete;
    TmpFile& operator =( const TmpFile& ) = delete;

public:

    TmpFile();

    virtual size_t read( void * buffer, size_t dsize, size_t count = 1 ) noexcept override;
    virtual size_t readExactly( void * buffer, size_t dsize, size_t count = 1 ) noexcept override;

    virtual size_t write( const void * buffer, size_t dsize, size_t count = 1 ) noexcept override;
    virtual size_t write( const std::string& str ) noexcept override;

    virtual bool seek( long offset, FileWhence whence ) noexcept override;
    virtual size_t tell() const noexcept;

    virtual ~TmpFile();
};


/**
*   @fn AbstractFile& operator <<(AbstractFile& f, const char s[]) noexcept
*
*   Write a string into the file
*
*   @param [in,out] f The file to write data into
*   @param [in] s A null-terminated C string
*
*   @return The updated file
*
*   @warning If s is not a null-terminated string (it has not the final '\0'),
*            the behaviour of the function is undefined
*/
AbstractFile& operator <<( AbstractFile& f, const char s[] ) noexcept;

/**
*   @fn AbstractFile& operator <<(AbstractFile& f, const std::string& s) noexcept
*
*   Write a string into the file
*
*   @param [in,out] f The file to write data into
*   @param [in] s The string
*
*   @return The updated file
*/
AbstractFile& operator <<( AbstractFile& f, const std::string& s ) noexcept;
/**
*   @fn AbstractFile& operator <<(AbstractFile& f, UTF8string& u8s) noexcept
*
*   Write a utf-8 string into the file
*
*   @param [in, out] f The file to write data into
*   @param [in] u8s The utf-8 string
*
*   @return The updated file
*/
AbstractFile& operator <<( AbstractFile& f, const UTF8string& u8s ) noexcept;

// Those functions are not defined
AbstractFile& operator >>( AbstractFile& f, char s[] ) noexcept = delete;
AbstractFile& operator >>( AbstractFile& f, std::string& s ) noexcept  = delete;
AbstractFile& operator >>( AbstractFile& f, UTF8string& u8s ) noexcept = delete;

/**
*   @fn template <typename T> AbstractFile& operator <<(AbstractFile& f, const T data) noexcept
*
*   Write data into the file
*
*   @param [in, out] f The file to write data into
*   @param [in] data
*
*   @return The updated file
*/
template <typename T>
AbstractFile& operator <<( AbstractFile& f, const T data ) noexcept;

/**
*   @fn template <typename T> AbstractFile& operator >>(AbstractFile& f, T& data) noexcept
*
*   Read data from the file
*
*   @param [in, out] f The file to read data from
*   @param [out] data
*
*   @return The updated file
*/
template <typename T>
AbstractFile& operator >>( AbstractFile& f, T& data ) noexcept;

#include "FileIO.tpp"

}   // FileIO

}   // lx

#endif // FILEIO_H_INCLUDED
