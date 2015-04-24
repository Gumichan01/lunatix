

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
/*
int main ( int argc, char** argv )
{

    SDL_Rect pos = {400,200,150,120};
    SDL_Rect pos1 = {100,200,178,32};
    SDL_Rect pos2 = {100,250,768,32};

    SDL_Color color = {255,255,255};

    bool err, game = true;
    int wt, ht;

    SDL_Surface *sf = NULL;
    SDL_Texture *st = NULL;

    std::string name = "data/cb.bmp";
    std::string mus = "data/Prototype Princess v1_01.wav";

    LX_Renderer *graphics = NULL;
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

    try
    {
        graphics = LX_Renderer::createInstance();

    }
    catch(std::exception & e )
    {
        std::cout << "exception occurred : " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    ttf = new LX_Font(&color);
    audio = new LX_Music(mus);

    // Load the texture from the data file
    st = graphics->loadTextureFromFile(name.c_str());

    if(st == NULL)
    {
        std::cerr << "[MAIN] LX_Graphics::LX_Renderer::load_surface : " << SDL_GetError() <<std::endl;
    }

    ttf->sizeOfText("LunatiX_engine",&wt,&ht);
    std::cout << "[TEST TTF]Size of the text \"LunatiX_engine\" - w : " << wt << "; h : " << ht << std::endl;


    SDL_Texture *t1 = ttf->drawTextToTexture(LX_TTF_BLENDED,"LunatiX_engine",LX_TTF_DEFAULT_FONT_SIZE);
    SDL_Texture *t2 = ttf->drawTextToTexture(LX_TTF_BLENDED,"RETURN : play music, SPACE : pause/resume, BACKSPACE : stop",
                                                LX_TTF_DEFAULT_FONT_SIZE);

    audio->volume(MIX_MAX_VOLUME/2);
    std::cout << "Volume : " << audio->volume(-1) <<std::endl;
    std::cout << "Allocated channels : " << LX_Mixer::allocateChannels(16) <<std::endl;

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
                                        case SDLK_d :   graphics->setFullscreen(LX_GRAPHICS_FULLSCREEN_DESKTOP);
                                                        break;

                                        case SDLK_f :   graphics->setFullscreen(LX_GRAPHICS_FULLSCREEN);
                                                        break;

                                        case SDLK_g :   graphics->setFullscreen(LX_GRAPHICS_NO_FULLSCREEN);
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

        graphics->clearRenderer();

        graphics->putTexture(st,NULL,&pos);
        graphics->putTexture(t1,NULL,&pos1);
        graphics->putTexture(t2,NULL,&pos2);

        graphics->updateRenderer();

        SDL_Delay(33);
    }


    SDL_FreeSurface(sf);
    SDL_DestroyTexture(st);
    SDL_DestroyTexture(t1);
    SDL_DestroyTexture(t2);

    delete audio;
    delete ttf;
    LX_Renderer::destroy();

    std::cout << "Allocated channels : " << LX_Mixer::allocateChannels(0) <<std::endl;
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


*/


/* Main test to display a window, compilable */
int main( int argc, char** argv )
{
    int err;
    LX_Init();

    LX_Window * win = new LX_Window("Test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,600,480,0);

    LX_WindowManager::init();

    err = LX_WindowManager::getInstance()->addWindow(win);

    std::cout << err << std::endl;

    SDL_Delay(4000);

    err = LX_WindowManager::getInstance()->deleteWindow(err);

    std::cout << err << std::endl;

    LX_WindowManager::destroy();

    LX_Quit();
    return 0;
}
