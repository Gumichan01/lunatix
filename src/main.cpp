

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

#include "engine/LX_lib.h"
#include "engine/LX_config.h"
#include "engine/LX_graphics.h"
#include "engine/LX_ttf.h"
#include "engine/LX_audio.h"
#include "engine/LX_physics.h"



int main ( int argc, char** argv )
{

    SDL_Rect pos = {400,200,10,10};
    SDL_Rect pos1 = {100,200,10,10};
    SDL_Rect pos2 = {100,250,10,10};

    SDL_Color color = {255,255,255};

    bool err;


    SDL_Surface *sf = NULL;
    SDL_Surface *txt = NULL;
    SDL_Surface *background = NULL;

    std::string name = "data/cb.bmp";
    std::string mus = "data/Prototype Princess v1_01.wav";
    std::string sample = "data/Prototype Princess v1_01.wav";
    std::string font_file = "data/AozoraMinchoMedium.ttf";

    LX_graphics *graphics;
    LX_ttf *ttf;
    LX_Audio *audio;

    err = LX_Init();

    if(!err)
    {
        std::cout << "ERREUR" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "LX_Init returns true value" << std::endl;

    // initialization

    try
    {
        graphics = LX_graphics::getInstance();
        ttf = LX_ttf::getInstance();
    }
    catch(std::exception & e )
    {
        std::cout << "exception occurred : " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    audio = new LX_Audio();


    sf = graphics->loadSurfaceFromBMP(name.c_str());

    if(sf == NULL)
    {
        std::cerr << "LX_graphics::load_surface : " << SDL_GetError() <<std::endl;
    }

    audio->load_music(mus);

    bool game = true;
    SDL_Event event;

    SDL_Surface *tmp1 = ttf->draw_BlendedText("LunatiX_engine");
    SDL_Surface *tmp2 = ttf->draw_BlendedText("RETURN : play music, SPACE : pause/resume, BACKSPACE : stop");

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


        graphics->clearMainWindow();

        if(sf != NULL)
            graphics->put_surface(sf,NULL,&pos);


        if(tmp1 == NULL)
        {
            std::cerr << "LX_ttf::drawBlendedText : " << IMG_GetError() << std::endl;
        }
        else
        {
            graphics->put_surface(tmp1,NULL,&pos1);
        }


        if(tmp2 == NULL)
        {
            std::cerr << "LX_ttf::drawBlendedText : " << IMG_GetError() << std::endl;
        }
        else
        {
            graphics->put_surface(tmp2,NULL,&pos2);
        }


        //graphics->updateMainRenderer();
        graphics->updateMainWindow();

        SDL_Delay(33);
    }

    SDL_Texture *t1 = graphics->loadTextureFromSurface(tmp1);
    SDL_Texture *t2 = graphics->loadTextureFromSurface(tmp2);


    if(t1 == NULL)
    {
        std::cout << " t1 is NULL" << std::endl;
    }
    else
    {
        std::cout << " t1 exists" << std::endl;
        SDL_DestroyTexture(t1);
    }

    if(t2 == NULL)
    {
        std::cout << " t2 is NULL" << std::endl;
    }
    else
    {
        std::cout << " t2 exists" << std::endl;
        SDL_DestroyTexture(t2);
    }

    if(graphics->loadTextureFromSurface(NULL) == NULL)
    {
        std::cout << " The result is NULL : OK" << std::endl;
    }
    else
        std::cout << "What the hell ? " << std::endl;


    SDL_FreeSurface(sf);
    SDL_FreeSurface(tmp1);
    SDL_FreeSurface(tmp2);

    delete audio;
    ttf->destroy();
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



    return EXIT_SUCCESS;
}


/*int main(int argc,char **argv)
{
    SDL_Surface *s = NULL;
    SDL_Texture *t = NULL;

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


    //s = graphics->loadSurfaceFromBMP("data/cb.bmp");
    //s = graphics->loadSurface("data/explosion.png");

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

































