
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


class _Prand
{
private:

    template <typename Num>
    friend LX_Num<Num> xrand(Num, Num) noexcept;
    friend unsigned long long xorshiftRand() noexcept;

    _Prand() = delete;
    ~_Prand() = delete;
    _Prand(const _Prand& other) = delete;
    _Prand(_Prand&& other) = delete;
    _Prand& operator=(const _Prand& other) = delete;
    _Prand& operator=(_Prand&& other) = delete;

    static unsigned long long rand_() noexcept;
};

template <typename Num>
LX_Num<Num> xrand(Num min, Num max) noexcept
{
    return ( static_cast<Num>(_Prand::rand_()) % (max - min) ) + min;
}
