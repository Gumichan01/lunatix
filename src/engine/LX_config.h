#ifndef LX_LUA_LAYER_H_INCLUDED
#define LX_LUA_LAYER_H_INCLUDED



/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_config.h
*	@brief The LunatiX_engine configuration class
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 7th, 2015
*
*/

#include <iostream>


#define LUA_CONFIG_FILE "script/LX_config.lua"   /**< The lua file the engine uses for the configuration loading*/
#define LUAC_CONFIG_FILE "script/LX_config.luac"  /**< The compiled lua file the engine uses for the configuration loading*/

/**
*   @class LX_configuration_exception
*   @brief The Window_creation_exception class.
*
*   This class describes the exception occured when the configuration construction fails.
*
*/
class LX_configuration_exception : public std::exception
{

    std::string str_err;                    /**< The string where the error message will be conteined*/

    public :

    LX_configuration_exception(std::string err);

    const char * what() const throw();

    ~LX_configuration_exception() throw();
};

/**
*   @class LX_configuration
*   @brief The LX_configuration class.
*
*   This class assure the communication between the LunatiX_engine and the Lua library
*
*/

class LX_configuration
{

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
    void setVideoFlag();
    void setTTF_Flag();
    void setAudioFlag();
    void setJoystickFlag();
    void setOpenGL_Flag();
    void setFontFile();
    void setFontSize();
    void setWinWidth();
    void setWinHeight();
    void setFullscreenFlag();


    LX_configuration();


    public :

    static LX_configuration * getInstance();
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

    ~LX_configuration();

};


#endif // LX_LUA_LAYER_H_INCLUDED











