
#include <LunatiX/Lunatix.hpp>
#include <GL/glu.h>

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using namespace LX_Graphics;

void test_window1(LX_Win::LX_Window *win);
void test_window2(void);
void test_rendering(LX_Win::LX_Window *win);
void test_image(LX_Win::LX_Window *win);
void test_winManager(LX_Win::LX_Window *win);
void test_winInfo(LX_Win::LX_Window *win);
void test_opengl();
void test_opengl2();
void test_drawing(LX_Win::LX_Window *win);
void test_viewport(LX_Win::LX_Window *win);

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
        cout << "SUCCESS - The LunatiX library has been initialized with success" << endl;

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Window ==== ");
    LX_loadWindowConfig(info);
    info.w = 1000;
    info.h = 600;
    LX_Log::log("Info configuration:\n%s",winInfoToString(info).c_str());
    info.title = "Hello #1";
    LX_Win::LX_Window *win = new LX_Win::LX_Window(info);
    w = win;

    test_winInfo(win);
    test_opengl();
    test_opengl2();
    test_window1(w);
    test_window2();
    test_winManager(w);
    test_image(w);
    test_drawing(w);
    test_viewport(w);
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
    wi.flag = SDL_WINDOW_SHOWN;
    LX_Win::LX_Window win2(wi);

    cout << " = TEST 2 window = " << endl;

    if(win2.getWidth() != w)
        cerr << "FAILURE - width ; expected : " << w << "; got: " << win2.getWidth() << endl;
    else
        cout << "SUCCESS - width " << w << endl;

    if(win2.getHeight() != h)
        cerr << "FAILURE - height ; expected : " << h << "; got: " << win2.getHeight() << endl;
    else
        cout << "SUCCESS - height " << h << endl;

    LX_Log::log(" = END TEST = ");
    LX_Timer::delay(750);
}


