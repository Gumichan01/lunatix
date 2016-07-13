
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
*	@file LX_Config.cpp
*	@brief The configuration class implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/


#include <cstring>

#include <exception>
#include <sstream>

#include <Lua/lua.hpp>

#include <LunatiX/LX_Config.hpp>
#include <LunatiX/LX_Error.hpp>


namespace
{
const int DEFAULT_VIDEO_FLAG = 1;
const int DEFAULT_VSYNC_FLAG = 0;
const int DEFAULT_TTF_FLAG = 1;
const int DEFAULT_AUDIO_FLAG = 1;
const int DEFAULT_GAMEPAD_FLAG = 1;
const int DEFAULT_OPENGL_FLAG = 0;
const int DEFAULT_FONT_SIZE = 0;
const int DEFAULT_WIDTH = 800;
const int DEFAULT_HEIGHT = 600;
const int DEFAULT_FULLSCREEN_FLAG = 0;
}

// unique instance
static LX_Configuration *instance = nullptr;


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
    stringError = err;
}


/**
*   @fn const char * LX_ConfigurationException::what() const noexcept
*
*   Get the error string
*
*   @return The error string
*
*/
const char * LX_ConfigurationException::what() const noexcept
{
    return stringError.c_str();
}


/**
*   @fn LX_ConfigurationException::~LX_ConfigurationException() noexcept
*
*   Destroy the instance
*
*/
LX_ConfigurationException::~LX_ConfigurationException() noexcept {}



/*
*
*   Create an instance of the configuration
*
*/
LX_Configuration::LX_Configuration()
    : video_flag(DEFAULT_VIDEO_FLAG), vsync_flag(DEFAULT_VSYNC_FLAG),
      ttf_flag(DEFAULT_TTF_FLAG), audio_flag(DEFAULT_AUDIO_FLAG),
      joystick_flag(DEFAULT_GAMEPAD_FLAG), opengl_flag(DEFAULT_OPENGL_FLAG),
      fontFile(),fontSize(DEFAULT_FONT_SIZE), width(DEFAULT_WIDTH),
      height(DEFAULT_HEIGHT), fullscreen_flag(DEFAULT_FULLSCREEN_FLAG)
{
    // Load configuration
    setFlags();
}


LX_Configuration::~LX_Configuration() {}



/**
*   @fn void LX_Configuration::initConfig()
*
*   Launch the system configuration
*
*   @note   1: This function is automatically called in LX_Init()
*   @note   2: The instance of LX_Configuration may not be created.
*           So it will be necessary to call LX_GetError() to get
*           the error message
*
*/
void LX_Configuration::initConfig()
{
    if(instance == nullptr)
    {
        try
        {
            instance = new LX_Configuration();
        }
        catch(std::exception & ex_conf)
        {
            LX_SetError(ex_conf.what());
            instance = nullptr;
        }
    }
}


/**
*   @fn LX_Configuration * LX_Configuration::getInstance()
*
*   Get the unique instance of the LX_Configuration class
*
*   @return The instance of LX_Configuration
*
*   @note   The instance can be a null pointer
*           if LX_Configuration::initConfig() failed.
*
*/
LX_Configuration * LX_Configuration::getInstance()
{
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
    instance = nullptr;
}


/*
*   Get the string from the lua stack
*
*   If state or str is not valid, a segmentation fault may occur
*   If len is 0 or less than the string length,
*   then the behaviour is undefined.
*
*/
void LX_Configuration::assignString(lua_State * state, char *str, unsigned int len)
{
    char *tmp;
    memset(str,0,len);
    tmp = (char *) lua_tostring(state,-2);

    if(tmp != nullptr)
        strncpy(str,tmp,len-2);

    str[len-1] = '\0';
}


