
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
*   @file Text.cpp
*   @brief The implementation of LX_TextInput
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/Text.hpp>
#include <Lunatix/Event.hpp>
#include <Lunatix/Timer.hpp>
#include <Lunatix/Log.hpp>

#include <SDL2/SDL_clipboard.h>
#include <SDL2/SDL_keyboard.h>


// Anonymous
namespace
{

// Check if the string is an End-Of-Line string (EOL)
inline bool isEOL( const std::string& text ) noexcept
{
    return text[0] == '\n' || text[0] == '\r';
}

}


namespace lx
{

namespace Text
{

const uint32_t DELAY = 33;

/* Text input, private implementation   */

class LX_TextInput_ final
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
        static const uint8_t * KEYS = lx::Event::LX_EventHandler::getKeyboardState().state;

        if ( KEYS[SDL_SCANCODE_LCTRL] )
        {
            int err = SDL_SetClipboardText( _u8text.utf8_str() );

            if ( err == -1 )
            {
                UTF8string s( "Cannot set " + _u8text + "in the clipboard" + SDL_GetError() );
                lx::Log::logDebug( lx::Log::LX_LogType::INPUT,
                                  "Cannot set %s in the clipboard.", s.utf8_str() );
            }
            else
            {
                lx::Log::logDebug( lx::Log::LX_LogType::INPUT,
                                  "Copy %s into the clipboard.", _u8text.utf8_str() );
            }
        }
    }

    void paste_() noexcept
    {
        static const uint8_t * KEYS = lx::Event::LX_EventHandler::getKeyboardState().state;

        if ( KEYS[SDL_SCANCODE_LCTRL] )
        {
            if ( !SDL_HasClipboardText() )
            {
                lx::Log::log( "Empty clipboard." );
                return;
            }

            char * s = SDL_GetClipboardText();

            if ( s == nullptr )
            {
                lx::Log::logError( lx::Log::LX_LogType::SYSTEM,
                                  "Cannot get the string from the clipboard" );
                return;
            }

            try
            {
                u8stringInput_( UTF8string( s ) );
            }
            catch ( ... )
            {
                lx::Log::logError( lx::Log::LX_LogType::INPUT,
                                  "Invalid UTF-8 string from the clipboard." );
            }

            lx::Log::logDebug( lx::Log::LX_LogType::INPUT, "Paste %s", s );
        }
    }

    // Input
    void keyCode( const lx::Event::LX_EventHandler& ev )
    {
        switch ( ev.getKeyCode() )
        {

        case SDLK_BACKSPACE:
            backslashKey_();
            break;

        case SDLK_DELETE:
            deleteKey_();
            break;

        case SDLK_LEFT:
            if ( _cursor > 0U )
                _cursor -= 1U;
            break;

        case SDLK_RIGHT:
            if ( _cursor < _u8text.utf8_length() )
                _cursor += 1U;
            break;

        case SDLK_HOME:
            _cursor = 0U;
            break;

        case SDLK_END:
            _cursor = _u8text.utf8_length();
            break;

        default:
            break;
        }
    }

    void keyboardInput_( const lx::Event::LX_EventHandler& ev ) noexcept
    {
        const size_t old_cursor = _cursor;

        if ( ev.getKeyCode() == SDLK_ESCAPE )
        {
            _done = true;
            return;
        }

        if ( _composing )
            return;

        keyCode( ev );
        lx::Event::LX_ScanCode sc = ev.getScanCode();

        if ( sc == SDL_SCANCODE_C )
            save_();

        else if ( sc == SDL_SCANCODE_V )
        {
            paste_();
            _draw = true;
        }

        if ( old_cursor != _cursor )
            lx::Log::logDebug( lx::Log::LX_LogType::INPUT,
                              "Input - _cursor at %d", _cursor );
    }

    void textInput_( const lx::Event::LX_EventHandler& ev ) noexcept
    {
        const lx::Event::LX_TextEvent tev = ev.getTextEvent();

        if ( tev.text[0] == '\0' || isEOL( tev.text ) )
            return;

        lx::Log::logDebug( lx::Log::LX_LogType::INPUT,
                          "New input : '%s' of length (in bytes) %d",
                          tev.text.c_str(), tev.text.length() );

        try
        {
            u8stringInput_( UTF8string( tev.text ) );
            _draw = true;
            _u8comp = "";
        }
        catch ( ... )
        {
            lx::Log::logError( lx::Log::LX_LogType::INPUT,
                              "Invalid UTF-8 string: %s", tev.text.c_str() );
        }
    }

