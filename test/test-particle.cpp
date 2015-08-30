

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include "../src/engine/Lunatix_engine.hpp"

//#define DEBUG_MAIN_TEST

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

class Dot{

    LX_ParticleSystem *sys;
    LX_AABB box;

    public:

    Dot()
    {
        LX_Particle *p = NULL;
        srand(time(NULL));

        sys = new LX_ParticleSystem(N);
        box = {100,100,20,20};

        for(int i = 0; i < N; i++)
        {
            p = new LX_Particle(box.x - 5 + (rand()%25),box.y - 5 + (rand()%25),5,5);

            switch(rand()%3)
            {
                case 0 :    p->setTexture(red,0);
                            break;

                case 1 :    p->setTexture(blue,0);
                            break;

                case 2 :    p->setTexture(green,0);
                            break;

                default :   p->setTexture(red,0);
                            break;
            }

            sys->addParticle(p);
        }
    }

    void update()
    {
        LX_Particle *p = NULL;

        sys->updateParticles();
        moveRect(&box,10,0);

        for(int i = 0; i < N; i++)
        {
            p = new LX_Particle(box.x - 5 + (rand()%25),box.y - 5 + (rand()%25),5,5);

            switch(rand()%3)
            {
                case 0 :    p->setTexture(red,0);
                            break;

                case 1 :    p->setTexture(blue,0);
                            break;

                case 2 :    p->setTexture(green,0);
                            break;

                default :   p->setTexture(red,0);
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
    LX_Window *w = NULL;

    bool err = LX_Init();

    cout << " ==== Test Particle ==== " << endl;

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;

    w = new LX_Window("Test particle",LX_WINDOW_RENDERING);

    LX_WindowManager::getInstance()->addWindow(w);

    //File buffer of particle
    red = new LX_FileBuffer("test/asset/red.bmp");
    green = new LX_FileBuffer("test/asset/green.bmp");
    blue = new LX_FileBuffer("test/asset/blue.bmp");

    // Dot with particle
    dot = new Dot();

    SDL_Event e;
    int go = 1;

    while(go == 1)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                go = 0;
        }

        LX_WindowManager::getInstance()->getWindow(0)->clearRenderer();
        dot->update();
        LX_WindowManager::getInstance()->getWindow(0)->updateRenderer();

        SDL_Delay(16);
    }

    delete w;
    delete dot;
    delete red;
    delete green;
    delete blue;
    LX_Quit();

    cout << " ==== End Particle ==== " << endl;

    return EXIT_SUCCESS;
}
