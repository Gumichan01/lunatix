
#include <Lunatix/Lunatix.hpp>
#include <iostream>

using namespace std;
using namespace lx::SystemInfo;

void testSys() noexcept;
void testTime1() noexcept;
void testTime2() noexcept;
void testTime3() noexcept;
void testTime4() noexcept;
void testConversion() noexcept;

int main( int argc, char ** argv )
{
    lx::Log::log( "global time prologue - value: %u ms", lx::Time::getTicks() );
    lx::init();
    lx::Log::log( "global time beginning - value: %u ms", lx::Time::getTicks() );
    lx::Log::setDebugMode();

    testSys();
    testTime1();
    testTime2();
    testTime3();
    testTime4();
    testConversion();
    lx::Log::log( "global time end - value: %u ms", lx::Time::getTicks() );
    lx::quit();

    return EXIT_SUCCESS;
}

void testSys() noexcept
{
    lx::Log::log( " ==== Test System ==== \n" );
    lx::Log::log( "System: %s", getPlatform().utf8_str() );
    lx::Log::log( "L1 cache size: %d KB", getCPUCacheLineSize() );
    lx::Log::log( "Number of CPU cores: %d", getCPUCount() );
    lx::Log::log( "RAM: %d MB\n ", getSystemRAM() );

    DisplayModes modes;
    getAvailableDisplayModes( modes );

    lx::Log::log( "Display modes: " );
    for ( auto mode : modes )
    {
        lx::Log::log( "%d × %d @ ~%d Hz", mode.w, mode.h, mode.refresh_rate );
    }

    lx::Log::log( " ==== End System ==== " );
}


void testTime1() noexcept
{
    lx::Log::log( " ==== Test Time 1 ==== \n" );
    lx::Time::Timer timer;

    lx::Log::log( "start" );
    timer.start();
    lx::Time::delay( 1000 );
    lx::Log::log( "ticks: %u", timer.getTicks() );
    lx::Time::delay( 1000 );
    lx::Log::log( "ticks: %u", timer.getTicks() );
    timer.stop();

    lx::Log::log( " ==== End Time 1 ==== \n" );
}

void testTime2() noexcept
{
    lx::Log::log( " ==== Test Time 2 ==== \n" );
    lx::Time::Timer timer;

    lx::Log::log( "start" );
    timer.start();
    lx::Log::log( "ticks0: %u", timer.getTicks() );
    lx::Time::delay( 1000 );
    lx::Log::log( "ticks1: %u", timer.getTicks() );
    lx::Time::delay( 500 );
    lx::Log::log( "pause" );
    timer.pause();
    lx::Log::log( "ticks2: %u", timer.getTicks() );
    lx::Time::delay( 500 );
    lx::Log::log( "ticks3: %u", timer.getTicks() );
    lx::Time::delay( 1000 );
    lx::Log::log( "ticks4: %u", timer.getTicks() );
    lx::Log::log( "resume" );
    timer.resume();
    lx::Time::delay( 1000 );
    lx::Log::log( "ticks5: %u", timer.getTicks() );

    lx::Time::delay( 500 );
    timer.pause();
    lx::Log::log( "ticks6: %u", timer.getTicks() );
    timer.resume();
    lx::Time::delay( 1000 );
    lx::Log::log( "ticks7: %u", timer.getTicks() );

    timer.stop();

    lx::Log::log( " ==== End Time 2 ==== \n" );
}

