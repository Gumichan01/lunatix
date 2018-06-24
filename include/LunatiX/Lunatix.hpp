
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
#include <LunatiX/Library.hpp>
#include <LunatiX/Version.hpp>

// Graphics
#include <LunatiX/Graphics.hpp>

// Audio
#include <LunatiX/Audio.hpp>

//Event
#include <LunatiX/Event.hpp>

// Game controller
#include <LunatiX/Device.hpp>
#include <LunatiX/Mouse.hpp>
#include <LunatiX/Gamepad.hpp>
#include <LunatiX/Haptic.hpp>

// Physics
#include <LunatiX/Particle.hpp>
#include <LunatiX/ParticleSystem.hpp>
#include <LunatiX/Physics.hpp>
#include <LunatiX/Hitbox.hpp>
#include <LunatiX/Polygon.hpp>

// System
#include <LunatiX/FileIO.hpp>
#include <LunatiX/FileBuffer.hpp>
#include <LunatiX/Log.hpp>
#include <LunatiX/MessageBox.hpp>
#include <LunatiX/Random.hpp>
#include <LunatiX/SystemInfo.hpp>
#include <LunatiX/FileSystem.hpp>

// Multithread
#include <LunatiX/Thread.hpp>

// Others
#include <LunatiX/Timer.hpp>
#include <LunatiX/Text.hpp>

// Utils
/**
*   @defgroup Utils Utilities
*   @brief Miscellaneous namespaces/classes/functions
*/
#include <LunatiX/utils/libtagspp/libtagspp.hpp>
#include <LunatiX/utils/utf8_string.hpp>
#include <LunatiX/utils/float.hpp>

#endif // LUNATIX_H_INCLUDED
