/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is an SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_FileIO.cpp
*	@brief The file handling implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/


#include <SDL2/SDL_image.h>

#include <LunatiX/LX_FileIO.hpp>
#include <LunatiX/LX_Error.hpp>


namespace LX_FileIO
{

/**
*   @fn IOException::IOException(std::string err)
*
*   The exception constructor
*
*   @param err The error string
*
*/
IOException::IOException(std::string err)
{
    stringError = err;
}


/**
*   @fn IOException::IOException(IOException& io)
*
*   The exception constructor
*
*   @param io The object to copy
*
*/
IOException::IOException(const IOException& io)
{
    stringError = io.stringError;
}



/**
*   @fn const char * IOException::what() const noexcept
*
*   Get the error string
*
*   @return The error string
*
*/
const char * IOException::what() const noexcept
{
    return stringError.c_str();
}


IOException::~IOException() noexcept {}


/**
*   @fn LX_File::LX_File(std::string filename, const Uint32 mode)
*
*   The constuctor
*
*   @param filename The file to open
*   @param mode The mode to be used for opening the file.
*               It is one of these following :
*               - ::LX_FILEIO_RDONLY
*               - ::LX_FILEIO_WRONLY
*               - ::LX_FILEIO_APPEND
*               - ::LX_FILEIO_RDWR
*               - ::LX_FILEIO_RDAP
*               - ::LX_FILEIO_WRTR
*
*   @exception IOException If one of these aruguments are invalid
*               or the file is not openable
*
*/
LX_File::LX_File(std::string filename, const Uint32 mode)
    : name(filename), data(NULL)
{
    if(mode == 0x00000000)
        throw IOException("LX_File : Invalid mode");

    open(mode);
}


/**
*   @fn void LX_File::open(const Uint32 mode)
*
*   This private function opens the file
*
*   @param mode The mode to be used for opening the file
*
*/
void LX_File::open(const Uint32 mode)
{
    std::string str = "LX_File : ";

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
        data = SDL_RWFromFile(name.c_str(),"ab+");
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

    if(data == NULL)
        throw IOException(str + LX_GetError());
}


/**
*   @fn size_t LX_File::read(void *ptr,size_t data_size,size_t max_num)
*
*   Read the file
*
*   @param ptr The pointer to a buffer to read data into
*   @param data_size The size of each object to read, in bytes
*   @param max_num The maximum number of objects to read
*
*   @return The number of objects read. 0 at error or end of file
*
*   @note It can read less bytes than expected.
*/
size_t LX_File::read(void *ptr,size_t data_size,size_t max_num)
{
    return SDL_RWread(data,ptr,data_size,max_num);
}


/**
*   @fn size_t LX_File::readExactly(void *ptr,size_t data_size,size_t num)
*
*   Read exactly max_num bytes of the file
*
*   @param ptr The pointer to a buffer to read data into
*   @param data_size The size of each object to read, in bytes
*   @param num The maximum number of objects to read
*
*   @return The number of objects read. 0 at error or end of file
*
*   @note   This function assures that exactly num bytes will be read
*
*/
size_t LX_File::readExactly(void *ptr,size_t data_size,size_t num)
{
    size_t total_read = 0;
    size_t read_data = 0;
    char * p = static_cast<char *>(ptr);

    // Read at most num bytes
    while(total_read < num)
    {
        read_data = read(p,data_size,num);

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


/**
*   @fn size_t LX_File::write(void *ptr,size_t data_size,size_t num)
*
*   Write on the file
*
*   @param ptr The pointer to a buffer containing data to write
*   @param data_size The size of an object to write, in bytes
*   @param num The maximum number of objects to write
*
*   @return The number of objects written.
*           This value will be less than num on error
*
*/
size_t LX_File::write(void *ptr,size_t data_size,size_t num)
{
    return SDL_RWwrite(data,ptr,data_size,num);
}


/**
*   @fn size_t LX_File::write(std::string str)
*
*   Write a string on the file
*
*   @param str The string to write
*
*   @return The number of characters written.
*           This value will be less than the string length on error
*
*/
size_t LX_File::write(std::string str)
{
    size_t len = str.length();
    return write((void *)str.c_str(),sizeof(char),len);
}


/**
*   @fn Sint64 LX_File::seek(Sint64 offset, int whence)
*
*   Seek for a position the file
*
*   @param offset An offset in bytes, relative to the whence; can be negative
*   @param whence Any of LX_SEEK_SET, LX_SEEK_CUR and LX_SEEK_END
*
*   @return The final offset in the data stream. -1 on error
*
*/
Sint64 LX_File::seek(Sint64 offset, int whence)
{
    return SDL_RWseek(data,offset,whence);
}


/**
*   @fn Sint64 LX_File::tell(void)
*
*   Get the position in a file
*
*   @return The current offset of the stream.
*           -1 if the position cannot be determined
*
*/
Sint64 LX_File::tell(void)
{
    return SDL_RWtell(data);
}


/**
*   @fn Sint64 LX_File::size(void)
*
*   Get the size of a file
*
*   @return The size of the file.
*           -1 on failure
*
*/
Sint64 LX_File::size(void)
{
    return SDL_RWsize(data);
}


/**
*   @fn void LX_File::close(void)
*
*   Close the file
*
*/
void LX_File::close(void)
{
    if(data != NULL)
    {
        SDL_RWclose(data);
        data = NULL;
    }
}


/**
*   @fn SDL_Surface * LX_File::getSurfaceFromData(void)
*
*   Try to load a surface from the file
*
*   @return A valid pointer to a surface if the file is an image file.
*           a null pointer otherwise
*
*   @note This function needs to read the entire file to create the surface.
*           So the cursor is reinitialized to 0 to do that.
*           However, It saves the old position of the cursor and restores it
*           at the end of the call;
*
*/
SDL_Surface * LX_File::getSurfaceFromData(void)
{
    SDL_Surface * surface = NULL;
    Sint64 save = tell();

    seek(0,LX_SEEK_SET);
    surface = IMG_Load_RW(data,0);
    seek(save,LX_SEEK_SET);

    return surface;
}

/**
*   @fn const char * LX_File::getFilename(void)
*
*   Get the name of the file the instance refers to
*
*   @return The name of the file
*
*/
const char * LX_File::getFilename(void)
{
    return name.c_str();
}

/**
*   @fn LX_File::~LX_File()
*
*   Destroy the instance closing the file
*
*/
LX_File::~LX_File()
{
    close();
}

};

