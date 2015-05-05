



#include <iostream>

#include "../src/engine/Lunatix_engine.hpp"

using namespace std;
using namespace LX_Device;


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
        cerr << "FAILURE - The device subsystem have not been initialized" << endl;
    else
        cout << "SUCCESS - The device subsystem hev been initialized" << endl;

    // Joystick and Game controller
    cout << "\nYou have " << numberOfDevices() << " gamepad(s) connected " << endl;

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
                cout << "SUCCES - Got the string format of joystick information" << endl;
                cout << str << endl;
            }

        }

        SDL_JoystickClose(joy);
    }

    LX_Quit();

    cout << " ==== END Test Device ==== " << endl;

    return EXIT_SUCCESS;
}
