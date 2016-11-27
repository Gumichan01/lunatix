
/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    https://gumichan01.github.io/
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

#include <LunatiX/LX_FileSystem.hpp>
#include <SDL2/SDL_filesystem.h>


namespace
{

#ifdef __WIN32__
const char * current_dir = ".\\";
const char * separator = "\\";
#else
const char * current_dir = "./";
const char * separator = "/";
#endif

/// Remove trailing separators ('/' on POSIX system, '\' on Windows)
UTF8string removeTrailingSep(const UTF8string& u8str)
{
    const UTF8iterator u8end = u8str.utf8_end();
    UTF8iterator it = u8str.utf8_begin();
    UTF8string u8s;

    while(it != u8end)
    {
        u8s += *it;

        if(*it == separator)
        {
            while(it != u8end && *it == separator)
            {
                ++it;
            }
            --it;
        }

        ++it;
    }

    return u8s;
}

size_t countSeparator(const UTF8string& u8str)
{
    const UTF8iterator e = u8str.utf8_end();
    UTF8iterator it = u8str.utf8_begin();
    size_t counter = 0;

    while(it != e)
    {
        if(*it == separator) ++counter;
        ++it;
    }
    return counter;
}

};


namespace LX_FileSystem
{

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
    const UTF8string root(separator);
    const UTF8string sep(separator);
    const UTF8string npath = removeTrailingSep(path);

    // Empty string → current
    if(npath.utf8_empty())
        return current;

    // ".", ".." or root directory → return the path
    if(npath == current || npath == parent || npath == root)
        return npath;

    // No separator → the path itself
    if(npath.utf8_find(sep) == UTF8string::npos)
        return npath;

    // The path contains at least one separator
    const size_t u8len = npath.utf8_length();
    const UTF8iterator beg = npath.utf8_begin();
    UTF8iterator it = --(npath.utf8_end());
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
            return npath.utf8_substr(spos,u8len-spos - 1);
        else
            return npath.utf8_substr(spos,u8len);
    }

    return npath.utf8_substr(0,u8len - 1);
}

UTF8string dirname(const UTF8string& path)
{
    const UTF8string current(".");
    const UTF8string parent("..");
    const UTF8string root(separator);
    const UTF8string sep(separator);
    const UTF8string scurs(sep + current + sep);
    const UTF8string spars(sep + parent + sep);
    const UTF8string npath = removeTrailingSep(path);

    // Empty string or parent → current
    if(npath.utf8_empty() || npath == parent)
        return current;

    // "." or root directory → return the path
    if(npath == current || npath == root)
        return npath;

    // "." or ".." between separators → current directory
    if(npath == scurs || npath == spars)
        return current;

    const size_t pos = npath.utf8_find(sep);
    const size_t u8len = npath.utf8_length();
    // No separator → current directory
    if(pos == UTF8string::npos)
        return current;

    // The path contains at least one separator
    // The first separator is at the end of string → it is unique
    if(pos == u8len -1)
        return current;

    // If a unique separator was found and is at position 0 → root
    if(pos == 0 && countSeparator(npath) == 1)
    {
        return root;
    }
    else if(countSeparator(npath) == 1)
    {
        return npath.utf8_substr(0,pos + 1);
    }

    // At this point, there are more than 1 separators
    const UTF8iterator beg = npath.utf8_begin();
    UTF8iterator it = --(npath.utf8_end());
    size_t spos = u8len - 1;

    // Last character == separator → do not count it
    if(*it == separator)
    {
        --it;
        --spos;
    }

    while(it != beg && *it != separator)
    {
        --it;
        --spos;
    }

    return npath.utf8_substr(0, (spos == 0 ? spos + 1 : spos));
}

};