void testTime3() noexcept
{
    lx::Log::log( " ==== Test Time 3 ==== \n" );
    lx::Time::Timer timer;

    lx::Log::log( "start" );
    timer.start();
    lx::Log::log( "ticks0: %u", timer.getTicks() );
    lx::Time::delay( 1000 );
    lx::Log::log( "ticks1: %u", timer.getTicks() );
    lx::Time::delay( 1000 );
    lx::Log::log( "stop" );
    timer.stop();
    lx::Log::log( "ticks2: %u", timer.getTicks() );
    lx::Log::log( "reset" );
    timer.reset();
    lx::Time::delay( 1000 );
    lx::Log::log( "ticks3: %u", timer.getTicks() );
    lx::Time::delay( 500 );
    lx::Log::log( "start again" );
    timer.start();
    lx::Log::log( "ticks4: %u", timer.getTicks() );
    lx::Time::delay( 1000 );
    lx::Log::log( "ticks5: %u", timer.getTicks() );
    lx::Time::delay( 1000 );
    timer.pause();
    lx::Log::log( "ticks6: %u", timer.getTicks() );
    timer.resume();
    lx::Time::delay( 1000 );
    lx::Log::log( "ticks7: %u", timer.getTicks() );
    timer.stop();

    lx::Log::log( " ==== End Time 3 ==== \n" );
}

void testTime4() noexcept
{
    lx::Log::log( " ==== Test Time 4 ==== \n" );
    const uint32_t MIN_TIME = 1000U;
    const uint32_t MAX_TIME = 10000U;
    lx::Time::Timer timer;
    uint32_t total_time = 0U;
    uint32_t lap_time = 0U;

    lx::Random::initRand();
    lx::Log::log( "start" );
    timer.start();
    lx::Time::delay( lx::Random::xrand<uint32_t>( MIN_TIME, MAX_TIME ) );
    lap_time = timer.lap();
    total_time += lap_time;
    lx::Log::log( "lap 1: %u", lap_time );

    lx::Time::delay( lx::Random::xrand<uint32_t>( MIN_TIME, MAX_TIME ) );
    lap_time = timer.lap();
    total_time += lap_time;
    lx::Log::log( "lap 2: %u", lap_time );

    lx::Time::delay( lx::Random::xrand<uint32_t>( MIN_TIME, MAX_TIME ) );
    lap_time = timer.lap();
    total_time += lap_time;
    lx::Log::log( "lap 3: %u", lap_time );
    lx::Log::log( "total time: %u", total_time );
    timer.stop();

    lx::Log::log( " ==== End Time 4 ==== \n" );
}

void testConversion() noexcept
{
    lx::Log::log( " ==== Test Conversion ==== \n" );

    const uint32_t ONE_SEC = 1000U;
    const uint32_t ONE_MINUTE = 1000U * 60U;
    const uint32_t ONE_HOUR = 1000U * 3600U;

    const uint32_t ONE_SEC_X = 1U;
    const uint32_t ONE_MINUTE_X = 1U;
    const uint32_t ONE_HOUR_X = 1U;
    uint32_t v = lx::Time::seconds(ONE_SEC);

    if( v == ONE_SEC_X )
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - conversion millisecond to second" );
    else
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - expected: %u; got: %u", ONE_SEC_X, v );

    v = lx::Time::minutes(ONE_MINUTE);

    if( v == ONE_MINUTE_X )
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - conversion millisecond to minute" );
    else
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - expected: %u; got: %u", ONE_MINUTE_X, v );

    v = lx::Time::hours(ONE_HOUR);

    if( v == ONE_HOUR_X )
        lx::Log::logInfo( lx::Log::TEST, "SUCCESS - conversion millisecond to hour" );
    else
        lx::Log::logInfo( lx::Log::TEST, "FAILURE - expected: %u; got: %u", ONE_HOUR_X, v );

    lx::Random::initRand();
    uint32_t rv = lx::Random::xrand<uint32_t>( 1000U, 1000000000U );
    uint32_t s = lx::Time::seconds(rv);
    uint32_t m = lx::Time::minutes(rv);
    uint32_t h = lx::Time::hours(rv);

    lx::Log::log( "value (ms): %u ms", rv );
    lx::Log::log( "value (s): %u seconds", s );
    lx::Log::log( "value (m): %u minutes", m );
    lx::Log::log( "value (h): %u hours", h );

    lx::Log::log( " ==== End Conversion ==== \n" );

}
