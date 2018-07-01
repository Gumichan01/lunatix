
#include <Lunatix/Lunatix.hpp>
#include <GL/gl.h>

#include <sstream>
#include <vector>

using namespace std;
using namespace lx::Graphics;

void test_window1(lx::Win::Window *win);
void test_window2(void);
void test_rendering(lx::Win::Window *win);
void test_image(lx::Win::Window *win);
void test_winManager(lx::Win::Window *win);
void test_winInfo(lx::Win::Window *win);
void test_opengl();
void test_opengl2();
void test_drawing(lx::Win::Window *win);
void test_viewport(lx::Win::Window *win);

string winInfoToString(lx::Win::WindowInfo &winfo);
bool winInfoEqual(lx::Win::WindowInfo &info1, lx::Win::WindowInfo &info2);

lx::Win::WindowInfo info;

int main(int argc, char **argv)
{
    lx::Win::Window *w = nullptr;

    bool err = lx::init();

    if(!err)
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - lx::init() failed");
    else
        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - The LunatiX library has been initialized with success");

    lx::Log::setDebugMode();
    lx::Log::log(" ==== Test Window ==== ");
    loadWindowConfig(info);
    info.w = 1000;
    info.h = 600;
    lx::Log::log("Info configuration:\n%s",winInfoToString(info).c_str());
    info.title = "Hello #1";
    lx::Win::Window *win = new lx::Win::Window(info);
    lx::Log::log( "Window: %s", win->getTitle().c_str() );
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

    lx::quit();
    lx::Log::log(" ==== END Window ==== ");
    return EXIT_SUCCESS;
}


void test_window1(lx::Win::Window *win)
{
    lx::Log::log(" = TEST main window = ");

    if(win == nullptr)
        lx::Log::log("FAILURE - The window was not initialized");
    else
        lx::Log::log("SUCCESS - The window exists");

    lx::Log::log(" = END TEST = ");
}


void test_window2(void)
{
    const int w = 256;
    const int h = 256;

    lx::Win::WindowInfo wi;
    lx::Win::initWindowInfo(wi);
    wi.title = "Hello #2";
    wi.x = 12;
    wi.y = 128;
    wi.w = w;
    wi.h = h;
    wi.flag = SDL_WINDOW_SHOWN;
    lx::Win::Window win2(wi);
    lx::Log::log( "Window: %s", win2.getTitle().c_str() );

    lx::Log::log(" = TEST 2 window = ");

    if(win2.getWidth() != w)
        lx::Log::log("FAILURE - width; expected: %d; got: %d",w,win2.getWidth());
    else
        lx::Log::log("SUCCESS - width: %d",w);

    if(win2.getHeight() != h)
        lx::Log::log("FAILURE - height; expected: %d; got: %d",h,win2.getHeight());
    else
        lx::Log::log("SUCCESS - width: %d",h);

    lx::Log::log(" = END TEST = ");
    lx::Time::delay(750);
}


