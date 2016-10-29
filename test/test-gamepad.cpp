
#include <LunatiX/Lunatix.hpp>

const int N = 4;

using namespace LX_Device;
using namespace LX_Event;

void printEvent(const LX_WEvent& event);


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
    LX_UserEvent usr;
    usr.wid = 1;
    usr.code = 42;
    evh.pushUserEvent(usr);

    while(!d)
    {
        while(evh.pollEvent())
        {
            switch(evh.getEventType())
            {
            case SDL_QUIT:
                LX_Log::log("Quit Request");
                d = true;
                break;

                /// ---------------- Keyboard ----------------

            case SDL_KEYUP:
                LX_Log::log("KEYBOARD INPUT");
                LX_Log::log("physical key → %s",stringOfScanCode(evh.getScanCode()).utf8_str());
                LX_Log::log("virtual key  → %s",stringOfKeyCode(evh.getKeyCode()).utf8_str());
                break;

                /// ---------------- Mouse ------------------

            case SDL_MOUSEBUTTONUP:
                LX_Log::log("MOUSE BUTTON INPUT");
                LX_Log::log("window ID → %d",evh.getMouseButton().wid);
                LX_Log::log("button    → %d",evh.getMouseButton().button);
                LX_Log::log("state     → %d",evh.getMouseButton().state);
                LX_Log::log("clicks    → %d",evh.getMouseButton().clicks);
                LX_Log::log("X         → %d",evh.getMouseButton().x);
                LX_Log::log("Y         → %d",evh.getMouseButton().y);
                break;

            case SDL_MOUSEMOTION:
                LX_Log::log("MOUSE MOTION INPUT");
                LX_Log::log("window ID  → %d",evh.getMouseMotion().wid);
                LX_Log::log("state → %d %d %d %d %d",
                            evh.getMouseMotion().state[LX_MOUSE_LBUTTON],
                            evh.getMouseMotion().state[LX_MOUSE_MBUTTON],
                            evh.getMouseMotion().state[LX_MOUSE_RBUTTON],
                            evh.getMouseMotion().state[LX_MOUSE_X1],
                            evh.getMouseMotion().state[LX_MOUSE_X2]);
                LX_Log::log("X          → %d",evh.getMouseMotion().x);
                LX_Log::log("Y          → %d",evh.getMouseMotion().y);
                LX_Log::log("X relative → %d",evh.getMouseMotion().xrel);
                LX_Log::log("Y relative → %d",evh.getMouseMotion().yrel);
                break;

            case SDL_MOUSEWHEEL:
                LX_Log::log("MOUSE WHEEL INPUT");
                LX_Log::log("window ID → %d",evh.getMouseWheel().wid);
                LX_Log::log("X         → %d",evh.getMouseWheel().x);
                LX_Log::log("Y         → %d",evh.getMouseWheel().y);
                break;

                /// ---------------- Gamepad ----------------

            case SDL_CONTROLLERBUTTONUP:
                LX_Log::log("GAMEPAD BUTTON INPUT");
                LX_Log::log("button which → %u",evh.getButton().which);
                LX_Log::log("button → %s",stringOfButton(evh.getButton().value).utf8_str());
                break;

            case SDL_CONTROLLERAXISMOTION:
                LX_Log::log("GAMEPAD AXIS INPUT");
                if(evh.getAxis().value > 8192 || evh.getAxis().value < -8192)
                {
                    LX_Log::log("move which → %u",evh.getAxis().id);
                    LX_Log::log("move → %s",stringOfAxis(evh.getAxis().axis).utf8_str());
                }
                break;

            case SDL_CONTROLLERDEVICEADDED:
                LX_Log::log("NEW GAMEPAD ADDED");
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
                LX_Log::log("GAMEPAD REMOVED");
                gid = evh.getGamepadID();
                LX_Log::log("move which → %u",gid);
                g[gid].close();
                break;

            case SDL_WINDOWEVENT:
                LX_Log::log("WINDOW EVENT");
                printEvent(evh.getWindowEvent());
                break;

                /// ---------------- User Event ----------------

            case SDL_USEREVENT:
                LX_Log::log("USER EVENT");
                LX_Log::log("window ID → %d",evh.getUserEvent().wid);
                LX_Log::log("code      → %d",evh.getUserEvent().code);
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

    LX_Quit();
    return 0;
}


void printEvent(const LX_WEvent& event)
{
    switch (event.evid)
    {
    case SDL_WINDOWEVENT_SHOWN:
        LX_Log::log("Window %d shown", event.wid);
        break;

    case SDL_WINDOWEVENT_HIDDEN:
        LX_Log::log("Window %d hidden", event.wid);
        break;

    case SDL_WINDOWEVENT_EXPOSED:
        LX_Log::log("Window %d exposed", event.wid);
        break;

    case SDL_WINDOWEVENT_MOVED:
        LX_Log::log("Window %d moved to %d,%d", event.wid, event.data1, event.data2);
        break;

    case SDL_WINDOWEVENT_RESIZED:
        LX_Log::log("Window %d resized to %dx%d", event.wid, event.data1, event.data2);
        break;

    case SDL_WINDOWEVENT_SIZE_CHANGED:
        LX_Log::log("Window %d size changed to %dx%d", event.wid, event.data1, event.data2);
        break;

    case SDL_WINDOWEVENT_MINIMIZED:
        LX_Log::log("Window %d minimized", event.wid);
        break;

    case SDL_WINDOWEVENT_MAXIMIZED:
        LX_Log::log("Window %d maximized", event.wid);
        break;

    case SDL_WINDOWEVENT_RESTORED:
        LX_Log::log("Window %d restored", event.wid);
        break;

    case SDL_WINDOWEVENT_ENTER:
        LX_Log::log("Mouse entered window %d", event.wid);
        break;

    case SDL_WINDOWEVENT_LEAVE:
        LX_Log::log("Mouse left window %d", event.wid);
        break;

    case SDL_WINDOWEVENT_FOCUS_GAINED:
        LX_Log::log("Window %d gained keyboard focus", event.wid);
        break;

    case SDL_WINDOWEVENT_FOCUS_LOST:
        LX_Log::log("Window %d lost keyboard focus", event.wid);
        break;

    case SDL_WINDOWEVENT_CLOSE:
        LX_Log::log("Window %d closed", event.wid);
        break;

    default:
        LX_Log::log("Window %d got unknown event %d", event.wid, event.evid);
        break;
    }
}

