


#include <iostream>

#include "../src/engine/Lunatix_engine.hpp"

using namespace std;
using namespace LX_Device;

void test_joystick(void);
void test_gamepad(void);


int main(int argc, char **argv)
{
    bool err = false;

    int flag = SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER;

    cout << " ==== Test Device ==== " << endl;

    err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;


    if(SDL_WasInit(flag) != flag)
        cerr << "FAILURE - The device subsystem has not been initialized" << endl;
    else
        cout << "SUCCESS - The device subsystem has been initialized" << endl;

    // Joystick and Game controller
    cout << "\nYou have " << numberOfDevices() << " gamepad(s) connected " << endl;

    test_joystick();
    test_gamepad();

    LX_Quit();

    cout << " ==== END Test Device ==== " << endl;

    return EXIT_SUCCESS;
}



void test_joystick(void)
{
    LX_GamepadInfo gi;
    SDL_Joystick *joy = SDL_JoystickOpen(0);
    const char *str;

    if(joy != NULL)
    {
        if(statGamepad(joy,&gi) == -1)
            cerr << "FAILURE - Cannot get information : " << LX_GetError() << endl;
        else
        {
            str = gamepadToString(&gi);

            if(str == NULL)
                cerr << "FAILURE - Cannot get the string format of information" << endl;
            else
            {
                cout << "SUCCESS - Got the string format of joystick information" << endl;
                cout << str << endl;
            }

        }

        SDL_JoystickClose(joy);
    }
}


void test_gamepad(void)
{
    LX_Gamepad *gp = NULL;

    gp = new LX_Gamepad();

    if(gp->isConnected())
    {
        cout << "Connected " << endl;
        cout << "INFO - Gamepad - Name : " << gp->getName() << endl;
    }
    else
        cout << "INFO - No gamepad at index 0" << endl;


    delete gp;
}














