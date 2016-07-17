

#include <LunatiX/Lunatix_engine.hpp>
#include <iostream>
#include <string>

void test_audioInit();
void test_music();
void test_chunk();
void test_fx();
void test_volume();


int main(int argc, char **argv)
{
    bool err = LX_Init();

    if(!err)
        std::cerr << "FAILURE - Init does not work" << std::endl;
    else
        std::cout << "SUCCESS - LunatiX Engine have been initialized with success"
                  << std::endl;

    LX_Log::setDebugMode();
    LX_Log::log(" ==== Test Audio ==== ");
    test_audioInit();
    LX_Log::log(" ==== End Audio ==== ");

    return EXIT_SUCCESS;
}


void test_audioInit()
{
    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION," = TEST audio = ");

    int n, freq, channels;
    Uint16 format;
    n = Mix_QuerySpec(&freq, &format, &channels);

    if(n == 0)
    {
        LX_Log::logError(LX_Log::LX_LOG_TEST,"Cannot get information: %s",
                        Mix_GetError());
    }
    else
    {
        std::string format_str = "Unknown";

        switch(format)
        {
            case AUDIO_U8: format_str="U8"; break;
            case AUDIO_S8: format_str="S8"; break;
            case AUDIO_U16LSB: format_str="U16LSB"; break;
            case AUDIO_S16LSB: format_str="S16LSB"; break;
            case AUDIO_U16MSB: format_str="U16MSB"; break;
            case AUDIO_S16MSB: format_str="S16MSB"; break;
            default: break;
        }
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"opened = %d time(s)",n);
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"frequency = %d Hz",freq);
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"format = %s",format_str.c_str());
        LX_Log::logInfo(LX_Log::LX_LOG_TEST,"channels = %d",channels);
    }

    LX_Log::logInfo(LX_Log::LX_LOG_APPLICATION," = END TEST = ");
}
