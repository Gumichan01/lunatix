
#include <Lunatix/Log.hpp>
#include <Lunatix/Random.hpp>

void rand_unsigned();
void rand_float();

int main( int argc, char * argv[] )
{
    lx::Random::initRand();
    rand_unsigned();
    rand_float();
    return 0;
}


void rand_unsigned()
{
    lx::Log::log( "= Test random - unsigned value =" );
    lx::Log::log( "-> %u", lx::Random::xrand<unsigned int>() );
    lx::Log::log( "-> %lu", lx::Random::xrand<unsigned long>() );
    lx::Log::log( "-> %lu", lx::Random::xrand<unsigned long long>() );
    lx::Log::log( "-> %u", lx::Random::xrand<unsigned short>() );

    lx::Log::log( "-> %u", lx::Random::xrand( 0U, 100U ) );
    lx::Log::log( "-> %ul", lx::Random::xrand( 0UL, 100UL ) );
    lx::Log::log( "-> %u", lx::Random::xrand<unsigned short>( 5, 10 ) );
    lx::Log::log( "-> %u", lx::Random::xrand<unsigned short>( 1, 6 ) );

    lx::Log::log( "= Test random - unsigned value OK =" );
}

void rand_float()
{
    lx::Log::log( "= Test random - float value =" );

    for ( int i = 0; i < 10; ++i )
    {
        lx::Log::log( "-> %f", lx::Random::fxrand() );
    }

    lx::Log::log( "--------" );

    for ( int i = 0; i < 10; ++i )
    {
        lx::Log::log( "-> %f", lx::Random::fxrand( 0.0f, 10000.0f ) );
    }

    lx::Log::log( "= Test random - float value OK =" );
}
