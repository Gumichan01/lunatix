
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
*   @file LX_Mouse.cpp
*   @brief The implementation of the mouse
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <LunatiX/Mouse.hpp>
#include <LunatiX/Texture.hpp>

#include <SDL2/SDL_mouse.h>

namespace LX_Device
{

class LX_Mouse_ final
{
    SDL_Cursor * _cursor = nullptr;

public:

    LX_Mouse_( const LX_Mouse_& ) = delete;
    LX_Mouse_& operator =( const LX_Mouse_& ) = delete;

    LX_Mouse_( SDL_Surface * surface, int hot_x, int hot_y ) noexcept
        : _cursor( SDL_CreateColorCursor( surface, hot_x, hot_y ) ) {}

    bool isOpen() const noexcept
    {
        return _cursor != nullptr;
    }

    void setMouse() noexcept
    {
        SDL_SetCursor( _cursor );
    }

    ~LX_Mouse_()
    {
        SDL_FreeCursor( _cursor );
    }
};


LX_Mouse::LX_Mouse( const LX_Graphics::LX_BufferedImage& surface,
                    int hot_x, int hot_y ) noexcept
    : _mimpl( new LX_Mouse_( surface._surface, hot_x, hot_y ) ) {}

bool LX_Mouse::isOpen() const noexcept
{
    return _mimpl->isOpen();
}

void LX_Mouse::setMouse() noexcept
{
    _mimpl->setMouse();
}

LX_Mouse::~LX_Mouse()
{
    _mimpl.reset();
}

}
