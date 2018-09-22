
#include <Lunatix/Lunatix.hpp>
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;
using namespace lx::Event;
using namespace FloatBox;

using namespace lx::Graphics;
using namespace lx::TrueTypeFont;
using namespace lx::Device;
using namespace lx::Physics;
using namespace lx::ParticleEngine;
using namespace lx::FileIO;

#define N 20

namespace
{
Sprite * red;
Sprite * green;
Sprite * blue;
}

class Dot
{
    ParticleSystem * sys;
    FloatingBox box;

    Dot( Dot& d );

public:

    Dot()
    {
        Particle * p = nullptr;
        lx::Random::initRand();

        sys = new ParticleSystem( N );
        box = FloatingBox{FloatPosition{100.0f, 100.0f}, 20, 20};

        for ( int i = 0; i < N; i++ )
        {
            FloatingBox hitbox{FloatPosition{box.p.x - fbox( 5.0f ) + fbox( rand() % 25 ),
                                             box.p.y - fbox( 5.0f ) + fbox( rand() % 25 )}, 5, 5};

            switch ( rand() % 3 )
            {
            case 0 :
                p = new Particle( *red, hitbox );
                break;

            case 1 :
                p = new Particle( *blue, hitbox );
                break;

            case 2 :
                p = new Particle( *green, hitbox );
                break;

            default :
                p = new Particle( *red, hitbox );
                break;
            }

            sys->addParticle( p );
        }
    }

    void update()
    {
        Particle * p = nullptr;
        sys->updateParticles();
        moveBox( box, Vector2D{10.0f, 0.0f} );

        for ( int i = 0; i < N; i++ )
        {
            FloatingBox hitbox{FloatPosition{box.p.x - fbox( 5.0f ) + fbox( rand() % 25 ),
                                             box.p.y - fbox( 5.0f ) + fbox( rand() % 25 )}, 5, 5};

            switch ( rand() % 3 )
            {
            case 0 :
                p = new Particle( *red, hitbox );
                break;

            case 1 :
                p = new Particle( *blue, hitbox );
                break;

            case 2 :
                p = new Particle( *green, hitbox );
                break;

            default :
                p = new Particle( *red, hitbox );
                break;
            }

            if ( sys->addParticle( p ) == false )
            {
                delete p;
            }
        }

        sys->displayParticles();
    }

    ~Dot()
    {
        delete sys;
    }
};


int main( int argc, char ** argv )
{
    Dot * dot;
    Uint32 begin_time;

    bool err = lx::init();

    if ( !err )
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - lx::init() failed" );
    else
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - The LunatiX library has been initialized with success" );

    lx::Log::setDebugMode();
    lx::Log::log( " ==== Test Particle ==== \n" );

    lx::Win::WindowInfo winfo;
    lx::Win::loadWindowConfig( winfo );
    winfo.title = "Test particle";

    lx::Win::Window w( winfo );
    lx::Win::getWindowManager().addWindow( w );

    try
    {
        red = new Sprite( std::string( "test/asset/red.bmp" ), w );
        green = new Sprite( std::string( "test/asset/green.bmp" ), w );
        blue = new Sprite( std::string( "test/asset/blue.bmp" ), w );
        lx::Log::log( "SUCCESS - The three assets were successfully loaded" );
    }
    catch ( lx::Graphics::ImageException& ie )
    {
        lx::Log::log( "FAILURE - (At least) One of the three assets was not loaded" );
        lx::Log::log( "%s", ie.what() );
    }

    lx::Log::log( "Loading the dot" );
    dot = new Dot();
    lx::Log::log( "Dot loaded" );

    EventHandler e;
    int go = 1;
    begin_time = SDL_GetTicks();

    lx::Log::log( "The programm is running ..." );

    while ( go == 1 &&  ( ( SDL_GetTicks() - begin_time ) < 4000 ) )
    {
        while ( e.pollEvent() )
        {
            if ( e.getEventType() == EventType::QUIT )
                go = 0;
        }

        lx::Win::getWindowManager().clearWindows();
        dot->update();
        lx::Win::getWindowManager().updateWindows();
        lx::Time::delay( 16 );
    }

    lx::Win::getWindowManager().removeWindow( 0 );
    lx::Log::log( "End of program" );

    delete dot;
    delete blue;
    delete green;
    delete red;
    lx::quit();

    lx::Log::log( " ==== END Particle ==== \n" );
    return EXIT_SUCCESS;
}
