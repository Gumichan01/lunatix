
#include <LunatiX/utils/float.hpp>

#include <cmath>
#include <algorithm>
#include <limits>

Float::operator float() const
{
    return v;
}

Float operator -(const Float& x)
{
    return Float{ -x.v };
}

Float& operator ++(Float& x)
{
    x.v += 1.0f;
    return x;
}

Float operator ++(Float& x, int)
{
    Float tmp{ x.v++ };
    return tmp;
}

Float& operator --(Float& x)
{
    x.v -= 1.0f;
    return x;
}

Float operator --(Float& x, int)
{
    Float tmp{ x.v-- };
    return tmp;
}

Float operator +(const Float x, const Float y)
{
    return Float{ x.v + y.v };
}

Float operator -(const Float x, const Float y)
{
    return Float{ x.v - y.v };
}

Float operator *(const Float x, const Float y)
{
    return Float{ x.v * y.v };
}

Float operator /(const Float x, const Float y)
{
    return Float{ x.v / y.v };
}

Float& operator +=(Float& x, const Float y)
{
    x.v += y.v;
    return x;
}

Float& operator -=(Float& x, const Float y)
{
    x.v -= y.v;
    return x;
}

Float& operator *=(Float& x, const Float y)
{
    x.v *= y.v;
    return x;
}

Float& operator /=(Float& x, const Float y)
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
bool operator ==(const Float& x, const Float& y)
{
    static const float EPSILON = std::numeric_limits<float>::epsilon();
    const float abs_x = fabsf(x);
    const float abs_y = fabsf(y);
    const float diff  = fabsf(x - y);

    if(abs_x == abs_y)
    {
        return true;
    }
    else if(abs_x == 0.0f || abs_y == 0.0f || diff < std::numeric_limits<float>::min())
    {
        return diff < (EPSILON * std::numeric_limits<float>::min());
    }
    else
    {
        return (diff / std::min((abs_x + abs_y),
                                std::numeric_limits<float>::max())) < EPSILON;
    }
}

bool operator !=(const Float& x, const Float& y)
{
    return !(x == y);
}

bool operator <(const Float& x, const Float& y)
{
    return x.v < y.v;
}

bool operator >(const Float& x, const Float& y)
{
    return x.v > y.v;
}

bool operator <=(const Float& x, const Float& y)
{
    return !(x.v > y.v);
}

bool operator >=(const Float& x, const Float& y)
{
    return !(x.v < y.v);
}
