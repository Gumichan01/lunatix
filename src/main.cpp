/*
    Main file for the demo
*/

#include <LunatiX/LX_Library.hpp>
#include <LunatiX/LX_Graphics.hpp>
#include <LunatiX/LX_Version.hpp>
#include <LunatiX/LX_Timer.hpp>
#include <LunatiX/LX_Log.hpp>


int main(int argc, char** argv)
{
    static const int W = 256;
    static const int H = 256;
    bool go = true;

    if(!LX_Init())
    {
        LX_Log::logCritical(LX_Log::LX_LOG_APPLICATION,"Cannot load the library: %s",
                            LX_GetError());
        return -1;
    }

    setSDLConfig(SDL_HINT_RENDER_SCALE_QUALITY,"linear");

    LX_AABB position = {0,0,W,H};
    LX_Win::LX_WindowInfo info;
    LX_Win::LX_loadWindowConfig(info);      // Load the default configuration
    LX_Win::LX_Window w(info);              // Create the window with this configuration

    w.setWindowSize(W,H);
    LX_Timer::delay(100);

    SDL_Event event;
    LX_Graphics::LX_Sprite sprite("data/bullet.png",w);

    while(go)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT :
                go = false;
                break;
            default :
                break;
            }
        }

        w.clearWindow();
        sprite.draw(&position);
        w.update();
        LX_Timer::delay(33);
    }

    // Information about the library
    LX_VersionInfo::LX_EngineInfo();
    LX_Quit();
    return 0;
}
