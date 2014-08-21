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
*	@file LX_lua_layer.h
*	@brief The LunatiX_engine Lua layer
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
#include <Lua/lualib.h>
#include <Lua/lauxlib.h>

#define LUA_CONFIG_FILE "LX_config.lua" /**< The lua file the engine uses for the configuration loading*/

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

    LX_configuration_exception( std::string err)
    {
        str_err = err;
    }

    const char * what() const throw() {return str_err.c_str() ;}

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

    int videoTag;
    int ttf_Tag;
    int audioTag;
    int joystickTag;
    int openglTag;
    std::string font_file;
    int font_size;
    int width;
    int height;
    int fullscreenTag;

    // private functions
    void setVideoTag();
    void setTTF_Tag();
    void setAudioTag();
    void setJoystickTag();
    void setOpenGL_Tag();
    void setFontFile();
    void setFontSize();
    void setWinWidth();
    void setWinHeight();
    void setFullscreenTag();




    LX_configuration()
    {
        //initialize the variables at the default values
        videoTag = 0;
        ttf_Tag = 0;
        audioTag = 0;
        joystickTag = 0;
        openglTag = 0;
        font_size = 0;
        width = 800;
        height = 600;
        fullscreenTag = 0;


        try
        {
            //loading configuration
            setVideoTag();
            setTTF_Tag();
            setAudioTag();
            setJoystickTag();
            setOpenGL_Tag();
            setFontFile();
            setFontSize();
            setWinWidth();
            setWinHeight();
            setFullscreenTag();

        }
        catch(LX_configuration_exception & ex_conf)
        {
            std::cerr << "Exception occurred at LX_configuration constructor" << ex_conf.what() << std::endl;
        }

    }

    public :

    static LX_configuration * getInstance();


    int getVideoTag();
    int getTTF_Tag();
    int getAudioTag();
    int getJoystickTag();
    int getOpenGL_Tag();
    const char * getFontFile();
    int getFontSize();
    int getWinWidth();
    int getWinHeight();
    int getFullscreenTag();


    ~LX_configuration(){}

};


#endif // LX_LUA_LAYER_H_INCLUDED











