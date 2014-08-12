

#include <iostream>

#include "engine/TX_graphics.h"
#include "engine/TX_audio.h"
#include "engine/TX_ttf.h"
#include "engine/TX_physics.h"

int main ( int argc, char** argv )
{


    TX_Audio *audio = NULL;

    TX_graphics *graphics = NULL;
    TX_ttf *ttf = NULL;
    SDL_Color color = {255,255,255};

    SDL_Surface *bmp = NULL;

    SDL_Rect dstrect;
    dstrect.x = 200;
    dstrect.y = 300;

    SDL_Rect pos1;
    pos1.x = 100;
    pos1.y = 200;

    SDL_Rect pos2;
    pos2.x = 100;
    pos2.y = 250;

    std::string name = "data/cb.bmp";
    std::string mus = "data/Prototype Princess v1_01.wav";

    //std::string font_file = "Japonesa.ttf";
    std::string font_file = "data/AozoraMinchoMedium.ttf";

    graphics = new TX_graphics(1024,768,32);
    ttf = new TX_ttf(font_file,24,&color, graphics->getScreen());

    bmp = graphics->load_BMP(name);         // for the bmp images
    //bmp = graphics->load_image(name);     // for the other image types

    graphics->put_transparency(bmp,0,0,0);


    audio = new TX_Audio();

    audio->load_music(mus);


    SDL_Event event;
    bool game = true;

    while(game)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {

                case SDL_KEYDOWN :  switch(event.key.keysym.sym)
                                    {
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
        graphics->put_image(bmp,NULL,&dstrect);

        //ttf->draw_SolidText("GumichanO1 アカツキアライヴァル", &pos);   // test the japanese characters
        ttf->draw_BlendedText("Gumichan01's LunatiX-engine", &pos1);
        ttf->draw_BlendedText("RETURN : play music, SPACE : pause/resume, BACKSPACE : stop ", &pos2);

        //ttf->draw_BlendedText_WithSize("Gumichan01 Target Xplosion アカツキアライヴァル", 38, &pos);

        graphics->update();


        SDL_Delay(33);
    }

    delete audio;
    delete ttf;
    delete graphics;



    TX_Circle cir = {500,350,50,50*50};
    TX_Circle cir2 = {500,301,50,50*50};
    TX_AABB re = {484,306,32,32};
    TX_AABB re1 = {500,302,32,32};

    TX_physics phy;

    if(phy.collision( &cir, &re))
    {
        std::cout << "COLLISION" << std::endl;
    }
    else
    {
        std::cout << "FAUX" << std::endl;
    }

    // COLLISION AABB/AABB
    std::cout << "AABB/AAB" << std::endl;

    if(phy.collision( &re, &re1))
    {
        std::cout << "COLLISION" << std::endl;
    }
    else
    {
        std::cout << "FAUX" << std::endl;
    }

    // COLLISION CIRCLE/CIRCLE
    std::cout << "circle *2" << std::endl;

    if(phy.collision( &cir, &cir2))
    {
        std::cout << "COLLISION" << std::endl;
    }
    else
    {
        std::cout << "FAUX" << std::endl;
    }


    return EXIT_SUCCESS;
}
