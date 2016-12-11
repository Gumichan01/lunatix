
/*
*   Copyright (C) 2016 Luxon Jean-Pierre
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

namespace
{
const int CONF_WIDTH  = 800;
const int CONF_HEIGHT = 600;
};

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
    UTF8string font_file;   // Font file
    int font_size;          // Font size
    int width;              // Width
    int height;             // Height
};

static LX_InternalConfig _conf;


void readFile_(std::ifstream& f,LX_InternalConfig& config);
void loadFileConfig_(LX_InternalConfig& config);

void readFile_(std::ifstream& f,LX_InternalConfig& config)
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

    // depracated: remove these two regular expression
    const std::regex FONT_REG("font=.+",std::regex::extended);
    const std::regex SIZE_REG("size=.+",std::regex::extended);

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

        case 6:
            if(std::regex_match(line,FONT_REG))
            {
                config.font_file = s;
                cpt++;
            }
            break;

        case 7:
            if(std::regex_match(line,SIZE_REG))
            {
                config.font_size = atoi(s.c_str());
                cpt++;
            }
            break;

        default:
            break;
        }
    }
}

void loadFileConfig_(LX_InternalConfig& config)
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

    _conf = {0,0,0,0,0,0,UTF8string(""),0,0,0};
    readFile_(f,config);
    f.close();
}


/* LX_ConfigurationException */

LX_ConfigurationException::LX_ConfigurationException(UTF8string err)
    : _string_error(err) {}

const char * LX_ConfigurationException::what() const noexcept
{
    return _string_error.utf8_str();
}

LX_ConfigurationException::~LX_ConfigurationException() noexcept {}


/* LX_Configuration */

LX_Configuration::LX_Configuration()
{
    loadFlags_();
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

void LX_Configuration::loadFlags_()
{
    LX_Config::loadFileConfig_(_conf);
    _conf.width  = CONF_WIDTH;
    _conf.height = CONF_HEIGHT;
}

bool LX_Configuration::getVideoFlag() const
{
    return _conf.video_flag;
}

bool LX_Configuration::getVSyncFlag() const
{
    return _conf.vsync_flag;
}

bool LX_Configuration::getTTFFlag() const
{
    return _conf.ttf_flag;
}

bool LX_Configuration::getAudioFlag() const
{
    return _conf.audio_flag;
}

bool LX_Configuration::getGamepadFlag() const
{
    return _conf.gamepad_flag;
}

bool LX_Configuration::getOpenGLFlag() const
{
    return _conf.opengl_flag;
}

int LX_Configuration::getWinWidth() const
{
    return _conf.width;
}

int LX_Configuration::getWinHeight() const
{
    return _conf.height;
}

};
