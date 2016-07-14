#ifndef LX_CONFIGLOADER_HPP_INCLUDED
#define LX_CONFIGLOADER_HPP_INCLUDED

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
*	@file LX_ConfigLoader.hpp
*	@brief The configuration loader class header
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.8
*
*/

#include <LunatiX/utils/utf8_string.hpp>

#define LX_SDL_FILE "config/lxsdl.cfg"
#define LX_WINFO_FILE "config/lxwindow.cfg"

/**
*   @namespace LX_ConfigLoader
*   @brief The configuration loader
*/
namespace LX_ConfigLoader
{

/**
*   @struct LX_InternalConfig
*   @brief The configuration structure
*
*   This is the internal structure configuration
*/
struct LX_InternalConfig
{
    bool video_flag;        ///< Video flag
    bool vsync_flag;        ///< VSync flag
    bool ttf_flag;          ///< TTF flag
    bool audio_flag;        ///< Audio flag
    bool gamepad_flag;      ///< Gamepad flag
    bool opengl_flag;       ///< OpenGL flag
    UTF8string font_file;   ///< Font file
    int font_size;          ///< Font size
    int width;              ///< Width
    int height;             ///< Height
    bool fullscreen_flag;   ///< Fullscreen flag
};

/**
*   @fn void loadSDLfileConfig(LX_InternalConfig& config)
*
*   Load the configuration of the engine and store it into the struture
*
*   @param config The structure to fill data in
*
*/
void loadSDLfileConfig(LX_InternalConfig& config);

/**
*   @fn void loadWindowFileConfig(LX_InternalConfig& config)
*
*   Load the default window configuration of the engine
*   and store it into the struture
*
*   @param config The structure to fill data in
*
*/
void loadWindowFileConfig(LX_InternalConfig& config);

};

#endif // LX_CONFIGLOADER_HPP_INCLUDED
