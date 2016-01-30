/*
    Main file for the demo
*/

#include <iostream>

#include <LunatiX/Lunatix_engine.hpp>


static const int W = 256;
static const int H = 256;

using namespace std;
using namespace LX_Graphics;
using namespace LX_FileIO;
using namespace LX_VersionInfo;

void inputTextExperiment();

#if defined(__WIN32__)
int main(int argc, char** argv)
#else
int main()
#endif
{
    LX_Log::setDebugMode();

    if(!LX_Init())
    {
        cerr << "Cannot load the library: " << LX_GetError() << endl;
        return -1;
    }

    bool go = true;
    SDL_Event event;
    LX_AABB position = {0,0,W,H};
    LX_Window w(LX_WINDOW_RENDERING);
    SDL_Texture *texture = loadTextureFromFile("data/bullet.png",&w);

    w.setWindowSize(W,H);
    SDL_Delay(100);
    w.clearWindow();
    w.putTexture(texture,nullptr,&position);
    w.update();

    while(go)
    {
        inputTextExperiment();

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT : go = false;
                                break;
                default : break;
            }
        }

        SDL_Delay(33);
    }

    SDL_DestroyTexture(texture);

    // Information about
    LX_EngineVersionString();
    LX_Quit();

    return 0;
}


void inputTextExperiment()
{
    bool done = false;
    SDL_Color color = {0,0,0,0};
    /*string font_file = LX_Configuration::getInstance()->getFontFile();
    LX_TrueTypeFont::LX_Font font(font_file,color);*/
    SDL_Event event;
    string typed_text = "";

    SDL_LogInfo(LX_Log::LX_LOG_APPLICATION,"Test the text input");
    SDL_StartTextInput();

    if(SDL_IsTextInputActive())
        SDL_LogInfo(LX_Log::LX_LOG_APPLICATION,"Text input is active");
    else
        SDL_LogError(LX_Log::LX_LOG_APPLICATION,"Text input is noy active");

    while(!done)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_TEXTINPUT: typed_text += event.text.text;
                                    SDL_LogInfo(LX_Log::LX_LOG_APPLICATION,typed_text.c_str());
                                    break;

                case SDL_KEYDOWN:   if(event.key.keysym.sym == SDLK_RETURN)
                                        done = true;
                                    else if(event.key.keysym.sym == SDLK_BACKSPACE)
                                    {
                                        typed_text.pop_back();
                                        SDL_LogInfo(LX_Log::LX_LOG_APPLICATION,typed_text.c_str());
                                    }
            }
        }
        SDL_Delay(33);
    }

    SDL_StopTextInput();
}
























