
/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_ConfigLoader.cpp
*    @brief The configuration loader class implementation
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/LX_ConfigLoader.hpp>
#include <LunatiX/LX_Log.hpp>

#include <cstdlib>
#include <fstream>
#include <regex>


namespace LX_Config
{

/*
    Read the file and retrieve data in order to put it
    into the configuration structure
*/
void readFile_(std::ifstream& f,LX_InternalConfig& config);

void readFile_(std::ifstream& f,LX_InternalConfig& config)
{
    const char SHARP = '#';
    const std::string ONE("1");
    const std::string EQUAL("=");
    const std::regex VIDEO_REG("video=[[:digit:]]+",std::regex::extended);
    const std::regex VSYNC_REG("vsync=[[:digit:]]+",std::regex::extended);
    const std::regex TTF_REG("ttf=[[:digit:]]+",std::regex::extended);
    const std::regex AUDIO_REG("audio=[[:digit:]]+",std::regex::extended);
    const std::regex GAMEPAD_REG("joystick=[[:digit:]]+",std::regex::extended);
    const std::regex OPENGL_REG("opengl=[[:digit:]]+",std::regex::extended);
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

void loadSDLfileConfig(LX_InternalConfig& config)
{
    const char * LX_SDL_FILE="config/lxsdl.cfg";

    std::ifstream f;
    f.open(LX_SDL_FILE,std::ios::in);

    if(f.is_open() == false)
    {
        LX_Log::logCritical(LX_Log::LX_LOG_SYSTEM,
                            "loadSDLfileConfig - Cannot open %s",LX_SDL_FILE);
        return;
    }

    readFile_(f,config);
    f.close();
}

};
