
#include <iostream>
#include <cstring>

#include <LunatiX/Lunatix.hpp>

#define STRING_SIZE 256

using namespace std;
using namespace LX_Device;

void test_gamepad(void);
void test_haptic(void);
void test_mouse(void);


int main(int argc, char **argv)
{
    Uint32 flag = SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER|SDL_INIT_HAPTIC;
    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - The LunatiX library has been initialized with success" << endl;

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Device ==== ");

    if(SDL_WasInit(flag) != flag)
        cerr << "FAILURE - The device subsystem has not been initialized" << endl;
    else
        cout << "SUCCESS - The device subsystem has been initialized" << endl;

    // Joystick and Game controller
    cout << "\nYou have " << numberOfDevices() << " gamepad(s) connected " << endl;

    test_gamepad();
    test_haptic();
    test_mouse();
    LX_Quit();

    LX_Log::log(" ==== END Test Device ==== ");
    return EXIT_SUCCESS;
}


void test_gamepad(void)
{
    LX_Log::log(" == Test Gamepad == ");

    {
        LX_Gamepad gp;

        if(gp.isConnected())
        {
            LX_Log::log("Name: %s",gp.getName());
            LX_Log::log("\n%s\n",gp.toString().utf8_str());
            LX_Haptic *hp = gp.getHaptic();

            if(hp != nullptr)
            {
                LX_Log::log("The device has force feedback");
                hp->rumbleEffectInit();
                hp->rumbleEffectPlay(1.0,100);
                SDL_Delay(500);
            }
            else
                LX_Log::log("No haptic");
        }
    }
    LX_Log::log(" == END TEST == ");
}


void test_haptic(void)
{
    LX_Haptic haptic(0);
    SDL_HapticEffect effect;

    LX_Log::log(" == Test Haptic == ");
    memset(&effect,0,sizeof(SDL_HapticEffect));

    if(haptic.isOpened())
    {
        LX_Log::log("Haptic device detected");

        if(haptic.rumbleEffectInit())
        {
            LX_Log::log("Play the rumble effect");
            haptic.rumbleEffectPlay(0.5,500);
            SDL_Delay(1000);
        }

        // Effect
        effect.type = SDL_HAPTIC_SINE;
        effect.periodic.direction.type = SDL_HAPTIC_POLAR;      // Polar coordinates
        effect.periodic.direction.dir[0] = 18000;               // Force comes from south
        effect.periodic.period = 1000;                          // 1000 ms
        effect.periodic.magnitude = 20000;                      // 20000/32767 strength
        effect.periodic.length = 5000;                          // 5 seconds long
        effect.periodic.attack_length = 1000;                   // Takes 1 second to get max strength
        effect.periodic.fade_length = 1000;                     // Takes 1 second to fade away

        LX_Log::log("Add a custom effect");
        int effectid = haptic.newEffect(effect);

        if(effectid < 0)
            LX_Log::logError(LX_Log::LX_LOG_TEST,"Cannot add effect: %s",LX_GetError());
        else
        {
            LX_Log::log("Run the effect");
            haptic.runEffect(effectid,1);
            SDL_Delay(5128);                                    // Wait for the effect to finish
        }

        LX_Log::log("Done");
    }
    else
        LX_Log::log("No haptic device");

    LX_Log::log(" == END TEST == ");
}


void test_mouse(void)
{
    LX_Log::log(" == Test Gamepad == ");
    LX_Win::LX_WindowInfo info;
    LX_Win::LX_initWindowInfo(info);
    info.w = 800;
    info.h = 600;
    LX_Win::LX_Window w(info);

    std::string s = "data/bullet.png";
    LX_Log::log("Define %s as the mouse cursor",s.c_str());
    LX_Graphics::LX_Surface img(s,w);
    LX_Device::LX_Mouse c(img,0,0);

    if(c.isOpen())
        LX_Log::logDebug(LX_Log::LX_LOG_TEST,"SUCCESS - the mouse cursor was loaded");
    else
        LX_Log::logDebug(LX_Log::LX_LOG_TEST,"FAILURE - not loaded; expeected: OK");

    c.setMouse();

    LX_Log::log("Try to get the haptic feedback of the mouse, if possible");

    if(LX_Device::mouseIsHaptic())
    {
        LX_Log::log("Haptic feedback supported by the mouse");
        LX_Haptic * h = getMouseHaptic();

        if(h == nullptr)
            LX_Log::log("FAILURE - The haptic feedback does not seem to be supported");
        else
        {
            LX_Log::log("SUCCESS - OK");
        }

        delete h;
    }
    else
    {
        LX_Log::log("Haptic feedback not supported by the mouse");
    }

    Uint32 t = SDL_GetTicks();
    SDL_Event ev;
    while(SDL_GetTicks() - t < 4000)
    {
        while(SDL_PollEvent(&ev))
        {
            switch(ev.type)
            {
            case SDL_MOUSEBUTTONUP:
                if(ev.button.button == SDL_BUTTON_RIGHT)
                    LX_Device::mouseCursorDisplay(0);
                else
                    LX_Device::mouseCursorDisplay(1);
                break;

            default: break;
            }
        }

        w.clearWindow();
        w.update();
        SDL_Delay(16);
    }

    LX_Log::log(" == END TEST == ");
}
