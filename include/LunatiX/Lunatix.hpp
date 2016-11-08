#ifndef LUNATIX_H_INCLUDED
#define LUNATIX_H_INCLUDED


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
*    @file Lunatix.hpp
*    @brief The header file of the LunatiX
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*
*/

/// @todo (#2#) Refactor the classes that uses private implementation

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
#include <LunatiX/LX_Library.hpp>
#include <LunatiX/LX_Version.hpp>

// Graphics
#include <LunatiX/LX_Graphics.hpp>

// Audio
#include <LunatiX/LX_Audio.hpp>

//Event
#include <LunatiX/LX_Event.hpp>

// Game controller
#include <LunatiX/LX_Device.hpp>
#include <LunatiX/LX_Mouse.hpp>
#include <LunatiX/LX_Gamepad.hpp>
#include <LunatiX/LX_Haptic.hpp>

// Physics
#include <LunatiX/LX_Particle.hpp>
#include <LunatiX/LX_ParticleSystem.hpp>
#include <LunatiX/LX_Physics.hpp>
#include <LunatiX/LX_Hitbox.hpp>
#include <LunatiX/LX_Polygon.hpp>
#include <LunatiX/LX_Vector2D.hpp>

// System
#include <LunatiX/LX_FileIO.hpp>
#include <LunatiX/LX_FileBuffer.hpp>
#include <LunatiX/LX_Log.hpp>
#include <LunatiX/LX_MessageBox.hpp>
#include <LunatiX/LX_Random.hpp>
#include <LunatiX/LX_SystemInfo.hpp>
#include <LunatiX/LX_FileSystem.hpp>

// Multithread
#include <LunatiX/LX_Multithread.hpp>

// Utils
#include <LunatiX/LX_Colour.hpp>
#include <LunatiX/LX_Timer.hpp>
#include <LunatiX/LX_Text.hpp>
#include <LunatiX/utils/libtagspp/libtagspp.hpp>



#endif // LUNATIX_H_INCLUDED
