#ifndef LX_FILESYSTEM_HPP_INCLUDED
#define LX_FILESYSTEM_HPP_INCLUDED


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
*    @file LX_FileSystem.hpp
*    @brief The File system
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>

/**
*   @namespace LX_FileSystem
*   @brief The file system
*/
namespace LX_FileSystem
{

/**
*   @fn UTF8string getWorkingDirectory()
*
*   Get the directory where the program was run from.
*
*   @return The working directory in absolute path, UTF-8 encoded.
*           If the function cannot retrieve the directory, it returns
*           the current directory in relative path:
*           - './' on POSIX systems
*           - '.\' on Windows
*
*   @note The return path will be guaranteed to end with a
*         path separator ('\' on Windows, '/' on most other platforms)
*/
UTF8string getWorkingDirectory();

/**
*   @fn UTF8string getPreferencesDirectory(const std::string& org, const std::string& app)
*
*   Get the preference directory. That means the directory where
*   the program can write personnal files (Preferences, game save, ...).
*
*   @param [in] org The name of the user/organization
*   @param [in] app The name of the application
*
*   @return The working directory in absolute path, UTF-8 encoded.
*           If the function cannot retrieve the directory,
*           it returns an empty string.
*
*   @note 1 - The directory is unique per user and per application.
*
*   @note 2 - The returned directory has the following syntax:
*
*             <path>/org/app/   # On POSIX systems
*             <path>\org\app\   # On Windows
*
*   @note 3 - The return path will be guaranteed to end with a
*             path separator ('\' on Windows, '/' on most other platforms)
*
*   @note 4 - You should assume the path returned by this function
*             is the only safe place to write files
*             (and that ::getWorkingDirectory(), while it might be writable,
               or even the parent of the returned path,
               aren't where you should be writing things).
*
*/
UTF8string getPreferencesDirectory(const std::string& org, const std::string& app);

UTF8string basename(const UTF8string& path);

};

#endif // LX_FILESYSTEM_HPP_INCLUDED
