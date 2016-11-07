
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
*    @file LX_MessageBox.cpp
*    @brief The message box Library
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*
*/

#include <LunatiX/LX_MessageBox.hpp>
#include <SDL2/SDL_messagebox.h>


namespace LX_MSGBox
{

bool showMSG(uint32_t flag, std::string title, std::string msg)
{
    return SDL_ShowSimpleMessageBox(flag,title.c_str(),msg.c_str(),nullptr) == true;
}

};
