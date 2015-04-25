

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
*	@version 0.2
*	@date January 18th, 2015
*
*
*/

#include <iostream>
#include <cstdio>

#include "engine/Lunatix_engine.hpp"

using namespace LX_Graphics;
using namespace LX_TrueTypeFont;

// Keep it in comments, it part of code is no longer compilable

int main ( int argc, char** argv )
{

    SDL_Rect pos = {400,200,150,120};
    SDL_Rect pos1 = {100,200,178,32};
    SDL_Rect pos2 = {100,250,768,32};

    SDL_Color color = {255,255,255};

    bool err, game = true;
    int wt, ht;

    SDL_Texture *st = NULL;
    SDL_Texture *ex = NULL;

    std::string name = "data/cb.bmp";
    std::string expl_str = "data/explosion.png";
    std::string mus = "data/Prototype Princess v1_01.wav";

    LX_Window *window = NULL;
    LX_Font *ttf = NULL;
    LX_Music *audio = NULL;

    SDL_Event event;


    err = LX_Init();

    if(!err)
    {
        std::cout << "ERREUR" << std::endl;
        return EXIT_FAILURE;
    }

    // initialization
    window = new LX_Window();

    LX_WindowManager::init();
    LX_WindowManager::getInstance()->addWindow(window);
    LX_WindowManager::getInstance()->addWindow(new LX_Window("Windows #2",512,512,600,480,SDL_WINDOW_RESIZABLE));

    ttf = new LX_Font(&color);
    audio = new LX_Music(mus);

    // Load the texture from the data file
    st = loadTextureFromFile(name.c_str(),0);
    ex = loadTextureFromFile(expl_str.c_str(),1);

    if(st == NULL)
    {
        std::cerr << "[MAIN] loadTexture : " << SDL_GetError() <<std::endl;
    }

    ttf->sizeOfText("LunatiX_engine",&wt,&ht);
    std::cout << "[TEST TTF]Size of the text \"LunatiX_engine\" - w : " << wt << "; h : " << ht << std::endl;


    SDL_Texture *t1 = ttf->drawTextToTexture(LX_TTF_BLENDED,"LunatiX_engine",LX_TTF_DEFAULT_FONT_SIZE,0);
    SDL_Texture *t2 = ttf->drawTextToTexture(LX_TTF_BLENDED,"RETURN : play music, SPACE : pause/resume, BACKSPACE : stop",
                                                LX_TTF_DEFAULT_FONT_SIZE,0);

    audio->volume(MIX_MAX_VOLUME/2);
    std::cout << "Volume : " << audio->volume(-1) <<std::endl;
    std::cout << "Allocated channels before : " << LX_Mixer::allocateChannels(16) <<std::endl;

    LX_Mixer::fadeInMusic(audio,4000);

    while(game)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {

                case SDL_KEYDOWN :  switch(event.key.keysym.sym)
                                    {
                                        case SDLK_ESCAPE :   game = false;
                                                            break;

                                        case SDLK_SPACE :    audio->pause();
                                                            break;

                                        case SDLK_RETURN :   audio->play();
                                                            break;

                                        case SDLK_BACKSPACE :   LX_Mixer::fadeOutMusic(4000);
                                                                break;
                                        case SDLK_d :   window->setFullscreen(LX_GRAPHICS_FULLSCREEN_DESKTOP);
                                                        break;

                                        case SDLK_f :   window->setFullscreen(LX_GRAPHICS_FULLSCREEN);
                                                        break;

                                        case SDLK_g :   window->setFullscreen(LX_GRAPHICS_NO_FULLSCREEN);
                                                        break;

                                        case SDLK_LEFT :    LX_Mixer::setPanning(MIX_CHANNEL_POST,255,0);
                                                            break;

                                        case SDLK_RIGHT :    LX_Mixer::setPanning(MIX_CHANNEL_POST,0,255);
                                                            break;

                                        case SDLK_UP :  LX_Mixer::setPanning(MIX_CHANNEL_POST,255,255);
                                                        break;

                                        default :   break;
                                    }
                                    break;


                case SDL_QUIT:  game=false;
                                break;


                default :   break;
            }
        }

        window->clearRenderer();

        window->putTexture(st,NULL,&pos);
        window->putTexture(t1,NULL,&pos1);
        window->putTexture(t2,NULL,&pos2);

        window->updateRenderer();

        // Put the image of explosion to the second window
        LX_WindowManager::getInstance()->getWindow(1)->putTexture(ex,NULL,&pos);
        LX_WindowManager::getInstance()->getWindow(1)->updateRenderer();

        SDL_Delay(33);
    }

    if(LX_WindowManager::getInstance()->getWindow(1024) == NULL)
        std::cout << "LX_WindowManager::getInstance()->getWindow(1024) is NULL " << std::endl;

    if(LX_WindowManager::getInstance()->deleteWindow(128) == -1)
        std::cout << "LX_WindowManager::getInstance()->deleteWindow(128) returned -1 " << std::endl;


    SDL_DestroyTexture(st);
    SDL_DestroyTexture(ex);
    SDL_DestroyTexture(t1);
    SDL_DestroyTexture(t2);

    delete audio;
    delete ttf;

    std::cout << "Allocated channels after : " << LX_Mixer::allocateChannels(0) <<std::endl;
    LX_WindowManager::destroy();
    LX_Quit();



    // Load configuration
    LX_Configuration *configuration;

    configuration = LX_Configuration::getInstance();


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


    LX_Configuration::destroy();

    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    printf("We compiled against SDL version %d.%d.%d ...\n",
                compiled.major, compiled.minor, compiled.patch);
    printf("But we linked against SDL version %d.%d.%d.\n",
                linked.major, linked.minor, linked.patch);

    return EXIT_SUCCESS;
}


