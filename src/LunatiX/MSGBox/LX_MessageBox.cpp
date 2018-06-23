
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
*   @file LX_MessageBox.cpp
*   @brief The message box Library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <LunatiX/LX_MessageBox.hpp>
#include <SDL2/SDL_messagebox.h>


namespace
{

using namespace LX_MSGBox;

inline constexpr uint32_t touint(const LX_MsgType& type) noexcept
{
    return type == LX_MsgType::ERR ? SDL_MESSAGEBOX_ERROR :
           type == LX_MsgType::WARN ? SDL_MESSAGEBOX_ERROR :
           SDL_MESSAGEBOX_INFORMATION;

}

}

namespace LX_MSGBox
{

void showMSG(LX_MsgType flag, std::string title, std::string msg) noexcept
{
    SDL_ShowSimpleMessageBox(touint(flag), title.c_str(), msg.c_str(), nullptr);
}

}
