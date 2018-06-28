
#include <Lunatix/Lunatix.hpp>
#include <iostream>
#include <cstring>


using namespace std;
using namespace lx::Device;

void test_gamepad(void);
void test_haptic(void);
void test_mouse(void);


int main(int argc, char **argv)
{
    Uint32 flag = SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER|SDL_INIT_HAPTIC;
    bool err = lx::init();

    if(!err)
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - lx::init() failed");
    else
        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - The LunatiX library has been initialized with success");

    lx::Log::setDebugMode();
    lx::Log::log(" ==== Test Device ==== ");

    if(SDL_WasInit(flag) != flag)
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - The device subsystem has not been initialized");
    else
        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - The device subsystem has been initialized");

    // Joystick and Game controller
    lx::Log::logInfo(lx::Log::TEST,"You have %d gamepad(s) connected", numberOfDevices());

    test_gamepad();
    test_haptic();
    test_mouse();
    lx::quit();

    lx::Log::log(" ==== END Test Device ==== ");
    return EXIT_SUCCESS;
}


void test_gamepad(void)
{
    lx::Log::log(" == Test Gamepad == ");

    {
        LX_Gamepad gp;
        gp.open(0);

        if(gp.isConnected())
        {
            lx::Log::log("Name: %s",gp.getName());
            lx::Log::log("\n%s\n",gp.toString().utf8_str());
            LX_Haptic *hp = gp.getHaptic();

            if(hp != nullptr)
            {
                lx::Log::log("The device has force feedback");
                hp->rumbleEffectInit();
                hp->rumbleEffectPlay(1.0,100);
                lx::Time::delay(500);
            }
            else
                lx::Log::log("No haptic");
        }
        gp .close();
    }
    lx::Log::log(" == END TEST == ");
}


void test_haptic(void)
{
    LX_Haptic haptic(0);
    SDL_HapticEffect effect;

    lx::Log::log(" == Test Haptic == ");
    memset(&effect,0,sizeof(SDL_HapticEffect));

    if(haptic.isOpened())
    {
        lx::Log::log("Haptic device detected");

        if(haptic.rumbleEffectInit())
        {
            lx::Log::log("Play the rumble effect");
            haptic.rumbleEffectPlay(0.5,500);
            lx::Time::delay(1000);
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

        lx::Log::log("Add a custom effect");
        int effectid = haptic.newEffect(effect);

        if(effectid < 0)
            lx::Log::logError(lx::Log::TEST,"Cannot add effect: %s",LX_getError());
        else
        {
            lx::Log::log("Run the effect");
            haptic.runEffect(effectid,1);
            lx::Time::delay(5128);                                    // Wait for the effect to finish
        }

        lx::Log::log("Done");
    }
    else
        lx::Log::log("No haptic device");

    lx::Log::log(" == END TEST == ");
}


void test_mouse(void)
{
    lx::Log::log(" == Test Gamepad == ");
    LX_Win::LX_WindowInfo info;
    LX_Win::LX_initWindowInfo(info);
    info.w = 800;
    info.h = 600;
    LX_Win::LX_Window w(info);

    std::string s = "data/bullet.png";
    lx::Log::log("Define %s as the mouse cursor",s.c_str());
    lx::Device::LX_Mouse c(lx::Graphics::LX_BufferedImage(s),0,0);

    if(c.isOpen())
        lx::Log::logDebug(lx::Log::TEST,"SUCCESS - the mouse cursor was loaded");
    else
        lx::Log::logDebug(lx::Log::TEST,"FAILURE - not loaded; expeected: OK");

    c.setMouse();

    lx::Log::log("Try to get the haptic feedback of the mouse, if possible");

    if(lx::Device::mouseIsHaptic())
    {
        lx::Log::log("Haptic feedback supported by the mouse");
        LX_MouseHaptic h;

        if(h.isOpened())
            lx::Log::log("FAILURE - The haptic feedback does not seem to be supported");
        else
            lx::Log::log("SUCCESS - OK");
    }
    else
    {
        lx::Log::log("Haptic feedback not supported by the mouse");
    }

    Uint32 t = SDL_GetTicks();
    lx::Event::LX_EventHandler ev;
    while(SDL_GetTicks() - t < 4000)
    {
        while(ev.pollEvent())
        {
            switch(ev.getEventType())
            {
            case lx::Event::LX_EventType::MOUSEBUTTONUP:
                if(ev.getMouseButton().button == lx::Event::LX_MouseButton::LBUTTON)
                    lx::Device::mouseCursorDisplay(lx::Device::LX_MouseToggle::HIDE);
                else
                    lx::Device::mouseCursorDisplay(lx::Device::LX_MouseToggle::SHOW);
                break;

            default:
                break;
            }
        }

        w.clearWindow();
        w.update();
        lx::Time::delay(16);
    }

    lx::Log::log(" == END TEST == ");
}
