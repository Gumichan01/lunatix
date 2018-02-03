
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

#ifndef LX_RANDOM_HPP_INCLUDED
#define LX_RANDOM_HPP_INCLUDED

/**
*   @file LX_Random.hpp
*   @brief The Random Number Generator library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.12
*/

#include <type_traits>
#include <limits>
#include <cstdint>


/**
*   @ingroup System
*   @namespace LX_Random
*   @brief The Random Number Generator (RNG) namespace
*
*   This random number generator can be used using the Xorshift* generator,
*   or the standard C generator.
*/
namespace LX_Random
{

/**
*   @fn void initRand() noexcept
*   Initializes the random number generator
*   setting a seed
*/
void initRand() noexcept;

#define LX_Num \
typename std::enable_if<                                \
std::is_integral<Num>::value &&                         \
std::is_unsigned<Num>::value &&                         \
!std::is_same<Num, bool>::value &&                      \
!std::is_same<Num, unsigned char>::value, Num >::type   \

/// @todo doc
template <typename Num>
LX_Num xrand(Num min = 0, Num max = std::numeric_limits<Num>::max());


/**
*   @deprecated xorshiftRand() is deprecated and will be removed in v0.14.0
*
*   @fn uint64_t xorshiftRand() noexcept
*   Returns a pseudorandom number between 0 and (2^64 - 1)
*   @return An integer value between 0 and 2^64 - 1
*
*   @note This function uses the Xorshift* generator
*/
uint64_t xorshiftRand() noexcept;

/**
*   @deprecated crand() is deprecated and will be removed in v0.14.0
*
*   @fn int crand() noexcept
*
*   Returns a pseudorandom number between 0 and RAND_MAX (at least 32767)
*
*   @return An integer value between 0 and RAND_MAX
*   @note This function uses the standard C generator
*/
int crand() noexcept;

/**
*   @deprecated xorshiftRand100() is deprecated and will be removed in v0.14.0
*   @fn uint64_t xorshiftRand100() noexcept
*   Xorshift random value between 0 and 100
*   @return A random value generated by the Xorshift* RNG
*/
inline uint64_t xorshiftRand100() noexcept
{
    return LX_Random::xorshiftRand()%100;
}

/**
*   @deprecated crand100() is deprecated and will be removed in v0.14.0
*
*   @fn inline int crand100() noexcept
*   C random value between 0 and 100
*   @return A random value generated by the standard C RNG
*/
inline int crand100() noexcept
{
    return LX_Random::crand()%100;
}

#include "LX_Random.tpp"

}

#endif // LX_RANDOM_HPP_INCLUDED
