
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

#ifndef MOUSE_HPP_INCLUDED
#define MOUSE_HPP_INCLUDED

/**
*   @file Mouse.hpp
*   @brief The mouse interface
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*/

#include <memory>


namespace lx
{

namespace Graphics
{
class BufferedImage;
}

namespace Device
{

class Mouse_;

/**
*   @class Mouse
*   @brief The mouse cursor
*   It handles a user-defined mouse (with custom cursor)
*/
class Mouse final
{
    std::unique_ptr<Mouse_> m_mimpl;

    Mouse( const Mouse& ) = delete;
    Mouse& operator =( const Mouse& ) = delete;

public:

    /**
    *   @fn Mouse(const lx::Graphics::BufferedImage& surface, int hot_x, int hot_y) noexcept
    *
    *   @param [in] surface The buffered image to load the cursor from
    *   @param [in] hot_x The x hot spot position
    *   @param [in] hot_y The y hot spot position
    */
    Mouse( const lx::Graphics::BufferedImage& surface, int hot_x, int hot_y ) noexcept;
    /**
    *   @fn bool isOpen() const noexcept
    *   Check if the mouse is loaded without issues
    *   @return TRUE if there is no problem, FALSE otherwise
    */
    bool isOpen() const noexcept;
    /**
    *   @fn void setMouse() noexcept
    *   Activate the current mouse
    */
    void setMouse() noexcept;

    ~Mouse();
};

}   // Device

}   // lx

#endif // MOUSE_HPP_INCLUDED
