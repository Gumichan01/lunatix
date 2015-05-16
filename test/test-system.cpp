

#include <iostream>

#include "../src/engine/Lunatix_engine.hpp"

using namespace std;
using namespace LX_SystemInfo;



int main(int argc, char **argv)
{
    LX_Init();

    cout << " ==== Test System ==== " << endl;

    cout << "System : " << getPlatform() << endl;
    cout << "L1 cache size : " << getCPUCacheLineSize() << " KB" << endl;
    cout << "Number of CPU cores : " << getCPUCount() << endl;
    cout << "RAM : " << getSystemRAM() << " MB" << endl;

    cout << " ==== End System ==== " << endl;

    LX_Quit();

    return EXIT_SUCCESS;
}
