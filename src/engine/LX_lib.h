#ifndef LX_LIB_H_INCLUDED
#define LX_LIB_H_INCLUDED



/*
*
*	Copyright (C)  Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*
*/

/**
*	@file LX_lib.h
*	@brief The LX_lib file. It manages the SDL systems
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date August 14th, 2014
*
*
*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>


#define LX_AUDIO_STEREO_SOUND 2             /**< The stereo variable the mix module */
#define LX_AUDIO_MONO_SOUND 1               /**< The mono variable for the mix module */
#define LX_AUDIO_DEFAULT_CHUNKSIZE 1024     /**< The default chunsize for the mix module */


// #include "LX_config.h"  /// @todo create a configuration library


bool LX_Init(void);

void LX_Quit(void);








#endif // LX_LIB_H_INCLUDED
