
#include <Lunatix/Lunatix.hpp>
#include <cstring>

using namespace lx::Event;

const char * fname = "font/AozoraMinchoMedium.ttf";
constexpr lx::Graphics::Colour COLOUR = { 255, 255, 255, 255 };

void generateInput();


class FuncDraw : public virtual lx::Text::RedrawCallback
{
    lx::Win::Window& _w;
    lx::TrueTypeFont::Font _font;

public:

    explicit FuncDraw( lx::Win::Window& win )
        : lx::Text::RedrawCallback(), _w( win ), _font( fname, COLOUR, 32 ) {}

    void operator ()( UTF8string& u8str, UTF8string& u8comp, bool update,
                      size_t cursor, size_t prev_cur ) noexcept
    {
        if ( update )
        {
            lx::Log::log( "cursor → prev: %d; cur: %d\n", prev_cur, cursor );
            _w.clearWindow();

            if ( !u8str.utf8_empty() )
            {
                lx::Graphics::BlendedTextTexture img( _font, _w );
                img.setText( u8str, 24 );
                img.setPosition( 100, 100 );
                img.draw();
            }

            if ( !u8comp.utf8_empty() )
            {
                lx::Graphics::Colour colour = { 127, 127, 127, 255 };
                lx::Graphics::ShadedTextTexture im( u8comp, 18, _font, colour, _w );
                im.setPosition( 100, 124 );
                im.draw();
            }
            _w.update();
        }
    }

    ~FuncDraw() = default;
};

void generateInput()
{
    SDL_Event event;
    event.type = SDL_TEXTINPUT;
    strcpy( event.text.text, "hello world!" );
    SDL_PushEvent( &event );

    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_BACKSPACE;

    // Remove 6 characters
    for ( int i = 0; i < 6; i++ )
    {
        SDL_PushEvent( &event );
    }

    // Add "がんばつて"
    event.type = SDL_TEXTINPUT;
    strcpy( event.text.text, "がんばつて" );
    SDL_PushEvent( &event );

    // Add an invalid string
    strcpy( event.text.text, "\255" );
    SDL_PushEvent( &event );

    // Add "øþŋł"
    strcpy( event.text.text, "øþŋł" );
    SDL_PushEvent( &event );

    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_LEFT;
    SDL_PushEvent( &event );
    SDL_PushEvent( &event );

    event.type = SDL_TEXTINPUT;
    strcpy( event.text.text, " がんばつて Gumichan01 " );
    SDL_PushEvent( &event );

    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_DELETE;
    SDL_PushEvent( &event );
    SDL_PushEvent( &event );
    SDL_PushEvent( &event );

    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_BACKSPACE;

    for ( int i = 0; i < 12; i++ )
    {
        SDL_PushEvent( &event );
    }

    SDL_Event nev;
    nev.type = SDL_KEYDOWN;
    nev.key.keysym.sym = SDLK_ESCAPE;
    SDL_PushEvent( &nev );
}

int main( int argc, char ** argv )
{
    lx::Win::WindowInfo info;
    lx::Win::initWindowInfo( info );
    lx::Win::loadWindowConfig( info );

    lx::init();
    lx::Log::setDebugMode( true );
    lx::Log::log( " ==== TEST the text input ==== " );

    try
    {
        lx::Win::Window win( info );
        win.clearWindow();
        win.update();
        // Text input
        {
            FuncDraw callbck( win );
            generateInput();            // Remove it in order to use the manual input
            lx::Text::TextInput input;
            input.eventLoop( callbck );
        }

        lx::Log::log( "SUCCESS - The input text module is well-implemented!" );
    }
    catch ( ... )
    {
        lx::Log::logError( lx::Log::LogType::TEST,
                           "FAILURE - Unexpected exception!" );
    }

    lx::Log::log( " ==== END TEST ==== \n" );
    lx::quit();
    return EXIT_SUCCESS;
}
