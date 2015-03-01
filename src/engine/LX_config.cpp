

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
*	@file LX_config.cpp
*	@brief The LunatiX_engine configuration class
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.2
*	@date February 7th, 2015
*
*
*/


#include <string>
#include <exception>

#include <Lua/lua.hpp>

#include "LX_config.h"

// unique instance
static LX_configuration *instance;



/**
*   @fn LX_configuration_exception::LX_configuration_exception(std::string err)
*
*   Build the LX_configuration_exception class
*
*   @param err the error string
*
*/
LX_configuration_exception::LX_configuration_exception(std::string err)
{
    str_err = err;
}

/**
*   @fn const char * LX_configuration_exception::what() const throw()
*
*   Get the error string
*
*   @return the error string
*
*/
const char * LX_configuration_exception::what() const throw()
{
    return str_err.c_str();
}


/**
*   @fn LX_configuration_exception::~LX_configuration_exception() throw()
*
*   Destroy the instance
*
*/
LX_configuration_exception::~LX_configuration_exception() throw(){}





/**
*   @fn LX_configuration::LX_configuration()
*
*   Create an instance of the configuration
*
*/
LX_configuration::LX_configuration()
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


/**
*   @fn LX_configuration::~LX_configuration()
*
*   Destroy the instance
*
**/
LX_configuration::~LX_configuration(){}

/**
*   @fn LX_configuration * LX_configuration::getInstance()
*
*   Get the unique instance of the LX_configuration class
*
*   @return the instance of LX_configuration
*
*   @note If no instance exists, a new unique instance will be created and returned
*   @note otherwise, a current instance will be returned
*
*/
LX_configuration * LX_configuration::getInstance()
{

    if(instance == NULL)
    {
        try
        {
            instance = new LX_configuration();
        }
        catch(std::exception & ex_conf)
        {
            std::cerr << "Exception occurred at LX_configuration constructor : " << ex_conf.what() << std::endl;
            instance = NULL;
        }
    }

    return instance;
}



/**
*
*   @fn void LX_configuration::destroy()
*
*   Destroy the unique instance
*
*   @warning you must call this function to prevent a memory leak if you called LX_configuration::getInstances()
*
*/
void LX_configuration::destroy()
{
    delete instance;
    instance = NULL;
}



/**
*
*   @fn void LX_configuration::setVideoFlag()
*
*   Set the video flag
*
*/
void LX_configuration::setVideoFlag()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setVideoFlag : " << lua_tostring(state,-1) << std::endl;
        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getVideo");

    if(!lua_isfunction(state,-1))
    {
        std::cerr << "Error occured in LX_configuration::setVideoFlag : The Lua function getVideo does not exist" << std::endl;
        throw LX_configuration_exception("The Lua function getVideo does not exist");
    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        videoFlag = (int) lua_tonumber(state, -1);
    }

    lua_pop(state,1);
}


/**
*
*   @fn void LX_configuration::setTTF_Flag()
*
*   Set the true type font (TTF) flag
*
*/
void LX_configuration::setTTF_Flag()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setTTF_Flag : " << lua_tostring(state,-1) << std::endl;
        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getTTF");

    if(!lua_isfunction(state,-1))
    {
        std::cerr << "Error occured in LX_configuration::setTTF_Flag : The Lua function getTTF does not exist" << std::endl;
        throw LX_configuration_exception("The Lua function getTTF does not exist");
    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        ttf_Flag = (int) lua_tonumber(state, -1);
    }

    lua_pop(state,1);
}


/**
*
*   @fn void LX_configuration::setAudioFlag()
*
*   Set the audio flag
*
*/
void LX_configuration::setAudioFlag()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setAudioFlag : " << lua_tostring(state,-1) << std::endl;
        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getAudio");

    if(!lua_isfunction(state,-1))
    {
        std::cerr << "Error occured in LX_configuration::setAudioFlag : The Lua function getAudio does not exist" << std::endl;
        throw LX_configuration_exception("The Lua function getAudio does not exist");
    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        audioFlag = (int) lua_tonumber(state, -1);
    }

    lua_pop(state,1);
}


/**
*
*   @fn void LX_configuration::setJoystickFlag()
*
*   Set the Joystick flag
*
*/
void LX_configuration::setJoystickFlag()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setJoystickFlag : " << lua_tostring(state,-1) << std::endl;
        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getJoystick");

    if(!lua_isfunction(state,-1))
    {
        std::cerr << "Error occured in LX_configuration::setJoystickFlag : The Lua function getJoystick does not exist" << std::endl;
        throw LX_configuration_exception("The Lua function getJoystick does not exist");
    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        joystickFlag = (int) lua_tonumber(state, -1);
    }

    lua_pop(state,1);
}



/**
*
*   @fn void LX_configuration::setOpenGL_Flag()
*
*   Set the OpenGL flag
*
*/
void LX_configuration::setOpenGL_Flag()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setOpenGL_Flag : " << lua_tostring(state,-1) << std::endl;

        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getOpenGL");

    if(!lua_isfunction(state,-1))
    {
        std::cerr << "Error occured in LX_configuration::setOpenGL_Flag : The Lua function getOpenGL does not exist" << std::endl;
        throw LX_configuration_exception("The Lua function getOpenGL does not exist");
    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        openglFlag = (int) lua_tonumber(state, -1);
    }

    lua_pop(state,1);
}


