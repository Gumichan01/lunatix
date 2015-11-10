

/*
*
*	Copyright (C)  Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*
*/

/**
*	@file main.cpp
*	@brief the main function which use the new LunatiX engine
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*	@date January 18th, 2015
*
*
*/

#include <iostream>
#include <cstdio>

#include <LunatiX/Lunatix_engine.hpp>

#define DEBUG_MAIN_TEST
#define TEXT_SIZE 256

using namespace LX_Graphics;
using namespace LX_TrueTypeFont;
using namespace LX_Device;
using namespace LX_Mixer;
using namespace LX_FileIO;
using namespace LX_MSGBox;
using namespace LX_VersionInfo;

#ifdef _WIN32_
int main(int argc, char** argv)
#else
int main()
#endif
{

    SDL_Rect pos = {400,200,150,120};
    SDL_Rect pos1 = {100,200,178,32};
    SDL_Rect pos2 = {100,250,768,32};
    SDL_Color color = {255,255,255,0};

    bool err, game = true;
    int wt, ht;

    SDL_Event event;

    SDL_Texture *st = NULL;
    SDL_Texture *ex = NULL;

    std::string name = "data/cb.bmp";
    std::string expl_str = "data/explosion.png";
    std::string mus = "data/Prototype Princess v1_01.wav";

    LX_Window *window = NULL;
    LX_Window *window2 = NULL;
    LX_Font *ttf = NULL;
    LX_Music *audio = NULL;

    err = LX_Init();

    if(!err)
    {
        std::cerr << "ERROR while Lauching the engine: " << LX_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    // initialization
    try
    {
        window = new LX_Window(LX_WINDOW_RENDERING);
        window2 = new LX_Window("Windows #2",512,512,600,480,LX_WINDOW_RENDERING,SDL_WINDOW_RESIZABLE);

        // getWindowManager() and LX_WindowManager::getInstance() are the same thing
        getWindowManager()->addWindow(window);
        LX_WindowManager::getInstance()->addWindow(window2);
    }
    catch(LX_WindowException & win_ex)
    {
        std::cerr << win_ex.what() << std::endl;
        return -1;
    }

    ttf = new LX_Font(color);
    audio = new LX_Music(mus);

    // Load the texture from the data file
    st = loadTextureFromFile(name.c_str());
    ex = loadTextureFromFile(expl_str.c_str(),1);

    if(st == NULL)
    {
        std::cerr << "[MAIN] loadTexture : " << LX_GetError() << std::endl;
    }

    ttf->sizeOfText("LunatiX_engine",wt,ht);

#ifdef DEBUG_MAIN_TEST
    std::cout << "[TEST TTF]Size of the text \"LunatiX_engine\" - w : " << wt << "; h : " << ht << std::endl;
#endif

    SDL_Texture *t1 = ttf->drawTextToTexture(LX_TTF_BLENDED,"LunatiX_engine",LX_TTF_DEFAULT_FONT_SIZE);
    SDL_Texture *t2 = ttf->drawTextToTexture(LX_TTF_BLENDED,"RETURN : play music, SPACE : pause/resume, BACKSPACE : stop",
                      LX_TTF_DEFAULT_FONT_SIZE);

    audio->volume(MIX_MAX_VOLUME/2);

#ifdef DEBUG_MAIN_TEST
    std::cout << "Volume : " << audio->volume(-1) <<std::endl;
    std::cout << "Allocated channels before : " << LX_Mixer::allocateChannels(16) <<std::endl;
#endif

    LX_Mixer::fadeInMusic(audio,4000);

    while(game)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {

            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE :
                    game = false;
                    showMSG(LX_MSG_INFO,"End of program","It is over",NULL);
                    break;

                case SDLK_SPACE :
                    audio->pause();
                    break;

                case SDLK_RETURN :
                    audio->play();
                    break;

                case SDLK_BACKSPACE :
                    LX_Mixer::fadeOutMusic(4000);
                    break;

                case SDLK_d :
                    window->setFullscreen(LX_GRAPHICS_FULLSCREEN_DESKTOP);
                    break;

                case SDLK_f :
                    window->setFullscreen(LX_GRAPHICS_FULLSCREEN);
                    break;

                case SDLK_g :
                    window->setFullscreen(LX_GRAPHICS_NO_FULLSCREEN);
                    break;

                case SDLK_LEFT :
                    LX_Mixer::setPanning(MIX_CHANNEL_POST,255,0);
                    break;

                case SDLK_RIGHT :
                    LX_Mixer::setPanning(MIX_CHANNEL_POST,0,255);
                    break;

                case SDLK_UP :
                    LX_Mixer::setPanning(MIX_CHANNEL_POST,255,255);
                    break;

                default :
                    break;
                }
                break;


            case SDL_QUIT:
                game=false;
                break;


            default :
                break;
            }
        }

        getWindowManager()->clearWindows();

        // Window is in the window manager, so its content was cleared
        window->putTexture(st,NULL,&pos);
        window->putTexture(t1,NULL,&pos1);
        window->putTexture(t2,NULL,&pos2);

        window->update();

        // Put the image of explosion to the second window
        // This is window2
        getWindowManager()->getWindow(1)->putTextureAndRotate(ex,NULL,&pos,45);

        getWindowManager()->updateWindows();

        SDL_Delay(33);
    }


    SDL_DestroyTexture(st);
    SDL_DestroyTexture(ex);
    SDL_DestroyTexture(t1);
    SDL_DestroyTexture(t2);

    delete audio;
    delete ttf;
    delete window;
    delete window2;

    // Gamepad
    LX_Gamepad *gp = new LX_Gamepad();
    char str[TEXT_SIZE];

    if(gp->isConnected())
    {
        gp->toString(str);

        std::cout << str << std::endl;
    }

    delete gp;

    // Version of SDL
    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    printf("We compiled against SDL version %d.%d.%d ...\n",
           compiled.major, compiled.minor, compiled.patch);
    printf("But we linked against SDL version %d.%d.%d.\n",
           linked.major, linked.minor, linked.patch);

    // Version of LunatiX Engine
    LX_Version luna;

    LX_EngineVersion(luna);

    printf("LunatiX Engine - Version %d.%d.%d \n",
           luna.major, luna.minor, luna.patch);

    LX_Quit();

    return EXIT_SUCCESS;
}


