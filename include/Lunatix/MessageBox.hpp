
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

#ifndef MESSAGEBOX_HPP_INCLUDED
#define MESSAGEBOX_HPP_INCLUDED

/**
*   @file MessageBox.hpp
*   @brief The message box Library
*   @author Luxon Jean-Pierre(Gumichan01)
*
*/

#include <Lunatix/utils/utf8_string.hpp>

namespace lx
{

/**
*   @ingroup System
*   @namespace lx::MSGBox
*   @brief The Message Box namespace
*/
namespace MSGBox
{

/**
*   @enum MsgType
*   @brief Type of message
*
*/
enum class MsgType
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
*              - MSG_ERR : Error megssage
*              - MSG_WARN : Warning message
*              - MSG_INFO : Information message
*   @param [in] title The title of the box, UTF-8 format
*   @param [in] msg The text to display in the box, UTF-8 format
*/
void showMSG( MsgType flag, std::string title, std::string msg ) noexcept;

}

}

#endif // MESSAGEBOX_HPP_INCLUDED
