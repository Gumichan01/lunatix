
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

static LX_FileBuffer *red;
static LX_FileBuffer *green;
static LX_FileBuffer *blue;

class Dot
{
    LX_ParticleSystem *sys;
    LX_AABB box;

    Dot(Dot& d);

public:

    Dot()
    {
        bool err;
        LX_Particle *p = nullptr;
        LX_Random::initRand();

        sys = new LX_ParticleSystem(N);
        box = {100,100,20,20};

        for(int i = 0; i < N; i++)
        {
            p = new LX_Particle(box.x - 5 + (rand()%25),
                                box.y - 5 + (rand()%25),5,5);

            switch(rand()%3)
            {
            case 0 :
                err = p->setTexture(red);
                break;

            case 1 :
                err = p->setTexture(blue);
                break;

            case 2 :
                err = p->setTexture(green);
                break;

            default :
                err = p->setTexture(red);
                break;
            }

            sys->addParticle(p);

            if(err == false)
                cerr << "FAILURE - Dot - Cannot load any texture "
                     << "from a file buffer" << endl;
        }
    }

    void update()
    {
        bool err;
        LX_Particle *p = nullptr;

        sys->updateParticles();
        moveRect(box,10,0);

        for(int i = 0; i < N; i++)
        {
            p = new LX_Particle(box.x - 5 + (rand()%25),
                                box.y - 5 + (rand()%25),5,5);

            switch(rand()%3)
            {
            case 0 :
                err = p->setTexture(red);
                break;

            case 1 :
                err = p->setTexture(blue);
                break;

            case 2 :
                err = p->setTexture(green);
                break;

            default :
                err = p->setTexture(red);
                break;
            }

            if(sys->addParticle(p) == false)
            {
                delete p;
            }

            if(err == false)
                cerr << "FAILURE - Dot::update() - Cannot load any texture "
                     << "from a file buffer" << endl;
        }

        sys->displayParticles();
    }

    ~Dot()
    {
        delete sys;
    }
};


int main()
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
    w = new LX_Win::LX_Window("Test particle",LX_WINDOW_RENDERING);
    LX_Win::LX_WindowManager::getInstance()->addWindow(w);

    //File buffer of particle
    try
    {
        red = new LX_FileBuffer("test/asset/red.bmp");
        green = new LX_FileBuffer("test/asset/green.bmp");
        blue = new LX_FileBuffer("test/asset/blue.bmp");

    }
    catch(IOException)
    {
        cerr << "FAILURE - An asset was not loaded" << endl;
        cout << " ==== Abort Particle ==== " << endl;
        return EXIT_FAILURE;
    }

    cout << "SUCCESS - The three assets were successfully loaded "
         << "in each file buffer" << endl;
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
