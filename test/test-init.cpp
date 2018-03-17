
#include <iostream>
#include <LunatiX/Lunatix.hpp>

using namespace std;


int main(int argc, char **argv)
{
    LX_Log::log(" ==== Test Init ==== ");
    bool err = LX_Init();

    if(!err)
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - LX_Init() failed");
    else
        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - The LunatiX library has been initialized with success");

    LX_Quit();
    LX_Log::log(" ==== END Test Init ==== \n");
    return EXIT_SUCCESS;
}
