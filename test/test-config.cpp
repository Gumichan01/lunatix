



#include <iostream>

#include <LunatiX/Lunatix_engine.hpp>

using namespace std;


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


    int video = configuration->getVideoFlag();
    int ttfont = configuration->getTTF_Flag();
    int sound = configuration->getAudioFlag();
    int gamepad = configuration->getJoystickFlag();
    int opengl = configuration->getOpenGL_Flag();
    std::string font = configuration->getFontFile();
    int size = configuration->getFontSize();
    int w = configuration->getWinWidth();
    int h = configuration->getWinHeight();
    int f = configuration->getFullscreenFlag();


    std::cout << "\n==== LunatiX engine configuration ==== \n" << std::endl;
    std::cout << "video : " << video << std::endl;
    std::cout << "true type font : " << ttfont << std::endl;
    std::cout << "audio : " << sound << std::endl;
    std::cout << "gamepad : " << gamepad << std::endl;
    std::cout << "opengl : " << opengl << std::endl;
    std::cout << "font : " << font << std::endl;
    std::cout << "size : " << size << std::endl;
    std::cout << "width : " << w << std::endl;
    std::cout << "height : " << h << std::endl;
    std::cout << "fullscreen : " << f << std::endl;

    LX_Quit();

    cout << " ==== END Test Config ==== " << endl;

    return EXIT_SUCCESS;
}
