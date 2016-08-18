#ifndef LUNATIX_ENGINE_H_INCLUDED
#define LUNATIX_ENGINE_H_INCLUDED


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
*    @file Lunatix_engine.hpp
*    @brief The header file of the LunatiX
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/

#if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
#undef __WIN32__
#define __WIN32__
#elif defined(linux) || defined(__linux) || defined(__linux__)  // Unix/Linux
#undef __linux__
#define __linux__
#else
#error "Not supported system"
#endif

// Initialization
#include "LX_Library.hpp"
#include "LX_Config.hpp"
#include "LX_Version.hpp"

// Graphics
#include "LX_Image.hpp"
#include "LX_OpenGL.hpp"
#include "LX_TrueTypeFont.hpp"
#include "LX_Window.hpp"
#include "LX_WindowManager.hpp"

// Audio
#include "LX_Chunk.hpp"
#include "LX_Mixer.hpp"
#include "LX_Music.hpp"

// Game controller
#include "LX_Device.hpp"
#include "LX_Gamepad.hpp"
#include "LX_Haptic.hpp"

// Physics
#include "LX_Particle.hpp"
#include "LX_ParticleSystem.hpp"
#include "LX_Physics.hpp"
#include "LX_Polygon.hpp"

// System
#include "LX_Channel.hpp"
#include "LX_Error.hpp"
#include "LX_FileIO.hpp"
#include "LX_FileBuffer.hpp"
#include "LX_Log.hpp"
#include "LX_MessageBox.hpp"
#include "LX_Random.hpp"
#include "LX_Sync.hpp"
#include "LX_SystemInfo.hpp"
#include "LX_Thread.hpp"

// Utils
#include "LX_Text.hpp"
#include "utils/utf8_string.hpp"



#endif // LUNATIX_ENGINE_H_INCLUDED
