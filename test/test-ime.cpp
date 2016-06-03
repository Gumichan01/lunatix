
#include <LunatiX/Lunatix_engine.hpp>


class FuncDraw : public virtual LX_Text::LX_RedrawCallback
{
    LX_Win::LX_Window& w;
    LX_TrueTypeFont::LX_Font font;

public:

    FuncDraw(LX_Win::LX_Window& win)
    : LX_Text::LX_RedrawCallback(), w(win), font(SDL_Color{255,255,255,0}){}

    void operator ()(UTF8string& u8str)
    {
        SDL_Surface *sf = nullptr;
        SDL_Texture *tx = nullptr;

        w.clearWindow();

        if(!u8str.utf8_empty())
        {
            sf = font.drawBlendedText(u8str.utf8_str());
            tx = LX_Graphics::loadTextureFromSurface(sf,&w);

            int width, height;
            font.sizeOfText(u8str.utf8_str(),width,height);
            SDL_Rect r = {100,100,width,height};

            w.clearWindow();
            w.putTexture(tx,nullptr,&r);
        }
        w.update();
    }

    ~FuncDraw() = default;
};


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
            LX_Text::LX_TextInput input;
            input.eventLoop(callbck);
        }
    }

    LX_Quit();
    return 0;
}
