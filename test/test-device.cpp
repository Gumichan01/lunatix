


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

    test_gamepad();

    LX_Quit();

    cout << " ==== END Test Device ==== " << endl;

    return EXIT_SUCCESS;
}



void test_gamepad(void)
{
    LX_Gamepad *gp = NULL;

    gp = new LX_Gamepad();

    if(gp->isConnected())
    {
        cout << "Connected " << endl;
        cout << "INFO - Name of the gamepad : " << gp->getName() << endl;
        cout << gp->toString() << endl;
    }
    else
        cout << "INFO - No gamepad at index 0" << endl;


    delete gp;
}














