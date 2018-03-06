
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

#ifndef LX_MESSAGEBOX_HPP_INCLUDED
#define LX_MESSAGEBOX_HPP_INCLUDED

/**
*   @file LX_MessageBox.hpp
*   @brief The message box Library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <LunatiX/utils/utf8_string.hpp>

/**
*   @ingroup System
*   @namespace LX_MSGBox
*   @brief The Message Box namespace
*/
namespace LX_MSGBox
{

/**
*   @enum LX_MsgType
*   @brief Type of message
*
*/
enum class LX_MsgType: unsigned int
{
    ERR,    /**< Error message          */
    WARN,   /**< Warning message        */
    INFO    /**< Information message    */
};

/**
*   @fn void showMSG(uint32_t flag, std::string title, std::string msg) noexcept
*
*   Display a message box
*
*   @param [in] flag One of these following flags:
*              - LX_MSG_ERR : Error megssage
*              - LX_MSG_WARN : Warning message
*              - LX_MSG_INFO : Information message
*   @param [in] title The title of the box, UTF-8 format
*   @param [in] msg The text to display in the box, UTF-8 format
*/
void showMSG(LX_MsgType flag, std::string title, std::string msg) noexcept;

}

#endif // LX_MESSAGEBOX_HPP_INCLUDED
