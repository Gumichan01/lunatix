#ifndef LX_CONFIG_H_INCLUDED
#define LX_CONFIG_H_INCLUDED


/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_Config.hpp
*    @brief The configuration class header
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>

/**
*   @namespace LX_Config
*   @brief The configuration loader
*
*   This module is responsible of loading subsystems of the library
*
*/
namespace LX_Config
{

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

public:

    /// Constructor
    explicit LX_ConfigurationException(UTF8string err);

    /**
    *   @fn const char * LX_ConfigurationException::what() const noexcept
    *   Get the error message
    *   @return The error string
    */
    const char * what() const noexcept;

    /// Destructor
    ~LX_ConfigurationException() noexcept;
};


/**
*   @class LX_Configuration
*   @brief The The LunatiX configuration.
*/
class LX_Configuration
{
    LX_Configuration();
    LX_Configuration(LX_Configuration& c);
    LX_Configuration& operator =(LX_Configuration& c);
    ~LX_Configuration();

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
    */
    static LX_Configuration * getInstance();

    /**
    *   @fn void destroy()
    *
    *   Destroy the unique instance
    *
    *   @note It is not necessary to call this function because it is
    *           automatically called when the library subsystems are shut down
    */
    static void destroy();

    /**
    *   @fn bool getVideoFlag() const
    *
    *   Get the video flag
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    bool getVideoFlag() const;
    /**
    *   @fn bool getVSyncFlag() const
    *
    *   Get the Vertical Synchronization (VSync) flag
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    bool getVSyncFlag() const;
    /**
    *   @fn bool getTTFFlag() const
    *
    *   Get the True Ttype Font (TTF) flag
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    bool getTTFFlag() const;
    /**
    *   @fn bool getAudioFlag() const
    *
    *   Get the audio flag
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    bool getAudioFlag() const;
    /**
    *   @fn bool getGamepadFlag() const
    *
    *   Get the audio flag
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    bool getGamepadFlag() const;
    /**
    *   @fn bool getOpenGLFlag() const
    *
    *   Get the opengl flag
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    bool getOpenGLFlag() const;
    /**
    *   @fn char * getFontFile() const
    *
    *   Get the font file
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    const char * getFontFile() const;
    /**
    *   @fn int getFontSize() const
    *
    *   Get the font size
    *
    *   @return TRUE if the flag is set, FALSE otherwise
    */
    int getFontSize() const;
    /**
    *   @fn int getWinWidth() const
    *
    *   Get the window width
    *
    *   @return The width
    */
    int getWinWidth() const;
    /**
    *   @fn int getWinHeight() const
    *
    *   Get the window height
    *
    *   @return The height
    */
    int getWinHeight() const;

};

};
#endif // LX_CONFIG_H_INCLUDED
