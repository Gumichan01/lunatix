
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
    friend typename std::enable_if<std::is_integral<Num>::value &&
    !std::is_same<Num, bool>::value &&
    !std::is_same<Num, char>::value, Num>::type xrand();
    friend uint64_t xorshiftRand() noexcept;

    _Prand() = delete;
    ~_Prand() = delete;
    _Prand(const _Prand& other) = delete;
    _Prand(_Prand&& other) = delete;
    _Prand& operator=(const _Prand& other) = delete;
    _Prand& operator=(_Prand&& other) = delete;

    static uint64_t rand();
};

template <typename Num>
typename std::enable_if<std::is_integral<Num>::value &&
!std::is_same<Num, bool>::value &&
!std::is_same<Num, char>::value, Num>::type xrand(Num min = 0,
        Num max = std::numeric_limits<Num>::max())
{
    return static_cast<Num>(_Prand::rand()) % (max - min) + min;
}
