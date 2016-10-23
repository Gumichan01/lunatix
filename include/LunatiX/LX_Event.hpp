#ifndef LX_EVENT_HPP_INCLUDED
#define LX_EVENT_HPP_INCLUDED


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
*    @file LX_Event.hpp
*    @brief The Event module
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.9
*/

#include <SDL2/SDL_events.h>

namespace LX_Event
{
using LX_Input = SDL_Event;

bool pollEvent(LX_Input *event);
bool waitEvent(LX_Input *event);
bool waitEventTimeout(LX_Input *event, int timeout);

bool pushEvent(LX_Input *event);
};

#endif // LX_EVENT_HPP_INCLUDED