void test_image(lx::Win::Window *win)
{
    lx::Log::log(" = TEST Texture = ");
    std::string sp_str = "data/boss.png";
    std::string name = "data/bullet.png";
    std::string mname = "data/01.ogg";
    UTF8string u8name("data/bullet.png");

    lx::Log::log("|> Sprite");
    lx::Log::logInfo(lx::Log::APPLICATION,"open new image: %s",name.c_str());

    try
    {
        lx::Log::logInfo(lx::Log::APPLICATION,"UTF8string argument");
        lx::Graphics::Sprite img(u8name,*win);
        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - image loaded");
    }
    catch(lx::Graphics::ImageException& ie)
    {
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - image from file: should be loaded");
        lx::Log::log("%s", ie.what());
    }

    try
    {
        lx::Log::logInfo(lx::Log::APPLICATION,"open a image file using the file buffer");
        lx::FileIO::FileBuffer b(name);
        lx::Graphics::BufferedImage *bf =  b.loadBufferedImage();
        lx::Graphics::Sprite *img = bf->generateSprite(*win);
        delete bf;

        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - image loaded from memory");

        delete img;
    }
    catch(lx::Graphics::ImageException& ie)
    {
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - image from memory: should be loaded");
        lx::Log::log("%s", ie.what());
    }

    try
    {
        lx::Log::logInfo(lx::Log::APPLICATION,"open a file that is not an image from memory");
        lx::Graphics::Sprite *img = lx::Graphics::BufferedImage(mname).generateSprite(*win);

        lx::Log::logInfo(lx::Log::TEST,"FAILURE - should not be loaded");
        delete img;
    }
    catch(lx::Graphics::ImageException& ie)
    {
        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - failure expected");
        lx::Log::log("%s", ie.what());
    }

    lx::Log::log("|> StreamingTexture");
    lx::Log::log("||> BufferedImage");

    /// NORMAL CASE
    lx::Log::logInfo(lx::Log::APPLICATION,"create a surface");
    try
    {
        lx::Log::logInfo(lx::Log::APPLICATION,"std::string argument");
        BufferedImage data(name);

        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - Surface created");
    }
    catch(lx::Graphics::ImageException& ie)
    {
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - Surface; it should be created");
        lx::Log::log("%s", ie.what());
    }

    try
    {
        lx::Log::logInfo(lx::Log::APPLICATION,"UTF8string argument");
        BufferedImage data(u8name);

        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - Surface created");
    }
    catch(lx::Graphics::ImageException& ie)
    {
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - Surface; it should be created");
        lx::Log::log("%s", ie.what());
    }

    try
    {
        lx::Log::logInfo(lx::Log::APPLICATION,"FileBuffer argument");
        lx::FileIO::FileBuffer b(name);
        BufferedImage *data = b.loadBufferedImage();

        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - Surface created");
        delete data;
    }
    catch(lx::Graphics::ImageException& ie)
    {
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - Surface; it should be created");
        lx::Log::log("%s", ie.what());
    }

    /// ERROR CASE
    lx::Log::logInfo(lx::Log::APPLICATION,"invalid argument");

    try
    {
        BufferedImage data(std::string("<invalid>"));
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - Surface created. It must not");
    }
    catch(lx::Graphics::ImageException& ie)
    {
        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - expected");
        lx::Log::log("%s", ie.what());
    }

    lx::Log::logInfo(lx::Log::APPLICATION,"invalid argument");

    try
    {
        BufferedImage data(mname);
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - Surface created. It must not");
    }
    catch(lx::Graphics::ImageException& ie)
    {
        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - expected");
        lx::Log::log("%s", ie.what());
    }

    // Display a bullet
    try
    {
        lx::Graphics::Sprite img(name,*win);
        ImgRect box{64,64,256,128};

        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - image loaded");
        lx::Log::logInfo(lx::Log::APPLICATION,"Sprite example");
        lx::Log::logInfo(lx::Log::APPLICATION,"Draw the image (angle: 0 → 2π)");

        const double PI2 = M_PI * 2;

        for(double i = 0.00; i < PI2; i += 0.02)
        {
            win->clearWindow();
            img.draw(box, i);
            win->update();
            lx::Time::delay(16);
        }

        lx::Log::logInfo(lx::Log::APPLICATION,"Movement of the sprite");

        Uint32 t1 = SDL_GetTicks();
        for(int i = 0; i < 512; i++)
        {
            box.p.x += 1;
            win->clearWindow();
            img.draw(box);
            win->update();
            lx::Time::delay(16);
        }
        Uint32 t2 = SDL_GetTicks();
        lx::Log::logInfo(lx::Log::APPLICATION,"Done in %d ms",t2-t1);
    }
    catch(lx::Graphics::ImageException& ie)
    {
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - image from file: should be loaded");
        lx::Log::log("%s", ie.what());
    }

    lx::Log::log("||> Streaming");
    lx::Log::logInfo(lx::Log::APPLICATION,"create a streaming image");

    try
    {
        StreamingTexture img(*win);
        BufferedImage data(name);
        ImgRect box{256,256,256,128};

        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - Streaming image created");
        lx::Log::logInfo(lx::Log::APPLICATION,"put a surface in a streaming image");

        if(img.blit(data,box))
            lx::Log::logInfo(lx::Log::TEST,"SUCCESS - surface on the image");
        else
            lx::Log::logInfo(lx::Log::TEST,"FAILURE - expected: TRUE; got: FALSE");

        lx::Log::logInfo(lx::Log::APPLICATION,"Update the stream");
        lx::Log::logInfo(lx::Log::APPLICATION,"StreamingTexture example, with BufferedImage");

        Uint32 t1 = SDL_GetTicks();
        for(int i = 0; i < 64; i++)
        {
            box.p.x += 4;
            img.blit(data,box);
            img.update();
            win->clearWindow();
            img.draw();
            win->update();
            lx::Time::delay(16);
        }
        Uint32 t2 = SDL_GetTicks();
        lx::Log::logInfo(lx::Log::APPLICATION,"Done in %d ms",t2-t1);
    }
    catch(lx::Graphics::ImageException& ie)
    {
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - Streaming image; it should be created");
        lx::Log::log("%s", ie.what());
    }

    lx::Log::log("|> AnimatedSprite");
    lx::Log::logInfo(lx::Log::APPLICATION,"open new image: %s",name.c_str());
    lx::Log::logInfo(lx::Log::APPLICATION,"UTF8string argument");
    UTF8string u8_str(sp_str);
    std::vector<ImgRect> c;

    try
    {
        lx::Graphics::AnimatedSprite img(u8_str,*win,c,0,false);
        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - animated sprite loaded");
    }
    catch(lx::Graphics::ImageException& ie)
    {
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - animated sprite from file: should be loaded");
        lx::Log::log("%s", ie.what());
    }

    try
    {
        lx::Log::logInfo(lx::Log::APPLICATION,"open a sprite sheet file using the bufered image");
        lx::Graphics::AnimatedSprite *img = BufferedImage(sp_str).generateAnimatedSprite(*win,c,0, false);

        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - animated sprite loaded from memory");
        delete img;
    }
    catch(lx::Graphics::ImageException& ie)
    {
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - animated sprite from memory: should be loaded");
        lx::Log::log("%s", ie.what());
    }

    try
    {
        lx::Log::logInfo(lx::Log::APPLICATION,"open a file that is not an image from memory");
        lx::Graphics::AnimatedSprite *img = BufferedImage(mname).generateAnimatedSprite(*win,c,0,false);

        lx::Log::logInfo(lx::Log::TEST,"FAILURE - should not be loaded");
        delete img;
    }
    catch(lx::Graphics::ImageException& ie)
    {
        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - animated sprite failure expected");
        lx::Log::log("%s", ie.what());
    }

    {
        lx::Log::logInfo(lx::Log::APPLICATION,"Animation");
        Uint32 delay = 125;
        std::vector<ImgRect> coordinates;
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

        {
            // Infinite animation
            ImgRect rect{256,64,211,448};
            lx::Graphics::AnimatedSprite sprite(sp_str,*win,coordinates,delay, true);
            lx::Log::logInfo(lx::Log::TEST,"animated sprite — infinitely looped: %s",
                            sprite.isInfinitelyLooped() ? "Yes" : "No");
            lx::Log::log("frame delay: %u ms", sprite.getFrameDelay());

            for(int i = 0; i < 512; i++)
            {
                win->clearWindow();
                sprite.draw(rect);
                win->update();
                lx::Time::delay(16);
            }
            win->clearWindow();
        }

        lx::Log::log("Not infinite animation");

        {
            // Animation
            ImgRect rect{420,100,211,448};
            lx::Graphics::AnimatedSprite sprite(sp_str,*win,coordinates,delay, false);
            lx::Log::logInfo(lx::Log::TEST,"animated sprite — infinitely looped: %s",
                            sprite.isInfinitelyLooped() ? "Yes" : "No");
            lx::Log::log("frame delay: %u ms", sprite.getFrameDelay());

            uint32_t t = lx::Time::getTicks();
            for(int j = 0; j <= 1; j++)
            {
                while((lx::Time::getTicks() - t) < 2000)
                {
                    win->clearWindow();
                    sprite.draw(rect);
                    win->update();
                    lx::Time::delay(16);
                }

                win->clearWindow();
                sprite.resetAnimation();
                lx::Log::log("Reset animation");
                t = lx::Time::getTicks();
                lx::Time::delay(500);
            }
        }
    }

    lx::Log::log(" = END TEST= ");
}

