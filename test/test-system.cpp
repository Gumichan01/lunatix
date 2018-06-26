
#include <Lunatix/Lunatix.hpp>

using namespace std;
using namespace LX_SystemInfo;


int main(int argc, char **argv)
{
    lx::init();
    lx::Log::setDebugMode();

    lx::Log::log(" ==== Test System ==== \n");
    lx::Log::log("System: %s",getPlatform().utf8_str());
    lx::Log::log("L1 cache size: %d KB",getCPUCacheLineSize());
    lx::Log::log("Number of CPU cores: %d",getCPUCount());
    lx::Log::log("RAM: %d MB\n ",getSystemRAM());

    LX_DisplayModes modes;
    getAvailableDisplayModes(modes);

    lx::Log::log("Display modes: ");
    for(auto mode: modes)
    {
        lx::Log::log("%d × %d @ ~%d Hz", mode.w, mode.h, mode.refresh_rate);
    }

    lx::Log::log(" ==== End System ==== ");
    lx::quit();

    return EXIT_SUCCESS;
}
