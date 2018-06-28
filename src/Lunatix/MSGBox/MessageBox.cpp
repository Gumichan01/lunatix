
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
*   @file MessageBox.cpp
*   @brief The message box Library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <Lunatix/MessageBox.hpp>
#include <SDL2/SDL_messagebox.h>


namespace
{

using namespace lx::MSGBox;

inline constexpr uint32_t touint( const MsgType& type ) noexcept
{
    return type == MsgType::ERR ? SDL_MESSAGEBOX_ERROR :
           type == MsgType::WARN ? SDL_MESSAGEBOX_ERROR :
           SDL_MESSAGEBOX_INFORMATION;

}

}

namespace lx
{

namespace MSGBox
{

void showMSG( MsgType flag, std::string title, std::string msg ) noexcept
{
    SDL_ShowSimpleMessageBox( touint( flag ), title.c_str(), msg.c_str(), nullptr );
}

}

}
