/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_FileIO.cpp
*    @brief The file handling implementation
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*
*/

#include <LunatiX/LX_FileIO.hpp>
#include <LunatiX/LX_Error.hpp>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rwops.h>

#include <cstring>
#include <cstdio>
#include <cerrno>


namespace LX_FileIO
{

IOException::IOException(std::string err) : _string_error(err) {}

IOException::IOException(const IOException& io) : _string_error(io._string_error) {}

const char * IOException::what() const noexcept
{
    return _string_error.c_str();
}

IOException::~IOException() noexcept {}


/// LX_AbstractFile

LX_AbstractFile::~LX_AbstractFile() {}


/// LX_File

/* Private implementation */

class LX_File_
{
    UTF8string _name;        /* The name of the file         */
    SDL_RWops *_data;        /* The internal file structure  */

    void open_(const uint32_t mode)
    {
        std::string str = "LX_File: ";

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
        else
            throw IOException(str + "Unrecognized mode");

        if(_data == nullptr)
            throw IOException(str + LX_GetError());
    }

public :

    LX_File_(const UTF8string& filename, const uint32_t mode)
        : _name(filename), _data(nullptr)
    {
        if(mode == 0x00000000)
            throw IOException("LX_File: Invalid mode");

        open_(mode);
    }

    size_t read(void *ptr, size_t data_size, size_t max_num)
    {
        return SDL_RWread(_data,ptr,data_size,max_num);
    }

    size_t readExactly(void *ptr, size_t data_size, size_t num)
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

    size_t write(void *ptr, size_t data_size, size_t num)
    {
        return SDL_RWwrite(_data,ptr,data_size,num);
    }

    size_t write(const std::string& str)
    {
        size_t len = str.size();
        return write((void *)str.c_str(),sizeof(char),len);
    }

    int64_t seek(int64_t offset, int whence)
    {
        return SDL_RWseek(_data,offset,whence);
    }

    int64_t tell() const
    {
        return SDL_RWtell(_data);
    }

    int64_t size()
    {
        return SDL_RWsize(_data);
    }

    const char * getFilename() const
    {
        return  _name.utf8_str();
    }

    void close()
    {
        if(_data != nullptr)
        {
            SDL_RWclose(_data);
            _data = nullptr;
        }
    }

    ~LX_File_()
    {
        close();
    }
};


/* Public functions */

LX_File::LX_File(const std::string& filename, const uint32_t mode)
    : LX_File(UTF8string(filename),mode) {}


LX_File::LX_File(const UTF8string& filename, const uint32_t mode)
    : _fimpl(new LX_File_(filename,mode)) {}


size_t LX_File::read(void *ptr, size_t data_size, size_t max_num)
{
    return _fimpl->read(ptr,data_size,max_num);
}


size_t LX_File::readExactly(void *ptr, size_t data_size, size_t num)
{
    return _fimpl->readExactly(ptr,data_size,num);
}


size_t LX_File::write(void *ptr, size_t data_size, size_t num)
{
    return _fimpl->write(ptr,data_size,num);
}


size_t LX_File::write(const std::string& str)
{
    return _fimpl->write(str);
}


int64_t LX_File::seek(int64_t offset, int whence)
{
    return _fimpl->seek(offset,whence);
}


int64_t LX_File::tell() const
{
    return _fimpl->tell();
}


int64_t LX_File::size()
{
    return _fimpl->size();
}


const char * LX_File::getFilename() const
{
    return _fimpl->getFilename();
}


void LX_File::close()
{
    _fimpl->close();
}


LX_File::~LX_File()
{
    close();
}


/// LX_TmpFile

/* Private implementation */

class LX_TmpFile_
{
    FILE * _f;

public:

    LX_TmpFile_() : _f(tmpfile())
    {
        if(_f == nullptr)
            throw IOException(strerror(errno));
    }

    size_t read(void *ptr, size_t data_size, size_t max_num)
    {
        size_t sz = fread(ptr,data_size,max_num,_f);
        char * err = strerror(errno);

        if(ferror(_f))
            LX_SetError(err);

        return sz;
    }

    size_t readExactly(void *ptr, size_t data_size, size_t num)
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

        return total_read != num ? 0 : total_read;
    }

    size_t write(void *ptr, size_t data_size, size_t num)
    {
        size_t sz = fwrite(ptr,data_size,num,_f);
        char * err = strerror(errno);

        if(ferror(_f))
            LX_SetError(err);

        return sz;
    }

    size_t write(const std::string& str)
    {
        size_t len = str.size();
        return write((void *)str.c_str(),sizeof(char),len);
    }

    int64_t seek(int64_t offset, int whence)
    {
        return fseek(_f,offset,whence);
    }

    int64_t tell() const
    {
        return ftell(_f);
    }

    void close()
    {
        fclose(_f);
        _f = nullptr;
    }

    ~LX_TmpFile_()
    {
        close();
    }
};


/* Public functions */

LX_TmpFile::LX_TmpFile(): _timpl(new LX_TmpFile_()) {}


size_t LX_TmpFile::read(void *ptr, size_t data_size, size_t max_num)
{
    return _timpl->read(ptr,data_size,max_num);
}


size_t LX_TmpFile::readExactly(void *ptr, size_t data_size, size_t num)
{
    return _timpl->readExactly(ptr,data_size,num);
}


size_t LX_TmpFile::write(void *ptr, size_t data_size, size_t num)
{
    return _timpl->write(ptr,data_size,num);
}


size_t LX_TmpFile::write(const std::string& str)
{
    return _timpl->write(str);
}


int64_t LX_TmpFile::seek(int64_t offset, int whence)
{
    return _timpl->seek(offset,whence);
}


int64_t LX_TmpFile::tell() const
{
    return _timpl->tell();
}

// private
void LX_TmpFile::close() {}

LX_TmpFile::~LX_TmpFile() {}

/// Stream

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

LX_TmpFile& operator <<(LX_TmpFile& f, UTF8string& u8s)
{
    f.write(u8s.utf8_str());
    return f;
}


LX_TmpFile& operator <<(LX_TmpFile& f, std::string s)
{
    f.write(s);
    return f;
}

};
