
#include <iostream>
#include <Lunatix/Lunatix.hpp>

using namespace std;
using namespace lx::TrueTypeFont;
using namespace lx::FileIO;
using namespace lx::Config;

void test_font(void);
void test_font2(void);
void test_SolidText();
void test_ShadedText();
void test_BlendedText();


#ifdef __WIN32__
const char * fname = "font\\AozoraMinchoMedium.ttf";
#else
const char * fname = "font/AozoraMinchoMedium.ttf";
#endif


int main(int argc, char **argv)
{
    bool err = lx::init();

    if(!err)
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - lx::init() failed");
    else
        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - The LunatiX library has been initialized with success");

    lx::Log::setDebugMode();
    lx::Log::log("==== Test True Type Font ====");
    test_font();
    test_SolidText();
    test_ShadedText();
    test_BlendedText();
    lx::Log::log("==== END Test ====");

    lx::quit();
    return EXIT_SUCCESS;
}


void test_font(void)
{
    Font *font = nullptr;
    lx::Graphics::Colour colour = {255,255,255,255};

    lx::Log::log("Load an Font object using RAII");
    {
        Font f1(fname,colour,0);
        lx::Log::log("SUCCESS - Loaded with success");
        lx::Log::log("font file: %s",f1.getName().utf8_str());
        lx::Log::log("font file with path: %s",f1.getName(true).utf8_str());
    }

    lx::Log::log("Load another Font object using RAII");
    {
        Font f2(fname,colour,0);
        lx::Log::log("SUCCESS - Loaded with success");
    }

    {
        try
        {
            Font ferror("invalid_file",colour,0);
            lx::Log::log("FAILURE - o_O. Expected: IOException, got: a valid object");
        }
        catch(IOException &)
        {
            lx::Log::log("SUCCESS - IOException occured. It was expected");
        }
    }

    font = new Font(fname,colour,0);

    if(font == nullptr)
        lx::Log::log("FAILURE - Font not null");
    else
        lx::Log::log("SUCCESS - Font defined");

    delete font;
}


void test_SolidText()
{
    lx::Graphics::Colour dcolour = {255,0,255,127};
    lx::Graphics::Colour bcolour = {255,255,255, 127};

    UTF8string str("がんばつて Gumichan01");
    lx::Win::WindowInfo winfo;
    lx::Win::initWindowInfo(winfo);
    winfo.title = "LunatiX - Test True Type Font - Solid text";
    winfo.w = 1000;
    lx::Win::Window win(winfo);

    lx::Log::log("Load a solid text image and display it");

    {
        Font font(fname, dcolour, 32);
        lx::Graphics::SolidTextTexture simg(str,font,win);
        lx::Graphics::SolidTextTexture simg2(font,win);
        lx::Log::log("SUCCESS - Image loaded");
        lx::Log::log("sizes: %u %u", simg.getTextSize(), simg2.getTextSize());
        lx::Log::log("Set the following text: %s; size: 32",str.utf8_str());
        simg.setTextColour(bcolour);
        simg.setPosition(100,100);
        lx::Log::log("Done");
        lx::Log::log("text: %s", simg.getText().utf8_str());
        win.clearWindow();
        lx::Log::log("Draw text");
        simg.draw();
        win.update();
        lx::Time::delay(1024);

        simg2.setPosition(100,400);
        simg2.setText(str, 48);

        lx::Log::log("Size: 32 → 72");
        for(unsigned int j = 32; j < 74; j += 2)
        {
            simg.setTextSize(j);
            const std::pair< int, int> DIMENSION = simg.getTextDimension();
            lx::Log::log("Dimension: %d × %d", DIMENSION.first, DIMENSION.second);
            win.clearWindow();
            simg.draw();
            simg2.draw();
            win.update();
            lx::Time::delay(100);
        }
        lx::Log::log("Done");

        simg.setPosition(256,256);
        simg.setTextSize(32);

        lx::Log::log("Rotation");
        for(double j = 0.0; j < 3.14 * 2; j += 0.1)
        {
            win.clearWindow();
            simg.draw(j);
            win.update();
            lx::Time::delay(33);
        }
        lx::Log::log("Done");
    }
}