void test_image(LX_Win::LX_Window *win)
{
    LX_Log::log(" = TEST LX_Texture = ");

    std::string name = "data/bullet.png";
    std::string mname = "data/01.ogg";
    UTF8string u8name("data/bullet.png");

    LX_Log::log("|> LX_Sprite");
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"open new image: %s",name.c_str());

    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"UTF8string argument");
        LX_Graphics::LX_Sprite img(u8name,*win);

        if(img.isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - image loaded");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - image from file: should be loaded");
    }

    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"open a image file using the file buffer");
        LX_FileIO::LX_FileBuffer b(name);
        LX_Graphics::LX_BufferedImage *bf =  b.loadBufferedImage();
        LX_Graphics::LX_Sprite *img = bf->generateSprite(*win);
        delete bf;

        if(img->isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - image loaded from memory");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - image from memory: should be loaded");

        delete img;
    }

    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"open a file that is not an image from memory");
        LX_Graphics::LX_Sprite *img = LX_Graphics::LX_BufferedImage(mname).generateSprite(*win);

        if(!img->isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - failure expected");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - should not be loaded");

        delete img;
    }

    LX_Log::log("|> LX_StreamingTexture");
    LX_Log::log("||> LX_BufferedImage");

    /// NORMAL CASE
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"create a surface");
    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"std::string argument");
        LX_BufferedImage data(name);

        if(data.isLoaded())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Surface created");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Surface; it should be created");
    }

    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"UTF8string argument");
        LX_BufferedImage data(u8name);

        if(data.isLoaded())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Surface created");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Surface; it should be created");
    }

    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"FileBuffer argument");
        LX_FileIO::LX_FileBuffer b(name);
        LX_BufferedImage *data = b.loadBufferedImage();

        if(data->isLoaded())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - Surface created");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Surface; it should be created");

        delete data;
    }

    /// ERROR CASE
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"invalid argument");
    {
        LX_BufferedImage data("<invalid>");

        if(data.isLoaded())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Surface created. It must not");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - expected");
    }

    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"invalid argument");
    {
        LX_BufferedImage data(mname);

        if(data.isLoaded())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - Surface created. It must not");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - expected");
    }

    // Display a bullet
    {
        LX_Graphics::LX_Sprite img(name,*win);
        LX_AABB box = {64,64,256,128};

        if(img.isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - image loaded");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - image from file: should be loaded");

        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"LX_Sprite example");
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"Draw the image (angle: 0 → 2π)");

        const double PI2 = M_PI * 2;

        for(double i = 0.00; i < PI2; i += 0.02)
        {
            win->clearWindow();
            img.draw(&box,i);
            win->update();
            LX_Timer::delay(16);
        }

        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"Movement of the sprite");

        Uint32 t1 = SDL_GetTicks();
        for(int i = 0; i < 512; i++)
        {
            box.x += 1;
            win->clearWindow();
            img.draw(&box);
            win->update();
            LX_Timer::delay(16);
        }
        Uint32 t2 = SDL_GetTicks();
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"Done in %d ms",t2-t1);
    }

    LX_Log::log("||> Streaming");
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"create a streaming image");
    {
        LX_StreamingTexture img(*win);
        LX_BufferedImage data(name);
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

        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"Update the stream");
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"LX_StreamingTexture example, with LX_BufferedImage");

        Uint32 t1 = SDL_GetTicks();
        for(int i = 0; i < 256; i++)
        {
            box.x += 1;
            img.blit(data,box);
            img.update();
            win->clearWindow();
            img.draw();
            win->update();
            LX_Timer::delay(16);
        }
        Uint32 t2 = SDL_GetTicks();
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"Done in %d ms",t2-t1);
    }

    LX_Log::log("|> LX_AnimatedSprite");
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"open new image: %s",name.c_str());
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"UTF8string argument");
    std::string sp_str = "data/boss.png";
    UTF8string u8_str(sp_str);
    std::vector<LX_AABB> c;

    {
        LX_Graphics::LX_AnimatedSprite img(u8_str,*win,c,0);

        if(img.isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - animated sprite loaded");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - animated sprite from file: should be loaded");
    }

    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"open a sprite sheet file using the bufered image");
        LX_Graphics::LX_AnimatedSprite *img = LX_BufferedImage(sp_str).generateAnimatedSprite(*win,c,0);

        if(img->isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - animated sprite loaded from memory");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - animated sprite from memory: should be loaded");

        delete img;
    }

    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"open a file that is not an image from memory");
        LX_Graphics::LX_AnimatedSprite *img = LX_BufferedImage(mname).generateAnimatedSprite(*win,c,0);

        if(!img->isOpen())
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - animated sprite failure expected");
        else
            LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - should not be loaded");

        delete img;
    }

    {
        LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"Animation");
        LX_AABB rect = {256, 64,211,448};
        Uint32 delay = 125;
        std::vector<LX_AABB> coordinates;
        coordinates.push_back({212,0,211,448});
        coordinates.push_back({424,0,211,448});
        coordinates.push_back({636,0,211,448});
        coordinates.push_back({0,449,211,448});
        coordinates.push_back({212,449,211,448});
        coordinates.push_back({424,449,211,448});
        coordinates.push_back({636,449,211,448});
        coordinates.push_back({848,0,211,448});
        coordinates.push_back({1060,0,211,448});
        coordinates.push_back({1272,0,211,448});
        coordinates.push_back({848,449,211,448});
        coordinates.push_back({1484,0,211,448});
        coordinates.push_back({1060,449,211,448});
        coordinates.push_back({1272,449,211,448});
        coordinates.push_back({1484,449,211,448});

        LX_Graphics::LX_AnimatedSprite sprite(sp_str,*win,coordinates,delay);

        for(int i = 0; i < 448; i++)
        {
            win->clearWindow();
            sprite.draw(&rect);
            win->update();
            LX_Timer::delay(16);
        }
        win->clearWindow();
    }

    LX_Log::log(" = END TEST= ");
}

