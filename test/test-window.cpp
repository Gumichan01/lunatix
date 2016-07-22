
#include <iostream>
#include <sstream>
#include <LunatiX/Lunatix_engine.hpp>
#include <LunatiX/LX_Image.hpp>

using namespace std;
using namespace LX_Graphics;


void test_window1(LX_Win::LX_Window *win);
void test_window2(void);
void test_surface(void);
void test_rendering(LX_Win::LX_Window *win);
void test_image(LX_Win::LX_Window *win);
void test_winManager(LX_Win::LX_Window *win);
void test_winInfo(LX_Win::LX_Window *win);

string winInfoToString(LX_Win::LX_WindowInfo &winfo);
bool winInfoEqual(LX_Win::LX_WindowInfo &info1, LX_Win::LX_WindowInfo &info2);

LX_Win::LX_WindowInfo info;

int main(int argc, char **argv)
{
    LX_Win::LX_Window *w = nullptr;

    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Window ==== ");
    LX_loadWindowConfig(info);
    LX_Log::log("Info configuration:\n%s",winInfoToString(info).c_str());
    info.title = "Hello #1";
    LX_Win::LX_Window *win = new LX_Win::LX_Window(info);
    w = win;

    /*test_winInfo(win);
    test_window1(w);
    test_window2();
    test_surface();
    test_rendering(w);*/
    test_image(w);
    //test_winManager(w);

    delete win;
    LX_Quit();

    LX_Log::log(" ==== END Window ==== ");
    return EXIT_SUCCESS;
}


void test_window1(LX_Win::LX_Window *win)
{
    cout << " = TEST main window = " << endl;

    if(win == nullptr)
        cerr << "FAILURE - The window was not initialized" << endl;
    else
        cout << "SUCCESS - The window exists" << endl;

    if(win != nullptr && win->getRenderer() == nullptr)
        cerr << "FAILURE - the renderer was not initialized" << endl;
    else
        cout << "SUCCESS - the renderer is ready" << endl;

    LX_Log::log(" = END TEST = ");
}


void test_window2(void)
{
    const int w = 256;
    const int h = 256;

    LX_Win::LX_WindowInfo wi;
    LX_Win::LX_initWindowInfo(wi);
    wi.title = "Hello #2";
    wi.x = 12;
    wi.y = 128;
    wi.w = w;
    wi.h = h;
    wi.mode = LX_WINDOW_RENDERING;
    wi.flag = SDL_WINDOW_SHOWN;
    LX_Win::LX_Window win2(wi);

    cout << " = TEST 2 window = " << endl;

    cout << "INFO - Is rendering mode used?" << endl;
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

    LX_Log::log(" = END TEST = ");
    SDL_Delay(750);
}


void test_surface(void)
{
    const int w = 512;
    const int h = 256;

    bool screen_ok;
    LX_Win::LX_WindowInfo wi;
    LX_Win::LX_initWindowInfo(wi);
    wi.title = "Hello #3";
    wi.x = 448;
    wi.y = 128;
    wi.w = w;
    wi.h = h;
    wi.mode = LX_WINDOW_SURFACE;
    wi.flag = SDL_WINDOW_SHOWN;
    LX_Win::LX_Window win3(wi);
    std::string name = "data/bullet.png";
    SDL_Surface *sf = nullptr;
    SDL_Rect pos = {256,256,256,128};

    cout << " = TEST 3 window with Surface = " << endl;

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
    cout << "INFO - load a surface." << endl;
    sf = loadSurface(name.c_str());

    if(sf == nullptr)
        cerr << "FAILURE - failed to load the surface " << LX_GetError() << endl;
    else
        cout << "SUCCESS - the surface was loaded with success" << endl;

    win3.clearWindow();

    // Is the surface put on the window
    cout << "INFO - put the surface on the screen" << endl;
    if(win3.putSurface(sf,nullptr,&pos) == false)
        cerr << "FAILURE - failed to put the surface " << LX_GetError() << endl;
    else
        cout << "SUCCESS - surface on the window" << endl;

    // Update the window
    SDL_Delay(1000);
    win3.update();

    // take a screenshot
    cout << "INFO - Screenshot" << endl;
    screen_ok = win3.screenshot("win-surface.png");

    if(screen_ok == false)
        cerr << "FAILURE - failed to take a screenshot of the surface "
             << LX_GetError() << endl;
    else
        cout << "SUCCESS - screenshot token from a surface" << endl;

    SDL_Delay(1000);
    win3.clearWindow();
    SDL_FreeSurface(sf);
    LX_Log::log(" = END TEST = ");
}


