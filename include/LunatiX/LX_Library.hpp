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

#define LX_GL_MAJOR_VERSION 3   /**< Major version of OpenGL supported by the library */
#define LX_GL_MINOR_VERSION 2   /**< Minor version of OpenGL supported by the library */

/**
*   @fn bool LX_Init(void)
*
*   Loads the library according the configuration file
*
*   @return TRUE if all systems were init, FALSE otherwise
*
*   @note   This function automatically calls LX_WindowManager::init()
*           and LX_Configuration::initConfig()
*
*/
bool LX_Init(void);
/**
*   @fn void LX_Quit(void)
*
*   Shut down the library
*
*   @note This function automatically calls LX_WindowManager::destroy()
*
*/
void LX_Quit(void);

#endif // LX_LIBRARY_H_INCLUDED
