

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX-engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_config.cpp
*	@brief The LunatiX_engine configuration class
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 7th, 2015
*
*
*/

#include <cstdlib>
#include <cstring>

#include <string>
#include <exception>

#include "LX_Config.hpp"

// unique instance
static LX_Configuration *instance;



/**
*   @fn LX_ConfigurationException::LX_ConfigurationException(std::string err)
*
*   Build the LX_ConfigurationException class
*
*   @param err the error string
*
*/
LX_ConfigurationException::LX_ConfigurationException(std::string err)
{
    str_err = err;
}

/**
*   @fn const char * LX_ConfigurationException::what() const throw()
*
*   Get the error string
*
*   @return the error string
*
*/
const char * LX_ConfigurationException::what() const throw()
{
    return str_err.c_str();
}


/**
*   @fn LX_ConfigurationException::~LX_ConfigurationException() throw()
*
*   Destroy the instance
*
*/
LX_ConfigurationException::~LX_ConfigurationException() throw(){}





/**
*   @fn LX_Configuration::LX_Configuration()
*
*   Create an instance of the configuration
*
*/
LX_Configuration::LX_Configuration()
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
    /*setVideoFlag();
    setTTF_Flag();
    setAudioFlag();
    setJoystickFlag();
    setOpenGL_Flag();
    setFontFile();
    setFontSize();
    setWinWidth();
    setWinHeight();
    setFullscreenFlag();*/
    setFlags();
}


/**
*   @fn LX_Configuration::~LX_Configuration()
*
*   Destroy the instance
*
**/
LX_Configuration::~LX_Configuration(){}

/**
*   @fn LX_Configuration * LX_Configuration::getInstance()
*
*   Get the unique instance of the LX_Configuration class
*
*   @return the instance of LX_Configuration
*
*   @note If no instance exists, a new unique instance will be created and returned
*   @note otherwise, a current instance will be returned
*
*/
LX_Configuration * LX_Configuration::getInstance()
{

    if(instance == NULL)
    {
        try
        {
            instance = new LX_Configuration();
        }
        catch(std::exception & ex_conf)
        {
            std::cerr << "Exception occurred at LX_Configuration constructor : " << ex_conf.what() << std::endl;
            instance = NULL;
        }
    }

    return instance;
}



/**
*
*   @fn void LX_Configuration::destroy()
*
*   Destroy the unique instance
*
*   @warning you must call this function to prevent a memory leak if you called LX_Configuration::getInstances()
*
*/
void LX_Configuration::destroy()
{
    delete instance;
    instance = NULL;
}


/**
*
*   @fn void LX_Configuration::assignString(lua_State * state, char *str, int len)
*
*   Get the string from the lua stack
*
*   @param state The Lua state
*   @param str the string you will store the extracted string
*   @param len the length of the string str
*
*   @warning if state or str is NULL, a segmentation fault may occur
*
*/
void LX_Configuration::assignString(lua_State * state, char *str, int len)
{
    char *tmp;
    memset(str,0,len);
    tmp = (char *) lua_tostring(state,-2);

    if(tmp != NULL)
        strncpy(str,tmp,len-2);

    str[len-1] = '\0';
}



