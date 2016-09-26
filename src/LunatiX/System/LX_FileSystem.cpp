

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


#include <LunatiX/LX_FileSystem.hpp>
#include <SDL2/SDL_filesystem.h>


namespace LX_FileSystem
{

#ifdef __WIN32__
const char * current_dir = ".\\";
#else
const char * current_dir = "./";
#endif

UTF8string getWorkingDirectory()
{
    char *base_path = SDL_GetBasePath();
    UTF8string path(base_path == nullptr ? current_dir: base_path);

    if(base_path != nullptr)
        SDL_free(base_path);

    return path;
}


UTF8string getPreferencesDirectory(const std::string& org, const std::string& app)
{
    char *base_path = SDL_GetPrefPath(org.c_str(),app.c_str());
    UTF8string path(base_path == nullptr ? "": base_path);

    if(base_path != nullptr)
        SDL_free(base_path);

    return path;
}

};
