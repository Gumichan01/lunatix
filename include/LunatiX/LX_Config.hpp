#ifndef LX_LUA_LAYER_H_INCLUDED
#define LX_LUA_LAYER_H_INCLUDED


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
*	@file LX_Config.hpp
*	@brief The configuration class header
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/LX_ConfigLoader.hpp>

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

    UTF8string _string_error;

public :

    /// Construct the exception
    LX_ConfigurationException(UTF8string err);

    /**
    *   @fn const char * LX_ConfigurationException::what() const noexcept
    *
    *   Get the error message
    *
    *   @return The error string
    */
    const char * what() const noexcept;

    /// Destroy the exception
    ~LX_ConfigurationException() noexcept;
};


/**
*   @class LX_Configuration
*   @brief The The LunatiX engine configuration.
*/
class LX_Configuration
{
    LX_ConfigLoader::LX_InternalConfig _conf;

    LX_Configuration();
    LX_Configuration(LX_Configuration& c);
    LX_Configuration& operator =(LX_Configuration& c);
    void loadSDLFlags_();

public :

    /**
    *   @fn void initConfig()
    *
    *   Launch the system configuration
    *
    *   @note   1: This function is automatically called in LX_Init()
    *   @note   2: The instance of LX_Configuration may not be created.
    *           So it will be necessary to call LX_GetError() to get
    *           the error message
    *
    */
    static void initConfig();

    /**
    *   @fn LX_Configuration * getInstance()
    *
    *   Get the unique instance of the LX_Configuration class
    *
    *   @return The instance of LX_Configuration
    *
    *   @note   The instance can be a null pointer
    *           if initConfig() failed.
    *
    */
    static LX_Configuration * getInstance();

    /**
    *   @fn void destroy()
    *
    *   Destroy the unique instance
    *
    *   @note It is not necessary to call this function because it is
    *           automatically called when the engine subsystems are shut down
    *
    */
    static void destroy();

    /**
    *   @fn bool getVideoFlag()
    *
    *   Get the video flag
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    *
    */
    bool getVideoFlag();

    /**
    *   @fn bool getVSyncFlag()
    *
    *   Get the Vertical Synchronization (VSync) flag
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    *
    */
    bool getVSyncFlag();

    /**
    *   @fn bool getTTFFlag()
    *
    *   Get the True Ttype Font (TTF) flag
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    *
    */
    bool getTTFFlag();

    /**
    *   @fn bool getAudioFlag()
    *
    *   Get the audio flag
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    *
    */
    bool getAudioFlag();

    /**
    *   @fn bool getGamepadFlag()
    *
    *   Get the audio flag
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    *
    */
    bool getGamepadFlag();

    /**
    *   @fn bool getOpenGLFlag()
    *
    *   Get the opengl flag
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    *
    */
    bool getOpenGLFlag();

    /**
    *   @fn char * getFontFile()
    *
    *   Get the font file
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    *
    */
    const char * getFontFile();

    /**
    *   @fn int getFontSize()
    *
    *   Get the font size
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    *
    */
    int getFontSize();

    /**
    *   @fn int getWinWidth()
    *
    *   Get the window width
    *
    *   @return The width
    *
    */
    int getWinWidth();

    /**
    *   @fn int getWinHeight()
    *
    *   Get the window height
    *
    *   @return The height
    *
    */
    int getWinHeight();

    /**
    *   @fn bool getFullscreenFlag()
    *
    *   Get the fullscreen tag
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    *
    */
    bool getFullscreenFlag();

    ~LX_Configuration();
};

#endif // LX_LUA_LAYER_H_INCLUDED
