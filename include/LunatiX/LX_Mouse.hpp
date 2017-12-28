
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

#ifndef LX_MOUSE_HPP_INCLUDED
#define LX_MOUSE_HPP_INCLUDED

/**
*   @file LX_Mouse.hpp
*   @brief The mouse interface
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*/

#include <memory>

namespace LX_Graphics
{
class LX_BufferedImage;
}

namespace LX_Device
{

class LX_Mouse_;

/**
*   @class LX_Mouse
*   @brief The mouse cursor
*   It handles a user-defined mouse (with custom cursor)
*/
class LX_Mouse
{
    std::unique_ptr<LX_Mouse_> _mimpl;

    LX_Mouse(const LX_Mouse& m) = delete;
    LX_Mouse& operator =(const LX_Mouse& m) = delete;

public:

    /**
    *   @fn LX_Mouse(const LX_Graphics::LX_BufferedImage& surface, int hot_x, int hot_y) noexcept
    *   @brief Constructor
    *
    *   Construct the mouse cursor using a surface and the coordinates of
    *   the mouse clicking zone
    *
    *   @param [in] surface The buffered image to load the cursor from
    *   @param [in] hot_x The x hot spot position
    *   @param [in] hot_y The y hot spot position
    */
    LX_Mouse(const LX_Graphics::LX_BufferedImage& surface, int hot_x, int hot_y) noexcept;
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

    /// Destructor
    ~LX_Mouse();
};

}

#endif // LX_MOUSE_HPP_INCLUDED
