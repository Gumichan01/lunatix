/*
    Main file for the demo
*/

#include <LunatiX/LX_Library.hpp>
#include <LunatiX/LX_Graphics.hpp>
#include <LunatiX/LX_Event.hpp>
#include <LunatiX/LX_Timer.hpp>
#include <LunatiX/LX_Log.hpp>
#include <LunatiX/LX_Version.hpp>

#define UNUSED(X) (void)(X)

using namespace LX_Event;

int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);
    LX_ImgRect position{0,0,256,256};
    LX_EventHandler event;
    bool go = true;
    std::string s("data/bullet.png");

    if(!LX_Init())
    {
        LX_Log::log("Cannot load the library: %s",LX_GetError());
        return -1;
    }

    // Information about how to build the window
    LX_Win::LX_WindowInfo info;
    LX_Win::LX_loadWindowConfig(info);
    info.w = 256;
    info.h = 256;

    LX_Win::LX_Window w(info);
    w.setIcon(s);
    LX_Graphics::LX_Sprite sprite(s, w);
    LX_Log::log("Display %s", sprite.getFileName().utf8_str());

    while(go)
    {
        while(event.pollEvent())
        {
            switch(event.getEventType())
            {
            case LX_EventType::QUIT:
                go = false;
                break;
            default:
                break;
            }
        }

        w.clearWindow();
        sprite.draw(&position);
        w.update();
        LX_Timer::delay(33);
    }

    LX_VersionInfo::info();
    LX_Quit();
    return 0;
}
