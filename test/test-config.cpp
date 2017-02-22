
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
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - LX_Init() failed");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The LunatiX library has been initialized with success");

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Config ==== ");
    configuration  = LX_Config::LX_Configuration::getInstance();
    configuration2 = LX_Config::LX_Configuration::getInstance();

    if(configuration == nullptr)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - The configuration is not initialized");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The configuration is initialized");

    if(configuration != configuration2)
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"FAILURE - The configuration class is not instantiated as a singleton");
    else
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"SUCCESS - The configuration class is instantiated as a singleton");

    bool video   = configuration->getVideoFlag();
    bool vsync   = configuration->getVSyncFlag();
    bool ttfont  = configuration->getTTFFlag();
    bool sound   = configuration->getAudioFlag();
    bool gamepad = configuration->getGamepadFlag();
    bool opengl  = configuration->getOpenGLFlag();
    int w        = configuration->getWinWidth();
    int h        = configuration->getWinHeight();

    LX_Log::logInfo(LX_Log::LX_LOG_TEST,"======== Configuration ========");
    LX_Log::logInfo(LX_Log::LX_LOG_TEST,"video: %s", boolState(video).c_str());
    LX_Log::logInfo(LX_Log::LX_LOG_TEST,"true type font: %s", boolState(ttfont).c_str());
    LX_Log::logInfo(LX_Log::LX_LOG_TEST,"vsync: %s", boolState(vsync).c_str());
    LX_Log::logInfo(LX_Log::LX_LOG_TEST,"audio: %s", boolState(sound).c_str());
    LX_Log::logInfo(LX_Log::LX_LOG_TEST,"gamepad: %s", boolState(gamepad).c_str());
    LX_Log::logInfo(LX_Log::LX_LOG_TEST,"opengl: %s", boolState(opengl).c_str());
    LX_Log::logInfo(LX_Log::LX_LOG_TEST,"width: %d ", w);
    LX_Log::logInfo(LX_Log::LX_LOG_TEST,"height: %d ", h);
    LX_Log::logInfo(LX_Log::LX_LOG_TEST,"===============================");

    LX_Quit();
    LX_Log::log(" ==== END Test Config ==== \n");

    return EXIT_SUCCESS;
}
