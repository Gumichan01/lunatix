
#include <iostream>
#include <cstring>

#include <LunatiX/Lunatix_engine.hpp>

#define STRING_SIZE 256

using namespace std;
using namespace LX_Device;

void test_gamepad(void);
void test_haptic(void);


int main(int argc, char **argv)
{
    Uint32 flag = SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER|SDL_INIT_HAPTIC;

    cout << endl << " ==== Test Device ==== " << endl;
    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;

    LX_Log::setDebugMode();

    if(SDL_WasInit(flag) != flag)
        cerr << "FAILURE - The device subsystem has not been initialized" << endl;
    else
        cout << "SUCCESS - The device subsystem has been initialized" << endl;

    // Joystick and Game controller
    cout << "\nYou have " << numberOfDevices() << " gamepad(s) connected " << endl;

    test_gamepad();
    test_haptic();
    LX_Quit();

    cout << " ==== END Test Device ==== " << endl << endl;
    return EXIT_SUCCESS;
}


void test_gamepad(void)
{
    cout << " == Test Gamepad == " << endl;

    {
        LX_Gamepad gp;

        if(gp.isConnected())
        {
            cout << "INFO - Name : " << gp.getName() << gp.toString() << endl;
            LX_Haptic *hp = gp.getHaptic();

            if(hp != nullptr)
            {
                hp->RumbleEffectInit();
                hp->RumbleEffectPlay(1.0,100);
                SDL_Delay(500);
            }
        }
    }
    cout << "  == End Test == " << endl;
}


void test_haptic(void)
{
    LX_Haptic haptic;
    SDL_HapticEffect effect;

    cout << "  == Test Haptic == " << endl;

    memset(&effect,0,sizeof(SDL_HapticEffect));

    if(haptic.isOpened())
    {
        if(haptic.RumbleEffectInit())
        {
            haptic.RumbleEffectPlay(0.5,500);
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

        int effectid = haptic.newEffect(&effect);

        if(effectid < 0)
            cerr << "INFO - Cannot add effect: " << LX_GetError() << endl;
        else
        {
            haptic.runEffect(effectid,1);
            SDL_Delay(5128);                                    // Wait for the effect to finish
        }

        cout << "INFO - Done" << endl;
    }
    else
        cout << "INFO - No haptic device" << endl;

    cout << "  == End Test == " << endl;
}
