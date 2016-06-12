
#include <LunatiX/Lunatix_engine.hpp>
#include <cstring>

class FuncDraw : public virtual LX_Text::LX_RedrawCallback
{
    LX_Win::LX_Window& w;
    LX_TrueTypeFont::LX_Font font;

public:

    explicit FuncDraw(LX_Win::LX_Window& win)
     : LX_Text::LX_RedrawCallback(), w(win), font(SDL_Color{255,255,255,0}) {}

    void operator ()(UTF8string& u8str)
    {
        w.clearWindow();

        if(!u8str.utf8_empty())
        {
            SDL_Surface *sf = font.drawBlendedText(u8str.utf8_str());
            SDL_Texture *tx = LX_Graphics::loadTextureFromSurface(sf,&w);

            int width, height;
            font.sizeOfText(u8str.utf8_str(),width,height);

            SDL_Rect r = {100,100,width,height};
            w.putTexture(tx,nullptr,&r);
        }
        w.update();
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

    // Add "øþŋł"
    event.type = SDL_TEXTINPUT;
    strcpy(event.text.text,"øþŋł");
    SDL_PushEvent(&event);

    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_BACKSPACE;

    for(int i = 0; i < 16; i++)
    {
        SDL_PushEvent(&event);
    }

    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_ESCAPE;
    SDL_PushEvent(&event);
}

int main(int argc, char** argv)
{
    LX_Log::setDebugMode(true);
    LX_Win::LX_WindowInfo info;
    LX_Win::LX_initWindowInfo(info);
    LX_Win::LX_loadWindowConfig(info);

    LX_Init();

    {
        LX_Win::LX_Window win(info);

        // Text input
        {
            FuncDraw callbck(win);
            generateInput();            // Automatic input
            LX_Text::LX_TextInput input;
            input.eventLoop(callbck);
        }
    }

    LX_Quit();
    return 0;
}
