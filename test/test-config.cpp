



#include <iostream>

#include <LunatiX/Lunatix_engine.hpp>

using namespace std;


string boolState(const bool b)
{
    if(b)
        return "active";

    return "inactive";
}


int main(int argc, char **argv)
{
    bool err = false;
    LX_Configuration *configuration =  NULL;

    cout << " ==== Test Config ==== " << endl;

    err = LX_Init();

    if(!err)
        cerr << "FAILURE - Init does not work" << endl;
    else
        cout << "SUCCESS - LunatiX Engine was initialized with success" << endl;


    configuration = LX_Configuration::getInstance();

    if(configuration == NULL)
        cerr << "FAILURE - The singleton is not initialized" << endl;
    else
        cout << "SUCCESS - LunatiX Engine has a singleton configuration" << endl;


    bool video = configuration->getVideoFlag();
    bool ttfont = configuration->getTTF_Flag();
    bool sound = configuration->getAudioFlag();
    bool gamepad = configuration->getJoystickFlag();
    bool opengl = configuration->getOpenGL_Flag();
    std::string font = configuration->getFontFile();
    int size = configuration->getFontSize();
    int w = configuration->getWinWidth();
    int h = configuration->getWinHeight();
    bool f = configuration->getFullscreenFlag();


    std::cout << "\n==== LunatiX engine configuration ==== \n" << std::endl;
    std::cout << "video : " << boolState(video) << std::endl;
    std::cout << "true type font : " << boolState(ttfont) << std::endl;
    std::cout << "audio : " << boolState(sound) << std::endl;
    std::cout << "gamepad : " << boolState(gamepad) << std::endl;
    std::cout << "opengl : " << boolState(opengl) << std::endl;
    std::cout << "font : " << font << std::endl;
    std::cout << "size : " << size << std::endl;
    std::cout << "width : " << w << std::endl;
    std::cout << "height : " << h << std::endl;
    std::cout << "fullscreen : " << boolState(f) << std::endl;

    LX_Quit();

    cout << " ==== END Test Config ==== " << endl;

    return EXIT_SUCCESS;
}
