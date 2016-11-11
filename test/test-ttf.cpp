
#include <iostream>
#include <LunatiX/Lunatix.hpp>

using namespace std;
using namespace LX_TrueTypeFont;
using namespace LX_FileIO;
using namespace LX_Config;

void test_font(void);
void test_font2(void);
void test_SolidText();
void test_ShadedText();
void test_BlendedText();

int main(int argc, char **argv)
{
    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - The LunatiX library has been initialized with success"
             << endl;

    LX_Log::setDebugMode();
    LX_Log::log("==== Test True Type Font ====");
    test_font();
    test_SolidText();
    test_ShadedText();
    test_BlendedText();
    LX_Log::log("==== END Test ====");

    LX_Quit();
    return EXIT_SUCCESS;
}


void test_font(void)
{
    LX_Font *font = nullptr;
    SDL_Color color = {255,255,255,255};

    LX_Log::log("Load an LX_Font object using RAII");
    {
        LX_Font f1(LX_Configuration::getInstance()->getFontFile(),color);
        LX_Log::log("SUCCESS - Loaded with success");
    }

    LX_Log::log("Load another LX_Font object using RAII");
    {
        LX_Font f2(LX_Configuration::getInstance()->getFontFile(),color,48);
        LX_Log::log("SUCCESS - Loaded with success");
    }

    {
        try
        {
            LX_Font ferror("invalid_file",color);
            LX_Log::log("FAILURE - o_O. Expected: IOException, got: a valid object");
        }
        catch(IOException &)
        {
            LX_Log::log("SUCCESS - IOException occured. It was expected");
        }
    }

    font = new LX_Font(color);

    if(font == nullptr)
        LX_Log::log("FAILURE - Font not null");
    else
        LX_Log::log("SUCCESS - Font defined");

    delete font;
}


void test_SolidText()
{
    SDL_Color color = {255,255,255,255};

    UTF8string str("がんばつて Gumichan01");
    LX_Win::LX_WindowInfo winfo;
    LX_Win::LX_initWindowInfo(winfo);
    winfo.title = "LunatiX - Test True Type Font - Solid text";
    winfo.w = 1000;
    LX_Win::LX_Window win(winfo);
    LX_Font font(LX_Configuration::getInstance()->getFontFile(),color);

    LX_Log::log("Load a solid text image and display it");

    {
        LX_Graphics::LX_SolidTextTexture simg(font,win);
        LX_Log::log("SUCCESS - Image loaded");
        LX_Log::log("Set the following text: %s; size: 32",str.utf8_str());
        simg.setText(str,32);
        simg.setPosition(100,100);
        LX_Log::log("Done");
        win.clearWindow();
        LX_Log::log("Update");
        simg.draw();
        win.update();
        SDL_Delay(1024);

        LX_Log::log("Size: 32 → 72");
        for(unsigned int j = 34; j < 74; j += 2)
        {
            simg.setSize(j);
            win.clearWindow();
            simg.draw();
            win.update();
            SDL_Delay(100);
        }
        LX_Log::log("Done");

        LX_Log::log("Rotation");
        for(double j = 0.0; j < 3.14 * 2; j += 0.1)
        {
            simg.setPosition(256,256);
            simg.setSize(32);
            win.clearWindow();
            simg.draw(j);
            win.update();
            SDL_Delay(33);
        }
        LX_Log::log("Done");
    }
}


void test_ShadedText()
{
    SDL_Color color = {0,0,0,0};
    SDL_Color bg = {255,200,127,0};

    UTF8string str("がんばつて Gumichan01");
    LX_Win::LX_WindowInfo winfo;
    LX_Win::LX_initWindowInfo(winfo);
    winfo.title = "LunatiX - Test True Type Font - Shaded text";
    winfo.w = 1000;
    LX_Win::LX_Window win(winfo);
    LX_Font font(LX_Configuration::getInstance()->getFontFile(),color);

    LX_Log::log("Load a shaded text image and display it");

    {
        LX_Graphics::LX_ShadedTextTexture simg(str,32,font,bg,win);
        LX_Log::log("SUCCESS - Image loaded");
        LX_Log::log("Set the following text: %s; size: 32",str.utf8_str());
        simg.setText(str,bg,32);
        simg.setPosition(100,100);
        LX_Log::log("Done");
        win.clearWindow();
        LX_Log::log("Update");
        simg.draw();
        win.update();
        SDL_Delay(1024);

        LX_Log::log("Size: 32 → 72");
        for(int j = 34; j < 74; j += 2)
        {
            simg.setSize(j);
            win.clearWindow();
            simg.draw();
            win.update();
            SDL_Delay(100);
        }
        LX_Log::log("Done");

        LX_Log::log("Rotation");
        for(double j = 0.0; j < 3.14 * 2; j += 0.1)
        {
            simg.setPosition(256,256);
            simg.setSize(32);
            win.clearWindow();
            simg.draw(j);
            win.update();
            SDL_Delay(33);
        }
        LX_Log::log("Done");
    }
}


void test_BlendedText()
{
    SDL_Color color = {255,255,255,255};

    UTF8string str("がんばつて Gumichan01");
    LX_Win::LX_WindowInfo winfo;
    LX_Win::LX_initWindowInfo(winfo);
    winfo.title = "LunatiX - Test True Type Font - Blended text";
    winfo.w = 1000;
    LX_Win::LX_Window win(winfo);
    LX_Font font(LX_Configuration::getInstance()->getFontFile(),color);

    LX_Log::log("Load a solid text image and display it");

    {
        LX_Graphics::LX_BlendedTextTexture simg(font,win);
        LX_Log::log("SUCCESS - Image loaded");
        LX_Log::log("Set the following text: %s; size: 32",str.utf8_str());
        simg.setText(str,32);
        simg.setPosition(100,100);
        LX_Log::log("Done");
        win.clearWindow();
        LX_Log::log("Update");
        simg.draw();
        win.update();
        SDL_Delay(1024);

        LX_Log::log("Size: 32 → 72");
        for(int j = 34; j < 74; j += 2)
        {
            simg.setSize(j);
            win.clearWindow();
            simg.draw();
            win.update();
            SDL_Delay(100);
        }
        LX_Log::log("Done");

        LX_Log::log("Rotation");
        for(double j = 0.0; j < 3.14 * 2; j += 0.1)
        {
            simg.setPosition(256,256);
            simg.setSize(32);
            win.clearWindow();
            simg.draw(j);
            win.update();
            SDL_Delay(33);
        }
        LX_Log::log("Done");
    }
}
