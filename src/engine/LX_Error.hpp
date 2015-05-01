#ifndef LX_ERROR_HPP_INCLUDED
#define LX_ERROR_HPP_INCLUDED



/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Error.hpp
*	@brief The LX_Error file
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.3
*
*/

#include <SDL2/SDL.h>


#ifndef LX_GetError
#define LX_GetError() SDL_GetError()        /**< Alias of SDL_GetError */
#endif


#ifndef LX_SetError
#define LX_SetError(str) SDL_SetError(str)  /**< Alias of SDL_SetError */
#endif

#endif // LX_ERROR_HPP_INCLUDED