void test_ShadedText()
{
    lx::Graphics::Colour colour = {0,0,0,240};
    lx::Graphics::Colour bg = {255,200,127,127};
    lx::Graphics::Colour bg2 = {64,40,4,164};

    UTF8string str("がんばつて Gumichan01");
    lx::Win::WindowInfo winfo;
    lx::Win::initWindowInfo(winfo);
    winfo.title = "LunatiX - Test True Type Font - Shaded text";
    winfo.w = 1000;
    lx::Win::Window win(winfo);
    Font font(fname,colour,32);

    lx::Log::log("Load a shaded text image and display it");

    {
        lx::Graphics::ShadedTextTexture simg(str,font,bg,win);
        lx::Graphics::ShadedTextTexture simg2(font,win);
        lx::Log::log("SUCCESS - Image loaded");
        lx::Log::log("sizes: %u %u", simg.getTextSize(), simg2.getTextSize());
        lx::Log::log("Set the following text: %s; size: 32",str.utf8_str());
        simg.setPosition(100,100);
        lx::Log::log("Done");
        lx::Log::log("text: %s", simg.getText().utf8_str());
        win.clearWindow();
        lx::Log::log("Draw the text");
        simg.draw();
        lx::Log::log("Update");
        win.update();
        lx::Time::delay(1024);

        simg2.setTextColour({255,0,255,127});
        simg2.setPosition(100,400);
        simg2.setBgColour(bg2);
        simg2.setText(str);

        lx::Log::log("Size: 32 → 72");
        for(int j = 34; j < 74; j += 2)
        {
            simg.setTextSize(j);
            const std::pair< int, int> DIMENSION = simg.getTextDimension();
            lx::Log::log("Dimension: %d × %d", DIMENSION.first, DIMENSION.second);
            win.clearWindow();
            simg.draw();
            simg2.draw();
            win.update();
            lx::Time::delay(100);
        }
        lx::Log::log("Done");

        simg.setPosition(256,256);
        simg.setTextSize(32);

        lx::Log::log("Rotation");
        for(double j = 0.0; j < 3.14 * 2; j += 0.1)
        {
            win.clearWindow();
            simg.draw(j);
            win.update();
            lx::Time::delay(33);
        }
        lx::Log::log("Done");
    }
}


void test_BlendedText()
{
    lx::Graphics::Colour colour = {255,255,255,127};

    UTF8string str("がんばつて Gumichan01");
    lx::Win::WindowInfo winfo;
    lx::Win::initWindowInfo(winfo);
    winfo.title = "LunatiX - Test True Type Font - Blended text";
    winfo.w = 1000;
    lx::Win::Window win(winfo);
    Font font(fname,colour, 32);

    lx::Log::log("Load a blended text image and display it");

    {
        lx::Graphics::BlendedTextTexture simg(str,font,win);
        lx::Graphics::BlendedTextTexture simg2(font,win);
        lx::Log::log("SUCCESS - Image loaded");
        lx::Log::log("Set the following text: %s; size: 32",str.utf8_str());
        simg.setPosition(100,100);
        lx::Log::log("Done");
        lx::Log::log("text: %s", simg.getText().utf8_str());
        win.clearWindow();
        lx::Log::log("Draw the text");
        simg.draw();
        lx::Log::log("Update");
        win.update();
        lx::Time::delay(1024);

        simg2.setTextColour({255,0,255,127});
        simg2.setPosition(100,400);
        simg2.setText(str,48);

        lx::Log::log("Size: 32 → 72");
        for(int j = 34; j < 74; j += 2)
        {
            simg.setTextSize(j);
            const std::pair< int, int> DIMENSION = simg.getTextDimension();
            lx::Log::log("Dimension: %d × %d", DIMENSION.first, DIMENSION.second);
            win.clearWindow();
            simg.draw();
            simg2.draw();
            win.update();
            lx::Time::delay(100);
        }
        lx::Log::log("Done");

        simg.setPosition(256,256);
        simg.setTextSize(32);

        lx::Log::log("Rotation");
        for(double j = 0.0; j < 3.14 * 2; j += 0.1)
        {
            win.clearWindow();
            simg.draw(j);
            win.update();
            lx::Time::delay(33);
        }
        lx::Log::log("Done");
    }
}
