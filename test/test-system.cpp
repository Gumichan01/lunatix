
#include <Lunatix/Lunatix.hpp>

using namespace std;
using namespace LX_SystemInfo;


int main(int argc, char **argv)
{
    lx::init();
    LX_Log::setDebugMode();

    LX_Log::log(" ==== Test System ==== \n");
    LX_Log::log("System: %s",getPlatform().utf8_str());
    LX_Log::log("L1 cache size: %d KB",getCPUCacheLineSize());
    LX_Log::log("Number of CPU cores: %d",getCPUCount());
    LX_Log::log("RAM: %d MB\n ",getSystemRAM());

    LX_DisplayModes modes;
    getAvailableDisplayModes(modes);

    LX_Log::log("Display modes: ");
    for(auto mode: modes)
    {
        LX_Log::log("%d × %d @ ~%d Hz", mode.w, mode.h, mode.refresh_rate);
    }

    LX_Log::log(" ==== End System ==== ");
    lx::quit();

    return EXIT_SUCCESS;
}
