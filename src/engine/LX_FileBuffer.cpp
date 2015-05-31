

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
*	@file LX_FileBuffer.cpp
*	@brief The file buffer implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include <new>
#include <SDL2/SDL_image.h>

#include "LX_FileIO.hpp"
#include "LX_FileBuffer.hpp"
#include "LX_Error.hpp"


namespace LX_FileIO{

    /**
    *   @fn LX_FileBuffer::LX_FileBuffer(const char * filename)
    *
    *   Build the instance of the file buffer
    *
    *   @param filename The file to generate the buffer
    *
    *   @exception IOException If the filename is NULL
    *
    */
    LX_FileBuffer::LX_FileBuffer(const char * filename)
    {
        LX_File *reader = NULL;
        std::string str("LX_FileBuffer : ");
        int r = 0;

        if(filename == NULL)
            throw IOException("LX_FileBuffer : invalid filename");


        buffer = NULL;
        bufsize = 0;
        name = filename;
        reader = new LX_File(filename,LX_FILEIO_RDONLY);

        reader->seek(0,LX_SEEK_END);

        {
            Sint64 n = reader->tell();

            if(n == -1)
                throw IOException(str + LX_GetError());

            bufsize = n;
        }

        reader->seek(0,LX_SEEK_SET);
        buffer = new (std::nothrow) char[bufsize];

        if(buffer == NULL)
        {
            delete reader;
            throw IOException(str + "Internal error, not enough memory to store the file content");
        }

        r = reader->read(buffer,sizeof(char),bufsize);

        reader->close();
        delete reader;
    }


    /**
    *   @fn SDL_Surface * LX_FileBuffer::getSurfaceFromBuffer(void)
    *
    *   Try to load a surface from the memory
    *
    *   @return A valid surface if the memory refers to an image
    *
    */
    SDL_Surface * LX_FileBuffer::getSurfaceFromBuffer(void)
    {
        SDL_RWops *rw = SDL_RWFromConstMem(buffer,bufsize);
        return (rw == NULL) ? NULL:IMG_Load_RW(rw,1);
    }


    /**
    *   @fn TTF_Font * LX_FileBuffer::getTTFFromBuffer(int size)
    *
    *   Try to load a TTF_Font from the memory
    *
    *   @return A valid font if the memory refers to an image
    *
    */
    TTF_Font * LX_FileBuffer::getTTFFromBuffer(int size)
    {
        SDL_RWops *rw = SDL_RWFromConstMem(buffer,bufsize);
        return (rw == NULL) ? NULL:TTF_OpenFontRW(rw,1,size);
    }



    /**
    *   @fn const char * LX_FileBuffer::getFilename(void)
    *
    *   Get the name of the file the buffer refers to
    *
    *   @return The name of the file
    *
    */
    const char * LX_FileBuffer::getFilename(void)
    {
        return name.c_str();
    }


    /**
    *   @fn LX_FileBuffer::~LX_FileBuffer()
    *
    *   Destroy the file buffer
    *
    */
    LX_FileBuffer::~LX_FileBuffer()
    {
        delete [] buffer;
    }

};
