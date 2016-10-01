
#include <iostream>
#include <LunatiX/Lunatix.hpp>

using namespace std;
using namespace LX_SystemInfo;


int main(int argc, char **argv)
{
    LX_Init();
    LX_Log::setDebugMode();

    LX_Log::log(" ==== Test System ==== \n");
    cout << "System : " << getPlatform() << endl;
    cout << "L1 cache size : " << getCPUCacheLineSize() << " KB" << endl;
    cout << "Number of CPU cores : " << getCPUCount() << endl;
    cout << "RAM : " << getSystemRAM() << " MB" << endl;

    LX_DisplayMode modes;
    LX_SystemInfo::getAvailableDisplayModes(modes);

    cout << "\nDisplay : " << endl;
    LX_Log::log("Display:\n ");
    for(auto it = modes.begin(); it != modes.end(); it++)
    {
        LX_Log::log("%d × %d @ ~%d Hz",(*it).w,(*it).h,(*it).refresh_rate);
    }

    LX_Log::log(" ==== End System ==== ");
    LX_Quit();

    return EXIT_SUCCESS;
}
