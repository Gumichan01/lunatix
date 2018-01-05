
#include <LunatiX/Lunatix.hpp>

const int N = 8;

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
            case LX_EventType::QUIT:
                LX_Log::log("Quit Request");
                d = true;
                break;

            /// ---------------- Keyboard ----------------

            case LX_EventType::KEYUP:
                LX_Log::log("KEYBOARD INPUT");
                LX_Log::log("physical key → %s",stringOfScanCode(evh.getScanCode()).utf8_str());
                LX_Log::log("virtual key  → %s",stringOfKeyCode(evh.getKeyCode()).utf8_str());
                break;

            /// ---------------- Mouse ------------------

            case LX_EventType::MOUSEBUTTONUP:
                LX_Log::log("MOUSE BUTTON INPUT");
                LX_Log::log("window ID → %d",evh.getMouseButton().wid);
                LX_Log::log("button    → %d",evh.getMouseButton().button);
                LX_Log::log("state     → %d",evh.getMouseButton().state);
                LX_Log::log("clicks    → %d",evh.getMouseButton().clicks);
                LX_Log::log("X         → %d",evh.getMouseButton().x);
                LX_Log::log("Y         → %d",evh.getMouseButton().y);
                break;

            /*case LX_EventType::MOUSEMOTION:
                LX_Log::log("MOUSE MOTION INPUT");
                LX_Log::log("window ID  → %d",evh.getMouseMotion().wid);
                LX_Log::log("state → %d %d %d %d %d",
                            evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::LBUTTON)],
                            evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::MBUTTON)],
                            evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::RBUTTON)],
                            evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::X1)],
                            evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::X2)]);
                LX_Log::log("X          → %d",evh.getMouseMotion().x);
                LX_Log::log("Y          → %d",evh.getMouseMotion().y);
                LX_Log::log("X relative → %d",evh.getMouseMotion().xrel);
                LX_Log::log("Y relative → %d",evh.getMouseMotion().yrel);
                break;*/

            case LX_EventType::MOUSEWHEEL:
                LX_Log::log("MOUSE WHEEL INPUT");
                LX_Log::log("window ID → %d",evh.getMouseWheel().wid);
                LX_Log::log("X         → %d",evh.getMouseWheel().x);
                LX_Log::log("Y         → %d",evh.getMouseWheel().y);
                break;

            /// ---------------- Gamepad ----------------

            case LX_EventType::CONTROLLERBUTTONUP:
                LX_Log::log("GAMEPAD BUTTON INPUT");
                LX_Log::log("button which → %u",evh.getButton().which);
                LX_Log::log("button → %s",stringOfButton(evh.getButton().value).utf8_str());
                break;

            case LX_EventType::CONTROLLERAXISMOTION:
                if(evh.getAxis().value > 8192 || evh.getAxis().value < -8192)
                {
                    LX_Log::log("GAMEPAD AXIS INPUT");
                    LX_Log::log("move which → %u",evh.getAxis().id);
                    LX_Log::log("move → %s",stringOfAxis(evh.getAxis().axis).utf8_str());
                }
                break;

            case LX_EventType::CONTROLLERDEVICEADDED:
                LX_Log::log("NEW GAMEPAD ADDED");
                gid = evh.getGamepadID();
                LX_Log::log("move which → %u",gid);
                if(!g[gid].isConnected())
                {
                    g[gid].open(gid);
                    if(g[gid].isConnected())
                    {
                        LX_GamepadInfo gi;
                        g[gid].stat(gi);
                        LX_Log::log("%s",gamepadToString(gi).utf8_str());
                    }
                }
                break;

            case LX_EventType::CONTROLLERDEVICEREMOVED:
                LX_Log::log("GAMEPAD REMOVED");
                gid = evh.getGamepadID();
                LX_Log::log("move which → %u",gid);
                g[gid].close();
                break;

            case LX_EventType::WINDOWEVENT:
                LX_Log::log("WINDOW EVENT");
                printEvent(evh.getWindowEvent());
                break;

            /// ---------------- User Event ----------------

            case LX_EventType::USEREVENT:
                LX_Log::log("USER EVENT");
                LX_Log::log("window ID → %d",evh.getUserEvent().wid);
                LX_Log::log("code      → %d",evh.getUserEvent().code);
                break;

            /// ---------------- Drag and drop ----------------

            case LX_EventType::DROPFILE:
                LX_Log::log("DRAG & DROP EVENT");
                LX_Log::log("file → %s",evh.getDropEvent().file.c_str());
                break;

            default:
                break;
            }
        }
        LX_Timer::delay(33);
    }

    for(int k = 0; k < N; k++)
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
    case LX_WinEventType::WIN_SHOWN:
        LX_Log::log("Window %d shown", event.wid);
        break;

    case LX_WinEventType::WIN_HIDDEN:
        LX_Log::log("Window %d hidden", event.wid);
        break;

    case LX_WinEventType::WIN_EXPOSED:
        LX_Log::log("Window %d exposed", event.wid);
        break;

    case LX_WinEventType::WIN_MOVED:
        LX_Log::log("Window %d moved to %d,%d", event.wid, event.data1, event.data2);
        break;

    case LX_WinEventType::WIN_RESIZED:
        LX_Log::log("Window %d resized to %dx%d", event.wid, event.data1, event.data2);
        break;

    case LX_WinEventType::WIN_SIZE_CHANGED:
        LX_Log::log("Window %d size changed to %dx%d", event.wid, event.data1, event.data2);
        break;

    case LX_WinEventType::WIN_MINIMIZED:
        LX_Log::log("Window %d minimized", event.wid);
        break;

    case LX_WinEventType::WIN_MAXIMIZED:
        LX_Log::log("Window %d maximized", event.wid);
        break;

    case LX_WinEventType::WIN_RESTORED:
        LX_Log::log("Window %d restored", event.wid);
        break;

    case LX_WinEventType::WIN_ENTER:
        LX_Log::log("Mouse entered window %d", event.wid);
        break;

    case LX_WinEventType::WIN_LEAVE:
        LX_Log::log("Mouse left window %d", event.wid);
        break;

    case LX_WinEventType::WIN_FOCUS_GAINED:
        LX_Log::log("Window %d gained keyboard focus", event.wid);
        break;

    case LX_WinEventType::WIN_FOCUS_LOST:
        LX_Log::log("Window %d lost keyboard focus", event.wid);
        break;

    case LX_WinEventType::WIN_CLOSE:
        LX_Log::log("Window %d closed", event.wid);
        break;

    default:
        LX_Log::log("Window %d got unknown event %d", event.wid, event.evid);
        break;
    }
}
