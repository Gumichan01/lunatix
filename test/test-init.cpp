
#include <iostream>
#include <LunatiX/Lunatix_engine.hpp>

using namespace std;


int main(int argc, char **argv)
{
    LX_Log::log(" ==== Test Init ==== ");
    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - The LunatiX library has been initialized with success" << endl;

    LX_Quit();
    LX_Log::log(" ==== END Test Init ==== \n");
    return EXIT_SUCCESS;
}
