#ifndef ERROR_HPP_INCLUDED
#define ERROR_HPP_INCLUDED


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
*   @file Error.hpp
*   @brief The error header.
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/utils/utf8_string.hpp>
#include <SDL2/SDL_error.h>

namespace lx
{

/**
*   @fn inline const char * getError()
*   Get the error message set by setError
*   @return The error message
*/
inline const char * getError()
{
    return SDL_GetError();
}

/**
*   @fn inline void setError(const char * str) noexcept
*   Set an error message
*   @param [in] str The error string
*/
inline void setError( const char * str )
{
    SDL_SetError( "%s", str );
}

/**
*   @fn inline void setError(const std::string& str) noexcept
*   Set an error message
*   @param [in] str The error string
*/
inline void setError( const std::string& str ) noexcept
{
    setError( str.c_str() );
}

/**
*   @fn inline void setError(const UTF8string& u8str) noexcept
*   Set an error message (utf-8)
*   @param [in] u8str The error utf-8 string
*/
inline void setError( const UTF8string& u8str ) noexcept
{
    setError( u8str.utf8_sstring() );
}

}   // lx

#endif // ERROR_HPP_INCLUDED