void test_viewport(lx::Win::Window *win)
{
    lx::Log::log(" = TEST Viewport = ");

    std::string sp_str = "data/boss.png";
    std::string name = "data/bullet.png";

    Uint32 delay = 125;
    ImgRect rect{0, 0,win->getWidth()/4,win->getHeight()/2};
    std::vector<ImgRect> coordinates;
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

    lx::Graphics::Sprite img(name, *win);
    lx::Graphics::AnimatedSprite sprite(sp_str,*win,coordinates,delay,true);

    ImgRect viewport{{win->getWidth()/2, 0}, win->getWidth()/2, win->getHeight()/2};
    lx::Log::logInfo(lx::Log::APPLICATION,"Viewport: {%d,%d,%d,%d}",
                    viewport.p.x, viewport.p.y, viewport.w, viewport.h);

    Uint32 b = SDL_GetTicks();
    ImgRect brect{0, 0, win->getWidth()/2, win->getHeight()/2};
    lx::Graphics::Colour bcolour{0, 0, 0, 255};

    while(SDL_GetTicks() - b < 4096)
    {
        win->clearWindow();
        win->resetViewPort();
        img.draw();

        win->setViewPort(viewport);
        win->setDrawColour(bcolour);
        win->fillRect(brect);
        sprite.draw(rect);

        win->update();
        lx::Time::delay(16);
    }
    win->clearWindow();
    lx::Log::log(" = END TEST= ");
}

