
#include <iostream>
#include <LunatiX/Lunatix_engine.hpp>

using namespace std;
using namespace LX_TrueTypeFont;
using namespace LX_FileIO;


void test_font(void);
void test_font2(void);


int main(int argc, char **argv)
{
    cout << endl << " ==== Test True Type Font ==== " << endl;

    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;

    LX_Log::setDebugMode();
    test_font();
    test_font2();

    cout << " ==== END Test ==== " << endl << endl;

    return EXIT_SUCCESS;
}



void test_font(void)
{
    LX_Font *font = nullptr;
    SDL_Surface *textS = nullptr;
    SDL_Color color = {255,255,255};
    SDL_Color grey = {127,127,127};
    SDL_Rect pos = {100,100,32,12};

    string str = "My name is Gumichan01";

    LX_Win::LX_Window win("LunatiX Engine test TTF No 1",LX_WINDOW_SURFACE);


    cout << "INFO - Load an LX_Font object with RAII" << endl;
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

        }
        catch(IOException &e)
        {
            cout << "SUCCESS - IOException occured. It was expected" << endl;
        }
    }

    font = new LX_Font(color);

    if(font == nullptr)
        cerr << "FAILURE - Font not null" << endl;
    else
        cout << "SUCCESS - Font defined" << endl;


    textS = font->drawSolidText(str);

    if(textS == nullptr)
        cerr << "FAILURE - Text not loaded - " << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - Solid text with default size OK" << endl;
        win.clearWindow();
        win.putSurface(textS,nullptr,&pos);
        win.update();
        SDL_Delay(1000);
        SDL_FreeSurface(textS);
    }


    textS = font->drawShadedText(str,0,127,255);

    if(textS == nullptr)
        cerr << "FAILURE - Text not loaded - " << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - Shaded text with default size OK" << endl;
        win.clearWindow();
        win.putSurface(textS,nullptr,&pos);
        win.update();
        SDL_Delay(1000);
        SDL_FreeSurface(textS);
    }


    textS = font->drawBlendedText(str);

    if(textS == nullptr)
        cerr << "FAILURE - text not loaded" << endl;
    else
    {
        cout << "SUCCESS - Blended text with default size OK" << endl;
        win.clearWindow();
        win.putSurface(textS,nullptr,&pos);
        win.update();
        SDL_Delay(1000);
        SDL_FreeSurface(textS);
    }

    delete font;
}



void test_font2(void)
{
    LX_Font *font = nullptr;
    SDL_Texture *textS = nullptr;

    string str = "My name is Gumichan01";
    SDL_Color color = {255,255,255};
    SDL_Color grey = {127,127,127};
    SDL_Rect pos = {100,100,0,0};
    SDL_Rect pos2 = {100,100,0,0};
    int size_for_test = 48;
    int w,h;

    LX_Win::LX_Window win("LunatiX Engine test TTF No 2",LX_WINDOW_RENDERING);

    font = new LX_Font(color,size_for_test);

    if(font == nullptr)
        cerr << "FAILURE - Font not null" << endl;
    else
        cout << "SUCCESS - Font defined" << endl;


    // In rendering mode, it is necessary to get the dimension of the text
    // according to the size of it
    font->sizeOfText(str,size_for_test,w,h);
    pos2 = {pos.x,pos.y,w,h};
    textS = LX_Graphics::loadTextureFromSurface(font->drawSolidText(str),&win);

    if(textS == nullptr)
        cerr << "FAILURE - Text not loaded - " << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - Solid text with size "
             << size_for_test << " OK" << endl;
        win.clearWindow();
        win.putTexture(textS,nullptr,&pos2);
        win.update();
        SDL_Delay(1000);
        SDL_DestroyTexture(textS);
    }

    font->sizeOfText(str,size_for_test,w,h);
    pos2 = {pos.x,pos.y,w,h};
    textS = LX_Graphics::loadTextureFromSurface(font->drawShadedText(str,0,127,255),&win);

    if(textS == nullptr)
        cerr << "FAILURE - Text not loaded - " << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - Shaded text with size "
             << size_for_test << " OK" << endl;
        win.clearWindow();
        win.putTexture(textS,nullptr,&pos2);
        win.update();
        SDL_Delay(1000);
        SDL_DestroyTexture(textS);
    }

    font->sizeOfText(str,size_for_test,w,h);
    pos2 = {pos.x,pos.y,w,h};
    textS = LX_Graphics::loadTextureFromSurface(font->drawBlendedText(str),&win);

    if(textS == nullptr)
        cerr << "FAILURE - Text not loaded - " << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - Blended text with size "
             << size_for_test << " OK" << endl;
        win.clearWindow();
        win.putTexture(textS,nullptr,&pos2);
        win.update();
        SDL_Delay(1000);
        SDL_DestroyTexture(textS);
    }


    font->sizeOfText(str,(size_for_test/4),w,h);
    pos2 = {pos.x,pos.y,w,h};
    textS = LX_Graphics::loadTextureFromSurface(font->drawBlendedText(str,
            (size_for_test/4)),&win);

    if(textS == nullptr)
        cerr << "FAILURE - Text not loaded - " << LX_GetError() << endl;
    else
    {
        cout << "SUCCESS - Blended text with size "
             << (size_for_test/4) << " OK" << endl;
        win.clearWindow();
        win.putTexture(textS,nullptr,&pos2);
        win.update();
        SDL_Delay(1000);
    }

    SDL_DestroyTexture(textS);
    textS = nullptr;

    cout << "INFO - error cases" << endl;


    SDL_Surface *s = font->drawSolidText(str,0);

    if(s != nullptr)
        cerr << "FAILURE - Expected: nullptr, got : a valid pointer " << endl;
    else
        cout << "SUCCESS - The solid text was not loaded - " << LX_GetError() << endl;

    SDL_FreeSurface(s);


    s = font->drawShadedText(str,0,0,0,0);

    if(s != nullptr)
        cerr << "FAILURE - Expected: nullptr, got : a valid pointer " << endl;
    else
        cout << "SUCCESS - The shaded text was not loaded - " << LX_GetError() << endl;

    SDL_FreeSurface(s);


    s = font->drawBlendedText(str,0);

    if(s != nullptr)
        cerr << "FAILURE - Expected: nullptr, got : a valid pointer " << endl;
    else
        cout << "SUCCESS - The blended text was not loaded - " << LX_GetError() << endl;

    SDL_FreeSurface(s);


    delete font;
}
