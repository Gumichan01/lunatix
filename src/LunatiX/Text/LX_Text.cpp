
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
    const size_t oldcursor = cursor;

    switch(ev.key.keysym.sym)
    {
        case SDLK_ESCAPE:       done = true;
                                break;

        case SDLK_BACKSPACE:    utf8Pop();
                                if(cursor > 0) {cursor -= 1;}
                                break;

        case SDLK_LEFT:         if(cursor > 0) {cursor -= 1;}
                                break;

        case SDLK_RIGHT:        if(cursor < u8text.utf8_length()) {cursor += 1;}
                                break;
    }

    if(oldcursor != cursor)
        LX_Log::log("Input - cursor at %d",cursor);
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
        const size_t u8len = u8text.utf8_length();

        if(cursor == u8len)
        {
            u8text += ev.text.text;
        }
        else
        {
            UTF8string ntext(ev.text.text);
            UTF8string rtmp = u8text.utf8_substr(cursor);
            UTF8string ltmp = u8text.utf8_substr(0,cursor);
            u8text = ltmp + ntext + rtmp;
        }

        cursor += 1;
        LX_Log::log("Input - cursor at %d",cursor);
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
