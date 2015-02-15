

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
*	@version 0.1
*	@date January 18th, 2015
*
*
*/

#include <iostream>
#include <cstdio>

//#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
/*#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>*/

#include "engine/LX_lib.h"
#include "engine/LX_config.h"
#include "engine/LX_graphics.h"
#include "engine/LX_ttf.h"
#include "engine/LX_audio.h"
#include "engine/LX_physics.h"



int main ( int argc, char** argv )
{

    SDL_Rect pos = {400,200,150,120};
    SDL_Rect pos1 = {100,200,256,32};
    SDL_Rect pos2 = {100,250,768,32};

    SDL_Color color = {255,255,255};

    bool err;


    SDL_Surface *sf = NULL;
    SDL_Texture *st = NULL;

    std::string name = "data/cb.bmp";
    std::string mus = "data/Prototype Princess v1_01.wav";


    LX_graphics *graphics;
    LX_ttf *ttf;
    LX_Audio *audio;

    err = LX_Init();

    if(!err)
    {
        std::cout << "ERREUR" << std::endl;
        return EXIT_FAILURE;
    }

    //std::cout << "LX_Init returns true value" << std::endl;

    // initialization

    try
    {
        graphics = LX_graphics::createInstance();
        ttf = new LX_ttf(&color);
    }
    catch(std::exception & e )
    {
        std::cout << "exception occurred : " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    audio = new LX_Audio();

    // Load the texture from the data file
    st = graphics->loadTextureFromFile(name.c_str());

    if(st == NULL)
    {
        std::cerr << "LX_graphics::load_surface : " << SDL_GetError() <<std::endl;
    }

    audio->load_music(mus);

    bool game = true;
    SDL_Event event;

    SDL_Surface *tmp1 = ttf->draw_BlendedText("LunatiX_engine");
    SDL_Surface *tmp2 = ttf->draw_BlendedText("RETURN : play music, SPACE : pause/resume, BACKSPACE : stop");

    SDL_Texture *t1 = graphics->loadTextureFromSurface(tmp1);
    SDL_Texture *t2 = graphics->loadTextureFromSurface(tmp2);

    audio->musicVolume(MIX_MAX_VOLUME/2);
    std::cout << "Volume : " << audio->musicVolume(-1) <<std::endl;

    while(game)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {

                case SDL_KEYDOWN :  switch(event.key.keysym.sym)
                                    {
                                        case SDLK_ESCAPE:   game = false;
                                                            break;

                                        case SDLK_SPACE:    audio->pause_music();
                                                            break;

                                        case SDLK_RETURN:   audio->play_music();
                                                            break;

                                        case SDLK_BACKSPACE:    audio->stop_music();
                                                                break;

                                        default :   break;
                                    }
                                    break;


                case SDL_QUIT:  game=false;
                                break;


                default :   break;
            }
        }

        graphics->clearMainRenderer();

        graphics->putTexture(st,NULL,&pos); //graphics->put_surface(sf,NULL,&pos);

        if(t1 == NULL)
        {
            std::cerr << "LX_ttf::drawBlendedText : " << IMG_GetError() << std::endl;
        }
        else
        {
            graphics->putTexture(t1,NULL,&pos1);
        }


        if(t2 == NULL)
        {
            std::cerr << "LX_ttf::drawBlendedText : " << IMG_GetError() << std::endl;
        }
        else
        {
            graphics->putTexture(t2,NULL,&pos2);
        }


        graphics->updateMainRenderer();

        SDL_Delay(33);
    }


    SDL_FreeSurface(sf);
    SDL_DestroyTexture(st);
    SDL_DestroyTexture(t1);
    SDL_DestroyTexture(t2);
    SDL_FreeSurface(tmp1);
    SDL_FreeSurface(tmp2);

    delete audio;
    delete ttf;
    graphics->destroy();

    LX_Quit();



    // Load configuration
    LX_configuration *configuration;

    configuration = LX_configuration::getInstance();


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

    std::cout << "\nLunatiX engine configuration : " << video << std::endl;
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


    delete configuration;

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


/*int main(int argc,char **argv)
{
    SDL_Surface *s = NULL;
    SDL_Texture *t = NULL;
    SDL_Texture *tt = NULL;

    SDL_Rect r = {100,100,400,100};

    LX_graphics *graphics = NULL;
    LX_ttf *ttf = NULL;
    LX_Audio *audio = NULL;

    bool err;

    err = LX_Init();

    if(!err)
    {
        std::cerr << "ERREUR" << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        graphics = LX_graphics::getInstance();
        ttf = LX_ttf::getInstance();
    }
    catch(std::exception & e )
    {
        std::cerr << "exception occurred : " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    audio = new LX_Audio();


    s = graphics->loadSurface("data/cb.bmp");
    s = graphics->loadSurface("data/explosion.png");

    s = ttf->draw_BlendedText("LunatiX engine");

    if(s == NULL)
    {
        std::cerr << "hum " << std::endl;
        delete audio;
        delete ttf;
        delete graphics;
        LX_Quit();
        return EXIT_FAILURE;
    }

    t = graphics->loadTextureFromSurface(s);

    if(t == NULL)
        std::cout << "NULL " << std::endl;
    else
        std::cout << "YES" << std::endl;

    graphics->putTexture(t,NULL,&r);
    graphics->putTexture(s,NULL,&r);
    graphics->updateMainRenderer();

    SDL_Delay(2000);

    SDL_FreeSurface(s);
    SDL_DestroyTexture(t);
    delete audio;
    delete ttf;
    delete graphics;
    LX_Quit();

    return EXIT_SUCCESS;
}*/






























