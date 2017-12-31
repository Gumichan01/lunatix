
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
*   @file LX_Version.cpp
*   @brief The version implementation
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*
*/

#include <LunatiX/LX_Version.hpp>
#include <SDL2/SDL_version.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <cstring>


using namespace std;

namespace
{
const short LX_MAJOR_VERSION = 0;
const short LX_MINOR_VERSION = 12;
const short LX_PATCH_VERSION = 0;
const char * LX_STATUS       = "stable";
const char * LX_COPYRIGHT    = "Copyright © 2018";
const char * LX_AUTHOR       = "Luxon Jean-Pierre";
}

namespace LX_VersionInfo
{

void info() noexcept
{
    LX_Version luna;
    getVersion(luna);

    cout << endl << "LunatiX v" << luna.major
         << "."  << luna.minor << "." <<  luna.patch << "-" << luna.status
         << endl << LX_COPYRIGHT << " " << LX_AUTHOR << endl;
}


void getVersion(LX_Version& version) noexcept
{
    version.major = LX_MAJOR_VERSION;
    version.minor = LX_MINOR_VERSION;
    version.patch = LX_PATCH_VERSION;
    strcpy(version.status, LX_STATUS);
}


void dependencies() noexcept
{
    // Information about SDL2 and LunatiX
    const SDL_version *img_linked = IMG_Linked_Version();
    const SDL_version *ttf_linked = TTF_Linked_Version();
    const SDL_version *mix_linked = Mix_Linked_Version();

    SDL_version sdl_compiled;
    SDL_version sdl_linked;
    SDL_version img_compiled;
    SDL_version ttf_compiled;
    SDL_version mix_compiled;

    // Version of SDL
    SDL_VERSION(&sdl_compiled);
    SDL_GetVersion(&sdl_linked);
    SDL_IMAGE_VERSION(&img_compiled);
    SDL_TTF_VERSION(&ttf_compiled);
    SDL_MIXER_VERSION(&mix_compiled);

    cout << "Dependencies : \n\n";

    cout << "Compiled against SDL version "
         << static_cast<int>(sdl_compiled.major) << "."
         << static_cast<int>(sdl_compiled.minor) << "."
         << static_cast<int>(sdl_compiled.patch) << " ...\n\n";

    cout << "Linked against SDL version "
         << static_cast<int>(sdl_linked.major) << "."
         << static_cast<int>(sdl_linked.minor) << "."
         << static_cast<int>(sdl_linked.patch) << " ...\n\n";

    cout << "Compiled against SDL_Image version "
         << static_cast<int>(img_compiled.major) << "."
         << static_cast<int>(img_compiled.minor) << "."
         << static_cast<int>(img_compiled.patch) << " ...\n\n";

    cout << "Linked against SDL_Image version "
         << static_cast<int>(img_linked->major) << "."
         << static_cast<int>(img_linked->minor) << "."
         << static_cast<int>(img_linked->patch) << " ...\n\n";

    cout << "Compiled against SDL_TTF version "
         << static_cast<int>(ttf_compiled.major) << "."
         << static_cast<int>(ttf_compiled.minor) << "."
         << static_cast<int>(ttf_compiled.patch) << " ...\n\n";

    cout << "Linked against SDL_TTF version "
         << static_cast<int>(ttf_linked->major) << "."
         << static_cast<int>(ttf_linked->minor) << "."
         << static_cast<int>(ttf_linked->patch) << " ...\n\n";

    cout << "Compiled against SDL_Mixer version "
         << static_cast<int>(mix_compiled.major) << "."
         << static_cast<int>(mix_compiled.minor) << "."
         << static_cast<int>(mix_compiled.patch) << " ...\n\n";

    cout << "Linked against SDL_Mixer version "
         << static_cast<int>(mix_linked->major) << "."
         << static_cast<int>(mix_linked->minor) << "."
         << static_cast<int>(mix_linked->patch) << " ...\n\n";
}

}
