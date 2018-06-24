
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_LIBRARY_H_INCLUDED
#define LX_LIBRARY_H_INCLUDED

/**
*   @file Library.hpp
*   @brief Library ressource manager (load and shut down)
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/Error.hpp>
#include <Lunatix/Config.hpp>
#include <SDL2/SDL.h>


/**
*   @defgroup Config Configuration
*   @brief Basics (initialization and shutdown, version, configuration)
*/

/**
*   @namespace lx
*   @brief the global namespace
*/
namespace lx
{

/**
*   @addtogroup Config
*   @{
*/

/**
*   @fn bool init() noexcept
*
*   Load the library according the configuration file
*
*   @return TRUE on success, FALSE otherwise
*
*   @note 1 — This function initializes the subsystems defined in
*          the configuration file (lunatix.cfg)
*/
bool init() noexcept;

/**
*   @fn bool setSDLConfig(const std::string& sdlconfig_name, const std::string& sdlconfig_value) noexcept
*
*   Set a configuration hint
*
*   @param [in] sdlconfig_name The name of the [hint](http://wiki.libsdl.org/CategoryHints#Hints)
*   @param [in] sdlconfig_value The value of the hint
*
*   @return TRUE on SUCCESS, FALSE otherwise.
*/
bool setSDLConfig( const std::string& sdlconfig_name, const std::string& sdlconfig_value ) noexcept;
/**
*   @fn const std::string getSDLConfig(const std::string& sdlconfig_name) noexcept
*
*   Get ht evalue of a configuration hint given in argument
*
*   @param [in] sdlconfig_name The name of the [hint](http://wiki.libsdl.org/CategoryHints#Hints)
*
*   @return A non-empty string on success, an empty string on failure
*/
const std::string getSDLConfig( const std::string& sdlconfig_name ) noexcept;

/**
*   @fn void quit() noexcept
*   Shut down the library
*   @note This function automatically calls LX_WindowManager::destroy()
*/
void quit() noexcept;

/** @} */

}

#endif // LX_LIBRARY_H_INCLUDED
