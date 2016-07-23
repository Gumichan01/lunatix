

/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Library.cpp
*	@brief The implementatino of the engine ressources
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/LX_Library.hpp>
#include <LunatiX/LX_Config.hpp>
#include <LunatiX/LX_Mixer.hpp>
#include <LunatiX/LX_WindowManager.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


namespace
{

bool LX_Mixer_Init(void)
{
    if(Mix_Init(MIX_INIT_OGG|MIX_INIT_FLAC|MIX_INIT_MP3) == 0)
        return false;

    if(Mix_OpenAudio(LX_MIXER_AUDIO_FREQUENCY,MIX_DEFAULT_FORMAT,
                     LX_MIXER_STEREO_SOUND,LX_MIXER_DEFAULT_CHUNKSIZE) == -1)
    {
        Mix_Quit();
        return false;
    }

    return true;
}

};


bool LX_Init(void)
{
    const std::string mappingFile = "config/gamecontrollerdb.txt";

    Uint32 sdl_flags = 0x00000000;                  // The flags for SDL_Init
    int img_flags = IMG_INIT_PNG|IMG_INIT_JPG;      // The IMG flag for SDL_Image

    // Load the configuration
    LX_Configuration::initConfig();
    LX_Configuration *configuration = LX_Configuration::getInstance();

    // Video flag
    if(configuration->getVideoFlag())
    {
        sdl_flags |= SDL_INIT_VIDEO;
    }

    // Audio flag
    if(configuration->getAudioFlag())
    {
        sdl_flags |= SDL_INIT_AUDIO;
    }

    // Gamepad flag
    if(configuration->getGamepadFlag())
    {
        sdl_flags |= SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER|SDL_INIT_HAPTIC;
    }

    // Init SDL
    if(SDL_Init(sdl_flags|SDL_INIT_TIMER) == -1)
    {
        return false;
    }

    // Load mappings from another configuration file
    if(SDL_WasInit(SDL_INIT_GAMECONTROLLER != 0))
    {
        SDL_GameControllerAddMappingsFromFile(mappingFile.c_str());
    }

    if(configuration->getVideoFlag())
    {
        // Init SDL_Image
        if(IMG_Init(img_flags) != img_flags)
        {
            SDL_Quit();
            return false;
        }
    }

    if(configuration->getTTFFlag())
    {
        // Init SDL_ttf
        if(TTF_Init() == -1)
        {
            IMG_Quit();
            SDL_Quit();
            return false;
        }
    }

    if(configuration->getAudioFlag())
    {
        // Init SDL_Mixer
        if(!LX_Mixer_Init())
        {
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
            return false;
        }
    }

    if(configuration->getOpenGLFlag())
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, LX_GL_MAJOR_VERSION);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, LX_GL_MINOR_VERSION);
    }

    LX_Win::LX_WindowManager::init();
    return true;
}


void LX_Quit(void)
{
    LX_Win::LX_WindowManager::destroy();

    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    LX_Configuration::destroy();
}
