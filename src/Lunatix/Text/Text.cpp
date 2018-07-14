
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
*   @brief The implementation of TextInput
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.13
*
*/

#include <Lunatix/Text.hpp>
#include <Lunatix/Event.hpp>
#include <Lunatix/Time.hpp>
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

class TextInput_ final
{
    UTF8string m_u8text;
    UTF8string m_u8comp;
    size_t m_cursor;
    bool m_done;
    bool m_draw;
    bool m_composing;

    // Save a text in the clipboard get it from it
    void save_() noexcept
    {
        static const uint8_t * KEYS = lx::Event::EventHandler::getKeyboardState().state;

        if ( KEYS[SDL_SCANCODE_LCTRL] )
        {
            int err = SDL_SetClipboardText( m_u8text.utf8_str() );

            if ( err == -1 )
            {
                UTF8string s( "Cannot set " + m_u8text + "in the clipboard" + SDL_GetError() );
                lx::Log::logDebug( lx::Log::LogType::INPUT,
                                   "Cannot set %s in the clipboard.", s.utf8_str() );
            }
            else
            {
                lx::Log::logDebug( lx::Log::LogType::INPUT,
                                   "Copy %s into the clipboard.", m_u8text.utf8_str() );
            }
        }
    }

    void paste_() noexcept
    {
        static const uint8_t * KEYS = lx::Event::EventHandler::getKeyboardState().state;

        if ( KEYS[SDL_SCANCODE_LCTRL] )
        {
            if ( !SDL_HasClipboardText() )
            {
                lx::Log::log( "Empty clipboard." );
                return;
            }

            const char * CLIPBOARD_TXT = SDL_GetClipboardText();

            if ( CLIPBOARD_TXT == nullptr )
            {
                lx::Log::logError( lx::Log::LogType::SYSTEM,
                                   "Cannot get the text from the clipboard" );
                return;
            }

            lx::Log::logDebug( lx::Log::LogType::INPUT, "Paste %s", CLIPBOARD_TXT );

            try
            {
                u8stringInput_( UTF8string( CLIPBOARD_TXT ) );
            }
            catch ( ... )
            {
                lx::Log::logError( lx::Log::LogType::INPUT,
                                   "Invalid UTF-8 string from the clipboard." );
            }
        }
    }

    // Input
    void keyCode( const lx::Event::EventHandler& ev )
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
            if ( m_cursor > 0U )
                m_cursor -= 1U;
            break;

        case SDLK_RIGHT:
            if ( m_cursor < m_u8text.utf8_length() )
                m_cursor += 1U;
            break;

        case SDLK_HOME:
            m_cursor = 0U;
            break;

        case SDLK_END:
            m_cursor = m_u8text.utf8_length();
            break;

