

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



class Dot{

    LX_ParticleSystem *sys;
    LX_AABB box;

    public:

    Dot()
    {
        LX_Particle *p = NULL;
        srand(time(NULL));

        sys = new LX_ParticleSystem(16);
        box = {256,256,20,20};

        for(int i = 0; i < 16; i++)
        {
            p = new LX_Particle(box.x + (rand()%box.w),box.y + (rand()%box.h),5,5);
            p->setTexture("test/asset/red.bmp",0);

            sys->addParticle(p);
        }
    }

    void update()
    {
        LX_Particle *p = NULL;
        p = new LX_Particle(box.x + (rand()%box.w),box.y + (rand()%box.h),5,5);

        sys->updateParticles();
        if(sys->addParticle(p) == false)
        {
            delete p;
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

    Dot dot;
    int i = 0;

    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;

    LX_WindowManager::init();

    LX_WindowManager::getInstance()->addWindow(new LX_Window("Test particle",LX_WINDOW_RENDERING));


    while(i < 512)
    {
        LX_WindowManager::getInstance()->getWindow(0)->clearRenderer();
        dot.update();
        LX_WindowManager::getInstance()->getWindow(0)->updateRenderer();
        SDL_Delay(30);
        i += 4;
    }

    LX_WindowManager::destroy();

    LX_Quit();

    return EXIT_SUCCESS;
}
