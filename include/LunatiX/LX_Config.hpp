#ifndef LX_LUA_LAYER_H_INCLUDED
#define LX_LUA_LAYER_H_INCLUDED



/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Config.hpp
*	@brief The configuration class header
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/

#include <string>

#define LUAC_CONFIG_FILE "script/LX_config.luac"  /**< The compiled lua file the engine uses for the configuration loading */

struct lua_State;


/**
*   @class LX_ConfigurationException
*   @brief The exception class of LX_Configuration
*
*   This class describes the exception occured when
*   the configuration construction fails.
*
*/
class LX_ConfigurationException : public std::exception
{

    std::string stringError;

public :

    LX_ConfigurationException(std::string err);

    const char * what() const noexcept;

    ~LX_ConfigurationException() noexcept;
};


/**
*   @class LX_Configuration
*   @brief The The LunatiX engine configuration.
*/
class LX_Configuration
{

    // Variables
    int video_flag;
    int vsync_flag;
    int ttf_flag;
    int audio_flag;
    int joystick_flag;
    int opengl_flag;
    std::string fontFile;
    int fontSize;
    int width;
    int height;
    int fullscreen_flag;

    // private functions
    void assignString(lua_State * state, char *str, unsigned int len);
    void setFlags(void);

    LX_Configuration();
    LX_Configuration(LX_Configuration& c);
    LX_Configuration& operator =(LX_Configuration& c);


public :

    static void initConfig();
    static LX_Configuration * getInstance();
    static void destroy();

    bool getVideoFlag();
    bool getVSyncFlag();
    bool getTTFFlag();
    bool getAudioFlag();
    bool getJoystickFlag();
    bool getOpenGLFlag();
    const char * getFontFile();
    int getFontSize();
    int getWinWidth();
    int getWinHeight();
    bool getFullscreenFlag();

    ~LX_Configuration();

};


#endif // LX_LUA_LAYER_H_INCLUDED


