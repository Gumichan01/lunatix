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
        lx::Log::log( "Cannot load the library: %s", lx::getError() );
        return -1;
    }

    // Information about how to build the window
    lx::Win::WindowInfo info;
    lx::Win::loadWindowConfig( info );
    info.w = 256;
    info.h = 256;

    lx::Win::Window w( info );
    const std::string s = "data/bullet.png";
    const lx::Graphics::ImgRect position = { { 0, 0 }, 256, 256 };
    lx::Graphics::Sprite sprite( s, w );
    lx::Event::EventHandler ev;
    bool go = true;

    while ( go )
    {
        while ( ev.pollEvent() )
        {
            switch ( ev.getEventType() )
            {
            case lx::Event::EventType::QUIT:
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
