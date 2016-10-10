

/*
*    Copyright (C) 2016 Luxon Jean-Pierre
*    gumichan01.olympe.in
*
*    LunatiX is a free, SDL2-based library.
*    It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*    Luxon Jean-Pierre (Gumichan01)
*    luxon.jean.pierre@gmail.com
*/

#include <LunatiX/LX_Random.hpp>
#include <cinttypes>
#include <cstdlib>
#include <ctime>


// If UINT64_C was defined, we undefine it
#ifdef UINT64_C
#undef UINT64_C
#endif

// This macro expands to integer constants
#ifdef _MSC_VER
typedef unsigned __int64 uint64_t;
#define UINT64_C(val) (val##ui64)
#else
#define UINT64_C(val) (val##ULL)
#endif


/**
*    @file LX_Random.cpp
*    @brief The Random Number Generator implementation
*    @author Luxon Jean-Pierre(Gumichan01)
*    @version 0.8
*
*/


namespace LX_Random
{

void initRand()
{
    srand(static_cast<unsigned int>(time(nullptr)));
}


uint64_t xorshiftRand()
{
    static uint64_t x = 0;
    static bool first_call = false;

    if(first_call == false)
    {
        // x must be a nonzero value
        x = static_cast<uint64_t>(crand() + 1);
        first_call = true;
    }

    // The Xorshift* (64-bit generator)
    x ^= x >> 12; // a
    x ^= x << 25; // b
    x ^= x >> 27; // c
    return x * UINT64_C(2685821657736338717);
}


int crand()
{
    return rand();
}

};
