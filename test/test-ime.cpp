
#include <LunatiX/Lunatix.hpp>
#include <cstring>

using namespace LX_Event;

const char * fname = "font/AozoraMinchoMedium.ttf";
constexpr LX_Colour COLOUR = {255,255,255,0};

void generateInput();


class FuncDraw : public virtual LX_Text::LX_RedrawCallback
{
    LX_Win::LX_Window& _w;
    LX_TrueTypeFont::LX_Font _font;

public:

    explicit FuncDraw(LX_Win::LX_Window& win)
        : LX_Text::LX_RedrawCallback(), _w(win),
          _font(fname, COLOUR, 32) {}

    void operator ()(UTF8string& u8str, UTF8string& u8comp, bool update,
                     size_t cursor, size_t prev_cur) noexcept
    {
        if(update)
        {
            LX_Log::log("cursor → prev: %d; cur: %d\n",prev_cur,cursor);
            _w.clearWindow();

            if(!u8str.utf8_empty())
            {
                LX_Graphics::LX_BlendedTextTexture img(_font,_w);
                img.setText(u8str,24);
                img.setPosition(100,100);
                img.draw();
            }

            if(!u8comp.utf8_empty())
            {
                LX_Colour colour = {127,127,127,255};
                LX_Graphics::LX_ShadedTextTexture im(u8comp,18,_font,colour,_w);
                im.setPosition(100,124);
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
    strcpy(event.text.text,"hello world!");
    SDL_PushEvent(&event);

    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_BACKSPACE;

    // Remove 6 characters
    for(int i = 0; i < 6; i++)
    {
        SDL_PushEvent(&event);
    }

    // Add "がんばつて"
    event.type = SDL_TEXTINPUT;
    strcpy(event.text.text,"がんばつて");
    SDL_PushEvent(&event);

    // Add an invalid string
    strcpy(event.text.text,"\255");
    SDL_PushEvent(&event);

    // Add "øþŋł"
    strcpy(event.text.text,"øþŋł");
    SDL_PushEvent(&event);

    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_LEFT;
    SDL_PushEvent(&event);
    SDL_PushEvent(&event);

    event.type = SDL_TEXTINPUT;
    strcpy(event.text.text," がんばつて Gumichan01 ");
    SDL_PushEvent(&event);

    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_DELETE;
    SDL_PushEvent(&event);
    SDL_PushEvent(&event);
    SDL_PushEvent(&event);

    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_BACKSPACE;

    for(int i = 0; i < 12; i++)
    {
        SDL_PushEvent(&event);
    }

    SDL_Event nev;
    nev.type = SDL_KEYDOWN;
    nev.key.keysym.sym = SDLK_ESCAPE;
    SDL_PushEvent(&nev);
}

int main(int argc, char** argv)
{
    LX_Win::LX_WindowInfo info;
    LX_Win::LX_initWindowInfo(info);
    LX_Win::LX_loadWindowConfig(info);

    LX_Init();
    LX_Log::setDebugMode(true);
    LX_Log::log(" ==== TEST the text input ==== ");

    try
    {
        LX_Win::LX_Window win(info);
        win.clearWindow();
        win.update();
        // Text input
        {
            FuncDraw callbck(win);
            generateInput();            // Remove it in order to use the manual input
            LX_Text::LX_TextInput input;
            input.eventLoop(callbck);
        }

        LX_Log::log("SUCCESS - The input text module is well-implemented!");
    }
    catch(...)
    {
        LX_Log::logError(LX_Log::LX_LogType::TEST,
                         "FAILURE - Unexpected exception!");
    }

    LX_Log::log(" ==== END TEST ==== \n");
    LX_Quit();
    return EXIT_SUCCESS;
}
