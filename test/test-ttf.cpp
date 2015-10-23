

#include <iostream>

#include <LunatiX/Lunatix_engine.hpp>

using namespace std;
using namespace LX_Graphics;
using namespace LX_TrueTypeFont;


void test_font(void);


int main(int argc, char **argv)
{
    cout << " ==== Test True Type Font ==== " << endl;

    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;

    test_font();

    cout << " ==== END Test ==== " << endl;

    return EXIT_SUCCESS;
}



void test_font(void)
{
    LX_Font *font = NULL;
    SDL_Surface *textS = NULL;
    SDL_Color color = {255,255,255};
    SDL_Color grey = {127,127,127};
    SDL_Rect pos = {100,100,32,12};

    LX_Window win("LunatiX Engine test TTF",LX_WINDOW_SURFACE);


    cout << "INFO - Load a LX_Font object with RAII" << endl;
    {
        LX_Font f1(LX_Configuration::getInstance()->getFontFile(),color);
    }
    cout << "SUCCESS - Loaded with success" << endl;

    cout << "INFO - Load another LX_Font object with RAII" << endl;
    {
        LX_Font f2(LX_Configuration::getInstance()->getFontFile(),color,48);
    }
    cout << "SUCCESS - Loaded with success" << endl;

    {
        try
        {
            LX_Font ferror("invalid_file",color);
            cout << "FAILURE - o_O. Expected: IOException, got: a valid object"
            << endl;

        }catch(IOException &e)
        {
            cout << "SUCCESS - IOException occured. It was expected" << endl;
        }
    }

    font = new LX_Font(color);

    if(font == NULL)
        cerr << "FAILURE - Font not null" << endl;
    else
        cout << "SUCCESS - Font defined" << endl;


    textS = font->drawSolidText("My name is Gumichan01");

    if(textS == NULL)
        cerr << "FAILURE - text not loaded" << endl;
    else
    {
        cout << "SUCCESS - Solid text OK" << endl;
        win.clear();
        win.putSurface(textS,NULL,&pos);
        win.update();
        SDL_Delay(1000);
        SDL_FreeSurface(textS);
    }


    textS = font->drawShadedText("My name is Gumichan01",0,255,0);

    if(textS == NULL)
        cerr << "FAILURE - text not loaded" << endl;
    else
    {
        cout << "SUCCESS - Shaded text OK" << endl;
        win.clear();
        win.putSurface(textS,NULL,&pos);
        win.update();
        SDL_Delay(1000);
        SDL_FreeSurface(textS);
    }


    textS = font->drawBlendedText("My name is Gumichan01");

    if(textS == NULL)
        cerr << "FAILURE - text not loaded" << endl;
    else
    {
        cout << "SUCCESS - Blended text OK" << endl;
        win.clear();
        win.putSurface(textS,NULL,&pos);
        win.update();
        SDL_Delay(1000);
        SDL_FreeSurface(textS);
    }

    delete font;
}
























