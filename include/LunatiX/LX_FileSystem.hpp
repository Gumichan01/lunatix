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

namespace LX_FileSystem
{

UTF8string getWorkingDirectory();

UTF8string getPreferencesDirectory(const std::string& org, const std::string& app);

};

#endif // LX_FILESYSTEM_HPP_INCLUDED
