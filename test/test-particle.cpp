
#include <iostream>
#include <LunatiX/Lunatix.hpp>

using namespace std;
using namespace LX_Event;

using namespace LX_Graphics;
using namespace LX_TrueTypeFont;
using namespace LX_Device;
using namespace LX_Mixer;
using namespace LX_Physics;
using namespace LX_ParticleEngine;
using namespace LX_FileIO;

#define N 20

namespace
{
LX_Sprite *red;
LX_Sprite *green;
LX_Sprite *blue;
}

class Dot
{
    LX_ParticleSystem *sys;
    LX_FloatingBox box;

    Dot(Dot& d);

public:

    Dot()
    {
        LX_Particle *p = nullptr;
        LX_Random::initRand();

        sys = new LX_ParticleSystem(N);
        box = LX_FloatingBox{LX_FloatPosition{100.0f, 100.0f}, 20, 20};

        for(int i = 0; i < N; i++)
        {
            LX_FloatingBox hitbox{LX_FloatPosition{box.fpoint.x - fbox(5.0f) + fbox(rand()%25),
                                                   box.fpoint.y - fbox(5.0f) + fbox(rand()%25)}, 5, 5};

            switch(rand()%3)
            {
            case 0 :
                p = new LX_Particle(*red, hitbox);
                break;

            case 1 :
                p = new LX_Particle(*blue, hitbox);
                break;

            case 2 :
                p = new LX_Particle(*green, hitbox);
                break;

            default :
                p = new LX_Particle(*red, hitbox);
                break;
            }

            sys->addParticle(p);
        }
    }

    void update()
    {
        LX_Particle *p = nullptr;
        sys->updateParticles();
        moveBox(box, LX_Vector2D{10.0f, 0.0f});

        for(int i = 0; i < N; i++)
        {
            LX_FloatingBox hitbox{LX_FloatPosition{box.fpoint.x - fbox(5.0f) + fbox(rand()%25),
                                                   box.fpoint.y - fbox(5.0f) + fbox(rand()%25)}, 5, 5};

            switch(rand()%3)
            {
            case 0 :
                p = new LX_Particle(*red, hitbox);
                break;

            case 1 :
                p = new LX_Particle(*blue, hitbox);
                break;

            case 2 :
                p = new LX_Particle(*green, hitbox);
                break;

            default :
                p = new LX_Particle(*red, hitbox);
                break;
            }

            if(sys->addParticle(p) == false)
            {
                delete p;
            }
        }

        sys->displayParticles();
    }

    ~Dot()
    {
        delete sys;
    }
};


int main(int argc, char **argv)
{
    Dot *dot;
    Uint32 begin_time;

    bool err = LX_Init();

    if(!err)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - LX_Init() failed");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The LunatiX library has been initialized with success");

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Particle ==== \n");

    LX_Win::LX_WindowInfo winfo;
    LX_Win::LX_loadWindowConfig(winfo);
    winfo.title = "Test particle";

    LX_Win::LX_Window w(winfo);
    LX_Win::getWindowManager().addWindow(w);

    try
    {
        red = new LX_Sprite("test/asset/red.bmp", w);
        green = new LX_Sprite("test/asset/green.bmp", w);
        blue = new LX_Sprite("test/asset/blue.bmp", w);
        LX_Log::log("SUCCESS - The three assets were successfully loaded");
    }
    catch(LX_Graphics::LX_ImageException& ie)
    {
        LX_Log::log("FAILURE - (At least) One of the three assets was not loaded");
        LX_Log::log("%s", ie.what());
    }

    LX_Log::log("Loading the dot");
    dot = new Dot();
    LX_Log::log("Dot loaded");

    LX_EventHandler e;
    int go = 1;
    begin_time = SDL_GetTicks();

    LX_Log::log("The programm is running ...");

    while(go == 1 &&  ((SDL_GetTicks() - begin_time) < 4000))
    {
        while(e.pollEvent())
        {
            if(e.getEventType() == LX_EventType::QUIT)
                go = 0;
        }

        LX_Win::getWindowManager().clearWindows();
        dot->update();
        LX_Win::getWindowManager().updateWindows();
        LX_Timer::delay(16);
    }

    LX_Win::getWindowManager().removeWindow(0);
    LX_Log::log("End of program");

    delete dot;
    delete blue;
    delete green;
    delete red;
    LX_Quit();

    LX_Log::log(" ==== END Particle ==== \n");
    return EXIT_SUCCESS;
}
