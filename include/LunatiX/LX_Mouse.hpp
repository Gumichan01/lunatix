#ifndef LX_MOUSE_HPP_INCLUDED
#define LX_MOUSE_HPP_INCLUDED

/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    https://gumichan01.github.io/
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

/**
*    @file LX_Mouse.hpp
*    @brief The mouse interface
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
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
*
*   It handles a user-defined mouse (with custom cursor)
*/
class LX_Mouse
{
    std::unique_ptr<LX_Mouse_> _mimpl;

public:

    /**
    *   @fn LX_Mouse(const LX_Graphics::LX_BufferedImage& surface, int hot_x, int hot_y)
    *   @brief Constructor
    *
    *   Construct the mouse cursor using a surface and the coordinates of
    *   the mouse clicking zone
    *
    *   @param [in] surface The surface image to load the cursor from
    *   @param [in] hot_x The x hot spot position
    *   @param [in] hot_y The y hot spot position
    */
    LX_Mouse(const LX_Graphics::LX_BufferedImage& surface, int hot_x, int hot_y);
    /**
    *   @fn bool isOpen() const
    *
    *   Check if the mouse is loaded without issues
    *
    *   @return TRUE if there is no problem, FALSE otherwise
    */
    bool isOpen() const;
    /**
    *   @fn void setMouse()
    *   Activate the current mouse
    */
    void setMouse();

    /// Destructor
    ~LX_Mouse();
};

};


#endif // LX_MOUSE_HPP_INCLUDED
