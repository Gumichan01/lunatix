/*
    Main file for the demo
*/

#include <Lunatix/Library.hpp>
#include <Lunatix/Graphics.hpp>
#include <Lunatix/Event.hpp>
#include <Lunatix/Timer.hpp>
#include <Lunatix/Log.hpp>
#include <Lunatix/Version.hpp>

#define UNUSED(X) (void)(X)

int main( int argc, char ** argv )
{
    UNUSED( argc );
    UNUSED( argv );

    if ( !lx::init() )
    {
        lx::Log::log( "Cannot load the library: %s", LX_getError() );
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
    lx::Event::LX_EventHandler ev;
    bool go = true;

    while ( go )
    {
        while ( ev.pollEvent() )
        {
            switch ( ev.getEventType() )
            {
            case lx::Event::LX_EventType::QUIT:
                go = false;
                break;
            default:
                break;
            }
        }

        w.clearWindow();
        sprite.draw( position );
        w.update();
        lx::Time::delay( 33 );
    }

    lx::VersionInfo::info();
    lx::quit();
    return 0;
}