void test_rendering(LX_Win::LX_Window *win)
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
    LX_Log::log(" = END TEST = ");
}


void test_image(LX_Win::LX_Window *win)
{
    LX_Log::log(" = TEST LX_Image = ");

    std::string name = "data/bullet.png";
    std::string mname = "data/01.ogg";
    UTF8string u8name("data/bullet.png");

    LX_Log::log("|> LX_Static_Image");
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"open new image: %s",name.c_str());

    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"UTF8string argument");
        LX_Graphics::LX_Static_Image img(u8name,*win);

        if(img.isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - image loaded");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - image from file: should be loaded");
    }

    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"open a image file using the file buffer");
        LX_FileIO::LX_FileBuffer b(name);
        LX_Graphics::LX_Static_Image img(b,*win);

        if(img.isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - image loaded from memory");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - image from memory: should be loaded");
    }

    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"open a file that is not an image from memory");
        LX_FileIO::LX_FileBuffer b(mname);
        LX_Graphics::LX_Static_Image img(b,*win);

        if(!img.isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - failure expected");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - should not be loaded");
    }

    LX_Log::log("|> LX_Streaming_Image");
    LX_Log::log("||> LX_Surface");

    /// NORMAL CASE
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"create a surface");
    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"std::string argument");
        LX_Surface data(name,*win);

        if(data.isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Surface created");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Surface; it should be created");
    }

    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"UTF8string argument");
        LX_Surface data(u8name,*win);

        if(data.isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Surface created");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Surface; it should be created");
    }

    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"FileBuffer argument");
        LX_FileIO::LX_FileBuffer b(name);
        LX_Surface data(b,*win);

        if(data.isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Surface created");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Surface; it should be created");
    }

    /// ERROR CASE
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"invalid argument");
    {
        LX_Surface data("<invalid>",*win);

        if(data.isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Surface created. It must not");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - expected");
    }

    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"invalid argument");
    {
        LX_FileIO::LX_FileBuffer b(mname);
        LX_Surface data(b,*win);

        if(data.isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Surface created. It must not");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - expected");
    }

    // Display a bullet
    {
        LX_Graphics::LX_Static_Image img(name,*win);
        LX_AABB box = {64,64,256,128};

        if(img.isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - image loaded");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - image from file: should be loaded");

        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"LX_Static_Image example");
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"Draw the image (angle: 0 → 360)");
        for(int i = 0; i < 361; i++)
        {
            win->clearWindow();
            img.draw(&box,i);
            win->update();
            SDL_Delay(16);

            if(i == 0)
                LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"angle: 0 [2kπ]");
            if(i == 30)
                LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"angle: π/6 [2kπ]");
            else if(i == 45)
                LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"angle: π/4 [2kπ]");
            else if(i == 90)
                LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"angle: π/2 [2kπ]");
            else if(i == 180)
                LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"angle: π [2kπ]");
            else if(i == 270)
                LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"angle: 3π/2 [2kπ]");
            else if(i == 360)
                LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"angle: 2π [2kπ]");
        }

        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"Movement of the sprite");

        Uint32 t1 = SDL_GetTicks();
        for(int i = 0; i < 512; i++)
        {
            box.x += 1;
            win->clearWindow();
            img.draw(&box);
            win->update();
            SDL_Delay(16);
        }
        Uint32 t2 = SDL_GetTicks();
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"Done in %d ms",t2-t1);
    }

    LX_Log::log("||> Streaming");
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"create a streaming image");
    {
        LX_Streaming_Image img(*win);
        LX_Surface data(name,*win);
        LX_AABB box = {256,256,256,128};

        if(img.isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Streaming image created");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Streaming image; it should be created");

        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"put a surface in a streaming image");

        if(img.blit(data,box))
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - surface on the image");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - expected: TRUE; got: FALSE");

        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"update the stream");
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"LX_Streaming_Image example, with LX_Surface");

        Uint32 t1 = SDL_GetTicks();
        for(int i = 0; i < 512; i++)
        {
            box.x += 1;
            img.blit(data,box);
            img.update();
            win->clearWindow();
            img.draw();
            win->update();
            SDL_Delay(16);
        }
        Uint32 t2 = SDL_GetTicks();
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"Done in %d ms",t2-t1);
    }

    LX_Log::log(" = END TEST= ");
}


