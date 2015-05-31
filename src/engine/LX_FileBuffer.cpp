

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

#include "LX_FileIO.hpp"
#include "LX_FileBuffer.hpp"
#include "LX_Error.hpp"


namespace LX_FileIO{


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


    LX_FileBuffer::~LX_FileBuffer()
    {
        delete [] buffer;
    }

};
