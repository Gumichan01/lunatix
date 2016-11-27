
/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    https://gumichan01.github.io/
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

#ifndef LX_LIBRARY_H_INCLUDED
#define LX_LIBRARY_H_INCLUDED

/**
*    @file LX_Library.hpp
*    @brief Library ressource manager (load and shut down)
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*/

#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_Config.hpp>
#include <SDL2/SDL.h>

const int LX_GL_MAJOR_VERSION = 3;  /**< Major version of OpenGL supported by the library */
const int LX_GL_MINOR_VERSION = 1;  /**< Minor version of OpenGL supported by the library */

/**
*   @defgroup Config Configuration
*   @brief Basics (initialization and shutdown, version, configuration)
*/

/**
*   @addtogroup Config
*   @{
*/

/**
*   @fn bool LX_Init()
*
*   Load the library according the configuration file
*
*   @return TRUE on success, FALSE otherwise
*
*   @note 1 — LX_Init initializes the subsystems defined in
*           the configuration file (lunatix.cfg)
*   @note 2 — This function automatically calls LX_WindowManager::init()
*           and LX_Configuration::initConfig()
*
*/
bool LX_Init();

/**
*   @fn bool setSDLConfig(const std::string& sdlconfig_name, const std::string& sdlconfig_value)
*
*   Set a configuration hint
*
*   @param [in] sdlconfig_name The name of the [hint](http://wiki.libsdl.org/CategoryHints#Hints)
*   @param [in] sdlconfig_value The value of the hint
*
*   @return TRUE on SUCCESS, FALSE otherwise.
*/
bool setSDLConfig(const std::string& sdlconfig_name, const std::string& sdlconfig_value);

/**
*   @fn const std::string getSDLConfig(const std::string& sdlconfig_name)
*
*   Get ht evalue of a configuration hint given in argument
*
*   @param [in] sdlconfig_name The name of the [hint](http://wiki.libsdl.org/CategoryHints#Hints)
*
*   @return A non-empty string on success, an empty string on failure
*/
const std::string getSDLConfig(const std::string& sdlconfig_name);

/**
*   @fn void LX_Quit()
*   Shut down the library
*   @note This function automatically calls LX_WindowManager::destroy()
*/
void LX_Quit();

/** @} */

#endif // LX_LIBRARY_H_INCLUDED
