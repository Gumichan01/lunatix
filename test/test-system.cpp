
#include <LunatiX/Lunatix.hpp>

using namespace std;
using namespace LX_SystemInfo;


int main(int argc, char **argv)
{
    LX_Init();
    LX_Log::setDebugMode();

    LX_Log::log(" ==== Test System ==== \n");
    LX_Log::log("System: %s",getPlatform().utf8_str());
    LX_Log::log("L1 cache size: %d KB",getCPUCacheLineSize());
    LX_Log::log("Number of CPU cores: %d",getCPUCount());
    LX_Log::log("RAM: %d MB\n ",getSystemRAM());

    LX_DisplayMode modes;
    getAvailableDisplayModes(modes);

    LX_Log::log("Display modes: ");
    for(auto it = modes.begin(); it != modes.end(); it++)
    {
        LX_Log::log("%d × %d @ ~%d Hz",(*it).w,(*it).h,(*it).refresh_rate);
    }

    LX_Log::log(" ==== End System ==== ");
    LX_Quit();

    return EXIT_SUCCESS;
}
