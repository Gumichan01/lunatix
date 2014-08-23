

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
*	@file LX_config.cpp
*	@brief The LunatiX_engine configuration class
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.1
*	@date August 20th, 2014
*
*
*
*/

#include "LX_config.h"



/**
*   @fn LX_configuration * LX_configuration::getInstance()
*
*   Get the unique instance of the LX_configuration class
*
*   @return the instance of LX_configuration
*
*/
LX_configuration * LX_configuration::getInstance()
{
    static LX_configuration *instance = NULL;


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
*   @fn void LX_configuration::setVideoTag()
*
*   Set the video flag
*
*/
void LX_configuration::setVideoTag()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setVideoTag : " << lua_tostring(state,-1) << std::endl;

        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getVideo");

    if(!lua_isfunction(state,-1))
    {
        std::cerr << "Error occured in LX_configuration::setVideoTag : The Lua function getVideo does not exist" << std::endl;

        throw LX_configuration_exception("The Lua function getVideo does not exist");

    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        videoTag = (int) lua_tonumber(state, -1);

    }

    lua_pop(state,1);

}


/**
*
*   @fn void LX_configuration::setTTF_Tag()
*
*   Set the true type font (TTF) flag
*
*/
void LX_configuration::setTTF_Tag()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setTTF_Tag : " << lua_tostring(state,-1) << std::endl;

        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getTTF");

    if(!lua_isfunction(state,-1))
    {
        //Ce n'est pas une fonction
        std::cerr << "Error occured in LX_configuration::setTTF_Tag : The Lua function getTTF does not exist" << std::endl;

        throw LX_configuration_exception("The Lua function getTTF does not exist");

    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        ttf_Tag = (int) lua_tonumber(state, -1);

    }

    lua_pop(state,1);

}


/**
*
*   @fn void LX_configuration::setAudioTag()
*
*   Set the audio flag
*
*/
void LX_configuration::setAudioTag()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setAudioTag : " << lua_tostring(state,-1) << std::endl;

        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getAudio");

    if(!lua_isfunction(state,-1))
    {
        //Ce n'est pas une fonction
        std::cerr << "Error occured in LX_configuration::setAudioTag : The Lua function getAudio does not exist" << std::endl;

        throw LX_configuration_exception("The Lua function getAudio does not exist");

    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        audioTag = (int) lua_tonumber(state, -1);

    }

    lua_pop(state,1);

}


/**
*
*   @fn void LX_configuration::setJoystickTag()
*
*   Set the Joystick flag
*
*/
void LX_configuration::setJoystickTag()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setJoystickTag : " << lua_tostring(state,-1) << std::endl;

        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getJoystick");

    if(!lua_isfunction(state,-1))
    {
        //Ce n'est pas une fonction
        std::cerr << "Error occured in LX_configuration::setJoystickTag : The Lua function getJoystick does not exist" << std::endl;

        throw LX_configuration_exception("The Lua function getJoystick does not exist");

    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        joystickTag = (int) lua_tonumber(state, -1);

    }

    lua_pop(state,1);

}



/**
*
*   @fn void LX_configuration::setOpenGL_Tag()
*
*   Set the OpenGL flag
*
*/
void LX_configuration::setOpenGL_Tag()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setOpenGL_Tag : " << lua_tostring(state,-1) << std::endl;

        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getOpenGL");

    if(!lua_isfunction(state,-1))
    {
        //Ce n'est pas une fonction
        std::cerr << "Error occured in LX_configuration::setOpenGL_Tag : The Lua function getOpenGL does not exist" << std::endl;

        throw LX_configuration_exception("The Lua function getOpenGL does not exist");

    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        openglTag = (int) lua_tonumber(state, -1);

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
        //Ce n'est pas une fonction
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
        //Ce n'est pas une fonction
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
        //Ce n'est pas une fonction
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
        //Ce n'est pas une fonction
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
*   @fn void LX_configuration::setFullscreenTag()
*
*   Set the window height
*
*/
void LX_configuration::setFullscreenTag()
{
    //State
    lua_State *state;

    state=lua_open();

    //Opening of the Lua library
    luaL_openlibs(state);

    //Opening of the Lua file
    if (luaL_dofile(state,LUA_CONFIG_FILE)!=0)
    {
        std::cerr << "Error occured in LX_configuration::setFullscreenTag : " << lua_tostring(state,-1) << std::endl;

        throw LX_configuration_exception("The lua file does not exist or is corrupted");
    }

    //we get an entity
    lua_getglobal(state,"getFullscreen");

    if(!lua_isfunction(state,-1))
    {
        //Ce n'est pas une fonction
        std::cerr << "Error occured in LX_configuration::setFullscreenTag : The Lua function getFullscreen does not exist" << std::endl;

        throw LX_configuration_exception("The Lua function getFullscreen does not exist");

    }
    else
    {
        //The call
        lua_call(state,0,1);

        //Getting the returned value
        fullscreenTag = (int) lua_tonumber(state, -1);

    }

    lua_pop(state,1);

}




/**
*
*   @fn int LX_configuration::getVideoTag()
*
*   Get the video flag
*
*   @return the video configuration
*
*/
int LX_configuration::getVideoTag()
{
    return videoTag;
}


/**
*
*   @fn int LX_configuration::getTTF_Tag()
*
*   Get the ttf flag
*
*   @return the ttf configuration
*
*/
int LX_configuration::getTTF_Tag()
{
    return ttf_Tag;
}


/**
*
*   @fn int LX_configuration::getAudioTag()
*
*   Get the audio flag
*
*   @return the audio configuration
*
*/
int LX_configuration::getAudioTag()
{
    return audioTag;
}



/**
*
*   @fn int LX_configuration::getJoystickTag()
*
*   Get the audio flag
*
*   @return the joystick configuration
*
*/
int LX_configuration::getJoystickTag()
{
    return joystickTag;
}


/**
*
*   @fn int LX_configuration::getOpenGL_Tag()
*
*   Get the opengl flag
*
*   @return the opengl configuration
*
*/
int LX_configuration::getOpenGL_Tag()
{
    return openglTag;
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
*   @fn int LX_configuration::getFullscreenTag()
*
*   Get the fullscreen tag
*
*   @return the fullscreen tag
*
*/
int LX_configuration::getFullscreenTag()
{
    return fullscreenTag;
}

























