/*
    Main file for the demo
*/

#include <LunatiX/Library.hpp>
#include <LunatiX/Graphics.hpp>
#include <LunatiX/Event.hpp>
#include <LunatiX/Timer.hpp>
#include <LunatiX/Log.hpp>
#include <LunatiX/Version.hpp>

#define UNUSED(X) (void)(X)

using namespace LX_Event;

int main( int argc, char ** argv )
{
    UNUSED( argc );
    UNUSED( argv );

    if ( !LX_Init() )
    {
        LX_Log::log( "Cannot load the library: %s", LX_getError() );
        return -1;
    }

    // Information about how to build the window
    LX_Win::LX_WindowInfo info;
    LX_Win::LX_loadWindowConfig( info );
    info.w = 256;
    info.h = 256;

    LX_Win::LX_Window w( info );
    const std::string s = "data/bullet.png";
    const LX_Graphics::LX_ImgRect position = { { 0, 0 }, 256, 256 };
    LX_Graphics::LX_Sprite sprite( s, w );
    LX_EventHandler ev;
    bool go = true;

    while ( go )
    {
        while ( ev.pollEvent() )
        {
            switch ( ev.getEventType() )
            {
            case LX_EventType::QUIT:
                go = false;
                break;
            default:
                break;
            }
        }

        w.clearWindow();
        sprite.draw( position );
        w.update();
        LX_Timer::delay( 33 );
    }

    LX_VersionInfo::info();
    LX_Quit();
    return 0;
}
