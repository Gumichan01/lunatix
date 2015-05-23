

#include <iostream>

#include "../src/engine/Lunatix_engine.hpp"

using namespace std;
using namespace LX_Graphics;
using namespace LX_TrueTypeFont;


void test_font(void);


int main(int argc, char **argv)
{
    cout << " ==== Test Rendering ==== " << endl;

    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;

    test_font();

    cout << " ==== END Test ==== " << endl;
}



void test_font(void)
{
    LX_Font *font = NULL;
    SDL_Surface *textS = NULL;
    SDL_Color color = {255,255,255};
    SDL_Color grey = {127,127,127};
    SDL_Rect pos = {100,100,32,12};

    LX_Window win("LunatiX Engine test TTF",LX_WINDOW_SURFACE);


    font = new LX_Font(&color);

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
        win.clearWindow();
        win.putSurface(textS,NULL,&pos);
        win.updateWindow();
        SDL_Delay(1000);
        SDL_FreeSurface(textS);
    }


    textS = font->drawShadedText("My name is Gumichan01",127,127,127);

    if(textS == NULL)
        cerr << "FAILURE - text not loaded" << endl;
    else
    {
        cout << "SUCCESS - Shaded text OK" << endl;
        win.clearWindow();
        win.putSurface(textS,NULL,&pos);
        win.updateWindow();
        SDL_Delay(1000);
        SDL_FreeSurface(textS);
    }


    textS = font->drawBlendedText("My name is Gumichan01");

    if(textS == NULL)
        cerr << "FAILURE - text not loaded" << endl;
    else
    {
        cout << "SUCCESS - Blended text OK" << endl;
        win.clearWindow();
        win.putSurface(textS,NULL,&pos);
        win.updateWindow();
        SDL_Delay(1000);
        SDL_FreeSurface(textS);
    }

    delete font;
}
























