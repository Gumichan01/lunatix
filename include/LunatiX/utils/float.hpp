
/*
*   Copyright © 2018 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   This library is under the MIT license
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef FLOAT_HPP
#define FLOAT_HPP

#include <type_traits>

struct Float
{
    float v;
    /// Unboxing ≡ static_cast<float>(Float)
    operator float() const noexcept;
};

namespace FloatBox
{

template <typename N>
using Ftype = typename std::enable_if< std::is_arithmetic<N>::value &&
              !std::is_same<N,float>::value >::type;

/// Boxing
template <typename N>
inline constexpr Float fbox(Ftype<N> x) noexcept
{
    return Float{static_cast<float>(x)};
}

inline constexpr Float fbox(float x) noexcept
{
    return Float{ x };
}

constexpr Float FNIL = fbox(0.0f);

}

Float& operator ++(Float& x) noexcept;
Float operator ++(Float& x, int) noexcept;
Float& operator --(Float& x) noexcept;
Float operator --(Float& x, int) noexcept;


constexpr Float operator -(const Float& x) noexcept
{
    return Float{ -x.v };
}

constexpr Float operator +(const Float& x, const Float& y) noexcept
{
    return Float{ x.v + y.v };
}

constexpr Float operator -(const Float& x, const Float& y) noexcept
{
    return Float{ x.v - y.v };
}

constexpr Float operator *(const Float& x, const Float& y) noexcept
{
    return Float{ x.v * y.v };
}

constexpr Float operator /(const Float& x, const Float& y) noexcept
{
    return Float{ x.v / y.v };
}


Float& operator +=(Float& x, const Float& y) noexcept;
Float& operator -=(Float& x, const Float& y) noexcept;
Float& operator *=(Float& x, const Float& y) noexcept;
Float& operator /=(Float& x, const Float& y) noexcept;

bool operator ==(const Float& x, const Float& y) noexcept;
bool operator !=(const Float& x, const Float& y) noexcept;


namespace FloatMath
{

Float& abs(Float& f) noexcept;

Float& acos(Float& f) noexcept;
Float& asin(Float& f) noexcept;
Float& atan(Float& f) noexcept;

Float& cos(Float& f) noexcept;
Float& cosh(Float& f) noexcept;

Float& sin(Float& f) noexcept;
Float& sinh(Float& f) noexcept;

Float& tan(Float& f) noexcept;
Float& tanh(Float& f) noexcept;

Float& ceil(Float& f) noexcept;
Float& floor(Float& f) noexcept;

Float& exp(Float& f) noexcept;
Float& log(Float& f) noexcept;
Float& log10(Float& f) noexcept;

Float& pow(Float& f) noexcept;
Float& sqrt(Float& f) noexcept;

}

#endif // FLOAT_HPP
