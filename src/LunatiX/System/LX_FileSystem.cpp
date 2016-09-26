

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
const char * separator = "\\";
#else
const char * current_dir = "./";
const char * separator = "/";
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


UTF8string basename(const UTF8string& path)
{
    const UTF8string current(".");
    const UTF8string parent("..");
    const UTF8string root("/");
    const UTF8string sep(separator);

    // Empty string → current
    if(path.utf8_empty())
        return current;

    // ".", ".." or "/" → return the path
    if(path == current || path == parent || path == root)
        return path;

    // No separator → the path itself
    if(path.utf8_find(sep) == UTF8string::npos)
        return path;

    // Path that contains at least one separator
    const size_t u8len = path.utf8_length();
    const UTF8iterator beg = path.utf8_begin();
    UTF8iterator it = --(path.utf8_end());
    size_t spos = 0;
    bool end_sep = false;

    // If the last character is a separator ('/', '\')
    if(*it == sep)
    {
        end_sep = true;
        spos = u8len - 1;
        --it;
    }
    else
        spos = u8len;

    while(*it != sep && it != beg)
    {
        --it;
        --spos;
    }

    // If there is a separator at the beginning
    if(*it == sep)
    {
        if(end_sep)
            return path.utf8_substr(spos,u8len-spos -1);
        else
            return path.utf8_substr(spos,u8len);
    }

    return path.utf8_substr(0,u8len -1);
}

};
