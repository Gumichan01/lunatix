
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

#include <LunatiX/LX_Config.hpp>
#include <LunatiX/LX_Error.hpp>


// unique instance
static LX_Configuration *instance = nullptr;


LX_ConfigurationException::LX_ConfigurationException(UTF8string err)
{
    stringError = err;
}

const char * LX_ConfigurationException::what() const noexcept
{
    return stringError.utf8_str();
}

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

LX_Configuration * LX_Configuration::getInstance()
{
    return instance;
}

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

bool LX_Configuration::getVideoFlag()
{
    return conf.video_flag;
}

bool LX_Configuration::getVSyncFlag()
{
    return conf.vsync_flag;
}

bool LX_Configuration::getTTFFlag()
{
    return conf.ttf_flag;
}

bool LX_Configuration::getAudioFlag()
{
    return conf.audio_flag;
}

bool LX_Configuration::getGamepadFlag()
{
    return conf.gamepad_flag;
}

bool LX_Configuration::getOpenGLFlag()
{
    return conf.opengl_flag;
}

const char * LX_Configuration::getFontFile()
{
    return conf.font_file.utf8_str();
}

int LX_Configuration::getFontSize()
{
    return conf.font_size;
}

int LX_Configuration::getWinWidth()
{
    return conf.width;
}

int LX_Configuration::getWinHeight()
{
    return conf.height;
}

bool LX_Configuration::getFullscreenFlag()
{
    return conf.fullscreen_flag;
}
