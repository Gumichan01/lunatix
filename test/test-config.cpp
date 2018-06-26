
#include <iostream>
#include <Lunatix/Lunatix.hpp>

using namespace std;
string boolState(const bool b);

string boolState(const bool b)
{
    return b ? "active":"inactive";
}


int main(int argc, char **argv)
{
    using namespace lx::Config;
    const lx::Configuration& configuration  = lx::Config::lx::Configuration::getInstance();
    const lx::Configuration& configuration2 = lx::Config::lx::Configuration::getInstance();

    lx::Log::setDebugMode();
    lx::Log::log(" ==== Test Config ==== ");

    if(&configuration != &configuration2)
        lx::Log::logInfo(lx::Log::TEST,"FAILURE - The configuration object is not a singleton");
    else
        lx::Log::logInfo(lx::Log::TEST,"SUCCESS - The configuration object is a singleton");

    bool video   = configuration.getVideoFlag();
    bool vsync   = configuration.getVSyncFlag();
    bool ttfont  = configuration.getTTFFlag();
    bool sound   = configuration.getAudioFlag();
    bool gamepad = configuration.getGamepadFlag();
    bool opengl  = configuration.getOpenGLFlag();

    lx::Log::logInfo(lx::Log::TEST,"======== Configuration ========");
    lx::Log::logInfo(lx::Log::TEST,"video: %s", boolState(video).c_str());
    lx::Log::logInfo(lx::Log::TEST,"true type font: %s", boolState(ttfont).c_str());
    lx::Log::logInfo(lx::Log::TEST,"vsync: %s", boolState(vsync).c_str());
    lx::Log::logInfo(lx::Log::TEST,"audio: %s", boolState(sound).c_str());
    lx::Log::logInfo(lx::Log::TEST,"gamepad: %s", boolState(gamepad).c_str());
    lx::Log::logInfo(lx::Log::TEST,"opengl: %s", boolState(opengl).c_str());
    lx::Log::logInfo(lx::Log::TEST,"===============================");

    lx::Log::log(" ==== END Test Config ==== \n");

    return EXIT_SUCCESS;
}
