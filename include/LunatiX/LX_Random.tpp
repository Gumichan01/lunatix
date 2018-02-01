
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

template <typename T, typename std::enable_if<!std::is_same<T, char>::value, T>::type>
T xrand();

template <typename T, typename std::enable_if<!std::is_same<T, bool>::value, T>::type>
T xrand();

template <typename Num, typename std::enable_if<std::is_integral<Num>::value, Num>::type >
Num xrand()
{
    return static_cast<Num>(1024); // for testing
}