        default:
            break;
        }
    }

    void keyboardInput_( const lx::Event::EventHandler& ev ) noexcept
    {
        const size_t OLD_CURSOR = m_cursor;

        if ( ev.getKeyCode() == SDLK_ESCAPE )
        {
            m_done = true;
            return;
        }

        if ( m_composing )
            return;

        keyCode( ev );
        lx::Event::ScanCode sc = ev.getScanCode();

        if ( sc == SDL_SCANCODE_C )
            save_();

        else if ( sc == SDL_SCANCODE_V )
        {
            paste_();
            m_draw = true;
        }

        if ( OLD_CURSOR != m_cursor )
            lx::Log::logDebug( lx::Log::LogType::INPUT,
                               "Input - m_cursor at %d", m_cursor );
    }

    void textInput_( const lx::Event::EventHandler& ev ) noexcept
    {
        const lx::Event::TextEvent TEXTEV = ev.getTextEvent();

        if ( TEXTEV.text[0] == '\0' || isEOL( TEXTEV.text ) )
            return;

        lx::Log::logDebug( lx::Log::LogType::INPUT,
                           "New input : '%s' of length (in bytes) %d",
                           TEXTEV.text.c_str(), TEXTEV.text.length() );

        try
        {
            u8stringInput_( UTF8string( TEXTEV.text ) );
            m_draw = true;
            m_u8comp = "";
        }
        catch ( ... )
        {
            lx::Log::logError( lx::Log::LogType::INPUT,
                               "Invalid UTF-8 string: %s", TEXTEV.text.c_str() );
        }
    }

    void textEdit_( const lx::Event::EventHandler& ev ) noexcept
    {
        lx::Log::logDebug( lx::Log::LogType::INPUT, "Edit the text" );
        lx::Log::logDebug( lx::Log::LogType::INPUT, "New edition: %s",
                           ev.getTextEvent().text.c_str() );

        lx::Log::logDebug( lx::Log::LogType::INPUT, "start: %d; len: %d",
                           ev.getTextEvent().start, ev.getTextEvent().length );
        m_u8comp = ev.getTextEvent().text;

        if ( m_u8comp.utf8_empty() )
            m_composing = false;
        else
            m_composing = true;

        m_draw = true;
    }

    // Operation on the string
    void u8stringInput_( const UTF8string& ntext ) noexcept
    {
        const size_t U8LEN = m_u8text.utf8_length();

        if ( m_cursor == U8LEN )
        {
            m_u8text += ntext;
        }
        else
        {
            const UTF8string& RTMP = m_u8text.utf8_substr( m_cursor );
            const UTF8string& LTMP = m_u8text.utf8_substr( 0, m_cursor );
            m_u8text = LTMP + ntext + RTMP;
        }

        m_cursor += ntext.utf8_length();
    }

    void utf8Pop_() noexcept
    {
        lx::Log::logDebug( lx::Log::LogType::INPUT,
                           "Remove the last codepoint (utf8 character)" );

        try
        {
            m_u8text.utf8_pop();
        }
        catch ( ... )
        {
            lx::Log::logError( lx::Log::LogType::INPUT,
                               "Empty UTF-8 string: cannot remove the character" );
        }
    }

    void backslashKey_() noexcept
    {
        if ( m_cursor > 0U )
        {
            lx::Log::logDebug( lx::Log::LogType::INPUT,
                               "Backslash key - Remove the following codepoint at %d: %s",
                               m_cursor - 1, m_u8text.utf8_at( m_cursor - 1 ).c_str() );

            if ( m_cursor == m_u8text.utf8_length() )
            {
                utf8Pop_();
            }
            else
            {
                m_u8text.utf8_erase( m_u8text.utf8_begin() + m_cursor - 1U );
            }

            m_cursor -= 1U;
            m_draw = true;
        }
    }

    void deleteKey_() noexcept
    {
        const size_t U8LEN = m_u8text.utf8_length();

        if ( m_cursor < U8LEN )
        {
            lx::Log::logDebug( lx::Log::LogType::INPUT,
                               "Delete key - Remove the following codepoint at %d: %s",
                               m_cursor, m_u8text.utf8_at( m_cursor ).c_str() );
        }

        if ( m_cursor > 0U && m_cursor < U8LEN )
        {
            m_u8text.utf8_erase( m_u8text.utf8_begin() + m_cursor );
            m_draw = true;
        }
        else if ( m_cursor == 0 )
        {
            m_u8text = m_u8text.utf8_substr( m_cursor + 1U );
            m_draw = true;
        }
    }

public:

    TextInput_() noexcept
        : m_u8text(), m_u8comp(), m_cursor( 0 ), m_done( false ), m_draw( false ),
          m_composing( false )
    {
        lx::Log::logDebug( lx::Log::LogType::INPUT, "Start the input." );
        SDL_StartTextInput();
    }


    void eventLoop_( RedrawCallback& redraw ) noexcept
    {
        size_t prev_cur = m_cursor;
        lx::Event::EventHandler ev;
        m_done = false;
        m_draw = false;

        while ( !m_done )
        {
            while ( ev.pollEvent() )
            {
                switch ( ev.getEventType() )
                {
                case lx::Event::EventType::KEYDOWN:
                    keyboardInput_( ev );
                    break;

                case lx::Event::EventType::TEXTINPUT:
                    textInput_( ev );
                    break;

                case lx::Event::EventType::TEXTEDITING:
                    textEdit_( ev );
                    break;

                default:
                    break;
                }

                redraw( m_u8text, m_u8comp, m_draw, m_cursor, prev_cur );
                prev_cur = m_cursor;
                m_draw = false;
            }

            lx::Time::delay( DELAY );
        }
    }


    ~TextInput_() noexcept
    {
        lx::Log::logDebug( lx::Log::LogType::INPUT, "End of input." );
        SDL_StopTextInput();
    }
};

/* Text input, public functions         */

TextInput::TextInput() noexcept : m_timpl( new TextInput_() ) {}

/*
*   Handle the event loop and the internal text input.
*/
void TextInput::eventLoop( RedrawCallback& redraw ) noexcept
{
    m_timpl->eventLoop_( redraw );
}

TextInput::~TextInput() noexcept
{
    m_timpl.reset();
}

}   // Text

}   // lx
