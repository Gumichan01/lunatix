/*
    Main file for the demo
*/

#include <iostream>

#include <LunatiX/Lunatix_engine.hpp>


static const int W = 256;
static const int H = 256;

using namespace std;
using namespace LX_Graphics;
using namespace LX_FileIO;
using namespace LX_VersionInfo;

#if defined(__WIN32__)
int main(int argc, char** argv)
#else
int main()
#endif
{
    LX_Log::setDebugMode();

    if(!LX_Init())
    {
        cerr << "Cannot load the library: " << LX_GetError() << endl;
        return -1;
    }

    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION,"The program was load with success\n");

    bool go = true;
    SDL_Event event;
    LX_AABB position = {0,0,W,H};
    LX_Window w(LX_WINDOW_RENDERING);
    SDL_Texture *texture = loadTextureFromFile("data/bullet.png",&w);

    w.setWindowSize(W,H);
    SDL_Delay(100);
    w.clearWindow();
    w.putTexture(texture,nullptr,&position);
    w.update();

    while(go)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT : go = false;
                                break;
                default : break;
            }
        }

        SDL_Delay(33);
    }
    SDL_DestroyTexture(texture);

    // Information about
    LX_EngineVersionString();
    LX_Quit();

    return 0;
}

