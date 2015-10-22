#ifndef LX_MESSAGEBOX_HPP_INCLUDED
#define LX_MESSAGEBOX_HPP_INCLUDED


/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_MessageBox.hpp
*	@brief The message box Library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <SDL2/SDL_messagebox.h>

#define LX_MSG_ERR  SDL_MESSAGEBOX_ERROR            /**< Error message */
#define LX_MSG_WARN SDL_MESSAGEBOX_WARNING          /**< Warning message */
#define LX_MSG_INFO SDL_MESSAGEBOX_INFORMATION      /**< Information message */



namespace LX_MSGBox
{
// Display a message box in a little window
bool showMSG(Uint32 flag, const char *title, const char *msg, SDL_Window *w);

};


#endif // LX_MESSAGEBOX_HPP_INCLUDED
