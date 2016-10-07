

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
*    @version 0.8
*
*/

#include <LunatiX/LX_Mouse.hpp>
#include <LunatiX/LX_Image.hpp>

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


LX_Mouse::LX_Mouse(LX_Graphics::LX_Surface& surface, int hot_x, int hot_y)
    : _mouse(new LX_Mouse_(surface._surface,hot_x,hot_y)) {}


bool LX_Mouse::isOpen() const
{
    return _mouse.get()->isOpen();
}


void LX_Mouse::setMouse()
{
    _mouse.get()->setMouse();
}


LX_Mouse::~LX_Mouse()
{
    _mouse.reset();
}

};
