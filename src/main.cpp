

#include <iostream>

#include "engine/LX_lib.h"
#include "engine/LX_config.h"
#include "engine/LX_graphics.h"
#include "engine/LX_ttf.h"
#include "engine/LX_audio.h"
#include "engine/LX_physics.h"

/// @todo modify the music library + commit

int main ( int argc, char** argv )
{

    int error;
    SDL_Rect pos = {300,300,10,10};
    SDL_Rect pos1 = {100,200,10,10};
    SDL_Rect pos2 = {100,250,10,10};
    SDL_Color color = {255,255,255};

    bool err;


    SDL_Surface *sf = NULL;
    SDL_Surface *txt = NULL;

    std::string name = "data/cb.bmp";
    std::string mus = "data/Prototype Princess v1_01.wav";
    std::string sample = "data/Prototype Princess v1_01.wav";
    std::string font_file = "data/AozoraMinchoMedium.ttf";
    std::string engine_name = "LunatiX_engine";

    LX_window *win;
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

    /// GRAPHICS + TTF

    graphics = LX_graphics::getInstance();

    try
    {
        ttf = new LX_ttf(&color);
    }
    catch(std::exception & e )
    {
        std::cout << "exception occurred in LX_ttf constructor: " << e.what() << std::endl;
        return -16;
    }


    audio = new LX_Audio();

    LX_window::setTitle("LunatiX_engine");

    sf = graphics->load_BMP("data/cb.bmp");

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

        graphics->clear();

        graphics->put_image(sf,NULL,&pos);
        graphics->put_image(ttf->draw_BlendedText(engine_name),NULL,&pos1);
        graphics->put_image(ttf->draw_BlendedText("RETURN : play music, SPACE : pause/resume, BACKSPACE : stop"),NULL,&pos2);

        graphics->update();

        SDL_Delay(33);
    }


    SDL_FreeSurface(sf);
    delete audio;
    delete ttf;
    delete graphics;
    //delete win;

    LX_Quit();



    /// load configuration
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









