

/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#include <LunatiX/LX_Random.hpp>
#include <cstdlib>
#include <ctime>

namespace
{
using uint32 = unsigned int;
constexpr unsigned long long UINT64_V = 0x2545F4914F6CDD1DULL;
constexpr float UF_MAX = static_cast<float>(std::numeric_limits<uint32>::max());
}

namespace LX_Random
{

void initRand() noexcept
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

// private
unsigned long long _Prand::rand_() noexcept
{
    static unsigned long long x = 0;
    static bool first_call = false;

    if(!first_call)
    {
        // x must be a nonzero value
        x = static_cast<unsigned long long>(crand() + 1);
        first_call = true;
    }

    // The Xorshift* (64-bit generator)
    x ^= x >> 12; // a
    x ^= x << 25; // b
    x ^= x >> 27; // c
    return x * UINT64_V;

}

float fxrand(float minf, float maxf) noexcept
{
    const float R = static_cast<float>(xrand<unsigned int>());
    return ( (R / UF_MAX) + minf ) * maxf;
}

unsigned long long xorshiftRand() noexcept
{
    return _Prand::rand_();
}

int crand() noexcept
{
    return rand();
}

}