void test_winManager(lx::Win::Window *win)
{
    lx::Log::log(" = TEST WinManager = ");
    std::string name = "data/bullet.png";
    lx::Graphics::Sprite img(name,*win);

    if(win == nullptr)
        lx::Log::log("FAILURE - The window was not initialized");
    else
        lx::Log::log("SUCCESS - The window exists");

    bool r = lx::Win::getWindowManager().addWindow(*win);

    if(r == false)
        lx::Log::log("FAILURE - cannot add a window: %s", lx::getError());
    else
        lx::Log::log("SUCCESS - the window was added into the window manager");


    lx::Win::Window& lxw = lx::Win::getWindowManager().getWindow(win->getID());

    if(&lxw == win)
        lx::Log::log("SUCCESS - (getWindow) the window is exactly what we added");
    else
        lx::Log::log("FAILURE - (getWindow) the window is not exactly what we added");

    lx::Win::getWindowManager().clearWindows();
    img.draw();
    lx::Win::getWindowManager().updateWindows();
    lx::Time::delay(512);

    lx::Log::log("Remove the same window");
    bool r2 = lx::Win::getWindowManager().removeWindow(win->getID());

    if(r2)
        lx::Log::log("SUCCESS - The removed window is exactly what we added");
    else
        lx::Log::log("FAILURE - The removed window is not exactly what we added");

    lx::Log::log("Remove the same window (again)");
    bool r3 = lx::Win::getWindowManager().removeWindow(win->getID());

    if(!r3)
        lx::Log::log("SUCCESS - false expected");
    else
        lx::Log::log("FAILURE - The window must not be in the manager");

    lx::Log::log(" = END TEST = ");
}


