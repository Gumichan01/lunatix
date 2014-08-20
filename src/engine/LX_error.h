#ifndef LX_ERROR_H_INCLUDED
#define LX_ERROR_H_INCLUDED



/*
*	Copyright (C) 2014 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_error.h
*	@brief The LX_error library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date July 26th, 2014
*
*
*/

// All error defined into the physics class
#define LX_LIST_POINT_ERROR -1  /**< The list of the polygon point could not be created */
#define LX_SDL_RECT_ERROR -2    /**< The SDL_Rect pointer could not be allocated */

// All error defined into the LX_graphics and LX_ttf class
#define LX_SDL_INIT_ERROR -10       /**< Error occured during the SDL subsystems initialization */
#define LX_IMG_INIT_ERROR -11       /**< Error occured during the SDL_Image subsystems initialization */
#define LX_SCREEN_ERROR -12         /**< Error occured during the screen mode setting */
#define LX_TTF_INIT_ERROR -13       /**< Error occured during the TTF engine initialization */
#define LX_FONT_ERROR -14           /**< Error occured during a file font processing */
#define LX_FONT_SCREEN_ERROR -15    /**< Error occured because no screen has been set */

// All error defined into the LX_Audio class
#define LX_AUDIO_INIT_ERROR -30     /**< Error occured during the SDL_Mixer libraries initialization */
#define LX_AUDIO_OPEN_ERROR -31     /**< Error occured during the mixer opening */

#endif // LX_ERROR_H_INCLUDED












