

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
*	@file LX_Library.cpp
*	@brief The implementatino of the engine ressources
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include "LX_Library.hpp"
#include "LX_Config.hpp"
#include "LX_Mixer.hpp"
#include "LX_Error.hpp"
#include "LX_WindowManager.hpp"


using namespace LX_Graphics;

static const std::string mappingFile = "config/gamecontrollerdb.txt";

/**
*   @fn bool LX_Init(void)
*
*   Loads the engine according the configuration file
*
*   @return TRUE if all systems were init, FALSE otherwise
*
*   @note This function automatically calls LX_WindowManager::init()
*
*/
bool LX_Init(void)
{
    int err = 0;
    Uint32 sdl_flags = 0x00000000;                  // The flags for SDL_Init
    int img_flags = IMG_INIT_PNG| IMG_INIT_JPG;     // The IMG flag for SDL_Image

    // Load the configuration
    LX_Configuration::initConfig();
    LX_Configuration *configuration = LX_Configuration::getInstance();

    // Check the tags (video, audio, joystick)
    if(configuration->getVideoFlag() == 1)
    {
        sdl_flags |= SDL_INIT_VIDEO;
    }


    if(configuration->getAudioFlag() == 1)
    {
        sdl_flags |= SDL_INIT_AUDIO;
    }


    if(configuration->getJoystickFlag() == 1)
    {
        sdl_flags |= SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER|SDL_INIT_HAPTIC;
    }


    // Init SDL
    if(SDL_Init(sdl_flags|SDL_INIT_TIMER) == -1)
    {
        std::cerr << "Error occurred in SDL_Init : " << LX_GetError() << std::endl;
        return false;
    }

    // Load mappings from another configuration file
    if(SDL_WasInit(SDL_INIT_GAMECONTROLLER != 0))
    {
        SDL_GameControllerAddMappingsFromFile(mappingFile.c_str());
    }

    if(configuration->getVideoFlag() == 1)
    {
        // Init SDL_Image
        if( IMG_Init(img_flags) != img_flags)
        {
            std::cerr << "Error occurred in IMG_Init : " << IMG_GetError() << std::endl;
            SDL_Quit();
            return false;
        }
    }

    if(configuration->getTTF_Flag() == 1)
    {
        // Init SDL_ttf
        if(TTF_Init() == -1)
        {
            std::cerr << "Error occurred in TTF_Init : " << LX_GetError() << std::endl;
            IMG_Quit();
            SDL_Quit();
            return false;
        }
    }


    if(configuration->getAudioFlag() == 1)
    {
        // Init SDL_Mixer
        err = Mix_Init(MIX_INIT_OGG);

        if(err == -1)
        {
            std::cerr << "Error occurred in Mix_Init : " << LX_GetError() << std::endl;
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
            return false;
        }

        err = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,LX_MIXER_STEREO_SOUND,LX_MIXER_DEFAULT_CHUNKSIZE);

        if( err < 0)
        {
            std::cerr << "Error occurred in Mix_OpenAudio : " << LX_GetError() << std::endl;
            Mix_Quit();
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
            return false;
        }
    }

    if(configuration->getOpenGL_Flag() == 1)
    {
        err = SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);

        if(err == -1)
            std::cerr << "Error Attribute : " << LX_GetError() << std::endl;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        if(err == -1)
            std::cerr << "Error Attribute : " << LX_GetError() << std::endl;
    }

    LX_WindowManager::init();

    return true;
}



/**
*   @fn void LX_Quit(void)
*
*   Shut down the engine
*
*   @note This function automatically calls LX_WindowManager::destroy()
*
*/
void LX_Quit(void)
{
    LX_WindowManager::destroy();

    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    LX_Configuration::destroy();
}


