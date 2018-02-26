
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#include <LunatiX/LX_FileSystem.hpp>
#include <SDL2/SDL_filesystem.h>


namespace
{

#ifdef __WIN32__
const char * CURRENT_DIR = ".\\";
const UTF8string SEPARATOR("\\");
#else
const char * CURRENT_DIR = "./";
const UTF8string SEPARATOR("/");
#endif

const UTF8string CURRENT(".");
const UTF8string PARENT("..");
const UTF8string ROOT(SEPARATOR);
const UTF8string SCURS(SEPARATOR + CURRENT + SEPARATOR);
const UTF8string SPARS(SEPARATOR + PARENT  + SEPARATOR);

// separator: '/' on POSIX system, '\' on Windows
UTF8string removeTrailingSep(const UTF8string& u8str) noexcept
{
    const UTF8iterator u8end = u8str.utf8_end();
    UTF8iterator it = u8str.utf8_begin();
    UTF8string u8s;

    while(it != u8end)
    {
        u8s += *it;

        if(*it == SEPARATOR)
        {
            UTF8iterator tmp_it = it + 1;
            while(tmp_it != u8end && *tmp_it == SEPARATOR)
            {
                ++tmp_it;
            }

            it = tmp_it;
        }
        else
            ++it;
    }

    return u8s;
}

size_t countSeparator(const UTF8string& u8str) noexcept
{
    size_t counter = 0;
    const std::string& SEP = SEPARATOR.utf8_sstring();

    for(const std::string& s: u8str)
    {
        if(s == SEP)
            ++counter;
    }

    return counter;
}

bool basename_check(const UTF8string& npath)
{
    // ".", ".." or root directory → return the path
    // No separator → the path itself
    return npath == CURRENT || npath == PARENT || npath == ROOT
           || npath.utf8_find(SEPARATOR) == UTF8string::npos;
}

bool dirname_check(const UTF8string& npath)
{
    // Empty string
    if(npath.utf8_empty())
        return true;

    const size_t POS = npath.utf8_find(SEPARATOR);
    const size_t U8LEN = npath.utf8_length();

    // Current directory or parent → current
    // "." or ".." between separators → current directory
    // OR No separator → CURRENT directory
    // OR The path contains at least one separator
    // and the first separator is at the end of string → it is unique
    return npath == CURRENT || npath == PARENT || npath == SCURS
           || npath == SPARS || POS == UTF8string::npos || POS == U8LEN -1;
}

}


namespace LX_FileSystem
{

UTF8string getWorkingDirectory() noexcept
{
    char * base_path = SDL_GetBasePath();
    UTF8string path(base_path == nullptr ? CURRENT_DIR: base_path);

    if(base_path != nullptr)
        SDL_free(base_path);

    return path;
}

UTF8string getPreferencesDirectory(const std::string& org, const std::string& app) noexcept
{
    char * base_path = SDL_GetPrefPath(org.c_str(), app.c_str());
    UTF8string path(base_path == nullptr ? "": base_path);

    if(base_path != nullptr)
        SDL_free(base_path);

    return path;
}

UTF8string basename(const UTF8string& path) noexcept
{
    const UTF8string npath = removeTrailingSep(path);

    // Empty string → current
    if(npath.utf8_empty())
        return CURRENT;

    // basic checking
    if(basename_check(npath))
        return npath;

    // The path contains at least one separator
    const size_t U8LEN = npath.utf8_length();
    const UTF8iterator beg = npath.utf8_begin();
    UTF8iterator it = --(npath.utf8_end());
    size_t spos = 0;
    bool end_sep = false;

    // If the last character is a separator ('/', '\')
    if(*it == SEPARATOR)
    {
        end_sep = true;
        spos = U8LEN - 1;
        --it;
    }
    else
        spos = U8LEN;

    while(*it != SEPARATOR && it != beg)
    {
        --it;
        --spos;
    }

    // If there is a separator at the beginning
    if(*it == SEPARATOR)
    {
        if(end_sep)
            return npath.utf8_substr(spos, U8LEN - spos - 1);
        else
            return npath.utf8_substr(spos, U8LEN);
    }

    return npath.utf8_substr(0, U8LEN - 1);
}

UTF8string dirname(const UTF8string& path) noexcept
{
    const UTF8string npath = removeTrailingSep(path);

    // root directory → return the path
    if(npath == ROOT)
        return npath;

    // Other particular cases
    if(dirname_check(npath))
        return CURRENT;

    const size_t POS = npath.utf8_find(SEPARATOR);
    const size_t U8LEN = npath.utf8_length();

    // If a unique separator was found and is at position 0 → root
    if(POS == 0 && countSeparator(npath) == 1)
    {
        return ROOT;
    }
    else if(countSeparator(npath) == 1)
    {
        return npath.utf8_substr(0, POS + 1);
    }

    // At this point, there are more than 1 separators
    const UTF8iterator beg = npath.utf8_begin();
    UTF8iterator it = --(npath.utf8_end());
    size_t spos = U8LEN - 1;

    // Last character == separator → do not count it
    if(*it == SEPARATOR)
    {
        --it;
        --spos;
    }

    while(it != beg && *it != SEPARATOR)
    {
        --it;
        --spos;
    }

    return npath.utf8_substr(0, (spos == 0 ? spos + 1 : spos));
}

}