/*
*   Set the flags from configuration files
*
*   This function need to use LX_config.luac to work,
*   otherwise, a LX_ConfigurationException exception will occur
*/
void LX_Configuration::setFlags(void)
{
    const std::string luaFunction = "getFlags";
    std::string key;
    lua_State *state = nullptr;

    // Constant values
    const std::string VIDEO_KEY = "video";
    const std::string VSYNC_KEY = "vsync";
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

    if(state == nullptr)
    {
        LX_SetError("Error occured in LX_Configuration::setFlags : Internal error");
        return;
    }

    // Open standard lua libraries
    luaL_openlibs(state);

    // Open of the Lua file
    if(luaL_dofile(state,LUAC_CONFIG_FILE) != 0)
    {
        LX_SetError(lua_tostring(state,-1));
        lua_close(state);
        return;
    }

    // Get the function
    lua_getglobal(state,luaFunction.c_str());

    // Is it what we want?
    if(!lua_isfunction(state,-1))
    {
        std::stringstream ss;
        std::string err;

        ss << "Error occured in LX_Configuration::setFlags : The Lua function "
           << luaFunction << " does not exist" << std::endl;
        err = ss.str();

        LX_SetError(err.c_str());
        lua_close(state);
        return;
    }
    else
    {
        int index = 1;
        char tmp[16];
        // Call the function
        lua_call(state,0,1);
        lua_pushnil(state);

        while(lua_next(state, index))
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
                video_flag = atoi((char *) lua_tostring(state,-1));
            }

            // VSync flag
            if(key.compare(0,VSYNC_KEY.length(),VSYNC_KEY) == 0)
            {
                vsync_flag = atoi((char *) lua_tostring(state,-1));
            }

            // TTF flag
            if(key.compare(0,TTF_KEY.length(),TTF_KEY) == 0)
            {
                ttf_flag = atoi((char *) lua_tostring(state,-1));
            }

            // Audio flag
            if(key.compare(0,AUDIO_KEY.length(),AUDIO_KEY) == 0)
            {
                audio_flag = atoi((char *) lua_tostring(state,-1));
            }

            // Joystick flag
            if(key.compare(0,JOYSTICK_KEY.length(),JOYSTICK_KEY) == 0)
            {
                joystick_flag = atoi((char *) lua_tostring(state,-1));
            }

            // OpenGL flag
            if(key.compare(0,OPENGL_KEY.length(),OPENGL_KEY) == 0)
            {
                opengl_flag = atoi((char *) lua_tostring(state,-1));
            }

            // Font file flag
            if(key.compare(0,FONT_KEY.length(),FONT_KEY) == 0)
            {
                char *seq = (char *) lua_tostring(state,-1);

                if(seq != nullptr)
                    fontFile = seq;
            }

            // Size flag
            if(key.compare(0,SIZE_KEY.length(),SIZE_KEY) == 0)
            {
                fontSize = atoi((char *) lua_tostring(state,-1));
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
                fullscreen_flag = atoi((char *) lua_tostring(state,-1));
            }

            lua_pop(state,1);
        }
    }

    lua_pop(state,1);
    lua_close(state);
}


/**
*   @fn bool LX_Configuration::getVideoFlag()
*
*   Get the video flag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getVideoFlag()
{
    return video_flag == 1;
}


/**
*   @fn bool LX_Configuration::getVSyncFlag()
*
*   Get the Vertical Synchronization (VSync) flag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getVSyncFlag()
{
    return vsync_flag == 1;
}


/**
*   @fn bool LX_Configuration::getTTFFlag()
*
*   Get the True Ttype Font (TTF) flag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getTTFFlag()
{
    return ttf_flag == 1;
}


/**
*   @fn bool LX_Configuration::getAudioFlag()
*
*   Get the audio flag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getAudioFlag()
{
    return audio_flag == 1;
}


/**
*   @fn bool LX_Configuration::getJoystickFlag()
*
*   Get the audio flag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getJoystickFlag()
{
    return joystick_flag == 1;
}


/**
*   @fn bool LX_Configuration::getOpenGLFlag()
*
*   Get the opengl flag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getOpenGLFlag()
{
    return opengl_flag == 1;
}


/**
*   @fn char * LX_Configuration::getFontFile()
*
*   Get the font file
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
const char * LX_Configuration::getFontFile()
{
    return fontFile.c_str();
}


/**
*   @fn int LX_Configuration::getFontSize()
*
*   Get the font size
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
int LX_Configuration::getFontSize()
{
    return fontSize;
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
*   @fn bool LX_Configuration::getFullscreenFlag()
*
*   Get the fullscreen tag
*
*   @return TRUE if the flag is set, FALSE otherwise
*
*/
bool LX_Configuration::getFullscreenFlag()
{
    return fullscreen_flag == 1;
}

