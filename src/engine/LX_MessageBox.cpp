
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


#include "LX_MessageBox.hpp"


namespace LX_MSGBox
{


int showMSG(Uint32 flag, const char *title, const char *msg, SDL_Window *w)
{
    return SDL_ShowSimpleMessageBox(flag,title,msg,w);
}


};


