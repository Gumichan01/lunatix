#ifndef LX_LUA_LAYER_H_INCLUDED
#define LX_LUA_LAYER_H_INCLUDED



/*
*	Copyright (C) 2014 Luxon Jean-Pierre
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
*	@version 0.1
*	@date August 20th, 2014
*
*
*/

#include <iostream>
#include <string>
#include <exception>

#include <Lua/lua.hpp>

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
    public :

    std::string str_err;                    /**< The string where the error message will be conteined*/
/**
*   @fn LX_configuration_exception(std::string err)
*   Build the LX_configuration_exception class
*   @param err the error string
*/
    LX_configuration_exception(std::string err)
    {
        str_err = err;
    }

/**
*   @fn const char * what() const throw()
*   Get the error string
*   @return the error string
*/
    const char * what() const throw() {return str_err.c_str();}

    ~LX_configuration_exception() throw(){}
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


    LX_configuration()
    {
        //initialize the variables at the default values
        videoFlag = 0;
        ttf_Flag = 0;
        audioFlag = 0;
        joystickFlag = 0;
        openglFlag = 0;
        font_size = 0;
        width = 800;
        height = 600;
        fullscreenFlag = 0;

        //loading configuration
        setVideoFlag();
        setTTF_Flag();
        setAudioFlag();
        setJoystickFlag();
        setOpenGL_Flag();
        setFontFile();
        setFontSize();
        setWinWidth();
        setWinHeight();
        setFullscreenFlag();

    }


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

    ~LX_configuration(){}

};


#endif // LX_LUA_LAYER_H_INCLUDED











