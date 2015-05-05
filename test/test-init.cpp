


#include <iostream>

#include "../src/engine/Lunatix_engine.hpp"

using namespace std;


int main(int argc, char **argv)
{
    bool err = false;

    cout << " ==== Test Init ==== " << endl;

    err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine have been initialized with success" << endl;

    LX_Quit();

    cout << " ==== END Test Init ==== " << endl;

    return EXIT_SUCCESS;
}
