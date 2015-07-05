#ifndef LX_FILEBUFFER_HPP_INCLUDED
#define LX_FILEBUFFER_HPP_INCLUDED



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
*	@file LX_FileBuffer.hpp
*	@brief The file buffer
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include <iostream>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>

struct SDL_Surface;
struct Mix_Chunk;


namespace LX_FileIO
{

class LX_File;
class IOException;

/**
*   @class LX_FileBuffer
*   @brief The file buffer class
*
*   This structure contains information about a file buffer.
*   It store a memory copy of a file content into a buffer.
*
*/
class LX_FileBuffer
{

    std::string name;       /**< The name of the file the instance refers to */
    char *buffer;           /**< The read-only buffer */
    Uint64 bufsize;         /**< The size of the buffer */


public :

    LX_FileBuffer(const char * filename);

    SDL_Surface * getSurfaceFromBuffer(void);
    TTF_Font * getTTFFromBuffer(int size);
    Mix_Chunk * getChunkFromBuffer(void);
    const char * getFilename(void);

    ~LX_FileBuffer();
};

};


#endif // LX_FILEBUFFER_HPP_INCLUDED

