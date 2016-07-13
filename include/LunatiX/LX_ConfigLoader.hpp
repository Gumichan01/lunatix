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


namespace LX_ConfigLoader
{

struct LX_InternalConfig
{
    bool video_flag;
    bool vsync_flag;
    bool ttf_flag;
    bool audio_flag;
    bool gamepad_flag;
    bool opengl_flag;
    UTF8string font_file;
    int font_size;
    int width;
    int height;
    bool fullscreen_flag;
};

void loadSDLfileConfig(LX_InternalConfig& config);
void loadWindowFileConfig(LX_InternalConfig& config);

};

#endif // LX_CONFIGLOADER_HPP_INCLUDED
