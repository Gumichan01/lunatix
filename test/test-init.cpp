
#include <iostream>
#include <Lunatix/Lunatix.hpp>

using namespace std;


int main(int argc, char **argv)
{
    lx::Log::log(" ==== Test Init ==== ");
    bool err = lx::init();

    if(!err)
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - lx::init() failed");
    else
        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - The LunatiX library has been initialized with success");

    lx::quit();
    lx::Log::log(" ==== END Test Init ==== \n");
    return EXIT_SUCCESS;
}
