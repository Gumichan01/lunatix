


#include <iostream>

#include "../src/engine/Lunatix_engine.hpp"

using namespace std;
using namespace LX_Graphics;


void test_window1(LX_Window *win);
void test_window2(void);
void test_surface(void);
void test_rendering(LX_Window *win);
void test_winManager(LX_Window *win);



int main(int argc, char **argv)
{

    cout << " ==== Test Rendering ==== " << endl;
    LX_Window *w = NULL;

    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;


    LX_Window *win = new LX_Window("Test window",LX_WINDOW_RENDERING);
    w = win;

    test_window1(w);
    test_window2();
    test_surface();
    test_rendering(w);
    test_winManager(w);

    LX_Quit();

    cout << " ==== END Rendering ==== " << endl;

    return EXIT_SUCCESS;
}


void test_window1(LX_Window *win)
{

    cout << " = TEST main window = " << endl;

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


    cout << " = END TEST = " << endl;
}


void test_window2(void)
{
    LX_Window win2("Hello",512,128,64,32,LX_WINDOW_RENDERING,SDL_WINDOW_SHOWN);

    cout << " = TEST 2 window = " << endl;

    if(win2.getWindow() == NULL)
        cerr << "FAILURE - the window was not initialized" << endl;
    else
        cout << "SUCCESS - the window is ready" << endl;

    if(win2.getRenderer() == NULL)
        cerr << "FAILURE - the renderer was not initialized" << endl;
    else
        cout << "SUCCESS - the renderer is ready" << endl;


    if(win2.getWidth() != 64)
        cerr << "FAILURE - width ; expected : 64; got: " << win2.getWidth() << endl;
    else
        cout << "SUCCESS - width 64" << endl;


    if(win2.getHeight() != 32)
        cerr << "FAILURE - height ; expected : 32; got: " << win2.getHeight() << endl;
    else
        cout << "SUCCESS - height 32" << endl;

    cout << " = END TEST = " << endl;

}


void test_surface(void)
{
    LX_Window win3("Hello",512,128,256,256,LX_WINDOW_SURFACE,SDL_WINDOW_SHOWN);
    std::string name = "data/cb.bmp";
    SDL_Surface *sf = NULL;
    SDL_Rect pos = {100,100,150,120};

    cout << " = TEST 3 window with Surface = " << endl;

    if(win3.getWindow() == NULL)
        cerr << "FAILURE - the window was not initialized" << endl;
    else
        cout << "SUCCESS - the window is ready" << endl;

    if(win3.getSurface() == NULL)
        cerr << "FAILURE - the surface was not initialized" << endl;
    else
        cout << "SUCCESS - the surface is ready" << endl;


    if(win3.getWidth() != 256)
        cerr << "FAILURE - width ; expected : 64; got: " << win3.getWidth() << endl;
    else
        cout << "SUCCESS - width 64" << endl;


    if(win3.getHeight() != 256)
        cerr << "FAILURE - height ; expected : 32; got: " << win3.getHeight() << endl;
    else
        cout << "SUCCESS - height 32" << endl;

    sf = loadSurface(name.c_str());

    if(sf == NULL)
        cerr << "FAILURE - failed to load the surface " << LX_GetError() << endl;
    else
        cout << "SUCCESS - the surface was loaded with success" << endl;


    if(win3.putSurface(sf,NULL,&pos) == false)
        cerr << "FAILURE - failed to put the surface " << LX_GetError() << endl;
    else
        cout << "SUCCESS - surface on the window" << endl;

    win3.updateWindow();
    SDL_Delay(1000);
    win3.clearWindow();

    cout << " = END TEST = " << endl;
}


void test_rendering(LX_Window *win)
{

    std::string name = "data/cb.bmp";

    SDL_Texture *st = NULL;
    SDL_Rect pos = {100,100,150,120};


    cout << " = TEST Rendering = " << endl;

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

    SDL_Delay(1000);

    win->clearRenderer();


    if(win->putTextureAndRotate(st,NULL,&pos,45) == false)
        cerr << "FAILURE - failed to put the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - Texture on the renderer with rotation" << endl;

    win->updateRenderer();

    SDL_Delay(1000);

    win->clearRenderer();

    cout << " = END TEST = " << endl;
}


void test_winManager(LX_Window *win)
{
    std::string name = "data/cb.bmp";

    SDL_Texture *st = NULL;
    SDL_Rect pos = {100,100,150,120};

    unsigned int id = 0;

    cout << " = TEST WinManager = " << endl;

    if(win == NULL)
    {
        cerr << "FAILURE - The window was not initialized" << endl;
        return;
    }
    else
        cout << "SUCCESS - The window exists" << endl;


    id = LX_WindowManager::getInstance()->addWindow(win);

    if(id == -1)
        cerr << "FAILURE - failed to add a window" << LX_GetError() << endl;
    else
        cout << "SUCCESS - the window was added into the window manager" << endl;

    st = loadTextureFromFile(name.c_str(), id);

    if(st == NULL)
        cerr << "FAILURE - failed to load the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - the texture was loaded with success" << endl;


    if(win->putTexture(st,NULL,&pos) == false)
        cerr << "FAILURE - failed to put the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - Texture on the renderer" << endl;


    win->updateRenderer();

    SDL_Delay(1000);

    win->clearRenderer();


    if(win->putTextureAndRotate(st,NULL,&pos,45) == false)
        cerr << "FAILURE - failed to put the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - Texture on the renderer with rotation" << endl;

    win->updateRenderer();

    SDL_Delay(1000);

    win->clearRenderer();

    LX_WindowManager::getInstance()->deleteWindow(id);

    cout << " = END TEST = " << endl;
}

























