#ifndef LX_TEXT_HPP_INCLUDED
#define LX_TEXT_HPP_INCLUDED

/*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/

/**
*	@file LX_Text.hpp
*	@brief The interface of LX_TextInput
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.7
*
*/

#include <LunatiX/utils/utf8_string.hpp>

union SDL_Event;


namespace LX_Text
{

class LX_RedrawCallback
{
public:
    LX_RedrawCallback();
    virtual void operator ()(UTF8string& u8str) = 0;
    virtual ~LX_RedrawCallback();
};


class LX_TextInput
{
    UTF8string u8text;
    bool done;

    LX_TextInput(LX_TextInput& t);
    LX_TextInput(LX_TextInput&& t);
    LX_TextInput& operator =(LX_TextInput t);

    void keyboardInput(SDL_Event& ev);
    void textInput(SDL_Event& ev);
    void utf8Pop();

public:

    LX_TextInput();
    void eventLoop(LX_RedrawCallback& redraw);
    ~LX_TextInput();
};

};

#endif // LX_TEXT_HPP_INCLUDED
