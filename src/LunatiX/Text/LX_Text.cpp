
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

/**
*   @file LX_Text.cpp
*   @brief The implementation of LX_TextInput
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*
*/

#include <LunatiX/LX_Text.hpp>
#include <LunatiX/LX_Event.hpp>
#include <LunatiX/LX_Timer.hpp>
#include <LunatiX/LX_Log.hpp>

#include <SDL2/SDL_clipboard.h>
#include <SDL2/SDL_keyboard.h>

using namespace LX_Event;

// Anonymous
namespace
{

uint32_t DELAY = 33;

// Check if the string is an End-Of-Line string (EOL)
inline bool isEOL(const std::string& text) noexcept
{
    return text[0] == '\n' || text[0] == '\r';
}

}

namespace LX_Text
{


/* Text input, private implementation   */

class LX_TextInput_
{
    UTF8string _u8text;
    UTF8string _u8comp;
    size_t _cursor;
    bool _done;
    bool _draw;
    bool _composing;

    // Save a text in the clipboard get it from it
    void save_() noexcept
    {
        static const uint8_t *KEYS = LX_EventHandler::getKeyboardState().state;

        if(KEYS[SDL_SCANCODE_LCTRL])
        {
            int err = SDL_SetClipboardText(_u8text.utf8_str());

            if(err == -1)
            {
                UTF8string s("Cannot set " + _u8text + "in the clipboard" + SDL_GetError());
                LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                                 "Cannot set %s in the clipboard.",s.utf8_str());
            }
            else
            {
                LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                                 "Copy %s into the clipboard.",_u8text.utf8_str());
            }
        }
    }

    void paste_() noexcept
    {
        static const uint8_t *KEYS = LX_EventHandler::getKeyboardState().state;

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
                u8stringInput_(ntext);
            }
            catch(...)
            {
                LX_Log::logError(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                                 "Invalid UTF-8 string from the clipboard.");
            }

            LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,"Paste %s",s);
        }
    }

    // Input
    void keyboardInput_(LX_Event::LX_EventHandler& ev) noexcept
    {
        const size_t old_cursor = _cursor;

        if(ev.getKeyCode() == SDLK_ESCAPE)
        {
            _done = true;
            return;
        }

        if(_composing)
            return;

        switch(ev.getKeyCode())
        {

        case SDLK_BACKSPACE:
            backslashKey_();
            break;

        case SDLK_DELETE:
            deleteKey_();
            break;

        case SDLK_LEFT:
            if(_cursor > 0)
            {
                _cursor -= 1;
            }
            break;

        case SDLK_RIGHT:
            if(_cursor < _u8text.utf8_length())
            {
                _cursor += 1;
            }
            break;

        case SDLK_HOME:
            _cursor = 0;
            break;

        case SDLK_END:
            _cursor = _u8text.utf8_length();
            break;

        default:
            break;
        }

        LX_Event::LX_ScanCode sc = ev.getScanCode();

        if(sc == SDL_SCANCODE_C)
            save_();
        else if(sc == SDL_SCANCODE_V)
        {
            paste_();
            _draw = true;
        }

        if(old_cursor != _cursor)
            LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                             "Input - _cursor at %d",_cursor);
    }

    void textInput_(LX_Event::LX_EventHandler& ev) noexcept
    {
        const LX_Event::LX_TextEvent tev = ev.getTextEvent();

        if(tev.text[0] == '\0' || isEOL(tev.text))
            return;

        LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                         "New input : '%s' of length (in bytes) %d",
                         tev.text.c_str(),tev.text.length());

        try
        {
            UTF8string ntext(tev.text);
            u8stringInput_(ntext);
            _draw = true;
            _u8comp = "";
        }
        catch(...)
        {
            LX_Log::logError(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                             "Invalid UTF-8 string: %s", tev.text.c_str());
        }
    }

    void textEdit_(LX_Event::LX_EventHandler& ev) noexcept
    {
        LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,"Edit the text");
        LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,"New edition: %s",
                         ev.getTextEvent().text.c_str());

        LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,"start: %d; len: %d",
                         ev.getTextEvent().start, ev.getTextEvent().length);
        _u8comp = ev.getTextEvent().text.c_str();

        if(_u8comp.utf8_empty())
            _composing = false;
        else
            _composing = true;

        _draw = true;
    }

    // Operation on the string
    void u8stringInput_(UTF8string& ntext) noexcept
    {
        const size_t u8len = _u8text.utf8_length();

        if(_cursor == u8len)
        {
            _u8text += ntext;
        }
        else
        {
            UTF8string rtmp = _u8text.utf8_substr(_cursor);
            UTF8string ltmp = _u8text.utf8_substr(0,_cursor);
            _u8text = ltmp + ntext + rtmp;
        }

        _cursor += ntext.utf8_length();
    }

    void utf8Pop_() noexcept
    {
        LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                         "Remove the last codepoint (utf8 character)");

        try
        {
            _u8text.utf8_pop();
        }
        catch(...)
        {
            LX_Log::logError(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                             "Empty UTF-8 string: cannot remove the character");
        }
    }

    void backslashKey_() noexcept
    {
        if(_cursor > 0)
        {
            LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                             "Backslash key - Remove the following codepoint at %d: %s",
                             _cursor-1, _u8text.utf8_at(_cursor-1).c_str());

            if(_cursor == _u8text.utf8_length())
            {
                utf8Pop_();
            }
            else
            {
                UTF8string rtmp = _u8text.utf8_substr(_cursor);
                UTF8string ltmp = _u8text.utf8_substr(0,_cursor-1);
                _u8text = ltmp + rtmp;
            }

            _cursor -= 1;
            _draw = true;
        }
    }

    void deleteKey_() noexcept
    {
        const size_t u8len = _u8text.utf8_length();

        if(_cursor < u8len)
        {
            LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,
                             "Delete key - Remove the following codepoint at %d: %s",
                             _cursor, _u8text.utf8_at(_cursor).c_str());
        }

        if(_cursor > 0 && _cursor < u8len)
        {
            UTF8string rtmp = _u8text.utf8_substr(_cursor + 1);
            UTF8string ltmp = _u8text.utf8_substr(0,_cursor);
            _u8text = ltmp + rtmp;
            _draw = true;
        }
        else if(_cursor == 0)
        {
            _u8text = _u8text.utf8_substr(_cursor + 1);
            _draw = true;
        }
    }