/**
*   @fn void LX_Configuration::setFlags(void)
*
*   Set the flags from configuration files
*
*   @warning This function need to use LX_config.luac to work,
*               otherwise, a LX_ConfigurationException exception will occur
*/
void LX_Configuration::setFlags(void)
{
    int t = 1;
    const std::string luaFunction = "getFlags";
    std::string key;
    char tmp[16];
    lua_State *state = NULL;

    // Constant values
    const std::string VIDEO_KEY = "video";
    const std::string TTF_KEY = "ttf";
    const std::string AUDIO_KEY = "audio";
    const std::string JOYSTICK_KEY = "joystick";
    const std::string OPENGL_KEY = "opengl";
    const std::string FONT_KEY = "font";
    const std::string SIZE_KEY = "size";
    const std::string WIDTH_KEY = "width";
    const std::string HEIGHT_KEY = "height";
    const std::string FULLSCREEN_KEY = "fullscreen";


    state = lua_open();

    if(state == NULL)
        throw LX_ConfigurationException("Error occured in LX_Configuration::setFlags : Internal error\n");

    // Open standard lua libraries
    luaL_openlibs(state);

    // Open of the Lua file
    if(luaL_dofile(state,LUAC_CONFIG_FILE) != 0)
    {
        std::cerr << "Error occured in LX_Configuration::setVideoFlag : " << lua_tostring(state,-1) << std::endl;
        lua_close(state);
        throw LX_ConfigurationException("The lua file does not exist or is corrupted");
    }

    // Get the function
    lua_getglobal(state,luaFunction.c_str());

    // Is it what we want ?
    if(!lua_isfunction(state,-1))
    {
        std::cerr << "Error occured in LX_Configuration::setVideoFlag : The Lua function "
                        << luaFunction << " does not exist" << std::endl;

        lua_close(state);
        throw LX_ConfigurationException("The Lua function getVideo does not exist");
    }
    else
    {
        // Call the function
        lua_call(state,0,1);

        lua_pushnil(state);

        while(lua_next(state, t))
        {
            /// @todo Get the key, compare with constant keys
            assignString(state,tmp,sizeof(tmp));

            if(strlen(tmp) == 0)
            {
                    lua_pop(state,1);
                    continue;
            }

            key.assign(tmp);

            //std::cout << "key : " << key << " | " << lua_tostring(state,-1) << std::endl;

            // Video flasg
            if(key.compare(0,VIDEO_KEY.length(),VIDEO_KEY) == 0)
            {
                videoFlag = atoi((char *) lua_tostring(state,-1));
            }

            // TTF flag
            if(key.compare(0,TTF_KEY.length(),TTF_KEY) == 0)
            {
                ttf_Flag = atoi((char *) lua_tostring(state,-1));
            }

            // Audio flag
            if(key.compare(0,AUDIO_KEY.length(),AUDIO_KEY) == 0)
            {
                audioFlag = atoi((char *) lua_tostring(state,-1));
            }

            // Joystick flag
            if(key.compare(0,JOYSTICK_KEY.length(),JOYSTICK_KEY) == 0)
            {
                joystickFlag = atoi((char *) lua_tostring(state,-1));
            }

            // OpenGL flag
            if(key.compare(0,OPENGL_KEY.length(),OPENGL_KEY) == 0)
            {
                openglFlag = atoi((char *) lua_tostring(state,-1));
            }

            // Font file flag
            if(key.compare(0,FONT_KEY.length(),FONT_KEY) == 0)
            {
                font_file = (char *) lua_tostring(state,-1);
            }

            // Size flag
            if(key.compare(0,SIZE_KEY.length(),SIZE_KEY) == 0)
            {
                font_size = atoi((char *) lua_tostring(state,-1));
            }

            // Width flag
            if(key.compare(0,WIDTH_KEY.length(),WIDTH_KEY) == 0)
            {
                width = atoi((char *) lua_tostring(state,-1));
            }

            // Height flag
            if(key.compare(0,HEIGHT_KEY.length(),HEIGHT_KEY) == 0)
            {
                height = atoi((char *) lua_tostring(state,-1));
            }

            // Fullscreen flag
            if(key.compare(0,FULLSCREEN_KEY.length(),FULLSCREEN_KEY) == 0)
            {
                fullscreenFlag = atoi((char *) lua_tostring(state,-1));
            }

            lua_pop(state,1);
        }

    }

    lua_pop(state,1);
    lua_close(state);
}




/**
*
*   @fn int LX_Configuration::getVideoFlag()
*
*   Get the video flag
*
*   @return the video configuration
*
*/
int LX_Configuration::getVideoFlag()
{
    return videoFlag;
}


/**
*
*   @fn int LX_Configuration::getTTF_Flag()
*
*   Get the ttf flag
*
*   @return the ttf configuration
*
*/
int LX_Configuration::getTTF_Flag()
{
    return ttf_Flag;
}


/**
*
*   @fn int LX_Configuration::getAudioFlag()
*
*   Get the audio flag
*
*   @return the audio configuration
*
*/
int LX_Configuration::getAudioFlag()
{
    return audioFlag;
}



/**
*
*   @fn int LX_Configuration::getJoystickFlag()
*
*   Get the audio flag
*
*   @return the joystick configuration
*
*/
int LX_Configuration::getJoystickFlag()
{
    return joystickFlag;
}


/**
*
*   @fn int LX_Configuration::getOpenGL_Flag()
*
*   Get the opengl flag
*
*   @return the opengl configuration
*
*/
int LX_Configuration::getOpenGL_Flag()
{
    return openglFlag;
}


/**
*
*   @fn char * LX_Configuration::getFontFile()
*
*   Get the font file
*
*   @return the font file
*
*/
const char * LX_Configuration::getFontFile()
{
    return font_file.c_str();
}


/**
*
*   @fn int LX_Configuration::getFontSize()
*
*   Get the font size
*
*   @return the font size
*
*/
int LX_Configuration::getFontSize()
{
    return font_size;
}



/**
*
*   @fn int LX_Configuration::getWinWidth()
*
*   Get the window width
*
*   @return the width
*
*/
int LX_Configuration::getWinWidth()
{
    return width;
}



/**
*
*   @fn int LX_Configuration::getWinHeight()
*
*   Get the window height
*
*   @return the height
*
*/
int LX_Configuration::getWinHeight()
{
    return height;
}



/**
*
*   @fn int LX_Configuration::getFullscreenFlag()
*
*   Get the fullscreen tag
*
*   @return the fullscreen tag
*
*/
int LX_Configuration::getFullscreenFlag()
{
    return fullscreenFlag;
}