void test_viewport(LX_Win::LX_Window *win)
{
    LX_Log::log(" = TEST Viewport = ");

    std::string sp_str = "data/boss.png";
    std::string name = "data/bullet.png";

    Uint32 delay = 125;
    LX_AABB rect = {0, 0,win->getWidth()/4,win->getHeight()/2};
    std::vector<LX_AABB> coordinates;
    coordinates.push_back({212,0,211,448});
    coordinates.push_back({424,0,211,448});
    coordinates.push_back({636,0,211,448});
    coordinates.push_back({0,449,211,448});
    coordinates.push_back({212,449,211,448});
    coordinates.push_back({424,449,211,448});
    coordinates.push_back({636,449,211,448});
    coordinates.push_back({848,0,211,448});
    coordinates.push_back({1060,0,211,448});
    coordinates.push_back({1272,0,211,448});
    coordinates.push_back({848,449,211,448});
    coordinates.push_back({1484,0,211,448});
    coordinates.push_back({1060,449,211,448});
    coordinates.push_back({1272,449,211,448});
    coordinates.push_back({1484,449,211,448});

    LX_Graphics::LX_Sprite img(name,*win);
    LX_Graphics::LX_AnimatedSprite sprite(sp_str,*win,coordinates,delay);

    LX_AABB viewport = {win->getWidth()/2, 0,win->getWidth()/2, win->getHeight()/2};
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"Viewport: {%d,%d,%d,%d}",
                    viewport.x,viewport.y,viewport.w,viewport.h);

    Uint32 b = SDL_GetTicks();
    LX_AABB brect = {0, 0, win->getWidth()/2, win->getHeight()/2};
    LX_Colour bcolor = {0,0,0,255};

    while(SDL_GetTicks() - b < 4096)
    {
        win->clearWindow();
        win->setViewPort(nullptr);
        img.draw();

        win->setViewPort(&viewport);
        win->setDrawColor(bcolor);
        win->fillRect(brect);
        sprite.draw(&rect);

        win->update();
        LX_Timer::delay(16);
    }
    win->clearWindow();
    LX_Log::log(" = END TEST= ");
}

void test_winManager(LX_Win::LX_Window *win)
{
    cout << " = TEST WinManager = " << endl;

    std::string name = "data/bullet.png";
    LX_Graphics::LX_Sprite img(name,*win);

    if(win == nullptr)
        cerr << "FAILURE - The window was not initialized" << endl;
    else
        cout << "SUCCESS - The window exists" << endl;

    uint32_t id = LX_Win::LX_WindowManager::getInstance()->addWindow(win);
    uint32_t wid = LX_Win::LX_WindowManager::getInstance()->addWindow(win);

    if(id == static_cast<uint32_t>(-1))
        cerr << "FAILURE - failed to add a window" << LX_GetError() << endl;
    else
        cout << "SUCCESS - the window was added into the window manager" << endl;

    if(wid == static_cast<uint32_t>(-1))
        cout << "SUCCESS - the window was not added into the window manager" << endl;
    else
        cerr << "FAILURE - the window has been added" << LX_GetError() << endl;


    LX_Win::LX_Window *lxw = LX_Win::LX_WindowManager::getInstance()->getWindow(id);

    if(lxw == win)
        cout << "SUCCESS - (getWindow) the window is exactly what we added" << endl;
    else
        cerr << "FAILURE - (getWindow) the window is not exactly what we added" << endl;

    LX_Win::LX_WindowManager::getInstance()->clearWindows();
    img.draw();
    LX_Win::LX_WindowManager::getInstance()->updateWindows();
    LX_Timer::delay(512);

    LX_Win::LX_Window *wi = LX_Win::LX_WindowManager::getInstance()->removeWindow(id);

    if(wi == win)
        cout << "SUCCESS - the removed window is exactly what we added" << endl;
    else
        cerr << "FAILURE - the removed window is not exactly what we added" << endl;

    cout << "INFO - remove the same window (again) " << endl;
    LX_Win::LX_Window *null = LX_Win::LX_WindowManager::getInstance()->removeWindow(id);

    if(null == nullptr)
        cout << "SUCCESS - nullptr: expected" << endl;
    else
        cerr << "FAILURE - expected : nullptr, got: a valid pointer" << endl;

    LX_Log::log(" = END TEST = ");
}


