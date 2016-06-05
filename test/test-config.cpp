
#include <iostream>
#include <LunatiX/Lunatix_engine.hpp>

using namespace std;
string boolState(const bool b);

string boolState(const bool b)
{
    if(b)
        return "active";

    return "inactive";
}


int main(int argc, char **argv)
{
    LX_Configuration *configuration = nullptr;
    LX_Configuration *configuration2 = nullptr;

    cout << endl << " ==== Test Config ==== " << endl;
    bool err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine was initialized with success" << endl;

    LX_Log::setDebugMode();
    configuration  = LX_Configuration::getInstance();
    configuration2 = LX_Configuration::getInstance();

    if(configuration == nullptr)
        cerr << "FAILURE - The configuration is not initialized" << endl;
    else
        cout << "SUCCESS - The configuration is initialized" << endl;

    if(configuration != configuration2)
        cerr << "FAILURE - The configuration class is not instantiated as a singleton" << endl;
    else
        cout << "SUCCESS - The configuration class is instantiated as a singleton" << endl;

    bool video   = configuration->getVideoFlag();
    bool ttfont  = configuration->getTTFFlag();
    bool sound   = configuration->getAudioFlag();
    bool gamepad = configuration->getJoystickFlag();
    bool opengl  = configuration->getOpenGLFlag();
    string font  = configuration->getFontFile();
    int size     = configuration->getFontSize();
    int w        = configuration->getWinWidth();
    int h        = configuration->getWinHeight();
    bool f       = configuration->getFullscreenFlag();

    std::cout << "\n==== LunatiX engine configuration ==== \n" << std::endl
              << "video : " << boolState(video) << std::endl
              << "true type font : " << boolState(ttfont) << std::endl
              << "audio : " << boolState(sound) << std::endl
              << "gamepad : " << boolState(gamepad) << std::endl
              << "opengl : " << boolState(opengl) << std::endl
              << "font : " << font << std::endl
              << "size : " << size << std::endl
              << "width : " << w << std::endl
              << "height : " << h << std::endl
              << "fullscreen : " << boolState(f) << std::endl;

    LX_Quit();
    cout << " ==== END Test Config ==== " << endl << endl;

    return EXIT_SUCCESS;
}
