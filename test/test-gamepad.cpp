
#include <LunatiX/Lunatix.hpp>

const int N = 4;

using namespace LX_Device;
using namespace LX_Event;

int main(int argc, char **argv)
{
    LX_Gamepad g[N];
    LX_GamepadID gid;

    LX_Init();
    LX_Log::setDebugMode();

    LX_Win::LX_WindowInfo winfo;
    LX_Win::LX_initWindowInfo(winfo);
    LX_Win::LX_Window w(winfo);

    int pads = numberOfDevices();

    if(pads > 0)
    {
        for(int i = 0; i < pads; i++)
        {
            g[i].open(i);
        }
    }

    for(int j = 0; j < pads; j++)
    {
        if(g[j].isConnected())
        {
            LX_GamepadInfo gi;
            g[j].stat(gi);
            LX_Log::log("%s",gamepadToString(gi).utf8_str());
        }
    }

    bool d = false;
    LX_EventHandler evh;

    while(!d)
    {
        while(evh.pollEvent())
        {
            switch(evh.getEventType())
            {
            case SDL_QUIT:
                d = true;
                break;

                /// ---------------- Keyboard ----------------

            case SDL_KEYUP:
                LX_Log::log("physical key → %s",stringOfScanCode(evh.getScanCode()).utf8_str());
                LX_Log::log("virtual key  → %s",stringOfKeyCode(evh.getKeyCode()).utf8_str());
                break;

                /// ---------------- Gamepad ----------------

            case SDL_CONTROLLERBUTTONUP:
                LX_Log::log("button which → %u",evh.getButton().which);
                LX_Log::log("button → %s",stringOfButton(evh.getButton().value).utf8_str());
                break;

            case SDL_CONTROLLERAXISMOTION:
                if(evh.getAxis().value > 8192 || evh.getAxis().value < -8192)
                {
                    LX_Log::log("move which → %u",evh.getAxis().id);
                    LX_Log::log("move → %s",stringOfAxis(evh.getAxis().axis).utf8_str());
                }
                break;

            case SDL_CONTROLLERDEVICEADDED:
                gid = evh.getGamepadID();
                LX_Log::log("move which → %u",gid);
                g[gid].open(gid);
                if(g[gid].isConnected())
                {
                    LX_GamepadInfo gi;
                    g[gid].stat(gi);
                    LX_Log::log("%s",gamepadToString(gi).utf8_str());
                }
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
                gid = evh.getGamepadID();
                LX_Log::log("move which → %u",gid);
                g[gid].close();
                break;

            default:
                break;
            }
        }
        LX_Timer::delay(33);
    }

    for(int k = 0; k < pads; k++)
    {
        g[k].close();
    }
    //g.close();
    LX_Quit();
    return 0;
}
