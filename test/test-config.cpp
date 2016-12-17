
#include <iostream>
#include <LunatiX/Lunatix.hpp>

using namespace std;
string boolState(const bool b);

string boolState(const bool b)
{
    return b ? "active":"inactive";
}


int main(int argc, char **argv)
{
    LX_Config::LX_Configuration *configuration = nullptr;
    LX_Config::LX_Configuration *configuration2 = nullptr;
    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - The LunatiX library has been initialized with success" << endl;

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Config ==== ");
    configuration  = LX_Config::LX_Configuration::getInstance();
    configuration2 = LX_Config::LX_Configuration::getInstance();

    if(configuration == nullptr)
        cerr << "FAILURE - The configuration is not initialized" << endl;
    else
        cout << "SUCCESS - The configuration is initialized" << endl;

    if(configuration != configuration2)
        cerr << "FAILURE - The configuration class is not instantiated as a singleton" << endl;
    else
        cout << "SUCCESS - The configuration class is instantiated as a singleton" << endl;

    bool video   = configuration->getVideoFlag();
    bool vsync   = configuration->getVSyncFlag();
    bool ttfont  = configuration->getTTFFlag();
    bool sound   = configuration->getAudioFlag();
    bool gamepad = configuration->getGamepadFlag();
    bool opengl  = configuration->getOpenGLFlag();
    int w        = configuration->getWinWidth();
    int h        = configuration->getWinHeight();

    cout << "\n==== LunatiX configuration ==== \n" << endl
         << "video: " << boolState(video) << endl
         << "true type font: " << boolState(ttfont) << endl
         << "vsync: " << boolState(vsync) << endl
         << "audio: " << boolState(sound) << endl
         << "gamepad: " << boolState(gamepad) << endl
         << "opengl: " << boolState(opengl) << endl
         << "width: " << w << endl << "height : " << h << endl;

    LX_Quit();
    LX_Log::log(" ==== END Test Config ==== \n");

    return EXIT_SUCCESS;
}
