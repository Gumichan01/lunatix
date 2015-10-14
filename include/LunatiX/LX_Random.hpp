#ifndef LX_RANDOM_HPP_INCLUDED
#define LX_RANDOM_HPP_INCLUDED


/*
*	Copyright (C) 2015 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*	LunatiX Engine is a SDL-based game engine.
*	It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*/


/**
*	@file LX_Random.hpp
*	@brief The Random Number Generator library
*	@author Luxon Jean-Pierre(Gumichan01)
*	@version 0.6
*
*/


#include <cinttypes>


// Macros
#define xorshiftRand100(void) xorshiftRand()%100    /**< Xorshift random value between 0 and 100 */
#define crand100(void) crand()%100                  /**< C random value between 0 and 100 */


/**
*	@namespace LX_Random
*	@brief The Random Number Generator (RNG) namespace
*
*   This namespace describes LX_Random. This random number generator is based on
*   the Xorshift* generator, but has also a support of the standard C generator
*
*/
namespace LX_Random
{

void initRand(void);
uint64_t xorshiftRand(void);
int crand(void);

};


#endif // LX_RANDOM_HPP_INCLUDED

