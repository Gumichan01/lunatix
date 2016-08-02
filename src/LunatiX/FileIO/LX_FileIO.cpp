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
*	@file LX_FileIO.cpp
*	@brief The file handling implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <SDL2/SDL_image.h>

#include <LunatiX/LX_FileIO.hpp>
#include <LunatiX/LX_Error.hpp>


namespace LX_FileIO
{

IOException::IOException(std::string err) : _string_error(err) {}

IOException::IOException(const IOException& io) : _string_error(io._string_error) {}

const char * IOException::what() const noexcept
{
    return _string_error.c_str();
}

IOException::~IOException() noexcept {}


LX_File::LX_File(const std::string filename, const Uint32 mode)
    : LX_File(UTF8string(filename),mode) {}


LX_File::LX_File(const UTF8string& filename, const Uint32 mode)
    : _name(filename), _data(nullptr)
{
    if(mode == 0x00000000)
        throw IOException("LX_File : Invalid mode");

    open_(mode);
}

void LX_File::open_(const Uint32 mode)
{
    std::string str = "LX_File : ";

    if((mode&LX_FILEIO_WRTR) == LX_FILEIO_WRTR)
    {
        _data = SDL_RWFromFile(_name.utf8_str(),"wb+");
    }
    else if((mode&LX_FILEIO_RDWR) == LX_FILEIO_RDWR)
    {
        _data = SDL_RWFromFile(_name.utf8_str(),"rb+");
    }
    else if((mode&LX_FILEIO_RDAP) == LX_FILEIO_RDAP)
    {
        _data = SDL_RWFromFile(_name.utf8_str(),"ab+");
    }
    else if((mode&LX_FILEIO_RDONLY) == LX_FILEIO_RDONLY)
    {
        _data = SDL_RWFromFile(_name.utf8_str(),"rb");
    }
    else if((mode&LX_FILEIO_WRONLY) == LX_FILEIO_WRONLY)
    {
        _data = SDL_RWFromFile(_name.utf8_str(),"wb");
    }
    else if((mode&LX_FILEIO_APPEND) == LX_FILEIO_APPEND)
    {
        _data = SDL_RWFromFile(_name.utf8_str(),"ab");
    }

    if(_data == nullptr)
        throw IOException(str + LX_GetError());
}


size_t LX_File::read(void *ptr,size_t data_size,size_t max_num)
{
    return SDL_RWread(_data,ptr,data_size,max_num);
}


size_t LX_File::readExactly(void *ptr,size_t data_size,size_t num)
{
    size_t total_read = 0;
    char * p = static_cast<char *>(ptr);

    // Read at most num bytes
    while(total_read < num)
    {
        size_t read_data = read(p,data_size,num);

        // Did it work?
        if(read_data == 0)
            return 0;

        // Move a the end of retrieved data
        p += read_data;
        total_read += read_data;
    }

    if(total_read != num)
    {
        return 0;
    }

    return total_read;
}


size_t LX_File::write(void *ptr,size_t data_size,size_t num)
{
    return SDL_RWwrite(_data,ptr,data_size,num);
}


size_t LX_File::write(std::string str)
{
    size_t len = str.length();
    return write((void *)str.c_str(),sizeof(char),len);
}


Sint64 LX_File::seek(Sint64 offset, int whence)
{
    return SDL_RWseek(_data,offset,whence);
}


Sint64 LX_File::tell(void)
{
    return SDL_RWtell(_data);
}


Sint64 LX_File::size(void)
{
    return SDL_RWsize(_data);
}


void LX_File::close(void)
{
    if(_data != nullptr)
    {
        SDL_RWclose(_data);
        _data = nullptr;
    }
}


SDL_Surface * LX_File::getSurfaceFromData(void)
{
    SDL_Surface * surface = nullptr;
    Sint64 save = tell();

    seek(0,LX_SEEK_SET);
    surface = IMG_Load_RW(_data,0);
    seek(save,LX_SEEK_SET);

    return surface;
}


const char * LX_File::getFilename(void)
{
    return  _name.utf8_str();
}


LX_File::~LX_File()
{
    close();
}


LX_File& operator <<(LX_File& f, UTF8string& u8s)
{
    f.write(u8s.utf8_str());
    return f;
}


LX_File& operator <<(LX_File& f, std::string s)
{
    f.write(s);
    return f;
}

};
