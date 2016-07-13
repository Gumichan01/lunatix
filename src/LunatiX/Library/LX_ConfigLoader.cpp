
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
*	@file LX_ConfigLoader.cpp
*	@brief The configuration loader class implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/LX_ConfigLoader.hpp>
#include <LunatiX/LX_Log.hpp>

#include <cstdlib>
#include <fstream>
#include <regex>

const std::regex videoreg("video=[[:digit:]]+",std::regex::extended);
const std::regex vsyncreg("vsync=[[:digit:]]+",std::regex::extended);
const std::regex ttfreg("ttf=[[:digit:]]+",std::regex::extended);
const std::regex audioreg("audio=[[:digit:]]+",std::regex::extended);
const std::regex gamepadreg("joystick=[[:digit:]]+",std::regex::extended);
const std::regex openglreg("opengl=[[:digit:]]+",std::regex::extended);
const std::regex fontreg("font=.+",std::regex::extended);
const std::regex sizereg("size=.+",std::regex::extended);
const std::regex widthreg("width=.+",std::regex::extended);
const std::regex heigthreg("height=.+",std::regex::extended);
const std::regex fullscreenreg("fullscreen=[[:digit:]]+",std::regex::extended);
const std::string ONE("1");
const char SHARP = '#';


namespace LX_Config_Loader
{

void loadSDLfileConfig(LX_InternalConfig& config)
{
    std::ifstream f;
    f.open(LX_SDL_FILE,std::ios::in);

    if(f.is_open() == false)
    {
        LX_Log::logCritical(LX_Log::LX_LOG_SYSTEM,
                            "loadSDLfileConfig - Cannot open %s",LX_SDL_FILE);
        return;
    }

    int cpt = 0;
    std::string line;

    while(getline(f,line))
    {
        if(line.empty() || line[0] == SHARP)
            continue;

        std::string s = line.substr(line.find("=") + 1);

        switch(cpt)
        {
        case 0:
            if(std::regex_match(line,videoreg))
            {
                config.video_flag = (s == ONE);
                cpt++;
            }
            break;

        case 1:
            if(std::regex_match(line,vsyncreg))
            {
                config.vsync_flag = (s == ONE);
                cpt++;
            }
            break;

        case 2:
            if(std::regex_match(line,ttfreg))
            {
                config.ttf_flag = (s == ONE);
                cpt++;
            }
            break;

        case 3:
            if(std::regex_match(line,audioreg))
            {
                config.audio_flag = (s == ONE);
                cpt++;
            }
            break;

        case 4:
            if(std::regex_match(line,gamepadreg))
            {
                config.gamepad_flag = (s == ONE);
                cpt++;
            }
            break;

        case 5:
            if(std::regex_match(line,openglreg))
            {
                config.opengl_flag = (s == ONE);
                cpt++;
            }
            break;

        case 6:
            if(std::regex_match(line,fontreg))
            {
                config.font_file = s;
                cpt++;
            }
            break;

        case 7:
            if(std::regex_match(line,sizereg))
            {
                config.font_size = atoi(s.c_str());
                cpt++;
            }
            break;

        default:
            break;
        }
    }

    f.close();
}

void loadWindowFileConfig(LX_InternalConfig& config)
{
    std::ifstream f;
    f.open(LX_WINFO_FILE,std::ios::in);

    if(f.is_open() == false)
    {
        LX_Log::logCritical(LX_Log::LX_LOG_SYSTEM,
                            "loadWindowFileConfig - Cannot open %s",
                            LX_SDL_FILE);
        return;
    }

    int cpt = 0;
    std::string line;

    while(getline(f,line))
    {
        if(line.empty() || line[0] == SHARP)
            continue;

        std::string s = line.substr(line.find("=") + 1);

        switch(cpt)
        {
        case 0:
            if(std::regex_match(line,widthreg))
            {
                config.width = atoi(s.c_str());
                cpt++;
            }
            break;

        case 1:
            if(std::regex_match(line,heigthreg))
            {
                config.height = atoi(s.c_str());
                cpt++;
            }
            break;

        case 2:
            if(std::regex_match(line,fullscreenreg))
            {
                config.fullscreen_flag = (s == ONE);
                cpt++;
            }
            break;

        default:
            break;
        }
    }

    f.close();
}

};
