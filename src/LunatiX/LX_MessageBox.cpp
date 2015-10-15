
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


#include <LunatiX/LX_MessageBox.hpp>


/**
*   @namespace LX_MSGBox
*
*   @brief The Message Box module
*
*/
namespace LX_MSGBox
{

/**
*   @fn int showMSG(Uint32 flag, const char *title, const char *msg, SDL_Window *w)
*
*   Display a simple message box
*
*   @param flag One of these following flags:
*           - LX_MSG_ERR : Error megssage
*           - LX_MSG_WARN : Warning message
*           - LX_MSG_INFO : Information message
*   @param title The title of the box, UTF-8 format
*   @param msg The text to display in the box, UTF-8 format
*   @param w The parent window, or NULL for no parent
*
*   @return 0 on success, -1 on error
*/
int showMSG(Uint32 flag, const char *title, const char *msg, SDL_Window *w)
{
    return SDL_ShowSimpleMessageBox(flag,title,msg,w);
}


};


