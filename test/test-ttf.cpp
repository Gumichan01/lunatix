
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

const char * fname = "font/AozoraMinchoMedium.ttf";

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
    LX_Colour colour = {255,255,255,255};

    LX_Log::log("Load an LX_Font object using RAII");
    {
        LX_Font f1(fname,colour,0);
        LX_Log::log("SUCCESS - Loaded with success");
    }

    LX_Log::log("Load another LX_Font object using RAII");
    {
        LX_Font f2(fname,colour,0);
        LX_Log::log("SUCCESS - Loaded with success");
    }

    {
        try
        {
            LX_Font ferror("invalid_file",colour,0);
            LX_Log::log("FAILURE - o_O. Expected: IOException, got: a valid object");
        }
        catch(IOException &)
        {
            LX_Log::log("SUCCESS - IOException occured. It was expected");
        }
    }

    font = new LX_Font(fname,colour,0);

    if(font == nullptr)
        LX_Log::log("FAILURE - Font not null");
    else
        LX_Log::log("SUCCESS - Font defined");

    delete font;
}


void test_SolidText()
{
    LX_Colour colour[] = {{255,255,255,0}, {255,0,255,0}};

    UTF8string str("がんばつて Gumichan01");
    LX_Win::LX_WindowInfo winfo;
    LX_Win::LX_initWindowInfo(winfo);
    winfo.title = "LunatiX - Test True Type Font - Solid text";
    winfo.w = 1000;
    LX_Win::LX_Window win(winfo);
    LX_Font font(fname, colour[0], 32);

    LX_Log::log("Load a solid text image and display it");

    {
        LX_Graphics::LX_SolidTextTexture simg(font,win);
        LX_Graphics::LX_SolidTextTexture simg2(font,win);
        LX_Log::log("SUCCESS - Image loaded");
        LX_Log::log("Set the following text: %s; size: 32",str.utf8_str());
        simg.setText(str);
        simg.setPosition(100,100);
        LX_Log::log("Done");
        win.clearWindow();
        LX_Log::log("Update");
        simg.draw();
        win.update();
        LX_Timer::delay(1024);

        simg2.setTextColour(colour[1]);
        simg2.setPosition(100,400);
        simg2.setText(str, 48);

        LX_Log::log("Size: 32 → 72");
        for(unsigned int j = 32; j < 74; j += 2)
        {
            simg.setSize(j);
            win.clearWindow();
            simg.draw();
            simg2.draw();
            win.update();
            LX_Timer::delay(100);
        }
        LX_Log::log("Done");

        simg.setPosition(256,256);
        simg.setSize(32);

        LX_Log::log("Rotation");
        for(double j = 0.0; j < 3.14 * 2; j += 0.1)
        {
            win.clearWindow();
            simg.draw(j);
            win.update();
            LX_Timer::delay(33);
        }
        LX_Log::log("Done");
    }
}


void test_ShadedText()
{
    LX_Colour colour = {0,0,0,0};
    LX_Colour bg = {255,200,127,0};
    LX_Colour bg2 = {64,40,4,0};

    UTF8string str("がんばつて Gumichan01");
    LX_Win::LX_WindowInfo winfo;
    LX_Win::LX_initWindowInfo(winfo);
    winfo.title = "LunatiX - Test True Type Font - Shaded text";
    winfo.w = 1000;
    LX_Win::LX_Window win(winfo);
    LX_Font font(fname,colour,32);

    LX_Log::log("Load a shaded text image and display it");

    {
        LX_Graphics::LX_ShadedTextTexture simg(str,32,font,bg,win);
        LX_Graphics::LX_ShadedTextTexture simg2(font,win);
        LX_Log::log("SUCCESS - Image loaded");
        LX_Log::log("Set the following text: %s; size: 32",str.utf8_str());
        simg.setText(str);
        simg.setPosition(100,100);
        LX_Log::log("Done");
        win.clearWindow();
        LX_Log::log("Update");
        simg.draw();
        win.update();
        LX_Timer::delay(1024);

        simg2.setTextColour({255,0,255,0});
        simg2.setPosition(100,400);
        simg2.setText(str,bg2);

        LX_Log::log("Size: 32 → 72");
        for(int j = 34; j < 74; j += 2)
        {
            simg.setSize(j);
            win.clearWindow();
            simg.draw();
            simg2.draw();
            win.update();
            LX_Timer::delay(100);
        }
        LX_Log::log("Done");

        simg.setPosition(256,256);
        simg.setSize(32);

        LX_Log::log("Rotation");
        for(double j = 0.0; j < 3.14 * 2; j += 0.1)
        {
            win.clearWindow();
            simg.draw(j);
            win.update();
            LX_Timer::delay(33);
        }
        LX_Log::log("Done");
    }
}


void test_BlendedText()
{
    LX_Colour colour = {255,255,255,255};

    UTF8string str("がんばつて Gumichan01");
    LX_Win::LX_WindowInfo winfo;
    LX_Win::LX_initWindowInfo(winfo);
    winfo.title = "LunatiX - Test True Type Font - Blended text";
    winfo.w = 1000;
    LX_Win::LX_Window win(winfo);
    LX_Font font(fname,colour, 32);

    LX_Log::log("Load a solid text image and display it");

    {
        LX_Graphics::LX_BlendedTextTexture simg(font,win);
        LX_Graphics::LX_BlendedTextTexture simg2(font,win);
        LX_Log::log("SUCCESS - Image loaded");
        LX_Log::log("Set the following text: %s; size: 32",str.utf8_str());
        simg.setText(str);
        simg.setPosition(100,100);
        LX_Log::log("Done");
        win.clearWindow();
        LX_Log::log("Update");
        simg.draw();
        win.update();
        LX_Timer::delay(1024);

        simg2.setTextColour({255,0,255,0});
        simg2.setPosition(100,400);
        simg2.setText(str,48);

        LX_Log::log("Size: 32 → 72");
        for(int j = 34; j < 74; j += 2)
        {
            simg.setSize(j);
            win.clearWindow();
            simg.draw();
            simg2.draw();
            win.update();
            LX_Timer::delay(100);
        }
        LX_Log::log("Done");

        simg.setPosition(256,256);
        simg.setSize(32);

        LX_Log::log("Rotation");
        for(double j = 0.0; j < 3.14 * 2; j += 0.1)
        {
            win.clearWindow();
            simg.draw(j);
            win.update();
            LX_Timer::delay(33);
        }
        LX_Log::log("Done");
    }
}
