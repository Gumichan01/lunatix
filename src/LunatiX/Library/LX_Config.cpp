
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
*	@file LX_Config.cpp
*	@brief The configuration class implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <cstring>
#include <exception>
#include <sstream>

#include <Lua/lua.hpp>
#include <LunatiX/LX_Config.hpp>
#include <LunatiX/LX_Error.hpp>


namespace
{
const int DEFAULT_VIDEO_FLAG = 1;
const int DEFAULT_VSYNC_FLAG = 0;
const int DEFAULT_TTF_FLAG = 1;
const int DEFAULT_AUDIO_FLAG = 1;
const int DEFAULT_GAMEPAD_FLAG = 1;
const int DEFAULT_OPENGL_FLAG = 0;
const int DEFAULT_FONT_SIZE = 0;
const int DEFAULT_WIDTH = 800;
const int DEFAULT_HEIGHT = 600;
const int DEFAULT_FULLSCREEN_FLAG = 0;
}

// unique instance
static LX_Configuration *instance = nullptr;


/**
*   @fn LX_ConfigurationException::LX_ConfigurationException(std::string err)
*
*   Build the exeception
*
*   @param err The error string
*
*/
LX_ConfigurationException::LX_ConfigurationException(UTF8string err)
{
    stringError = err;
}


/**
*   @fn const char * LX_ConfigurationException::what() const noexcept
*
*   Get the error string
*
*   @return The error string
*
*/
const char * LX_ConfigurationException::what() const noexcept
{
    return stringError.utf8_str();
}

/**
*   @fn LX_ConfigurationException::~LX_ConfigurationException() noexcept
*
*   Destroy the instance
*
*/
LX_ConfigurationException::~LX_ConfigurationException() noexcept {}


/*
*
*   Create an instance of the configuration
*
*/
LX_Configuration::LX_Configuration()
{
    // Load configuration
    loadSDLFlags();
}

LX_Configuration::~LX_Configuration() {}


/**
*   @fn void LX_Configuration::initConfig()
*
*   Launch the system configuration
*
*   @note   1: This function is automatically called in LX_Init()
*   @note   2: The instance of LX_Configuration may not be created.
*           So it will be necessary to call LX_GetError() to get
*           the error message
*
*/
void LX_Configuration::initConfig()
{
    if(instance == nullptr)
    {
        try
        {
            instance = new LX_Configuration();
        }
        catch(std::exception & ex_conf)
        {
            LX_SetError(ex_conf.what());
            instance = nullptr;
        }
    }
}


/**
*   @fn LX_Configuration * LX_Configuration::getInstance()
*
*   Get the unique instance of the LX_Configuration class
*
*   @return The instance of LX_Configuration
*
*   @note   The instance can be a null pointer
*           if LX_Configuration::initConfig() failed.
*
*/
LX_Configuration * LX_Configuration::getInstance()
{
    return instance;
}


/**
*   @fn void LX_Configuration::destroy()
*
*   Destroy the unique instance
*
*   @note It is not necessary to call this function because it is
*           automatically called when the engine subsystems are shut down
*
*/
void LX_Configuration::destroy()
{
    delete instance;
    instance = nullptr;
}

void LX_Configuration::loadSDLFlags()
{
    LX_ConfigLoader::loadSDLfileConfig(conf);
    LX_ConfigLoader::loadWindowFileConfig(conf);
}

/**
*   @fn bool LX_Configuration::getVideoFlag()
*
*   Get the video flag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getVideoFlag()
{
    return conf.video_flag;
}


/**
*   @fn bool LX_Configuration::getVSyncFlag()
*
*   Get the Vertical Synchronization (VSync) flag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getVSyncFlag()
{
    return conf.vsync_flag;
}


/**
*   @fn bool LX_Configuration::getTTFFlag()
*
*   Get the True Ttype Font (TTF) flag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getTTFFlag()
{
    return conf.ttf_flag;
}


/**
*   @fn bool LX_Configuration::getAudioFlag()
*
*   Get the audio flag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getAudioFlag()
{
    return conf.audio_flag;
}


/**
*   @fn bool LX_Configuration::getGamepadFlag()
*
*   Get the audio flag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getGamepadFlag()
{
    return conf.gamepad_flag;
}


/**
*   @fn bool LX_Configuration::getOpenGLFlag()
*
*   Get the opengl flag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getOpenGLFlag()
{
    return conf.opengl_flag;
}


/**
*   @fn char * LX_Configuration::getFontFile()
*
*   Get the font file
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
const char * LX_Configuration::getFontFile()
{
    return conf.font_file.utf8_str();
}


/**
*   @fn int LX_Configuration::getFontSize()
*
*   Get the font size
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
int LX_Configuration::getFontSize()
{
    return conf.font_size;
}


/**
*   @fn int LX_Configuration::getWinWidth()
*
*   Get the window width
*
*   @return The width
*
*/
int LX_Configuration::getWinWidth()
{
    return conf.width;
}


/**
*   @fn int LX_Configuration::getWinHeight()
*
*   Get the window height
*
*   @return The height
*
*/
int LX_Configuration::getWinHeight()
{
    return conf.height;
}


/**
*   @fn bool LX_Configuration::getFullscreenFlag()
*
*   Get the fullscreen tag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getFullscreenFlag()
{
    return conf.fullscreen_flag;
}