/**
*
*   @fn void LX_configuration::setFontFile()
*
*   Set the font file
*
*
*/
void LX_configuration::setFontFile()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setFontFile : " << lua_tostring(state,-1) << std::endl;

        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getFont");

    if(!lua_isfunction(state,-1))
    {
        std::cerr << "Error occured in LX_configuration::setFontFile : The Lua function getFont does not exist" << std::endl;
        throw LX_configuration_exception("The Lua function getFont does not exist");
    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        font_file = (char *) lua_tostring(state, -1);

    }

    lua_pop(state,1);
}



/**
*
*   @fn void LX_configuration::setFontSize()
*
*   Set the font size
*
*/
void LX_configuration::setFontSize()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setFontSize : " << lua_tostring(state,-1) << std::endl;

        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getFontSize");

    if(!lua_isfunction(state,-1))
    {
        std::cerr << "Error occured in LX_configuration::setFontSize : The Lua function getFontSize does not exist" << std::endl;
        throw LX_configuration_exception("The Lua function getFontSize does not exist");

    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        font_size = (int) lua_tonumber(state, -1);
    }

    lua_pop(state,1);
}



/**
*
*   @fn void LX_configuration::setWinWidth()
*
*   Set the window width
*
*/
void LX_configuration::setWinWidth()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setWinWidth : " << lua_tostring(state,-1) << std::endl;
        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getWidth");

    if(!lua_isfunction(state,-1))
    {
        std::cerr << "Error occured in LX_configuration::setWinWidth : The Lua function getWidth does not exist" << std::endl;
        throw LX_configuration_exception("The Lua function getWidth does not exist");
    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        width = (int) lua_tonumber(state, -1);
    }

    lua_pop(state,1);
}



/**
*
*   @fn void LX_configuration::setWinHeight()
*
*   Set the window height
*
*/
void LX_configuration::setWinHeight()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setWinHeight : " << lua_tostring(state,-1) << std::endl;
        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getHeight");

    if(!lua_isfunction(state,-1))
    {
        std::cerr << "Error occured in LX_configuration::setWinHeight : The Lua function getHeight does not exist" << std::endl;
        throw LX_configuration_exception("The Lua function getHeight does not exist");
    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        height = (int) lua_tonumber(state, -1);
    }

    lua_pop(state,1);
}



/**
*
*   @fn void LX_configuration::setFullscreenFlag()
*
*   Set the window height
*
*/
void LX_configuration::setFullscreenFlag()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setFullscreenFlag : " << lua_tostring(state,-1) << std::endl;
        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getFullscreen");

    if(!lua_isfunction(state,-1))
    {
        std::cerr << "Error occured in LX_configuration::setFullscreenFlag : The Lua function getFullscreen does not exist" << std::endl;
        throw LX_configuration_exception("The Lua function getFullscreen does not exist");

    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        fullscreenFlag = (int) lua_tonumber(state, -1);
    }

    lua_pop(state,1);
}




/**
*
*   @fn int LX_configuration::getVideoFlag()
*
*   Get the video flag
*
*   @return the video configuration
*
*/
int LX_configuration::getVideoFlag()
{
    return videoFlag;
}


/**
*
*   @fn int LX_configuration::getTTF_Flag()
*
*   Get the ttf flag
*
*   @return the ttf configuration
*
*/
int LX_configuration::getTTF_Flag()
{
    return ttf_Flag;
}


/**
*
*   @fn int LX_configuration::getAudioFlag()
*
*   Get the audio flag
*
*   @return the audio configuration
*
*/
int LX_configuration::getAudioFlag()
{
    return audioFlag;
}



/**
*
*   @fn int LX_configuration::getJoystickFlag()
*
*   Get the audio flag
*
*   @return the joystick configuration
*
*/
int LX_configuration::getJoystickFlag()
{
    return joystickFlag;
}


/**
*
*   @fn int LX_configuration::getOpenGL_Flag()
*
*   Get the opengl flag
*
*   @return the opengl configuration
*
*/
int LX_configuration::getOpenGL_Flag()
{
    return openglFlag;
}


/**
*
*   @fn char * LX_configuration::getFontFile()
*
*   Get the font file
*
*   @return the font file
*
*/
const char * LX_configuration::getFontFile()
{
    return font_file.c_str();
}


/**
*
*   @fn int LX_configuration::getFontSize()
*
*   Get the font size
*
*   @return the font size
*
*/
int LX_configuration::getFontSize()
{
    return font_size;
}



/**
*
*   @fn int LX_configuration::getWinWidth()
*
*   Get the window width
*
*   @return the width
*
*/
int LX_configuration::getWinWidth()
{
    return width;
}



/**
*
*   @fn int LX_configuration::getWinHeight()
*
*   Get the window height
*
*   @return the height
*
*/
int LX_configuration::getWinHeight()
{
    return height;
}



/**
*
*   @fn int LX_configuration::getFullscreenFlag()
*
*   Get the fullscreen tag
*
*   @return the fullscreen tag
*
*/
int LX_configuration::getFullscreenFlag()
{
    return fullscreenFlag;
}











