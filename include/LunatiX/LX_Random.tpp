
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


template <typename Num>
typename std::enable_if<std::is_integral<Num>::value &&
                        !std::is_same<Num, bool>::value &&
                        !std::is_same<Num, char>::value, Num>::type xrand()
{
    return static_cast<Num>(1024); // for testing
}
