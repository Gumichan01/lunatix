
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
    using namespace LX_Config;
    const LX_Configuration& configuration  = LX_Config::LX_Configuration::getInstance();
    const LX_Configuration& configuration2 = LX_Config::LX_Configuration::getInstance();

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Config ==== ");

    if(&configuration != &configuration2)
        LX_Log::logInfo(LX_Log::TEST,"FAILURE - The configuration object is not a singleton");
    else
        LX_Log::logInfo(LX_Log::TEST,"SUCCESS - The configuration object is a singleton");

    bool video   = configuration.getVideoFlag();
    bool vsync   = configuration.getVSyncFlag();
    bool ttfont  = configuration.getTTFFlag();
    bool sound   = configuration.getAudioFlag();
    bool gamepad = configuration.getGamepadFlag();
    bool opengl  = configuration.getOpenGLFlag();

    LX_Log::logInfo(LX_Log::TEST,"======== Configuration ========");
    LX_Log::logInfo(LX_Log::TEST,"video: %s", boolState(video).c_str());
    LX_Log::logInfo(LX_Log::TEST,"true type font: %s", boolState(ttfont).c_str());
    LX_Log::logInfo(LX_Log::TEST,"vsync: %s", boolState(vsync).c_str());
    LX_Log::logInfo(LX_Log::TEST,"audio: %s", boolState(sound).c_str());
    LX_Log::logInfo(LX_Log::TEST,"gamepad: %s", boolState(gamepad).c_str());
    LX_Log::logInfo(LX_Log::TEST,"opengl: %s", boolState(opengl).c_str());
    LX_Log::logInfo(LX_Log::TEST,"===============================");

    LX_Log::log(" ==== END Test Config ==== \n");

    return EXIT_SUCCESS;
}