void test_winManager(LX_Win::LX_Window *win)
{
    std::string name = "data/bullet.png";

    SDL_Texture *st = nullptr;
    SDL_Rect pos = {100,100,256,128};
    cout << " = TEST WinManager = " << endl;

    if(win == nullptr)
        cerr << "FAILURE - The window was not initialized" << endl;
    else
        cout << "SUCCESS - The window exists" << endl;

    int id = LX_Win::LX_WindowManager::getInstance()->addWindow(win);

    if(id == -1)
        cerr << "FAILURE - failed to add a window" << LX_GetError() << endl;
    else
        cout << "SUCCESS - the window was added into the window manager" << endl;

    st = loadTextureFromFile(name.c_str(), static_cast<unsigned int>(id));

    if(st == nullptr)
        cerr << "FAILURE - failed to load the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - the texture was loaded with success" << endl;

    if(win != nullptr && win->putTexture(st,nullptr,&pos) == false)
        cerr << "FAILURE - failed to put the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - Texture on the renderer" << endl;

    LX_Win::LX_WindowManager::getInstance()->updateWindows();
    SDL_Delay(1000);
    LX_Win::LX_WindowManager::getInstance()->clearWindows();

    if(win != nullptr && win->putTextureAndRotate(st,nullptr,&pos,45) == false)
        cerr << "FAILURE - failed to put the texture " << LX_GetError() << endl;
    else
        cout << "SUCCESS - Texture on the renderer with rotation" << endl;

    LX_Win::LX_WindowManager::getInstance()->updateWindows();
    SDL_Delay(1000);
    LX_Win::LX_WindowManager::getInstance()->updateWindows();
    LX_Win::LX_WindowManager::getInstance()->removeWindow(id);
    LX_Log::log(" = END TEST = ");
}


void test_winInfo(LX_Win::LX_Window *win)
{
    cout << " = TEST window information = " << endl;
    LX_Win::LX_WindowInfo info_g;
    cout << "INFO - get information" << endl;
    win->getInfo(info_g);

    if(winInfoEqual(info,info_g))
        cout << "SUCCESS - Information retrieved and "
             << "information from user are identicals" << endl
             << winInfoToString(info_g) << endl;
    else
        cerr << "FAILURE - expected : " << winInfoToString(info)
             << "got : " << winInfoToString(info_g) << endl;

    LX_Log::log(" = END TEST = ");
}

string winInfoToString(LX_Win::LX_WindowInfo &winfo)
{
    ostringstream ss;
    ss << "(" << winfo.title << "," << winfo.x << "," << winfo.y
       << ",w: " << winfo.w << ",h: " << winfo.h
       << ",lw: " << winfo.w << ",lh: " << winfo.h
       << "," << winfo.mode << "," << winfo.flag
       << "," << (winfo.accel ? 1:0) << ")" << endl;

    return ss.str();
}

bool winInfoEqual(LX_Win::LX_WindowInfo &info1, LX_Win::LX_WindowInfo &info2)
{
    return (info1.title == info2.title)
            && (info1.x == info2.x) && (info1.y == info2.y)
            && (info1.w == info2.w) && (info1.h == info2.h)
            && (info1.lw == info2.lw) && (info1.lh == info2.lh)
            && (info1.mode == info2.mode) && (info1.flag == info2.flag)
            && (info1.accel == info2.accel);
}
