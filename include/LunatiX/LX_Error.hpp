#ifndef LX_ERROR_HPP_INCLUDED
#define LX_ERROR_HPP_INCLUDED


/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file LX_Error.hpp
*   @brief The error header.
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <SDL2/SDL_error.h>


/**
*   @fn inline const char * LX_GetError()
*
*   Get the error message set by LX_SetError
*
*   @return The error message
*
*/
inline const char * LX_GetError()
{
    return SDL_GetError();
}


/**
*   @fn inline int LX_SetError(std::string str)
*
*   Set an error message
*
*   @param [in] str The error string
*
*   @return Always returns -1
*
*/
inline int LX_SetError(std::string str)
{
    return SDL_SetError(str.c_str());
}

/**
*   @fn inline int LX_SetError(UTF8string u8str)
*
*   Set an error message
*
*   @param [in] u8str The error utf-8 string
*
*   @return Always returns -1
*
*/
inline int LX_SetError(UTF8string u8str)
{
    return SDL_SetError(u8str.utf8_str());
}


#endif // LX_ERROR_HPP_INCLUDED
