#ifndef LX_MOUSE_HPP_INCLUDED
#define LX_MOUSE_HPP_INCLUDED

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
*    @file LX_Mouse.hpp
*    @brief The mouse interface
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*/


namespace LX_Graphics
{
class LX_Surface;
}

struct SDL_Cursor;

namespace LX_Device
{

/**
*   @class LX_Mouse
*   @brief The mouse cursor
*/
class LX_Mouse
{
    SDL_Cursor * _cursor;

public:

    /**
    *   @fn LX_Mouse(LX_Graphics::LX_Surface& surface, int hot_x, int hot_y)
    *
    *   Construct the mouse cursor using a surface and the coordinates of
    *   the mouse clicking zone
    *
    *   @param [in] surface The surface image to load the cursor from
    *   @param [in] hot_x The x hot spot position
    *   @param [in] hot_y The y hot spot position
    */
    LX_Mouse(LX_Graphics::LX_Surface& surface, int hot_x, int hot_y);
    /**
    *   @fn bool isOpen()
    *
    *   Check if the mouse is loaded without issues
    *
    *   @return TRUE if there is no problem, FALSE otherwise
    */
    bool isOpen();
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
