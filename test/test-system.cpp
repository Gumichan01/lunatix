
#include <iostream>
#include <LunatiX/Lunatix_engine.hpp>

using namespace std;
using namespace LX_SystemInfo;


int main(int argc, char **argv)
{
    LX_Init();
    LX_Log::setDebugMode();

    cout << endl << " ==== Test System ==== " << endl;
    cout << "System : " << getPlatform() << endl;
    cout << "L1 cache size : " << getCPUCacheLineSize() << " KB" << endl;
    cout << "Number of CPU cores : " << getCPUCount() << endl;
    cout << "RAM : " << getSystemRAM() << " MB" << endl;

    int sz;
    const SDL_DisplayMode * mode = getDisplayModes(sz);

    if(mode != nullptr && sz != 0)
    {
        cout << "\nDisplay : " << endl;
        for(int i = 0; i < sz; i++)
        {
            cout << mode[i].w << " x " << mode[i].h << " @ ~"
                 << mode[i].refresh_rate << " Hz" << endl;
        }
    }
    else
    {
        cout << "INFO - " << LX_GetError() << endl ;
    }

    delete [] mode;
    cout << " ==== End System ==== " << endl << endl;
    LX_Quit();

    return EXIT_SUCCESS;
}
