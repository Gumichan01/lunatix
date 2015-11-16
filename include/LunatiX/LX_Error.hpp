#ifndef LX_ERROR_HPP_INCLUDED
#define LX_ERROR_HPP_INCLUDED



/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Error.hpp
*	@brief The error header.
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <string>
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
*   @param str The error string
*
*   @return Always returns -1
*
*/
inline int LX_SetError(std::string str)
{
    return SDL_SetError(str.c_str());
}


#endif // LX_ERROR_HPP_INCLUDED


