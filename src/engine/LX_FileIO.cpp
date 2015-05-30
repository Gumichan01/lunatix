

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
            throw new IOException("Invalid filename or mode\n");

        name = filename;
        open(mode);

        if(data == NULL)
            throw new IOException(LX_GetError());

    }



    void LX_File::open(const Uint32 mode)
    {

        if(mode&LX_FILEIO_RDWR == LX_FILEIO_RDWR)
        {
            data = SDL_RWFromFile(name.c_str(),"rb+");
        }
        else if(mode&LX_FILEIO_RDONLY == LX_FILEIO_RDONLY)
        {
            data = SDL_RWFromFile(name.c_str(),"rb");
        }
        else if(mode&LX_FILEIO_WRONLY == LX_FILEIO_WRONLY)
        {
            data = SDL_RWFromFile(name.c_str(),"wb");
        }
        else if(mode&LX_FILEIO_APPEND == LX_FILEIO_APPEND)
        {
            data = SDL_RWFromFile(name.c_str(),"ab");
        }
        else if(mode&LX_FILEIO_WRTR == LX_FILEIO_WRTR)
        {
            data = SDL_RWFromFile(name.c_str(),"wb+");
        }
        else if(mode&LX_FILEIO_RDAP == LX_FILEIO_RDAP)
        {
            data = SDL_RWFromFile(name.c_str(),"a+");
        }
    }


    void LX_File::close(void)
    {
        if(data != NULL)
            SDL_RWclose(data);
    }



    LX_File::~LX_File()
    {
        close();
    }

};
