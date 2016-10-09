#ifndef LX_LIBRARY_H_INCLUDED
#define LX_LIBRARY_H_INCLUDED

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
*    @file LX_Library.hpp
*    @brief The Library header. It manages the library ressources (load and shut down)
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#include <LunatiX/LX_Error.hpp>
#include <LunatiX/LX_Config.hpp>
#include <SDL2/SDL.h>

const int LX_GL_MAJOR_VERSION = 3;  /**< Major version of OpenGL supported by the library */
const int LX_GL_MINOR_VERSION = 2;  /**< Minor version of OpenGL supported by the library */

/**
*   @fn bool LX_Init()
*
*   Load the library according the configuration file
*
*   @return TRUE if all systems were init, FALSE otherwise
*
*   @note   This function automatically calls LX_WindowManager::init()
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
*
*   Shut down the library
*
*   @note This function automatically calls LX_WindowManager::destroy()
*
*/
void LX_Quit();

#endif // LX_LIBRARY_H_INCLUDED
