

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
*	@file LX_FileIO.cpp
*	@brief The file handling implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/


#include "LX_FileIO.hpp"
#include "LX_Error.hpp"


namespace LX_FileIO{


    IOException::IOException(std::string err)
    {
        str_err = err;
    }

    const char * IOException::what() const throw()
    {
        return str_err.c_str();
    }

    IOException::~IOException() throw(){}


    LX_File::LX_File(const char * filename, const Uint32 mode)
    {
        data = NULL;

        if(filename == NULL || mode == 0x00000000)
            throw IOException("Invalid filename or mode\n");

        name = filename;
        open(mode);

        if(data == NULL)
            throw IOException(LX_GetError());

    }



    void LX_File::open(const Uint32 mode)
    {

        if((mode&LX_FILEIO_WRTR) == LX_FILEIO_WRTR)
        {
            data = SDL_RWFromFile(name.c_str(),"wb+");
        }
        else if((mode&LX_FILEIO_RDWR) == LX_FILEIO_RDWR)
        {
            data = SDL_RWFromFile(name.c_str(),"rb+");
        }
        else if((mode&LX_FILEIO_RDAP) == LX_FILEIO_RDAP)
        {
            data = SDL_RWFromFile(name.c_str(),"a+");
        }
        else if((mode&LX_FILEIO_RDONLY) == LX_FILEIO_RDONLY)
        {
            data = SDL_RWFromFile(name.c_str(),"rb");
        }
        else if((mode&LX_FILEIO_WRONLY) == LX_FILEIO_WRONLY)
        {
            data = SDL_RWFromFile(name.c_str(),"wb");
        }
        else if((mode&LX_FILEIO_APPEND) == LX_FILEIO_APPEND)
        {
            data = SDL_RWFromFile(name.c_str(),"ab");
        }

    }


    size_t LX_File::read(void *ptr,size_t size,size_t max_num)
    {
        return SDL_RWread(data,ptr,size,max_num);
    }


    size_t LX_File::write(void *ptr,size_t size,size_t max_num)
    {
        return SDL_RWwrite(data,ptr,size,max_num);
    }


    size_t LX_File::write(std::string str)
    {
        size_t len = str.length();
        return write((void *)str.c_str(),sizeof(char),len);
    }


    Sint64 LX_File::seek(Sint64 offset, int whence)
    {
        return SDL_RWseek(data,offset,whence);
    }


    Sint64 LX_File::tell(void)
    {
        return SDL_RWtell(data);
    }


    void LX_File::close(void)
    {
        if(data != NULL)
        {
            SDL_RWclose(data);
            data = NULL;
        }
    }


    SDL_Surface * LX_File::getSurfaceFromData(void)
    {
        SDL_Surface * surface = NULL;

        surface = IMG_Load_RW(data,0);
        seek(0,LX_SEEK_SET);

        return surface;
    }


    LX_File::~LX_File()
    {
        close();
    }

};
