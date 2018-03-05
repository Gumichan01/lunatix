
#include <LunatiX/utils/float.hpp>

#include <cmath>
#include <algorithm>
#include <limits>

Float::operator float() const noexcept
{
    return v;
}

Float& operator ++(Float& x) noexcept
{
    x.v += 1.0f;
    return x;
}

Float operator ++(Float& x, int) noexcept
{
    return Float{ x.v++ };
}

Float& operator --(Float& x) noexcept
{
    x.v -= 1.0f;
    return x;
}

Float operator --(Float& x, int) noexcept
{
    return Float{ x.v-- };
}


Float& operator +=(Float& x, const Float& y) noexcept
{
    x.v += y.v;
    return x;
}

Float& operator -=(Float& x, const Float& y) noexcept
{
    x.v -= y.v;
    return x;
}

Float& operator *=(Float& x, const Float& y) noexcept
{
    x.v *= y.v;
    return x;
}

Float& operator /=(Float& x, const Float& y) noexcept
{
    x.v /= y.v;
    return x;
}


/*
*   Implementation of a "safe" floating point comparison
*
*   This implementation is based on Nerdylicious's implementation
*   of floating point comparison program
*
*   https://github.com/Nerdylicious/FloatingPointComparison
*/
bool operator ==(const Float& x, const Float& y) noexcept
{
    static constexpr float EPSILON   = std::numeric_limits<float>::epsilon();
    static constexpr float FLOAT_MIN = std::numeric_limits<float>::min();
    static constexpr float FLOAT_MAX = std::numeric_limits<float>::max();

    const float abs_x = std::abs(x.v);
    const float abs_y = std::abs(y.v);
    const float diff  = std::abs(abs_x - abs_y);

    if(abs_x == abs_y)
    {
        return true;
    }
    else if(abs_x == 0.0f || abs_y == 0.0f || diff < FLOAT_MIN)
    {
        return diff < (EPSILON * FLOAT_MIN);
    }
    else
    {
        return (diff / std::min((abs_x + abs_y), FLOAT_MAX)) < EPSILON;
    }
}

bool operator !=(const Float& x, const Float& y) noexcept
{
    return !(x == y);
}


namespace FloatMath
{

Float& abs(Float& f) noexcept
{
    f.v = std::abs(f.v);
    return f;
}

Float& acos(Float& f) noexcept
{
    f.v = std::acos(f.v);
    return f;
}

Float& asin(Float& f) noexcept
{
    f.v = std::asin(f.v);
    return f;
}

Float& atan(Float& f) noexcept
{
    f.v = std::atan(f.v);
    return f;
}

Float& ceil(Float& f) noexcept
{
    f.v = std::ceil(f.v);
    return f;
}

Float& cos(Float& f) noexcept
{
    f.v = std::cos(f.v);
    return f;
}

Float& cosh(Float& f) noexcept
{
    f.v = std::cosh(f.v);
    return f;
}

Float& exp(Float& f) noexcept
{
    f.v = std::exp(f.v);
    return f;
}


Float& floor(Float& f) noexcept
{
    f.v = std::floor(f.v);
    return f;
}


Float& log(Float& f) noexcept
{
    f.v = std::log(f.v);
    return f;
}

Float& log10(Float& f) noexcept
{
    f.v = std::log10(f.v);
    return f;
}

Float& pow(Float& f, const Float& p) noexcept
{
    f.v = std::pow(f.v, p.v);
    return f;
}

Float& sin(Float& f) noexcept
{
    f.v = std::sin(f.v);
    return f;
}

Float& sinh(Float& f) noexcept
{
    f.v = std::sinh(f.v);
    return f;
}

Float& sqrt(Float& f) noexcept
{
    f.v = std::sqrt(f.v);
    return f;
}

Float& tan(Float& f) noexcept
{
    f.v = std::tan(f.v);
    return f;
}

Float& tanh(Float& f) noexcept
{
    f.v = std::tanh(f.v);
    return f;
}

}