public:

    LX_TextInput_() noexcept
        : _cursor(0),_done(false),_draw(false), _composing(false)
    {
        LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,"Start the input.");
        SDL_StartTextInput();
    }


    void eventLoop_(LX_RedrawCallback& redraw) noexcept
    {
        size_t prev_cur = _cursor;
        LX_EventHandler ev;
        _done = false;
        _draw = false;

        while(!_done)
        {
            while(ev.pollEvent())
            {
                switch(ev.getEventType())
                {
                case LX_EventType::LX_KEYDOWN:
                    keyboardInput_(ev);
                    break;

                case LX_EventType::LX_TEXTINPUT:
                    textInput_(ev);
                    break;

                case LX_EventType::LX_TEXTEDITING:
                    textEdit_(ev);
                    break;

                default:
                    break;
                }

                redraw(_u8text, _u8comp, _draw, _cursor, prev_cur);
                prev_cur = _cursor;
                _draw = false;
            }

            LX_Timer::delay(DELAY);
        }
    }


    ~LX_TextInput_()
    {
        LX_Log::logDebug(LX_Log::LX_CATEGORY::LX_LOG_INPUT,"End of input.");
        SDL_StopTextInput();
    }
};

/* Text input, public functions         */

LX_TextInput::LX_TextInput() noexcept : _timpl(new LX_TextInput_()) {}

/*
*   Handle the event loop and the internal text input.
*
*   This function updates an internal string on each text input and
*   send it to the callback function given by the user to something with that.
*/
void LX_TextInput::eventLoop(LX_RedrawCallback& redraw) noexcept
{
    _timpl->eventLoop_(redraw);
}

LX_TextInput::~LX_TextInput()
{
    _timpl.reset();
}

}
