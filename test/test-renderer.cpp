


#include <iostream>

#include "../src/engine/Lunatix_engine.hpp"

using namespace std;
using namespace LX_Graphics;


void test_window1(LX_Window *win);
void test_window2(void);
void test_window3(void);
void test_rendering(LX_Window *win);



int main(int argc, char **argv)
{

    cout << " ==== Test Rendering ==== " << endl;
    LX_Window *w = NULL;

    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;


    LX_Window win("Test window");
    w = &win;

    test_window1(w);
    test_window2();
    test_rendering(w);

    cout << " ==== END Rendering ==== " << endl;
}


void test_window1(LX_Window *win)
{

    cout << " = TEST main window = " << endl;

    SDL_Delay(100);

    if(win == NULL)
    {
        cerr << "FAILURE - The window was not initialized" << endl;
        return;
    }
    else
        cout << "SUCCESS - The window exists" << endl;


    if(win->getWindow() == NULL)
        cerr << "FAILURE - the window was not initialized" << endl;
    else
        cout << "SUCCESS - the window is ready" << endl;

    if(win->getRenderer() == NULL)
        cerr << "FAILURE - the renderer was not initialized" << endl;
    else
        cout << "SUCCESS - the renderer is ready" << endl;


    if(win->getSurface() == NULL)
        cerr << "FAILURE - the surface was not initialized" << endl;
    else
        cout << "SUCCESS - the surface is ready" << endl;

    cout << " = END TEST = " << endl;

    SDL_Delay(100);
}


void test_window2(void)
{
    LX_Window win2("Hello",512,128,64,32,SDL_WINDOW_SHOWN);

    cout << " = TEST 2 window = " << endl;

    SDL_Delay(100);

    if(win2.getWindow() == NULL)
        cerr << "FAILURE - the window was not initialized" << endl;
    else
        cout << "SUCCESS - the window is ready" << endl;

    if(win2.getRenderer() == NULL)
        cerr << "FAILURE - the renderer was not initialized" << endl;
    else
        cout << "SUCCESS - the renderer is ready" << endl;


    if(win2.getSurface() == NULL)
        cerr << "FAILURE - the surface was not initialized" << endl;
    else
        cout << "SUCCESS - the surface is ready" << endl;


    if(win2.getWidth() != 64)
        cerr << "FAILURE - width ; expected : 64; got: " << win2.getWidth() << endl;
    else
        cout << "SUCCESS - width 64" << endl;


    if(win2.getHeight() != 32)
        cerr << "FAILURE - height ; expected : 32; got: " << win2.getHeight() << endl;
    else
        cout << "SUCCESS - height 32" << endl;

    cout << " = END TEST = " << endl;

    SDL_Delay(100);

}


void test_window3(void)
{

}


void test_rendering(LX_Window *win)
{

    std::string name = "data/cb.bmp";

    SDL_Texture *st = NULL;
    SDL_Rect pos = {100,100,150,120};

    if(win == NULL)
    {
        cerr << "FAILURE - The window was not initialized" << endl;
        return;
    }
    else
        cout << "SUCCESS - The window exists" << endl;

    st = SDL_CreateTextureFromSurface(win->getRenderer(),loadSurface(name.c_str()));

    if(st == NULL)
        cerr << "FAILURE - failed to load the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - the texture was loaded with success" << endl;


    if(win->putTexture(st,NULL,&pos) == false)
        cerr << "FAILURE - failed to put the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - Texture on the renderer" << endl;


    win->updateRenderer();

    SDL_Delay(2000);

    win->clearRenderer();

    /// @todo test with rotation

}








