
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file Library.cpp
*   @brief The implementatino of the library ressources
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/Library.hpp>
#include <Lunatix/Mixer.hpp>
#include <Lunatix/WindowManager.hpp>
#include <Lunatix/OpenGL.hpp>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <GL/gl.h>

using namespace lx::Config;

namespace
{

const int LX_MIX_AUDIO_FREQUENCY = 44100;   /**< The default audio frequency                */
const int LX_MIX_STEREO_SOUND = 2;          /**< The stereo variable for the mix namespace  */
const int LX_MIX_DEFAULT_CHUNKSIZE = 1024;  /**< The default chunsize for the mix namespace */

bool initAudio() noexcept
{
    if ( Mix_Init( MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MP3 ) == 0 )
        return false;

    if ( Mix_OpenAudio( LX_MIX_AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT,
                        LX_MIX_STEREO_SOUND, LX_MIX_DEFAULT_CHUNKSIZE ) == -1 )
    {
        Mix_Quit();
        return false;
    }

    return true;
}

bool loadMainSystem()
{
    uint32_t sdl_flags = 0;

    const lx::Configuration& config = lx::Configuration::getInstance();

    // Video flag
    if ( config.getVideoFlag() )
        sdl_flags |= SDL_INIT_VIDEO;

    // Audio flag
    if ( config.getAudioFlag() )
        sdl_flags |= SDL_INIT_AUDIO;

    // Gamepad flag
    if ( config.getGamepadFlag() )
        sdl_flags |= SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC;

    return SDL_Init( sdl_flags | SDL_INIT_TIMER ) == 0;
}

void loadGamepadSubSystem()
{
    // Load mappings from another configuration file
    const std::string mappingFile( "config/gamecontrollerdb.txt" );

    if ( SDL_WasInit( SDL_INIT_GAMECONTROLLER ) != 0 )
        SDL_GameControllerAddMappingsFromFile( mappingFile.c_str() );
}

bool loadImgSubSystem()
{
    int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;

    if ( lx::Configuration::getInstance().getVideoFlag() )
    {
        if ( IMG_Init( img_flags ) != img_flags )
        {
            SDL_Quit();
            return false;
        }
    }

    return true;
}

bool loadTrueTypeFontSubSystem()
{
    if ( lx::Configuration::getInstance().getTTFFlag() )
    {
        if ( TTF_Init() == -1 )
        {
            IMG_Quit();
            SDL_Quit();
            return false;
        }
    }

    return true;
}

bool loadAudioSubSystem()
{
    if ( lx::Configuration::getInstance().getAudioFlag() )
    {
        if ( !initAudio() )
        {
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
            return false;
        }
    }

    return true;
}

void loadOpenGLSubSystem()
{
    if ( lx::Configuration::getInstance().getOpenGLFlag() )
    {
        LX_Graphics::LX_OpenGL::setAttribute( SDL_GL_CONTEXT_PROFILE_MASK,
                                              SDL_GL_CONTEXT_PROFILE_CORE );
        LX_Graphics::LX_OpenGL::setAttribute( SDL_GL_CONTEXT_MAJOR_VERSION,
                                              LX_Graphics::LX_OpenGL::MAJOR_VERSION );
        LX_Graphics::LX_OpenGL::setAttribute( SDL_GL_CONTEXT_MINOR_VERSION,
                                              LX_Graphics::LX_OpenGL::MINOR_VERSION );
    }
}

}


bool lx::init() noexcept
{
    if ( !loadMainSystem() )
        return false;

    if ( !loadImgSubSystem() )
        return false;

    if ( !loadTrueTypeFontSubSystem() )
        return false;

    if ( !loadAudioSubSystem() )
        return false;

    loadGamepadSubSystem();
    loadOpenGLSubSystem();
    return true;
}


bool lx::setSDLConfig( const std::string& sdlconfig_name, const std::string& sdlconfig_value ) noexcept
{
    return SDL_SetHint( sdlconfig_name.c_str(), sdlconfig_value.c_str() ) == SDL_TRUE;
}

const std::string lx::getSDLConfig( const std::string& sdlconfig_name ) noexcept
{
    const char * SDL_CONFIG = SDL_GetHint( sdlconfig_name.c_str() );
    return SDL_CONFIG == nullptr ? "" : std::string( SDL_CONFIG );
}


void lx::quit() noexcept
{
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