    void textEdit_( const lx::Event::LX_EventHandler& ev ) noexcept
    {
        lx::Log::logDebug( lx::Log::LX_LogType::INPUT, "Edit the text" );
        lx::Log::logDebug( lx::Log::LX_LogType::INPUT, "New edition: %s",
                          ev.getTextEvent().text.c_str() );

        lx::Log::logDebug( lx::Log::LX_LogType::INPUT, "start: %d; len: %d",
                          ev.getTextEvent().start, ev.getTextEvent().length );
        _u8comp = ev.getTextEvent().text.c_str();

        if ( _u8comp.utf8_empty() )
            _composing = false;
        else
            _composing = true;

        _draw = true;
    }

    // Operation on the string
    void u8stringInput_( const UTF8string& ntext ) noexcept
    {
        const size_t U8LEN = _u8text.utf8_length();

        if ( _cursor == U8LEN )
        {
            _u8text += ntext;
        }
        else
        {
            const UTF8string& RTMP = _u8text.utf8_substr( _cursor );
            const UTF8string& LTMP = _u8text.utf8_substr( 0, _cursor );
            _u8text = LTMP + ntext + RTMP;
        }

        _cursor += ntext.utf8_length();
    }

    void utf8Pop_() noexcept
    {
        lx::Log::logDebug( lx::Log::LX_LogType::INPUT,
                          "Remove the last codepoint (utf8 character)" );

        try
        {
            _u8text.utf8_pop();
        }
        catch ( ... )
        {
            lx::Log::logError( lx::Log::LX_LogType::INPUT,
                              "Empty UTF-8 string: cannot remove the character" );
        }
    }

    void backslashKey_() noexcept
    {
        if ( _cursor > 0U )
        {
            lx::Log::logDebug( lx::Log::LX_LogType::INPUT,
                              "Backslash key - Remove the following codepoint at %d: %s",
                              _cursor - 1, _u8text.utf8_at( _cursor - 1 ).c_str() );

            if ( _cursor == _u8text.utf8_length() )
            {
                utf8Pop_();
            }
            else
            {
                _u8text.utf8_erase( _u8text.utf8_begin() + _cursor - 1U );
            }

            _cursor -= 1U;
            _draw = true;
        }
    }

    void deleteKey_() noexcept
    {
        const size_t U8LEN = _u8text.utf8_length();

        if ( _cursor < U8LEN )
        {
            lx::Log::logDebug( lx::Log::LX_LogType::INPUT,
                              "Delete key - Remove the following codepoint at %d: %s",
                              _cursor, _u8text.utf8_at( _cursor ).c_str() );
        }

        if ( _cursor > 0U && _cursor < U8LEN )
        {
            _u8text.utf8_erase( _u8text.utf8_begin() + _cursor );
            _draw = true;
        }
        else if ( _cursor == 0 )
        {
            _u8text = _u8text.utf8_substr( _cursor + 1U );
            _draw = true;
        }
    }

public:

    LX_TextInput_() noexcept
        : _u8text(), _u8comp(), _cursor( 0 ), _done( false ), _draw( false ),
          _composing( false )
    {
        lx::Log::logDebug( lx::Log::LX_LogType::INPUT, "Start the input." );
        SDL_StartTextInput();
    }


    void eventLoop_( LX_RedrawCallback& redraw ) noexcept
    {
        size_t prev_cur = _cursor;
        lx::Event::LX_EventHandler ev;
        _done = false;
        _draw = false;

        while ( !_done )
        {
            while ( ev.pollEvent() )
            {
                switch ( ev.getEventType() )
                {
                case lx::Event::LX_EventType::KEYDOWN:
                    keyboardInput_( ev );
                    break;

                case lx::Event::LX_EventType::TEXTINPUT:
                    textInput_( ev );
                    break;

                case lx::Event::LX_EventType::TEXTEDITING:
                    textEdit_( ev );
                    break;

                default:
                    break;
                }

                redraw( _u8text, _u8comp, _draw, _cursor, prev_cur );
                prev_cur = _cursor;
                _draw = false;
            }

            lx::Time::delay( DELAY );
        }
    }


    ~LX_TextInput_() noexcept
    {
        lx::Log::logDebug( lx::Log::LX_LogType::INPUT, "End of input." );
        SDL_StopTextInput();
    }
};

/* Text input, public functions         */

LX_TextInput::LX_TextInput() noexcept : _timpl( new LX_TextInput_() ) {}

/*
*   Handle the event loop and the internal text input.
*
*   This function updates an internal string on each text input and
*   send it to the callback function given by the user to something with that.
*/
void LX_TextInput::eventLoop( LX_RedrawCallback& redraw ) noexcept
{
    _timpl->eventLoop_( redraw );
}

LX_TextInput::~LX_TextInput() noexcept
{
    _timpl.reset();
}

}   // Text

}   // lx
