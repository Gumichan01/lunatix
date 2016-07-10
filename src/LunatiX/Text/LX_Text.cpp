
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
*	@version 0.8
*
*/

#include <LunatiX/LX_Text.hpp>
#include <LunatiX/LX_Log.hpp>

#include <cstring>
#include <string>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_clipboard.h>

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

/**
*   @fn void LX_TextInput::eventLoop(LX_RedrawCallback& redraw)
*
*   Handle the event loop and the internal text input.
*
*   This function updates an internal string on each text input and
*   send it to the callback function given by the user to something with that.
*
*   @param redraw The callback function
*
*/
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
                case SDL_KEYDOWN    :
                    keyboardInput(ev);
                    break;

                case SDL_TEXTINPUT  :
                    textInput(ev);
                    break;

                case SDL_TEXTEDITING:
                    textEdit(ev);
                    break;

                default :
                    break;
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
        case SDLK_ESCAPE:
            done = true;
            break;

        case SDLK_BACKSPACE:
            backslashKey();
            if(cursor > 0)
            {
                cursor -= 1;
            }
            break;

        case SDLK_DELETE:
            deleteKey();
            break;

        case SDLK_LEFT:
            if(cursor > 0)
            {
                cursor -= 1;
            }
            break;

        case SDLK_RIGHT:
            if(cursor < u8text.utf8_length())
            {
                cursor += 1;
            }
            break;

        case SDLK_HOME:
            cursor = 0;
            break;

        case SDLK_END:
            cursor = u8text.utf8_length();
            break;

        case SDLK_v:
            paste();
            break;

        case SDLK_c:
            save();
            break;
    }

    if(oldcursor != cursor)
        LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                         "Input - cursor at %d",cursor);
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
        UTF8string ntext(ev.text.text);
        u8stringInput(ntext);
    }
    catch(...)
    {
        LX_Log::logError(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                         "Invalid UTF-8 string: %s", ev.text.text);
    }
}


void LX_TextInput::u8stringInput(UTF8string& ntext)
{
    const size_t u8len = u8text.utf8_length();

    if(cursor == u8len)
    {
        u8text += ntext;
    }
    else
    {
        UTF8string rtmp = u8text.utf8_substr(cursor);
        UTF8string ltmp = u8text.utf8_substr(0,cursor);
        u8text = ltmp + ntext + rtmp;
    }

    cursor += ntext.utf8_length();
}


void LX_TextInput::textEdit(SDL_Event& ev)
{
    LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,"Edit the text");
    LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,"New edition: %s",
                     ev.edit.text);
}


void LX_TextInput::save()
{
    static const Uint8 *KEYS = SDL_GetKeyboardState(nullptr);

    if(KEYS[SDL_SCANCODE_LCTRL])
    {
        int err = SDL_SetClipboardText(u8text.utf8_str());

        if(err == -1)
        {
            UTF8string s("Cannot set " + u8text + "in the clipboard" + SDL_GetError());
            LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                             "Cannot set %s in the clipboard.",s.utf8_str());
        }
        else
        {
            LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                             "Copy %s into the clipboard.",u8text.utf8_str());
        }
    }
}


void LX_TextInput::paste()
{
    static const Uint8 *KEYS = SDL_GetKeyboardState(nullptr);

    if(KEYS[SDL_SCANCODE_LCTRL])
    {
        if(!SDL_HasClipboardText())
        {
            LX_Log::log("Empty clipboard.");
            return;
        }

        char *s = SDL_GetClipboardText();

        if(s == nullptr)
        {
            LX_Log::logError(LX_Log::LX_CATEGORY::LX_LOG_SYSTEM,
                             "Cannot get the string from the clipboard");
            return;
        }

        try
        {
            UTF8string ntext(s);
            u8stringInput(ntext);
        }
        catch(...)
        {
            LX_Log::logError(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                             "Invalid UTF-8 string from the clipboard.");
        }

        LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                         "Paste %s",s);
    }
}


void LX_TextInput::backslashKey()
{
    if(cursor == u8text.utf8_length())
    {
        utf8Pop();
    }
    else if(cursor > 0)
    {
        LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                         "Backslash key - Remove the following codepoint at %d: %s",
                         cursor-1, u8text.utf8_at(cursor-1).c_str());

        UTF8string rtmp = u8text.utf8_substr(cursor);
        UTF8string ltmp = u8text.utf8_substr(0,cursor-1);
        u8text = ltmp + rtmp;
    }
}


void LX_TextInput::deleteKey()
{
    const size_t u8len = u8text.utf8_length();

    if(cursor < u8len)
    {
        LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                         "Delete key - Remove the following codepoint at %d: %s",
                         cursor, u8text.utf8_at(cursor).c_str());
    }

    if(cursor > 0 && cursor < u8len)
    {
        UTF8string rtmp = u8text.utf8_substr(cursor + 1);
        UTF8string ltmp = u8text.utf8_substr(0,cursor);
        u8text = ltmp + rtmp;
    }
    else if(cursor == 0)
    {
        u8text = u8text.utf8_substr(cursor + 1);
    }
    else if(cursor == u8len - 1)
        utf8Pop();
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
