#ifndef LX_LUA_LAYER_H_INCLUDED
#define LX_LUA_LAYER_H_INCLUDED



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
*	@file LX_Config.hpp
*	@brief The configuration class header
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.5
*
*/

#include <iostream>

#include <Lua/lua.hpp>

#define LUA_CONFIG_FILE "script/LX_config.lua"   /**< The lua file the engine uses for the configuration loading */
#define LUAC_CONFIG_FILE "script/LX_config.luac"  /**< The compiled lua file the engine uses for the configuration loading */

/**
*   @class LX_ConfigurationException
*   @brief The exception class of LX_Configuration
*
*   This class describes the exception occured when the configuration construction fails.
*
*/
class LX_ConfigurationException : public std::exception
{

    std::string str_err;

    public :

    LX_ConfigurationException(std::string err);

    const char * what() const throw();

    ~LX_ConfigurationException() throw();
};

/**
*   @class LX_Configuration
*   @brief The configuration class.
*
*   This class loads the configuration
*
*/

class LX_Configuration
{

    // Variables
    int videoFlag;
    int ttf_Flag;
    int audioFlag;
    int joystickFlag;
    int openglFlag;
    std::string font_file;
    int font_size;
    int width;
    int height;
    int fullscreenFlag;

    // private functions
    void assignString(lua_State * state, char *str, int len);
    void setFlags(void);

    LX_Configuration();


    public :

    static void initConfig();
    static LX_Configuration * getInstance();
    static void destroy();

    int getVideoFlag();
    int getTTF_Flag();
    int getAudioFlag();
    int getJoystickFlag();
    int getOpenGL_Flag();
    const char * getFontFile();
    int getFontSize();
    int getWinWidth();
    int getWinHeight();
    int getFullscreenFlag();

    ~LX_Configuration();

};


#endif // LX_LUA_LAYER_H_INCLUDED


