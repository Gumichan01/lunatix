

/*
*	Copyright (C) 2014-2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_config.cpp
*	@brief The LX_Configuration implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.3
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
*   Build the exeception
*
*   @param err The error string
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
*   @return The error string
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
    videoFlag = 1;
    ttf_Flag = 1;
    audioFlag = 1;
    joystickFlag = 1;
    openglFlag = 0;
    font_size = 0;
    width = 800;
    height = 600;
    fullscreenFlag = 0;

    //loading configuration
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
*   @fn void LX_Configuration::initConfig()
*
*   Launch the system configuration
*
*   @note  1 : This function is just a shortcut of LX_Configuration::getInstance()
*               but it does not return the reference to the instance.
*               So you need to call getInstance() to get it
*   @note  2 : Normally you do not need to call it because it is already done in LX_Init()
*
*/
void LX_Configuration::initConfig()
{
    LX_Configuration::getInstance();
}



/**
*   @fn LX_Configuration * LX_Configuration::getInstance()
*
*   Get the unique instance of the LX_Configuration class
*
*   @return The instance of LX_Configuration
*
*   @note If no instance exists, a new unique instance will be created and returned
*           otherwise, a current instance will be returned
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
*   @fn void LX_Configuration::destroy()
*
*   Destroy the unique instance
*
*   @note It is not necessary to call this function because it is
*           automatically called when the engine subsystems are shut down
*
*/
void LX_Configuration::destroy()
{
    delete instance;
    instance = NULL;
}


/**
*   @fn void LX_Configuration::assignString(lua_State * state, char *str, int len)
*
*   Get the string from the lua stack
*
*   @param state The Lua state
*   @param str The string you will store the extracted string
*   @param len The length of the string str
*
*   @warning If state or str is NULL, a segmentation fault may occur
*               If len is 0 or less than the string you want to take from the lua state,
*               the behaviour is undefined.
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
    {
        std::cerr << "Error occured in LX_Configuration::setFlags : Internal error" << std::endl;
        return;
    }

    // Open standard lua libraries
    luaL_openlibs(state);

    // Open of the Lua file
    if(luaL_dofile(state,LUAC_CONFIG_FILE) != 0)
    {
        std::cerr << "Error occured in LX_Configuration::setFlags : " << lua_tostring(state,-1) << std::endl;
        lua_close(state);
        return;
    }

    // Get the function
    lua_getglobal(state,luaFunction.c_str());

    // Is it what we want ?
    if(!lua_isfunction(state,-1))
    {
        std::cerr << "Error occured in LX_Configuration::setFlags : The Lua function "
                        << luaFunction << " does not exist" << std::endl;

        lua_close(state);
        return;
    }
    else
    {
        // Call the function
        lua_call(state,0,1);

        lua_pushnil(state);

        while(lua_next(state, t))
        {
            assignString(state,tmp,sizeof(tmp));

            if(strlen(tmp) == 0)
            {
                    lua_pop(state,1);
                    continue;
            }

            key.assign(tmp);


            // Video flag
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
*   @fn int LX_Configuration::getVideoFlag()
*
*   Get the video flag
*
*   @return The video flag
*
*/
int LX_Configuration::getVideoFlag()
{
    return videoFlag;
}


/**
*   @fn int LX_Configuration::getTTF_Flag()
*
*   Get the ttf flag
*
*   @return The ttf flag
*
*/
int LX_Configuration::getTTF_Flag()
{
    return ttf_Flag;
}


/**
*   @fn int LX_Configuration::getAudioFlag()
*
*   Get the audio flag
*
*   @return The audio flag
*
*/
int LX_Configuration::getAudioFlag()
{
    return audioFlag;
}



/**
*   @fn int LX_Configuration::getJoystickFlag()
*
*   Get the audio flag
*
*   @return The joystick flag
*
*/
int LX_Configuration::getJoystickFlag()
{
    return joystickFlag;
}


/**
*   @fn int LX_Configuration::getOpenGL_Flag()
*
*   Get the opengl flag
*
*   @return The opengl flag
*
*/
int LX_Configuration::getOpenGL_Flag()
{
    return openglFlag;
}


/**
*   @fn char * LX_Configuration::getFontFile()
*
*   Get the font file
*
*   @return The font file
*
*/
const char * LX_Configuration::getFontFile()
{
    return font_file.c_str();
}


/**
*   @fn int LX_Configuration::getFontSize()
*
*   Get the font size
*
*   @return The font size
*
*/
int LX_Configuration::getFontSize()
{
    return font_size;
}



/**
*   @fn int LX_Configuration::getWinWidth()
*
*   Get the window width
*
*   @return The width
*
*/
int LX_Configuration::getWinWidth()
{
    return width;
}



/**
*   @fn int LX_Configuration::getWinHeight()
*
*   Get the window height
*
*   @return The height
*
*/
int LX_Configuration::getWinHeight()
{
    return height;
}



/**
*   @fn int LX_Configuration::getFullscreenFlag()
*
*   Get the fullscreen tag
*
*   @return The fullscreen flag
*
*/
int LX_Configuration::getFullscreenFlag()
{
    return fullscreenFlag;
}











