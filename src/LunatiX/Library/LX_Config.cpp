
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file LX_Config.cpp
*   @brief The configuration class implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*
*/

#include <LunatiX/LX_Config.hpp>
#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_Log.hpp>

#include <exception>
#include <fstream>
#include <regex>

namespace LX_Config
{

// unique instance
static LX_Configuration *instance = nullptr;


/* LX_ConfigLoader */

struct LX_InternalConfig
{
    bool video_flag;        // Video flag
    bool vsync_flag;        // VSync flag
    bool ttf_flag;          // TTF flag
    bool audio_flag;        // Audio flag
    bool gamepad_flag;      // Gamepad flag
    bool opengl_flag;       // OpenGL flag
};

static LX_InternalConfig _conf;


void readFile_(std::ifstream& f,LX_InternalConfig& config) noexcept;
void loadFileConfig_(LX_InternalConfig& config) noexcept;

void readFile_(std::ifstream& f,LX_InternalConfig& config) noexcept
{
    const char SHARP = '#';
    const std::string ONE("1");
    const std::string EQUAL("=");
    const std::regex VIDEO_REG("video=[[:digit:]]+",std::regex::extended);
    const std::regex VSYNC_REG("vsync=[[:digit:]]+",std::regex::extended);
    const std::regex TTF_REG("ttf=[[:digit:]]+",std::regex::extended);
    const std::regex AUDIO_REG("audio=[[:digit:]]+",std::regex::extended);
    const std::regex GAMEPAD_REG("gamepad=[[:digit:]]+",std::regex::extended);
    const std::regex OPENGL_REG("opengl=[[:digit:]]+",std::regex::extended);

    int cpt = 0;
    std::string line;

    while(getline(f,line))
    {
        if(line.empty() || line[0] == SHARP)
            continue;

        const std::string s = line.substr(line.find(EQUAL) + 1);

        switch(cpt)
        {
        case 0:
            if(std::regex_match(line,VIDEO_REG))
            {
                config.video_flag = (s == ONE);
                cpt++;
            }
            break;

        case 1:
            if(std::regex_match(line,VSYNC_REG))
            {
                config.vsync_flag = (s == ONE);
                cpt++;
            }
            break;

        case 2:
            if(std::regex_match(line,TTF_REG))
            {
                config.ttf_flag = (s == ONE);
                cpt++;
            }
            break;

        case 3:
            if(std::regex_match(line,AUDIO_REG))
            {
                config.audio_flag = (s == ONE);
                cpt++;
            }
            break;

        case 4:
            if(std::regex_match(line,GAMEPAD_REG))
            {
                config.gamepad_flag = (s == ONE);
                cpt++;
            }
            break;

        case 5:
            if(std::regex_match(line,OPENGL_REG))
            {
                config.opengl_flag = (s == ONE);
                cpt++;
            }
            break;

        default:
            break;
        }
    }
}

void loadFileConfig_(LX_InternalConfig& config) noexcept
{
    const char * LX_CFG_FILE = "config/lunatix.cfg";

    std::ifstream f;
    f.open(LX_CFG_FILE,std::ios::in);

    if(f.is_open() == false)
    {
        LX_Log::logCritical(LX_Log::LX_LOG_SYSTEM,
                            "loadFileConfig - Cannot open %s",LX_CFG_FILE);
        return;
    }

    _conf = {0,0,0,0,0,0};
    readFile_(f,config);
    f.close();
}


/* LX_Configuration */

LX_Configuration::LX_Configuration() noexcept
{
    loadFlags_();
}

LX_Configuration::~LX_Configuration() {}

void LX_Configuration::initConfig() noexcept
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

LX_Configuration * LX_Configuration::getInstance() noexcept
{
    return instance;
}

void LX_Configuration::destroy() noexcept
{
    delete instance;
    instance = nullptr;
}

void LX_Configuration::loadFlags_() noexcept
{
    LX_Config::loadFileConfig_(_conf);
}

bool LX_Configuration::getVideoFlag() const noexcept
{
    return _conf.video_flag;
}

bool LX_Configuration::getVSyncFlag() const noexcept
{
    return _conf.vsync_flag;
}

bool LX_Configuration::getTTFFlag() const noexcept
{
    return _conf.ttf_flag;
}

bool LX_Configuration::getAudioFlag() const noexcept
{
    return _conf.audio_flag;
}

bool LX_Configuration::getGamepadFlag() const noexcept
{
    return _conf.gamepad_flag;
}

bool LX_Configuration::getOpenGLFlag() const noexcept
{
    return _conf.opengl_flag;
}

}
