

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
*    @file LX_Mouse.cpp
*    @brief The implementation of the mouse
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*
*/

#include <LunatiX/LX_Mouse.hpp>
#include <LunatiX/LX_Texture.hpp>

#include <SDL2/SDL_mouse.h>

namespace LX_Device
{

class LX_Mouse_
{
    SDL_Cursor * _cursor;

public:

    LX_Mouse_(SDL_Surface * surface, int hot_x, int hot_y)
        : _cursor(SDL_CreateColorCursor(surface,hot_x,hot_y)) {}

    bool isOpen() const
    {
        return _cursor != nullptr;
    }

    void setMouse()
    {
        SDL_SetCursor(_cursor);
    }

    ~LX_Mouse_()
    {
        SDL_FreeCursor(_cursor);
    }
};


LX_Mouse::LX_Mouse(LX_Graphics::LX_BufferedImage& surface, int hot_x, int hot_y)
    : _mimpl(new LX_Mouse_(surface._surface,hot_x,hot_y)) {}


bool LX_Mouse::isOpen() const
{
    return _mimpl->isOpen();
}


void LX_Mouse::setMouse()
{
    _mimpl->setMouse();
}


LX_Mouse::~LX_Mouse()
{
    _mimpl.reset();
}

};
