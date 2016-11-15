#ifndef LX_MESSAGEBOX_HPP_INCLUDED
#define LX_MESSAGEBOX_HPP_INCLUDED


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
*    @file LX_MessageBox.hpp
*    @brief The message box Library
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*
*/

#include <LunatiX/utils/utf8_string.hpp>
#include <SDL2/SDL_messagebox.h>

#define LX_MSG_ERR  SDL_MESSAGEBOX_ERROR        /**< Error message          */
#define LX_MSG_WARN SDL_MESSAGEBOX_WARNING      /**< Warning message        */
#define LX_MSG_INFO SDL_MESSAGEBOX_INFORMATION  /**< Information message    */


/**
*   @namespace LX_MSGBox
*   @brief The Message Box module
*/
namespace LX_MSGBox
{

/**
*   @fn bool showMSG(uint32_t flag, std::string title, std::string msg)
*
*   Display a simple message box
*
*   @param [in] flag One of these following flags:
*               - LX_MSG_ERR : Error megssage
*               - LX_MSG_WARN : Warning message
*               - LX_MSG_INFO : Information message
*   @param [in] title The title of the box, UTF-8 format
*   @param [in] msg The text to display in the box, UTF-8 format
*
*   @return TRUE on success, FALSE on error
*/
bool showMSG(uint32_t flag, std::string title, std::string msg);

};

#endif // LX_MESSAGEBOX_HPP_INCLUDED
