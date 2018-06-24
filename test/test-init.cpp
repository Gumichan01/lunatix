
#include <iostream>
#include <Lunatix/Lunatix.hpp>

using namespace std;


int main(int argc, char **argv)
{
    LX_Log::log(" ==== Test Init ==== ");
    bool err = lx::init();

    if(!err)
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - lx::init() failed");
    else
        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - The LunatiX library has been initialized with success");

    lx::quit();
    LX_Log::log(" ==== END Test Init ==== \n");
    return EXIT_SUCCESS;
}
