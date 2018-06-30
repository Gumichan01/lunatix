
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

#ifndef LUNATIX_H_INCLUDED
#define LUNATIX_H_INCLUDED

/**
*   @file Lunatix.hpp
*   @brief The header file of LunatiX
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
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

#pragma message "Random: Some functions are deprecated, please check the documentation"
#pragma message "Texture: Some functions are deprecated, please check the documentation"
#pragma message "Window: Some functions are deprecated, please check the documentation"

// Initialization
#include <Lunatix/Library.hpp>
#include <Lunatix/Version.hpp>

// Graphics
#include <Lunatix/Graphics.hpp>

// Audio
#include <Lunatix/Audio.hpp>

//Event
#include <Lunatix/Event.hpp>

// Game controller
#include <Lunatix/Device.hpp>
#include <Lunatix/Mouse.hpp>
#include <Lunatix/Gamepad.hpp>
#include <Lunatix/Haptic.hpp>

// Physics
#include <Lunatix/Particle.hpp>
#include <Lunatix/ParticleSystem.hpp>
#include <Lunatix/Physics.hpp>
#include <Lunatix/Polygon.hpp>

// System
#include <Lunatix/FileIO.hpp>
#include <Lunatix/FileBuffer.hpp>
#include <Lunatix/Log.hpp>
#include <Lunatix/MessageBox.hpp>
#include <Lunatix/Random.hpp>
#include <Lunatix/SystemInfo.hpp>
#include <Lunatix/FileSystem.hpp>

// Multithread
#include <Lunatix/Thread.hpp>

// Others
#include <Lunatix/Timer.hpp>
#include <Lunatix/Text.hpp>

// Utils
/**
*   @defgroup Utils Utilities
*   @brief Miscellaneous namespaces/classes/functions
*/
#include <Lunatix/utils/libtagspp/libtagspp.hpp>

#endif // LUNATIX_H_INCLUDED
