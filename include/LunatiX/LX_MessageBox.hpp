
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_MESSAGEBOX_HPP_INCLUDED
#define LX_MESSAGEBOX_HPP_INCLUDED

/**
*   @file LX_MessageBox.hpp
*   @brief The message box Library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*/

#include <LunatiX/utils/utf8_string.hpp>


/**
*   @ingroup System
*   @namespace LX_MSGBox
*   @brief The Message Box namespace
*/
namespace LX_MSGBox
{
const uint32_t LX_MSG_ERR  = 0x00000010;    /**< Error message          */
const uint32_t LX_MSG_WARN = 0x00000020;    /**< Warning message        */
const uint32_t LX_MSG_INFO = 0x00000040;    /**< Information message    */

/**
*   @fn bool showMSG(uint32_t flag, std::string title, std::string msg)
*
*   Display a simple message box
*
*   @param [in] flag One of these following flags:
*              - LX_MSG_ERR : Error megssage
*              - LX_MSG_WARN : Warning message
*              - LX_MSG_INFO : Information message
*   @param [in] title The title of the box, UTF-8 format
*   @param [in] msg The text to display in the box, UTF-8 format
*
*   @return TRUE on success, FALSE on error
*/
bool showMSG(uint32_t flag, std::string title, std::string msg);

}

#endif // LX_MESSAGEBOX_HPP_INCLUDED
