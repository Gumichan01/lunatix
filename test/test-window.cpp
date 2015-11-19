


#include <iostream>

#include <LunatiX/Lunatix_engine.hpp>

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
    LX_Window *w = nullptr;

    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;


    LX_Window *win = new LX_Window("Hello #1",LX_WINDOW_RENDERING);
    w = win;

    test_window1(w);
    test_window2();
    test_surface();
    test_rendering(w);
    test_winManager(w);

    delete win;
    LX_Quit();

    cout << " ==== END Rendering ==== " << endl;

    return EXIT_SUCCESS;
}


void test_window1(LX_Window *win)
{

    cout << " = TEST main window = " << endl;

    if(win == nullptr)
    {
        cerr << "FAILURE - The window was not initialized" << endl;
        return;
    }
    else
        cout << "SUCCESS - The window exists" << endl;


    if(win->getWindow() == nullptr)
        cerr << "FAILURE - the window was not initialized" << endl;
    else
        cout << "SUCCESS - the window is ready" << endl;

    if(win->getRenderer() == nullptr)
        cerr << "FAILURE - the renderer was not initialized" << endl;
    else
        cout << "SUCCESS - the renderer is ready" << endl;

    cout << " = END TEST = " << endl;
}


void test_window2(void)
{
    const int w = 256;
    const int h = 256;

    LX_Window win2("Hello #2",12,128,w,h,LX_WINDOW_RENDERING,SDL_WINDOW_SHOWN);

    cout << " = TEST 2 window = " << endl;

    if(win2.getWindow() == nullptr)
        cerr << "FAILURE - the window was not initialized" << endl;
    else
        cout << "SUCCESS - the window is ready" << endl;

    if(win2.getRenderer() == nullptr)
        cerr << "FAILURE - the renderer was not initialized" << endl;
    else
        cout << "SUCCESS - the renderer is ready" << endl;


    if(win2.getWidth() != w)
        cerr << "FAILURE - width ; expected : " << w << "; got: " << win2.getWidth() << endl;
    else
        cout << "SUCCESS - width " << w << endl;


    if(win2.getHeight() != h)
        cerr << "FAILURE - height ; expected : " << h << "; got: " << win2.getHeight() << endl;
    else
        cout << "SUCCESS - height " << h << endl;

    cout << " = END TEST = " << endl;

    SDL_Delay(750);
}


void test_surface(void)
{
    const int w = 512;
    const int h = 256;

    bool screen_ok;
    LX_Window win3("Hello #3",448,128,w,h,LX_WINDOW_SURFACE,SDL_WINDOW_SHOWN);
    std::string name = "data/bullet.png";
    SDL_Surface *sf = nullptr;
    SDL_Rect pos = {100,100,200,100};

    cout << " = TEST 3 window with Surface = " << endl;

    if(win3.getWindow() == nullptr)
        cerr << "FAILURE - the window was not initialized" << endl;
    else
        cout << "SUCCESS - the window is ready" << endl;

    /*
    *   Is the surface mode initialized?
    *   If LX_WINDOW_SURFACE was made,
    *   then getSurface must return a valid surface
    */
    if(win3.getSurface() == nullptr)
        cerr << "FAILURE - the surface was not initialized" << endl;
    else
        cout << "SUCCESS - the surface is ready" << endl;


    if(win3.getWidth() != w)
        cerr << "FAILURE - width ; expected : " << w
        << "; got: " << win3.getWidth() << endl;
    else
        cout << "SUCCESS - width " << w << endl;


    if(win3.getHeight() != h)
        cerr << "FAILURE - height ; expected : " << h
        << "; got: " << win3.getHeight() << endl;
    else
        cout << "SUCCESS - height " << h << endl;

    // Load the surface and test its validity
    sf = loadSurface(name.c_str());

    if(sf == nullptr)
        cerr << "FAILURE - failed to load the surface " << LX_GetError() << endl;
    else
        cout << "SUCCESS - the surface was loaded with success" << endl;

    // Is the surface put on the window
    if(win3.putSurface(sf,nullptr,&pos) == false)
        cerr << "FAILURE - failed to put the surface " << LX_GetError() << endl;
    else
        cout << "SUCCESS - surface on the window" << endl;

    // Update the window
    win3.update();

    // take a screenshot
    screen_ok = win3.screenshot("win-surface.png");

    if(screen_ok == false)
        cerr << "FAILURE - failed to take a screenshot of the surface "
        << LX_GetError() << endl;
    else
        cout << "SUCCESS - screenshot token from a surface" << endl;


    SDL_Delay(1000);
    win3.clearWindow();
    SDL_FreeSurface(sf);

    cout << " = END TEST = " << endl;
}


void test_rendering(LX_Window *win)
{
    bool screen_ok;
    std::string name = "data/bullet.png";

    SDL_Surface *sf = nullptr;
    SDL_Texture *st = nullptr;
    SDL_Rect pos = {100,100,256,128};


    cout << " = TEST Rendering = " << endl;

    if(win == nullptr)
    {
        cerr << "FAILURE - The window was not initialized" << endl;
        return;
    }
    else
        cout << "SUCCESS - The window exists" << endl;

    if(win->getRenderer() == nullptr)
        cerr << "FAILURE - the renderer was not initialized" << endl;
    else
        cout << "SUCCESS - the renderer is ready" << endl;


    sf = loadSurface(name.c_str());
    st = SDL_CreateTextureFromSurface(win->getRenderer(),sf);
    SDL_FreeSurface(sf);

    if(st == nullptr)
        cerr << "FAILURE - failed to load the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - the texture was loaded with success" << endl;


    if(win->putTexture(st,nullptr,&pos) == false)
        cerr << "FAILURE - failed to put the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - Texture on the renderer" << endl;


    win->update();
    SDL_Delay(750);
    win->clearWindow();


    if(win->putTextureAndRotate(st,nullptr,&pos,45) == false)
        cerr << "FAILURE - failed to put the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - Texture on the renderer with rotation" << endl;

    win->update();

    // Take a screenshot
    screen_ok = win->screenshot("win-renderer.png");

    if(screen_ok == false)
        cerr << "FAILURE - failed to take a screenshot of the renderer"
        << LX_GetError() << endl;
    else
        cout << "SUCCESS - screenshot token from the renderer" << endl;

    SDL_Delay(500);
    win->clearWindow();

    SDL_DestroyTexture(st);

    cout << " = END TEST = " << endl;
}


void test_winManager(LX_Window *win)
{
    std::string name = "data/bullet.png";

    SDL_Texture *st = nullptr;
    SDL_Rect pos = {100,100,256,128};

    int id = 0;

    cout << " = TEST WinManager = " << endl;

    if(win == nullptr)
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

    if(st == nullptr)
        cerr << "FAILURE - failed to load the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - the texture was loaded with success" << endl;


    if(win->putTexture(st,nullptr,&pos) == false)
        cerr << "FAILURE - failed to put the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - Texture on the renderer" << endl;


    LX_WindowManager::getInstance()->updateWindows();

    SDL_Delay(1000);

    LX_WindowManager::getInstance()->clearWindows();


    if(win->putTextureAndRotate(st,nullptr,&pos,45) == false)
        cerr << "FAILURE - failed to put the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - Texture on the renderer with rotation" << endl;

    LX_WindowManager::getInstance()->updateWindows();

    SDL_Delay(1000);

    LX_WindowManager::getInstance()->updateWindows();

    LX_WindowManager::getInstance()->removeWindow(id);

    cout << " = END TEST = " << endl;
}

