void test_winInfo(LX_Win::LX_Window *win)
{
    LX_Log::log(" = TEST window information = ");
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


void test_opengl()
{
    LX_Log::log(" = TEST OpenGL #1 = ");
    LX_Win::LX_WindowInfo winfo;
    LX_Win::LX_initWindowInfo(winfo);
    info.title = "OpenGL window #0";
    info.flag = SDL_WINDOW_OPENGL;

    {
        LX_Win::LX_Window w(info);

        {
            LX_Log::log("Get an OpengGL function: glClearColor");
            typedef void (APIENTRY * LX_Fun)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
            LX_Fun f = LX_Graphics::LX_OpenGL::getProcAddress<LX_Fun>("glClearColor");

            if(f == nullptr)
                LX_Log::log("This function is not available ×");
            else
                LX_Log::log("This function is available √");

            f(1.0, 0.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            w.update();
            LX_Timer::delay(1000);
        }

        // Red color
        LX_Log::log("Blue color");
        w.clearWindow();
        glClearColor(0.0, 0.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        w.update();
        LX_Timer::delay(2000);

        LX_Log::log("Move colors: blue → red");
        for(float i = 1.0f; i > -0.01f; i=i-0.01f)
        {
            w.clearWindow();
            glClearColor(1.0f - i, 0.0f, i, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            w.update();
            LX_Timer::delay(16);
        }

        LX_Log::log("Move colors: red → green");
        for(float i = 1.0f; i > -0.01f; i=i-0.01f)
        {
            w.clearWindow();
            glClearColor(i, 1.0f - i, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            w.update();
            LX_Timer::delay(16);
        }

        LX_Log::log("Move colors: green → black");
        for(float i = 1.0f; i > -0.01f; i=i-0.01f)
        {
            w.clearWindow();
            glClearColor(0.0, i, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            w.update();
            LX_Timer::delay(16);
        }

        LX_Log::log("Window size → Width × Height: %d × %d",w.getWidth(),w.getHeight());
        int width, height;
        w.glGetDrawableSize(width,height);
        LX_Log::log("Drawable size (OpenGL) → Width × Height: %d × %d",width,height);
    }

    LX_Log::log(" = END TEST = ");
}


void test_opengl2()
{
    LX_Log::log(" = TEST OpenGL #2 = ");

    LX_Win::LX_WindowInfo winfo1;
    LX_Win::LX_WindowInfo winfo2;
    LX_Win::LX_initWindowInfo(winfo1);
    LX_Win::LX_initWindowInfo(winfo2);

    // Window #1
    winfo1.title = "OpenGL window #1";
    winfo1.flag = SDL_WINDOW_OPENGL;
    winfo1.x = 128;
    winfo1.y = 128;
    winfo1.w = 256;
    winfo1.h = 256;

    // Window #2
    winfo2.title = "OpenGL window #2";
    winfo2.flag = SDL_WINDOW_OPENGL;
    winfo2.x = 512;
    winfo2.y = 128;
    winfo2.w = 256;
    winfo2.h = 256;

    {
        LX_Win::LX_Window w1(winfo1);
        LX_Win::LX_Window w2(winfo2);

        LX_Log::log("Define window #1 as the current OpenGL window");
        if(w1.glMakeCurrent())
            LX_Log::log("SUCCESS - OpenGl window #1 OK → current context defined");
        else
            LX_Log::log("FAILURE - %s",LX_GetError());

        LX_Log::log("Define window #2 as the current OpenGL window");
        if(w2.glMakeCurrent())
            LX_Log::log("SUCCESS - OpenGl window #2 OK → current context defined");
        else
            LX_Log::log("FAILURE - %s",LX_GetError());


        LX_Log::log("Blue color on window #1");
        w1.glMakeCurrent();                         // Work on the first window
        w1.clearWindow();
        glClearColor(0.0, 0.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        w1.update();
        LX_Timer::delay(1000);

        LX_Log::log("Red color on window #2");
        w2.glMakeCurrent();                         // Work on the second window
        w2.clearWindow();
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        w2.update();
        LX_Timer::delay(2000);

        {
            LX_Graphics::LX_Sprite img("data/bullet.png",w1);
            LX_Log::log("Bind the sprite to the first window → #1");
            float w, h;
            bool b = img.bind(&w,&h);

            if(b)
                LX_Log::log("OK");
            else
                LX_Log::log("KO: %s",LX_GetError());


            LX_Log::log("Green color on window #2");
            w2.glMakeCurrent();                         // Work on the first window
            w2.clearWindow();
            glClearColor(0.0, 1.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            w2.update();
            LX_Timer::delay(1000);

            LX_Log::log("Undind the first window → #1");
            b = img.unbind();

            if(b)
                LX_Log::log("OK");
            else
                LX_Log::log("KO: %s",LX_GetError());
        }

    }

    LX_Log::log(" = END TEST = ");
}

void test_drawing(LX_Win::LX_Window *win)
{
    LX_Log::log(" = TEST draw = ");
    LX_Log::log("Draw a segment with M(32,32) and N(64,448)");
    LX_Physics::LX_Point M(32,32);
    LX_Physics::LX_Point N(64,448);
    LX_Physics::LX_Point O(512,256);
    LX_Physics::LX_Vector2D u(256.0f,128.0f);
    LX_Physics::LX_Vector2D v(2048.0f,0.0f);
    LX_AABB b = {128,128,512,100};

    win->clearWindow();
    win->drawSegment(M,N);
    win->update();
    LX_Timer::delay(1000);

    LX_Log::log("Draw a line with N(64,448) and u⃗(256.0,128.0)");
    win->clearWindow();
    win->drawLine(N,u);
    win->update();
    LX_Timer::delay(1000);

    LX_Colour c = {255,0,0,255};
    win->setDrawColor(c);
    LX_Log::log("Draw multiple lines (1024) with O(512,256) and v⃗(2048.0,0.0) in red");
    LX_Log::log("From v⃗(2048.0,0.0) to v⃗(2048.0,512.0), step : 64");
    win->clearWindow();
    for(float j = 0.0f; j < 256; j++)
    {
        win->drawLine(O,v);
        v.vy += j + 64;
        win->update();
        LX_Timer::delay(16);
    }

    LX_Timer::delay(2048);
    LX_Log::log("Draw multiple lines using several points");
    LX_Physics::LX_Point points[8] = {{64,64},{128,32},{256,64},{768,512},
        {512,256},{16,448},{32,512},{256,42}
    };

    c = {255,255,255,255};
    win->setDrawColor(c);
    win->clearWindow();
    win->drawSegments(points,8);
    win->update();
    LX_Timer::delay(2048);

    LX_Log::log("Draw a rectangle using a bounding box");
    win->clearWindow();
    win->drawRect(b);
    win->update();
    LX_Timer::delay(1000);

    LX_Log::log("Fill a rectangle using a bounding box");
    win->clearWindow();
    win->fillRect(b);
    win->update();
    LX_Timer::delay(1000);

    LX_Log::log("Draw a rectangle using a point and a vector : N and u⃗");
    win->clearWindow();
    win->drawRect(N,u);
    win->update();
    LX_Timer::delay(1000);
    win->clearWindow();

    LX_Log::log("Fill a rectangle using a point and a vector : N and u⃗");
    win->clearWindow();
    win->fillRect(N,u);
    win->update();
    LX_Timer::delay(1000);
    win->clearWindow();

    LX_Log::log("Draw circles");
    for(unsigned int i = 0; i < 300; i++)
    {
        LX_Physics::LX_Circle C = LX_Physics::LX_Circle(LX_Physics::LX_Point(512,300),i);
        win->clearWindow();
        win->drawCircle(C);
        win->update();
        LX_Timer::delay(16);
    }

    LX_Log::log("Draw filled circles");
    for(int j = 0; j < 300; j++)
    {
        LX_Physics::LX_Circle C = LX_Physics::LX_Circle(LX_Physics::LX_Point(512,300),j);
        win->clearWindow();
        win->fillCircle(C);
        win->update();
        LX_Timer::delay(16);
    }

    LX_Log::log(" = END TEST = ");
}


string winInfoToString(LX_Win::LX_WindowInfo &winfo)
{
    ostringstream ss;
    ss << "(" << winfo.title << "," << winfo.x << "," << winfo.y
       << ",w: " << winfo.w << ",h: " << winfo.h
       << ",lw: " << winfo.w << ",lh: " << winfo.h
       << winfo.flag << "," << (winfo.accel ? 1:0) << ")" << endl;

    return ss.str();
}

bool winInfoEqual(LX_Win::LX_WindowInfo &info1, LX_Win::LX_WindowInfo &info2)
{
    return (info1.id == info2.id)
           && (info1.title == info2.title)
           && (info1.x == info2.x) && (info1.y == info2.y)
           && (info1.w == info2.w) && (info1.h == info2.h)
           && (info1.lw == info2.lw) && (info1.lh == info2.lh)
           && (info1.flag == info2.flag) && (info1.accel == info2.accel);
}
