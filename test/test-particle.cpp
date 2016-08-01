
#include <iostream>
#include <LunatiX/Lunatix_engine.hpp>

using namespace std;

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
};

class Dot
{
    LX_ParticleSystem *sys;
    LX_AABB box;

    Dot(Dot& d);

public:

    Dot()
    {
        LX_Particle *p = nullptr;
        LX_Random::initRand();
        LX_AABB hitbox;

        sys = new LX_ParticleSystem(N);
        box = {100,100,20,20};

        for(int i = 0; i < N; i++)
        {
            hitbox = {box.x - 5 + (rand()%25), box.y - 5 + (rand()%25),5,5};

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
        LX_AABB hitbox;

        sys->updateParticles();
        moveRect(box,10,0);

        for(int i = 0; i < N; i++)
        {
            hitbox = {box.x - 5 + (rand()%25), box.y - 5 + (rand()%25),5,5};

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
    LX_Win::LX_Window *w = nullptr;
    Uint32 begin_time;

    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success"
             << endl;

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Particle ==== \n");

    LX_Win::LX_WindowInfo winfo;
    LX_Win::LX_loadWindowConfig(winfo);
    winfo.title = "Test particle";
    winfo.mode = LX_WINDOW_RENDERING;

    w = new LX_Win::LX_Window(winfo);
    LX_Win::LX_WindowManager::getInstance()->addWindow(w);

    red = new LX_Sprite("test/asset/red.bmp",*w);
    green = new LX_Sprite("test/asset/green.bmp",*w);
    blue = new LX_Sprite("test/asset/blue.bmp",*w);

    if(red->isOpen() && green->isOpen() && blue->isOpen())
        LX_Log::log("SUCCESS - The three assets were successfully loaded");
    else
        LX_Log::log("FAILURE - (At least) One of the three assets was not loaded");

    LX_Log::log("Loading the dot");
    dot = new Dot();
    LX_Log::log("Dot loaded");

    SDL_Event e;
    int go = 1;
    begin_time = SDL_GetTicks();

    LX_Log::log("The programm is running ...");

    while(go == 1 &&  ((SDL_GetTicks() - begin_time) < 4000))
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                go = 0;
        }

        LX_Win::LX_WindowManager::getInstance()->clearWindows();
        dot->update();
        LX_Win::LX_WindowManager::getInstance()->updateWindows();
        SDL_Delay(16);
    }

    LX_Win::LX_WindowManager::getInstance()->removeWindow(0);
    LX_Log::log("End of program");

    delete dot;
    delete blue;
    delete green;
    delete red;
    delete w;
    LX_Quit();

    LX_Log::log(" ==== END Particle ==== \n");
    return EXIT_SUCCESS;
}
