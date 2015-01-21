

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


/*int main(int argc, char **argv)
{
   LX_configuration *config = NULL;

    config = LX_configuration::getInstance();

    std::cout << "OK for the conficguration" << std::endl;

    LX_configuration::destroy();

    return 0;
}*/

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


    sf = graphics->loadSurfaceFromBMP("data/cb.bmp");

    if(sf == NULL)
    {
        std::cerr << "LX_graphics::load_surface : " << SDL_GetError() <<std::endl;
    }

    audio->load_music(mus);

    bool game = true;
    SDL_Event event;


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

        std::cout << "clear" << std::endl;
        graphics->clearWindow();

        if(sf != NULL)
            graphics->put_surface(sf,NULL,&pos);

        ///@todo fix this bug. Check the return pointer of draw_BlendedText
        std::cout << "draw 1" << std::endl;
        SDL_Surface *tmp1 = ttf->draw_BlendedText("LunatiX_engine");
        std::cout << "result 1" << std::endl;

        if(tmp1 == NULL)
        {
            std::cout << "err 1" << std::endl;
            std::cerr << "LX_ttf::drawBlendedText : " << IMG_GetError() << std::endl;
        }
        else
        {
            std::cout << "OK 1" << std::endl;
            //graphics->put_surface(tmp1,NULL,&pos1);
        }
        std::cout << "draw 2" << std::endl;
        SDL_Surface *tmp2 = ttf->draw_BlendedText("RETURN : play music, SPACE : pause/resume, BACKSPACE : stop");
        std::cout << "result 2" << std::endl;

        if(tmp2 == NULL)
        {
            std::cerr << "LX_ttf::drawBlendedText : " << IMG_GetError() << std::endl;
        }
        else
            //graphics->put_surface(tmp2,NULL,&pos2);


        //graphics->updateMainWindow();

        SDL_Delay(33);
    }


    SDL_FreeSurface(sf);
    delete audio;
    ttf->destroy();
    graphics->destroy();

    LX_Quit();



    /** Load configuration */
    /*LX_configuration *configuration;

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


    delete configuration;*/



    return EXIT_SUCCESS;
}





