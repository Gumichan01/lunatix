
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
*   @file Config.cpp
*   @brief The configuration class implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/Config.hpp>
#include <Lunatix/Error.hpp>
#include <Lunatix/Log.hpp>

#include <fstream>
#include <regex>

namespace lx
{

namespace
{

const unsigned int NB_CONFIG = 6;

/* lx::ConfigLoader */

struct LX_InternalConfig final
{
    bool video_flag;        // Video flag
    bool vsync_flag;        // VSync flag
    bool ttf_flag;          // TTF flag
    bool audio_flag;        // Audio flag
    bool gamepad_flag;      // Gamepad flag
    bool opengl_flag;       // OpenGL flag
};

static LX_InternalConfig _conf;

unsigned int checkLine_( unsigned int cpt, LX_InternalConfig& config,
                         const std::string& line, const std::string& sub ) noexcept;
void readFile_( std::ifstream& f, LX_InternalConfig& config ) noexcept;
void loadFileConfig_( LX_InternalConfig& config ) noexcept;

/*
    Return 1 if a configuration has been found, 0 otherwise
*/
unsigned int checkLine_( unsigned int cpt, LX_InternalConfig& config,
                         const std::string& line, const std::string& sub ) noexcept
{
    if ( cpt >= NB_CONFIG )
        return 0;

    const std::string ONE( "1" );
    const std::regex VIDEO_REG( "video=[[:digit:]]+", std::regex::extended );
    const std::regex VSYNC_REG( "vsync=[[:digit:]]+", std::regex::extended );
    const std::regex TTF_REG( "ttf=[[:digit:]]+", std::regex::extended );
    const std::regex AUDIO_REG( "audio=[[:digit:]]+", std::regex::extended );
    const std::regex GAMEPAD_REG( "gamepad=[[:digit:]]+", std::regex::extended );
    const std::regex OPENGL_REG( "opengl=[[:digit:]]+", std::regex::extended );

    unsigned int ret = 0;
    const bool IS_ONE = ( sub == ONE );

    switch ( cpt )
    {
    case 0:
        if ( std::regex_match( line, VIDEO_REG ) )
        {
            config.video_flag = IS_ONE;
            ret = 1;
        }
        break;

    case 1:
        if ( std::regex_match( line, VSYNC_REG ) )
        {
            config.vsync_flag = IS_ONE;
            ret = 1;
        }
        break;

    case 2:
        if ( std::regex_match( line, TTF_REG ) )
        {
            config.ttf_flag = IS_ONE;
            ret = 1;
        }
        break;

    case 3:
        if ( std::regex_match( line, AUDIO_REG ) )
        {
            config.audio_flag = IS_ONE;
            ret = 1;
        }
        break;

    case 4:
        if ( std::regex_match( line, GAMEPAD_REG ) )
        {
            config.gamepad_flag = IS_ONE;
            ret = 1;
        }
        break;

    case 5:
        if ( std::regex_match( line, OPENGL_REG ) )
        {
            config.opengl_flag = IS_ONE;
            ret = 1;
        }
        break;

    default:        // unreachable code
        break;
    }

    return ret;
}

void readFile_( std::ifstream& f, LX_InternalConfig& config ) noexcept
{
    const char SHARP = '#';
    const std::string EQUAL( "=" );

    unsigned int cpt = 0U;
    std::string line;

    while ( cpt < NB_CONFIG && getline( f, line ) )
    {
        size_t pos = 0;

        if ( line.empty() || line[0] == SHARP
                || ( pos = line.find( EQUAL ) ) == std::string::npos )
            continue;

        // Get the string starting by the first character after '=' (substr())
        // check the line of a file
        cpt += checkLine_( cpt, config, line, line.substr( pos + 1 ) );
    }
}

void loadFileConfig_( LX_InternalConfig& config ) noexcept
{
    const std::string LX_CFG_FILE( "config/lunatix.cfg" );
    std::ifstream f( LX_CFG_FILE, std::ios::in );

    if ( f.is_open() )
    {
        _conf = {0, 0, 0, 0, 0, 0};
        readFile_( f, config );
        f.close();
    }
    else
    {
        lx::Log::logCritical( lx::Log::SYSTEM, "config - Cannot open %s",
                             LX_CFG_FILE.c_str() );
    }
}

}   // anonymous namespace


namespace Config
{

/* lx::Configuration */

lx::Configuration::lx::Configuration() noexcept
{
    loadFlags_();
}

lx::Configuration& lx::Configuration::getInstance() noexcept
{
    static lx::Configuration singleton;
    return singleton;
}


void lx::Configuration::loadFlags_() noexcept
{
    loadFileConfig_( _conf );
}

bool lx::Configuration::getVideoFlag() const noexcept
{
    return _conf.video_flag;
}

bool lx::Configuration::getVSyncFlag() const noexcept
{
    return _conf.vsync_flag;
}

bool lx::Configuration::getTTFFlag() const noexcept
{
    return _conf.ttf_flag;
}

bool lx::Configuration::getAudioFlag() const noexcept
{
    return _conf.audio_flag;
}

bool lx::Configuration::getGamepadFlag() const noexcept
{
    return _conf.gamepad_flag;
}

bool lx::Configuration::getOpenGLFlag() const noexcept
{
    return _conf.opengl_flag;
}

}   // Config

}   // lx
