
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

/**
*   @file Version.cpp
*   @brief The version implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*
*
*/

#include <Lunatix/Version.hpp>
#include <Lunatix/utils/utf8_string.hpp>

#include <SDL2/SDL_version.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <cstring>

using namespace std;

namespace
{

// Constants

const short MAJOR_VERSION = 0;
const short MINOR_VERSION = 14;
const short PATCH_VERSION = 0;
const UTF8string STATUS( "beta" );
const UTF8string COPYRIGHT( "Copyright © 2018" );
const UTF8string AUTHOR( "Luxon Jean-Pierre" );

// Functions
constexpr int cast( const Uint8 v )
{
    return static_cast<int>( v );
}

}   // namespace

namespace lx
{

namespace VersionInfo
{

void info() noexcept
{
    const Version& luna = getVersion();

    cout << "\nLunatiX v" << luna.major << "."  << luna.minor << "."
         <<  luna.patch << "-" << luna.status << "\n"
         << COPYRIGHT << " " << AUTHOR << "\n";
}


const Version getVersion() noexcept
{
    return Version{ MAJOR_VERSION, MINOR_VERSION,
                    PATCH_VERSION, STATUS.utf8_sstring() };
}


const SDLVersion getSDLVersion() noexcept
{
    SDL_version sdl_compiled;
    SDL_version sdl_linked;

    SDL_VERSION( &sdl_compiled );
    SDL_GetVersion( &sdl_linked );

    return SDLVersion{ Version{ sdl_compiled.major, sdl_compiled.minor,
                                sdl_compiled.patch, "" },
                       Version{ sdl_linked.major, sdl_linked.minor,
                                sdl_linked.patch, "" }, "" };
}

const SDLVersion getSDLImageVersion() noexcept
{
    const std::string SDL2_IMAGE( "sdl2_image" );
    const SDL_version * img_linked = IMG_Linked_Version();
    SDL_version img_compiled;
    SDL_IMAGE_VERSION( &img_compiled );

    return SDLVersion{ Version{ img_compiled.major, img_compiled.minor,
                                img_compiled.patch, "" },
                       Version{ img_linked->major, img_linked->minor,
                                img_linked->patch, "" }, SDL2_IMAGE };
}

const SDLVersion getSDLTTFVersion() noexcept
{
    const std::string SDL2_TTF( "sdl2_ttf" );
    const SDL_version * ttf_linked = TTF_Linked_Version();
    SDL_version ttf_compiled;
    SDL_TTF_VERSION( &ttf_compiled );

    return SDLVersion{ Version{ ttf_compiled.major, ttf_compiled.minor,
                                ttf_compiled.patch, "" },
                       Version{ ttf_linked->major, ttf_linked->minor,
                                ttf_linked->patch, "" }, SDL2_TTF };
}

const SDLVersion getSDLMixerVersion() noexcept
{
    const std::string SDL2_MIXER( "sdl2_mixer" );
    const SDL_version * mix_linked = Mix_Linked_Version();
    SDL_version mix_compiled;
    SDL_MIXER_VERSION( &mix_compiled );

    return SDLVersion{ Version{ mix_compiled.major, mix_compiled.minor,
                                mix_compiled.patch, "" },
                       Version{ mix_linked->major, mix_linked->minor,
                                mix_linked->patch, "" }, SDL2_MIXER };
}


void dependencies() noexcept
{
    // Information about SDL2 and LunatiX
    const SDL_version * img_linked = IMG_Linked_Version();
    const SDL_version * ttf_linked = TTF_Linked_Version();
    const SDL_version * mix_linked = Mix_Linked_Version();

    SDL_version sdl_compiled;
    SDL_version sdl_linked;
    SDL_version img_compiled;
    SDL_version ttf_compiled;
    SDL_version mix_compiled;

    // Version of SDL
    SDL_VERSION( &sdl_compiled );
    SDL_GetVersion( &sdl_linked );
    SDL_IMAGE_VERSION( &img_compiled );
    SDL_TTF_VERSION( &ttf_compiled );
    SDL_MIXER_VERSION( &mix_compiled );

    cout << "Dependencies : \n\n"
         << "Compiled against SDL version " << cast( sdl_compiled.major ) << "."
         << cast( sdl_compiled.minor ) << "." << cast( sdl_compiled.patch ) << " ...\n\n"

         << "Linked against SDL version " << cast( sdl_linked.major ) << "."
         << cast( sdl_linked.minor ) << "." << cast( sdl_linked.patch ) << " ...\n\n"

         << "Compiled against SDL_Image version " << cast( img_compiled.major ) << "."
         << cast( img_compiled.minor ) << "." << cast( img_compiled.patch ) << " ...\n\n"

         << "Linked against SDL_Image version " << cast( img_linked->major ) << "."
         << cast( img_linked->minor ) << "." << cast( img_linked->patch ) << " ...\n\n"

         << "Compiled against SDL_TTF version " << cast( ttf_compiled.major ) << "."
         << cast( ttf_compiled.minor ) << "." << cast( ttf_compiled.patch ) << " ...\n\n"

         << "Linked against SDL_TTF version " << cast( ttf_linked->major ) << "."
         << cast( ttf_linked->minor ) << "." << cast( ttf_linked->patch ) << " ...\n\n"

         << "Compiled against SDL_Mixer version " << cast( mix_compiled.major ) << "."
         << cast( mix_compiled.minor ) << "." << cast( mix_compiled.patch ) << " ...\n\n"

         << "Linked against SDL_Mixer version " << cast( mix_linked->major ) << "."
         << cast( mix_linked->minor ) << "." << cast( mix_linked->patch ) << " ...\n\n";
}

}   // VersionInfo

}   // lx
