
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
*   @file Mouse.cpp
*   @brief The implementation of the mouse
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/Mouse.hpp>
#include <Lunatix/Texture.hpp>

#include <SDL2/SDL_mouse.h>

namespace lx
{

namespace Device
{

class Mouse_ final
{
    SDL_Cursor * _cursor = nullptr;

public:

    Mouse_( const Mouse_& ) = delete;
    Mouse_& operator =( const Mouse_& ) = delete;

    Mouse_( SDL_Surface * surface, int hot_x, int hot_y ) noexcept
        : _cursor( SDL_CreateColorCursor( surface, hot_x, hot_y ) ) {}

    bool isOpen() const noexcept
    {
        return _cursor != nullptr;
    }

    void setMouse() noexcept
    {
        SDL_SetCursor( _cursor );
    }

    ~Mouse_()
    {
        SDL_FreeCursor( _cursor );
    }
};


Mouse::Mouse( const lx::Graphics::BufferedImage& surface,
                    int hot_x, int hot_y ) noexcept
    : _mimpl( new Mouse_( surface._surface, hot_x, hot_y ) ) {}

bool Mouse::isOpen() const noexcept
{
    return _mimpl->isOpen();
}

void Mouse::setMouse() noexcept
{
    _mimpl->setMouse();
}

Mouse::~Mouse()
{
    _mimpl.reset();
}

}   // Device

}   // lx