void test_winInfo(lx::Win::Window *win)
{
    lx::Log::log(" = TEST window information = ");
    lx::Win::WindowInfo info_g;
    lx::Log::log("Get information");
    win->getInfo(info_g);

    if(winInfoEqual(info,info_g))
        lx::Log::log("SUCCESS - The information provided by user are correct: %s",
                    winInfoToString(info_g).c_str());
    else
        lx::Log::log("FAILURE - expected: %s; Got: %s",
                    winInfoToString(info_g).c_str(), winInfoToString(info_g).c_str());

    lx::Log::log(" = END TEST = ");
}


void test_opengl()
{
    lx::Log::log(" = TEST OpenGL #1 = ");
    lx::Win::WindowInfo winfo;
    lx::Win::initWindowInfo(winfo);
    info.title = "OpenGL window #0";
    info.flag = SDL_WINDOW_OPENGL;

    {
        lx::Win::Window w(info);
        lx::Log::log( "Window: %s", w.getTitle().c_str() );

        {
            lx::Log::log("Get an OpengGL function: glClearColor");
            typedef void (APIENTRY * Fun)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
            Fun f = lx::Graphics::OpenGL::getProcAddress<Fun>("glClearColor");

            if(f == nullptr)
                lx::Log::log("This function is not available ×");
            else
                lx::Log::log("This function is available √");

            f(1.0, 0.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            w.update();
            lx::Time::delay(1000);
        }

        // Red colour
        lx::Log::log("Blue colour");
        w.clearWindow();
        glClearColor(0.0, 0.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        w.update();
        lx::Time::delay(2000);

        lx::Log::log("Move colours: blue → red");
        for(float i = 1.0f; i > -0.01f; i=i-0.01f)
        {
            w.clearWindow();
            glClearColor(1.0f - i, 0.0f, i, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            w.update();
            lx::Time::delay(16);
        }

        lx::Log::log("Move colours: red → green");
        for(float i = 1.0f; i > -0.01f; i=i-0.01f)
        {
            w.clearWindow();
            glClearColor(i, 1.0f - i, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            w.update();
            lx::Time::delay(16);
        }

        lx::Log::log("Move colours: green → black");
        for(float i = 1.0f; i > -0.01f; i=i-0.01f)
        {
            w.clearWindow();
            glClearColor(0.0, i, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            w.update();
            lx::Time::delay(16);
        }

        lx::Log::log("Window size → Width × Height: %d × %d",w.getWidth(),w.getHeight());
        int width, height;
        w.glGetDrawableSize(width,height);
        lx::Log::log("Drawable size (OpenGL) → Width × Height: %d × %d",width,height);
    }

    lx::Log::log(" = END TEST = ");
}


void test_opengl2()
{
    lx::Log::log(" = TEST OpenGL #2 = ");

    lx::Win::WindowInfo winfo1;
    lx::Win::WindowInfo winfo2;
    lx::Win::initWindowInfo(winfo1);
    lx::Win::initWindowInfo(winfo2);

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
        lx::Win::Window w1(winfo1);
        lx::Win::Window w2(winfo2);
        lx::Log::log( "Window: %s", w1.getTitle().c_str() );
        lx::Log::log( "Window: %s", w2.getTitle().c_str() );

        lx::Log::log("Define window #1 as the current OpenGL window");
        if(w1.glMakeCurrent())
            lx::Log::log("SUCCESS - OpenGl window #1 OK → current context defined");
        else
            lx::Log::log("FAILURE - %s",lx::getError());

        lx::Log::log("Define window #2 as the current OpenGL window");
        if(w2.glMakeCurrent())
            lx::Log::log("SUCCESS - OpenGl window #2 OK → current context defined");
        else
            lx::Log::log("FAILURE - %s",lx::getError());


        lx::Log::log("Blue colour on window #1");
        w1.glMakeCurrent();                         // Work on the first window
        w1.clearWindow();
        glClearColor(0.0, 0.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        w1.update();
        lx::Time::delay(1000);

        lx::Log::log("Red colour on window #2");
        w2.glMakeCurrent();                         // Work on the second window
        w2.clearWindow();
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        w2.update();
        lx::Time::delay(2000);
    }

    lx::Log::log(" = END TEST = ");
}

void test_drawing(lx::Win::Window *win)
{
    lx::Log::log(" = TEST draw = ");
    lx::Log::log("Draw a segment with M(32,32) and N(64,448)");
    ImgCoord M{32,32};
    ImgCoord N{64,448};
    ImgCoord NO{N.x + 256, N.y + 128};
    ImgCoord O{512,256};
    ImgCoord OO{O.x + 2048, O.y + 0};
    ImgRect b{128,128,512,100};
    lx::Graphics::Colour c = {255,0,0,255};

    win->setDrawColour(c);
    win->clearWindow();
    win->drawLine(M, N);
    win->update();
    lx::Time::delay(1000);

    lx::Log::log("Draw a line with two points");
    win->clearWindow();
    win->drawLine(N, NO);
    win->update();
    lx::Time::delay(1000);

    lx::Log::log("Draw multiple lines (1024) with O(512,256) and v⃗(2048.0,0.0) in red");
    lx::Log::log("From v⃗(2048.0,0.0) to v⃗(2048.0,512.0), step : 64");
    win->clearWindow();
    const Float fend{256.0f};

    for(Float j{0.0f}; j < fend; ++j)
    {
        win->drawLine(O, OO);
        OO.y += j + 64;
        win->update();
        lx::Time::delay(16);
    }

    lx::Time::delay(2048);
    lx::Log::log("Draw multiple lines using several points");
    std::vector<ImgCoord> points = {{64,64},{128,32},{256,64},{768,512},
        {512,256},{16,448},{32,512},{256,42}
    };

    c = {255,255,255,255};
    win->setDrawColour(c);
    win->clearWindow();
    win->drawLines(points);
    win->update();
    lx::Time::delay(2048);

    lx::Log::log("Draw a rectangle using a bounding box");
    win->clearWindow();
    win->drawRect(b);
    win->update();
    lx::Time::delay(1000);

    lx::Log::log("Fill a rectangle using a bounding box");
    win->clearWindow();
    win->fillRect(b);
    win->update();
    lx::Time::delay(1000);

    lx::Physics::Circle C{lx::Physics::FloatPosition{512.0f,300.0f},0};

    lx::Log::log("Draw circles");
    for(unsigned int i = 0; i < 300; i++)
    {
        C.radius = i;
        win->clearWindow();
        win->drawCircle(C);
        win->update();
        lx::Time::delay(16);
    }

    lx::Log::log("Draw filled circles");
    for(unsigned int j = 0; j < 300; j++)
    {
        C.radius = j;
        win->clearWindow();
        win->fillCircle(C);
        win->update();
        lx::Time::delay(16);
    }

    lx::Log::log(" = END TEST = ");
}


string winInfoToString(lx::Win::WindowInfo &winfo)
{
    ostringstream ss;
    ss << "(" << winfo.title << "," << winfo.x << "," << winfo.y
       << ",w: " << winfo.w << ",h: " << winfo.h
       << ",lw: " << winfo.w << ",lh: " << winfo.h
       << winfo.flag << "," << (winfo.accel ? 1:0) << ")";

    return ss.str();
}

bool winInfoEqual(lx::Win::WindowInfo &info1, lx::Win::WindowInfo &info2)
{
    return (info1.id == info2.id)
           && (info1.title == info2.title)
           && (info1.x == info2.x) && (info1.y == info2.y)
           && (info1.w == info2.w) && (info1.h == info2.h)
           && (info1.lw == info2.lw) && (info1.lh == info2.lh)
           && (info1.flag == info2.flag) && (info1.accel == info2.accel);
}
