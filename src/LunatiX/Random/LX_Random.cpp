

/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	The LunatiX Engine is a SDL2-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/


#include <cstdlib>
#include <ctime>

#include <LunatiX/LX_Random.hpp>


/**
*	@file LX_Random.cpp
*	@brief The Random Number Generator implementation
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/


namespace LX_Random
{


/**
*   @fn void initRand(void)
*
*   Initializes the random number generator
*   setting a seed
*
*/
void initRand(void)
{
// Warning in thisfunction. Not imortant ! Ignore it !
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
    srand(time(nullptr));
#pragma clang diagnostic pop
}


/**
*   @fn uint64_t xorshiftRand(void)
*
*   Returns a pseudorandom number between 0 and (2^64 - 1)
*
*   @return An integer value between 0 and 2^64 - 1
*
*   @note This function uses the Xorshift* generator
*
*/
uint64_t xorshiftRand(void)
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



/**
*   @fn int crand(void)
*
*   Returns a pseudorandom number between 0 and RAND_MAX (at least 32767)
*
*   @return An integer value between 0 and RAND_MAX
*
*   @note This function uses the standard C generator
*
*/
int crand(void)
{
    return rand();
}

};

