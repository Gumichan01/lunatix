
#include <Lunatix/Log.hpp>
#include <Lunatix/Random.hpp>

void rand_unsigned();
void rand_float();

int main(int argc, char * argv[])
{
    LX_Random::initRand();
    rand_unsigned();
    rand_float();
    return 0;
}


void rand_unsigned()
{
    LX_Log::log("= Test random - unsigned value =");
    LX_Log::log("-> %u", LX_Random::xrand<unsigned int>());
    LX_Log::log("-> %lu", LX_Random::xrand<unsigned long>());
    LX_Log::log("-> %lu", LX_Random::xrand<unsigned long long>());
    LX_Log::log("-> %u", LX_Random::xrand<unsigned short>());

    LX_Log::log("-> %u", LX_Random::xrand(0U, 100U));
    LX_Log::log("-> %ul", LX_Random::xrand(0UL, 100UL));
    LX_Log::log("-> %u", LX_Random::xrand<unsigned short>(5, 10));
    LX_Log::log("-> %u", LX_Random::xrand<unsigned short>(1, 6));

    LX_Log::log("= Test random - unsigned value OK =");
}

void rand_float()
{
    LX_Log::log("= Test random - float value =");

    for(int i = 0; i < 10; ++i)
    {
        LX_Log::log("-> %f", LX_Random::fxrand());
    }

    LX_Log::log("--------");

    for(int i = 0; i < 10; ++i)
    {
        LX_Log::log("-> %f", LX_Random::fxrand(0.0f, 10000.0f));
    }

    LX_Log::log("= Test random - float value OK =");
}
