#ifndef LX_ERROR_HPP_INCLUDED
#define LX_ERROR_HPP_INCLUDED


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

/**
*   @file LX_Error.hpp
*   @brief The error header.
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
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
*/
inline const char * LX_GetError()
{
    return SDL_GetError();
}

/**
*   @fn inline void LX_SetError(const char * str) noexcept
*   Set an error message
*   @param [in] str The error string
*/
inline void LX_SetError(const char * str)
{
    SDL_SetError(str);
}

/**
*   @fn inline void LX_SetError(const std::string str) noexcept
*   Set an error message
*   @param [in] str The error string
*/
inline void LX_SetError(const std::string& str) noexcept
{
    LX_SetError(str.c_str());
}

/**
*   @fn inline void LX_SetError(const UTF8string u8str) noexcept
*   Set an error message (utf-8)
*   @param [in] u8str The error utf-8 string
*/
inline void LX_SetError(const UTF8string& u8str) noexcept
{
    LX_SetError(u8str.utf8_sstring());
}


#endif // LX_ERROR_HPP_INCLUDED
