
#include <LunatiX/utils/float.hpp>

#include <algorithm>
#include <limits>

Float::operator float() const noexcept
{
    return v;
}

Float& operator ++( Float& x ) noexcept
{
    x.v += 1.0f;
    return x;
}

Float operator ++( Float& x, int ) noexcept
{
    return Float{ x.v++ };
}

Float& operator --( Float& x ) noexcept
{
    x.v -= 1.0f;
    return x;
}

Float operator --( Float& x, int ) noexcept
{
    return Float{ x.v-- };
}


Float& operator +=( Float& x, const Float& y ) noexcept
{
    x.v += y.v;
    return x;
}

Float& operator -=( Float& x, const Float& y ) noexcept
{
    x.v -= y.v;
    return x;
}

Float& operator *=( Float& x, const Float& y ) noexcept
{
    x.v *= y.v;
    return x;
}

Float& operator /=( Float& x, const Float& y ) noexcept
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
bool operator ==( const Float& x, const Float& y ) noexcept
{
    static constexpr float EPSILON   = std::numeric_limits<float>::epsilon();
    static constexpr float FLOAT_MIN = std::numeric_limits<float>::min();
    static constexpr float FLOAT_MAX = std::numeric_limits<float>::max();

    const float abs_x = std::abs( x.v );
    const float abs_y = std::abs( y.v );
    const float diff  = std::abs( abs_x - abs_y );

    if ( abs_x == abs_y )
    {
        return true;
    }
    else if ( abs_x == 0.0f || abs_y == 0.0f || diff < FLOAT_MIN )
    {
        return diff < ( EPSILON * FLOAT_MIN );
    }
    else
    {
        return ( diff / std::min( ( abs_x + abs_y ), FLOAT_MAX ) ) < EPSILON;
    }
}

bool operator !=( const Float& x, const Float& y ) noexcept
{
    return !( x == y );
}
