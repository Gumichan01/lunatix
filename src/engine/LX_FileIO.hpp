#ifndef LX_FILEIO_H_INCLUDED
#define LX_FILEIO_H_INCLUDED



/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_FileIO.hpp
*	@brief The file handling library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include <iostream>

#include <SDL2/SDL.h>


#define LX_FILEIO_RDONLY 0x00000001                         /**< Read only mode (r) */
#define LX_FILEIO_WRONLY 0x00000010                         /**< Write only mode (w) */
#define LX_FILEIO_APPEND 0x00000100                         /**< Append mode (a) */
#define LX_FILEIO_WRTR   0x00001000                         /**< Write but can read mode (w+) */
#define LX_FILEIO_BINARY 0x11000000                         /**< Binary mode (b) */
#define LX_FILEIO_RDWR LX_FILEIO_RDONLY|LX_FILEIO_WRONLY    /**< Read/Write mode (r+) */
#define LX_FILEIO_RDAP LX_FILEIO_RDONLY|LX_FILEIO_APPEND    /**< Read/Append mode (a+) */


/**
*   @namespace LX_FileIO
*   @brief The file Input/Output module
*
*   This namespace describes the gile module of LunatiX Engine
*
*/
namespace LX_FileIO{

    /**
    *   @class IOException
    *   @brief The Input/Output exception
    *
    *   This exception class occured when there is a problem on a LX_File function
    *
    */
    class IOException: public std::exception{

        std::string str_err;

        public :

        IOException(std::string err);

        const char * what() const throw();

        ~IOException() throw();

    };


    /**
    *   @class LX_File
    *   @brief The file structure
    *
    *   This structure gathers information about a file
    *
    */
    class LX_File{

        std::string name;       /**< The name of the file */
        SDL_RWops *data;        /**< The data */

        void open(const Uint32 mode);

        public :

        LX_File(const char * filename, const Uint32 mode);

        size_t readInto(void *ptr,size_t size,size_t max_num);
        size_t writeFrom(void *ptr,size_t size,size_t max_num);

        Sint64 seek(Sint64 offset, int whence);
        Sint64 tell(void);

        SDL_Surface * getSurfaceFromData(void);

        void close(void);

        ~LX_File();
    };


};


#endif // LX_FILEIO_H_INCLUDED

