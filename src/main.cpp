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

    if(!LX_Init())
    {
        cerr << "Cannot load the library: " << LX_GetError() << endl;
        return -1;
    }


    LX_AABB position = {0,0,W,H};
    LX_Window w(LX_WINDOW_RENDERING);
    SDL_Texture *texture = loadTextureFromFile("data/bullet.png",&w);

    w.setWindowSize(W,H);
    SDL_Delay(100);
    w.clearWindow();
    w.putTexture(texture,nullptr,&position);
    w.update();

    SDL_Delay(3000);
    SDL_DestroyTexture(texture);

    // Information about SDL2 and the LunatiX engine
    SDL_version compiled;
    SDL_version linked;
    LX_Version luna;

    // Version of SDL
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);

    // Version of the LunatiX Engine
    LX_EngineVersion(luna);

    cout << "We compiled against SDL version "
         << static_cast<int>(compiled.major) << "."
         << static_cast<int>(compiled.minor) << "."
         << static_cast<int>(compiled.patch) << " ..." << endl;

    cout << "But we linked against SDL version "
         << static_cast<int>(compiled.major) << "."
         << static_cast<int>(compiled.minor) << "."
         << static_cast<int>(compiled.patch) << " ..." << endl;


    cout << "LunatiX Engine - Version " << luna.major << "." << luna.minor
         << "." <<  luna.patch << endl;

    LX_Quit();

    return 0;
}


