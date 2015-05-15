

#include <iostream>

#include "../src/engine/Lunatix_engine.hpp"

using namespace std;
using namespace LX_SystemInfo;



int main(int argc, char **argv)
{
    LX_Init();

    cout << " ==== Test System ==== " << endl;

    cout << "System : " << getPlatform() << endl;

    cout << " ==== End System ==== " << endl;
    LX_Quit();

    return EXIT_SUCCESS;
}
