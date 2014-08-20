

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
*	@file LX_lib.cpp
*	@brief The LX_lib file
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date August 14, 2014
*
*
*
*/

#include "LX_lib.h"

/**
*   @fn bool LX_Init(void)
*
*   Initializes all SDL systems
*
*   @return TRUE if all systems were init, FALSE otherwise
*
*/
bool LX_Init(void)
{

    int err = 0;

    //Init SDL
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) == -1)
    {
        fprintf(stderr,"\nError occured in SDL_Init : %s \n", SDL_GetError());
        return false;
    }

    //Init SDL_Image
    int flag= IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF ;

    if( IMG_Init(flag) != flag)
    {
        fprintf(stderr,"\nError occured in IMG_Init : %s \n", IMG_GetError());
        SDL_Quit();
        return false;
    }

    //Init SDL_ttf
    if(TTF_Init() == -1)
    {
        fprintf(stderr,"\nError occured in TTF_Init : %s \n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    //Init SDL_Mixer
    err = Mix_Init(MIX_INIT_OGG);

    if(err == -1)
    {
        fprintf(stderr,"\nError occured in Mix_Init : %s \n", Mix_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    err = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,LX_AUDIO_STEREO_SOUND,LX_AUDIO_DEFAULT_CHUNKSIZE);

    if( err < 0)
    {
        fprintf(stderr,"\nError occured in Mix_OpenAudio : %s \n", Mix_GetError());
        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }


    return true;

}



/**
*   @fn void LX_Quit(void)
*
*   Shut down all SDL systems
*
*/
void LX_Quit(void)
{
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}






















