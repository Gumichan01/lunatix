
#include <LunatiX/Lunatix.hpp>

using namespace LX_Device;

int main(int argc, char **argv)
{
    LX_Init();
    LX_Log::setDebugMode();

    LX_Win::LX_WindowInfo winfo;
    LX_Win::LX_initWindowInfo(winfo);
    LX_Win::LX_Window w(winfo);

    LX_Gamepad g;
    g.open(0);

    if(g.isConnected())
    {
        LX_GamepadInfo gi;
        g.stat(gi);
        LX_Log::log("%s",gamepadToString(gi).utf8_str());
    }

    bool d = false;
    SDL_Event ev;

    while(!d)
    {
        while(SDL_PollEvent(&ev))
        {
            switch(ev.type)
            {
            case SDL_QUIT:
                d = true;
                break;

            /// ---------------- Keyboard ----------------

            case SDL_KEYUP:
                LX_Log::log("physical key → %s",stringOfPhysicalKey(ev.key.keysym.scancode).utf8_str());
                LX_Log::log("virtual key  → %s",stringOfVirtualKey(ev.key.keysym.sym).utf8_str());
                break;

            /// ---------------- Gamepad ----------------

            case SDL_CONTROLLERBUTTONUP:
                LX_Log::log("button → %s",stringOfButton(ev.cbutton.button).utf8_str());
                break;

            case SDL_CONTROLLERAXISMOTION:
                if(ev.caxis.value > 8192 || ev.caxis.value < -8192)
                {
                    LX_Log::log("move which → %u",ev.caxis.which);
                    LX_Log::log("move → %s",stringOfAxis(ev.caxis.axis).utf8_str());
                }
                break;

            default:
                break;
            }
        }
    }

    g.close();
    LX_Quit();
    return 0;
}
