
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
*	@file LX_Text.cpp
*	@brief The implementation of LX_TextInput
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.7
*
*/

#include <LunatiX/LX_Text.hpp>
#include <LunatiX/LX_Log.hpp>

#include <cstring>
#include <string>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_events.h>

namespace LX_Text
{

// Anonymous
namespace
{
    bool isEndofLine(char * text)
    {
        return text[0] == '\n' || text[0] == '\r';
    }

    Uint32 DELAY = 33;
};


LX_RedrawCallback::LX_RedrawCallback() {}
LX_RedrawCallback::~LX_RedrawCallback() {}


LX_TextInput::LX_TextInput()
    : cursor(0),done(false)
{
    LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,"Start the input.");
    SDL_StartTextInput();
}


void LX_TextInput::eventLoop(LX_RedrawCallback& redraw)
{
    SDL_Event ev;
    done = false;

    while(!done)
    {
        while(SDL_PollEvent(&ev))
        {
            switch(ev.type)
            {
                case SDL_KEYDOWN    : keyboardInput(ev);
                                      break;

                case SDL_TEXTINPUT  : textInput(ev);
                                      break;

                case SDL_TEXTEDITING: textEdit(ev);
                                      break;

                default : break;
            }

            redraw(u8text,cursor);
        }

        SDL_Delay(DELAY);
    }
}

// Handle the keyboard input
void LX_TextInput::keyboardInput(SDL_Event& ev)
{
    switch(ev.key.keysym.sym)
    {
        case SDLK_ESCAPE:       done = true;
                                break;

        case SDLK_BACKSPACE:    utf8Pop();
                                break;

    }
}


void LX_TextInput::textInput(SDL_Event& ev)
{
    if(ev.text.text[0] == '\0' || isEndofLine(ev.text.text))
        return;

    LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                       "New input : '%s' of length (in bytes) %d",
                       ev.text.text,strlen(ev.text.text));

    try
    {
        u8text += ev.text.text;
    }
    catch(...)
    {
        LX_Log::logError(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                         "Invalid UTF-8 string: %s", ev.text.text);
        u8text.utf8_pop();
    }
}


void LX_TextInput::textEdit(SDL_Event& ev)
{
    /// NOTE How do I deal with that?
    LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,"Edit the text");
    LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,"New edition: %s",
                     ev.edit.text);
}


// Safely remove the last character (UTF-8 codepoint) of the string
void LX_TextInput::utf8Pop()
{
    LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                       "Remove the last codepoint (utf8 character)");

    try
    {
        u8text.utf8_pop();
    }
    catch(...)
    {
        LX_Log::logError(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                         "Empty UTF-8 string: cannot remove the character");
    }
}


LX_TextInput::~LX_TextInput()
{
    LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,"End of input.");
    SDL_StopTextInput();
}

};
